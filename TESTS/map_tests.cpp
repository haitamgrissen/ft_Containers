#include<iostream>
#include "../ft_containers.hpp"

#include <map>
#include <random>
#include <vector>

int main()
{
    {
        std::map<int, int> m;
        ft::Map<int, int> ft_m;

        for(size_t i=0; i < 5;i++)
        {
            m.insert(std::make_pair(i, i+10));
            ft_m.insert(ft::make_pair(i, i+10));
        }
        std::map<int, int>::iterator m_it=m.begin();
        ft::Map<int, int>::iterator ft_mit = ft_m.begin();

        for(size_t i=0; i < 5;i++)
        {
            std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << std::endl;
            std::cout << "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;
            std::cout << std::endl;
            m_it++;
            ft_mit++;
        }

        std::map<int, int>::iterator m_it2=m.find(2);
        ft::Map<int, int>::iterator ft_mit2 = ft_m.find(2);

        std::cout << "Element found : " << std::endl << std::endl; 
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second << std::endl;
        m.erase(m_it2);
        ft_m.erase(ft_mit2);

        m_it2=m.find(1);
        ft_mit2 = ft_m.find(1);
        m_it2++;
        ft_mit2++;

        std::cout << std::endl << "Checking if Elements are erased " << std::endl << std::endl;
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second << std::endl; 
        std::cout << std::endl;      
    }

    {
        std::map<int, int> m;
        ft::Map<int, int> ft_m;

        m.insert(std::make_pair(0, 10));
        ft_m.insert(ft::make_pair(0, 10));

        m.insert(std::make_pair(0, 21));
        ft_m.insert(ft::make_pair(0, 21));

        std::map<int, int>::iterator m_it=m.begin();
        ft::Map<int, int>::iterator ft_mit = ft_m.begin();

        std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << std::endl;
        std::cout << "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;  
         std::cout << std::endl;      
    }

    {
        std::map<int, int> m;
        ft::Map<int, int> ft_m;

        for(size_t i=0; i < 5;i++)
        {
            m.insert(std::make_pair(i, i+10));
            ft_m.insert(ft::make_pair(i, i+10));
        }
        std::map<int, int>::iterator m_it=m.find(1);
        ft::Map<int, int>::iterator ft_mit = ft_m.find(1);

        std::map<int, int>::iterator m_it2=m.find(3);
        ft::Map<int, int>::iterator ft_mit2 = ft_m.find(3);

        m.erase(m_it, m_it2);
        ft_m.erase(ft_mit, ft_mit2);

        std::cout << std::endl << "ERASING ALL ELEMENTS " << std::endl << std::endl;
        m.clear();
        ft_m.clear();

        std::cout << "M    : Size: " << m.size()   << std::endl;
        std::cout << "FT_M : Size: " << ft_m.size()  << std::endl;
    }

}