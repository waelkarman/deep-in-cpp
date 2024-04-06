#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
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

// Un contatore atomico condiviso tra i thread
std::atomic<int> counter(0);

void incrementCounter() {
    for (int i = 0; i < 100; ++i) {
        // Incrementa il contatore atomicamente
        int original_value = counter.fetch_add(1);
        cout << "This print is not sinchronized: "<< original_value << endl;
    }
}

int main() {
    const int numThreads = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(incrementCounter);
    }

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "Counter   : " << counter.load() << std::endl;
    return 0;
}
