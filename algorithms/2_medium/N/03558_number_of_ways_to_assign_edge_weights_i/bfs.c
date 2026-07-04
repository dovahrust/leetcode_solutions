#define MOD_TO 1000000007

typedef ptrdiff_t isize;

struct vec_int {
    int* ptr;
    size_t len;
    size_t cap;
};

static inline void vec_int_push(struct vec_int* vec, int val)
{
    if (vec->len == vec->cap) {
        const size_t new_cap = vec->cap == 0 ? 4 : vec->cap * 2;
        vec->ptr = realloc(vec->ptr, new_cap * sizeof(*vec->ptr));
        assert(vec->ptr != NULL);
        vec->cap = new_cap;
    }

    vec->ptr[vec->len] = val;
    vec->len += 1;
}

static inline int mod_pow(const int base, int exp, const int mod_to)
{
    int64_t base_i64 = base;
    int64_t res = 1;
    while (exp > 0) {
        if ((exp & 1) == 1) {
            res = (res * base_i64) % mod_to;
        }
        base_i64 = (base_i64 * base_i64) % mod_to;
        exp >>= 1;
    }
    return (int)res;
}

int assignEdgeWeights(int** edges, int len, int* edges_col_len)
{
    if (len == 0) { return 0; }
    assert(edges != NULL && edges_col_len[0] == 2);
    const isize n = (isize)len + 1;

    struct vec_int* adj = calloc((size_t)(n + 1), sizeof(*adj));
    assert(adj != NULL);
    for (int i = 0; i < len; i += 1) {
        const int* e = edges[i];
        const int u = e[0];
        const int v = e[1];
        vec_int_push(&adj[u], v);
        vec_int_push(&adj[v], u);
    }

    int* q = malloc((size_t)(n + 1) * sizeof(*q));
    assert(q != NULL);
    isize head = 0;
    isize tail = 0;
    bool* visited = calloc((size_t)(n + 1), sizeof(*visited));
    assert(visited != NULL);
    const int root = 1;
    q[tail] = root;
    tail += 1;
    visited[root] = true;
    int level = 0;
    while (head != tail) {
        const isize q_len = tail - head;
        for (isize step = 0; step < q_len; step += 1) {
            const int node = q[head];
            head += 1;
            const struct vec_int* curr = &adj[node];
            const isize curr_len = curr->len;
            for (isize i = 0; i < curr_len; i += 1) {
                const int other_node = curr->ptr[i];
                if (!visited[other_node]) {
                    visited[other_node] = true;
                    q[tail] = other_node;
                    tail += 1;
                }
            }
        }
        level += 1;
    }
    const int edges_max_depth = level - 1;
    const int res =  edges_max_depth  == 0 ? 0 : mod_pow(2, edges_max_depth - 1, MOD_TO);

/* cleanup: */
    free(visited);
    for (isize i = 0; i < n + 1; i += 1) {
        free(adj[i].ptr);
    }
    free(adj);
    free(q);
    return res;
}
