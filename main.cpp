#include "RandomAccessIterator.hpp"

#include <vector>
#include "Vector.hpp"
int main()
{
    ft::RandomAccessIterator<int>  a;
   //ft::Vector<int>::const_iterator c_it, c_ob(a);
    //ft::Vector<int>::const_iterator  c_ob(a);
    //ft::RandomAccessIterator<const int>   b(a);
    //b == a ? std::cout <<  "haha\n": std::cout << "hello\n";
    *a++;
}