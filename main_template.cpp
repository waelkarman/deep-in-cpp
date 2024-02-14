#include <iostream>

using namespace std;

template <typename F>
void some_function(F& f,int i){
    f(i); // f puo essere sia un funzionale che un puntatore a funzione
}

template<class T,int s>
class Goperation {

public:

    Goperation():counter(0){
    }

    bool operator>(const Goperation<T,s>& b) const{
        if(counter>b.getCounter() && counter>s){
            return true;
        }else
            return false;
    }

    bool operator<(const Goperation<T,s>& b) const{
        if(counter<b.getCounter() && counter<s)
            return true;
        else
            return false;
    }

    int getCounter() const{
        return counter;
    }

    int max(T a,T b){
        if(a>b)
            return a;
        else
            return b;
    }

    int sum(){
        counter++;
        return counter;
    }

private:
    int counter;
};



template<>
class Goperation<string,6>{

public:

    Goperation():counter(0){
    }

    bool operator>(const Goperation<string,6>& b) const{
        if(counter>b.getCounter() && counter>6){
            return true;
        }else
            return false;
    }

    bool operator<(const Goperation<string,6>& b) const{
        if(counter<b.getCounter() && counter<6)
            return true;
        else
            return false;
    }

    int getCounter() const{
        return counter;
    }

    int max(string a,string b){
        return b.size();
    }

    int sum(){
        counter++;
        return counter;
    }

private:
    int counter;

};


int main()
{
    cout << "Generic Programming int! " << endl;

    Goperation<int,7> a;
    Goperation<int,7> b;

    cout << "max " << a.max(2,3)<< endl;
    cout << "max " << a.getCounter()<< endl;
    a.sum();
    a.sum();
    a.sum();

    if(a>b){
        cout << "vero"<< endl;
    }else{
        cout << "falso"<< endl;
    }

    cout << "Generic Programming str! " << endl;

    Goperation<string,1> c;
    Goperation<string,1> d;

    //cout << "max " << c.max("a","fcfghjnb")<< endl; impossibile necessita di specializzazione
    cout << "max " << c.getCounter()<< endl;
    c.sum();
    c.sum();
    c.sum();

    if(c>d){
        cout << "vero"<< endl;
    }else{
        cout << "falso"<< endl;
    }


    cout << "Generic Programming SPECIALIZZAZIONE per valore int=6! " << endl;

    Goperation<string,6> e;
    Goperation<string,6> f;

    cout << "max " << e.max("a","fcfghjnb")<< endl;
    cout << "max " << e.getCounter()<< endl;
    e.sum();
    e.sum();
    e.sum();

    if(e>f){
        cout << "vero"<< endl;
    }else{
        cout << "falso"<< endl;
    }

    return 0;
}
