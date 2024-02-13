#include <iostream>
#include <exception>

using namespace std;

class Base0{

public:
    string a="999";

    Base0(string x) : a(x) { // Costruttore della classe Base che richiede un parametro
        cout << "Costruttore della classe Base con x = " << x << endl;
    }

    //quando si ridefinisce un operatore il parametro in inglesso è sempre const type reference
    //----------------------il costruttore di copia deve essere const type reference perche la copia non deve cambiare l oggetto quindi Base0(const Base& b ){}
     Base0(const Base0& b ){
        //campo=b->campo prendo dall esterno e popolo me stesso
        //ecc
     }
     //se non si vuole permettere la duplicazione basta dichiarare privato il costruttore di copia
     //quando si assegna un oggetto si suppone l esistenza del ogetto da assegnare e quindi bisogna anche cancellare quello che c'è dentro prima di procedere assegnando
     // se viene definito anche solo uno della terna: costruttore di copia, operatore di assegnazione e distruttore OCCORRE definire gli altri 2


    virtual void stampa0(){
        //virtual si propaga a tutta la gerarchia quando una classe eredita da due classi base con metodo stampa0 virtuale
        //come nel caso Base, Base0 quando il metodo viene invocato dal main sara selezionato il metodo corretto in funzione
        //del tipo di puntatore che effettua la richiesta e l' informazione su quale sia il metodo giusto da chiamare
        //sarà recuperato dalla vtable dell oggetto

        cout<< a << endl;
    }

    void stampa2(){
        cout<< a << endl;
    }
};

class Base{
//in una classe se non esplicitato public è sempre private
public:
    string a="123";

    //Base(Base && sorgente){} //costruttore di movimento


    virtual void stampa0(){//virtual si propaga a tutta la gerarchia quidni il metodo sarà sempre polimorfico
        cout<< a << endl;
    }
    void stampa1(){
        cout<< a << endl;
    }
    virtual void stampa2(){
        cout<< a << endl;
    }
};

class Derived1: public Base, public Base0{

public:
    string a="789";

    Derived1(string k, string j) : Base0(j), a(k) { // Chiamata esplicita al costruttore della classe Base
        cout << "Costruttore della classe Derivata con k = " << k << endl;
        cout << "Mentre quello della classe Base ereditata con j = " << j << endl;
    }

    void stampa0() override {
        cout<< a << endl;
        //se qui apro un file e lo chiudo nel distruttore della classe derivata
        //essendo nella classe base definito come virtual solo il metodo e non
        //anche il distruttore per deallocare l' oggetto è il distruttore della
        //classe base che sarà chiamato lasciando il file aperto
    }
    void stampa1(){
        cout<< a << endl;
    }

    void stampa2() override {//la keyword è opzionale
        //essendo questo un override dal main non si potrà più chiamare il metodo stampa2
        //del padre a menochè non si faccia uno static cast alla classe base tuttavia il
        //metodo definito nella classe base puo ancora essere chiamato espicitamente all
        //interno della classe specificando la classe base di cui si vuole invocare il
        //metodo
        cout<< a << endl;
        Base::stampa2();
        Base0::stampa2();
    }

};

class Derived2: public Base{

public:
    string a="456";

    void stampa0() {
        cout<< a << endl;
    }
    void stampa1(){
        cout<< a << endl;
    }
    void stampa2() {
        cout<< a <<endl;
    }
};




int main()
{
    cout << "Erediterietà!" << endl;
    cout << "Polimorfismo!" << endl;

    //quando un oggetto viene istanziato se questi ha un metodo virtual avrà una v teble al suo interno
    //ricordare di definire sempre il distruttore anche virtual in tal caso.

    //quando un oggetto di una classe derivata viene istanziato questi si porta anche spazio per la
    //classe base.

    //quando istanzio una classe derivata sto sempre istanziando anche la classe base
    //il costruttore della classe base chiamerà sempre prima quello della classe base
    //se non definito il costruttore di default sarà chiamato.

    Base *b1 = new Derived1("777","888");
    Base *b2 = new Derived2();
    //mai assegnare un oggetto (quindi definito come Derived d(); NON puntatore a oggetto) definito come
    //figlio ad un padre perche sarà copiato solo un pezzo usare sempre l' operatore di static_cast

    b1->stampa0();
    b2->stampa0();

    b1->stampa1();
    b2->stampa1();

    b1->stampa2();
    b2->stampa2();

    cout << "VTABLE:" << endl;
    //Ogni classe che ha almeno un metodo virtual (ma è bene definire anche il distruttore come
    //virtual 1.) ha un v reference all inizio del blocco memoria che punta alla corretta implentazione
    //da selezionare per il metodo virtual

    // 1. se scrivo una classe e in un metodo apro in file e lo chiudo nel distruttore. Quando questo
    //metodo viene chiamato da chiamate polimorfiche il distruttore chiamato sarà diverso il file
    //resterà aperto.

    //Una classe che eredita da due classi base avrà due vtable più la propria

    //classe che eredita da una sola classe base avrà una sola vtable

    cout << "SMART POINTER:" << endl;

    //RAII (Resource Acquisition Is Initialization): È una tecnica che incapsula le risorse (come la memoria dinamica, file handles, mutex, etc.)
    //all'interno di oggetti stack, in modo che la loro durata sia gestita automaticamente seguendo le regole di costruzione e distruzione degli oggetti.
    // e quindi in caso di problemi è possibile ancora fare operazioni ovvero i distruttori stando attenti a non peggiorare la situzione.
    // oltretutto acquisendo le risorse all inizializzazione le si libera alla distruzione.
    //Usare smart pointers (std::unique_ptr, std::shared_ptr) è un esempio di applicazione del principio RAII per la gestione della memoria.

    //un puntatore nativo supporta come minimo 3 operazioni:
    //- copia puntatore (operator=)
    //- asterisco (accedi al blocco di memoria) (operator*)
    //- operatore freccia accedi al blocco memoria + offset (operator->)
    //  -- (aritmetica dei puntatori) -- incremento, somma, confronto ecc

    //quando si crea uno smart_pointer si suppone che la memoria puntata viva sullo HEAP in quanto se poi si vuole cancellare l' oggetto
    //se questi punta nello stack (ad una variabile locale int a per esempio) si chiama una delete su un area che sta sullo stack con
    //conseguente errore

    //quando si ridefinisce l' operatore freccia questo non può essere riassegnato perchè non si puo assegnare una variabile a-> = 5 ma si puo fare *a=5

    //36:20 in caso di eccezioni (smart-pointer)
    //usando puntatori classici a oggetti un eccezione non gestita bene provocava l interruzione del progamma senza liberazione della memoria
    //e se il programma termina viene dallocato solo lo stack invece con RAII (smartpointer quindi) viene chiamato il distruttore degli oggetti a fine scope
    //che se scritto bene dealloca tutte le risorse che un errata gestione delle interruzioni non liberava.
    //alternativa è ogni volta che si usa un puntatore lo si sinclude sempre in un blocco try ma sistatticamente è impensabile

    //nel c++11 nella libreria <memory> sono state definite 3 classi di smartpointer

    //- std::shared_ptr<type>
    // manintiene un contatore all oggetto incrementato per copia e se si distrugge uno smart pointer il contatore si decrementa se tocca 0 si dealloca la memoria ma è
    //possibile specificare cosa fare invece di rilasciare la memoria
    //get(), operator*, operator-> restituiscono il puntatore nativo
    //delete, decrementa il contatore
    //operator=, aumenta il contatore
    //reset() ??

    //make_shared<>() lo si puo usare anche con tipi primitivi locali tipo int. il metodo garantisce una allocazione sullo heap
    // 51:03

    //- std::weak_ptr<type> permette di osservare il contenuto di uno shared_ptr

    //- std::unique_ptr<type> esiste un solo puntatore se lo passo ad un altro io mi distruggo

    // std::make_shared<base>(params...) prende dei parametri del costruttore e istanzia un oggetto base e lo restituisce

    // std::auto_ptr<base> vecchio prima del 2011 trasferisce la proprietà ad un altro puntatore e mette a null il puntatore corrente ma questo cambi ail puntatore di partenza e questo non va bene

    // PROBLEMA: su uno shared pointer non bisogna mai chiamre esplicitamente delete ma aspettare che il contatore tocchi lo zero.
    //in un caso del tipo:

    // class A {
    // public:
    //     std::shared_ptr<B> b_ptr;
    //     ~A() { std::cout << "Distruttore di A chiamato\n"; }
    // };
    // class B {
    // public:
    //     std::shared_ptr<A> a_ptr;
    //     ~B() { std::cout << "Distruttore di B chiamato\n"; }
    // };
    //
    // int main() {
    //     std::shared_ptr<A> a = std::make_shared<A>();
    //     std::shared_ptr<B> b = std::make_shared<B>();
    //     a->b_ptr = b;
    //     b->a_ptr = a;
    // }

    //il contatore non tocca mai lo zero. a causa del fatto che la classe non elimina il suo shared pointer ma l unico motivo di rilascio risorse è legato al contatore.
    //per questo si utilizzano i weak_ptr che è gestito da shared ptr ma non viene contato. Un std::weak_ptr può essere "promosso" (con il metodo lock()) a uno std::shared_ptr temporaneo
    //(aumentando temporaneamente il conteggio dei riferimenti) per accedere in modo sicuro all'oggetto, se questo esiste ancora (si controlla con il metodo expired()).
    //cosi si risolve il problema del ciclo usando in uno dei due riferimenti uno weak_ptr


    // unique_ptr non puo essere ne copiato ne assegnato non si da a nessuno. puo essere esplicitamente trasferito usando il metodo move()(da approfondire per capire come possa essere ritornato da una funzione).
    //supponendo di essere unico possessore della memoria se viene eliminato rilascia la memoria.
    //
    // make_unique similmente a quanto avviene per shared crea nello heap un oggetto e restituisce il puntatore unique.

    cout << "REFERENCE-POINTER differenze"<<endl;
    //Puntatori
    //Sintassi: Un puntatore è dichiarato usando un asterisco (*) nella sua dichiarazione. Ad esempio: int* ptr;
    //Indirizzamento: Un puntatore contiene l'indirizzo di memoria di un'altra variabile. Può essere modificato per puntare a un'altra variabile in qualsiasi momento.
    //Indirezione: L'operatore di indirezione (*) è usato per accedere al valore dell'oggetto a cui il puntatore punta. Ad esempio: *ptr = 10;
    //Valori Nulli: Un puntatore può essere impostato su nullptr (o, in C++ più vecchi, NULL), indicando che non punta a nulla.
    //Aritmetica dei Puntatori: È possibile eseguire aritmetica sui puntatori (ad es., ptr++ per spostarsi all'indirizzo della prossima variabile di un tipo specifico), il che è utile in contesti come gli array.
    //Riferimenti
    //Sintassi: Un riferimento è dichiarato usando l'operatore & nella sua dichiarazione. Ad esempio: int& ref = var;
    //Alias: Un riferimento funge da alias per un'altra variabile. Una volta inizializzato con una variabile, non può essere cambiato per riferirsi a un'altra variabile. In altre parole, un riferimento è sempre collegato alla variabile con cui è stato inizializzato.
    //Indirezione Nascosta: Non è necessario usare un operatore per accedere al valore a cui il riferimento si riferisce; si usa il nome del riferimento direttamente. Ad esempio: ref = 10; cambierà il valore della variabile a cui ref si riferisce.
    //Nessun Valore Nullo: Un riferimento deve essere inizializzato al momento della dichiarazione e non può essere nullo. Non esiste un "riferimento nullo" in C++ standard.
    //Nessuna Aritmetica: Non si può fare aritmetica con i riferimenti.



    cout << "FRIEND:"<<endl;
    //le funzioni friend devono esistere nel codice prima di essere definite friend
    //i campi privati on possono essere visti all esterno della classe stessa tuttavia è possibile dichiarare friend altre classi o funzioni per permettergli
    //di accedere ai campi private.

    //void func(A &a){a.datoprivato = 1;}
    //class ClasseA {
    //    friend class ClasseB; // Dichiarazione di amicizia
    //    friend void func(A&);
    //private:
    //    int datoPrivato;
    //public:
    //    ClasseA() : datoPrivato(42) {} // Costruttore che inizializza datoPrivato
    //};
    //class ClasseB {
    //public:
    //    void mostraDatoPrivatoDaA(const ClasseA& a) {
    //        // Accesso diretto al membro privato di ClasseA grazie alla friendship
    //        std::cout << "Dato privato di ClasseA: " << a.datoPrivato << std::endl;
    //    }
    //};

    //int main() {
    //    ClasseA a;
    //    ClasseB b;
    //    b.mostraDatoPrivatoDaA(a); // Mostra: Dato privato di ClasseA: 42
    //    return 0;
    //}



    // un metodo definito const non modifica lo stato dell oggetto se const è abbinato ad un reference permette di evitare la copia tenendo immutato l oggetto passato
    // override serve a specificare che si fa un override e quindi il compilatore eseguirà un marching dei tipi
    // noexcept dice al compilatore che una funzione non lancerà eccezioni questo permette al compilatore di ottimizzare meglio il codice perche sa di non dover gestire eccezioni
    //slicing per slicing si intende la copia di qualcosa in uno spazio piu piccolo che è consentita senza problemi ma non viene tutto effettivamente copiato ma solo la parte che ci entra con la conseguente perdita di informazione


    // explicit, inline, volatile,


    // iteratori
    //1:02:13

    //ce una classe operator per ogni tipo come  std::vector<int>::iterator ,  supporta ++ e -- punta sempre ad un elemento della collezione su puo vedere anche se punta allo stesso elemento o no con ==,  !=, begin() gli iteratori possono essere validi o non end()primo elemento fuori lista, iteratore non valido
    //si puo cancellare un elemento iterando ma bisogna farlo dall iteratore non dalla lista . tipo il metodo erase accetta un iteratore come parametro.

    // std::vector<int> myVector = {1, 2, 3, 4, 5};
    // for (auto it = myVector.begin(); it != myVector.end(); /* not incrementing here */) {
    //     if (*it == 3) {
    //         it = myVector.erase(it); // Cancella l'elemento e sposta l'iteratore all'elemento successivo
    //     } else {
    //         ++it; // Incrementa solo se non cancelli
    //     }
    // }

    //esisite il metodo remove_if che prende una funzione che se ritorna true cancella l elemento se ritorna false invece no. questi si chiamano funzionali e non funzioni.
    // anche il metodo sort ordina ascendente per default o prende in ingresso un funzionale che definisce il criterio di ordinamento
    // il metodi splice toglie elementi dal primo contenitore e li mette nel scondo passato come argomento
    // unique toglie i duplicati adiacenti quindi se si fa prima sort e poi unique si tolgono tutti.
    //essendo i contenitori come le mappe ordinati non è possibili costruirne una di un tipo custom senza ridefinire l' operatore minore. bisogna inoltre garantire la copia e l' assegnazione


    cout << "PUNTATORI A FUNZIONE: "<<endl;

    // sintassi <tipo_ritornato>(*var )(<argomenti>)
    // assegnamento int f(int i, double d){ .. .. }
    // int (*var)(int,double);
    // var = f;
    // var = &f; identico al precedente
    // var(10,3.48);
    // (*var)(10,3.48); identico al precedente

    // il match dei tipi deve essere perfetto anche se ci sono parametri di default va specificato il tipo perche i parametri di default sono sempre parametri passati alla funzione.

    cout << "FUNCTIONAL OBJECT" << endl;

    //è un oggetto con ridefinito l' operatore operator()
    // class FC{
    // public:
    //     int operator() (int v){
    //         return v*2;
    //     }
    // };

    //posso usare FC come una funzione :

    // FC fc; costruttore a cui potrei passare cose
    // int i = fc(5); fc gia costruito cosi chiamato chiamo la funzione definita nell operatore
    // // vale 10

    //anche operator() puo essere overloaded
    //se all oggetto metto dei campi privati posso definire un funzione risponda in funzione di uno stato interno nascosto
    // è possibile contare quante volte viene invocata una funzione!

    // usando i template
    //  è possibile scrivere
    //  template <typename F>
    //  void some_function(F& f){
    //      f(); // f puo essere sia un funzionale che un puntatore a funzione
    //  }
    // in entrambi i casi la riga f(); sarà risolta nel casi puntatore a funzione come invocazione della funzione puntata
    // in caso di oggetto funzionale come chiamata all operator() ridefinito aumentando la generalità dell espressione
    // il remove if quindi può prendere un oggetto funzionale o una funzione oppure si po fare l overload e dire remove if e si da un valore intero da rimuovere

    cout << "ESPRESSIONI LAMBDA" << endl;

    // la labda è un espressione sintattica che semplifica la creazione di un oggetto funzionale
    // uno dei vantaggi è che non abbiamo dovuto dare un nome alla funzione
    // foreach(v.begin(),v.end(), funzionale ); il funzionale puo essere rimpiazzato da una labda
    // foreach(v.begin(),v.end(), [](int t) -> string { count<<i; return "finito";} )

    // se il valore di ritorno non si specifica il controllo del compilatore non viene fatto ma è lecito ritornare a patto di non ritornare cose diverse a secondo di un if tipo ecc
    // se nelle quadre della labda non si mette niente le funzioni lambda definite sono alla pari di comuni funzioni
    // se nelle quadre invece si aggiungono delle variabili è possibile renderle disponibili nel corpo della funzione

    // attenzione a chiamare una labda quando i referece passati non sono piu disponibili peche magari le funzioni sono state distrutte

    //posso passare:
    // variabili [a,b,c]
    // reference a variabili [&a,&b,&c]
    // [=] cattura tutto per valore
    // [&] cattura tutto per riferimento

    cout << "COPIA E MOVIMENTO" << endl;
    // la copia è in cotrasto con l idea di prestazioni elevate
    // se un oggetto non mi serve piu e lo voglio copiare a qualcuno posso passarne la proprietà invece di copiare e poi cancellarlo
    // se io ho una lista che popolo in una funzione e poi la voglio ritornare perche copiarla? meglio spostarla
    // espressioni temporanee come f(3+i) f(string("ciao")) il parametro passato non ha senso copiarlo (oggetti anonimi in generale)

    //il movimento è utile anche perche alcuni oggetti sono effettivamente non copiabili come uno unique_ptr che non è copiabile ma è muovibile e quindi puo ritornare da una funzione
    // per fare il movimento è necessario un costruttore di movimento.
    //Base(Base && sorgente){}
    //il c++ non genenra un costruttore di movimento di default perche non sa come è fatta la nostra classe
    // se il dato è un Rvalue o un Lvalue expired detto Xvalue allora il compilatore muove invece di copiare
    // string&& è un Rvalue reference che NON è un riferimento ad un riferimento

    //quando viene chiamata un afunzione il compilatore alloca spazio per il return prima dell invocazione quando si ritorna copia e distrugge le variabili locali
    // questa operazione puo essere semplificata chiamnado il costruttore di movimento che invece di distruggere l oggetto copiato lo smonta e quanto al suo interno viene
    // passato

    //esempio costruttore di movimento prendo dall oggetto passato e lo setto a null
    // simple_string(simplestring&& that){
    // data = that.data
    // that.data= NULL;
    // }
    // evita la copia in profondità
    // quando questo succede:

    //b(a+x)
    //b(funcCheRitorna())

    //alcuni oggetti non sono copiabili ma movibili
    // copiare un intero o muoverlo è piu o meno la stessa cosa quindi non ha senso muoverlo forse dannoso

    // tabellina Rvalue Lvalue 24:41 lezione 9
    // Lvalue è riferito a un qualcosa che ha un indirizzo fisico di memoria
    // Rvalue è il risultato temporaneo di un espressione che sta per essere cancellato

    //la tabella mostra in funzione del tipo di parametro passato alla funzione quale argomenti la funzione può ricevere intermini di Rv o Lv ecc

    // una funzione che prende in inglesso un Const Type Reference può potenzialmente prendere in ingresso qualsiasi cosa sia Rvalue che Lvalue cost o non
    // invece una funzione Type Rvalue Reference solo oggetti di tipo Rvalue quindi se l' oggetto a destra dell uguale è un Rvalue teoricamente è possibile chiamare sia il costruttore di copia che di movimento
    // lo standard prevede che in tal caso si chiami il costruttore di movimento se disponibile altrimenti quello di copia


    // Si parla quindi di costruzione per movimento ma lo stesso problema esiste anche nel caso
    //dell assegnazione tuttavia questo provoca un comportamento simile a quello del distruttore piu altre operazioni per il movimento con duplicazione di codice o comunque problemi di manutenzione

    // Per risolvere questo problema nasce un paradigma denominato Copy&Swap
    // se si fa una funzione extra che chiamiamo swap fuori dalla classe da copiare ma sua friend in modo che possa accedere ad ogni suo campo
    // è possibile rendere il costruttore di copia l' unico responsabile della copia anche quando si fa l'assegnazione e trasformare l' assegnazione in movimento
    // a seconda dei casi in cui è possibile fare lo spostamento o no.
    // ovviamente bisognerà definire pure il costruttore di movimento.

    //dunque fatta la funzione swap si scrive l'operatore di assegnazione che prende un parametro passato epr valore
    //all interno si esegue lo swap.
    //il parametro passato verrà copiato dall costruttore di copia e passato come copia all oggetto che dopo aver scambiato i riferimenti propri con quelli dell
    //oggetto in questione ritornerà distruggendo l' oggetto copiato.
    //se l'oggetto originale passato alla funzione è un Rvalue Reference e queindi sta per morire anche il passaggio dell' argomento all operatore di assegnazione
    //avverrà per movimento e non per copia garantendo un duplice comportamento nel caso dell uso dell operatore di assegnazione
    //il costruttore di movimento invece viene invece normalmente definito.
    //
    //
    //// funzione esterna da dichiarare friend della classe che si intende supportare
    //void swap(intArray& a,intArray& b) {
    //    std::swap(a.mSize, b.mSize);
    //    std::swap(a.mArray, b.mArray);
    //}
    //
    //intArray& operator=(intArray that){
    //    //that è passato per valore,
    //    //copiato o mosso a seconda del
    //    //contesto in cui è usato
    //
    //    swap(*this, that);
    //    return *this;
    //}
    //
    ////costruttore di movimento
    //intArray(intArray&& that): // notare che il parametro non è const perche il costruttore di movimento deve poter motificare l oggetto passato
    //    mSize(0), mArray(NULL)  // azzero le mie risorse e poi faccio swap
    //{
    //    swap(*this, that);
    //}
    //swap corrisponde alla funzione assembler exchange che è molto veloce
    // se lo volessimo fare manualmente occorre allocare sullo stack che non costa molto ma va fatto

    //esiste la funzione move che promuove l oggetto ad Rvalue e quindi alla possibilità di essere svuotato e lo restituisce

    //v.push_back(str) in questo caso str viene copiato nel vettore e continua ad esserci copia in str
    //v.push_back(std::move(str)) in questo caso str si svuota e non avviene la copia

    cout << "PROGRAMMAZIONE CONCORRENTE" << endl;

    //la concorrenza ha senso solo se il problema è parallelizzabile
    //ha senso se devo fare operazioni tipo IO (su disco tipo) che comportano attese e nel mentre si puo continuare la computazione
    //questo si puo fare anche con 2 processi ma comporta una comunicazione interprocesso che è onerosa
    //In C++ un programma classico è di tipo sequenziale e inizia dove viene definita la prima variabile globale e poi si esegue il main e termina con la distruzione dell ultima variabile globale
    // ha un comportamento deterministico a parità di ingresso si fa sempre la stessa cosa. l OS garantisce l isolamento in memoria allo stesso indirizzo virtuale 10 corrispondono diversi indirizzi reali

    //La programmazione concorrente parte quando nello stesso spazio di indirizzamento allo scopo di risolvere lo stesso problema 2 o piu flussi di esecuzione vengono eseguiti ogni uno fa cose diverse
    // i programmi partono tutti con lo stesso thread principale poi questi lancia altri thread che vengono eseguiti nello stesso spazio di indirizzamento quindi l indirizzi per un thread corrisponderanno algi stessi indirizzi per gli altri thread
    //Quando un programma multi thread viene eseguito il risultato non diventa dipendente solo dalgi ingressi ma anche da tanti altri fattori indiendenti
    // perche l'avantamento dei thread non è deterministico

    //ad ogni thread il sistema operativo associa una struttura dati protetta nel kernel dove si scrive a cosa è arrivato il thread per gestire il contex swithch

    //occorre sincronizzare i thread

    // problemi di sincronizzazione:
    //- deadlock(io aspetto te tu aspetti me),
    //- livelock(continuo finche tu non dici basta ma se tu non mi dici basta perche non riesci io continuo all infinito),
    //- starvation(qualcun altro ha sempre prioritàe passa sempre prima e io non faccio nulla)
    //- ECC

    // fino al c++ 2011 bisognava create i thread differentemente per ogni sistema operativo

    // lettura mentre si scrive
    // lettura contemporanea e scrittura che sovrascrive

    // il problema della propagazione dei dati fra le cache è gestito con le fence-barriere
    // l assembler dei sistemi multi core hanno istruzioni barriera che quando si vuole che altri vedano i dati forzano il flush della cache. bloccano i processori scaricano la cache e riprendono
    // queste istruzioni sono diverse fra i diversi processori
    // la barriera e quindi la sincronizzazione è costosa e rallenta l' esecuzione
    //in caso intel x86 esistono diverse istruzioni barriera
    //    -mfence full memory fence
    //    -sfence store fence nessuno scrive piu finche non si sincronizza qunato scritto
    //    -lfence load fence nessuno legge finche non viene sincromnizzata la lettura

    // processori e compilatori possono fare la speculative processing ovvero possono scambiare le istruzioni che non cambiano nulla dal punto di vista del programma tipo 2 scritture.

    //oltre i problemi classici i processori multi core per ogni core hanno delle cache quindi il dato puo diventare visibile al sistema anche tempo dopo la sua effettiva computazione
    //per regolare la sincronizzazione fra cache e ram esistono delle istruzioni di fence nell assembler che sono incorporate nelle istruzioni di sincronizzazione del c++
    // per alcune operazioni è comodo tenere un informazione in un registro ma bisogna tenere a mente che così facendo il resto del sistema non la vede l ottimizzazione del
    // compilatore si puo disattivare usando la keyword volatile che è utile solo per le variabili condivise (se no si perde solo del tempo )
    // volatile non ha alcun effetto sul sottosistema di cache semplicemente evita che il compilatore ottimizzi (tenga  la variabile in un registro per esempio)
    // usare volatile non basta perche questi non agiscono sui memory fence quindi bisogna per forza usare i costrutti del c++ per la sincronizzazione


    //esistono due metodi per scrivere programmi concorrenti uno di alto livello che si chiama std::async basato sulla copia e sugli oggetti std::future
    //se questi non sono sufficienti ci sono altre classi che permettono di manipolare i thread a basso livello come la classe thread, mutex, condition variable, atomic


    //async e future si puo usare quando i c'è il thread principale che crea altri thread con compiti distinti e indipendenti e raccoglie i risultati finali se il lavoro di un thread diventa interdipendente dal lavoro
    //degli altri thread allora non basta piu e bisogna usare le classi di manipolazione dei thread

    //async prende in ingresso un oggetto callable quindi un funzionale o puntatore a funzione e anche i suoi parametri. Async restituisce un oggetto future
    // l oggetto future ha un metodo get con cui è possibile avere il valore di ritorno del thread se pronto oppure và in blocco finche il thread non termina o lancia un eccezione.
    // se l oggetto è morto con un eccezione allora lancia l' eccezione alla chiamata di get
    // se non ha iniziato forza l esecuzione.
    //future avrà il tipo do ritorno nella definizione
    // la chiamata a get funge anche da sincronizzatore contiene un memory fence

    //async puo essere chiamato con diverse modalità che indicano come dovrà essere eseguito.

    //- std::launch::async -> crea un thread che la svolga
    //possibile che il systema non abbia risorse per creare un thread e quindi ritorna un eccezione

    //- std::launch::deferred -> crea l oggetto ma mettilo da parte se non faccio la get non lo fare e chi fa get esegue il codice

    //creare dei thread costa bisogna allocale risorse quindi non si puo creare un thread per ogni cosa
    // agoritmo somma con thread  reg11 : 1:11:00

    //quando si chiama get il valore ritorna one shot se si vuole solo controllare se sia pronto o meno si puo chiamare wait che aspetta che il thread termini senza prelevarne il valore

    // esistono anche altre funzioni come
    //- wait_for: aspetta un tempo fissato in millisecondi e poi se il dato è pronto ritorna true e false altrimenti (std::chrono::duration)
    //- wait_until: aspetta fino ad un orario precisato (std::chrono::timepoint)

    //restituiscono:
    //- std::future_status::deferred se non ancora partita
    //- std::future_status::ready se il risultato è pronto
    //- std::future_status::timeout se il tempo è scaduto ma il risultato non è tornato

    // se si chiama wait su un thread creato con modalità deferred il thread che ha chiamato wait esegue le istruzioni messe nel oggetto deferred
    // wait_for e wait_until non lanciano nulla se chiamati su un deferred

    // se il thread è in esecuzione e si cerca di distruggere future il distruttore chiama la wait e attende che questi torni il future aspetta sempre il ritorno
    // quindi NON é POSSIBILE STOPPARE UN ESECUZIONE FATTA IN UN OGGETTO FUTURE
    //reg 11 1:24:00


    //è possibile che il risultato di un thread riportato nel metodo future debba esser consultato piu di una volta a tal scopo è possibile farsi restituire un oggetto shared_future
    //lo shared future è piu oneroso ma puo essere usato e copiato nvolte e tutte mantengono il riferimento all oggetto originale. quando su un oggetto future si chiama il metodo share()
    //questo restituisce uno shared future e l oggetto stesso diventa invalido da questo momento sara usato solo lo shared future

    //shared future è copiare e movibile e offre gli stessi metodi di future

    //uno shared_future puo servire per creare catene di esecuzioni:

    //->> si esegue un thread e si ritorna lo shared_future che si passa ad altri due che quando avranno bisogno del valore preso dall oggetto future chiameranno la get() su di esso
    //    reg12 08:57 schemino

    //se il programma fa computazione pesante inutile fare tanti thread perche quelli in esecuzione sono nel numero dei processori fisici.
    //se invece si fa tanto i/o puoavere unsenso avere molti thread per passimizzare la computazione e quelliche sono inattesa attendono l i/o

    //per creare un thread con la classe thread, si passa al construttore di thread un oggetto callable come un puntatore a funzione ecc
    //    std::thred t(<funzionale>);
    //e il thread parte subito oltre all oggetto callable se aggiungo altri parametri per VALORE questi vengono passati all oggetto callable. anche l oggetto callable è passato per VALORE
    //ad una certa bisogna per forza chiamare join sul thread creato per aspettare in modo bloccante la sua terminazione. chiamare join inoltre libera le risorse del thread
    // si può forzare il passaggio per reference con std::ref(<oggetto>) che in realtà è un passagio per valore ma questo valore è un reference e quindi è come passare per reference
    // in realtà si puo passare un puntatore e bisogna però gestirne il ciclo vita perche in questo caso l uscita dallo scope non cancellerà l oggetto

    // delle volte come in un webserver forse è meglio creare subito 100 thead e usarli a rotazione invece di crearne uno per richiesta.
    // questa tecnica prende il nome di thread pooling. si prende un thread che non sta facendo niente e gli si assegna un compito. questo non
    // termina a fine compito ma resta attivo notificando la fine delle operazioni egli assegnate. Questo approccio evita l onere di creare
    // ogni volta un thread.
    // Ad un thread è possibile passare una lambda. La labda ha la possibilità di catturare il contesto di esecuzione questo è un problema
    // nel caso un thread è chiamato dentro una funzione che però termina cancellando le variabili catturate dal thread che farebbe accesso
    // tramite il sudetto reference a qualcsoa di indefinito. ma anche se il contesto fosse ancora valido ciò comporterebbe comunque i classici
    // problemi di sincronizzazione fra lettue e scritture dentro e fuori il thread

    // usare thread invece di async non permette di selezionare politica la chiamat a acostruttore di thread fa partire un thread se ci sono risorse
    // se non ci sono lancia un eccezione
    // thread non torna un valore ma torna solo void. L unica cosa che so di un thread è che ha un nome univoco che si ottiene chiamndo get_id()
    // se un eccezione si verifica nel thread e nessuno fa il catch muore tutto il processo

    // se non invochiamo join possiamo invocare detach() sul thread e questo andrà per i fatti suoi e noi perderemo ogni contatto ma comunque se il thread principale termina fa terminare pure questi thread detached

    // è possibile muoreve un thread dentro un altro per movimento scaricando la responsabilità dello stesso su un altro thread
    // se per caso il distruttore di thread viene invocato esso fa terminare tutta l' esecuzione quindi è da evitare
    // se il thread principale termina gli altri terminano forzatamente anche se sono detached

    //se ho bisogno del risultato finale di un thread usare async e future va bene se ho bisogno di risultati intermedi invece ho bisogno di
    //una variabile condivisa ma come la gestisco ?

    //il modo migliore di gestire un valore restituito da un thread è usare un oggeto di tipo std::promise esso si puo riempire con un informazione con set_value e ritorna un oggetto future con il metodo get_future()
    // sul quale è possibile interrogare se il valore è pronto o non ancora
    //reg 12 40:18 restituzione di valori parziali

    // se un thread termina per cause non naturali si invoca exit
    // std::exit fa terminare il thread principale e uscire dal processo quindi esce dal main e distrugge le variabili globali
    // std::quick_exit che non chiama il distruttore delle variabili globali

    //l uso di promise permette di sincronizzare e quindi migiora la situazioen dei thread detached.
    //è possibile per un promise associare il valore alla fine di un thread in modo da aspettare comunque la terminazione del thread detached
    //cio si fa con la funzionce set_value_at_thread_exit(T val) set_exception_at_thread_exit(T val) ma di nuovo questo maschera i risultati intermedi

    //è possibile ottenenre l identificativo del thread corrente usando std::this_thread::get_id()
    // std::this_thread::sleep_for(<duration>) viene messo in stato wait e poi in ready in attesa di essere schedulato ed eseguito
    // std::this_thread::sleep_until(<duration>) fino a momemto preciso
    // yield() mi rimento in wait e faccio passare avanti gli altri
    // con thread e promise è possibile gestire un po le sincronizzazioni come con async in realtà è esattametne quello che async fa


    // in alcuni casi la necessità non è aspettare la disponibilità di un dato piuttosto quella di essere sicuro che nessun altro stia facendo una certa cosa
    // quindi non la presenza di qualcosa ma l' assenza !!!

    // in questo caso di usano i mutex che permettono di avere accesso controllato ad una frazione di codice mutual exclusion
    //esempio si sta usando una linked list bisogna rompere i puntatori aggiungere qualcosa e poi ricollegarli se qualcun altro
    //accede anche se solo in lettura potrebbero trovare dati inconsistenti
    //allora chi deve fare operazioni di questo tipo su linked list assume il lock e poi rilascia il lock per consentire ad altri di proseguire

    // tutti devono usare lo stesso mutex creato per lo scopo dal programmatore
    // le operazioni di lock e unlock includono dei full memory fence che gestiscono i problemi di sincronizzazione fra thread.

    // la chiamata di unlock è sempre a carico del programamtore anche se il codice si ferma per un eccezione bisogna prevedere tutto

    // il mutex non ha ancuna corrispondenza con quanto protegge è tutto a carico del programmatore e quindi va documentata bene
    // il mutex serve in lettura e scrittura perche se no potrei leggere scritture parziali che sono fatte al contempo

    // se chiamo due volte lock() attendo per sempre perche davanti ad un lock non rilasciato si attende che qualcuno lo rilasci ma se a doverlo rilasciare
    //sono io che sono bloccato nell attesa questo non avverrà mai -> deadlock

    //esiste anche std::recursive_mutex per gestire questa cosa ma alla chiamata di due lock servono 2 unlock
    // esiste anche un metodo try_lock che ritorna un booleano evitando di rimanere bloccati nell attesa di un mutex

    //è molto raro usare lock su un mutex direttamnete, in genere dal mutex si crea un oggetto std::lock_guard<lockable> prende un mutex in ingresso
    //il lock_guard è un oggetto che ha un lock nel costruttore e un unlock nel distruttore nel caso un eccezione avvenga nel blocco loccato la contrazione dello stack
    // fa sbloccare il mutex. se si costruisce questo oggetto lock_guard in un metodo si assicura che quando la graffa del metodo sarà chiusa il lock sarà rilasciato
    // quindi paradigma RAII reg12 1:23:16
    // se definisco un mutex dentro una classe per quell oggetto userò sempre lo stesso mutex anche se passo l oggetto a piu thread

    // è possibile definire un blocco di codice che sarà usato solo una volta
    //std::once_flag flag; //questo flag puo tornare 1.nulla di eseguito (e fa partire la funzione) 2.esecuzione in corso 3.operzione terminata
    // se qualcun altro prova a chimare call once aspetta che l esecuzioni in corso termini e passa senza fare nulla
    // l'operazione vine fatta una volta o aspettano. in generale si usa quando si inizialissano risorse
    //void initializeSharedResources() {
    //    // This code is executed only once
    //    std::cout << "Shared resources initialized." << std::endl;
    //}
    //
    //void threadFunction() {
    //    std::call_once(flag, initializeSharedResources);
    //    // Code that uses the shared resources
    //}
    //
    //int main() {
    //    std::thread t1(threadFunction);
    //    std::thread t2(threadFunction);
    //    t1.join();
    //    t2.join();
    //    return 0;
    //}


    // ci sono situazioni in cui bisogna addormentarsi per un tempo indefinito senza consumare cicli di cpu async o promise e future è una particolarizzazione dove si attende un dato che sia pronto
    // il fatto che ci sia un dato condiviso implicitamente richiede e l' esistenza di un mutex

    //un modo per fare questo è un polling si procede se una variabile è true si aspetta se questa è false
    //reg13 06:54 code

    //questo codice non va bene perche è un attesa attiva che consuma cicli di cpu in tutti i casi

    //però questo problema dell aspetttare di essere risvegliato senza sfociare in attese attive è cosa gestita dal c++ utilizzando una std::condition_variable

    //per funzionare richiede uno unique_lock .
    //condition variable ha diversi metodi
    //- wait(unique_lock) aspetta che qualcuno dica notify (wait fa unlock poi attende notify senza consumare risorse e poi cerca di riprendersi il suo lock )
    //- notify_one() uno a caso lo faccio uscire dallo stato di attesa
    //- notify_all() tutti si svegliano ma lo scheduler del OS scheglie chi entra
    //reg13 12:0 5 code
    //non è possibile così facendo di stabilire un ordine su chi sarà il prossimo thread. esiste un metodo per farlo ma è oneroso

    //quando si usa questa techina si usa una condition variable e un mutex
    // delle volte è possibile a causa dello scheduling delle segnalazioni spurie possono permettere che un thread si svegli anche se notify non è stata chiamata.
    //questo caso è gestito da un overload del metodo wait che prende in ingresso il mutex e una lambda (che ritorna vero falso) che controlla se sia il caso di svegliarsi o no
    //reg13 esempio 26:06
    //esistono anche altre wait_for e wait_until che cessano l' attesa dopo un tempo fissato
    //std::cv_status::timeout
    //std::cv_status::no_timeout
    //per indicare tempo esaurito o sveglio per notifiy

    //le condition_variable possono ritardare la notifia alla morte del thread
    //notify_all_at_thread_exit()






    // IO << <<
    // costruttore di copia
    // ridefinizione degli operatori
    // template
    // il tipo void
    // qualcosa in piu sulla vtable magari dal libro
    //se il costruttore di copia e l operatore di assegnazione sono privati la copia non si fa.

    //SOLID
    //ACID
    //REST

    return 0;
}
