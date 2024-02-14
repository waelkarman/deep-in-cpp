#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// iteratori
//1:02:13

//ce una classe operator per ogni tipo come  std::vector<int>::iterator ,  supporta ++ e -- punta sempre ad un elemento della collezione su puo vedere anche se punta allo stesso elemento o no con ==,  !=, begin() gli iteratori possono essere validi o non end()primo elemento fuori lista, iteratore non valido
//si puo cancellare un elemento iterando ma bisogna farlo dall iteratore non dalla lista . tipo il metodo erase accetta un iteratore come parametro.

//esisite il metodo remove_if che prende una funzione che se ritorna true cancella l elemento se ritorna false invece no. questi si chiamano funzionali e non funzioni.
// anche il metodo sort ordina ascendente per default o prende in ingresso un funzionale che definisce il criterio di ordinamento
// il metodi splice toglie elementi dal primo contenitore e li mette nel scondo passato come argomento
// unique toglie i duplicati adiacenti quindi se si fa prima sort e poi unique si tolgono tutti.
//essendo i contenitori come le mappe ordinati non è possibili costruirne una di un tipo custom senza ridefinire l' operatore minore. bisogna inoltre garantire la copia e l' assegnazione


int main(){
    int test = 0;
    cout << "---------- " << ++test << endl;
    {
        std::vector<int> v = {1, 2, 3, 4, 5};

        for (auto it = v.begin(); it != v.end(); /* not incrementing here */) {
            if (*it == 3) {
                it = v.erase(it); // Cancella l'elemento e sposta l'iteratore all'elemento successivo
            } else {
                ++it; // Incrementa solo se non cancelli
            }
        }
        for_each(v.begin(),v.end(),[](int i){cout<<i;});
        cout << endl;
    }

    cout << "---------- " << ++test << endl;

    {
        std::vector<int> v = {1, 2, 3, 4, 5};

        for_each(v.begin(), v.end(),
        [](int i){
            if(i==2){cout<<"true"<<endl;}else{cout<<"false"<<endl;}
        });
    }

    cout << "---------- " << ++test << endl;

    {
        std::vector<int> v = {1, 2, 2, 4, 5};

        for_each(v.begin(),v.end(),[](int i){cout<<i;});

        v.erase(remove_if(v.begin(), v.end(), [](int i){
            if(i==2){
                return true;
            }else{
                return false;
            }
        }), v.end());
        cout << endl;
        for_each(v.begin(),v.end(),[](int i){cout<<i;});
        cout << endl;
    }

    cout << "---------- " << ++test << endl;

    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        std::vector<int>::iterator it;
        for(it=v.end(); it!=v.begin(); ){
            if(*it==4){
                v.erase(it);
            }else{
                --it;
            }
        }
        for_each(v.begin(),v.end(),[](int i){cout<<i;});
        cout << endl;
    }

    cout << "---------- " << ++test << endl;

    {
        std::vector<int> v = {4, 8, 1, 6, 4, 3};

        sort(v.begin(), v.end(), [](int a, int b){
            if(a<=b){return false;}else{return true;}
        });
        for_each(v.begin(),v.end(),[](int i){cout<<i;});
        cout << endl;
    }

};

