//
// Created by ivan on 4/6/23.
//

#include <iostream>
#include <cmath>
#include <complex>
#include "FunctionSettings.h"
#include "exprtk.hpp"


template<typename T>
FunctionSettings<T>::FunctionSettings(const std::string& function,
                                      const std::string& variable,
                                      T lower_limit,
                                      T higher_limit,
                                      T interval_length) {
    this->expression_string = function;
    this->variable = variable;

    this->lower_limit = std::min(lower_limit, higher_limit);
    this->higher_limit = std::max(lower_limit, higher_limit);
    this->interval_length = interval_length;
}

template<typename T>
T FunctionSettings<T>::GetY(T x) {
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>   expression_t;
    typedef exprtk::parser<T>       parser_t;

    symbol_table_t symbol_table;
    symbol_table.add_variable(this->variable,x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(this->expression_string,expression);

    return expression.value();
}

template<typename T>
T FunctionSettings<T>::GetMin(T a, T b) {
    double gr = (std::sqrt(5) + 1) / 2;

    T x1 = b - (b - a) / gr;
    T x2 = a + (b - a) / gr;

    while (std::abs(b - a) > this->interval_length) {
        T fx1 = this->GetY(x1);
        T fx2 = this->GetY(x2);

        if (std::isnan(fx1) && std::isnan(fx2))
            throw std::invalid_argument("Limits are illegal");

        if (this->GetY(x1) < this->GetY(x2)){
            b = x2;
        }
        else {
            a = x1;
        }

        // For avoid loss of precision (may lead to incorrect results or infinite loop)
        x1 = b - (b - a) / gr;
        x2 = a + (b - a) / gr;
    }

    return (b + a) / 2;
}
