/**
 * \file Stack.h
 * \author Mengxi Lei, leim5
 * \date Created 2019/03/09
 * \date Last modified 2019/03/21
 * \brief Defines a generic stack
 */
#ifndef A3_STACK_H_
#define A3_STACK_H_

//Importation
#include <vector>

/**
 * \brief Generic template/class representing a stack.
 */
template <class T>
class Stack {
    private:
        std::vector<T> stack;
    public:
        /**
         * \brief Default constructor for the class
         */
        Stack();
        /**
         * \brief Constructor method for the class.
         * \details Set up with the given list of element
         * \param stack Initial list of element in the stack
         */
        Stack(std::vector<T> stack);
        /**
         * \brief Add a element to the top of stack.
         * \param element Initial list of element in the stack
         * \return A new Stack object with given element on top
         */
        Stack<T> push(T element);
        /**
         * \brief Remove a element from the top of stack.
         * \return A new Stack object without the top-most element
         * \throw out_of_range out of range exception when stack is empty
         */
        Stack<T> pop();
        /**
         * \brief Returns the element on the top of stack
         * \return The element on the top of stack
         * \throw out_of_range out of range exception when stack is empty
         */
        T top();
        /**
         * \brief Returns the size of the stack
         * \return The size of the stack
         */
        unsigned int size();
        /**
         * \brief Returns the sequence of element in the stack
         * \return Sequence of element in the stack
         */
        std::vector<T> toSeq();
};

#endif
