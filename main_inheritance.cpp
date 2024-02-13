#include <iostream>

using namespace std;

class Base0{
public:
    string a="999";

    Base0(string x) : a(x) {
        cout << "Costruttore della classe Base con x = " << x << endl;
    }

    Base0(const Base0& b ){}

    virtual void stampa0(){
        cout<< a << endl;
    }
    void stampa2(){
        cout<< a << endl;
    }
};

class Base{
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

class Derived1: public Base, public Base0{
public:
    string a="789";

    Derived1(string k, string j) : Base0(j), a(k) {
        cout << "Costruttore della classe Derivata con k = " << k << endl;
        cout << "Mentre quello della classe Base ereditata con j = " << j << endl;
    }
    void stampa0() override {
        cout<< a << endl;
    }
    void stampa1(){
        cout<< a << endl;
    }
    void stampa2() override {
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
    cout << "INHERITANCE:" << endl;

    Base *b1 = new Derived1("777","888");
    Base *b2 = new Derived2();

    b1->stampa0();
    b2->stampa0();

    b1->stampa1();
    b2->stampa1();

    b1->stampa2();
    b2->stampa2();

    cout << "cast operators!" << endl;
    Derived1 *b3 = new Derived1("348","388");
    Base *p31 = static_cast<Base*>(b3);
    Base0 *p32 = static_cast<Base0*>(b3);

    //AGGIUNGI IL CASO APERTURA FILE IN CLASSE DERIVATA IL CUI METODO é VIRTUAL NELLA BASE E VEDI SE VIENE CHIAMATO IL DISTRUTTORE DELLA BASE

    return 0;
}
