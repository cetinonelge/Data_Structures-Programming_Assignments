#include <iostream>
#include "sudoku.hpp"
#include "memory.hpp"

Sudoku::Sudoku()
{
    // Create 81 vertices to represent the 9x9 Sudoku grid
    for (size_t cell = 1; cell <= 81; ++cell) {
        add_vertex();
    }

    // Link vertices in the same row
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col1 = 0; col1 < 9; ++col1) {
            for (size_t col2 = col1 + 1; col2 < 9; ++col2) {
                size_t id1 = row * 9 + col1 + 1;
                size_t id2 = row * 9 + col2 + 1;
                connect(id1, id2);
            }
        }
    }

    // Link vertices in the same column
    for (size_t col = 0; col < 9; ++col) {
        for (size_t row1 = 0; row1 < 9; ++row1) {
            for (size_t row2 = row1 + 1; row2 < 9; ++row2) {
                size_t id1 = row1 * 9 + col + 1;
                size_t id2 = row2 * 9 + col + 1;
                connect(id1, id2);
            }
        }
    }

    // Link vertices in the same 3x3 subgrid
    for (size_t subgrid_row = 0; subgrid_row < 3; ++subgrid_row) {
        for (size_t subgrid_col = 0; subgrid_col < 3; ++subgrid_col) {
            for (size_t cell1 = 0; cell1 < 9; ++cell1) {
                for (size_t cell2 = cell1 + 1; cell2 < 9; ++cell2) {
                    size_t id1 = (subgrid_row * 3 + cell1 / 3) * 9 + (subgrid_col * 3 + cell1 % 3) + 1;
                    size_t id2 = (subgrid_row * 3 + cell2 / 3) * 9 + (subgrid_col * 3 + cell2 % 3) + 1;
                    connect(id1, id2);
                }
            }
        }
    }
}

Sudoku::~Sudoku()
{
    // Destructor relies on Graph's cleanup, no extra work needed
}

bool Sudoku::solve()
{
    // Utilize the inherited graph coloring functionality to solve Sudoku
    return color();
}

void Sudoku::print()
{
    // Iterate through each cell row by row and print the Sudoku grid
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            size_t id = row * 9 + col + 1; // Compute the cell ID
            std::cout << (*this)[id]->color() << " ";
        }
        std::cout << std::endl; // Start a new line after each row
    }
}

int Sudoku::max_color() const
{
    // Return the maximum allowable color for Sudoku (numbers 1 through 9)
    return 9;
}
