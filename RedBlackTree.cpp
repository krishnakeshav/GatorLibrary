#include "RedBlackTree.hpp"

using namespace std;

RBTree::RBTree()
{
    root = nullptr;
    color_flip_count = 0;
}

int RBTree::ColorFlipCount()
{
    return color_flip_count;
}

rbtnode* RBTree::rotate_left(rbtnode* node)
{
    rbtnode* parent_node = node->right;
    rbtnode* x = parent_node->right;
    rbtnode* y = parent_node->left;
    
    parent_node->left = node;
    
    node->right = y;
    node->parent = parent_node;
    
    if (y != nullptr)
    {
        y->parent = node;
    }
    return parent_node;
}

rbtnode* RBTree::rotate_right(rbtnode* node)
{
    rbtnode* parent_node = node->left;
    rbtnode* x = parent_node->left;
    rbtnode* y = parent_node->right;
    
    parent_node->right = node;
    
    node->left = y;
    node->parent = parent_node;
    
    if (y != nullptr)
    {
        y->parent = node;
    }
    return parent_node;
}

rbtnode* RBTree::insert_node(rbtnode* root_node, rbtnode* node)
{
    if (root_node == nullptr)
    {
        root_node = node;
        return root_node;
    }
    if (node->key > root_node->key)
    {
        root_node->right = insert_node(root_node->right, node);
        root_node->right->parent = root_node;
    }
    else
    {
        root_node->left = insert_node(root_node->left, node);
        root_node->left->parent = root_node;
    }
    return root_node;
}

void RBTree::fix_colorviolation(rbtnode* rootnode, rbtnode* node)
{
    rbtnode* parent_node = NULL;
    rbtnode* grandparent = NULL;

// fix the condition such that if node->color is red then node->parent->color is not evaluated
    while ((node != rootnode) && (node->color != BLACK) && (node->parent->color == RED))
    {
        parent_node = node->parent;
        grandparent = node->parent->parent;
        
        // if parent is left child of grandparent
        if (parent_node == grandparent->left)
        {
            rbtnode* uncle = grandparent->right;
            
            // if uncle is also red, only recoloring is required
            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent_node->color = BLACK;
                uncle->color = BLACK;
                color_flip_count ++;
                node = grandparent;
            }
            else
            {
                // if node is right child of parent, left rotation is required
                if (node == parent_node->right)
                {
                    rotate_left(node);
                    node = parent_node;
                    parent_node = node->parent;
                }
                // if node is left child of parent, right rotation is required
                rotate_right(node);
                swap(parent_node->color, grandparent->color);
                node = parent_node;
            }
            // if node is left child of a parent
            rotate_right(node);
            swap(parent_node->color, grandparent->color);
            node = parent_node;
        }
        // parent is right child of grandparent
        else
        {
            rbtnode* uncle = grandparent->left;
            // uncle of parent is also red, only recoloring is required
            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent_node->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            }
            else
            {
                // if node is left child of parent, right rotation is required
                if (node == parent_node->left)
                {
                    rotate_right(node);
                    node = parent_node;
                    parent_node = node->parent;
                }
                // if node is right child of parent, left rotation is required
                rotate_left(node);
                swap(parent_node->color, grandparent->color);
                node = parent_node;
            }
        }
    }
    rootnode->color = BLACK;
}

void RBTree::add(book book_info)
{
    rbtnode* node = new rbtnode(book_info.BookId, book_info);
    root = insert_node(root, node);
    fix_colorviolation(root, node);
}

rbtnode* RBTree::find(int key) const
{
    rbtnode *current = root;
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current;
        }
        else if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

rbtnode* RBTree::operator[](int key) const
{
    rbtnode *node = find(key);
    return node;
}
