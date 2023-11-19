#include "redblack_tree.hpp"

using namespace std;

RbtNode* RbtNode::sibling() const
{
    if (parent == nullptr)
    {
        return nullptr;
    }
    if (this == parent->left)
    {
        return parent->right;
    }
    else
    {
        return parent->left;
    }
}

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
                color_flip_count += (grandparent->color != RED);
                grandparent->color = RED;

                color_flip_count += (parent_node->color != BLACK);
                parent_node->color = BLACK;
                
                color_flip_count += (uncle->color != BLACK);
                uncle->color = BLACK;
                
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
                
                Color pcolor = parent_node->color;
                Color gcolor = grandparent->color;
                swap(parent_node->color, grandparent->color);
                color_flip_count += (pcolor != parent_node->color);
                color_flip_count += (gcolor != grandparent->color);

                node = parent_node;
            }
        }
        // parent is right child of grandparent
        else
        {
            rbtnode* uncle = grandparent->left;
            // uncle of parent is also red, only recoloring is required
            if (uncle != nullptr && uncle->color == Color::RED)
            {
                color_flip_count += (grandparent->color != RED);
                grandparent->color = Color::RED;

                color_flip_count += (parent_node->color != BLACK);
                parent_node->color = Color::BLACK;

                color_flip_count += (uncle->color != BLACK);
                uncle->color = Color::BLACK;

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
                
                Color pcolor = parent_node->color;
                Color gcolor = grandparent->color;
                swap(parent_node->color, grandparent->color);
                color_flip_count += (pcolor != parent_node->color);
                color_flip_count += (gcolor != grandparent->color);

                node = parent_node;
            }
        }
    }
    
    color_flip_count += (rootnode->color != BLACK);
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
    return current;
}

std::vector<int> RBTree::findclosest(int targetId) const
{
    std::vector<int> closestBooks;
    rbtnode* current = root;

    while (current != nullptr)
    {
        if (current->key == targetId)
        {
            closestBooks.push_back(current->key);
            break; // No need to search further if an exact match is found
        }
        else
        {
            // Update closestNodes based on the current node
            if (closestBooks.empty() || std::abs(current->key - targetId) < std::abs(closestBooks[0] - targetId))
            {
                closestBooks.clear();
                closestBooks.push_back(current->key);
            }
            else if (std::abs(current->key - targetId) == std::abs(closestBooks[0] - targetId))
            {
                // Handle ties by adding the current node to closestNodes
                closestBooks.push_back(current->key);
            }

            if (targetId < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
    }
    return closestBooks;
}

rbtnode* RBTree::successor(rbtnode *x)
{
    rbtnode *temp = x;
 
    while (temp->left != NULL)
      temp = temp->left;
 
    return temp;
}

rbtnode* RBTree::BSTreplace(rbtnode *x)
{
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
        return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
        return NULL;

    // when single child
    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

void RBTree::fix_double_black(rbtnode *node)
{
    if (node == root)
        return;
    rbtnode* sibling = NULL;
    rbtnode* parent = node->parent;
    if (parent->left == node)
        sibling = parent->right;
    else
        sibling = parent->left;
    if (sibling == NULL)
    {
        fix_double_black(parent);
    }
    else
    {
        if (sibling->color == RED)
        {
            Color last_color = parent->color;
            parent->color = RED;
            color_flip_count += (last_color != parent->color);

            sibling->color = BLACK;
            color_flip_count++;

            if (sibling->parent->left == sibling)
                rotate_right(root, parent);
            else
                rotate_left(root, parent);
            fix_double_black(node);
        }
        else
        {
            if ((sibling->left != NULL and sibling->left->color == RED) or
                (sibling->right != NULL and sibling->right->color == RED))
            {
                if (sibling->left != NULL and sibling->left->color == RED)
                {
                    if (sibling->parent->left == sibling)
                    {
                        // increment first here because color value is modified in next line
                        color_flip_count += (sibling->left->color != sibling->color);
                        sibling->left->color = sibling->color;

                        color_flip_count += (sibling->color != parent->color);
                        sibling->color = parent->color;
                        rotate_right(root, parent);
                    }
                    else
                    {
                        color_flip_count += (sibling->left->color != parent->color);
                        sibling->left->color = parent->color;

                        rotate_right(root, sibling);
                        rotate_left(root, parent);
                    }
                }
                else
                {
                    if (sibling->parent->left == sibling)
                    {
                        color_flip_count += (sibling->right->color != parent->color);
                        sibling->right->color = parent->color;

                        rotate_left(root, sibling);
                        rotate_right(root, parent);
                    }
                    else
                    {
                        color_flip_count += (sibling->right->color != sibling->color);
                        sibling->right->color = sibling->color;

                        color_flip_count += (sibling->color != parent->color);
                        sibling->color = parent->color;

                        rotate_left(root, parent);
                    }
                }
                color_flip_count += (parent->color != BLACK);
                parent->color = BLACK;
            }
            else
            {
                color_flip_count += (sibling->color != RED);
                sibling->color = RED;

                if (parent->color == BLACK)
                    fix_double_black(parent);
                else
                {
                    color_flip_count += (parent->color != BLACK);
                    parent->color = Color::BLACK;
                }
            }
        }
    }
}

void RBTree::remove(rbtnode* node)
{
    rbtnode *u = BSTreplace(node);
    bool uvBlack = ((u == nullptr or u->color == BLACK) and (node->color == BLACK));
    rbtnode *parent = node->parent;

    if(u == NULL)
    {
        if (node == root)
        {
            root = NULL;
        }
        else
        {
            if (uvBlack)
            {
                fix_double_black(node);
            }
            else
            {
                if (node->sibling() != NULL)
                {
                    node->sibling()->color = RED;
                }
            }
            if(node == parent->left)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
        }
        delete node;
        return;
    }
    if (node->left == NULL or node->right == NULL)
    {
        if (node == root)
        {
            node->key = u->key;
            node->value = u->value;
            delete u;
        }
        else
        {
            if (node == parent->left)
            {
                parent->left = u;
            }
            else
            {
                parent->right = u;
            }
            delete node;
            u->parent = parent;
            if (uvBlack)
            {
                fix_double_black(u);
            }
            else
            {
                color_flip_count += (u->color != BLACK);
                u->color = Color::BLACK;

            }
        }
        return;
    }
    swap(u->value, node->value);
    int tmp = u->key;
    u->key = node->key;
    node->key = tmp;
    remove(u);
}

void RBTree::remove(int key)
{
    rbtnode *node = find(key);
    if (node == nullptr)
    {
        cout << "Book Id " << key << " not found in library" << endl;
        return;
    }
    remove(node);
}

rbtnode* RBTree::operator[](int key) const
{
    rbtnode *node = find(key);
    return node;
}

bool RBTree::empty() const
{
    return root == nullptr;
}
