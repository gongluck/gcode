/*
 * @Author: gongluck 
 * @Date: 2020-09-06 16:15:44 
 * @Last Modified by: gongluck
 * @Last Modified time: 2020-09-06 17:03:54
 */

#include "../../errcode.h"

namespace galgorithm
{
    template <typename T>
    struct TreeNode
    {
        T value;
        TreeNode *left;
        TreeNode *right;
    };
    template <typename T>
    struct BTree
    {
        TreeNode<T> *root;
    };

    template <typename T>
    TreeNode<T> *CreateNode(T value)
    {
        auto node = static_cast<TreeNode<T>*>(malloc(sizeof(TreeNode<T>)));
        if (node == nullptr)
        {
            return nullptr;
        }

        node->value = value;
        node->left = node->right = nullptr;
        return node;
    }

    template <typename T>
    int Insert(BTree<T> *tree, T value)
    {
        if (tree == nullptr)
        {
            return G_ERROR_INVALIDPARAM;
        }

        if (tree->root == nullptr)
        {
            tree->root = CreateNode(value);
            return G_ERROR_SUCCEED;
        }

        auto node = tree->root;
        auto tmp = tree->root;
        while (node != nullptr)
        {
            tmp = node;
            if (value < node->value)
            {
                node = node->left;
            }
            else if(value > node->value)
            {
                node = node->right;
            }
            else
            {
                return G_ERROR_INVALIDPARAM;
            }
            
        }
        if (value < tmp->value)
        {
            tmp->left = CreateNode(value);
        }
        else if(value > tmp->value)
        {
            tmp->right = CreateNode(value);
        }

        return G_ERROR_SUCCEED;
    }

    template <typename T>
    int Traversal(TreeNode<T> *root, void (*func)(T *value), int type = 0)
    {
        if(root == nullptr)
        {
            return G_ERROR_SUCCEED;
        }

        if(type == 0)
        {
            func(&root->value);
        }
        Traversal(root->left, func);
        if(type == 1)
        {
            func(&root->value);
        }
        Traversal(root->right, func);
        if(type == 2)
        {
            func(&root->value);
        }
    }

} // namespace galgorithm