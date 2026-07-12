/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

typedef ptrdiff_t isize;

class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (root == nullptr) { return vector<vector<int>>(); }
        auto q = queue<Node*>();
        auto res = vector<vector<int>>();
        q.push(root);

        while (!q.empty()) {
            const isize q_len = std::ssize(q);
            auto temp = vector<int>(q_len);

            for (isize i = 0; i < q_len; i += 1) {
                auto f = q.front();
                q.pop();
                temp[i] = f->val;

                for (Node* c : f->children) {
                    q.push(c);
                }
            }

            res.push_back(std::move(temp));
        }

        return res;
    }
};
