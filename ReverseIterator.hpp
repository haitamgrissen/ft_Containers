#pragma once

#include "miscellaneous.hpp"

namespace ft
{
    template <typename Iterator>
    class reverse_iterator
    {

        public:
            typedef Iterator 									iterator_type;
            typedef typename iterator_type::value_type			value_type;
            typedef typename iterator_type::difference_type		difference_type;
            typedef typename iterator_type::pointer				pointer;
            typedef typename iterator_type::reference			reference;
            typedef typename iterator_type::iterator_category	iterator_category;

            reverse_iterator()															{ };
			explicit reverse_iterator(iterator_type it) : _current(--it) 				{ }//				{	operator=(--it);//}_current = it.base() - 1;}
			reverse_iterator(const reverse_iterator<iterator_type>& rIt)				{ _current = --rIt.base();}
			template<typename Iter>
			reverse_iterator (reverse_iterator<Iter> const& rIt): _current(--rIt.base())	{}




			iterator_type	base() const													{ iterator_type it = _current; return ++it;}



			//reference		operator*() const												{ return *(_current.base());}
			reference operator*() const
            {
                iterator_type tmp = _current;
                return (*(tmp));
            }
			pointer			operator->() const												{ return &(operator*());};
			reference		operator[](difference_type n) const								{ return _current[-n];};



			reverse_iterator&	operator= (const reverse_iterator& x)						{ _current = --x.base(); return (*this);}
			reverse_iterator&	operator+=(difference_type n)								{ this->_current -= n; return (*this);};
			reverse_iterator&	operator-=(difference_type n)								{ this->_current += n; return (*this);};



			reverse_iterator&	operator++()				{ --_current; return (*this);}
			reverse_iterator	operator++(int)				{ reverse_iterator tmp = *this; --_current; return (tmp);}
			reverse_iterator&	operator--()				{ ++_current; return (*this);}
			reverse_iterator	operator--(int)				{ reverse_iterator tmp(*this); ++_current; return (tmp);}



			reverse_iterator	operator+(difference_type n) const		{ reverse_iterator tmp(*this); tmp._current -= n; return tmp;}
			reverse_iterator	operator-(difference_type n) const		{ reverse_iterator tmp(*this); tmp._current += n; return tmp;}



            operator reverse_iterator<const iterator_type>() const		{ return reverse_iterator<const iterator_type>(_current);}



        private :
			iterator_type	_current;

    };


	template <class Iterator>
  	bool operator== (
		  const reverse_iterator<Iterator>& lhs,
		  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() == rhs.base();
	};


	template <class Iterator>
  	bool operator< (
		  const reverse_iterator<Iterator>& lhs,
	  	  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() > rhs.base();
	};


	template <class Iterator>
  	bool operator> (
		  const reverse_iterator<Iterator>& lhs,
	  	  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() < rhs.base();
	};


	template <class Iterator>
  	bool operator!= (
		  const reverse_iterator<Iterator>& lhs,
		  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() != rhs.base();
	};


	template <class Iterator>
  	bool operator>= (
		  const reverse_iterator<Iterator>& lhs,
		  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() <= rhs.base();
	};


	template <class Iterator>
  	bool operator<= (
		  const reverse_iterator<Iterator>& lhs,
		  const reverse_iterator<Iterator>& rhs)
	{
		  return lhs.base() >= rhs.base();
	};


	template <class Iterator>
  	reverse_iterator<Iterator> operator+(
		  	typename reverse_iterator<Iterator>::difference_type n, 
	  		const reverse_iterator<Iterator>& x)
	{
		reverse_iterator<Iterator> tmp (x.base() - n);
		return (tmp); 
	};


	template <class Iterator>
  	typename reverse_iterator<Iterator>::difference_type operator- (
    			const reverse_iterator<Iterator>& lhs,
    			const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}