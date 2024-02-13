#include <iostream>

using namespace std;

class Base0{
public:
    string a="999";

    Base0(string x) : a(x) {
        cout << "Costruttore della classe Base0 con x = " << x << endl;
    }

    Base0(const Base0& b ){}

    virtual void stampa0(){
        cout<< a << endl;
    }
    void stampa2(){
        cout<< a << endl;
    }
    virtual void stampa5(){
        cout<< a << endl;
    }
    ~Base0(){
        cout << "Distruttore Base0" << endl;
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
        //cout << "Mentre quello della classe Base1 ereditata con j = " << j << endl;
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
    void stampa5() override {
        cout<< "APRO UN FILE" << endl;
    }
    ~Derived1(){
        cout << "Distruttore Derived1" << endl;
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
    cout << "INHERITANCE:" << endl;

    Base1 *b1 = new Derived1("777","888");
    Base1 *b2 = new Derived2();

    b1->stampa0();
    b2->stampa0();

    b1->stampa1();
    b2->stampa1();

    b1->stampa2();
    b2->stampa2();

    //AGGIUNGI IL CASO APERTURA FILE IN CLASSE DERIVATA IL CUI METODO é VIRTUAL NELLA Base1 E VEDI SE VIENE CHIAMATO IL DISTRUTTORE DELLA Base1
    Base0 *b3 = new Derived1("123","321");
    b3->stampa5();
    Derived1* d1 = dynamic_cast<Derived1*>(b3);
    if (d1 != nullptr) {
        delete d1;
    }

    //Non chiama il distruttore della classe derivata e quindi non chiudo il file aperto nel metodo overriden nella classe Derived1
    //delete b3;

    return 0;
}
