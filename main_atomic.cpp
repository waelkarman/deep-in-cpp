#include <iostream>

using namespace std;

/*
le operazioni di lettura e scrittura su una cella di memoria non offrono garanzie sulla visibilità delle operazioni eseguite da piu thread

le operazioni atomic offrono una garanzia di visibilità sono osservabili nell ordine in cui realmente avvengono (quindi contengono memory fence)
il metodo load applicato ad un dato atomic fa la lettura del dato.
fetch_sub
fetch_add
exchange
atomic ha gia specializzazioni per interio boolean o comunque tipi piccoli
*/


int main(){
    cout << "HI" << endl;
}
