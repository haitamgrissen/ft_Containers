
#pragma once

# include <iostream>
# include "pair.hpp"

namespace ft {


    template<class Key, class T>
    struct node
    {
        node* left;
        node* right;
        node* parent;
        pair<const Key, T> *data;
        int height;
    };

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
    class AVL
    {
        private :
            typedef node< Key, T>                                           node;
            typedef pair< const Key, T >                                    pair;
            typedef typename Alloc::template rebind<node>::other            rebind_allocator;
            typedef typename Alloc::template rebind<pair>::other            _allocator;
            rebind_allocator                                                _NodeAlloc;
            _allocator                                                      _PairAlloc;
            Compare                                                         _cmp;
        public: 

        AVL(rebind_allocator rebind = rebind_allocator(), _allocator alloc = _allocator(), Compare _c = Compare())
        {
            _NodeAlloc = rebind;
            _PairAlloc = alloc;
            _cmp = _c;
        }
        ~AVL() { }
        int max( int a, int b) { return a > b ?  a : b; }
       
    /*
        // Function to update the height of
        // a node according to its children's
        // node's heights
    */
        void Updateheight(node* root)
        {
            if (root != NULL) {
        
                // Store the height of the
                // current node
                int val = 1;
        
                // Store the height of the left
                // and right substree
                if (root->left != NULL)
                    val = root->left->height + 1;
        
                if (root->right != NULL)
                    val = max(val, root->right->height + 1);
        
                // Update the height of the
                // current node
                root->height = val;
            }
        }
        
        node* LLR(node* root) {
            // Create a reference to the
            // left child
            node* tmpnode = root->left;

            // Update the left child of the
            // root to the right child of the
            // current left child of the root
            root->left = tmpnode->right;

            // Update parent pointer of the
            // left child of the root node
            if (tmpnode->right != NULL)
                tmpnode->right->parent = root;

            // Update the right child of
            // tmpnode to root
            tmpnode->right = root;

            // Update parent pointer of
            // the tmpnode
            tmpnode->parent = root->parent;

            // Update the parent pointer
            // of the root
            root->parent = tmpnode;

            // Update tmpnode as the left or the
            // right child of its parent pointer
            // according to its key value
            if (tmpnode->parent != NULL && _cmp(root->data->first, tmpnode->parent->data->first)) {
                tmpnode->parent->left = tmpnode;
            }
            else {
                if (tmpnode->parent != NULL)
                    tmpnode->parent->right = tmpnode;
            }

            // Make tmpnode as the new root
            root = tmpnode;

            // Update the heights
            Updateheight(root->left);
            Updateheight(root->right);
            Updateheight(root);
            Updateheight(root->parent);

            // Return the root node
            return root;
        }

        // Function to handle Right Right Case
        node* RRR(node* root) {
            // Create a reference to the
            // right child
            node* tmpnode = root->right;

            // Update the right child of the
            // root as the left child of the
            // current right child of the root
            root->right = tmpnode->left;

            // Update parent pointer of the
            // right child of the root node
            if (tmpnode->left != NULL)
                tmpnode->left->parent = root;

            // Update the left child of the
            // tmpnode to root
            tmpnode->left = root;

            // Update parent pointer of
            // the tmpnode
            tmpnode->parent = root->parent;

            // Update the parent pointer
            // of the root
            root->parent = tmpnode;

            // Update tmpnode as the left or
            // the right child of its parent
            // pointer according to its key value
            if (tmpnode->parent != NULL && _cmp(root->data->first, tmpnode->parent->data->first)) {
                tmpnode->parent->left = tmpnode;
            }
            else {
                if (tmpnode->parent != NULL)
                    tmpnode->parent->right = tmpnode;
            }

            // Make tmpnode as the new root
            root = tmpnode;

            // Update the heights
            Updateheight(root->left);
            Updateheight(root->right);
            Updateheight(root);
            Updateheight(root->parent);

            // Return the root node
            return root;
        }

        // Function to handle Left Right Case
        node* LRR( node* root ) {
            
            root->left = RRR(root->left);
            return LLR(root);
        }

        // Function to handle right left case
        node* RLR( node* root ) {
        
            root->right = LLR(root->right);
            return RRR(root);
        }

        // Function to balance the tree after
        // deletion of a node
        node* Balance(node* root)
        {
            // Store the current height of
            // the left and right subtree
            int firstheight = 0;
            int secondheight = 0;
        
            if (root->left != NULL)
                firstheight = root->left->height;
        
            if (root->right != NULL)
                secondheight = root->right->height;
        
            // If current node is not balanced
            if (abs(firstheight - secondheight) == 2) {
                if (firstheight < secondheight) {
        
                    // Store the height of the
                    // left and right subtree
                    // of the current node's
                    // right subtree
                    int rightheight1 = 0;
                    int rightheight2 = 0;
                    if (root->right->right != NULL)
                        rightheight2 = root->right->right->height;
        
                    if (root->right->left != NULL)
                        rightheight1 = root->right->left->height;
        
                    if (rightheight1 > rightheight2) {
        
                        // Right Left Case
                        root = RLR(root);
                    }
                    else {
        
                        // Right Right Case
                        root = RRR(root);
                    }
                }
                else {
        
                    // Store the height of the
                    // left and right subtree
                    // of the current node's
                    // left subtree
                    int leftheight1 = 0;
                    int leftheight2 = 0;
                
                    if (root->left->right != NULL)
                        leftheight2 = root->left->right->height;
        
                    if (root->left->left != NULL)
                        leftheight1 = root->left->left->height;
                    if (leftheight1 > leftheight2)
                        root = LLR(root);
                    else
                        root = LRR(root);
                }
            }
        
            // Return the root node
            return root;
        }
        node *TreeMinimum(node *root) const  {
        
            node *tmp = root;
                
            if (tmp)
                while (tmp->left != NULL)
                    tmp = tmp->left;
            return tmp;
        }
        node *find(node *node, Key key) const {
        
            if (node == nullptr)
                return nullptr;
            if (!_cmp(node->data->first, key) && !_cmp(key, node->data->first))
                return node;
            else if (!_cmp(node->data->first, key)) {
                return find(node->left, key);
            }
            else if (_cmp(node->data->first, key)) {
                return find(node->right, key);
            }
            return node;
        }

        node *lowerBound(node *root, const Key &k) const {
        
            node * result = NULL;
        
            while (root != nullptr)
            {
                if (!_cmp(root->data->first, k))
                {
                    result = root;
                    root = root->left;
                }
                else
                    root = root->right;
            }
            return result;
        }

        node *treeMaximum(node *x) const  {
        
            if (x == NULL)
                return NULL;
            while (x->right != NULL)
                x = x->right;
            return x;
        }
        node *treeMinimum(node *x) const {
        
            if (x == NULL)
                return NULL;
            while (x->left != NULL)
                x = x->left;
            return x;
        }

        node *treeSuccessor(node *x)  const {
        
            if (x == NULL)
                return x;
            if (x->right != NULL)
                return treeMinimum(x->right);
            node *y = x->parent;
            while (y != NULL && (x == y->right)) {
            
                x = y;
                y = y->parent;
            }
            return y;
        }
        node *treePredecessor(node *x) const  {

            if (x == NULL)
                return x;
            if (x->left != NULL)
                return treeMaximum(x->left);
            node *y = x->parent;
            while (y != NULL && (x == y->left)) {
            
                x = y;
                y = y->parent;
            }
            return y;
        }
        node *upperBound(node *root, const Key &k) const  {

            node * result = nullptr;
        
            while (root != nullptr)
            {
                if (_cmp(k, root->data->first))
                {
                    result = root;
                    root = root->left;
                }
                else
                    root = root->right;
            }
            return result;
        }

        node *TreeMaximum(node *root) const  {
        
            node *tmp = root;
                
            if (tmp)

                while (tmp->right != NULL)
                    tmp = tmp->right;
            return tmp;
        }
        
        node* Insert(node* root, node* parent, pair key)
        {
            if (root == NULL) {
        
                root = _NodeAlloc.allocate(1);
                root->data = _PairAlloc.allocate(1);
                _PairAlloc.construct(root->data, key);
                root->height = 1;
                root->left = NULL;
                root->right = NULL;
                root->parent = parent;

                return root;
            }
            else if (!_cmp(root->data->first, key.first)) {
        
                // Recur to the left subtree
                // to insert the node
                root->left = Insert(root->left, root, key);
        
                // Store the heights of the
                // left and right subtree
                int firstheight = 0;
                int secondheight = 0;
        
                if (root->left != NULL)
                    firstheight = root->left->height;
        
                if (root->right != NULL)
                    secondheight = root->right->height;
        
                // Balance the tree if the
                // current node is not balanced
                if (abs(firstheight - secondheight) == 2) {
        
                    if (root->left != NULL && _cmp(key.first, root->left->data->first))
                        root = LLR(root);
                    else
                        root = LRR(root);
                }
            }
            else if (_cmp(root->data->first, key.first)) {
        
                // Recur to the right subtree
                // to insert the node
                root->right = Insert(root->right, root, key);
        
                // Store the heights of the left
                // and right subtree
                int firstheight = 0;
                int secondheight = 0;
        
                if (root->left != NULL)
                    firstheight = root->left->height;
        
                if (root->right != NULL)
                    secondheight = root->right->height;
        
                // Balance the tree if the
                // current node is not balanced
                if (abs(firstheight - secondheight) == 2) {
                    if (root->right != NULL  && _cmp(key.first, root->right->data->first))
                        root = RLR(root);
                    else
                        root = RRR(root);
                }
            }
        
            // Case when given key is
            // already in tree
            else {
                return root;
            }
        
            // Update the height of the
            // root node
            Updateheight(root);
        
            // Return the root node
            return root;
        }
    
        // Function to delete a node from
        // the AVL tree
        node* Delete(node* root, pair key, int *found)
        {
            if (root != NULL) {
        
                // If the node is found
                if (root->data->first == key.first) {
        
                    // Replace root with its
                    // left child
                    if (root->right == NULL && root->left != NULL) {
                        
                        if (root->parent != NULL) {
                            
                            if (_cmp(root->parent->data->first, root->data->first)) {
                                _PairAlloc.destroy(root->parent->right->data);
                                _PairAlloc.deallocate(root->parent->right->data, 1);
                                _NodeAlloc.destroy(root->parent->right);
                                _NodeAlloc.deallocate(root->parent->right, 1);
                                root->parent->right = root->left;
                            }
                            else {
                                _PairAlloc.destroy(root->parent->left->data);
                                _PairAlloc.deallocate(root->parent->left->data, 1);
                                _NodeAlloc.destroy(root->parent->left);
                                _NodeAlloc.deallocate(root->parent->left, 1);
                                root->parent->left = root->left;
                            }
                            // Update the height
                            // of root's parent
                            Updateheight(root->parent);
                        }
                        root->left->parent = root->parent;
        

                        // Balance the node
                        // after deletion
                        root->left = Balance(root->left);
        
                        return root->left;
                    }
        
                    // Replace root with its
                    // right child
                    else if (root->left == NULL && root->right != NULL) {
                    
                        if (root->parent != NULL) {
                        
                            if (_cmp(root->parent->data->first, root->data->first)) {
                                root->parent->right = root->right;
                            }
                            else {
                                root->parent->left = root->right;
                            }
        
                            // Update the height
                            // of the root's parent
                            Updateheight(root->parent);
                        }
                        root->right->parent = root->parent;
        
                        // Balance the node after
                        // deletion
                        root->right = Balance(root->right);
                        return root->right;
                    }
        
                    // Remove the references of
                    // the current node
                    else if (root->left == NULL && root->right == NULL) {
                        
                        if (root->parent && _cmp(root->parent->data->first, root->data->first)) {
                            root->parent->right = NULL;
                        }
                        else  if (root->parent != NULL) {
                            root->parent->left = NULL;
                        }
                    
                        if (root->parent != NULL)
                            Updateheight(root->parent);
                        return NULL;
                    }
        
                    // Otherwise, replace the
                    // current node with its
                    // successor and then
                    // recursively call Delete()
                    else {
                        node* tmpnode;
                        tmpnode = root->right;
                        while (tmpnode->left != NULL) {
                            tmpnode = tmpnode->left;
                        }
        
                        pair  *val = tmpnode->data;
        
                        root->right = Delete(root->right, *tmpnode->data, found);
                        root->data = val;

                        // Balance the node
                        // after deletion
                        root = Balance(root);
                    }
                }
        
                // Recur to the right subtree to
                // delete the current node
                else if (_cmp(root->data->first, key.first)) {

                    root->right = Delete(root->right, key, found);
                    root = Balance(root);
                }
        
                // Recur into the right subtree
                // to delete the current node
                else if (!_cmp(root->data->first, key.first)) {
                    root->left = Delete(root->left, key, found);
        
                    root = Balance(root);
                }
        
                // Update height of the root
                if (root != NULL) {
                    Updateheight(root);
                }
            }
            else {
                *found = 0;
            }
            return root;
        }

        node*    DeleteAll(node * root)
        {
        
            if (root != NULL) {
            
                DeleteAll(root->right);
                DeleteAll(root->left);

                _PairAlloc.destroy(root->data);
                _PairAlloc.deallocate(root->data, 1);
                _NodeAlloc.destroy(root);
                _NodeAlloc.deallocate(root, 1);
            }
            return NULL;
        }
    };
}