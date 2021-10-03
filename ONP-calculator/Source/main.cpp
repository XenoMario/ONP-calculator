#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include "Stack.inl"

int priority(char ch);
List convert(const std::string& st);
double solution(List&);

int main()
{
    std::vector<std::string> vec(4);

    vec[0] = { "3+4*2/(1-5)^2" };
    vec[1] = { "7+1*(2*3+4/5)" };
    vec[2] = { "(1+2)*4+5-3" };
    vec[3] = { "12+2*(3*4+10/5)" };

    List trial;

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

List convert(const std::string& eq)
{
    List output;
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
                    output.push_back(cc);
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
            double num = std::stod(temp);
            output.push_back(num);
        }

        /*cout<<"List: "<<endl;
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

double solution(List& ls)
{
    Stack<double> stc;
    while (!ls.isempty())
    {
        if (ls.first_is_number())
        {
            double num = ls.pop_front<double>();
            stc.push(num);
        }
        else
        {
            char mark = ls.pop_front<char>();
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

