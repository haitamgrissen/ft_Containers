#pragma once


#include "Iterator.hpp"
#include <iostream>


namespace ft
{
    template <class T>
	class RandomAccessIterator : ft::iterator<std::random_access_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference			reference;





			/*
			=================================	Constructors =============================================================
			*/
			RandomAccessIterator(pointer ptr)						{ _pointer = ptr;   }
			RandomAccessIterator(const RandomAccessIterator& other)	{ _pointer = other._pointer;}
			RandomAccessIterator()									{ _pointer = nullptr;}
			~RandomAccessIterator()									{ }











			/*
			=================================	Arithmitics  =============================================================
			*/
			operator RandomAccessIterator<const value_type>() const             { return RandomAccessIterator<const value_type>(_pointer); }


			RandomAccessIterator& operator=(const RandomAccessIterator& other)  { _pointer = other.base(); return (*this);}
			RandomAccessIterator& operator+=(difference_type n)                 { _pointer += n; return (*this);}
			RandomAccessIterator& operator-=(difference_type n)                 { _pointer -= n; return (*this);}
	
			RandomAccessIterator& operator++()                                  { _pointer++; return (*this); }
			RandomAccessIterator operator++(int)
			{
				RandomAccessIterator tmp(*this);
				_pointer++;
				return (tmp);
			}
			RandomAccessIterator& operator--()                                  { _pointer--; return (*this); }
			RandomAccessIterator operator--(int)
			{
				RandomAccessIterator tmp(*this);
				_pointer--;
				return (tmp);
			}



 			difference_type operator-(RandomAccessIterator it) const									{ return (this->_pointer - it.base()); }
            RandomAccessIterator operator+(difference_type n) const										{ RandomAccessIterator it(this->_pointer + n); return (it);}
            RandomAccessIterator operator-(difference_type n) const										{ RandomAccessIterator it(this->_pointer - n); return (it);}
            friend RandomAccessIterator operator+(difference_type n, const RandomAccessIterator& input)	{ RandomAccessIterator it(input); return (it += n); }







			// /*
			// =================================	Access  =============================================================
			// */

			reference operator[](difference_type n) const                       { return (_pointer[n]); }
			reference operator*()                                               { return (*_pointer); }
			pointer operator->()                                                { return (_pointer);}








			// /*
			// =================================	Comparision  =============================================================
			// */
			// bool operator== (const RandomAccessIterator<T>&  comp)				{ return (_pointer == comp.base());}
			// bool operator!= (const RandomAccessIterator<T>&  comp)				{ return (_pointer != comp.base());}
			// bool operator<  (const RandomAccessIterator<T>&  comp)				{ return (_pointer <  comp.base());}
			// bool operator<=  (const RandomAccessIterator<T>& comp)				{ return (_pointer <= comp.base());}
			// bool operator>  (const RandomAccessIterator<T>&  comp)				{ return (_pointer >  comp.base());}
			// bool operator>=  (const RandomAccessIterator<T>& comp)				{ return (_pointer >= comp.base());}



			// /*
			// =================================	Getter and Setter =============================================================
			// */
			pointer	base() const 										{ return this->_pointer;}
			//void	set_pointer(pointer ptr) const 								{ this->_pointer = ptr;}
		private :
			pointer _pointer;
	};


			// /*
			// =================================	Comparision  =============================================================
			// */std::cout <<  "haha\n";

			template <class T>
			bool operator== (const RandomAccessIterator<T>&  rhs, const RandomAccessIterator<T>&  lhs)				{ return (rhs.base() == lhs.base());}

			template <class T>
			bool operator!= (const RandomAccessIterator<T>&  rhs, const RandomAccessIterator<T>&  lhs)				{ return (rhs.base() != lhs.base());}
			
			template <class T>
			bool operator<  (const RandomAccessIterator<T>&  rhs, const RandomAccessIterator<T>&  lhs)				{ return (rhs.base() <  lhs.base());}
			
			template <class T>
			bool operator<=  (const RandomAccessIterator<T>& rhs, const RandomAccessIterator<T>& lhs)				{ return (rhs.base() <= lhs.base());}
			
			template <class T>
			bool operator>  (const RandomAccessIterator<T>&  rhs, const RandomAccessIterator<T>&  lhs)				{ return (rhs.base() >  lhs.base());}
			
			template <class T>
			bool operator>=  (const RandomAccessIterator<T>&  rhs, const RandomAccessIterator<T>&  lhs)				{ return (rhs.base() >= lhs.base());}
	


	




}