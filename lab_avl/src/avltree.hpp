/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{   
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }

}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t-> right;
    t -> right = tmp -> left;
    tmp -> left = t;
    t -> height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp;
    t -> height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)//LR
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* tmp = t-> left;
    t -> left = tmp -> right;
    tmp -> right = t;
    t -> height = 1 + std::max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = tmp;
    tmp -> height = 1 + std::max(heightOrNeg1(tmp->left), heightOrNeg1(tmp->right));

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)//RL
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}
/**
     * Rebalance a node by performing rotations. You can assume that node->left
     * and node->right are both balanced. Even if no rotations are required,
     * you should update the node's height.
     * @param node The node to balance.
     */
template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{   
    if(subtree == NULL) {
        return;
    }
    int bf = heightOrNeg1(subtree -> left)-heightOrNeg1(subtree -> right);
    // your code here
    if (bf== 1 || bf == -1) {
        //subtree -> height =  1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));
        return;
    } 
    if (bf == 2) { 
        // left tree longer, RR
        // sub-left & sub-right tree are balanced
        if (heightOrNeg1(subtree -> left -> right)<heightOrNeg1(subtree -> left -> left)) {
            rotateRight(subtree);
            //subtree -> height = 1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));
        } else {
            rotateLeftRight(subtree);
            //subtree -> height = 1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));
        }
    }
    if (bf == -2) {
        if (heightOrNeg1(subtree -> right -> right) > heightOrNeg1(subtree -> right -> left)) {
            rotateLeft(subtree);
            //subtree -> height = 1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));
        } else {
            rotateRightLeft(subtree);
            //subtree -> height = 1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));
        }
    }
    //subtree -> height = 1+std::max(heightOrNeg1(subtree -> left),heightOrNeg1(subtree -> right));

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);

}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
// BST insert first
    if (subtree == NULL) {
        Node* insert = new Node(key,value);
        subtree = insert;
    } else if (key < subtree -> key) {
        insert(subtree -> left, key, value);
    } else {
        insert(subtree -> right, key, value);
    }
    rebalance(subtree);
    
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));

}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);

}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree -> right, key);
    } else 
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = nullptr;
            return;
            

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* curr = subtree -> left;
            while(curr -> right != nullptr) {
                curr = curr -> right;
            }
            swap(subtree, curr);
            remove(subtree -> left,curr -> key);
            
        } else {
            /* one-child remove */
            // your code here
            Node* tmp = (subtree -> right == nullptr) ? subtree -> left : subtree ->right;
            swap(subtree,tmp);
            subtree -> right = tmp -> right;
            subtree -> left = tmp -> left;
            delete tmp;
            tmp = nullptr;
            
        }
        subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
        rebalance(subtree);
        // your code here
}
