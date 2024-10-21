//
// Created by иван гаршин on 10/21/24.
//

#ifndef MAIN_TRANSFORMATIONS_H
#define MAIN_TRANSFORMATIONS_H

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

// Функция возвращает приоритет оператора.
// Чем выше значение, тем выше приоритет.
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  // Низший приоритет
    if (op == '*' || op == '/') return 2;  // Средний приоритет
    return 0;
}

// Функция применяет оператор к двум числам и возвращает результат.
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw std::invalid_argument("division by zero");
            }
            return a / b;
    }
    return 0;
}

// Функция для проверки синтаксиса выражения.
// Возвращает true, если выражение корректное, и false в случае ошибки.
bool isValidExpression(const std::string& expression) {
    int openBrackets = 0;
    bool lastWasOperator = true;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (c == ' ') continue; // Пропуск пробелов

        if (isdigit(c)) {
            lastWasOperator = false;  // После числа оператор обязателен
        } else if (c == '(') {
            openBrackets++;  // Увеличиваем количество открывающих скобок
            lastWasOperator = true;  // После скобки не может идти число или еще одна скобка
        } else if (c == ')') {
            openBrackets--;  // Уменьшаем количество открывающих скобок
            if (openBrackets < 0 || lastWasOperator) {
                return false;  // Неправильное закрытие скобок или пустая скобка
            }
            lastWasOperator = false;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (lastWasOperator) {
                return false;  // Операторы не могут следовать друг за другом
            }
            lastWasOperator = true;  // После оператора должно идти число или скобка
        } else {
            return false;  // Неподдерживаемый символ
        }
    }

    return openBrackets == 0 && !lastWasOperator;  // Проверка, что все скобки закрыты
}

// Основная функция для вычисления арифметического выражения.
int evaluate(std::string expression) {
    std::stack<int> values;   // Стек для чисел
    std::stack<char> ops;     // Стек для операторов

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') continue;  // Пропуск пробелов

        if (isdigit(expression[i])) {
            int value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            values.push(value);  // Помещаем число в стек
            i--;  // Возвращаемся на шаг назад, так как цикл ушел дальше
        } else if (expression[i] == '(') {
            ops.push(expression[i]);  // Открывающая скобка в стек операторов
        } else if (expression[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.pop();  // Убираем открывающую скобку
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.top();
                values.pop();

                int val1 = values.top();
                values.pop();

                char op = ops.top();
                ops.pop();

                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);  // Оператор в стек операторов
        }
    }

    while (!ops.empty()) {
        int val2 = values.top();
        values.pop();

        int val1 = values.top();
        values.pop();

        char op = ops.top();
        ops.pop();

        values.push(applyOp(val1, val2, op));
    }

    return values.top();  // Возвращаем результат
}

#endif //MAIN_TRANSFORMATIONS_H
