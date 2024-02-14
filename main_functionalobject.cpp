#include <iostream>
#include <functional>

using namespace std;

//cout << "PUNTATORI A FUNZIONE: "<<endl;

// sintassi <tipo_ritornato>(*var )(<argomenti>)
// assegnamento int f(int i, double d){ .. .. }
// int (*var)(int,double);
// var = f;
// var = &f; identico al precedente
// var(10,3.48);
// (*var)(10,3.48); identico al precedente

// il match dei tipi deve essere perfetto anche se ci sono parametri di default va specificato il tipo perche i parametri di default sono sempre parametri passati alla funzione.

//cout << "FUNCTIONAL OBJECT" << endl;

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

//cout << "ESPRESSIONI LAMBDA" << endl;

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


int f0(const int& i){ cout<<i<<endl; return i; }
int f1(const int& i){ cout<<i+1<<endl; return i+1; }

class Base0{
    int (*function_ptr_b)(const int&);
    int (*function_ptr_r)(const int&);
public:
    void setFunc(int (*func_ptr)(const int&)){
        function_ptr_b=func_ptr;
    }
    void setFuncRef(int (*&func_ptr)(const int&)){
        function_ptr_r=func_ptr;
    }
    void execute(const int& k){
        function_ptr_b(k);
    }
    void executeRef(const int& k){
        function_ptr_r(k);
    }
};

class Base1{
public:
    int a;
    int operator()(int i){
        cout << i+a << endl;
        return i+a;
    }
    int get_a(){
        return a;
    }
};

template <typename F>
void some_function(F& f,int i){
    f(i); // f puo essere sia un funzionale che un puntatore a funzione
}

int main(){
    //declaration function ptr
    int (*function_ptr_a)(const int&);
    function_ptr_a = f0;
    function_ptr_a(10);
    cout << "funzione: " << function_ptr_a << endl;
    cout << "funzione: " << f0 << endl;
    function_ptr_a = &f0;
    function_ptr_a(19);
    cout << "funzione: " << function_ptr_a << endl;
    cout << "funzione: " << &f0 << endl;
    function_ptr_a = f1;
    function_ptr_a(15);

    cout << "----" << endl;

    Base0 b1;
    b1.setFunc(f0);
    b1.execute(70);

    Base0 b2;
    {
        int (*function_ptr_c)(const int&) = [](const int& i){ cout<<i+5<<endl; return i+5; };
        b2.setFuncRef(function_ptr_c);
        b2.executeRef(100);
    }
    // The reference still stay even if destruction was expected
    b2.executeRef(101);

    cout << "----" << endl;

    Base1 func_class;
    func_class.a=15;
    func_class(50); //chiamata come se fosse una funzione
    cout<<func_class.get_a()<<endl;

    cout << "----" << endl;

    //Dovrebbe rompersi perchè il riferimento ad y è stato cancellato
    std::function<int(const int&)> function_with_capture;
    {
        int y = 5;
        function_with_capture = [&y](const int& i){ cout<<i+y<<endl; y=2; return i+y; };
        function_with_capture(10);
    }
    function_with_capture(80);

    //POSSO PASSARE UN FUNZIONALE O UNA FUNZIONE
    std::function<int(const int&)> function_ptr = [](const int& i){ cout<<i+4<<endl; return i+4; };
    some_function(func_class,5); //funzionale
    some_function(function_ptr,5); //puntatore a funzione

};

