#include <iostream>

using namespace std;

// la copia è in cotrasto con l idea di prestazioni elevate se un oggetto non mi serve piu e lo voglio copiare a qualcuno posso
// passarne la proprietà invece di copiare e poi cancellarlo
// se io ho una lista che popolo in una funzione e poi la voglio ritornare perche copiarla? meglio spostarla
// espressioni temporanee come f(3+i) f(string("ciao")) il parametro passato non ha senso copiarlo (oggetti anonimi in generale)

// il movimento è utile anche perche alcuni oggetti sono effettivamente non copiabili come uno unique_ptr che non è copiabile ma è
// muovibile e quindi puo ritornare da una funzione per fare il movimento è necessario un costruttore di movimento.
// Base(Base && sorgente){}
// il c++ non genenra un costruttore di movimento di default perche non sa come è fatta la nostra classe
// se il dato è un Rvalue o un Lvalue expired detto Xvalue allora il compilatore muove invece di copiare
// string&& è un Rvalue reference che NON è un riferimento ad un riferimento

// quando viene chiamata un afunzione il compilatore alloca spazio per il return prima dell invocazione quando si ritorna copia e
// distrugge le variabili locali questa operazione puo essere semplificata chiamnado il costruttore di movimento che invece di
// distruggere l oggetto copiato lo smonta e quanto al suo interno viene passato

// esempio costruttore di movimento prendo dall oggetto passato e lo setto a null
// simple_string(simplestring&& that){
// data = that.data
// that.data= NULL;
// }
// evita la copia in profondità
// quando questo succede:

// b(a+x)
// b(funcCheRitorna())

// alcuni oggetti non sono copiabili ma movibili
// copiare un intero o muoverlo è piu o meno la stessa cosa quindi non ha senso muoverlo forse dannoso

// tabellina Rvalue Lvalue 24:41 lezione 9
// Lvalue è riferito a un qualcosa che ha un indirizzo fisico di memoria
// Rvalue è il risultato temporaneo di un espressione che sta per essere cancellato

// la tabella mostra in funzione del tipo di parametro passato alla funzione quale argomenti la funzione può ricevere intermini di Rv o
// Lv ecc

// una funzione che prende in inglesso un Const Type Reference può potenzialmente prendere in ingresso qualsiasi cosa sia Rvalue che
// Lvalue cost o non invece una funzione Type Rvalue Reference solo oggetti di tipo Rvalue quindi se l' oggetto a destra dell uguale
// è un Rvalue teoricamente è possibile chiamare sia il costruttore di copia che di movimento
// lo standard prevede che in tal caso si chiami il costruttore di movimento se disponibile altrimenti quello di copia


// Si parla quindi di costruzione per movimento ma lo stesso problema esiste anche nel caso
// dell assegnazione tuttavia questo provoca un comportamento simile a quello del distruttore piu altre operazioni per il movimento
// con duplicazione di codice o comunque problemi di manutenzione

// Per risolvere questo problema nasce un paradigma denominato Copy&Swap
// se si fa una funzione extra che chiamiamo swap fuori dalla classe da copiare ma sua friend in modo che possa accedere ad ogni suo campo
// è possibile rendere il costruttore di copia l' unico responsabile della copia anche quando si fa l'assegnazione e trasformare l'
// assegnazione in movimento a seconda dei casi in cui è possibile fare lo spostamento o no.
// ovviamente bisognerà definire pure il costruttore di movimento.

// dunque fatta la funzione swap si scrive l'operatore di assegnazione che prende un parametro passato epr valore
// all interno si esegue lo swap.
// il parametro passato verrà copiato dall costruttore di copia e passato come copia all oggetto che dopo aver scambiato i riferimenti
// propri con quelli dell oggetto in questione ritornerà distruggendo l' oggetto copiato.
// se l'oggetto originale passato alla funzione è un Rvalue Reference e queindi sta per morire anche il passaggio dell' argomento
// all operatore di assegnazione
// avverrà per movimento e non per copia garantendo un duplice comportamento nel caso dell uso dell operatore di assegnazione
// il costruttore di movimento invece viene invece normalmente definito.
//
//
// funzione esterna da dichiarare friend della classe che si intende supportare
// void swap(intArray& a,intArray& b) {
//    std::swap(a.mSize, b.mSize);
//    std::swap(a.mArray, b.mArray);
// }
//
// intArray& operator=(intArray that){
//    //that è passato per valore,
//    //copiato o mosso a seconda del
//    //contesto in cui è usato
//
//    swap(*this, that);
//    return *this;
// }
//
// costruttore di movimento
// intArray(intArray&& that): // notare che il parametro non è const perche il costruttore di movimento deve poter motificare l oggetto passato
//    mSize(0), mArray(NULL)  // azzero le mie risorse e poi faccio swap
// {
//    swap(*this, that);
// }
// swap corrisponde alla funzione assembler exchange che è molto veloce
// se lo volessimo fare manualmente occorre allocare sullo stack che non costa molto ma va fatto

// esiste la funzione move che promuove l oggetto ad Rvalue e quindi alla possibilità di essere svuotato e lo restituisce

// v.push_back(str) in questo caso str viene copiato nel vettore e continua ad esserci copia in str
// v.push_back(std::move(str)) in questo caso str si svuota e non avviene la copia


int main(){
    cout<<"HELLO";
};

