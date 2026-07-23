struct res_helper {
    uint32_t height;
    struct TreeNode* node;
};

static uint32_t dfs(const uint32_t h, struct TreeNode* node, struct res_helper* res)
{
    if (node == NULL) {
        return h;
    }

    const uint32_t h_left = dfs(h + 1, node->left, res);
    const uint32_t h_right = dfs(h + 1, node->right, res);
    if (h_left == h_right && h_left >= res->height) {
        res->height = h_left;
        res->node = node;
    }
    return h_left > h_right ? h_left : h_right;
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root)
{
    struct res_helper res = { .height = 0, .node = NULL};
    dfs(0, root, &res);
    return res.node;
}
