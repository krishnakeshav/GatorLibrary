
/**
 * @file redblack_tree.hpp
 * @class RBTree
 * @brief Header file for the RBTree class and RbtNode class.
 * 
 * This file defines the RBTree class and RbtNode class, which implement a red-black tree data structure.
 * The RBTree class provides methods for adding, removing, and finding nodes in the red-black tree.
 * The RbtNode class represents a node in the red-black tree and stores a key-value pair.
 */

#pragma once

#include <type_traits>
#include "book.hpp"

/// @brief Red-black tree type
#define rbtree RBTree

/// @brief Red-black tree node type
#define rbtnode RbtNode

using namespace std;

/**
 * @enum Color
 * @brief Represents the color of a node in the red-black tree.
 * 
 * The Color enum represents the color of a node in the red-black tree.
 * Each node can be either red or black.
 */
enum Color { RED, BLACK };

/**
 * @class RbtNode
 * @brief Represents a node in the red-black tree.
 * 
 * The RbtNode class represents a node in the red-black tree.
 * Each node stores a key-value pair and has pointers to its left child, right child, and parent nodes.
 * It also stores the color of the node.
 */
class RbtNode {
public:
    int key; /**< The key of the node. */
    book value; /**< The value associated with the key. */
    RbtNode *left; /**< Pointer to the left child node. */
    RbtNode *right; /**< Pointer to the right child node. */
    RbtNode *parent; /**< Pointer to the parent node. */
    Color color; /**< The color of the node. */

public:
    /**
     * @brief Constructs a new RbtNode object.
     * 
     * @param k The key of the node.
     * @param v The value associated with the key.
     */
    RbtNode(int k, const book& v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}

    /**
     * @brief Returns the sibling of the node.
     * 
     * @return Pointer to the sibling node.
     */
    RbtNode* sibling() const;
};

/**
 * @class RBTree
 * @brief Represents a red-black tree data structure.
 * 
 * The RBTree class represents a red-black tree data structure.
 * It provides methods for adding, removing, and finding nodes in the red-black tree.
 */
class RBTree
{
private:
    rbtnode *root; /**< Pointer to the root node of the red-black tree. */
    int color_flip_count; /**< The number of color flips performed during tree operations. */

    void rotate_left(rbtnode *&, rbtnode *&); /**< Performs a left rotation on the given nodes. */
    void rotate_right(rbtnode *&, rbtnode *&); /**< Performs a right rotation on the given nodes. */
    void fix_colorviolation(rbtnode *&, rbtnode *&); /**< Fixes the color violation after inserting a node. */

    rbtnode* insert_node(rbtnode* root_node, rbtnode* node); /**< Inserts a node into the red-black tree. */

    void remove(rbtnode* node); /**< Removes a node from the red-black tree. */

    rbtnode* BSTreplace(rbtnode* x); /**< Finds the node that can replace the given node in the red-black tree. */
    rbtnode* successor(rbtnode* x); /**< Finds the successor of the given node in the red-black tree. */
    void fix_double_black(rbtnode* node); /**< Fixes the double black violation after removing a node. */

public:
    /**
     * @brief Constructs a new RBTree object.
     */
    RBTree();

    /**
     * @brief Returns the number of color flips performed during tree operations.
     * 
     * @return The number of color flips.
     */
    int ColorFlipCount();

    /**
     * @brief Returns a pointer to the first node in the red-black tree.
     * 
     * @return Pointer to the first node.
     */
    rbtnode* begin();

    /**
     * @brief Returns a pointer to the end of the red-black tree.
     * 
     * @return Pointer to the end.
     */
    rbtnode* end();

    /**
     * @brief Adds a new book to the red-black tree.
     * 
     * @param book_info The book to add.
     */
    void add(book book_info);

    /**
     * @brief Removes a book from the red-black tree based on the given key.
     * 
     * @param key The key of the book to remove.
     */
    void remove(int key);

    /**
     * @brief Finds a book in the red-black tree based on the given key.
     * 
     * @param key The key of the book to find.
     * @return Pointer to the node containing the book, or nullptr if not found.
     */
    rbtnode* find(int key) const;

    /**
     * @brief Finds the closest book IDs to the given target ID in the red-black tree.
     * 
     * @param targetId The target book ID.
     * @return A vector of closest book IDs.
     */
    std::vector<int> findclosest(int targetId) const;

    /**
     * @brief Overloads the subscript operator to find a book in the red-black tree based on the given key.
     * 
     * @param key The key of the book to find.
     * @return Pointer to the node containing the book, or nullptr if not found.
     */
    rbtnode* operator[](int key) const;

    /**
     * @brief Checks if the red-black tree is empty.
     * 
     * @return True if the tree is empty, false otherwise.
     */
    bool empty() const;
};
