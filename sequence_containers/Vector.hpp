# pragma once



#include "../ft_containers.hpp"

// #include "../Iterator.hpp"
// #include "RandomAccessIterator.hpp"
// #include "ReverseIterator.hpp"
// #include "Enable_if.hpp"
// #include "RelationalOperators.hpp"
// #include "Utilities.hpp"


namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public :
		typedef T                                               value_type;


		typedef Alloc                                           allocator_type;
		typedef typename    allocator_type::reference           reference;
		typedef typename    allocator_type::const_reference     const_reference;
		typedef typename    allocator_type::pointer             pointer;
		typedef typename    allocator_type::const_pointer       const_pointer;

		typedef ft::RandomAccessIterator<value_type>            iterator;
		typedef ft::RandomAccessIterator<const value_type>      const_iterator;
		typedef ft::reverse_iterator<iterator>                  reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

		typedef  size_t                                         size_type;
		typedef  size_t											difference_type;


		///////////// Constructors Destructor

		explicit Vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc)
		{
			_array = nullptr;
			_size = 0;
			_capacity = 0;
		}
		explicit Vector (size_type n, const value_type& val = value_type(),
				 const allocator_type& alloc = allocator_type()): _alloc(alloc)
		{
			_size = n;
			_capacity = n;
			if (n <= 0)
				return ;
			_array = _alloc.allocate(n);
			for (size_t i = 0; i < n; i++)
				_alloc.construct(&_array[i], val);
			
		}

		template<class InputIterator>
        Vector(InputIterator first, InputIterator last,
        const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) : _alloc(alloc)
        {
            difference_type n = last - first;
			// if (n < 0)
			// 	n *= -1;
			_capacity = n;
			_size = n;
			if (n <= 0)
				return;
            _array = _alloc.allocate(n);
            for(size_t i = 0; i < n && first != last; i++, first++)
                _alloc.construct(&_array[i], *first);
        }
		Vector (const Vector& copy)
		{
			_capacity = copy.capacity();
			_size = copy.size();
			_alloc = copy._alloc;

			_array = _alloc.allocate(_capacity);
			for(size_t i = 0; i < _capacity; i++)
				_alloc.construct(&_array[i], copy._array[i]);
		}
		
		~Vector()
		{
			this->clear();
			_alloc.deallocate(_array, _capacity);
		}

		Vector& operator= (const Vector& x)
		{
			reAlloc(x);
			return (*this);
		}


		///////Iterators

		iterator				begin() 		{return (iterator(_array));}
		iterator				end()			{return (iterator(_array + _size));}
		reverse_iterator		rbegin()		{return (reverse_iterator(end()));}
		reverse_iterator		rend()			{return (reverse_iterator(begin()));}
		const_iterator			begin() const	{return (iterator(_array));}
		const_iterator			end()  const	{return (iterator(_array + _size));}
		const_reverse_iterator	rbegin() const	{return (const_reverse_iterator(end()));}
		const_reverse_iterator	rend()  const	{return (const_reverse_iterator(begin()));}


		///////////// Capacity

		size_type		size() const 			{ return  _size; }
		size_type		max_size() const 		{ return _alloc.max_size();}
		void			resize (size_type n, value_type val = value_type())
		{
			if (n > _capacity)
			{
				reserve(n);
				for (; _size < n ; _size++)
					_array[_size] = val;
			}
			else if (n > _size)
				for (; _size < n ; _size++)
					_array[_size] = val;
			else
				for (; _size > n; )
					_array[_size--].~value_type();

		}
		size_type		capacity() const 		{ return  _capacity; }
		bool			empty() 				{ return ((_size == 0) ? true : false); }
		void			reserve (size_type n)	{ if (n > _capacity) reAlloc(n); }


		///////////// Element access:

		reference			operator[](size_t index) 			{ return _array[index];}
		const_reference		operator[](size_t index) const 		{ return _array[index];}
		reference			at (size_type n) 					{ if (n > _size) throw std::out_of_range("out of range"); else return _array[n];}
		const_reference		at (size_type n) const 				{ if (n > _size) throw std::out_of_range("out of range"); else return _array[n];}
		reference			front() 							{return _array[0];}
		const_reference		front() const 						{return _array[0];}
		reference			back() 								{return (_array[_size - 1]);}
		const_reference		back() const 						{return (_array[_size - 1]);}


		///////////// Modifiers:

		template <class InputIterator>
  		void		assign (InputIterator first, InputIterator last)
		{
			size_t dist = std::distance(first, last);
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			if (_capacity < dist)
			{
				_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(dist);
				_capacity = dist;
				_size = dist;
			}
			for (size_t i = 0; i < dist && first != last; first++, i++)
				_alloc.construct(&_array[i], *first);
		}
		void		assign (size_type n, const value_type& val)
		{
			if (n > _capacity)
			{
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_alloc.deallocate(_array, _capacity);
				_size = n;
				_capacity = n;
				_array = _alloc.allocate(n);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_array[i], val);
			}
			else {
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size = n;
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_array[i], val);
			}
		}
		
		void		push_back (const value_type& val)
		{
			if (_size == _capacity)
				_capacity == 0 ? reserve(1) : reserve(_capacity * 2);
			_alloc.construct(&_array[_size], val);
			_size++;
		}
		void		pop_back() { _alloc.destroy(&_array[_size--]);}
		
		iterator	insert (iterator position, const value_type& val)	
		{
			difference_type at = position - _array;
			if (_size == _capacity)
				_capacity == 0 ? reserve(1) : reserve(_capacity * 2);
			for (difference_type i = _size; i > at; i--)
				_alloc.construct(&_array[i], _array[i - 1]);
			_alloc.construct(&_array[at], val);
			_size++;
			return (_array + at);
		}
   		void		insert (iterator position, size_type n, const value_type& val)
		{
			int at = position - _array;
            if ((_size + n) > _capacity)
                reserve((n > _size) ? (_size + n) : (_capacity * 2));
            else if (_size == 0)
                reserve(n);
            for (int i = _size - 1; i >= at; i--)
                _alloc.construct(&_array[i + n], _array[i]);
            for (size_type i = 0; i < n; i++, at++)
                _alloc.construct(&_array[at], val);
			_size += n;
		}
		template <class InputIterator>
		void		insert (iterator position, InputIterator first, InputIterator last)
		{
			long long at = position - _array;
			size_type n = last - first;
            if ((_size + n) > _capacity)
                reserve((n > _size) ? (_size + n) : (_capacity * 2));
            else if (_size == 0)
                reserve(n);
            for (long long i = _size - 1; i >= at; i--)
                _alloc.construct(&_array[i + n], _array[i]);
            for (size_type i = 0; i < n; i++, at++, first++)
                _alloc.construct(&_array[at], *first);
			_size += n;
		}	
		
		iterator	erase (iterator position)
        {
			size_t at = position - _array;
			//_alloc.destroy(&_array[at]);
			for (size_t i = at; i < _size - 1; i++)
				_alloc.construct(&_array[i], _array[i + 1]);
			_size--;
			return (_array + at);
        }
		iterator	erase (iterator first, iterator last)
		{
			size_type at = first - _array;
			size_type n = last - first;
			for (size_type i = at; i < _size - n; i++)
			{
				//_alloc.destroy(&_array[i]);
				_alloc.construct(&_array[i], _array[i + n]);
			}
			_size -= n;
			return (_array + at);
		}
		
		void		swap (Vector& x)
		{
			value_type	*tmp_array;
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
		void		clear() { for(size_type i = 0; i < _size; i++) _alloc.destroy(&_array[i]); _size = 0; }


		///////////// Allocator

		allocator_type			get_allocator() const { return (_alloc); }


		private:
			void reAlloc(const Vector& x)
			{
				if (this == &x)
					return ;
				if (_array != nullptr)
					_alloc.deallocate(_array, _capacity);
				_size = x.size();
				_capacity = x.capacity();
				_array = _alloc.allocate(_capacity);
				for(size_t i = 0; i < _size; i++)
					_alloc.construct(&_array[i], x._array[i]);
			}
			void reAlloc(size_t newCap)
			{
				if (newCap > _capacity)
				{
					value_type *newArray = _alloc.allocate(newCap);
					for(size_t i = 0; i < _size; i++)
					{
						_alloc.construct(&newArray[i], _array[i]);
						_alloc.destroy(&_array[i]);
					}
					_alloc.deallocate(_array, _capacity);
					_array = newArray;
					_capacity = newCap;
				}
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