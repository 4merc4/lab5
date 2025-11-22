#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <syncstream>

using namespace std;

// ===========================================================
// Симуляція обчислень
// ===========================================================

void compute(const string& name, int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
    osyncstream(cout) << name << "\n";
}

// Швидке
void quick(const string& name) {
    compute(name, 1);
}

// Повільне
void slow(const string& name) {
    compute(name, 7);
}

// ===========================================================
// Робоча схема
// ===========================================================

void work() {
    auto start = chrono::steady_clock::now();

    // Потік гілки A
    auto futureA = async(std::launch::async, [] {
        quick("A1");
        slow("A2");
        quick("A3");
        });

    // Потік гілки B
    auto futureB = async(std::launch::async, [] {
        quick("B1");
        slow("B2");
        quick("B3");
        });

    // Чекаємо завершення обох гілок
    futureA.get();
    futureB.get();

    // Тепер виконуємо C (залежить від A3 і B3)
    quick("C");

    auto end = chrono::steady_clock::now();
    double seconds =
        chrono::duration_cast<chrono::seconds>(end - start).count();

    osyncstream(cout) << "Work is done! Total time = "
        << seconds << " seconds.\n";
}

// ===========================================================
// Демонстрація
// ===========================================================

int main() {
    work();
    return 0;
}
