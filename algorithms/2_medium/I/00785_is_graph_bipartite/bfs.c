bool isBipartite(int** graph, const int n, const int* cols_data)
{
    assert(n >= 1 && n <= 100 && graph != NULL && cols_data != NULL);
    int8_t* buff = calloc((size_t)n * 2, sizeof(*buff));
    assert(buff != NULL);
    int8_t* colors = &buff[0];
    int8_t* q = &buff[n];
    bool res = true;

    for (int node = 0; node < n; node += 1) {
        if (colors[node] != 0) {
            continue;
        }
        q[0] = (int8_t)node;
        size_t q_len = 1;
        size_t q_head = 0;
        colors[node] = 1;
        while (q_head < q_len) {
            const int parent = q[q_head];
            q_head += 1;
            const int8_t color_parent = colors[parent];
            const int* childs = graph[parent];
            const int childs_len = cols_data[parent];
            for (int i = 0; i < childs_len; i += 1) {
                const int child = childs[i];
                assert(child >= 0 && child < n);
                if (colors[child] == color_parent) {
                    res = false;
                    goto cleanup;
                }
                if (colors[child] != 0) {
                    continue;
                }
                if (color_parent == 1) {
                    colors[child] = 2;
                } else {
                    colors[child] = 1;
                }
                q[q_len] = (int8_t)child;
                q_len += 1;
            }
        }
    }

cleanup:
    free(buff);
    return res;
}
