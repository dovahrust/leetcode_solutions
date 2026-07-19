use std::sync::OnceLock;

const MAX_ALLOWED_N: i32 = 10_000;
const VALIDS: [i8; 3] = [0, 1, 8];
const VALIDS_WITH_DIFF: [i8; 4] =  [ 2, 5, 6, 9 ];
static FREQS: OnceLock<[i16; MAX_ALLOWED_N as usize + 1]> = OnceLock::new();

fn init_backtrack(a: i32, contains_diff: bool, freqs: &mut [i16]) {
    if a > MAX_ALLOWED_N {
        return;
    }

    if contains_diff {
        freqs[a as usize] = 1;
    }

    let base = a * 10;

    for v in VALIDS {
        init_backtrack(base + v as i32, contains_diff, freqs);
    }

    for v in VALIDS_WITH_DIFF {
        init_backtrack(base + v as i32, true, freqs);
    }
}

fn init() -> [i16; MAX_ALLOWED_N as usize + 1] {
    let mut freqs = [0_i16; MAX_ALLOWED_N as usize + 1];
    for v in VALIDS {
        if (v != 0) {
            init_backtrack(v as i32, false, &mut freqs);
        }
    }

    for v in VALIDS_WITH_DIFF {
        init_backtrack(v as i32, true, &mut freqs);
    }

    for i in 1..=(MAX_ALLOWED_N as usize) {
        freqs[i] += freqs[i - 1];
    }

    freqs
}

impl Solution {
    pub fn rotated_digits(mut n: i32) -> i32 {
        assert!(n <= MAX_ALLOWED_N && n >= 1);
        let freqs = FREQS.get_or_init(|| init());

        freqs[n as usize] as i32
    }
}
