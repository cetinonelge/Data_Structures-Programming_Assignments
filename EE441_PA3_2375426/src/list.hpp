#pragma once

#include <stdexcept>
#include "memory.hpp"

/*
    A doubly linked list implementation.
    This class provides functionalities to add, remove, and iterate over elements.
    Supports dynamic allocation and proper memory management.
*/

template <class T>
class List
{
private:
    struct Node
    {
        T m_data;
        Node* m_prev;
        Node* m_next;

        Node(T data) : m_data(data), m_prev(nullptr), m_next(nullptr) { }
    };

    Node* m_head;
    Node* m_tail;
    size_t m_size;

public:
    // Default constructor initializes an empty list
    List() : m_head(nullptr), m_tail(nullptr), m_size(0) { }

    // Destructor deletes all nodes in the list to free memory
    ~List()
    {
        Node* current = m_head;
        while (current) {
            Node* next = current->m_next;
            delete current;
            current = next;
        }
    }

    // Returns the size of the list
    size_t size() const {
        return m_size;
    }

    // Copy constructor creates a deep copy of the other list
    List(const List& other)
        : m_head(nullptr), m_tail(nullptr), m_size(0)
    {
        Node* current = other.m_head;
        while (current) {
            push_back(current->m_data);
            current = current->m_next;
        }
    }

    // Move constructor transfers ownership of nodes from another list
    List(List&& other)
        : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // Copy assignment operator creates a deep copy of the other list
    List& operator=(const List& other)
    {
        if (this == &other) return *this; // Handle self-assignment

        // Delete existing nodes
        Node* current = m_head;
        while (current) {
            Node* next = current->m_next;
            delete current;
            current = next;
        }

        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;

        // Copy nodes from the other list
        current = other.m_head;
        while (current) {
            push_back(current->m_data);
            current = current->m_next;
        }

        return *this;
    }

    // Move assignment operator transfers ownership of nodes from another list
    List& operator=(List&& other)
    {
        if (this == &other) return *this; // Handle self-assignment

        // Delete existing nodes
        Node* current = m_head;
        while (current) {
            Node* next = current->m_next;
            delete current;
            current = next;
        }

        // Transfer ownership
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_size = other.m_size;

        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;

        return *this;
    }

private:
    // Helper function for initializing the list with a single node
    inline void initiate(T data)
    {
        Node* newNode = new Node(data);
        m_head = m_tail = newNode;
        m_size = 1;
    }

    // Helper function for removing the only element in a list
    inline T deplete()
    {
        if (m_head != m_tail) {
            throw std::logic_error("deplete should only be called when size is 1.");
        }

        T data = m_head->m_data;
        delete m_head;
        m_head = m_tail = nullptr;
        m_size = 0;
        return data;
    }

    // Helper function to connect two nodes in the list
    static inline void hook(Node* prev, Node* next)
    {
        if (prev) prev->m_next = next;
        if (next) next->m_prev = prev;
    }

public:
    // Adds a new element to the end of the list
    void push_back(T data)
    {
        if (m_size == 0) {
            initiate(data);
        } else {
            Node* newNode = new Node(data);
            hook(m_tail, newNode);
            m_tail = newNode;
            ++m_size;
        }
    }

    // Adds a new element to the front of the list
    void push_front(T data)
    {
        if (m_size == 0) {
            initiate(data);
        } else {
            Node* newNode = new Node(data);
            hook(newNode, m_head);
            m_head = newNode;
            ++m_size;
        }
    }

    // Removes and returns the last element in the list
    T pop_back()
    {
        if (m_size == 0) {
            throw std::logic_error("Cannot pop from an empty list (pop_back).");
        }
        if (m_size == 1) {
            return deplete();
        }

        T data = m_tail->m_data;
        Node* prev = m_tail->m_prev;
        delete m_tail;
        m_tail = prev;
        m_tail->m_next = nullptr;
        --m_size;
        return data;
    }

    // Removes and returns the first element in the list
    T pop_front()
    {
        if (m_size == 0) {
            throw std::logic_error("Cannot pop from an empty list (pop_front).");
        }
        if (m_size == 1) {
            return deplete();
        }

        T data = m_head->m_data;
        Node* next = m_head->m_next;
        delete m_head;
        m_head = next;
        m_head->m_prev = nullptr;
        --m_size;
        return data;
    }

    // Iterator class for traversing the list
    class Iterator
    {
    private:
        Node* m_node;

        Iterator(Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(Iterator other) const
        {
            return m_node == other.m_node;
        }

        bool operator!=(Iterator other) const
        {
            return m_node != other.m_node;
        }

        T& operator*()
        {
            if (!m_node) {
                throw std::logic_error("Cannot dereference end iterator.");
            }
            return m_node->m_data;
        }

        Iterator next()
        {
            if (!m_node) {
                return Iterator(nullptr); // Return end iterator
            }
            return Iterator(m_node->m_next);
        }

        // Prefix increment operator
        Iterator operator++()
        {
            if (m_node) { // Increment only if the current node is valid
                m_node = m_node->m_next;
            }
            return *this;
        }
        // Postfix increment operator
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    // ConstIterator class for traversing the list without modification
    class ConstIterator
    {
    private:
        const Node* m_node;

        ConstIterator(const Node* node) : m_node(node) { }

        friend class List;

    public:
        bool operator==(ConstIterator other) const
        {
            return m_node == other.m_node;
        }

        bool operator!=(ConstIterator other) const
        {
            return m_node != other.m_node;
        }

        const T& operator*() const
        {
            if (!m_node) {
                throw std::logic_error("Cannot dereference end iterator. (const)");
            }
            return m_node->m_data;
        }

        ConstIterator next()
        {
            if (!m_node || !m_node->m_next) {
                throw std::range_error("Cannot obtain next iterator (const,next).");
            }
            return ConstIterator(m_node->m_next);
        }

        // Prefix increment operator
        ConstIterator operator++()
        {
            if (!m_node || !m_node->m_next) {
                throw std::range_error("Cannot increment iterator (const,prefix).");
            }
            m_node = m_node->m_next;
            return *this;
        }

        // Postfix increment operator
        ConstIterator operator++(int)
        {
            ConstIterator temp = *this;
            ++(*this);
            return temp;
        }
    };

    // Returns an iterator to the first element
    Iterator begin()
    {
        return Iterator(m_head);
    }

    // Returns an iterator to the end (null)
    Iterator end()
    {
        return Iterator(nullptr);
    }

    // Returns a const iterator to the first element
    ConstIterator begin() const
    {
        return ConstIterator(m_head);
    }

    // Returns a const iterator to the end (null)
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    // Inserts a new element before the given iterator
    Iterator insert(Iterator iter, T data)
    {
        if (iter == begin()) {
            push_front(data);
            return begin();
        }
        if (iter == end()) {
            push_back(data);
            Node* newNode = m_tail;
            return Iterator(newNode);
        }

        Node* nextNode = iter.m_node;
        Node* prevNode = nextNode->m_prev;

        Node* newNode = new Node(data);
        hook(prevNode, newNode);
        hook(newNode, nextNode);

        ++m_size;
        return Iterator(newNode);
    }

    // Removes the element at the given iterator
    Iterator remove(Iterator iter)
    {
        if (m_size == 0 || iter == end()) {
            throw std::logic_error("Cannot remove from an empty list or cannot remove the end iterator.");
        }

        Node* targetNode = iter.m_node;
        Node* prevNode = targetNode->m_prev;
        Node* nextNode = targetNode->m_next;

        hook(prevNode, nextNode);

        if (targetNode == m_head) {
            m_head = nextNode;
        }

        if (targetNode == m_tail) {
            m_tail = prevNode;
        }

        delete targetNode;
        --m_size;

        return Iterator(nextNode);
    }
};
