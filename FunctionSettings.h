//
// Created by ivan on 4/6/23.
//

#ifndef MATHME_FUNCTIONSETTINGS_H
#define MATHME_FUNCTIONSETTINGS_H


#include <string>

template <typename T>
class FunctionSettings {
public:
    std::string expression_string;
    std::string variable;
    T lower_limit;
    T higher_limit;
    T interval_length = 0.2;
    FunctionSettings(const std::string & function,
                     const std::string & variable,
                     T lower_limit,
                     T higher_limit,
                     T interval_length = 0.2);

    T GetY(T x);
    T GetMin(T a, T b);
};


#endif //MATHME_FUNCTIONSETTINGS_H
