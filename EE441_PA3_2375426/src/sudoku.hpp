#pragma once

#include "graph.hpp"
#include "memory.hpp"

class Sudoku : private Graph
{
private:
    int max_color() const override;
public:
    Sudoku();
    ~Sudoku();

    void set_clues(const char* filename);
    bool solve();
    void print();
};
