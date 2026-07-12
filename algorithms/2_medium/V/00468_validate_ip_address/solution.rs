impl Solution {

    #[inline(always)]
    fn is_ipv4(ip: &[u8]) -> bool {
        let len = ip.len();
        let mut num = 0_i32;
        let mut sep_cnt = 0_i32;

        for i in 0..len {
            match ip[i] {
                b'.' => {
                    sep_cnt += 1;
                    num = 0;
                    if sep_cnt > 3 || i == 0 || i + 1 == len || ip[i - 1] == b'.' {
                        return false;
                    }
                },
                b'0'..=b'9' => {
                    if i > 0 && num == 0 && ip[i - 1] != b'.' {
                        return false;
                    }
                    num = num * 10 + (ip[i] - b'0') as i32;
                    if num > 255 {
                        return false;
                    }
                },
                _ => {
                    return false;
                }
            }
        }

        sep_cnt == 3
    }

    #[inline(always)]
    fn is_ipv6(ip: &[u8]) -> bool {
        let len = ip.len();
        let mut num_width = 0_i32;
        let mut sep_cnt = 0_i32;

        for i in 0..len {
            match ip[i] {
                b':' => {
                    sep_cnt += 1;
                    if sep_cnt > 7 || i == 0 || i + 1 == len || ip[i - 1] == b':' {
                        return false;
                    }
                    num_width = 0;
                },
                b'0'..=b'9' | b'a'..=b'f' | b'A'..=b'F' => {
                    num_width += 1;
                    if num_width > 4 {
                        return false;
                    }
                },
                _ => {
                    return false;
                }
            }
        }

        sep_cnt == 7
    }

    pub fn valid_ip_address(ip: String) -> String {
        if Self::is_ipv4(ip.as_bytes()) {
            String::from("IPv4")
        } else if Self::is_ipv6(ip.as_bytes()) {
            String::from("IPv6")
        } else {
            String::from("Neither")
        }
    }
}
