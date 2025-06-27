#pragma once

#include "list.hpp"
#include "memory.hpp"

class Graph
{
public:
    class Vertex
    {
    private:
        size_t m_id;
        int m_color;

        List<Vertex*> m_neighbors;

        friend class Graph;

    public:
        Vertex(size_t id);

        size_t id() const;
        int color() const;
        bool color(int color);

        void add_neighbor(Vertex* other);
        void remove_neighbor(Vertex* other);
    };

private:
    List<Vertex*> m_vertices;

public:
    Graph();
    virtual ~Graph();

    Graph(const Graph& other);
    Graph(Graph&& other);
    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other);

    size_t add_vertex();

    Vertex* operator[](size_t id);

    void connect(size_t id1, size_t id2);

    virtual int max_color() const;

private:
    bool color_helper(List<Vertex*>::Iterator vertex);

public:
    bool color();
};

Graph create(const char* filename);
