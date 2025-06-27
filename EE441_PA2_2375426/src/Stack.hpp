#pragma once

#include <iostream>
#include <stdexcept>

template <class T>
class Stack {
private:
    size_t m_capacity;  // Maximum number of elements the stack can hold
    size_t m_size;      // Current number of elements in the stack
    T* m_data;          // Pointer to dynamically allocated array storing stack elements

public:
    // Default constructor
    Stack() {
        m_capacity = 0;      // Initialize capacity to 0, meaning no space allocated initially
        m_size = 0;          // Start with an empty stack
        m_data = nullptr;    // Pointer to data is initially null
    }
    // Initializes an empty stack with no elements and no capacity.

    // Parameterized constructor
    Stack(size_t capacity) {
        m_capacity = capacity;  // Set the desired capacity of the stack
        m_size = 0;             // Stack starts empty
        m_data = new T[m_capacity];  // Allocate memory for the stack elements
    }
    // Allows creating a stack with a specific initial capacity.

    // Destructor
    ~Stack() {
        if (m_data) {
            delete[] m_data;  // Free the dynamically allocated memory for the stack
        }
    }
    // Ensures memory used by the stack is properly released when the stack object is destroyed.

    // Check if the stack is empty
    bool is_empty() const {
        return (m_size == 0);  // Returns true if the stack has no elements
    }
    // Purpose: To check if the stack is empty without directly accessing the size.

    // Clear the stack
    void clear() {
        if (m_data) {
            delete[] m_data;  // Deallocate the memory holding stack elements
        }
        m_data = nullptr;      // Set data pointer to nullptr to avoid dangling references
        m_capacity = 0;        // Reset capacity
        m_size = 0;            // Reset the size to 0
    }
    // Clears the stack, effectively making it empty and resetting all properties.

    // Reserve new capacity for the stack
    void reserve(size_t new_capacity) {
        if (new_capacity == m_capacity) return; // No need to do anything if the capacity stays the same

        // Allocate a new array with the requested capacity
        T* new_data = new T[new_capacity];

        // Determine how many elements to copy (either the current size or the new capacity)
        size_t copy_elements = (new_capacity < m_size) ? new_capacity : m_size;

        // Copy elements from the old array to the new one
        for (size_t i = 0; i < copy_elements; ++i) {
            new_data[i] = m_data[i];
        }

        // Free the old data array
        delete[] m_data;

        // Update the stack's data pointer and capacity
        m_data = new_data;
        m_capacity = new_capacity;
        m_size = copy_elements; // Adjust size if the new capacity is smaller
    }
    // Expands the capacity of the stack to hold more elements when needed.

    // Add an element to the stack
    void push_back(const T& value) {
        if (m_size >= m_capacity) { 
            reserve((m_capacity == 0) ? 1 : m_capacity * 2); // Double the capacity if stack is full
        }
        m_data[m_size] = value;  // Add the new element to the stack
        m_size++;                // Increment the size of the stack
    }
    // Adds an element to the top of the stack and resizes the stack if necessary.

    // Remove the top element and return it
    T pop_back() {
        if (is_empty()) {  // Check if the stack is empty
            throw std::out_of_range("Stack is empty.");  // Throw an exception if there's nothing to pop
        }
        T popped_value = m_data[m_size - 1];  // Get the top element
        m_size--;  // Decrease the size of the stack
        return popped_value;  // Return the popped value
    }
    // Removes the top element of the stack and returns it, throws exception if empty.

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack) 
    {
        os << "[ ";
        for (size_t i = 0; i < stack.m_size; ++i) {
            os << stack.m_data[i] << ' ';
        }
        os << "]";
        return os;
    }
};
