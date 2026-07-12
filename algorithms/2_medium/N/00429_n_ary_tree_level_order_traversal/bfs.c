struct deque {
    struct Node** nodes;
    size_t len;
    size_t cap;
    size_t head;
};

static void deque_rev(struct deque* q, size_t start, size_t end)
{
    while (start < end) {
        end -= 1;
        struct Node* temp = q->nodes[start];
        q->nodes[start] = q->nodes[end];
        q->nodes[end] = temp;
        start += 1;
    }
}

static void deque_move_head_to_zero(struct deque* q)
{
    if (q->len == 0 || q->head == 0) { return; }
    deque_rev(q, 0, q->head);
    deque_rev(q, q->head, q->len);
    deque_rev(q, 0, q->len);
    q->head = 0;
}

static void deque_push(struct deque* q, struct Node* node)
{
    if (q->len == q->cap) {
        deque_move_head_to_zero(q);
        const size_t new_cap = (q->cap == 0 ? 4 : q->cap * 2);
        q->nodes = realloc(q->nodes, new_cap * sizeof(*q->nodes));
        assert(q != NULL);
        q->cap = new_cap;
    }

    q->nodes[(q->head + q->len) % q->cap] = node;
    q->len += 1;
}

static struct Node* deque_pop(struct deque* q)
{
    struct Node* res = q->nodes[q->head];
    q->nodes[q->head] = NULL;
    q->head = (q->head + 1) % q->cap;
    q->len -= 1;
    return res;
}

static void deque_free_data(struct deque* q)
{
    if (q != NULL) { free(q->nodes); }
}
/////
struct vec {
    int** ptr;
    int* cols;
    size_t len;
    size_t cap;
};

static void vec_push(struct vec* v, int* p, int p_len)
{
    if (v->len == v->cap) {
        const size_t new_cap = (v->cap == 0 ? 4 : v->cap * 2);
        v->ptr = realloc(v->ptr, new_cap * sizeof(*v->ptr));
        v->cols = realloc(v->cols, new_cap * sizeof(*v->cols));
        assert(v->ptr != NULL && v->cols != NULL);
        v->cap = new_cap;
    }

    v->ptr[v->len] = p;
    v->cols[v->len] = p_len;
    v->len += 1;
}

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct Node* root, int* return_len, int** return_col_len)
{
    assert(return_len != NULL && return_col_len != NULL);
    if (root == NULL) { 
        *return_len = 0;
        *return_col_len = NULL;
        return NULL;
    }
    struct deque q = { nodes: NULL, len: 0, cap: 0, head: 0};
    deque_push(&q, root);

    struct vec res = { ptr: NULL, cols: NULL, len: 0, cap: 0};

    while (q.len > 0) {
        const size_t q_len = q.len;
        int* temp = malloc(q_len * sizeof(*temp));
        assert(temp != NULL);

        for (size_t i = 0; i < q_len; i += 1) {
            struct Node* f = deque_pop(&q);
            temp[i] = f->val;
            const int c_len = f->numChildren;

            for (int j = 0; j < c_len; j += 1) {
                deque_push(&q, f->children[j]);
            }
        }

        assert(q_len <= (size_t)INT_MAX);
        vec_push(&res, temp, (int)q_len);
    }
/*cleanup: */
    deque_free_data(&q);
    *return_col_len = res.cols;
    assert(res.len <= (size_t)INT_MAX);
    *return_len = (int)res.len;
    return res.ptr;
}
