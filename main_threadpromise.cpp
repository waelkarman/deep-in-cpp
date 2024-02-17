#include <future>
#include <iostream>
#include <thread>

using namespace std;

/*
se il programma fa computazione pesante inutile fare tanti thread perche quelli in esecuzione sono nel numero dei processori fisici.
se invece si fa tanto i/o puoavere unsenso avere molti thread per passimizzare la computazione e quelliche sono inattesa attendono l i/o

per creare un thread con la classe thread, si passa al construttore di thread un oggetto callable come un puntatore a funzione ecc
-> std::thred t(<funzionale>);
e il thread parte subito oltre all oggetto callable se aggiungo altri parametri per VALORE questi vengono passati all oggetto callable.
anche l oggetto callable è passato per VALORE ad una certa bisogna per forza chiamare join sul thread creato per aspettare in modo
bloccante la sua terminazione. chiamare join inoltre libera le risorse del thread
 si può forzare il passaggio per reference con std::ref(<oggetto>) che in realtà è un passagio per valore ma questo valore è un
reference e quindi è come passare per reference in realtà si puo passare un puntatore e bisogna però gestirne il ciclo vita
perche in questo caso l uscita dallo scope non cancellerà l oggetto. (NON APPLICANDO IL PARADIGMA RAII)

delle volte come in un webserver forse è meglio creare subito 100 thead e usarli a rotazione invece di crearne uno per richiesta.
questa tecnica prende il nome di thread pooling. si prende un thread che non sta facendo niente e gli si assegna un compito. questo non
termina a fine compito ma resta attivo notificando la fine delle operazioni egli assegnate. Questo approccio evita l onere di creare
ogni volta un thread.

Ad un thread è possibile passare una lambda. La labda ha la possibilità di catturare il contesto di esecuzione questo è un problema
nel caso un thread è chiamato dentro una funzione che però termina cancellando le variabili catturate dal thread che farebbe accesso
tramite il sudetto reference a qualcsoa di indefinito. ma anche se il contesto fosse ancora valido ciò comporterebbe comunque i classici
problemi di sincronizzazione fra lettue e scritture dentro e fuori il thread

usare thread invece di async non permette di selezionare politica la chiamat a acostruttore di thread fa partire un thread se ci sono risorse
se non ci sono lancia un eccezione
thread non torna un valore ma torna solo void.
L unica cosa che so di un thread è che ha un nome univoco che si ottiene chiamndo get_id()
se un eccezione si verifica nel thread e nessuno fa il catch muore tutto il processo

se non invochiamo join possiamo invocare detach() sul thread e questo andrà per i fatti suoi e noi perderemo ogni contatto ma comunque
se il thread principale termina fa terminare pure questi thread detached

è possibile muoreve un thread dentro un altro per movimento scaricando la responsabilità dello stesso su un altro thread
se per caso il distruttore di thread viene invocato esso fa terminare tutta l' esecuzione quindi è da evitare
se il thread principale termina gli altri terminano forzatamente anche se sono detached

se ho bisogno del risultato finale di un thread usare async e future va bene se ho bisogno di risultati intermedi invece ho bisogno di
una variabile condivisa ma come la gestisco ?

il modo migliore di gestire un valore restituito da un thread è usare un oggeto di tipo std::promise esso si puo riempire con un
informazione con set_value e ritorna un oggetto future con il metodo get_future()
sul quale è possibile interrogare se il valore è pronto o non ancora
reg 12 40:18 restituzione di valori parziali

se un thread termina per cause non naturali si invoca exit
std::exit fa terminare il thread principale e uscire dal processo quindi esce dal main e distrugge le variabili globali
std::quick_exit che non chiama il distruttore delle variabili globali

l uso di promise permette di sincronizzare e quindi migiora la situazioen dei thread detached.
è possibile per un promise associare il valore alla fine di un thread in modo da aspettare comunque la terminazione del thread detached
cio si fa con la funzionce set_value_at_thread_exit(T val) set_exception_at_thread_exit(T val) ma di nuovo questo maschera i risultati intermedi

è possibile ottenenre l identificativo del thread corrente usando std::this_thread::get_id()
std::this_thread::sleep_for(<duration>) viene messo in stato wait e poi in ready in attesa di essere schedulato ed eseguito
std::this_thread::sleep_until(<duration>) fino a momemto preciso
yield() mi rimento in wait e faccio passare avanti gli altri
con thread e promise è possibile gestire un po le sincronizzazioni come con async in realtà è esattametne quello che async fa
*/
unsigned long long funzioneLunga(int n) {
    if (n <= 1) {
        return n;
    } else {
        return funzioneLunga(n - 1) + funzioneLunga(n - 2);
    }
}

void funzioneConPromise(std::promise<unsigned long long> prom0, std::promise<unsigned long long> prom1) {

    unsigned long long risultato0 = funzioneLunga(47);
    prom0.set_value(risultato0);

    cout << "Computazione parziale 0 ." << endl;

    unsigned long long risultato1 = funzioneLunga(47);
    prom1.set_value(risultato1);

    cout << "Computazione parziale 1 ." << endl;
}

int main() {
    // Crea un promise
    std::promise<unsigned long long> prom0;
    std::promise<unsigned long long> prom1;
    std::promise<int> prom2;
    std::promise<unsigned long long> prom3;
    std::promise<unsigned long long> prom4;
    std::promise<int> prom5;
    // Ottieni un future da questo promise
    std::future<unsigned long long> fut0 = prom0.get_future();
    std::future<unsigned long long> fut1 = prom1.get_future();
    std::future<int> fut2 = prom2.get_future();
    std::future<unsigned long long> fut3 = prom3.get_future();
    std::future<unsigned long long> fut4 = prom4.get_future();
    std::future<int> fut5 = prom5.get_future();
    // Avvia un thread passando il promise (è necessario usare std::move)
    std::thread t0(funzioneConPromise, std::move(prom0), std::move(prom1));

    // Fai qualcosa nel thread principale...
    cout << "svolgo operazioni" << endl;
    std::thread t1([](std::promise<int> prom2){
        cout << "Corpo lambda" << endl;
        prom2.set_value(20);
    }, std::move(prom2));

    int risultato2 = fut2.get();
    std::cout << "Risultato2: " << risultato2 << std::endl;

    unsigned long long risultato0 = fut0.get();
    std::cout << "Risultato0: " << risultato0 << std::endl;
    unsigned long long risultato1 = fut1.get();
    std::cout << "Risultato1: " << risultato1 << std::endl;


    std::thread t2(funzioneConPromise, std::move(prom3), std::move(prom4)); // questo thread essendo detached viene terminato prima del tempo

    // Non dimenticare di unire il thread
    t0.join();
    t1.join();
    t2.detach();


    //-----------------------------------ERRORS

    int* i = (int*)malloc(sizeof(int));
    *i=1000;
    unsigned long long (*func_ptr)(int) = funzioneLunga;
    cout << "Lancio il thread incriminato" << endl;

    std::thread t3([&](){
        unsigned long long risultato3 = func_ptr(50);
        cout << "Risultato3: " << risultato3 << endl;
        cout << "Stampo I che però non dovrebbe esistere:" << *i << endl;
    });

    cout << "Continuo a fare le mie operazioni chiamo la free prima che il thread abbia fatto accesso su i" << endl;
    free(i); //LA RIGA SEGUENTE STAMPA IL VALORE DI i GIA CANCELLATO E QUINDI NULL =0

    t3.join();

    return 0;
}



