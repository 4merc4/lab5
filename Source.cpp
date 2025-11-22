#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <syncstream>

using namespace std;



void compute(const string& name, int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
    osyncstream(cout) << name << "\n";
}


void quick(const string& name) {
    compute(name, 1);
}


void slow(const string& name) {
    compute(name, 7);
}



void work() {
    auto start = chrono::steady_clock::now();

    
    auto futureA = async(std::launch::async, [] {
        quick("A1");
        slow("A2");
        quick("A3");
        });

    
    auto futureB = async(std::launch::async, [] {
        quick("B1");
        slow("B2");
        quick("B3");
        });

    
    futureA.get();
    futureB.get();

    
    quick("C");

    auto end = chrono::steady_clock::now();
    double seconds =
        chrono::duration_cast<chrono::seconds>(end - start).count();

    osyncstream(cout) << "Work is done! Total time = "
        << seconds << " seconds.\n";
}


int main() {
    work();
    return 0;
}

