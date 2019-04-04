/**
 * \file Stack.cpp
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/09
 * \date Last modified 2019/03/18
 * \brief Implimentation of the generic stack
 */
//Importation
#include "Stack.h"
#include "CardTypes.h"
#include <stdexcept>

/**
 * \brief Default constructor for the class
 */
template <class T>
Stack<T>::Stack() {
    stack = *(new std::vector<T>());
}

/**
 * \brief Constructor method for the class.
 * \details Set up with the given list of element
 * \param stack Initial list of element in the stack
 */
template <class T>
Stack<T>::Stack(std::vector<T> stack) {
    this->stack = stack;
}

/**
 * \brief Add a element to the top of stack.
 * \param element Initial list of element in the stack
 * \return A new Stack object with given element on top
 */
template <class T>
Stack<T> Stack<T>::push(T element) {
    stack.push_back(element);
    Stack<T> newStack = *(new Stack(stack));
    stack.pop_back();
    return newStack;
}

/**
 * \brief Remove a element from the top of stack.
 * \return A new Stack object without the top-most element
 * \throw out_of_range out of range exception when stack is empty
 */
template <class T>
Stack<T> Stack<T>::pop() {
    if (size() == 0) {
        throw std::out_of_range("");
    }
    T element = top();
    stack.pop_back();
    Stack<T> newStack = *(new Stack(stack));
    stack.push_back(element);
    return newStack;
}

/**
 * \brief Returns the element on the top of stack
 * \return The element on the top of stack
 * \throw out_of_range out of range exception when stack is empty
 */
template <class T>
T Stack<T>::top() {
    if (size() == 0) {
        throw std::out_of_range("");
    }
    return stack.back();
}

/**
 * \brief Returns the size of the stack
 * \return The size of the stack
 */
template <class T>
unsigned int Stack<T>::size() {
    return stack.size();
}

/**
 * \brief Returns the sequence of element in the stack
 * \return Sequence of element in the stack
 */
template <class T>
std::vector<T> Stack<T>::toSeq() {
    return stack;
}

// Keep this at bottom
template class Stack<CardT>;
