#include <iostream>
#include "sudoku.hpp"
#include "memory.hpp"

void play(const char* filename)
{
    Sudoku sudoku;
    sudoku.set_clues(filename);
    if (sudoku.solve()) {
        sudoku.print();
    } else {
        std::cout << "No solution available!\n" << std::endl;
    }
}

int main()
{
    std::cout << "First Game" << std::endl;
    play("data/s1.txt");
    std::cout << "\nSecond Game" << std::endl;
    play("data/s2.txt");
    std::cout << "\nThird Game" << std::endl;
    play("data/s3.txt"); // No solution
}
