#include <iostream>
using namespace std;

//interface with basic stuff
class BasicInterface
{
    public:
    virtual void doTheBasic() = 0;
};

//implementation of the basic interface
class BasicImplementation : public BasicInterface
{
    public:
    void doTheBasic(){ std::cout << "dit it" << endl; }
}

//interface that do the the basic and also something advanced
class AdvancedInterface : virtual public BasicInterface
{
    public:
    virtual void doSomethingAdvanced() = 0;
}

class AdvancedImplementation: virtual public AdvancedInterface, public BasicImplementation
{
    public:
    void doSomethingAdvanced(){
        std::cout << "doing something advanced...";
        doTheBasic();
    }
}



int main(){
    AdvancedImplementation advancedImplementation;
    advancedImplementation.doSomethingAdvanced();
}
