use std::sync::Once;

static INIT: Once = Once::new();
const MAX_ALLOWED_N: i32 = 10_000;
const VALIDS: [i8; 3] = [0, 1, 8];
const VALIDS_WITH_DIFF: [i8; 4] =  [ 2, 5, 6, 9 ];
static mut FREQS: [i16; MAX_ALLOWED_N as usize + 1] = [0; MAX_ALLOWED_N as usize + 1];

fn init_backtrack(a: i32, contains_diff: bool) {
    if a > MAX_ALLOWED_N {
        return;
    }

    if contains_diff {
        unsafe { FREQS[a as usize] = 1; }
    }

    let base = a * 10;

    for v in VALIDS {
        init_backtrack(base + v as i32, contains_diff);
    }

    for v in VALIDS_WITH_DIFF {
        init_backtrack(base + v as i32, true);
    }
}

fn init() {
    for v in VALIDS {
        if (v != 0) {
            init_backtrack(v as i32, false);
        }
    }

    for v in VALIDS_WITH_DIFF {
        init_backtrack(v as i32, true);
    }

    for i in 1..=(MAX_ALLOWED_N as usize) {
        unsafe { FREQS[i] += FREQS[i - 1]; }
    }
}


impl Solution {
    pub fn rotated_digits(mut n: i32) -> i32 {
        assert!(n <= MAX_ALLOWED_N && n >= 1);

        INIT.call_once(|| {
            init();
        });

        unsafe { FREQS[n as usize] as i32 }
    }
}
