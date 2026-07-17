impl Solution {
    pub fn count_kth_roots(l: i32, r: i32, k: i32) -> i32 {
        assert!(k >= 1 && l <= r && l >= 0);
        if k == 1 {
            return r - l + 1; 
        }
        let (l, r) = (l as i64, r as i64);
        let mut cnt = 0_i32;
        let mut curr = 0_i64;
        let k = k as u32;
        loop {
            let pow = curr.pow(k);
            if pow > r {
                break;
            }
            if pow >= l {
                cnt += 1;
            }
            curr += 1;
        }
        cnt
    }
}
