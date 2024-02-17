#include <future>
#include <iostream>
#include <thread>

using namespace std;

/*
 è possibile definire un blocco di codice che sarà usato solo una volta
std::once_flag flag; //questo flag puo tornare
1.nulla di eseguito (e fa partire la funzione)
2.esecuzione in corso
3.operzione terminata
se qualcun altro prova a chimare call once aspetta che l esecuzioni in corso termini e passa senza fare nulla
l'operazione viene fatta una volta o aspettano. in generale si usa quando si inizialissano risorse
*/
void initializeSharedResources() {
    // This code is executed only once
    std::cout << "Shared resources initialized." << std::endl;
}

std::once_flag flag;

void threadFunction() {
    std::call_once(flag, initializeSharedResources);
}

int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    t1.join();
    t2.join();
    return 0;
};
