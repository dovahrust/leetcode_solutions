#define RED 0
#define BLUE 1
#define INF UINT8_MAX

struct data {
    uint8_t color;
    uint8_t node;
};

struct vec_data {
    struct data* ptr;
    size_t len;
    size_t cap;
};

static inline void vec_data_push(struct vec_data* vec, struct data data)
{
    if (vec->cap == vec->len) {
        const size_t new_cap = vec->cap == 0 ? 4 : 2 * vec->cap;
        vec->ptr = realloc(vec->ptr, new_cap * sizeof(*vec->ptr));
        assert(vec->ptr != NULL);
        vec->cap = new_cap;
    }

    vec->ptr[vec->len] = data;
    vec->len += 1;
}

static inline struct vec_data* init_adj(const int n, int** red_edges, const int red_len, int** blue_edges, const int blue_len)
{
    struct vec_data* adj = calloc((size_t)n, sizeof(*adj));
    assert(adj != NULL);
    for (int i = 0; i < red_len; i += 1) {
        const int* r = red_edges[i];
        assert(r[0] >= 0 && r[1] >= 0 && r[0] < n && r[1] < n);
        const int u = r[0];
        const int v = r[1];
        vec_data_push(&adj[u], (struct data){ .color = RED, .node = (uint8_t)v});
    }
    for (int i = 0; i < blue_len; i += 1) {
        const int* b = blue_edges[i];
        assert(b[0] >= 0 && b[1] >= 0 && b[0] < n && b[1] < n);
        const int u = b[0];
        const int v = b[1];
        vec_data_push(&adj[u], (struct data){ .color = BLUE, .node = (uint8_t)v});
    }
    return adj;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shortestAlternatingPaths(int n, int** red_edges, const int red_len, const int* red_cols,
                              int** blue_edges, int blue_len, int* blue_cols, int* return_len)
{
    assert(n <= 100 && n >= 1 && red_len >= 0 && blue_len >= 0 && return_len != NULL);
    int* res = malloc((size_t)n * sizeof(*res));
    assert(res != NULL);
    *return_len = n;

    struct vec_data* adj = init_adj(n, red_edges, red_len, blue_edges, blue_len);

    uint8_t* costs = malloc((size_t)n * 2 * sizeof(*costs));
    assert(costs != NULL);
    struct data* q = malloc((size_t)n * 2 * sizeof(*q));
    assert(q != NULL);
    
    q[0] = (struct data){ .color = RED, .node = 0 };
    q[1] = (struct data){ .color = BLUE, .node = 0 };
    size_t q_tail = 2;
    size_t q_head = 0;
    const size_t q_cap = 2 * (size_t)n;
    costs[0] = 0;
    costs[1] = 0;
    for (int i = 1; i < n; i += 1) {
        costs[2 * i] = INF;
        costs[2 * i + 1] = INF;
    }

    uint8_t level = 1;
    while (q_tail != q_head) {
        const size_t level_len = q_tail - q_head;

        for (size_t steps = 0; steps < level_len; steps += 1) {
            const uint8_t u = q[q_head].node;
            const uint8_t u_color = q[q_head].color;
            q_head += 1;
            switch (u_color) {
                case RED: {
                    struct vec_data* a = &adj[u];
                    const size_t a_len = a->len;
                    for (size_t i = 0; i < a_len; i += 1) {
                        const uint8_t v = a->ptr[i].node;
                        const uint8_t v_color = a->ptr[i].color;
                        if (v_color != RED && costs[v * 2 + 1] > level) {
                            costs[v * 2 + 1] = level;
                            q[q_tail] = (struct data){ .color = BLUE, .node = v };
                            q_tail += 1;
                        }
                    }
                    break;
                }
                case BLUE: {
                    struct vec_data* a = &adj[u];
                    const size_t a_len = a->len;
                    for (size_t i = 0; i < a_len; i += 1) {
                        const uint8_t v = a->ptr[i].node;
                        const uint8_t v_color = a->ptr[i].color;
                        if (v_color != BLUE && costs[v * 2] > level) {
                            costs[v * 2] = level;
                            q[q_tail] = (struct data){ .color = RED, .node = v };
                            q_tail += 1;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }

        level += 1;
    }

    for (int i = 0; i < n; i += 1) {
        const uint8_t min = costs[2 * i] < costs[2 * i + 1] ? costs[2 * i] : costs[2 * i + 1];
        res[i] = min == INF ? -1 : (int)min;
    }

/* cleanup: */
    free(costs);
    free(q);
    for (int i = 0; i < n; i += 1) {
        free(adj[i].ptr);
    }
    free(adj);

    return res;
}
