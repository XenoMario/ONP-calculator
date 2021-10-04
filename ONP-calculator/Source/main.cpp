#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include "Stack.inl"
#include "List.h"

// to do:
// Przerobic liste (Struktura osobno przedstawiona jako T)
// Operator przenoszacy
// Interface uzytkownika
// Klasa aplikacja 
// Google test (Github) - test jednostkowe

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

std::ostream& operator<<(std::ostream& os, const ONP_unit& un)
{
    if (un.nors == 1)
        os << un.number;
    else
        os << un.sign;

    return os;
}

int priority(char ch);
Queue<ONP_unit> convert(const std::string& st);
double solution(Queue<ONP_unit>&);

int main()
{

    std::vector<std::string> vec;
    vec.push_back("3+4*2/(1-5)^2");
    vec.push_back("7+1*(2*3+4/5)");
    vec.push_back("(1+2)*4+5-3" );
    vec.push_back("12+2*(3*4+10/5)" );

    Queue<ONP_unit> trial;

    for (size_t i = 0; i < vec.size(); i++)
    {
        trial = convert(vec[i]);
        //trial.Show();
        double result = solution(trial);
        cout << result << endl;
    }
    
    std::cout << "Goodbye" << std::endl;
    return 0;
}

int priority(char ch)
{
    if (ch == '(')
        return 0;
    else if (ch == '-' || ch == '+' || ch == ')')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if (ch == '^')
        return 3;
    else return 4;
}


Queue<ONP_unit> convert(const std::string& eq)
{
    Queue<ONP_unit> output;
    Stack<char> st;
    size_t s = eq.size();

    for (size_t i = 0; i < s; i++)
    {
        char ch;

        ch = eq[i];

        if (ch == ' ')
            continue;

        if (((int)ch >= 40 && (int)ch <= 47 && (int)ch != 46) || (int)ch == 94 || (int)ch == 37)
        {
            if (ch == ')')
            {
                char cc = st.Top();
                while (cc != '(')
                {
                    ONP_unit un = cc;
                    output.push_back(un);
                    st.pop();
                    cc = st.Top();
                }
                st.pop();
                continue;
            }

            if (!st.isempty())
            {
                if (ch == '(')
                {
                    st.push(ch);
                    continue;
                }

                char c = st.Top();
                while ((priority(ch) <= priority(c)))
                {
                    ONP_unit un = c;
                    output.push_back(st.Top());
                    st.pop();
                    if (!st.isempty())
                        c = st.Top();
                    else break;
                }

                st.push(ch);
            }
            else
            {
                st.push(ch);

            }
        }
        else
        {
            std::string temp;
            while ((int)ch >= 48 && (int)ch <= 57)
            {
                temp += ch;
                i++;
                ch = eq[i];
            }
            i--;
            ONP_unit u = std::stod(temp);
            output.push_back(u);
        }

        /*cout << "List: " << endl;
        output.Show();
        cout<<"Stack: "<<endl;
        Stack<char> dump;
        for (dump = st; !dump.isempty(); dump.pop())
            std::cout << dump.Top() << " ";
        cout<<endl;*/
    }

    while (!st.isempty())
    {
        output.push_back(st.Top());
        st.pop();
    }

    return output;
}

double solution(Queue<ONP_unit>& ls)
{
    Stack<double> stc;
    while (!ls.isempty())
    {
        ONP_unit unt = ls.pop_front();

        if (unt.nors==1)
        {
            stc.push(unt.number);
        }
        else
        {
            char mark = unt.sign;
            if (mark == '+')
            {
                double y = stc.Top();
                stc.pop();
                double x = stc.Top();
                stc.pop();

                stc.push(x + y);
            }
            else if (mark == '-')
            {
                double y = stc.Top();
                stc.pop();
                double x = stc.Top();
                stc.pop();

                stc.push(x - y);
            }
            else if (mark == '*')
            {
                double y = stc.Top();
                stc.pop();
                double x = stc.Top();
                stc.pop();

                stc.push(x * y);
            }
            else if (mark == '/')
            {
                double y = stc.Top();
                stc.pop();
                double x = stc.Top();
                stc.pop();

                if (y != 0)
                    stc.push(x / y);
                else
                {
                    std::cerr << "You can't divide by 0" << endl;
                    std::exit(EXIT_FAILURE);
                }
            }
            else if (mark == '^')
            {
                double y = stc.Top();
                stc.pop();
                double x = stc.Top();
                stc.pop();

                double z = 1;
                for (int j = 0; j < y; j++)
                    z *= x;

                stc.push(z);
            }
        }
    }

    return stc.Top();
}



// operator przenoszacy i konstruktor przenoszacy