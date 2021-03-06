#pragma once

#include "Queue.inl"
#include "Stack.inl"

struct ONP_unit;

// stworzyc jedna metode publiczba przyjmujaca string i zwracajaca double a reszta do private

class Calculator
{
public:

    double solution(const std::string& str);

private:

    void take();
    bool check() const;

    int priority(const char& ch);
    Queue<ONP_unit> convert(const std::string& st);
};

// Zapytac czy struktura jest w dobrym miejscu 

struct ONP_unit
{
    double number;
    char sign;
    bool nors;

    ONP_unit() = default;

    ONP_unit(const char& ch)
    {
        number = 0;
        sign = ch;
        nors = 0;
    }

    ONP_unit(const double& num)
    {
        number = num;
        sign = '.';
        nors = 1;
    }

    friend std::ostream& operator<<(std::ostream& os, const ONP_unit& un);

    template<typename T>
    ONP_unit& operator=(const T& x)
    {
        if (typeid(x) == typeid(char))
        {
            sign = x;
            number = 0;
            nors = 0;
        }
        else
        {
            sign = '.';
            number = x;
            nors = 1;
        }

        return *this;
    }
};