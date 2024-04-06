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

    // IO << <<
    // costruttore di copia
    // ridefinizione degli operatori
    // template
    // il tipo void
    // qualcosa in piu sulla vtable magari dal libro
    //se il costruttore di copia e l operatore di assegnazione sono privati la copia non si fa.



/*

    un oggetto visibile solo ad un thread è thread safe
    un oggetto immutabile è thread safe
    un oggetto non immutabile e accessibile da piu thread va incapsulato in un oggetto che garantisca la sua sinchronizzazione

    ->bozza sequenziale per dominare il problemas
    ->iniziare con riconoscere le operazioni parallele
    ->vedere sotto quali condizioni queste operazioni possono esser fatte parallelamente (lavare piatti -> mangiare)
    ->le variabili risorse che intervengono in queste condizioni saranno accessibili ai due ipotetici thread che eseguiranno le
    ->operazioni parallele. assicurarne la sincronizzazione

    -evitare quanto piu le variabili globali per limitare i punti di contatto fra i thread
    -evitare di prendere possesso di una risorsa mentre se ne ha gia un altra per cause deadlock
    -oppure selezione un ordine di acquisizione risorse esiste un supporto del c++ come std::lock
    -usare il lock il meno possibile per il minimo tempo possibile
    -documentare sempre la concorrenza
    -attività indipendenti
    -blocchi di dati
    -capire la macchina quanti thread in parallelo è in gradi di eseguire una macchina

    il numero dei core è in aumento quindi tenere a mente il trend che si sta pigliando quindi cercare di scrivere applicazioni
    che tengano in conto questo
*/

    return 0;
}
