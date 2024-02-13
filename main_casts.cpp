#include <iostream>

using namespace std;

/*
lo static cast serve a salire verticalmente sull asse ereditario ma anche a scendere amettendo
che l'oggetto in questione era in origine del tipo a cui si fa il cast

se ho un puntatore di classe base e faccio il lo static_cast a derivata NON essendo derivata originariamente
proverò ad accedere a zone di memoria non appartenenti all oggetto originale e questo produce
un comportamento indefinito

gli operatori di cast del c++ sono :

static_cast<>()  -> è un cast che puo essere fatto solo che c'è una regola di conversione che in genere coincide con una relazione di ereditarietà fra gli oggetti (controlla tutto a compiletime)
dynamic_cast<>()  -> è un cast che permette a runtime di verificare la compatibilità del cast (ha prestazioni piu scarse relativo alle verifiche che comporta) può lanciare leccezione bad cast a runtime
reinterpret_cast<>()  -> corrisponde al cast del C (int)variabile quindi il puntatore alla memoria è sempre quello così come la memoria semplicemente i byte sono interpretati diversamente
const_cast()  -> rimuove const da una variabile

usare il cast del C (int)variabile può generare problemi perche in alcuni casi il cast di oggetti ha una propria logica

si è detto che il puntatore in caso di c-style cast resta lo stesso ma la memoria viene interpretata diversamente
tuttavia nel caso di un cast di un oggetto che eredita da due classi base il puntatore cambia:

nel primo caso il puntatore non cambia perche in memoria un puntatore a classe derivata è un puntatore a vtable per la prima classe poi per la seconda poi per
gli elementi dell oggetto. Quando si fa un cast si ridefinisce il puntatore con le aree di memoria in cui confinato senza modificare la memoria iniziale
quindi un cast nel caso del C che lascia immutato il puntatore reinterpretando la memoria è diverso da un cast corretto eseguito in c++
*/


class Base0{
public:
    string a="999";

    Base0(string x) : a(x) {
        cout << "Costruttore della classe Base1 con x = " << x << endl;
    }

    Base0(const Base0& b ){}

    virtual void stampa0(){
        cout<< a << endl;
    }
    void stampa2(){
        cout<< a << endl;
    }
};

class Base1{
public:
    string a="123";

    virtual void stampa0(){
        cout<< a << endl;
    }
    void stampa1(){
        cout<< a << endl;
    }
    virtual void stampa2(){
        cout<< a << endl;
    }
};

class Derived1: public Base1, public Base0{
public:
    string a="789";

    Derived1(string k, string j) : Base0(j), a(k) {
        cout << "Costruttore della classe Derivata con k = " << k << endl;
        cout << "Mentre quello della classe Base1 ereditata con j = " << j << endl;
    }

    void stampa0() override {
        cout<< a << endl;
    }
    void stampa1(){
        cout<< a << endl;
    }
    void stampa2() override {
        cout<< a << endl;
        Base1::stampa2();
        Base0::stampa2();
    }
};

class Derived2: public Base1{
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
    Base1 *b1 = new Derived1("777","888");
    Base1 *b2 = new Derived2();

    Derived1 *b3 = new Derived1("348","388");
    Base1 *p1 = static_cast<Base1*>(b3);
    Base0 *p2 = static_cast<Base0*>(b3);

    cout << "---CAST OPERATOR---" << endl;
    //Dimostrazione del perchè il C-style cast non va bene
    cout << p1 << endl;
    cout << p2 << endl;

    return 0;
}
