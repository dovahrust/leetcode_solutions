impl Solution {

    #[inline(always)]
    fn is_ok(houses: &[i32], heaters: &[i32], guess: i32) -> bool {
        let (houses_len, heaters_len) = (houses.len(), heaters.len());
        let (mut houses_idx, mut heaters_idx) = (0, 0);
        let (mut lo, mut hi) = (-1, -1); 
        
        loop {
            while houses_idx < houses_len && houses[houses_idx] >= lo && houses[houses_idx] <= hi {
                houses_idx += 1;
            }
            if houses_idx == houses_len {
                return true;
            }
            if houses[houses_idx] < lo || heaters_idx == heaters_len {
                return false;
            }
            (lo, hi) = (heaters[heaters_idx] - guess, heaters[heaters_idx] + guess);
            heaters_idx += 1;
        }
    }

    pub fn find_radius(mut houses: Vec<i32>, mut heaters: Vec<i32>) -> i32 {
        assert!(heaters.len() > 0 && houses.len() > 0);
        houses.sort_unstable();
        heaters.sort_unstable();
        let (mut lo, mut hi) = (0_i32, i32::MAX);

        while lo <= hi {
            let mid = lo + (hi - lo) / 2;
            if Self::is_ok(&houses, &heaters, mid) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        
        lo
    }
}
