typedef ptrdiff_t isize;

static inline bool is_valid_ipv4_char(const char ch)
{
    return (ch >= '0' && ch <= '9') || (ch == '.');
}

static inline bool is_ipv4(const char* ip)
{
    if (ip == NULL) { return false; }

    int num = 0;
    int sep_cnt = 0;

    for (isize i = 0; ip[i] != '\0'; i += 1) {
        const char ch = ip[i];

        if (!is_valid_ipv4_char(ch)) {
            return false;
        }

        if (ch == '.') {
            sep_cnt += 1;
            num = 0;
            if (sep_cnt > 3 || i == 0 || ip[i - 1] == '.' || ip[i + 1] == '\0') {
                return false;
            }
        } else {
            if (i > 0 && num == 0 && ip[i - 1] != '.') {
                return false;
            }
            num = num * 10 + ch - '0';
            if (num > 255) {
                return false;
            }
        }
    }

    return sep_cnt == 3;
}

static inline bool is_valid_ipv6_char(const char ch)
{
    return (ch >= '0' && ch <= '9') ||
           (ch >= 'a' && ch <= 'f') ||
           (ch >= 'A' && ch <= 'F') ||
           (ch == ':');
}

static inline bool is_ipv6(const char* ip)
{
    if (ip == NULL) { return false; }

    int num_width = 0;
    int sep_cnt = 0;

    for (isize i = 0; ip[i] != '\0'; i += 1) {
        const char ch = ip[i];

        if (!is_valid_ipv6_char(ch)) {
            return false;
        }

        if (ch == ':') {
            sep_cnt += 1;
            if (sep_cnt > 7 || i == 0 || ip[i - 1] == ':' || ip[i + 1] == '\0') {
                return false;
            }

            num_width = 0;
        } else {
            num_width += 1;
            if (num_width > 4) {
                return false;
            }
        }
    }

    return sep_cnt == 7;
}

char* validIPAddress(const char* ip)
{
    char* res = NULL;

    if (is_ipv4(ip)) {
        res = strdup("IPv4");
    } else if (is_ipv6(ip)) {
        res = strdup("IPv6");
    } else {
        res = strdup("Neither");
    }

    assert(res != NULL);
    return res;
}
