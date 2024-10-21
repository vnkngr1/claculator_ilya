#include <iostream>
#include "main_transformations.h"

int main() {
    std::string expression;
    std::getline(std::cin, expression);  // Чтение строки из ввода

    try {
        // Проверка, является ли выражение корректным арифметическим
        if (!isValidExpression(expression)) {
            std::cout << "syntax error" << std::endl;
        } else {
            // Попытка вычисления выражения
            std::cout << evaluate(expression) << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        // Обработка исключения для деления на ноль
        std::cout << "division by zero" << std::endl;
    }

    return 0;
}
