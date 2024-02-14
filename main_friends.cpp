#include <iostream>

using namespace std;

//le funzioni friend devono esistere nel codice prima di essere definite friend
//i campi privati on possono essere visti all esterno della classe stessa tuttavia è possibile dichiarare friend altre classi o funzioni per permettergli
//di accedere ai campi private.

//void func(A &a){a.datoprivato = 1;}
//class ClasseA {
//    friend class ClasseB; // Dichiarazione di amicizia
//    friend void func(A&);
//private:
//    int datoPrivato;
//public:
//    ClasseA() : datoPrivato(42) {} // Costruttore che inizializza datoPrivato
//};
//class ClasseB {
//public:
//    void mostraDatoPrivatoDaA(const ClasseA& a) {
//        // Accesso diretto al membro privato di ClasseA grazie alla friendship
//        std::cout << "Dato privato di ClasseA: " << a.datoPrivato << std::endl;
//    }
//};

//int main() {
//    ClasseA a;
//    ClasseB b;
//    b.mostraDatoPrivatoDaA(a); // Mostra: Dato privato di ClasseA: 42
//    return 0;
//}



// un metodo definito const non modifica lo stato dell oggetto se const è abbinato ad un reference permette di evitare la copia tenendo immutato l oggetto passato
// override serve a specificare che si fa un override e quindi il compilatore eseguirà un marching dei tipi
// noexcept dice al compilatore che una funzione non lancerà eccezioni questo permette al compilatore di ottimizzare meglio il codice perche sa di non dover gestire eccezioni
//slicing per slicing si intende la copia di qualcosa in uno spazio piu piccolo che è consentita senza problemi ma non viene tutto effettivamente copiato ma solo la parte che ci entra con la conseguente perdita di informazione

int main(){
    cout<<"HELLO";
};

