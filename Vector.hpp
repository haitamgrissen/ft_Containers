# pragma once


#include <memory>
#include <cstddef>
#include "Iterator.hpp"
#include "RandomAccessIterator.hpp"
#include "ReverseIterator.hpp"
#include "Enable_if.hpp"
#include "lexico_compare.hpp"
#include "Utilities.hpp"


namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public :
		typedef T                                               value_type;

		//allocator memebers
		typedef Alloc                                           allocator_type;
		typedef typename    allocator_type::reference           reference;
		typedef typename    allocator_type::const_reference     const_reference;
		typedef typename    allocator_type::pointer             pointer;
		typedef typename    allocator_type::const_pointer       const_pointer;
		//iterators members
		typedef ft::RandomAccessIterator<value_type>            iterator;
		typedef ft::RandomAccessIterator<const value_type>      const_iterator;
		typedef ft::reverse_iterator<iterator>                  reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;



		typedef  size_t                                         size_type;
		typedef  size_t											difference_type;





		/////////////
		/////////////Constructors Destructor

		/*
			empty container constructor (default constructor)
				Constructs an empty container, with no elements.
		*/
		explicit Vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc)
		{
			_array = nullptr;
			_size = 0;
			_capacity = 0;
			reAlloc(2);
		}
		/*
			fill constructor
				Constructs a container with n elements. Each element is a copy of val.
		*/
		explicit Vector (size_type n, const value_type& val = value_type(),
				 const allocator_type& alloc = allocator_type()): _alloc(alloc)
		{
			if (!n)
			return ;
			_array = _alloc.allocate(n);
			for (_size = 0; _size < n; _size++)
				_alloc.construct(&_array[_size], val);//_array[_size] = val;
			_size++;
			_capacity = n;
		}
		/*
			range constructor
				Constructs a container with as many elements as the range [first,last), 
				with each element constructed from its corresponding element in that range, 
				in the same order.
		*/
		template<class InputIterator>
        Vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) :  _array(nullptr), _size(0), _capacity(0)
        {
			// _alloc = alloc;
            // size_t i = 0;
            // for (InputIterator it = first; it != last; it++)
            //     i++;
            // _array = _alloc.allocate(i + 1);
            // _alloc.construct(_array);
            // for(size_t j = 0; i > j; j++)
            // {
            //     _size++;
            //     _array[j] = *first;
            //     first++;
            // }
            // _capacity = i;



			_alloc = alloc;
            difference_type diff = last - first;
			if (diff < 0)
				diff *= -1;
            _array = _alloc.allocate(diff);
            //_alloc.construct(_array);
            for(size_t i = 0; i < diff && first != last; i++, _size++, first++)
            {
                _alloc.construct(&_array[i], *first);
            }
            _capacity = diff;

			// (void)f;
			// difference_type n;
			// n = std::distance(first, last);
			// if (n < 0)
			// 	n = n * (-1);
			// _capacity = n;
			// _size = n;
			// if(n)
			// 	_data = _alloc.allocate(n);
			// for (size_type i = 0; i < _size && first != last ; i++, first++)
			// 	_alloc.construct(&_data[i], *first);
        }
		/*
			copy constructor
				Constructs a container with a copy of each of the elements in x, in the same order.
		*/
		Vector (const Vector& x)
		{
			*this = x;
		}
		/*
			Vector destructor
				This destroys all container elements, and deallocates all the storage capacity
				allocated by the Vector using its allocator.
		*/
		~Vector()
		{
			_alloc.deallocate(_array, _capacity);
		}

		/*
			Assign content
			Assigns new contents to the container,
			replacing its current contents, and modifying its size accordingly.
		*/
		Vector& operator= (const Vector& x)
		{
			reAlloc(x);
			return (*this);
		}

		///////Iterators:






		allocator_type			get_allocator() const { return (_alloc); }

		iterator				begin() 		{return (iterator(_array));}
		const_iterator			begin() const	{return (iterator(_array));}
		iterator				end()			{return (iterator(_array + _size));}
		const_iterator			end()  const	{return (iterator(_array + _size));}
		const_reverse_iterator	rbegin() const	{return (reverse_iterator(iterator(_array + _size)));}
		reverse_iterator		rbegin()		{return (reverse_iterator(end()));}
		const_reverse_iterator	rend()  const	{return (reverse_iterator(iterator(_array + _size)));}
		reverse_iterator		rend()			{return (reverse_iterator(begin()));}









		/**/

		///////////// Capacity
		//
		//
		//
		// 
		/*
		*/       
		//
		size_type		size() const 		{ return  _size; }
		size_type		max_size() const 	{ return _alloc.max_size();}
		size_type		capacity() const 		{ return  _capacity; }
		bool			empty() 				{ return ((_size == 0) ? true : false); }
		void			reserve (size_type n)	{ if (n > _capacity) reAlloc(n); }
		void			resize (size_type n, value_type val = value_type())
		{
				if (n > _capacity)
				{
					reserve(n);
					for (; _size < n ; _size++)
						_array[_size] = val;
				}
				else if (n > _size)
				{
					for (; _size < n ; _size++)
						_array[_size] = val;
				}   
				else
				{
					for (; _size > n; )
						_array[_size--].~value_type();
				}
		}


		///////////// Element access:
		//
		//
		//
		// 
		/*
		*/       
		//

		const_reference		operator[](size_t index) const 		{ return _array[index];}
		reference			operator[](size_t index) 			{ return _array[index];}
		reference			at (size_type n) 					{ if (n > _size) throw std::out_of_range("out of range"); else return _array[n];}
		const_reference		at (size_type n) const 				{ if (n > _size) throw std::out_of_range("out of range"); else return _array[n];}
		reference			front() 							{return _array[0];}
		const_reference		front() const 						{return _array[0];}
		reference			back() 								{return (_array[_size - 1]);}
		const_reference		back() const 						{return (_array[_size - 1]);}


		// Modifiers:
		template <class InputIterator>
  		void		assign (InputIterator first, InputIterator last) {first = last;}
		void		assign (size_type n, const value_type& val) { if (n > _capacity) reAlloc(n); for (_size = 0; _size < n; ) _array[_size++] = val;}
		void		push_back (const value_type& val)
		{
			if (_size >= _capacity)
				reAlloc(_capacity * 2);
			_array[_size] = val;
			_size++;
		}
		void		pop_back() { _size--; }//TODO:might need to destroy that elements
		iterator	insert (iterator position, const value_type& val)	{ position = NULL; std::cout << val; return NULL;}	
   		void		insert (iterator position, size_type n, const value_type& val){position = NULL; std::cout << val; n= 0;}
		template <class InputIterator>
    	void		insert (iterator position, InputIterator first, InputIterator last){ position = NULL; first = last;}
		iterator	erase (iterator position){ position = NULL;  return NULL;}
		iterator	erase (iterator first, iterator last){ first = last; return NULL;}
		
		void		swap (Vector& x)
		{
			value_type *tmp_array;
			size_type	tmp_size;
			size_type	tmp_capacity;

			tmp_array 		= x._array;
			tmp_size 		= x._size;
			tmp_capacity 	= x._capacity;

			x._array 		= this->_array;
			x._size 		= this->_size;
			x._capacity 	= this->_capacity;

			this->_array	= tmp_array;
			this->_size		= tmp_size;
			this->_capacity = tmp_capacity;
		}
		void		clear() { _size = 0;}//TODO:might need to destroy all elements



		private:
		void reAlloc(const Vector& x)
		{
			_alloc.deallocate(_array, _capacity);
			if (x._capacity < _size)
				_size = x._capacity;
			value_type *newArray = _alloc.allocate(x._capacity);
			for(size_t i = 0; i < _size; i++)
				newArray[i] = x._array[i];
			_array = newArray;
			_capacity = x._capacity;

		}
		void reAlloc(size_t newCapacity)
		{
			if (newCapacity < _size)
				_size = newCapacity;
			value_type *newArray = _alloc.allocate(newCapacity);
			for(size_t i = 0; i < _size; i++)
				newArray[i] = _array[i];
			
			_alloc.deallocate(_array, _capacity);
			_array = newArray;
			_capacity = newCapacity;
		}







		private :
			value_type		*_array;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			pointer			_end;
			pointer			_begin;
			pointer			_endofcapacity;
	};


	template<class T, class Alloc>
    bool operator== (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (lhs.size() == rhs.size());
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
    template<class T, class Alloc>
    bool operator!= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template<class T, class Alloc>
    bool operator<  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template<class T, class Alloc>
    bool operator>  (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }
    template<class T, class Alloc>
    bool operator<= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs  < rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    bool operator>= (const Vector<T,Alloc>& lhs, const Vector<T,Alloc>& rhs)
    {
        if (lhs > rhs || lhs == rhs)
            return (true);
        return (false);
    }
    template<class T, class Alloc>
    void    swap(Vector<T, Alloc>& x, Vector<T, Alloc>& y) { x.swap(y);}

}