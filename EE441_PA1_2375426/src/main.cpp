#include "SortedList.hpp"

int main() {
    // Create two instances of the SortedList class
    SortedList List1;
    SortedList List2;

    // Insert floating-point numbers into List1 from 0 to 9
    for (float i = 0; i < 10; i++) {
        List1.insert(i); // Inserting values into List1
    }
    // Print the contents of List1
    std::cout << "Contents of List1: ";
    List1.print();

    // Insert floating-point numbers into List2, starting from 100 down to 25 in decrements of 5
    for (float i = 100; i > 20; i = i - 5) {
        List2.insert(i); // Inserting values into List2
    }
    // Print the contents of List2
    std::cout << "Contents of List2: ";
    List2.print();

    // Testing the index function on both lists
    std::cout << "index_test[5] for List1: " << List1.index(5) << std::endl; // Should return 5
    std::cout << "index_test[5] for List2: " << List2.index(5) << std::endl; // Should Return 50

    // Insert a new value into List1 and print the updated list
    List1.insert(1.234);
    std::cout << "Contents of List1 After Inserting 1.234: ";
    List1.print();

    // Insert a new value into List2 and print the updated list
    List2.insert(87.42);
    std::cout << "Contents of List2 After Inserting 87.42: ";
    List2.print();

    // Remove the element at index 7 from List1 and print the updated list
    List1.remove(7);
    std::cout << "Contents of List1 After Removing [7]: ";
    List1.print();

    // Remove the element at index 3 from List2 and print the updated list
    List2.remove(3);
    std::cout << "Contents of List2 After Removing [3]: ";
    List2.print();

    // Test the find function for the inserted value in List1
    std::cout << "Find_test with 1.234 in List1: " << List1.find(1.234) << std::endl; // Should return the index of 1.234
    // Test the find function for the inserted value in List2
    std::cout << "Find_test with 87.42 in List2: " << List2.find(87.42) << std::endl; // Should return the index of 87.42

    // Copy the contents of List2 into List1 and print both lists
    List1.copy(List2);
    std::cout << "Copy List2 to List1: " << std::endl;
	std::cout << "List1: ";
    List1.print(); // Print the contents of List1 after copying
	std::cout << "List2: ";
    List2.print(); // Print the contents of List2

	// Additional Tests
	std::cout << "\n=== Additional Tests ===\n";

	// Testing the boundary condition when the list reaches its maximum capacity
	try {
		SortedList fullList;
		for (float i = 0; i < 20; i++) {
			fullList.insert(i); // Insert items until the list is full
		}
		fullList.insert(21); // Try inserting an item into the already full list (should trigger an exception)
	} catch (const std::length_error& e) {
		std::cout << "Caught exception when trying to insert into a full list: " << e.what() << std::endl;
	}

	// Testing removal from an empty list
	SortedList emptyList;
	try {
		emptyList.remove(0); // Attempt to remove an element from an empty list (should throw an exception)
	} catch (const std::out_of_range& e) {
		std::cout << "Caught exception when attempting to remove from an empty list: " << e.what() << std::endl;
	}

	// Testing the find function when the number is not in the list
	try {
		List1.find(999.99); // Try finding a number that doesn't exist in the list (should throw an exception)
	} catch (const std::domain_error& e) {
		std::cout << "Caught exception when searching for a non-existent number: " << e.what() << std::endl;
	}

	// Testing the print function on an empty list
	std::cout << "Contents of an empty list: ";
	emptyList.print(); // Should indicate that the list is empty

	// Testing an edge case when accessing an index in an empty list
	try {
		std::cout << "Accessing index 0 of an empty list: " << emptyList.index(0) << std::endl; // Should throw an exception
	} catch (const std::out_of_range& e) {
		std::cout << "Caught exception when trying to access an index in an empty list: " << e.what() << std::endl;
	}

    return 0;
}
