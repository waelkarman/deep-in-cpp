#include <iostream>

using namespace std;

/*
le funzioni friend devono esistere nel codice prima di essere definite friend
i campi privati non possono essere visti all esterno della classe stessa tuttavia è possibile dichiarare friend altre classi o funzioni per permettergli
di accedere ai campi private.
*/

class Base0;
void func(Base0 &a);


class Base0 {
    friend class Base1;
    friend void func(Base0&);
private:
    int privateData;
public:
    Base0() : privateData(42) {}
};

void func(Base0 &a){a.privateData = 250;}

class Base1 {
public:
    void readPrivate(const Base0& a) {
        std::cout << "Dato privato di A: " << a.privateData << std::endl;
    }
};

int main() {
    Base0 a;
    func(a);
    Base1 b;
    b.readPrivate(a);
    return 0;
}


