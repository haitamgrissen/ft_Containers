

#pragma once

# include <iostream>
# include "pair.hpp"
# include "miscellaneous.hpp"
# include "tree.hpp"

namespace ft {

    template < class Key,                           // map::key_type
    class T,                                       // map::mapped_type
    class Compare = std::less<Key>,               // map::key_compare
    class Alloc = std::allocator<pair< const Key,T> > >
    class mapiterator {

        public:

            typedef typename iterator<std::random_access_iterator_tag, pair< const Key, T> >::difference_type       difference_type;
            typedef typename iterator<std::random_access_iterator_tag, pair< const Key, T> >::value_type            value_type;
            typedef typename iterator<std::random_access_iterator_tag, pair< const Key, T> >::pointer               pointer;
            typedef typename iterator<std::random_access_iterator_tag, pair< const Key, T> >::reference             reference;
            typedef typename iterator<std::random_access_iterator_tag, pair< const Key, T> >::iterator_category     iterator_category;
            Alloc                                                                                                   _allocator;
            typedef pair< const Key, T>                                                                             pair;
            typedef node< Key, T>                                                                                   node;
            operator mapiterator<Key, T> () const                                   { return mapiterator<Key, T> (); }

            node *                      _current;
            pair *                      currentData;
            pair *                      _safe;
            node *                      _root;
        
            mapiterator()
            {    
                _current = nullptr; currentData = nullptr;
                _safe = _allocator.allocate(1);
                _allocator.construct(_safe, pair(Key(), T()));
                _root = nullptr;
            }
        
            mapiterator( node * root, node * current )
            {
                _safe = _allocator.allocate(1);
                _allocator.construct(_safe, pair(Key(), T()));
                if (current == nullptr) 
                {
                    currentData = nullptr;
                } 
                else
                {
                    currentData = current->data;
                }
                _current = current;
                _root = root;
            }

            mapiterator( const mapiterator& obj )
            {
                _current = obj._current;
                currentData = obj.currentData;
                _root = obj._root;
                _safe = _allocator.allocate(1);
                _allocator.construct(_safe, *obj._safe);
            }
    
            mapiterator &operator=(const mapiterator& obj )
            {
                _current = obj._current;
                currentData = obj.currentData;
                _root = obj._root;
                _safe = _allocator.allocate(1);
                _allocator.construct(_safe, *obj._safe);
                return *this;
            }

            ~mapiterator()
            {
                _allocator.destroy(_safe);
                _allocator.deallocate(_safe, 1);
            }

            node *treeMaximum(node *x) const 
            {
                if (x == nullptr)
                    return nullptr;
                while (x->right != nullptr)
                    x = x->right;
                return x;
            }

            node *treeMinimum(node *x)
            {
                if (x == nullptr)
                    return nullptr;
                while (x->left != nullptr)
                    x = x->left;
                return x;
            }

            node *treeSuccessor(node *x)
            {
                if (x == nullptr)
                    return x;
                if (x->right != nullptr)
                    return treeMinimum(x->right);
                node *y = x->parent;
                while (y != nullptr && (x == y->right))
                {
                    x = y;
                    y = y->parent;
                }
                return y;
            }

            node *treePredecessor(node *x)
            {
                if (x == nullptr)
                    return x;
                if (x->left != nullptr)
                    return treeMaximum(x->left);
                node *y = x->parent;
                while (y != nullptr && (x == y->left)) {
                
                    x = y;
                    y = y->parent;
                }
                return y;
            }



            pair& operator*() const { if (_current == nullptr)                                                  { return *(_safe);} return *_current->data;}
            pair* operator->() const { if (_current == nullptr)                                                 { return _safe;} return _current->data;}
        

            mapiterator& operator+= ( difference_type rhs ) { for  (difference_type it = rhs; it >= 1; it--)    { (*this)++;} return *this; };
            mapiterator& operator-= ( difference_type rhs ) { for  (difference_type it = rhs; it >= 1; it--)    { (*this)--;} return *this; };

            mapiterator& operator--()
            {
                if (_root != nullptr && _current == nullptr && currentData == nullptr)
                {
                    _current = treeMaximum(_root);
                    currentData = _current->data;
                    return *this;
                }
                _current = treePredecessor(_current);
                if (_current != nullptr)
                    currentData = _current->data;
                else
                    currentData = nullptr;
                return *this;
            }
        
            mapiterator operator++(int)
            {
                if (_root != nullptr && _current == nullptr && currentData == nullptr)
                {
                    _current = treeMinimum(_root);
                    currentData = _current->data;
                    return *this;
                }
                mapiterator tmp(*this);
                _current = treeSuccessor(_current);
                if (_current != nullptr)
                    currentData = _current->data;
                else
                    currentData = nullptr;
                return tmp;
            }

            mapiterator& operator++()
            {
                if (_root != nullptr && _current == nullptr && currentData == nullptr) 
                {
                    _current = treeMinimum(_root);
                    currentData = _current->data;
                    return *this;
                }
                _current = treeSuccessor(_current);
                if (_current != nullptr)
                    currentData = _current->data;
                else
                    currentData = nullptr;
                return *this;
            }

            mapiterator operator--(int)
            {
                mapiterator tmp(*this);
                if (_root != nullptr && _current == nullptr && currentData == nullptr)
                {
                    _current = treeMaximum(_root);
                    currentData = _current->data;
                    return *this;
                }
                _current = treePredecessor(_current);
                if (_current != nullptr)
                    currentData = _current->data;
                else
                    tmp.currentData = nullptr;
                return tmp;
            }

            bool operator==(const mapiterator& rhs) const {if (_current && rhs._current) {return _current->data == rhs._current->data;} return (currentData == rhs.currentData);}
            bool operator!=(const mapiterator& rhs) const {if (_current  && rhs._current) {return _current->data != rhs._current->data;} return (currentData != rhs.currentData);}
    };
}