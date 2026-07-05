typedef ptrdiff_t isize;

static inline int min_int(const int a,const int b)
{
    return a < b ? a : b;
}

struct pair {
    int other_node;
    int w;
};

struct vec_int {
    struct pair* ptr;
    size_t len;
    size_t cap;
};

static inline void vec_int_push(struct vec_int* vec, struct pair val)
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

int minScore(int n_i32, int** roads, int roads_len, int* roads_col_len)
{
    assert(n_i32 >= 2 && roads_len >= 1 && roads_col_len != NULL && roads_col_len[0] == 3 && roads != NULL);
    const isize n = n_i32;
    struct vec_int* adj = calloc((size_t)(n + 1), sizeof(*adj));
    assert(adj != NULL);
    for (int i = 0; i < roads_len; i += 1) {
        const int* e = roads[i];
        const int u = e[0];
        const int v = e[1];
        const int w = e[2];
        vec_int_push(&adj[u], (struct pair){v, w});
        vec_int_push(&adj[v], (struct pair){u, w});
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
    int res = INT_MAX;

    while (head != tail) {
        const int node = q[head];
        head += 1;
        const struct vec_int* curr = &adj[node];
        const isize curr_len = (isize)curr->len;
        for (isize i = 0; i < curr_len; i += 1) {
            res = min_int(res, curr->ptr[i].w);
            const int other_node = curr->ptr[i].other_node;
            if (!visited[other_node]) {
                visited[other_node] = true;
                q[tail] = other_node;
                tail += 1;
            }
        }
    }

    if (!visited[n]) { 
        fprintf(stderr, "there is no path between 1 and %lld", n);
        exit(0);
    }

/* cleanup: */
    free(visited);
    for (isize i = 0; i < n + 1; i += 1) {
        free(adj[i].ptr);
    }
    free(adj);
    free(q);
    return res;
}
