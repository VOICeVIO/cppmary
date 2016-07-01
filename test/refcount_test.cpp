#include <iostream>
#include <vector>
#include <map>
#include "common.h"
using namespace std;

class A : public cppmary::ReferenceCounted {
public:
    A() {
        AddRef();
        std::cout << "construct in a " << std::endl;
    }
    ~A() {
        std::cout << "deconstruct in a " << std::endl;
    }
    virtual void quak() {
        std::cout << " quak in a" << std::endl;
        //doSomething();
    }
    void doSomething() {
        std::cout << "dosomethin in a" << std::endl;
    }
    void doAnother() {
        std::cout << "do another in a " << std::endl;
    }
};

class B : public  A {
public:
    B() {
        std::cout << "construct in b " << std::endl;
    }
    ~B() {
        std::cout << "deconstruct in b " << std::endl;
    }
    virtual void quak() {
        std::cout << "quak in b " << std::endl;
        doAnother();
    }
    void doSomething() {
        std::cout << "dosomethin in b" << std::endl;
    }

};

class C : public A {
public:
    C() {
        std::cout << "construct in c " << std::endl;
    }
    ~C() {
        ReleaseRef();
        std::cout << "deconstruct in c " << std::endl;
    }
    virtual void quak() {
        std::cout << "quak in c " << std::endl;
        doSomething();
    }
    void doSomething() {
        std::cout << "dosomethin in c" << std::endl;
    }
};


class Base {
public:
    Base(int a) : c(a) { }
    ~Base() { }
    virtual void quak() {
        std::cout << "in base " << c << std::endl;
    }
    virtual int process() {
        std::cout << "in base " << c + 1 << std::endl;
    }
protected:
    int c;
};

class Derive : public Base {
public:
    Derive(int a) : Base(a) {}
    ~Derive() { }
    virtual int process() {
        std::cout << "in derive " << c + 2 << std::endl;
    }
};


int main() {

    class Base* pb = new Derive(10);
    pb->quak();
    pb->process();


    A* cc = new C();
    cc->quak();
    std::cout << cc << std::endl;

    A* bb =  new B();
    bb->quak();
    bb->ReleaseRef();


    return 0;
}

