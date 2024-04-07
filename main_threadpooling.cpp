#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>
#include <atomic>

using namespace std;

/*
Il thread pooling è un pattern di progettazione utilizzato nella programmazione concorrente per gestire l'esecuzione di multiple task
 in modo efficiente, riutilizzando un numero limitato di thread. Invece di avviare un nuovo thread per ogni task, un pool di thread
mantiene un insieme di thread lavoratori che vengono riutilizzati per eseguire più task.

Come Funziona il Thread Pooling:
Inizializzazione: Al momento della creazione, il thread pool inizializza un certo numero di thread lavoratori, che rimangono in attesa
 di task da eseguire.

Assegnazione dei Task: Quando un compito viene sottomesso al pool, viene messo in una coda. Un thread disponibile nel pool preleva il
task dalla coda e inizia la sua esecuzione.

Esecuzione e Riutilizzo: Una volta completato il task, il thread non viene distrutto ma rimane nel pool, pronto per eseguire il
prossimo task.

Terminazione: I thread nel pool possono essere terminati quando il pool viene distrutto o in base a specifiche politiche di
terminazione, ad esempio dopo un periodo di inattività.

Vantaggi del Thread Pooling:
Riduzione dell'Overhead: La creazione e distruzione di thread può essere costosa in termini di tempo e risorse. Riutilizzando i
thread, il pooling riduce questo overhead.

Miglior Utilizzo delle Risorse: Limitando il numero di thread contemporanei, il thread pooling previene il sovraccarico del sistema
dovuto a un eccessivo numero di thread attivi.

Miglioramento delle Prestazioni: La gestione efficiente dei task e la riduzione dell'overhead possono portare a un miglioramento delle
prestazioni dell'applicazione.

Scalabilità: Il thread pooling permette di gestire meglio le risorse in scenari ad alta concorrenza, adattando l'applicazione a carichi
di lavoro variabili.

Implementazioni di Thread Pooling:
In C++, il thread pooling non è direttamente supportato dalla Standard Library. Tuttavia, è possibile implementare un proprio thread
pool utilizzando le primitive di concorrenza fornite da C++11 (come std::thread, std::mutex, std::condition_variable, ecc.) o utilizzare
 librerie di terze parti che offrono implementazioni di thread pool.
*/

/**
 * Thread pool draft
 * threads creation overhead still not managed
 *
*/

std::mutex queue_mutex;
std::atomic<int> i(0);
std::atomic<int> k(0);


unsigned long long fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

void th_lodable(vector<std::function<void()>> & tasks){
    std::function<void()> f;
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        if (tasks.empty()){
            return;
        }
        f = tasks.back();
        tasks.pop_back();
    }
    f();
    i--;
}

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << "Total available Cores: " << n << endl;

    vector<thread> workers;
    vector<std::function<void()>> tasks;


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(40, 46);

    for(int q=0; q<100; q++){
        int fib = distrib(gen);
        std::function<void()> task = [=](){
            cout << "execute task " << q << " on thread num: "<< k.fetch_add(1) << endl;
            fibonacci_recursive(fib);
        };

        tasks.push_back(std::move(task));
    }


    while(tasks.size()>0){
        if(i<n){
            workers.push_back(thread(th_lodable,std::ref(tasks)));
            i++;
        }
    }

    for(thread& w : workers){
        if(w.joinable()){
            w.join();
        }
    }

    return 0;
}
