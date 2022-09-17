#pragma once
//miscellaneous.hpp


# include <memory>
# include <cstddef>
# include <iostream>
# include <exception>
# include <functional>
# include <stddef.h>

#include <iterator>

namespace ft 
{


    //========================== Enable If            ===========================//
    //========================== ++++++++++++++++++++ ===========================//

    template <class T>
    struct is_integral { static const bool value = false;};
    template <> struct
    is_integral<bool> { static const bool value = true;};
    template <>
    struct is_integral<char> { static const bool value = true;};
    template <>
    struct is_integral<char16_t> { static const bool value = true;};
    template <>
    struct is_integral<char32_t> { static const bool value = true;};
    template <>
    struct is_integral<wchar_t> { static const bool value = true;};
    template <>
    struct is_integral<signed char> { static const bool value = true;};
    template <>
    struct is_integral<short int> { static const bool value = true;};
    template <>
    struct is_integral<int> { static const bool value = true;};
    template <>
    struct is_integral<long int> { static const bool value = true;};
    template <>
    struct is_integral<long long int> { static const bool value = true;};
    template <>
    struct is_integral<unsigned char> { static const bool value = true;};
    template <>
    struct is_integral<unsigned short int> { static const bool value = true;};
    template <>
    struct is_integral<unsigned int> { static const bool value = true;};
    template <>
    struct is_integral<unsigned long int> { static const bool value = true;};
    template <>
    struct is_integral<unsigned long long int> { static const bool value = true;};

    template<bool B, class T = void>
    struct enable_if
    {   };
  
    template<class T>
    struct enable_if<true, T> { typedef T type; };



    //========================== Relational Operators ===========================//
    //========================== ++++++++++++++++++++ ===========================//

    template <class InputIterator1, class InputIterator2>
 	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
 	{
		for(; first1 != last1 ; ++first1, ++first2)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
 			else if (*first1 < *first2)
				return true;
		}
 	  return (first2!=last2);
 	}

 	template <class InputIterator1, class InputIterator2, class Compare>
 	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
 	{
 	  for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
 		  if (comp(*first1, *first2)) return true;
 		  if (comp(*first2, *first1)) return false;
 	  }
 	  return ((first1 == last1) && (first2 != last2));
 	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		for (; first1!=last1;  ++first1, ++first2)
			if (!(*first1 == *first2))  
	    	  return false;
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1!=last1;  ++first1, ++first2)
			if (!pred(*first1,*first2)) 
	    	  return false;
		return true;
	}


    






	

	      //========================== Iterator Traits      ===========================//
    //========================== ++++++++++++++++++++ ===========================//

    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public :
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
	};


	template <class Iterator> 
	class iterator_traits
	{   
				public :     
		typedef typename Iterator::difference_type		difference_type;	
		typedef typename Iterator::value_type			value_type;			
		typedef typename Iterator::pointer				pointer;			
		typedef typename Iterator::reference			reference;			
		typedef typename Iterator::iterator_category	iterator_category; 	
	};

	template <class T>
  	class iterator_traits<T*>
  	{
		  		public :
  		typedef ptrdiff_t							difference_type;
  		typedef T									value_type;
  		typedef T*									pointer;
  		typedef T&									reference;
  		typedef std::random_access_iterator_tag		iterator_category;
  	};
	
	template <class T>
	class iterator_traits<const T*>
	{
				public :
		typedef ptrdiff_t							difference_type;
		typedef T									value_type;
		typedef const T*							pointer;
		typedef const T&							reference;
		typedef std::random_access_iterator_tag		iterator_category;
	};

}