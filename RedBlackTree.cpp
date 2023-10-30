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

void RBTree::rotate_left(rbtnode *&root, rbtnode *&pt)
{
    rbtnode *pt_right = pt->right;
 
    pt->right = pt_right->left;
 
    if (pt->right != NULL)
        pt->right->parent = pt;
 
    pt_right->parent = pt->parent;
 
    if (pt->parent == NULL)
        root = pt_right;
 
    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
 
    else
        pt->parent->right = pt_right;
 
    pt_right->left = pt;
    pt->parent = pt_right;
}

void RBTree::rotate_right(rbtnode *&root, rbtnode *&pt)
{
    rbtnode *pt_left = pt->left;
 
    pt->left = pt_left->right;
 
    if (pt->left != NULL)
        pt->left->parent = pt;
 
    pt_left->parent = pt->parent;
 
    if (pt->parent == NULL)
        root = pt_left;
 
    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
 
    else
        pt->parent->right = pt_left;
 
    pt_left->right = pt;
    pt->parent = pt_left;
}

rbtnode* RBTree::insert_node(rbtnode* root_node, rbtnode* node)
{
    if (root_node == nullptr)
    {
        return node;
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

void RBTree::fix_colorviolation(rbtnode *&rootnode, rbtnode *&node)
{
    rbtnode* parent_node = NULL;
    rbtnode* grandparent = NULL;

// if node->color is red then node->parent->color is not evaluated
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
                    rotate_left(rootnode, parent_node);
                    node = parent_node;
                    parent_node = node->parent;
                }
                // if node is left child of parent, right rotation is required
                rotate_right(rootnode, grandparent);
                swap(parent_node->color, grandparent->color);
                node = parent_node;
            }
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
                    rotate_right(rootnode, parent_node);
                    node = parent_node;
                    parent_node = node->parent;
                }
                // if node is right child of parent, left rotation is required
                rotate_left(rootnode, grandparent);
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
