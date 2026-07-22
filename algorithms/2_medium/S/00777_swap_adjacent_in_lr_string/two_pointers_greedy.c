typedef ptrdiff_t isize;

bool canTransform(char* start, char* result)
{
    assert(start != NULL && result != NULL);
    isize s_idx = 0;
    isize r_idx = 0;

    while (true) {
        while (start[s_idx] != '\0' && start[s_idx] == 'X') {
            s_idx += 1;
        }
        while (result[r_idx] != '\0' && result[r_idx] == 'X') {
            r_idx += 1;
        }
        if (start[s_idx] == '\0' || result[r_idx] == '\0') {
            break;
        }
        if (start[s_idx] != result[r_idx]) {
            return false;
        }
        if (start[s_idx] == 'R' && s_idx > r_idx) {
            return false;
        }
        if (start[s_idx] == 'L' && s_idx < r_idx) {
            return false;
        }
        s_idx += 1;
        r_idx += 1;
    }

    return start[s_idx] == '\0' && result[r_idx] == '\0';
}
