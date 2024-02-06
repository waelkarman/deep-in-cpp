#include <iostream>

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

    // static_cast<>()  -> è un cast che puo essere fatto solo che c'è una regola di conversione che in genere coincide con una relazione di ereditarietà fra gli oggetti
    // dynamic_cast<>()  -> è un cast che permette a runtime di verificare la compatibilità del cast (ha prestazioni piu scarse relativo alle verifiche che comporta)
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





    return 0;
}
