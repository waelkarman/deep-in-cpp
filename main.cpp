#include <iostream>
#include <exception>

using namespace std;

class Base0{

public:
    string a="999";

    Base0(string x) : a(x) { // Costruttore della classe Base che richiede un parametro
        cout << "Costruttore della classe Base con x = " << x << endl;
    }

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

    cout << "cast operators!" << endl;

    //lo static cast serve a salire verticalmente sull asse ereditario ma anche a scendere amettendo
    //che l'oggetto in questione era in origine del tipo a cui si fa il cast

    //se ho un puntatore di classe base e faccio il lo static_cast a derivata NON essendo derivata originariamente
    //proverò ad accedere a zone di memoria non appartenenti all oggetto originale e questo produce
    //un comportamento indefinito

    //gli operatori di cast del c++ sono :

    // static_cast<>()  -> è un cast che puo essere fatto solo che c'è una regola di conversione che in genere coincide con una relazione di ereditarietà fra gli oggetti (controlla tutto a compiletime)
    // dynamic_cast<>()  -> è un cast che permette a runtime di verificare la compatibilità del cast (ha prestazioni piu scarse relativo alle verifiche che comporta) può lanciare leccezione bad cast a runtime
    // reinterpret_cast<>()  -> corrisponde al cast del C (int)variabile quindi il puntatore alla memoria è sempre quello così come la memoria semplicemente i byte sono interpretati diversamente
    // const_cast()  -> rimuove const da una variabile

    // usare il cast del C (int)variabile può generare problemi perche in alcuni casi il cast di oggetti ha una propria logica

    //si è detto che il puntatore in caso di c-style cast resta lo stesso ma la memoria viene interpretata diversamente
    //tuttavia nel caso di un cast di un oggetto che eredita da due classi base il puntatore cambia:


    Derived1 *b3 = new Derived1("348","388");

    Base *p31 = static_cast<Base*>(b3);
    Base0 *p32 = static_cast<Base0*>(b3);

    cout << "puntatore iniziale: " << b3 <<endl<< "puntatore base: " << p31 <<endl<< "puntatore base0: " << p32 <<endl;
    //nel primo caso il puntatore non cambia perche in memoria un puntatore a classe derivata è un puntatore a vtable per la prima classe poi per la seconda poi per
    //gli elementi dell oggetto. Quando si fa un cast si ridefinisce il puntatore con le aree di memoria in cui confinato senza modificare la memoria iniziale
    //quindi un cast nel caso del C che lascia immutato il puntatore reinterpretando la memoria è diverso da un cast corretto eseguito in c++

    cout << "ECCEZIONI:" << endl;
    //delle volte è possibile aggiungere un if per controllare un comportamento atteso altre voltre come nel caso di scanf che ritorna un il numero di caratteri letti oppure EOF
    //basta controllare il valore di ritorno che spesso viene omesso. Delle volte la gestione o non si può fare in loco perche magari esiste una dipendenza esterna
    //di solito si usa il valore di ritorno delle funzioni come feedback e si passa alla funzione un reference per portare fuori il risutlato. Questo però non vale sempre
    //perche per esempio i costruttori non possono tornare nulla al di fuori del puntatore all oggetto. Ma comuqnue tutto questo discorso vale per gli errori attesi e controllati con
    //un if di cui si ritorna codice di errore.
    //GLi errori inattesi sono quelli che si sa che possono accadere ma non ci si aspetta che avvengano. Invece di aggiungere mille controlli perche mille sono i possibilimotivi di fallimento
    //per ogni volta che quel pezzo di codice viene eseguito cosa che rallenta il programma anche se funziona bene. Poi c'è il problema di cosa fare in caso in caso di errore.se gestito
    //in un if else nell else ci sarà un casino di roba probabilmente.
    //GLi errori attesi sono quasi sempre facilmente gestibili.

    //un eccezione si lanci acon "throw" e si può lanciare su qualsiasi tipo. cio provoca l interruzione del flusso di esecuzione e si passa a gestire l exception
    //Il tipo di dato viene usato per capire come gestire, il valore descrive meglio. quindi se fai throw usi un oggetto e quel tipo di oggetto viene usato nel
    //"catch" per capire che è sudccesso
    //esiste una classe std::exception con le sue sottoclassi fatta apposta per queste cose
    //Le ecezioni si gesticono con blocchi try{}catch(){}catch(exception& e){} supponiamo questo accada dentro una fuznione e che i 2 catch non siano in grado di
    //gestire l' eccezione, quello che accade è l'uscita dalla funzione con la distruzione del contesto uscendo di scope. Si torna dal chiamante e si vede se lui
    //sa gestire l'eccezione o no risalendo nella catena di chiamate fino a cancellare l esecuzione corrente. L'unico oggetto che resta vivo è quello creato nel catch
    //di cui si fa copia (e quindi deve supportare la copia in caso di eccezione custom)
    //il codice riprende dopo il blocco try-catch una volta eseguito il codice in catch

    //catch(...){} significa qualunque eccezione sia fa questo
    //in un blocco catch per rilanciare l eccezione stessa si usa solo "throw;"

    //Nel catch fra tonde si mette l' oggetto di cui si è fatto throw tale. E' bene mettere nel catch un reference all oggetto (che viene passato al catch un po come il passaggio a una funzione)
    //in modo che se l oggetto non è proprio quello specificato avendo indietro un puntatore non si perde l' informazione sul tipo originale perche metto un oggetto derivato in un eccezione base
    //e avviene lo slicing ovvero una parte dell oggetto viene copiata e un parte viene persa essendo tale classe appunto una classe base.

    //si puo creare una classe che importa exception ed eredita da exceprion che ridefinisce what() utile per creare eccezioni oppure si usano quelle predefinite

    //c++ non supporta finally perche lo stack si contrae e vengono chiamati i distruttori degli oggetti.

    throw std::out_of_range("Indice fuori dal range valido");

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

    //make_shared<>()
    // 51:03

    //- std::weak_ptr<type> permette di osservare il contenuto di uno shared_ptr

    //- std::unique_ptr<type> esiste un solo puntatore se lo passo ad un altro io mi distruggo



    cout << "REFERENCE-POINTER"<<endl;
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

    // explicit, inline, const, volatile, slicing, const noexcept override




    // iteratori
    // threads

    // costruttore di copia
    // ridefinizione degli operatori
    // puntatori a funzione
    // funzioni
    // template
    // il tipo void
    // qualcosa in piu sulla vtable magari dal libro
    // quali problemi comporta mettere privato il costruttore di copia ?
    //se il costruttore di copia e l operatore di assegnazione sono privati la copia non si fa.

    //SOLID
    //ACID
    //REST

    return 0;
}
