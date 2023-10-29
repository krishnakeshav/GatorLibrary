#pragma once

#include <type_traits>
#include "book.hpp"

#define rbtree RBTree
#define rbtnode RbtNode

using namespace std;

enum Color { RED, BLACK };
enum NodeLocation { LL, LR, RL, RR };

class RbtNode {
public:
    int key;
    book value;
    RbtNode *left;
    RbtNode *right;
    RbtNode *parent;
    Color color;

public:
    RbtNode(int k, const book& v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RBTree
{
    private:
        rbtnode* root;
        int color_flip_count;

        NodeLocation location;

        rbtnode* rotate_left(rbtnode* node);
        rbtnode* rotate_right(rbtnode* node);
        void fix_colorviolation(rbtnode* root_node, rbtnode* node);

        rbtnode* insert_node(rbtnode* root_node, rbtnode* node);

    public:
        RBTree();
        
        int ColorFlipCount();
        rbtnode* begin();
        rbtnode* end();

        void add(book book_info);
        void remove(int key);
        rbtnode* find(int key) const;

        // function to overload the operator []
        rbtnode* operator[](int key) const;
};
