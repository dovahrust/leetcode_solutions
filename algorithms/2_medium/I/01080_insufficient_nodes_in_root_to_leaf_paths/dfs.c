/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static bool dfs(struct TreeNode* node, const int parent_sum, const int limit);

struct TreeNode* sufficientSubset(struct TreeNode* root, const int limit)
{
    if (root == NULL) {
        return NULL;
    }

    const bool should_delete_root = dfs(root, 0, limit);
    if (should_delete_root) {
        free(root);
        return NULL;
    }

    return root;
}


static bool dfs(struct TreeNode* node, const int parent_sum, const int limit)
{
    assert(node != NULL);
    const int new_sum = parent_sum + node->val;

    if (node->left != NULL && node->right != NULL) {
        const bool should_delete_left = dfs(node->left, new_sum, limit);
        const bool should_delete_right = dfs(node->right, new_sum, limit);

        if (should_delete_left) {
            free(node->left);
            node->left = NULL;
        }

        if (should_delete_right) {
            free(node->right);
            node->right = NULL;
        }

        return should_delete_left && should_delete_right;
    } else if (node->left != NULL) {
        const bool should_delete_left = dfs(node->left, new_sum, limit);

        if (should_delete_left) {
            free(node->left);
            node->left = NULL;
        }

        return should_delete_left;
    } else if (node->right != NULL) {
        const bool should_delete_right = dfs(node->right, new_sum, limit);

        if (should_delete_right) {
            free(node->right);
            node->right = NULL;
        }

        return should_delete_right;
    } else {
        return new_sum < limit;
    }
}
