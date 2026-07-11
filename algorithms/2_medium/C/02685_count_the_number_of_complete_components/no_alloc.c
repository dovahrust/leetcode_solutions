#define MAX_ALLOWED_N 50

static inline int8_t max_int8(const int8_t a, const int8_t b)
{
    return a > b ? a : b;
}

static inline int8_t min_int8(const int8_t a, const int8_t b)
{
    return a < b ? a : b;
}

struct data_cell {
    int16_t edges;
    int16_t nodes;
};

int countCompleteComponents(int n, int** edges, int edges_len, int* edges_col_len)
{
    assert(edges_len >= 0 && n >= 1 && n <= MAX_ALLOWED_N);

    struct data_cell data[MAX_ALLOWED_N + 1];
    int data_len = 0;

    int8_t roots[MAX_ALLOWED_N + 1];
    int roots_len = 0;

    int8_t to_roots[MAX_ALLOWED_N + 1];
    for (int i = 0; i < n; i += 1) { to_roots[i] = -1; }

    for (int i = 0; i < edges_len; i += 1) {
        const int u = edges[i][0];
        const int v = edges[i][1];
        assert(u >= 0 && v >=0 && u < n && v < n);
        const int8_t max_root = max_int8(to_roots[u], to_roots[v]);
        const int8_t min_root = min_int8(to_roots[u], to_roots[v]);
        if (max_root == -1) {
            to_roots[u] = (int8_t)roots_len;
            to_roots[v] = (int8_t)roots_len;
            roots[roots_len] = (int8_t)data_len;
            roots_len += 1;
            data[data_len] = (struct data_cell){ edges: 1, nodes: 2 };
            data_len += 1;
        } else if (min_root == -1) {
            to_roots[u] = max_root;
            to_roots[v] = max_root;
            data[roots[max_root]].edges += 1;
            data[roots[max_root]].nodes += 1;
        } else if (roots[max_root] == roots[min_root]) {
            data[roots[min_root]].edges += 1;
        } else {
            data[roots[min_root]].edges += data[roots[max_root]].edges + 1;
            data[roots[min_root]].nodes += data[roots[max_root]].nodes;
            data[roots[max_root]] = (struct data_cell){ edges: -1, nodes: 0 };
            roots[max_root] = roots[min_root];
        }
    }

    for (int i = 0; i < n; i += 1) {
        if (to_roots[i] == -1) {
            data[data_len] = (struct data_cell){ edges: 0, nodes: 1};
            data_len += 1;
        }
    }

    int cnt = 0;
    for (int i = 0; i < data_len; i += 1) {
        const int16_t expected = (data[i].nodes * (data[i].nodes - 1)) / 2;
        if (data[i].edges == expected) {
            cnt += 1;
        }
    }

    return cnt;
}
