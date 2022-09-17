#pragma once

# include "Vector.hpp"

namespace ft {


    template <class T, class Container = Vector<T> >
    class Stack {
    

        public:

            Container _container;

            typedef T value_type;
            typedef Container container_type;
            typedef size_t size_type;

            explicit Stack (const container_type& ctnr = container_type()) {
            
                _container = ctnr;
            }
            bool empty() const {
                return _container.empty();
            }
            size_type size() const {
            
                return _container.size();
            }
            value_type& top() { return _container.back();}
            const value_type& top() const { return _container.back();}
            void push (const value_type& val) {_container.push_back(val);}
            void pop() {_container.pop_back();}
    };
    template <class T, class Container>
    bool operator== (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return (lhs._container == rhs._container);
    }

    template <class T, class Container>
    bool operator!= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return !(lhs._container == rhs._container);
    }

    template <class T, class Container>
    bool operator<  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return (lhs._container < rhs._container);
    }

    template <class T, class Container>
    bool operator<= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return (lhs._container <= rhs._container);
    }

    template <class T, class Container>
    bool operator>  (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return (lhs._container > rhs._container);
    }

    template <class T, class Container>
    bool operator>= (const Stack<T,Container>& lhs, const Stack<T,Container>& rhs) {

        return (lhs._container >= rhs._container);
    }
};