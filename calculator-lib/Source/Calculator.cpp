#include "Calculator.h"

#include <string>
#include <iomanip>
#include <vector>
#include <cmath>

//inline void eatline() { while (std::cin.get() != '\n') continue; }

/*bool Calculator::check() const
{

	size_t s = expression.size();

	if (((int)expression[0]<48 || (int)expression[0]>57) && ((int)expression[0] != 40 && (int)expression[0] != 41))
	{
		cout << "First sign must be a number" << endl;
		return false;
	}
	else if (((int)expression[s - 1] < 48 || (int)expression[s - 1]>57) && ((int)expression[s - 1] != 40 && (int)expression[s - 1] != 41))
	{
		cout << "Last sign must be a number" << endl;
		return false;
	}

	std::vector<char> marks;
	for (char i = 48; i <= 57; i++)
		marks.push_back(i);

	marks.push_back('+');
	marks.push_back('-');
	marks.push_back('*');
	marks.push_back('/');
	marks.push_back('^');
	marks.push_back('(');
	marks.push_back(')');

	for(size_t i=0; i<s; i++)
	if (std::find(marks.begin(), marks.end(), expression[i]) == marks.end())
	{
		cout << "Wrong arguments provided" << endl;
		return false;
	}

	return true;
}*/

int Calculator::priority(const char& ch)
{
	if (ch == '(')
		return 0;
	else if (ch == '-' || ch == '+' || ch == ')')
		return 1;
	else if (ch == '*' || ch == '/' || ch == '%')
		return 2;
	else if (ch == '^' || ch == 'p' || ch == 's' || ch == 'c' || ch == 't' || ch == 'g')
		return 3;
	else return 4;
}

/*void Calculator::take()
{
    cout << "Please enter expression" << endl;
    std::getline(std::cin, expression);
    //check();
}*/

/*void Application::show_interface()
{
	std::string expression;
	cout << "Please enter expression" << endl;
	std::getline(std::cin, expression);

    Queue<ONP_unit> unt;
    double result;

	while (!check(expression))
	{
		cout << "Please enter new expression" << endl;
		std::getline(std::cin, expression);
	}

	for (;;)
	{
		cout << "Your expression: " << expression << endl;
		cout << "---------------" << endl;

        unt = convert(expression);
        result = solution(unt);
        cout << "Solution: " << result << endl;
        cout << endl;
        cout << "Please enter new expression (put 0 to quit)" << endl;
		std::getline(std::cin, expression);

		while (!check(expression))
		{
			cout << "Please enter new expression" << endl;
			std::getline(std::cin, expression);
		}

		if (expression == "0")
		{
			cout << "Goodbye" << endl;
			std::exit(0);
		}
	}
}
*/

//((int)ch >= 40 && (int)ch <= 47 && (int)ch != 46) || (int)ch == 94 || (int)ch == 37

Queue<ONP_unit> Calculator::convert(const std::string& eq)
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

        if ((int)ch>=48 && (int)ch<=57)
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
        else
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

            if (ch == 's' || ch == 'c' || ch == 't')
            {
                std::string temp;
                
                while (ch != '(')
                {
                    temp += ch;
                    i++;
                    ch = eq[i];
                }
                i--;

                if (temp == "sin")
                    st.push('s');
                else if (temp == "cos")
                    st.push('c');
                else if (temp == "sqrt")
                    st.push('p');
                else if (temp == "tg")
                    st.push('t');
                else if (temp == "ctg")
                    st.push('g');

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

        cout << "List: " << endl;
        output.Show();
        cout<<"Stack: "<<endl;
        Stack<char> dump;
        for (dump = st; !dump.isempty(); dump.pop())
            std::cout << dump.Top() << " ";
        cout<<endl;
    }

    while (!st.isempty())
    {
        output.push_back(st.Top());
        st.pop();
    }

    return output;
}

double Calculator::solution(const std::string& str)
{
    Queue<ONP_unit> ls = convert(str);
    Stack<double> stc;
    while (!ls.isempty())
    {
        ONP_unit unt = ls.pop_front();

        if (unt.nors == 1)
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
            else if (mark == 's')
            {
                double x = stc.Top();
                stc.pop();

                stc.push(sin(x));
            }
            else if (mark == 'c')
            {
                double x = stc.Top();
                stc.pop();

                stc.push(cos(x));
            }
            else if (mark == 'p')
            {
                double x = stc.Top();
                stc.pop();

                stc.push(sqrt(x));
            }
            else if (mark == 't')
            {
                double x = stc.Top();
                stc.pop();

                stc.push(tan(x));
            }
            else if (mark == 's')
            {
                double x = stc.Top();
                stc.pop();

                stc.push(1/tan(x));
            }
        }
    }

    return stc.Top();
}

std::ostream& operator<<(std::ostream& os, const ONP_unit& un)
{
    if (un.nors == 1)
        os << un.number;
    else
        os << un.sign;

    return os;
}