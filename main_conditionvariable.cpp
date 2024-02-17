#include <iostream>

using namespace std;



// ci sono situazioni in cui bisogna addormentarsi per un tempo indefinito senza consumare cicli di cpu async o promise e future è una particolarizzazione dove si attende un dato che sia pronto
// il fatto che ci sia un dato condiviso implicitamente richiede e l' esistenza di un mutex

//un modo per fare questo è un polling si procede se una variabile è true si aspetta se questa è false
//reg13 06:54 code

//questo codice non va bene perche è un attesa attiva che consuma cicli di cpu in tutti i casi

//però questo problema dell aspetttare di essere risvegliato senza sfociare in attese attive è cosa gestita dal c++ utilizzando una std::condition_variable

//per funzionare richiede uno unique_lock .
//condition variable ha diversi metodi
//- wait(unique_lock) aspetta che qualcuno dica notify (wait fa unlock poi attende notify senza consumare risorse e poi cerca di riprendersi il suo lock )
//- notify_one() uno a caso lo faccio uscire dallo stato di attesa
//- notify_all() tutti si svegliano ma lo scheduler del OS scheglie chi entra
//reg13 12:0 5 code
//non è possibile così facendo di stabilire un ordine su chi sarà il prossimo thread. esiste un metodo per farlo ma è oneroso

//quando si usa questa techina si usa una condition variable e un mutex
// delle volte è possibile a causa dello scheduling delle segnalazioni spurie possono permettere che un thread si svegli anche se notify non è stata chiamata.
//questo caso è gestito da un overload del metodo wait che prende in ingresso il mutex e una lambda (che ritorna vero falso) che controlla se sia il caso di svegliarsi o no
//reg13 esempio 26:06
//esistono anche altre wait_for e wait_until che cessano l' attesa dopo un tempo fissato
//std::cv_status::timeout
//std::cv_status::no_timeout
//per indicare tempo esaurito o sveglio per notifiy

//le condition_variable possono ritardare la notifia alla morte del thread
//notify_all_at_thread_exit()

int main(){
    cout<<"HELLO";
};

