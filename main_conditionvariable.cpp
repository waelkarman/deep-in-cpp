#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

/*
 *RAII (Resource Acquisition Is Initialization)
 *
ci sono situazioni in cui bisogna addormentarsi per un tempo indefinito senza consumare cicli di cpu async o promise e future è una
particolarizzazione dove si attende un dato che sia pronto il fatto che ci sia un dato condiviso implicitamente richiede e l'
esistenza di un mutex

un modo per fare questo è un polling si procede se una variabile è true si aspetta se questa è false
reg13 06:54 code

questo codice non va bene perche è un attesa attiva che consuma cicli di cpu in tutti i casi

però questo problema dell aspetttare di essere risvegliato senza sfociare in attese attive è cosa gestita dal c++ utilizzando una
std::condition_variable

per funzionare richiede uno unique_lock .
condition variable ha diversi metodi
- wait(unique_lock) aspetta che qualcuno dica notify (wait fa unlock poi attende notify senza consumare risorse e poi cerca di
riprendersi il suo lock )
- notify_one() uno a caso lo faccio uscire dallo stato di attesa
- notify_all() tutti si svegliano ma lo scheduler del OS scheglie chi entra
reg13 12:0 5 code
non è possibile così facendo di stabilire un ordine su chi sarà il prossimo thread. esiste un metodo per farlo ma è oneroso

quando si usa questa techina si usa una condition variable e un mutex

delle volte è possibile a causa dello scheduling delle segnalazioni spurie possono permettere che un thread si svegli anche
se notify non è stata chiamata.
questo caso è gestito da un overload del metodo wait che prende in ingresso il mutex e una lambda (che ritorna vero falso)
che controlla se sia il caso di svegliarsi o no

reg13 esempio 26:06

esistono anche altre wait_for e wait_until che cessano l' attesa dopo un tempo fissato
std::cv_status::timeout
std::cv_status::no_timeout
per indicare tempo esaurito o sveglio per notifiy

le condition_variable possono ritardare la notifia alla morte del thread
notify_all_at_thread_exit()

----------------

Quando usi una std::condition_variable per sincronizzare thread, l'ordine tipico delle operazioni in un thread che notifica è:

1.Acquisire il lock su un mutex (tramite std::unique_lock o altro meccanismo di locking).
2.Modificare lo stato o la condizione che sarà controllata dai thread in attesa.
3.Chiamare notify_one() o notify_all() sulla condition_variable per risvegliare uno o più thread in attesa.
4.Rilasciare il lock, che può avvenire esplicitamente tramite unlock() sul std::unique_lock o implicitamente lasciando che il std::unique_lock venga distrutto (uscendo dal suo scope).

Perché non è necessariamente richiesto sbloccare prima di notificare?

!) Quando chiami notify_one() o notify_all(), i thread che sono stati notificati tenteranno di ri-acquisire il lock sul mutex prima di procedere. Se il lock non viene rilasciato prima della chiamata di notifica, questi thread semplicemente si metteranno in attesa del rilascio del lock prima di continuare. Non si "perde" la notifica; piuttosto, c'è un ritardo nell'effetto della notifica fino a quando il lock non viene rilasciato.
-)In alcuni casi, può essere desiderabile mantenere il lock durante la notifica per evitare "race conditions" dove un altro thread potrebbe intervenire e modificare lo stato prima che il thread notificato abbia la possibilità di agire sulla condizione aggiornata.

*/



// RISORSE PUBBLICHE
std::mutex mtx; // Mutex per proteggere l'accesso al buffer
std::condition_variable cv; // Variabile condizione per sincronizzare producer e consumer

int counter = 0;


void producer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx); // Acquisisce il lock sul mutex
        cout << "producer blocca il lock" << endl;
        counter += 1;

        cv.notify_one(); // non sblocca il lock
        lock.unlock();
        cout << "producer sblocca il lock" << endl;

        std::cout << "Producer ha inserito il dato: " << counter << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(8));
    }
}

void consumer() {
    while(true){
        std::unique_lock<std::mutex> lock(mtx);
        cout << "consumer blocca il lock" << endl;
        cv.wait(lock, []{ //wait sblocca il lock
            cout << "consumer sblocca il lock" << endl;
            if(counter>0){
                cout<<"consumer proceed"<<endl;
                return true;
            }else{
                cout<<"consumer stop"<<endl;
                return false;
            }
        }); // Verifica la condizione di consumo

        std::cout << "Consumer ha consumato il dato: " << counter << std::endl;
        counter--;
    }
}

int main() {
    std::thread t1(consumer); // il consumer resta in attesa nei prossimo 8 secondi finche un dato non è dispomnibile
    std::thread t2(producer);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    t1.join();
    t2.join();

    return 0;
}


