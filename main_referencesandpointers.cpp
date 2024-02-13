#include <iostream>

using namespace std;

/*
Puntatori
Sintassi: Un puntatore è dichiarato usando un asterisco (*) nella sua dichiarazione. Ad esempio: int* ptr;
Indirizzamento: Un puntatore contiene l'indirizzo di memoria di un'altra variabile. Può essere modificato per puntare a un'altra variabile in qualsiasi momento.
Indirezione: L'operatore di indirezione (*) è usato per accedere al valore dell'oggetto a cui il puntatore punta. Ad esempio: *ptr = 10;
Valori Nulli: Un puntatore può essere impostato su nullptr (o, in C++ più vecchi, NULL), indicando che non punta a nulla.
Aritmetica dei Puntatori: È possibile eseguire aritmetica sui puntatori (ad es., ptr++ per spostarsi all'indirizzo della prossima variabile di un tipo specifico), il che è utile in contesti come gli array.
Riferimenti
Sintassi: Un riferimento è dichiarato usando l'operatore & nella sua dichiarazione. Ad esempio: int& ref = var;
Alias: Un riferimento funge da alias per un'altra variabile. Una volta inizializzato con una variabile, non può essere cambiato per riferirsi a un'altra variabile. In altre parole, un riferimento è sempre collegato alla variabile con cui è stato inizializzato.
Indirezione Nascosta: Non è necessario usare un operatore per accedere al valore a cui il riferimento si riferisce; si usa il nome del riferimento direttamente. Ad esempio: ref = 10; cambierà il valore della variabile a cui ref si riferisce.
Nessun Valore Nullo: Un riferimento deve essere inizializzato al momento della dichiarazione e non può essere nullo. Non esiste un "riferimento nullo" in C++ standard.
Nessuna Aritmetica: Non si può fare aritmetica con i riferimenti.
*/

int main(){
    cout<<"HELLO";
};

