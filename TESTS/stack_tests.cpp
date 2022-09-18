#include<iostream>
#include "../ft_containers.hpp" 
#include <map>
#include <stack>

#include <random>
#include <vector>

int main()
{
    {
        std::vector<int>	vec(100, 2);
        std::vector<int>	vec1(100, 2);
        ft::Vector<int>	ft_vec(100, 2);
        ft::Vector<int>	ft_vec1(100, 2);


        ft::Stack<int, ft::Vector<int> > mystack1(ft_vec);
        ft::Stack<int, ft::Vector<int> > mystack(ft_vec1);
        std::stack<int, std::vector<int> > stack1(vec);
        std::stack<int, std::vector<int> > stack(vec1);

        std::cout << "First element is " << *(mystack1.base().begin()) << std::endl;
        std::cout << "ft_stack size is " << mystack1.size() << std::endl;
        std::cout << "stack size is " << mystack.size() << std::endl;
        std::cout << std::endl << std::endl;
    }
    {
        std::stack<int> stack;
        ft::Stack<int> ft_stack;
        stack.push(21);
        stack.push(22);
        stack.push(24);
        stack.push(25);
        
        ft_stack.push(21);
        ft_stack.push(22);
        ft_stack.push(24);
        ft_stack.push(25);

        while (!stack.empty() && !ft_stack.empty())
        {
            std::cout << "Stack : " << stack.top() << std::endl;;
            stack.pop();

            std::cout << "Ft_Stack : " << ft_stack.top() << std::endl;;
            ft_stack.pop();
        }

    }


}