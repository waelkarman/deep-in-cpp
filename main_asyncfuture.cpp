#include <future>
#include <iostream>

using namespace std;

/*
la concorrenza ha senso solo se il problema è parallelizzabile
ha senso se devo fare operazioni tipo IO (su disco tipo) che comportano attese e nel mentre si puo continuare la computazione
questo si puo fare anche con 2 processi ma comporta una comunicazione interprocesso che è onerosa.

In C++ un programma classico è di tipo sequenziale e inizia dove viene definita la prima variabile globale e poi si esegue
il main e termina con la distruzione dell ultima variabile globale ha un comportamento deterministico a parità di ingresso
si fa sempre la stessa cosa. l OS garantisce l isolamento in memoria allo stesso indirizzo virtuale 10 corrispondono diversi
indirizzi reali

La programmazione concorrente parte quando nello stesso spazio di indirizzamento allo scopo di risolvere lo stesso problema
2 o piu flussi di esecuzione vengono eseguiti ogni uno fa cose diverse
 i programmi partono tutti con lo stesso thread principale poi questi lancia altri thread che vengono eseguiti nello stesso
spazio di indirizzamento quindi l indirizzi per un thread corrisponderanno agli stessi indirizzi per gli altri thread
Quando un programma multi thread viene eseguito il risultato non diventa dipendente solo dalgi ingressi ma anche da tanti
 altri fattori indiendenti perche l'avantamento dei thread non è deterministico.

ad ogni thread il sistema operativo associa una struttura dati protetta nel kernel dove si scrive a cosa è arrivato il
thread per gestire il contex swithch

occorre sincronizzare i thread

 problemi di sincronizzazione:
- deadlock(io aspetto te tu aspetti me),
- livelock(continuo finche tu non dici basta ma se tu non mi dici basta perche non riesci io continuo all infinito),
- starvation(qualcun altro ha sempre prioritàe passa sempre prima e io non faccio nulla)
- ECC

fino al c++ 2011 bisognava create i thread differentemente per ogni sistema operativo

Tipicamente un processore moderno contiene 3 livelli di cache di cui 2 relative ai singoli soc e una globale di livello 3
e le informazioni bengono propagate su queste cacheche e quando il dato raggiounge la cache globale viene viso da tutti i
soc

il problema della propagazione dei dati fra le cache è gestito con le fence-barriere l'assembler dei sistemi multi core
hanno istruzioni barriera che quando si vuole che altri vedano i dati forzano il flush della cache. bloccano i processori
scaricano la cache e riprendono. queste istruzioni sono diverse fra i diversi processori
la barriera e quindi la sincronizzazione è costosa e rallenta l' esecuzione. in caso intel x86 esistono diverse istruzioni barriera
 -mfence full memory fence
 -sfence store fence nessuno scrive piu finche non si sincronizza qunato scritto
 -lfence load fence nessuno legge finche non viene sincromnizzata la lettura

-> troppi process abbattono le prestazioni per i troppi cambi di contesto - thrashing
-> memory fence in assembly

processori e compilatori possono fare la speculative processing ovvero possono scambiare le istruzioni che non cambiano
nulla dal punto di vista del programma tipo 2 scritture consecutive indipendenti.

oltre i problemi classici i processori multi core per ogni core hanno delle cache quindi il dato puo diventare visibile
al sistema anche tempo dopo la sua effettiva computazione per regolare la sincronizzazione fra cache e ram esistono delle
istruzioni di fence nell assembler che sono incorporate nelle istruzioni di sincronizzazione del c++
per alcune operazioni è comodo tenere un informazione in un registro ma bisogna tenere a mente che così facendo il resto del
sistema non la vede. l ottimizzazione del compilatore si puo disattivare usando la keyword volatile che è utile solo per le
variabili condivise (se no si perde solo del tempo ). volatile non ha alcun effetto sul sottosistema di cache semplicemente
evita che il compilatore ottimizzi (tenga la variabile in un registro per esempio) usare volatile non basta perche questi
non agiscono sui memory fence quindi bisogna per forza usare i costrutti del c++ per la sincronizzazione.

esistono due metodi per scrivere programmi concorrenti uno di alto livello che si chiama std::async basato sulla copia e sugli
oggetti std::future se questi non sono sufficienti ci sono altre classi che permettono di manipolare i thread a basso livello
come la classe thread, mutex, condition variable, atomic

async e future si puo usare quando i c'è il thread principale che crea altri thread con compiti distinti e indipendenti e
raccoglie i risultati finali se il lavoro di un thread diventa interdipendente dal lavoro degli altri thread allora non
basta piu e bisogna usare le classi di manipolazione dei thread

async prende in ingresso un oggetto callable quindi un funzionale o puntatore a funzione e anche i suoi parametri. Async restituisce
un oggetto future l oggetto future ha un metodo get con cui è possibile avere il valore di ritorno del thread se pronto oppure và
in blocco finche il thread non termina o lancia un eccezione. se l oggetto è morto con un eccezione allora lancia l' eccezione
alla chiamata di get. se non ha iniziato forza l esecuzione. future<> avrà il tipo di ritorno dell oggetto callable associato.
la chiamata a get funge anche da sincronizzatore contiene un memory fence.

async puo essere chiamato con diverse modalità che indicano come dovrà essere eseguito.

- std::launch::async -> crea un thread che la svolga
possibile che il systema non abbia risorse per creare un thread e quindi ritorna un eccezione

- std::launch::deferred -> crea l oggetto ma mettilo da parte se non faccio la get non lo fare e chi fa get esegue il codice

creare dei thread costa bisogna allocale risorse quindi non si puo creare un thread per ogni cosa
agoritmo somma con thread  reg11 : 1:11:00

quando si chiama get il valore ritorna one shot se si vuole solo controllare se sia pronto o meno si puo chiamare wait che
aspetta che il thread termini senza prelevarne il valore

esistono anche altre funzioni come
- wait_for: aspetta un tempo fissato in millisecondi e poi se il dato è pronto ritorna true e false altrimenti (std::chrono::duration)
- wait_until: aspetta fino ad un orario precisato (std::chrono::timepoint)

restituiscono:
- std::future_status::deferred se non ancora partita
- std::future_status::ready se il risultato è pronto
- std::future_status::timeout se il tempo è scaduto ma il risultato non è tornato
se si chiama wait su un thread creato con modalità deferred il thread che ha chiamato wait esegue le istruzioni messe nel oggetto deferred
wait_for e wait_until non lanciano nulla se chiamati su un deferred

se il thread è in esecuzione e si cerca di distruggere future il distruttore chiama la wait e attende che questi torni il future
aspetta sempre il ritorno quindi NON é POSSIBILE STOPPARE UN ESECUZIONE FATTA IN UN OGGETTO FUTURE.
reg 11 1:24:00

è possibile che il risultato di un thread riportato nel metodo future debba esser consultato piu di una volta a tal scopo è
possibile farsi restituire un oggetto shared_future lo shared future è piu oneroso ma puo essere usato e copiato nvolte e
tutte mantengono il riferimento all oggetto originale. quando su un oggetto future si chiama il metodo share()
questo restituisce uno shared future e l oggetto stesso diventa invalido da questo momento sara usato solo lo shared future

shared future è copiare e movibile e offre gli stessi metodi di future
uno shared_future puo servire per creare catene di esecuzioni:

->> si esegue un thread e si ritorna lo shared_future che si passa ad altri due che quando avranno bisogno del valore preso
dall oggetto future chiameranno la get() su di esso.
reg12 08:57 schemino

Quando si definisce async si lascia al compilatore la decisione del lancio del thread a menoche non si dichiari esplicitamnte
nel primo argomento la politica di esecuzione:
std::async(std::launch::async,funzioneLunga, 47); // lancia il thread subito
std::async(std::launch::deferred,funzioneLunga, 47); // lancia il thread quando viene chiamata get o wait ma l esecuzione
non avviene su un nuovo thread ma sul thread corrente che chiama la get o la wait
*/

unsigned long long funzioneLunga(int n) {
    if (n <= 1) {
        return n;
    } else {
        return funzioneLunga(n - 1) + funzioneLunga(n - 2);
    }
}

int main() {
    // Definizione
    std::future<unsigned long long> fut_obj0 = std::async(std::launch::async,funzioneLunga, 47);
    std::future<unsigned long long> fut_obj1 = std::async(std::launch::async,funzioneLunga, 46);
    std::future<unsigned long long> fut_obj2 = std::async(std::launch::deferred,funzioneLunga, 46);

    cout << "Procedo con il calcolo 0."<< endl;
    long long risultato0 = fut_obj0.get();
    cout << "Procedo con il calcolo 1."<< endl;
    long long risultato1 = fut_obj1.get();
    // il risultato è simultaneo perche la computazione 0 è piu lunga della 1 e quindi la 1 avrà già finito quando la 0 finisce

    std::cout << "Risultato: " << risultato0 << "-" << risultato1 << std::endl;
    long long risultato2 = fut_obj2.get();
    std::cout << "Risultato: " << risultato2 << std::endl;

    return 0;
}


