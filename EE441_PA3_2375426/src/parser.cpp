#include <fstream>
#include <string>
#include <sstream>

#include "graph.hpp"
#include "sudoku.hpp"
#include "memory.hpp"

Graph create(const char *filename)
{
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Couldn\'t open the file!");
    }

    Graph graph;
    graph.add_vertex(); // add the first vertex

    std::string line;
    while (std::getline(f, line)) {
        size_t id1 = graph.add_vertex();

        std::stringstream ss(line);
        int connection;

        for (size_t id2 = 1 ; ss >> connection ; ++id2) {
            if (connection) {
                graph.connect(id1, id2);
            }
        }
    }

    f.close();
    return graph;
}

void Sudoku::set_clues(const char *filename)
{
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Couldn\'t open the file!");
    }

    // clear all the colors
    for (size_t i = 1 ; i <= 81 ; ++i) {
        (*this)[i]->color(0);
    }

    std::string line;
    size_t id = 1;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        int clue;

        while (ss >> clue) {
            (*this)[id++]->color(clue);
        }
    }

    f.close();
}
