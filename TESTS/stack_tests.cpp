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
        ft::Vector<int>	ft_vec(100, 2);




        ft::Stack<int, ft::Vector<int> > ft_stack(ft_vec);
        std::stack<int, std::vector<int> > stack(vec);

        std::cout << "FT_S TOP  : " << (ft_stack.top()) << std::endl;
        std::cout << "S TOP     : " << (ft_stack.top()) << std::endl;
        std::cout << std::endl;
        std::cout << "ft_S size : " << ft_stack.size() << std::endl;
        std::cout << "S size    : " << stack.size() << std::endl;
        std::cout << std::endl << std::endl;
    }
    {
        std::stack<int> stack;
        ft::Stack<int> ft_stack;

        for (size_t i = 0; i < 10; i++)
        {
           stack.push(i);
           ft_stack.push(i);
        }
        ft::Stack<int> ft_stack2;

        if (ft_stack2 == ft_stack)
            std::cout << "stacks are equal" << std::endl;
        else
            std::cout << "stacks are not equal" << std::endl;
std::cout << std::endl;

        for ( ; !stack.empty() && !ft_stack.empty();  stack.pop(), ft_stack.pop())
            std::cout << "Stack : " << stack.top() <<  " ||| "<< "Ft_Stack : " << ft_stack.top() << std::endl;;

std::cout << std::endl;
        if (ft_stack2 == ft_stack)
            std::cout << "stacks are equal" << std::endl;
        else
            std::cout << "stacks are not equal" << std::endl;
    }

    //system("leaks stack.out");
}