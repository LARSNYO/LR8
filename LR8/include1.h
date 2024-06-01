#include <iostream>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>

class FractionNumber {
private:
    std::unique_ptr<int> numerator;
    std::unique_ptr<int> denominator;
    static int operationsCount;

public:
    // Constructor with parameters
    FractionNumber(int num, int denom)
        : numerator(std::make_unique<int>(num)), denominator(std::make_unique<int>(denom)) {}

    // Copy constructor
    FractionNumber(const FractionNumber& otherFraction)
        : numerator(std::make_unique<int>(*otherFraction.numerator)),
        denominator(std::make_unique<int>(*otherFraction.denominator)) {}

    // Default Constructor
    FractionNumber() : FractionNumber(5, 9) {}

    // Move constructor
    FractionNumber(FractionNumber&& otherFraction) noexcept
        : numerator(std::move(otherFraction.numerator)), denominator(std::move(otherFraction.denominator)) {}

    // Copy assignment
    FractionNumber& operator=(const FractionNumber& otherFraction) {
        if (this == &otherFraction)
            return *this;

        numerator = std::make_unique<int>(*otherFraction.numerator);
        denominator = std::make_unique<int>(*otherFraction.denominator);
        return *this;
    }

    // Move assignment
    FractionNumber& operator=(FractionNumber&& otherFraction) noexcept {
        if (this == &otherFraction)
            return *this;

        numerator = std::move(otherFraction.numerator);
        denominator = std::move(otherFraction.denominator);
        return *this;
    }

    // Destructor
    ~FractionNumber() = default;

    FractionNumber add(const FractionNumber& otherFraction) const {
        int resultNum = *numerator * (*otherFraction.denominator) + (*otherFraction.numerator) * *denominator;
        int resultDenom = *denominator * (*otherFraction.denominator);
        FractionNumber::operationsCount++;
        return FractionNumber(resultNum, resultDenom);
    }

    FractionNumber subtract(const FractionNumber& otherFraction) const {
        int resultNum = *numerator * (*otherFraction.denominator) - (*otherFraction.numerator) * *denominator;
        int resultDenom = *denominator * (*otherFraction.denominator);
        FractionNumber::operationsCount++;
        return FractionNumber(resultNum, resultDenom);
    }

    FractionNumber multiply(const FractionNumber& otherFraction) const {
        int resultNum = *numerator * (*otherFraction.numerator);
        int resultDenom = *denominator * (*otherFraction.denominator);
        FractionNumber::operationsCount++;
        return FractionNumber(resultNum, resultDenom);
    }

    FractionNumber divide(const FractionNumber& otherFraction) const {
        int resultNum = *numerator * (*otherFraction.denominator);
        int resultDenom = *denominator * (*otherFraction.numerator);
        FractionNumber::operationsCount++;
        return FractionNumber(resultNum, resultDenom);
    }

    void display() const {
        std::cout << *numerator << "/" << *denominator << std::endl;
    }

    static void displayCount() {
        std::cout << "Number of Fraction objects created: " << operationsCount << std::endl;
    }

    bool operator<(const FractionNumber& other) const {
        return (*numerator * (*other.denominator)) < (*denominator * (*other.numerator));
    }
};

int FractionNumber::operationsCount = 0;

template<typename T>
void measure_time(T func, const std::string& operation) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << operation << " took " << duration.count() << " seconds" << std::endl;
}

void test_queue_operations() {
    std::queue<FractionNumber> q;
    auto add_to_queue = [&]() {
        for (int i = 0; i < 100000; ++i) {
            q.push(FractionNumber(rand() % 100, rand() % 100 + 1));
        }
    };

    auto remove_from_queue = [&]() {
        while (!q.empty()) {
            q.pop();
        }
    };

    measure_time(add_to_queue, "Queue addition");
    measure_time(remove_from_queue, "Queue removal");
}

void test_map_operations() {
    std::unordered_map<int, FractionNumber> umap;
    auto add_to_map = [&]() {
        for (int i = 0; i < 100000; ++i) {
            umap[i] = FractionNumber(rand() % 100, rand() % 100 + 1);
        }
    };

    auto find_in_map = [&]() {
        for (int i = 0; i < 100000; ++i) {
            auto it = umap.find(i);
        }
    };

    auto remove_from_map = [&]() {
        for (int i = 0; i < 100000; ++i) {
            umap.erase(i);
        }
    };

    measure_time(add_to_map, "Map addition");
    measure_time(find_in_map, "Map search");
    measure_time(remove_from_map, "Map removal");
}


