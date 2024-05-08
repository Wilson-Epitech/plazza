#include "Kitchen.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
#include <mutex>

std::mutex print_mutex;

Kitchen::Kitchen(int numCooks, int restockTime, int multiplier)
    : numCooks_(numCooks), freeCooks_(numCooks), restockTime_(restockTime), multiplier_(multiplier) {
    for (int i = 0; i < numCooks_; ++i) {
        cooks_.emplace_back(&Kitchen::cook, this);
    }
}

Kitchen::Kitchen(Kitchen&& other) noexcept
    : numCooks_(other.numCooks_),
      freeCooks_(other.freeCooks_),
      restockTime_(other.restockTime_),
      multiplier_(other.multiplier_),
      stop_(other.stop_),
      cooks_(std::move(other.cooks_)) {
}


void synchronized_print(const std::string& message) {
    std::lock_guard<std::mutex> lock(print_mutex);
    std::cout << message << std::endl;
}

Kitchen::~Kitchen() {
    stop_ = true;
    order_cond_.notify_all();  // Notify all to stop blocking
    for (auto& cook : cooks_) {
        if (cook.joinable()) {
            cook.join();
        }
    }
}

void Kitchen::receiveOrder(const Pizza& pizza) {
    std::lock_guard<std::mutex> lock(order_mutex);
    if (freeCooks_ > 0) {
        orders_.push_back(pizza);
        --freeCooks_;
        synchronized_print("Order for " + std::to_string(pizza.getType()) + " size " + std::to_string(pizza.getSize()) + " added to kitchen.");
        order_cond_.notify_one();
    } else {
        synchronized_print("No free cooks available in this kitchen.");
    }
}

void Kitchen::cook() {
    std::ostringstream stream;

    std::unique_lock<std::mutex> lock(order_mutex);
    while (!stop_) {
        if (order_cond_.wait_for(lock, std::chrono::seconds(10), [this] { return !orders_.empty() || stop_; })) {
            if (!orders_.empty()) {
                auto pizza = std::move(orders_.back());
                orders_.pop_back();
                lock.unlock();

                synchronized_print(stream.str() + "Cooking " + std::to_string(pizza.getType()) + " size " + std::to_string(pizza.getSize()));
                std::this_thread::sleep_for(std::chrono::seconds(pizza.getCookTime()));

                lock.lock();
                ++freeCooks_;
                synchronized_print(stream.str() + "Order completed for " + std::to_string(pizza.getType()) + " size " + std::to_string(pizza.getSize()));
            }
        } else {
            synchronized_print(stream.str() + "No orders in 10 seconds, shutting down kitchen.");
            stop_ = true;
        }
    }
}

void Kitchen::restock() {
    std::this_thread::sleep_for(std::chrono::seconds(restockTime_));
    // Assume code here to increment stock of ingredients
    synchronized_print("Stock replenished.");
}

void Kitchen::completeOrder() {
    // Potentially redundant, consider removing or implementing functionality
}
