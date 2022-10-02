/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{   
    if(find(root,key) == NULL) {
        return V();
    }
    return find(root, key) -> value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL || subtree -> key == key) {
        return subtree;
    }
    if (subtree -> key > key) {
        return find(subtree -> left, key);
    }
    return find(subtree -> right ,key);

}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL ) {
        subtree = new Node(key,value);
        return;
    }
    if (subtree -> key == key) {
        return;
    }
    if (subtree -> key > key) {
        return insert(subtree -> left, key, value);
    }
    return insert(subtree -> right, key ,value);
    
}

/*template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::findParent(Node*& subtree, const K& key){
    if (subtree -> left == key || subtree -> right == key) {
        return subtree;
    }
    if (subtree -> left)
}*/

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    if (first == second) {
        return;
    }
    K k = second -> key;
    V v = second -> value;
    second -> key = first -> key;
    second -> value = first -> value;
    //second -> left = first -> left;

    first -> key = k;
    first -> value = v;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    // in order predecessor: in the left subtree,the largest (the most right) node
    if(subtree == nullptr || find(subtree,key) == NULL) {
        return;
    }
    if(subtree -> key > key) {
        return remove(subtree -> left, key);
    } else if (subtree -> key < key) {
        return remove(subtree -> right ,key);
    } else {
        // 0 child
        if (subtree -> left == NULL && subtree -> right == NULL) {
            delete subtree;
            subtree = nullptr;
            return;
        }
        // 1 child
        if (subtree -> left != nullptr && subtree -> right == nullptr) {
            Node* tmp = subtree -> left;
            swap(subtree,tmp);
            subtree -> left = tmp -> left;
            subtree -> right = tmp -> right;
            delete tmp;
            tmp = nullptr;
            return;
        }
        // 1 child
        if (subtree -> left == nullptr && subtree -> right != nullptr) {
            Node* tmp = subtree -> right;
            swap(subtree,tmp);
            subtree -> right = tmp -> right;
            subtree -> left = tmp -> left;
            delete tmp;
            tmp = nullptr;
            return;
        }
        // 2 child
        if (subtree -> left != nullptr && subtree -> right != nullptr) {
            Node* curr = subtree -> left;
            Node* tmp;
            while(curr -> right != nullptr) {
                tmp = curr;
                curr = curr -> right;
            }
            swap(subtree, curr);
            remove(subtree -> left,curr -> key);
            return;
            
        }
    }

}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> tree;
    if (inList.empty()) {
        return tree;
    }
    for (unsigned i = 0; i < inList.size(); i++) {
        std::pair<K,V> use = inList[i];
        tree.insert(use.first, use.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> h;
    h.push_back(0);
    int t_size;
    std::sort(inList.begin(),inList.end());
    while (std::next_permutation(inList.begin(), inList.end())) {
        //BST<K,V> tree;
        //tree = listBuild(inList);
        t_size = listBuild(inList).height();
        if (t_size + 1 > (int)h.size()) {
            h.resize(t_size + 1,0);
            h[t_size] = 1;
        } else {
            h[t_size]++;
        }
    }
    h[t_size] ++;
    return h;
    

}