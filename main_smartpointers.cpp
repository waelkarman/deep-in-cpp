#include <iostream>
#include <memory>

using namespace std;
/*
RAII (Resource Acquisition Is Initialization): È una tecnica che incapsula le risorse (come la memoria dinamica, file handles, mutex, etc.)
all'interno di oggetti che vivono sullo stack, in modo che la loro durata sia gestita automaticamente seguendo le regole di costruzione e
distruzione degli oggetti.
e quindi in caso di problemi (eccezzioni etc) è possibile ancora fare operazioni ovvero i distruttori stando attenti a non peggiorare la
situzione. Oltretutto acquisendo le risorse all' inizializzazione le si libera alla distruzione.
Usare smart pointers (std::unique_ptr, std::shared_ptr) è un esempio di applicazione del principio RAII per la gestione della memoria.

Un puntatore nativo supporta come minimo 3 operazioni:
- copia puntatore (operator=)
- asterisco (accedi al blocco di memoria) (operator*)
- operatore freccia accedi al blocco memoria + offset (operator->)
- (aritmetica dei puntatori) -- incremento, somma, confronto ecc

quando si crea uno smart_pointer si suppone che la memoria puntata viva sullo HEAP in quanto se poi si vuole cancellare l' oggetto
se questi punta nello stack (ad una variabile locale int a per esempio) si chiama una delete su un area che sta sullo stack con
conseguente errore.

quando si ridefinisce l' operatore freccia questo non può essere riassegnato perchè non si puo assegnare una variabile a-> = 5
ma si puo fare *a=5

36:20 in caso di eccezioni (smart-pointer)
usando puntatori classici a oggetti un eccezione non gestita bene provocava l interruzione del progamma senza liberazione della memoria
e se il programma termina viene dallocato solo lo stack invece con RAII (smartpointer quindi) viene chiamato il distruttore degli oggetti a
fine scope che se scritto bene dealloca tutte le risorse che un errata gestione delle interruzioni non liberava.
alternativa è ogni volta che si usa un puntatore lo si sinclude sempre in un blocco try ma sistatticamente è impensabile

nel c++11 nella libreria <memory> sono state definite 3 classi di smartpointer

- std::shared_ptr<type>
manintiene un contatore all oggetto incrementato per copia e se si distrugge uno smart pointer il contatore si decrementa se tocca 0 si dealloca la memoria ma è
possibile specificare cosa fare invece di rilasciare la memoria
get(), operator*, operator-> restituiscono il puntatore nativo
delete, decrementa il contatore (DA NON CHIAMARE MAI)
operator=, aumenta il contatore
reset() resetta lo shared pointer con un altro oggetto

make_shared<>() lo si puo usare anche con tipi primitivi locali tipo int. il metodo garantisce una allocazione sullo heap
come argomenti prende direttamente i valori da passare al costruttore del tipo passato fra parentesi angolari
 51:03

- std::weak_ptr<type> permette di osservare il contenuto di uno shared_ptr
- std::unique_ptr<type> esiste un solo puntatore se lo passo ad un altro io mi distruggo
- std::make_shared<base>(params...) prende dei parametri del costruttore e istanzia un oggetto base e lo restituisce
- std::auto_ptr<base> vecchio prima del 2011 trasferisce la proprietà ad un altro puntatore e mette a null il puntatore corrente ma questo cambi ail puntatore di partenza e questo non va bene

PROBLEMA: su uno shared pointer non bisogna mai chiamre esplicitamente delete ma aspettare che il contatore tocchi lo zero.
in un caso del tipo:

class A {
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "Distruttore di A chiamato\n"; }
};
class B {
public:
    std::shared_ptr<A> a_ptr;
    ~B() { std::cout << "Distruttore di B chiamato\n"; }
};

int main() {
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a;
}

il contatore non tocca mai lo zero. a causa del fatto che la classe non elimina il suo shared pointer ma l unico motivo di rilascio risorse è legato al contatore.
per questo si utilizzano i weak_ptr che è gestito da shared ptr ma non viene contato. Un std::weak_ptr può essere "promosso" (con il metodo lock()) a uno std::shared_ptr temporaneo
(aumentando temporaneamente il conteggio dei riferimenti) per accedere in modo sicuro all'oggetto, se questo esiste ancora (si controlla con il metodo expired()).
cosi si risolve il problema del ciclo usando in uno dei due riferimenti uno weak_ptr

unique_ptr non puo essere ne copiato ne assegnato non si da a nessuno. puo essere esplicitamente trasferito usando il metodo move()(da approfondire per capire come possa essere ritornato da una funzione).
supponendo di essere unico possessore della memoria se viene eliminato rilascia la memoria.

make_unique similmente a quanto avviene per shared crea nello heap un oggetto e restituisce il puntatore unique.
*/
class Base1;

class Base0{
public:
    int a=7;
    shared_ptr<Base1> p1;
    weak_ptr<Base1> w1;
    Base0(){}
};

class Base1{
public:
    int b=8;
    shared_ptr<Base0> p0;
    Base1(){}
};


int main(){

    //  ------------ SHARED AND WEAK

    //Osservo come il contatore dello smart_ptr sale e scende
    shared_ptr<Base0> p0;
    {
        p0 = shared_ptr<Base0>(new Base0());

        cout << "Il puntatore è l' unico proprietario? " << p0.unique() << endl;

        shared_ptr<Base0> p2=p0;

        {
            shared_ptr<Base0> p3;
            p3=p0;
            cout << "Il puntatore ha " << p0.use_count() << " riferimento" <<endl;
        }

        cout << "Il puntatore ha " << p0.use_count() << " riferimento" <<endl;
        cout << "Il puntatore è l' unico proprietario? " << p0.unique() << endl;

        cout << "Accedo all oggetto: " << p0->a << endl;
        cout << "Accedo all oggetto: " << (*p0).a << endl;
    }

    cout << "Il puntatore ha " << p0.use_count() << " riferimento che sarà cancellato all uscita dallo scope." <<endl;


    //Alloco sullo heap un intero passando al metodo make_shared gli argomenti per costruire il tipo in parentesi angolari.
    {
        int c;
        shared_ptr<int> p5 = make_shared<int>(c);
        shared_ptr<int> p6 = make_shared<int>(10);
        cout << "Modo errato di usare un sh_ptr: " << *p5 << endl;
        *p6 = 9;
        *p5 = 8;
        cout << "Ptr: " << *p5 << endl;
        cout << "Ptr: " << *p6 << endl;
    }


    //Alloco apposta una quantità presente sullo stack cosa non valida.
    //{
    //    int c=5;
    //    int* pc=&c;
    //    shared_ptr<int> p5 = shared_ptr<int>(pc);
    //}//ERRORE


    //Problema di circolarità dello shared_ptr il contatore non raggiungerà mai lo zero
    {
        std::shared_ptr<Base0> pb0 = std::make_shared<Base0>();
        std::shared_ptr<Base1> pb1 = std::make_shared<Base1>();
        pb0->p1=pb1;
        pb1->p0=pb0;
        cout << "pb0_count: " <<pb0.use_count() << " pb1_count: " <<pb1.use_count()<<endl;
    }

    {//SOLUTION
        std::shared_ptr<Base0> pb0 = std::make_shared<Base0>();
        std::shared_ptr<Base1> pb1 = std::make_shared<Base1>();
        pb0->w1=pb1;
        pb1->p0=pb0;
        cout << "pb0_count: " <<pb0.use_count() << " pb1_count: " <<pb1.use_count()<<endl;
    }

    //  ------------ UNIQUE
    std::unique_ptr<Base0> u0 = std::make_unique<Base0>();
    cout << "Accesso all unique_ptr 0 - : " << u0->a << endl;
    std::unique_ptr<Base0> u1 = std::move(u0);
    cout << "Accesso all unique_ptr 1 - : " << u1->a << endl;

    {
        // INTERROMPE L' ESECUZIONE SENZA DARE ALCUN SEGNALE
        //try{
        //    cout << "Accesso all unique_ptr 0 - : " << u0->a << endl;
        //}catch(...){
        //    cout << "ERRORE" << endl;
        //}//ERRORE
    }

    cout << "termine esecuzione" << endl;

};

