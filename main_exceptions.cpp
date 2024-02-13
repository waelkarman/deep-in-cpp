#include <iostream>
#include <exception>

/*
delle volte è possibile aggiungere un if per controllare un comportamento atteso altre voltre come nel caso di scanf che ritorna un il numero di caratteri letti oppure EOF
basta controllare il valore di ritorno che spesso viene omesso. Delle volte la gestione o non si può fare in loco perche magari esiste una dipendenza esterna
di solito si usa il valore di ritorno delle funzioni come feedback e si passa alla funzione un reference per portare fuori il risutlato. Questo però non vale sempre
perche per esempio i costruttori non possono tornare nulla al di fuori del puntatore all oggetto. Ma comuqnue tutto questo discorso vale per gli errori attesi e controllati con
un if di cui si ritorna codice di errore.
GLi errori inattesi sono quelli che si sa che possono accadere ma non ci si aspetta che avvengano. Invece di aggiungere mille controlli perche mille sono i possibilimotivi di fallimento
per ogni volta che quel pezzo di codice viene eseguito cosa che rallenta il programma anche se funziona bene. Poi c'è il problema di cosa fare in caso in caso di errore.se gestito
in un if else nell else ci sarà un casino di roba probabilmente.
GLi errori attesi sono quasi sempre facilmente gestibili.

un eccezione si lancia con "throw" e si può lanciare qualsiasi oggetto se si estende exception si accoda alla standard libary ma non è dettoche bisogna farlo. cio provoca l interruzione del flusso di esecuzione e si passa a gestire l exception
Il tipo (nel catch) di dato viene usato per capire come gestire, il valore descrive meglio. quindi se fai throw usi un oggetto e quel tipo di oggetto viene usato nel
"catch" per capire che è sudccesso
esiste una classe std::exception con le sue sottoclassi fatta apposta per queste cose
Le ecezioni si gesticono con blocchi try{}catch(){}catch(exception& e){} supponiamo questo accada dentro una fuznione e che i 2 catch non siano in grado di
gestire l' eccezione, quello che accade è l'uscita dalla funzione con la distruzione del contesto uscendo di scope. Si torna dal chiamante e si vede se lui
sa gestire l'eccezione o no risalendo nella catena di chiamate fino a cancellare l esecuzione corrente. L'unico oggetto che resta vivo è quello creato nel catch
di cui si fa copia (e quindi deve supportare la copia in caso di eccezione custom)
il codice riprende dopo il blocco try-catch una volta eseguito il codice in catch

catch(...){} significa qualunque eccezione sia fa questo
in un blocco catch per rilanciare l eccezione stessa si usa solo "throw;"

Nel catch fra tonde si mette l' oggetto di cui si è fatto throw tale. E' bene mettere nel catch un reference all oggetto (che viene passato al catch un po come il passaggio a una funzione)
in modo che se l oggetto non è proprio quello specificato avendo indietro un puntatore non si perde l' informazione sul tipo originale perche metto un oggetto derivato in un eccezione base
e avviene lo slicing ovvero una parte dell oggetto viene copiata e un parte viene persa essendo tale classe appunto una classe base.

si puo creare una classe che importa exception ed eredita da exceprion che ridefinisce what() utile per creare eccezioni oppure si usano quelle predefinite

c++ non supporta finally perche lo stack si contrae e vengono chiamati i distruttori degli oggetti.
*/


using namespace std;


class exc_custom_pure_std:public exception{
    string a;
public:
    exc_custom_pure_std(){}

    exc_custom_pure_std(string n):a(n){
        cout<<"exc_custom_pure_std LAUNCHED"<< endl;
    }
    exc_custom_pure_std(const exc_custom_pure_std& ecp){
        a=ecp.get_a();
    }
    string get_a() const {
        return a;
    }
    const char * what(){
        return "exception catched guess type and message!";
    }

};

class exc_custom_pure{
    string a;
public:
    exc_custom_pure(){}

    exc_custom_pure(string n):a(n){
        cout<<"exc_custom_pure LAUNCHED"<< endl;
    }
    exc_custom_pure(const exc_custom_pure& ecp){
        a=ecp.get_a();
    }
    string get_a() const {
        return a;
    }

};

class exc_custom:public exception{
public:
    exc_custom(){
        cout<<"exc_custom build"<< endl;
    }

    const char* what(){
        return "exc_custom LAUNCHED";
    }
};

class exc_custom_test:public exception{
public:
    exc_custom_test(){
        cout<<"unknown build"<< endl;
    }

    const char* what(){
        return "unknown LAUNCHED";
    }
};




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
        try{
            throw exc_custom_pure_std(a);
        }
        catch(out_of_range& e){
            cout << e.what() << " -> out_of_range" << endl;
        }
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
        try{
            throw exc_custom_test();
        }
        catch(...){
            cout << "Unknown inner exception." << std::endl;
        }

        try{
            throw exc_custom_test();
        }
        catch(out_of_range e){
            cout << e.what() << " -> exc_custom_test" << endl;
        }

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


int main()
{
    int test=0;
    Base *b1 = new Derived1("777","888");

    cout << "<- "<< ++test << endl << endl;

    try{
        b1->stampa0();
    }
    catch(...){
        cout << "Unknown outer exception." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        b1->stampa1();
    }
    catch(exc_custom_pure_std& e){
        cout << typeid(e).name() << std::endl;
        cout << e.what() << std::endl;
        cout << "return copied value  - " << e.get_a() << endl << endl ;
    }
    //catch(exception e){
    //    cout << typeid(e).name() << std::endl;
    //    cout << e.what() << std::endl;
    //    auto ee = static_cast<exc_custom_pure_std>(e);
    //    cout << " - " << ee.get_a() << endl << endl ;
    //}



    cout << "---Exceptions---" << endl;

    cout << "<- "<< ++test << endl << endl;

    try{
        throw exc_custom();
    }
    catch(out_of_range e){
        cout << e.what() << " -> out_of_range" << endl;
    }
    catch(exc_custom e){
        cout << e.what() << " -> exc_custom" << endl;
    }
    catch(...){
        cout << "Unknown exception ." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        throw exc_custom_pure();
    }
    catch(out_of_range e){
        cout << e.what() << " -> out_of_range" << endl;
    }
    catch(exc_custom_pure e){
        cout << " -> exc_custom_pure" << endl;
    }
    catch(...){
        cout << "Unknown exception ." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        throw std::out_of_range("Index out of range");
    }
    catch(out_of_range e){
        cout << e.what() << " -> out_of_range" << endl;
    }
    catch(exception e){
        cout << e.what() << " -> exception" << endl;
    }
    catch(...){
        cout << "Unknown exception ." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        throw std::out_of_range("Index out of range");
    }
    catch(exception e){
        cout << e.what() << " -> exception" << endl;
    }
    catch(out_of_range e){
        cout << e.what() << " -> out_of_range" << endl;
    }
    catch(...){
        cout << "Unknown exception ." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        throw exc_custom();
    }
    catch(out_of_range e){
        cout << e.what() << " -> out_of_range" << endl;
    }
    catch(exc_custom_pure e){
        cout << " -> exc_custom_pure" << endl;
    }
    catch(...){
        cout << "Unknown exception." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;

    try{
        throw exc_custom_test();
    }
    catch(exception& e){
        cout << e.what() << " ->GENERAL EXCEPTION" << endl;
        cout << typeid(e).name() << std::endl;
    }
    catch(out_of_range& e){
        cout << " -> out_of_range" << endl;
    }
    catch(...){
        cout << "Unknown exception exit execution." << std::endl;
    }

    cout << "<- "<< ++test << endl << endl;


    return 0;
}
