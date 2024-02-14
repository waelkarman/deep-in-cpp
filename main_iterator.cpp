#include <iostream>

using namespace std;

// iteratori
//1:02:13

//ce una classe operator per ogni tipo come  std::vector<int>::iterator ,  supporta ++ e -- punta sempre ad un elemento della collezione su puo vedere anche se punta allo stesso elemento o no con ==,  !=, begin() gli iteratori possono essere validi o non end()primo elemento fuori lista, iteratore non valido
//si puo cancellare un elemento iterando ma bisogna farlo dall iteratore non dalla lista . tipo il metodo erase accetta un iteratore come parametro.

// std::vector<int> myVector = {1, 2, 3, 4, 5};
// for (auto it = myVector.begin(); it != myVector.end(); /* not incrementing here */) {
//     if (*it == 3) {
//         it = myVector.erase(it); // Cancella l'elemento e sposta l'iteratore all'elemento successivo
//     } else {
//         ++it; // Incrementa solo se non cancelli
//     }
// }

//esisite il metodo remove_if che prende una funzione che se ritorna true cancella l elemento se ritorna false invece no. questi si chiamano funzionali e non funzioni.
// anche il metodo sort ordina ascendente per default o prende in ingresso un funzionale che definisce il criterio di ordinamento
// il metodi splice toglie elementi dal primo contenitore e li mette nel scondo passato come argomento
// unique toglie i duplicati adiacenti quindi se si fa prima sort e poi unique si tolgono tutti.
//essendo i contenitori come le mappe ordinati non è possibili costruirne una di un tipo custom senza ridefinire l' operatore minore. bisogna inoltre garantire la copia e l' assegnazione


int main(){
    cout<<"HELLO";
};

