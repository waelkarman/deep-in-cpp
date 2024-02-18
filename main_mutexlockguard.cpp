#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <vector>

using namespace std;
/*
in alcuni casi la necessità non è aspettare la disponibilità di un dato piuttosto quella di essere sicuro che nessun altro stia facendo
una certa cosa quindi non la presenza di qualcosa ma l' assenza !!

in questo caso di usano i mutex che permettono di avere accesso controllato ad una frazione di codice mutual exclusion
esempio si sta usando una linked list bisogna rompere i puntatori aggiungere qualcosa e poi ricollegarli se qualcun altro
accede anche se solo in lettura potrebbero trovare dati inconsistenti
allora chi deve fare operazioni di questo tipo su linked list assume il lock e poi rilascia il lock per consentire ad altri di proseguire

tutti devono usare lo stesso mutex creato per lo scopo dal programmatore
le operazioni di lock e unlock includono dei full memory fence che gestiscono i problemi di sincronizzazione fra thread.

la chiamata di unlock è sempre a carico del programmatore anche se il codice si ferma per un eccezione bisogna prevedere tutto

il mutex non ha ancuna corrispondenza con quanto protegge è tutto a carico del programmatore e quindi va documentata bene
il mutex serve in lettura e scrittura perche se no potrei leggere scritture parziali che sono fatte al contempo

se chiamo due volte lock() attendo per sempre perche davanti ad un lock non rilasciato si attende che qualcuno lo rilasci ma se a doverlo
rilasciare
sono io che sono bloccato nell attesa questo non avverrà mai -> deadlock

esiste anche std::recursive_mutex per gestire questa cosa ma alla chiamata di due lock servono 2 unlock
esiste anche un metodo try_lock che ritorna un booleano evitando di rimanere bloccati nell attesa di un mutex

è molto raro usare lock su un mutex direttamnete, in genere dal mutex si crea un oggetto std::lock_guard<lockable> prende un mutex in ingresso
il lock_guard è un oggetto che ha un lock nel costruttore e un unlock nel distruttore nel caso un eccezione avvenga nel blocco loccato la
contrazione dello stack fa sbloccare il mutex. se si costruisce questo oggetto lock_guard in un metodo si assicura che quando la graffa del
metodo sarà chiusa il lock sarà rilasciato quindi paradigma RAII reg12 1:23:16
se definisco un mutex dentro una classe per quell oggetto userò sempre lo stesso mutex anche se passo l oggetto a piu thread
*/


// Thread Safe class
class prod_cons{
    std::mutex mtx;
    int valore = 0;
public:


    void increase(int n){
        std::lock_guard<std::mutex> guard(mtx);
        valore+=n;
        cout << "Valore aumentato: " << valore << endl;
    }

    void decrease(int n){
        std::lock_guard<std::mutex> guard(mtx);
        valore-=n;
        cout << "Valore diminuito: " << valore << endl;
    }
};


void incr(prod_cons& p){
    for(int i = 0 ; i < 100 ; i++){
        p.increase(2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::this_thread::yield();
    }
}

void decr(prod_cons& p){
    for(int i = 0 ; i < 100 ; i++){
        p.decrease(2);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //std::this_thread::yield();
    }
}

int main() {
    prod_cons p;
    std::thread t0(incr,std::ref(p));
    std::thread t1(decr,std::ref(p));


    t0.join();
    t1.join();
    return 0;
}

