#include <iostream>
using namespace std;

// The class Counter is abstract
class Counter {
public:
    // Defined outside the class body (required for non-const static members)
    static int count_counters;

    // Constructor initialises value to 0 and increments count_counters
    Counter() {
        value = 0;
        count_counters += 1;
    }

    // Pure virtual: makes Counter abstract and forces derived classes to implement
    virtual void increment() = 0;
    virtual int read() const = 0;

    virtual ~Counter() { count_counters -= 1; }

protected:
    // Protected so derived classes can access value directly
    int value = 0;
};

// Out-of-class definition of the static member
int Counter::count_counters = 0;

// CounterWithOffset is a concrete derived class
class CounterWithOffset : public Counter {
public:
    // Initialiser list required because initial_value is const
    CounterWithOffset(int init) : initial_value(init) {}

    void increment() {
        value += 1;
    }

    // const because operator+ calls read() on a const reference
    int read() const {
        return initial_value + value;
    }

    // Merge two counters: new offset = sum of both read() values
    CounterWithOffset operator+(CounterWithOffset const& co) {
        CounterWithOffset merged(initial_value + value + co.read());
        return merged;
    }

    const int initial_value = 0;
};

// Uncomment the main to test if it compiles locally.
/*
int main(){
    CounterWithOffset c0(0);
    c0.increment();
    cout<<"The value of counter c0 is now: "<<c0.read()<<endl;
    return 0;
}
*/
