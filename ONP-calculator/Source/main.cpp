#include "Stack.inl"
#include <iostream>
#include <vector>
#include <stack>
#include <string>

int priority(char ch);

std::string convert(std::string& s);

double solve(std::string& str);

int main()
{
    Stack<int> stos;

    stos.push(1);
    stos.push(2);
    stos.push(3);
    stos.push(4);
    stos.push(5);

    /*using std::cout;
    using std::endl;

    std::vector<std::string> vec(4);

    vec[0] = { "3+4*2/(1-5)^2" };
    vec[1] = { "7+1*(2*3+4/5)" };
    vec[2] = { "(1+2)*4+5-3" };
    vec[3] = { "12+2*(3*4+10/5)" };

    std::string trial;

    for (size_t i = 0; i < vec.size(); i++)
    {
        trial = convert(vec[i]);
        double result = solve(trial);
        cout << result << endl;
    }

    cout << "Goodbye" << endl;*/
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

std::string convert(std::string& str)
{
    std::string eq = str;
    std::string output; // Kolejka string / struktura(char,double)
    std::stack<char> st;
    std::cout << "Enter expression" << std::endl;
    //std::cin>>eq;
    size_t s = eq.size();

    for (size_t i = 0; i < s; i++)
    {
        char ch;

        ch = eq[i];

        if (ch == ' ')
            continue;

        if (((int)ch >= 40 && (int)ch <= 47 && (int)ch != 46) || (int)ch == 94 || (int)ch == 37) // Zmiana na znaki
        {
            if (ch == ')')
            {
                char cc = st.top();
                while (cc != '(')
                {
                    output += cc;
                    output += ';';
                    st.pop();
                    cc = st.top();
                }
                st.pop();
                continue;
            }

            if (!st.empty())
            {
                if (ch == '(')
                {
                    st.push(ch);
                    continue;
                }

                char c = st.top();
                while ((priority(ch) <= priority(c)))
                {
                    output += st.top();
                    output += ';';
                    st.pop();
                    if (!st.empty())
                        c = st.top();
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
            int t = i;
            while ((int)ch >= 48 && (int)ch <= 57)
            {
                output += ch;
                t++;
                ch = eq[t];
            }
            t--;
            i = t;
            output += ';';
        }

        /*cout<<endl;
        for(size_t j=0; j<output.size(); j++)
            cout<<output[j]<<" ";
        cout<<endl;

        for (std::stack<char> dump = st; !dump.empty(); dump.pop())
            std::cout << dump.top() << " ";
        cout<<endl;*/
    }

    while (!st.empty())
    {
        output += st.top();
        if (st.size() > 1) output += ';';
        st.pop();
    }

    /*cout<<endl;
    for(size_t i=0; i<output.size(); i++)
        cout<<output[i]<<" ";
    cout<<endl;*/

    return output;
}

double solve(std::string& str)
{
    std::stack<double> stc;

    size_t length = str.length();

    for (size_t i = 0; i < length; i++)
    {
        if ((int)str[i] >= 48 && (int)str[i] <= 57)
        {
            std::string temp;

            while (str[i] != ';')
            {
                temp += str[i];
                i++;
            }

            stc.push(std::stod(temp));
        }
        else
        {
            if (str[i] == '+')
            {
                double y = stc.top();
                stc.pop();
                double x = stc.top();
                stc.pop();

                stc.push(x + y);
            }
            else if (str[i] == '-')
            {
                double y = stc.top();
                stc.pop();
                double x = stc.top();
                stc.pop();

                stc.push(x - y);
            }
            else if (str[i] == '*')
            {
                double y = stc.top();
                stc.pop();
                double x = stc.top();
                stc.pop();

                stc.push(x * y);
            }
            else if (str[i] == '/')
            {
                double y = stc.top();
                stc.pop();
                double x = stc.top();
                stc.pop();

                stc.push(x / y);
            }
            else if (str[i] == '^')
            {
                double y = stc.top();
                stc.pop();
                double x = stc.top();
                stc.pop();

                double z = 1;
                for (int j = 0; j < y; j++)
                    z *= x;

                stc.push(z);
            }
            i++;
        }

        /*std::cout<<std::endl;
        for (std::stack<double> dump = stc; !dump.empty(); dump.pop())
            std::cout << dump.top() << " ";
        std::cout<<std::endl;*/
    }

    return stc.top();
}
