#pragma once 

#include <exception>
#include <cstring>
#include <memory>

namespace ft
{
	template <class T, class Compare = std::less<typename T::key_type>, class Alloc = std::allocator<T> >
	class AVL
	{
		public:
        	typedef T															value_type;
			typedef Alloc														allocator_type;
       		typedef size_t                                      				size_type;
       		typedef ft::Node<T>*                           						pointer;
        	typedef ft::NODE<const T>											const_pointer;
        	//typedef typename Alloc::template rebind<ft::NODE<T> >::other		node_alloc;

        	typedef typename value_type::key_type								key;
        	typedef typename value_type::val_type								value;
       		typedef Compare                                     				key_compare;

        	typedef ft::map_iterator<T, ft::NODE<T>, Compare, AVL>				iterator;
        	typedef ft::reverse_iterator<iterator>								reverse_iterator;
        	typedef ft::map_iterator<const T, const ft::NODE<T>, Compare, AVL>	const_iterator;
        	typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
      
	  
	   		typedef ft::biterator<Node<value_type>, value_type> 				iterator;
       		typedef ft::biterator<Node<value_type>, const value_type> 			const_iterator;
       		typedef ft::reverse_iterator<iterator>             					reverse_iterator;
       		typedef ft::reverse_iterator<const_iterator>       					const_reverse_iterator;

	};

	template<class T>
	class NODE
	{
		public :
			typedef T			value_type;
			int					bf;
			value_type			*data;
			NODE<T>				*left;
			NODE<T>				*right;
			NODE<T>				*parent;
			int					height;


			NODE() : data(nullptr), left(nullptr), right(nullptr), parent(nullptr), height(0)
			{}
			NODE(value_type val) : data(val), left(nullptr), right(nullptr), height(0), parent(nullptr)
			{}
			NODE(const NODE& nd) : data(nd.data), left(nd.left), right(nd.right), height(nd.height), bf(nd.bf), parent(nd.parent)
			{}
			virtual ~NODE(){};
		  	NODE& operator=(const NODE& node)
		  	{
				data = node.data;
				left = node.left;
				right = node.right;
				bf = node.bf;
				height = node.height;
				parent = node.parent;
				return (*this);
		  	}
	};
  	template<class T>
  	bool  operator== (const NODE<T>&lhs, const NODE<T>&rhs)
  	{
		if (lhs->data == nullptr && rhs->data == nullptr)
		  return true;
		return (lhs->data == rhs.data);
  	}
  	template<class T>
  	bool operator!=(const NODE<T>&lhs, const NODE<T>&rhs)
  	{
		return (!(lhs == rhs));
  	}
  	template <class T>
  	struct less : std::binary_function<T,T,bool>
  	{
		bool operator() (const T& x, const T& y) const
		{
		  return (x < y);
		}
  	};
}