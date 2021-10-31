/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

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
    Node * y = t->right;
    t->right = y->left;
    y->left = t;
    y->height = newHeight(y);
    t->height = newHeight(t);
    t = y;
}

template <class K, class V>
int AVLTree<K, V>::newHeight(Node*& subtree) {
  return (1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
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
    Node * y = t->left;
    t->left = y->right;
    y->right = t;
    y->height = newHeight(y);
    t->height = newHeight(t);
    t = y;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if (subtree == NULL) {
        return;
    }

    if ((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) >= 2) {
        int right_side = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (right_side >= 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
    } else if ((heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left)) <= -2) {
        int left_side = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (left_side <= -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
    }
    subtree->height = newHeight(subtree);
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
    if (subtree == NULL) {
        Node * temp = new Node(key, value);
        subtree = temp;
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    }  else if (key > subtree->key) {
        insert(subtree->right, key, value);        
    } else if(key == subtree->key) {
        subtree->value = value;
        return;
    }
    rebalance(subtree);
    subtree->height = newHeight(subtree);
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
        remove(subtree->left, key);

    } else if (key > subtree->key) {
        remove(subtree->right, key);

    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * temp = subtree->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            swap(subtree, temp);
            remove(subtree->left, key);

        } else {
            /* one-child remove */
            // your code here
            Node * temp;
            if (subtree->left != NULL) {
                temp = subtree->left;
            } else {
                temp = subtree->right;
            }
            delete subtree;
            subtree = temp;

        }
    }
    subtree->height = newHeight(subtree);
    rebalance(subtree);
}

