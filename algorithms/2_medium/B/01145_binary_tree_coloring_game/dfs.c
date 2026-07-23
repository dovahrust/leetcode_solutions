enum states {
    NOT_SEEN_X,
    LEFT_X,
    RIGHT_X,
};

struct res_tuple {
    int not_seen_x;
    int left_x;
    int right_x;
};

static void dfs(struct TreeNode* node, const int x, const enum states state, struct res_tuple* res)
{
    if (node == NULL) {
        return;
    }

    if (node->val != x) {
        switch (state) {
            case NOT_SEEN_X: 
                res->not_seen_x += 1;
                break;
            case LEFT_X:
                res->left_x += 1;
                break;
            case RIGHT_X:
                res->right_x += 1;
                break;
            default:
                break;
        }
        dfs(node->left, x, state, res);
        dfs(node->right, x, state, res);
    } else {
        dfs(node->left, x, LEFT_X, res);
        dfs(node->right, x, RIGHT_X, res);
    }
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool btreeGameWinningMove(struct TreeNode* root, int n, int x)
{
    struct res_tuple res = { .not_seen_x = 0, .left_x = 0, .right_x = 0};
    dfs(root, x, NOT_SEEN_X, &res);

    return res.not_seen_x > res.left_x + res.right_x ||
           res.left_x > res.not_seen_x + res.right_x ||
           res.right_x > res.not_seen_x + res.left_x;
}
