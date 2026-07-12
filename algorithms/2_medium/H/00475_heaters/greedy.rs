impl Solution {
    #[inline(always)]
    fn dist_to_next_heater_is_eq_or_is_less(house: i32, heaters: &[i32], heaters_idx: usize) -> bool {
        if heaters_idx + 1 == heaters.len() {
            return false;
        }
        (house - heaters[heaters_idx]).abs() >= (house - heaters[heaters_idx + 1]).abs()
    }

    pub fn find_radius(mut houses: Vec<i32>, mut heaters: Vec<i32>) -> i32 {
        assert!(heaters.len() > 0 && houses.len() > 0);
        houses.sort_unstable();
        heaters.sort_unstable();

        let heaters_len = heaters.len();
        let mut heaters_idx = 0_usize;
        let mut res = 0_i32;

        for house in houses {
            while Self::dist_to_next_heater_is_eq_or_is_less(house, &heaters, heaters_idx) {
                heaters_idx += 1;
            }
            res = res.max((house - heaters[heaters_idx]).abs());
        }

        res
    }
}
