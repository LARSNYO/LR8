#include "include.h"

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(0)));

    // Тестирование операций с очередью
    test_queue_operations();

    // Тестирование операций с map
    test_map_operations();

    return 0;
}