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


        std::cout << "Inserting Element : " << std::endl << std::endl;
        for(size_t i=0; i < 5;i++)
        {
            m.insert(std::make_pair(i, i + 10));
            ft_m.insert(ft::make_pair(i, i + 10));
        }
        std::map<int, int>::iterator m_it=m.begin();
        ft::Map<int, int>::iterator ft_mit = ft_m.begin();

        for( size_t i = 0; i < 5; i++, m_it++, ft_mit++)
            std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << " ||| "<< "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;


        std::cout << std::endl;

        std::map<int, int>::iterator m_it2=m.find(2);
        ft::Map<int, int>::iterator ft_mit2 = ft_m.find(2);

        std::cout << "Element found and to be erased: " << std::endl << std::endl; 
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << " ||| " << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second <<std::endl;
        
        std::cout << std::endl;
        
        m.erase(m_it2);
        ft_m.erase(ft_mit2);

        m_it2=m.find(1);
        ft_mit2 = ft_m.find(1);
        
        m_it2++;
        ft_mit2++;

        std::cout << "Element to be erased: " << std::endl << std::endl; 
        std::cout << "M    : Key: " << m_it2->first << "| value: " << m_it2->second << " ||| " << "FT_M : Key: " << ft_mit2->first << "| value: " << ft_mit2->second <<std::endl;
        m.erase(m_it2);
        ft_m.erase(ft_mit2);

        std::cout << std::endl << "Checking if Elements are erased " << std::endl << std::endl;

        m_it = m.begin();
        ft_mit = ft_m.begin();
        for(; m_it != m.end(); m_it++, ft_mit++)
            std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << " ||| "<< "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;

        std::cout << std::endl;    


        std::cout << std::endl << "Lowest bound with 3 " << std::endl << std::endl;

        m_it = m.lower_bound(2);
        ft_mit = ft_m.lower_bound(2);
        std::cout << "M    : Key: " << m_it->first << "| value: " << m_it->second << " ||| "<< "FT_M : Key: " << ft_mit->first << "| value: " << ft_mit->second << std::endl;
        
        std::cout << std::endl << "ERASING ALL ELEMENTS " << std::endl << std::endl;
        m.clear();
        ft_m.clear();
        
        if (m.empty() && ft_m.empty())
            std::cout << "M    : Size: " << m.size()   << " ||| " << "FT_M : Size: " << ft_m.size()  << std::endl;
    }

    //system("leaks map.out");
}