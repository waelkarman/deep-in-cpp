#include <iostream>

using namespace std;

/*
Operatori che puoi sovraccaricare:
Aritmetici: +, -, *, /, %
Operazioni di confronto: ==, !=, <, >, <=, >=
Operatori logici: &&, || (ma con restrizioni sul cortocircuito)
Operatori di assegnazione: =, +=, -=, *=, /=, %=, <<=, >>=, &=, |=, ^=
Operatori di accesso: [], ->, ->*, ()
Operatori unari: +, -, *, &, ~, !, ++, --
Gestione della memoria: new, new[], delete, delete[]
Altri operatori: ,, <<, >>, &, |, ^, ~

la definizione degli operatori per oggetti diversi conviene farla fuori dalle classi un modo che siano entrambe già definite
*/


class Base0;

class Base1{
public:
    int u = 7;
    bool operator>(const Base0& i);
};

class Base0{
public:
    int a;
    int b;

    Base0(int a,int b):a(a),b(b){

    }

    bool operator>(const Base1& i) {
        if(this->a > i.u){
            return true;
        }else{
            return false;
        }
    }

    bool operator>(const Base0& i) {
        if(this->a > i.a){
            return true;
        }else{
            return false;
        }
    }

    bool operator<(const Base0& i) {
        if(this->a < i.a){
            return true;
        }else{
            return false;
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const Base0 &base) {
        return os << "a: " << base.a << ", b: " << base.b;
    }

    bool operator==(const Base0& i) {
        if(this->a == i.a){
            return true;
        }else{
            return false;
        }
    }

    const Base0& operator=(const Base0& i) {
        this->a=i.a;
        return *this;
    }

    const Base0& operator+(const Base0& i) {
        this->a+=i.a;
        return *this;
    }

};



bool Base1::operator>(const Base0& i){
    if(this->u > i.a){
        return true;
    }else{
        return false;
    }
}

int main(){
    int test = 0;
    Base0 b1(1,2);
    Base0 b2(2,2);
    Base0 b3(3,2);
    Base0 b4(4,2);
    Base0 b5(5,2);
    Base0 b7(55,23);

    cout << "---------- " << ++test << endl;
    if(b1>b2){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    cout << "---------- " << ++test << endl;
    if(b1<b2){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    cout << "---------- " << ++test << endl;
    b1=b5;
    if(b1<b2){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    cout << "---------- " << ++test << endl;
    if(b1==b1){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    cout << "---------- " << ++test << endl;
    if(b1==b2){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    cout << "---------- " << ++test << endl;
    cout << b1.a << endl;
    b1=b1+b1;
    cout << b1.a << endl;
    Base1 b6;
    if(b1>b6){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    if(b6>b1){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }


    cout << "---------- " << ++test << endl;
    cout << b7 << endl;

};


