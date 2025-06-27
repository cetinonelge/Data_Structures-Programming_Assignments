#include "graph.hpp"
#include "memory.hpp"

Graph::Vertex::Vertex(size_t id) : m_id(id), m_color(0) { }

size_t Graph::Vertex::id() const
{
    return m_id;
}

int Graph::Vertex::color() const
{
    return m_color;
}

bool Graph::Vertex::color(int color)
{
    // Always allow updating the color to 0 (unassigned)
    if (color == 0) {
        m_color = 0;
        return true;
    }

    // Iterate through all neighbors
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it) {
        if ((*it)->color() == color) {
            // A neighbor already has the same color
            return false;
        }
    }

    // If no neighbor has the same color, update the color
    m_color = color;
    return true;
}

void Graph::Vertex::add_neighbor(Vertex* other)
{
    // Do nothing if the input is nullptr
    if (other == nullptr) {
        return;
    }

    // Check if the other vertex is already a neighbor
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it) {
        if (*it == other) {
            // Already a neighbor, do nothing
            return;
        }
    }

    // Add the other vertex as a neighbor
    m_neighbors.push_back(other);

    // Add this vertex as a neighbor to the other vertex
    other->m_neighbors.push_back(this);
}

void Graph::Vertex::remove_neighbor(Vertex* other)
{
    // Do nothing if the input is nullptr
    if (other == nullptr) {
        return;
    }

    // Find and remove the other vertex from this vertex's neighbors
    for (auto it = m_neighbors.begin(); it != m_neighbors.end(); ++it) {
        if (*it == other) {
            m_neighbors.remove(it);
            break;
        }
    }

    // Find and remove this vertex from the other vertex's neighbors
    for (auto it = other->m_neighbors.begin(); it != other->m_neighbors.end(); ++it) {
        if (*it == this) {
            other->m_neighbors.remove(it);
            break;
        }
    }
}

Graph::Graph() { }

Graph::~Graph()
{
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        delete *it;
    }
    m_vertices = List<Vertex*>(); // Clear the list
}

Graph::Graph(const Graph &other)
{
    // Step 1: Create a map to associate old vertices with new vertices
    List<Vertex*> copied_vertices;

    // Step 2: Copy vertices
    for (auto it = other.m_vertices.begin(); it != other.m_vertices.end(); ++it) {
        Vertex* new_vertex = new Vertex((*it)->id());
        new_vertex->m_color = (*it)->color(); // Copy color
        copied_vertices.push_back(new_vertex);
    }

    // Step 3: Copy neighbors
    auto new_it = copied_vertices.begin();
    for (auto old_it = other.m_vertices.begin(); old_it != other.m_vertices.end(); ++old_it, ++new_it) {
        for (auto neighbor_it = (*old_it)->m_neighbors.begin(); neighbor_it != (*old_it)->m_neighbors.end(); ++neighbor_it) {
            // Find the corresponding new vertex for the neighbor
            auto target_new = copied_vertices.begin();
            for (auto original = other.m_vertices.begin(); original != other.m_vertices.end(); ++original, ++target_new) {
                if ((*original)->id() == (*neighbor_it)->id()) {
                    (*new_it)->add_neighbor(*target_new);
                    break;
                }
            }
        }
    }
    m_vertices = std::move(copied_vertices);
}
Graph::Graph(Graph&& other) : m_vertices(std::move(other.m_vertices))
{
    // Clear the other graph
    other.m_vertices = List<Vertex*>();
}

Graph &Graph::operator=(const Graph &other)
{
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Clean up current graph
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        delete *it;
    }

    m_vertices = List<Vertex*>(); // Clear the list

    // Step 1: Create a map to associate old vertices with new vertices
    List<Vertex*> copied_vertices;

    // Step 2: Copy vertices
    for (auto it = other.m_vertices.begin(); it != other.m_vertices.end(); ++it) {
        Vertex* new_vertex = new Vertex((*it)->id());
        new_vertex->m_color = (*it)->color(); // Copy color
        copied_vertices.push_back(new_vertex);
    }

    // Step 3: Copy neighbors
    auto new_it = copied_vertices.begin();
    for (auto old_it = other.m_vertices.begin(); old_it != other.m_vertices.end(); ++old_it, ++new_it) {
        for (auto neighbor_it = (*old_it)->m_neighbors.begin(); neighbor_it != (*old_it)->m_neighbors.end(); ++neighbor_it) {
            // Find the corresponding new vertex for the neighbor
            auto target_new = copied_vertices.begin();
            for (auto original = other.m_vertices.begin(); original != other.m_vertices.end(); ++original, ++target_new) {
                if ((*original)->id() == (*neighbor_it)->id()) {
                    (*new_it)->add_neighbor(*target_new);
                    break;
                }
            }
        }
    }
    m_vertices = std::move(copied_vertices);
    return *this;
}

Graph &Graph::operator=(Graph &&other)
{
    if (this == &other) {
        return *this; // Handle self-assignment
    }

    // Clean up current graph
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        delete *it;
    }

    // Transfer ownership
    m_vertices = std::move(other.m_vertices);

    // Clear the other graph
    other.m_vertices = List<Vertex*>();

    return *this;
}

size_t Graph::add_vertex()
{
    // Determine the new vertex ID
    size_t new_id = m_vertices.size() + 1;

    // Create a new vertex with the determined ID
    Vertex* new_vertex = new Vertex(new_id);

    // Add the vertex to the list
    m_vertices.push_back(new_vertex);

    // Return the new vertex's ID
    return new_id;
}

Graph::Vertex* Graph::operator[](size_t id)
{
    // Traverse the list of vertices to find the one with the given ID
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        if ((*it)->id() == id) {
            return *it; // Return the vertex pointer
        }
    }

    // If no vertex with the given ID exists, throw an exception
    throw std::domain_error("Vertex with the given ID could not be found.");
}

void Graph::connect(size_t id1, size_t id2)
{
    // Get the vertices corresponding to the given IDs
    Vertex* vertex1 = (*this)[id1];
    Vertex* vertex2 = (*this)[id2];

    // Connect the two vertices as neighbors
    vertex1->add_neighbor(vertex2);
    vertex2->add_neighbor(vertex1);
}

int Graph::max_color() const
{
    int max_degree = 0;

    // Traverse all vertices
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        int degree = 0;

        // Count the number of neighbors for the current vertex
        for (auto neighbor_it = (*it)->m_neighbors.begin(); neighbor_it != (*it)->m_neighbors.end(); ++neighbor_it) {
            ++degree;
        }

        // Update max_degree if the current degree is higher
        if (degree > max_degree) {
            max_degree = degree;
        }
    }

    // Return max degree plus one
    return max_degree + 1;
}

bool Graph::color_helper(List<Vertex*>::Iterator vertex)
{
    // Step (a): If all vertices are processed, return true
    if (vertex == m_vertices.end()) {
        return true;
    }

    // Save the next iterator before any recursion
    auto next_vertex = vertex;
    ++next_vertex;

    // Step (b): If the current vertex is already colored, skip to the next one
    if ((*vertex)->color() != 0) {
        return color_helper(next_vertex); // Recurse with the next vertex
    }

    // Step (c): Try all possible colors
    int max_possible_color = max_color();
    for (int c = 1; c <= max_possible_color; ++c) {
        if ((*vertex)->color(c)) { // If the color is valid
            if (color_helper(next_vertex)) { // Recurse with the next vertex
                return true; // Successfully colored the rest of the graph
            }
        }
    }

    // Step (d): If no valid color is found, reset the color and return false
    (*vertex)->color(0);
    return false;
}

bool Graph::color()
{
    // Attempt to color the graph by calling color_helper for each vertex
    for (auto it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        // Only call color_helper if the vertex is not already colored
        if ((*it)->color() == 0) {
            if (!color_helper(it)) {
                return false; // Coloring failed for this subgraph
            }
        }
    }
    return true; // Successfully colored the entire graph
}