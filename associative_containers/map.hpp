#pragma once 

#include <exception>
#include <cstring>
#include <memory>
#include "AVL.hpp"
#include "Pair.hpp"

namespace ft 
{
	template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		typedef Key                                         							key_type;
        typedef T                                           							mapped_type;
        typedef ft::pair<const key_type, mapped_type>       							value_type;
        typedef Compare                                     							key_compare;

										
		typedef class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
			protected:
				Compare _comp;
			public:
				value_compare(const Compare &c) : _comp(c) { }
				value_compare(){};
				bool operator()(const value_type &lhs, const value_type &rhs) const
				{
					return(_comp(lhs.first, rhs.first));
				}
		}																				value_compare;


		typedef Alloc                                       							allocator_type;
        typedef typename allocator_type::reference          							reference;
        typedef typename allocator_type::const_reference    							const_reference;
        typedef typename allocator_type::pointer            							pointer;
        typedef typename allocator_type::const_pointer      							const_pointer;

        typedef typename ft::AVL<value_type, Compare, Alloc>::iterator					iterator;
        typedef typename ft::AVL<value_type, Compare, Alloc>::const_iterator			const_iterator;
        typedef typename ft::AVL<value_type, Compare, Alloc>::reverse_iterator			reverse_iterator;
        typedef typename ft::AVL<value_type, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;

        typedef std::ptrdiff_t                              							difference_type;
        typedef size_t                                      							size_type;


	public :

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{

		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		{

		}
		map (const map& x)
		{

		}
		~map()
		{

		}


		iterator begin()						{}
		const_iterator begin() const			{}
		iterator end()							{}
		const_iterator end() const				{}
		reverse_iterator rbegin()				{}
		const_reverse_iterator rbegin() const	{}
		reverse_iterator rend()					{}
		const_reverse_iterator rend() const		{}


		bool empty() const			{}
		size_type size() const		{}
		size_type max_size() const	{}


		mapped_type& operator[] (const key_type& k)		{}
		mapped_type& at (const key_type& k)				{}
		const mapped_type& at (const key_type& k) const	{}



		pair<iterator,bool> insert (const value_type& val) {}

		iterator insert (iterator position, const value_type& val) {}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {}



    	void erase (iterator position) 				{}
		size_type erase (const key_type& k) 		{}
    	void erase (iterator first, iterator last) 	{}

		void swap (map& x) 	{}

		void clear()		{}


		key_compare key_comp() const		{}
		value_compare value_comp() const	{}







		iterator find (const key_type& k)				{}
		const_iterator find (const key_type& k) const	{}


		size_type count (const key_type& k) const		{}




		iterator lower_bound (const key_type& k)				{}
		const_iterator lower_bound (const key_type& k) const	{}

		iterator upper_bound (const key_type& k)				{}
		const_iterator upper_bound (const key_type& k) const	{}


		pair<const_iterator,const_iterator> equal_range (const key_type& k) const	{}
		pair<iterator,iterator>             equal_range (const key_type& k)			{}

		allocator_type get_allocator() const	{};


	private :


	};


}