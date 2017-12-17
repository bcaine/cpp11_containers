/**
 * @file BinaryTree.h
 *
 * @breif A very simple implementation of a Binary Tree in C++11
 *
 * @date 12/16/17
 * @author Ben Caine
 */

#ifndef TREESEARCH_BINARYTREE_H
#define TREESEARCH_BINARYTREE_H

#include <memory>

namespace trees {
/**
 * @brief A node class containing our key
 * @tparam T: The type of our key
 * @tparam Data: The type of our data stored in the node
 */
    template<typename T, typename Data>
    struct Node {
        T key;                       ///< The key position
        Data value;                  ///< The data contained in the node
        std::shared_ptr<Node> left;  ///< A pointer to the left node
        std::shared_ptr<Node> right; ///< A pointer to the right node
    };

/**
 * @brief A simple Binary Tree implementation
 * @tparam T: The type of our key
 * @tparam Data: The type of our data stored in the node
 */
    template<typename T, typename Data>
    class BinaryTree {
    public:
        /**
         * @breif A basic binary tree implementation
         */
        BinaryTree() :
                m_root(nullptr) {}

        /**
         * @brief Insert a key
         * @param key [in]: The key idx
         */
        void insert(T key, Data value);

        /**
         * @brief Search for a specific key
         * @param key [in]: The key to search for
         * @return The requested node
         */
        std::shared_ptr<Node<T, Data>> search(T key);

        /**
         * @brief Return the root of the tree
         * @return A shared ptr to the root of the tree
         */
        std::shared_ptr<Node<T, Data>> getRoot() { return m_root; }

        /**
         * @brief Get the max depth of the tree
         * @return The max depth of the tree
         */
        int getMaxDepth();

    private:
        /**
         * @brief Helper function to insert key
         * @param key [in]: Key to insert
         * @param value [in]: Data to insert into the node
         * @param node [in]: The current node (containing a subtree) to insert into
         */
        void insert(T key, Data value, std::shared_ptr<Node<T, Data>> node);

        /**
         * @brief Helper function to search the tree
         * @param key [in]: The key to search for
         * @param node [in]: The node (containing a subtree) to search through
         */
        std::shared_ptr<Node<T, Data>> search(T key, std::shared_ptr<Node<T, Data>> node);

        /**
         * @brief Helper function to get max depth of tree
         * @param node [in]: The current node (containing a subtree) to recurse through
         * @return
         */
        int getMaxDepth(std::shared_ptr<Node<T, Data>> node);

        /// Members
        std::shared_ptr<Node<T, Data>> m_root; ///< The root of the tree
    };

    template<typename T, typename Data>
    void BinaryTree<T, Data>::insert(T key, Data value) {
        if (m_root) {
            insert(key, value, m_root);
        } else {
            m_root.reset(new Node<T, Data>{key, value, nullptr, nullptr});
        }
    }

    template<typename T, typename Data>
    void BinaryTree<T, Data>::insert(T key, Data value, std::shared_ptr<Node<T, Data>> node) {
        if (key < node->key) {
            // Insert left
            if (node->left) {
                insert(key, value, node->left);
            } else {
                node->left.reset(new Node<T, Data>{key, value, nullptr, nullptr});
            }
        } else {
            // Insert right
            if (node->right) {
                insert(key, value, node->right);
            } else {
                node->right.reset(new Node<T, Data>{key, value, nullptr, nullptr});
            }
        }
    }

    template<typename T, typename Data>
    std::shared_ptr<Node<T, Data>> BinaryTree<T, Data>::search(T key) {
        if (m_root) {
            return search(key, m_root);
        } else {
            return {};
        }
    }

    template<typename T, typename Data>
    std::shared_ptr<Node<T, Data>> BinaryTree<T, Data>::search(T key, std::shared_ptr<Node<T, Data>> node) {
        if (!node) {
            return {};
        }

        if (key == node->key) {
            return node;
        }

        if (key < node->key) {
            return search(key, node->left);
        } else {
            return search(key, node->right);
        }
    }

    template<typename T, typename Data>
    int BinaryTree<T, Data>::getMaxDepth() {
        return getMaxDepth(m_root);
    }

    template<typename T, typename Data>
    int BinaryTree<T, Data>::getMaxDepth(std::shared_ptr<Node<T, Data>> node) {
        if (!node) {
            return 0;
        }

        return std::max(getMaxDepth(node->left), getMaxDepth(node->right)) + 1;
    }
}

#endif //TREESEARCH_BINARYTREE_H
