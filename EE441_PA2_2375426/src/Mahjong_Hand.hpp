#pragma once
#include <algorithm>
#include "Tile.hpp"
#include <stdexcept>

#define MAX_HAND_SIZE 14

class Hand {
private:
    Tile* m_tiles[MAX_HAND_SIZE];  // Array of pointers to Tile objects representing the hand
    size_t m_handSize;             // Tracks the current number of tiles in the hand

    // Insert a new tile before a given index
    void insert_before(size_t index, Tile* new_tile) {
        if (m_handSize >= MAX_HAND_SIZE) {
            throw std::out_of_range("Hand is full, cannot insert a new tile.");
        }
        for (size_t i = m_handSize; i > index; --i) {
            m_tiles[i] = m_tiles[i - 1]; // Shift tiles to the right to create space for the new tile
        }
        m_tiles[index] = new_tile;  // Place the new tile at the correct position
        ++m_handSize;              // Increment the hand size after the insertion
    }

    // Remove and return a tile at a specific index
    Tile* pop(size_t index) {
        if (index >= m_handSize) {
            throw std::out_of_range("Index out of range for pop, enter a valid Index.");
        }
        Tile* removed_tile = m_tiles[index]; // Store the tile being removed
        for (size_t i = index; i < m_handSize - 1; ++i) {
            m_tiles[i] = m_tiles[i + 1]; // Shift the elements to the left to fill the gap
        }
        m_tiles[m_handSize - 1] = nullptr; // Set the last pointer to nullptr after removal
        --m_handSize;                      // Decrease the hand size as one tile is removed
        return removed_tile;
    }

public:
    // Constructor: Initialize an empty hand
    Hand() {
        m_handSize = 0;  // Set hand size to 0 initially
        for (size_t i = 0; i < MAX_HAND_SIZE; ++i) {
            m_tiles[i] = nullptr; // Initialize each tile pointer to nullptr
        }
    }

    // Destructor: Free memory for all allocated tiles
    ~Hand() {
        for (size_t i = 0; i < m_handSize; ++i) {
            delete m_tiles[i];   // Free each tile pointer from memory
            m_tiles[i] = nullptr; // Set pointer to nullptr to avoid dangling references
        }
    }

    // Clear the hand and reset its size
    void clear() {
        for (size_t i = 0; i < m_handSize; ++i) {
            delete m_tiles[i];   // Free memory for each tile
            m_tiles[i] = nullptr; // Set each pointer to nullptr
        }
        m_handSize = 0; // Reset the hand size to 0
    }

    // Add a new tile into the hand while keeping it sorted
    void add_tile(Tile* new_tile) {
        if (m_handSize >= MAX_HAND_SIZE) {
            throw std::out_of_range("Cannot add more tiles, hand is currently full.");
        }
        size_t i = 0;
        while (i < m_handSize && *m_tiles[i] < *new_tile) {
            ++i; // Find the correct position for the new tile by comparing it to existing tiles
        }
        insert_before(i, new_tile); // Insert the tile at the correct position
    }

    // Discard the most "useless" tile based on specific rules
    Tile* discard_tile(void) {
        // Step I: Look for quadruplets
        for (size_t i = 0; i < m_handSize; ++i) {
            int count = 0;
            for (size_t j = 0; j < m_handSize; ++j) {
                if (*m_tiles[i] == *m_tiles[j]) {
                    count++; // Count how many times this tile appears
                }
            }
            if (count == 4) {  // If a quadruplet is found
                return pop(i);  // Discard one tile from the quadruplet and return it
            }
        }

        // Step II: Look for single tiles
        for (size_t i = 0; i < m_handSize; ++i) {
            int count = 0;
            for (size_t j = 0; j < m_handSize; ++j) {
                if (*m_tiles[i] == *m_tiles[j]) {
                    count++; // Count how many times this tile appears
                }
            }
            if (count == 1) {  // If a single tile is found
                return pop(i);  // Discard the single tile and return it
            }
        }

        // Step III: Look for pairs
        for (size_t i = 0; i < m_handSize; ++i) {
            int count = 0;
            for (size_t j = 0; j < m_handSize; ++j) {
                if (*m_tiles[i] == *m_tiles[j]) {
                    count++; // Count how many times this tile appears
                }
            }
            if (count == 2) {  // If a pair is found
                return pop(i);  // Discard one tile from the pair and return it
            }
        }
        return nullptr; // If no tile is discarded, return nullptr to avoid the warning.
    }

    // Check if the hand satisfies the winning condition (4 triplets + 1 pair)
    bool check_win_condition() const {
        size_t triplets = 0;
        size_t pairs = 0;

        for (size_t i = 0; i < m_handSize;) {
            size_t count = 1;
            while (i + count < m_handSize && *m_tiles[i] == *m_tiles[i + count]) {
                ++count; // Count consecutive identical tiles
            }
            if (count == 1 || count >= 4) {
                return false; // Invalid if there's a single tile or quadruplet
            }
            if (count == 2) pairs++; // Count pairs
            if (count == 3) triplets++; // Count triplets
            i += count; // Skip over the current group of tiles by adjusting index according to found grouping.
        }

        return (pairs == 1 && triplets == 4); // Check if there is exactly 1 pair and 4 triplets
    }

    // Display all tiles in the hand
    void display_hand() const {
        for (size_t i = 0; i < m_handSize; ++i) {
            std::cout << *m_tiles[i] << " "; // Dereference each tile pointer and print the tile
        }
        std::cout << std::endl; // Print a newline at the end of the hand
    }
};
