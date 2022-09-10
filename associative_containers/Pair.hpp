#pragma once


namespace ft 
{
	template <class K, class V>
	struct pair
	{
		public:
		typedef K	key_type;
		typedef V	val_type;

	  	pair() : key(), value() {}
	  	template< class K, class V>
	  	pair(const pair<K,V>& other) : key(other.key), value(other.value){}
	  	pair(const key_type& k, const val_type& v) : key(k), value(v) {}
	  	
		pair& operator= (const pair& other)
	  	{
			this->key = other.key;
			this->value = other.value;
			return (*this);
	  	}


		key_type	key;
	  	val_type	value;
  	};

  	template <class K, class V>
  	bool operator== (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		if (!lhs.key && !rhs.key )
		  return (true);
		return (lhs.key == rhs.key && lhs.value == rhs.value);
  	}
  	template <class K, class V>
  	bool operator!= (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		return (!(lhs == rhs));
  	}
  	template <class K, class V>
  	bool operator<  (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		return (lhs.key < rhs.key) || (!(rhs.key<lhs.key) && lhs.value < rhs.value);
	}
  	template <class K, class V>
  	bool operator>  (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		return rhs < lhs;
	}
  	template <class K, class V>
  	bool operator<= (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		return !(rhs < lhs);
	}
  	template <class K, class V>
  	bool operator>= (const pair<K,V>& lhs, const pair<K,V>& rhs)
  	{
		return !(lhs < rhs);
	}

  	template<class K, class V>
  	pair<K, V> make_pair(K key, V value)
  	{
		return (pair<K, V>(key, value));
  	}
}