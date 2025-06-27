#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <iostream>
#include <stdexcept>

// Macro defining the maximum size for the list
#define SORTEDLIST_MAX_SIZE 20

/**
 * @class SortedList
 * @brief A class that maintains a sorted list of floating-point numbers.
 *        Supports operations for inserting, removing, copying, finding,
 *        and printing elements, with automatic sorting.
 */
class SortedList {
    private:
        // Array to store the list elements, with a fixed maximum size
        float elements_of_list[SORTEDLIST_MAX_SIZE];

        // The current number of elements in the list
        size_t list_size;

    public:
        /**
         * @brief Default constructor that initializes the list size to 0.
         */
        SortedList() : list_size(0) {}

        /**
         * @brief Copies the contents of another SortedList into this one.
         * @param other The SortedList to copy from.
         */
        void copy(const SortedList& other);

        /**
         * @brief Returns the element at the specified index.
         * @param ind The index of the element to access.
         * @return The element at the given index.
         * @throws std::out_of_range if the index is out of bounds.
         */
        float index(size_t ind);

        /**
         * @brief Inserts a new number into the list while maintaining sorted order.
         * @param number The number to insert.
         * @return The index at which the number was inserted.
         * @throws std::length_error if the list exceeds maximum size after insertion.
         */
        size_t insert(float number);

        /**
         * @brief Removes and returns the element at the specified index.
         * @param index The index of the element to remove.
         * @return The removed element.
         * @throws std::out_of_range if the index is out of bounds.
         */
        float remove(size_t index);

        /**
         * @brief Finds the index of a specified number in the list using binary search.
         * @param number The number to find.
         * @return The index of the found number.
         * @throws std::domain_error if the number is not in the list.
         */
        size_t find(float number);

        /**
         * @brief Prints the contents of the list. If the list is empty, prints a message indicating so.
         */
        void print() const;
};

#endif // SORTEDLIST_H
