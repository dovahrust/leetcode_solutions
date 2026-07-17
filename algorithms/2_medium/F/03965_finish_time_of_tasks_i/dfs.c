static inline int64_t max_int64(const int64_t a, const int64_t b)
{
    return a > b ? a : b;
}

static inline int64_t min_int64(const int64_t a, const int64_t b)
{
    return a < b ? a : b;
}

struct vec {
    int* ptr;
    size_t len;
    size_t cap;
};

static inline void vec_push(struct vec* vec, const int val)
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

static inline struct vec* init_arr_of_default_vec(const size_t count)
{
    struct vec* init = malloc(count * sizeof(*init));
    assert(init != NULL);
    for (size_t i = 0; i < count; i += 1) {
        init[i].ptr = NULL;
        init[i].len = 0;
        init[i].cap = 0;
    }
    return init;
}

static inline void free_data_of_arr_of_vecs(struct vec* vec, const size_t len)
{
    for (size_t i = 0; i < len; i += 1) {
        free(vec[i].ptr);
        vec[i].cap = 0;
        vec[i].len = 0;
    }
}

static inline struct vec* init_adj(const int n, int** edges, const int edges_len)
{
    struct vec* adj = init_arr_of_default_vec((size_t)n);
    for (int i = 0; i < edges_len; i += 1) {
        const int* e = edges[i];
        const int u = e[0];
        const int v = e[1];
        assert(u >= 0 && v >= 0 && u < n && v < n);
        vec_push(&adj[u], v);
    }
    return adj;
}

int64_t dfs(const int node, const int n, const struct vec* adj, int* base_time)
{
    if (adj[node].len == 0) {
        return base_time[node];
    }

    int64_t max = INT64_MIN;
    int64_t min = INT64_MAX;
    const size_t len_adj_node = adj[node].len;
    const int* vec = adj[node].ptr;

    for (size_t i = 0; i < len_adj_node; i +=1) {
        const int64_t val = dfs(vec[i], n, adj, base_time);
        max = max_int64(max, val);
        min = min_int64(min, val);
    }

    const int64_t curr_node_time = max - min + base_time[node];

    return max + curr_node_time;
}

long long finishTime(const int n, int** edges, const int edges_len, const int* edges_cols_len, 
                     const int* base_time, const int base_time_len)
{
    assert(n >= 1 && n == base_time_len && edges_len == n - 1 && base_time != NULL);

    struct vec* adj = init_adj(n, edges, edges_len);
    const int root = 0;

    const int64_t res = dfs(root, n, adj, base_time);

/* cleanup: */
    free_data_of_arr_of_vecs(adj, (size_t)n);
    free(adj);
    return res;
}
