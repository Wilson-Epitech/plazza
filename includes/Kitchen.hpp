#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Pizza.hpp"  // Assuming this includes the declaration of the Pizza class

class Kitchen {
public:
    Kitchen(int numCooks, int restockTime, int multiplier);
    Kitchen(Kitchen&& other) noexcept;
    ~Kitchen();

    void receiveOrder(const Pizza& pizza);
    void cook();
    void restock();
    void completeOrder();  // If needed or remove if redundant
    int getFreeCooks() const { return freeCooks_; }

private:
    int numCooks_;
    int freeCooks_;
    int restockTime_;
    int multiplier_;
    bool stop_ = false;
    std::vector<std::thread> cooks_;
    std::vector<Pizza> orders_;
    std::mutex order_mutex;
    std::condition_variable order_cond_;
};

#endif // KITCHEN_HPP
