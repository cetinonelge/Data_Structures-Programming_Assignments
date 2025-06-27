#include "SortedList.hpp"

/**
 * @brief Copies the contents of another SortedList into this one.
 * 
 * @param other The SortedList to copy from.
 */
void SortedList::copy(const SortedList& other) {
    list_size = other.list_size; // Copy the size of the other list
    // Copy each element from the other list
    for (size_t i = 0; i < list_size; i++) {
        elements_of_list[i] = other.elements_of_list[i];
    }
}

/**
 * @brief Returns the element at the specified index.
 * 
 * @param ind The index of the element to access.
 * @return The element at the given index.
 * @throws std::out_of_range if the index is out of bounds.
 */
float SortedList::index(size_t ind) {
    // Check if the index is valid
    if (ind >= list_size) {
        throw std::out_of_range("You Have Entered Out of Range Index, Enter Again");
    }
    return elements_of_list[ind]; // Return the element at the specified index
}

/**
 * @brief Inserts a new number into the list while maintaining sorted order.
 * 
 * @param number The number to insert.
 * @return The index at which the number was inserted.
 * @throws std::length_error if the list exceeds maximum size after insertion.
 */
size_t SortedList::insert(float number) {
    // Check if the list has reached its maximum size
    if (list_size == SORTEDLIST_MAX_SIZE) {
        throw std::length_error("List Length is Maximum Already");
    }
    size_t inserted_index; // Variable to store the index where the number will be inserted

    // Find the appropriate index to insert the new number
    for (inserted_index = 0; inserted_index < list_size; inserted_index++) {
        if (elements_of_list[inserted_index] > number) break; // Find the first element greater than number
    }
    
    // Shift elements to the right to make space for the new number
    for (size_t j = list_size; j > inserted_index; --j) {
        elements_of_list[j] = elements_of_list[j - 1];
    }
    elements_of_list[inserted_index] = number; // Insert the new number at the correct index
    list_size++; // Increment the size of the list
    return inserted_index; // Return the index where the number was inserted
}

/**
 * @brief Removes and returns the element at the specified index.
 * 
 * @param index The index of the element to remove.
 * @return The removed element.
 * @throws std::out_of_range if the index is out of bounds.
 */
float SortedList::remove(size_t index) {
    // Check if the index is valid
    if (index >= list_size) {
        throw std::out_of_range("You Have Entered Out of Range Index, Enter Again");
    }
    float temp = elements_of_list[index]; // Store the element to be removed
    // Shift elements to the left to fill the gap left by the removed element
    for (size_t i = index; i < list_size - 1; i++) {
        elements_of_list[i] = elements_of_list[i + 1];
    }
    list_size--; // Decrement the size of the list
    return temp; // Return the removed element
}

/**
 * @brief Finds the index of a specified number in the list using binary search.
 * 
 * @param number The number to find.
 * @return The index of the found number.
 * @throws std::domain_error if the number is not in the list.
 */
size_t SortedList::find(float number) {
    int low_range = 0; // Lower index of the search range
    int high_range = list_size - 1; // Upper index of the search range
    
    // Perform binary search
    while (low_range <= high_range) {
        // Calculate the middle index
        size_t middle = (high_range + low_range) / 2;
        // Check if the middle element is the number we're looking for
        if (elements_of_list[middle] == number) return middle; // Number found
        else if (elements_of_list[middle] > number) {
            high_range = middle - 1; // Search in the left half
        } else {
            low_range = middle + 1; // Search in the right half
        }
    }
    
    // If the number is not found, throw an exception
    throw std::domain_error("Number not found in the list.");
}

/**
 * @brief Prints the contents of the list. If the list is empty, prints a message indicating so.
 */
void SortedList::print() const {
    if (list_size == 0) {
        std::cout << "The list is empty." << std::endl; // Indicate that the list is empty
    } else {
        for (size_t i = 0; i < list_size; i++) {
            std::cout << elements_of_list[i] << " ";
        }
        std::cout << std::endl; // Print a newline after the elements
    }
}

