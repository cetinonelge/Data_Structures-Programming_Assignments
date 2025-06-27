#pragma once
#include <iostream>
#include <stdexcept>

// Define the Tile class representing individual tiles in a Mahjong hand.
class Tile {
public:
    char m_suit;     // The suit of the tile (e.g., 'B' for Bamboo, 'C' for Character, 'D' for Dot).
    int m_number;    // The number on the tile (e.g., 1-9).

    // Default constructor
    Tile() {
        m_suit = 'D';       // Default suit is set to 'D' (Dot).
        m_number = 9;       // Default number is set to 9.
    }
    // Purpose: Provide a default tile in case no specific suit or number is given.
    // This ensures all Tile objects are always initialized properly.

    // Parameterized constructor
    Tile(char s, int n) {
        m_suit = s;         // Assign the suit to the tile.
        m_number = n;       // Assign the number to the tile.
    }
    // Purpose: Allow creating tiles with a specific suit and number, making it flexible for game logic.

    // Comparison operator for equality (==)
    bool operator==(const Tile& other) const {
        return (m_suit == other.m_suit) && (m_number == other.m_number);
        // Compares both the suit and number of the tile. Only if both match are the tiles considered equal.
    }

    // Overload less-than operator (<)
    bool operator<(const Tile& other) const {
        return (m_suit < other.m_suit) || 
               (m_suit == other.m_suit && m_number < other.m_number);
        // Logic: Compare suits first. If the suits are different, the comparison is based on suits alone.
        // If suits are the same, then compare the numbers. This ensures a natural sorting order.
    }

    // Overload greater-than operator (>)
    bool operator>(const Tile& other) const {
        return !(*this <= other);
        // Logic: Reuse the already defined <= operator to simplify implementation.
        // If not <=, then it must be greater.
    }

    // Overload less-than-or-equal operator (<=)
    bool operator<=(const Tile& other) const {
        return (m_suit < other.m_suit) || 
               (m_suit == other.m_suit && m_number <= other.m_number);
        // Logic: Similar to <, but includes equality. If suits are the same and numbers are also equal, return true.
    }

    // Overload greater-than-or-equal operator (>=)
    bool operator>=(const Tile& other) const {
        return !(*this < other);
        // Logic: Reuse the < operator. If it's not less, then it must be greater or equal.
    }

    // Overload not-equal operator (!=)
    bool operator!=(const Tile& other) const {
        return (m_suit != other.m_suit) || (m_number != other.m_number);
        // Logic: If either the suit or the number is different, the tiles are not equal.
    }

    // Friend function to overload << operator for output
    friend std::ostream& operator<<(std::ostream& os, const Tile& tile) {
        os << tile.m_suit << tile.m_number;
        return os;
    }
};
