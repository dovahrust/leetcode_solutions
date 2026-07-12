use std::collections::HashMap;

impl Solution {
    pub fn number_of_boomerangs(points: Vec<Vec<i32>>) -> i32 {
        let len = points.len();
        assert!(len <= 500);
        assert!(points.iter().all(|p| {
            p.len() == 2 &&
            p[0] >= -10_000 && p[0] <= 10_000 &&
            p[1] >= -10_000 && p[1] <= 10_000
        }));

        let mut hashmap: HashMap<i32, i32> = HashMap::with_capacity(len);
        let mut cnt = 0_i32;

        for i in 0..len {
            for j in 0..len {
                if i == j { continue; }
                let diff_x = (points[i][0] - points[j][0]).abs();
                let diff_y = (points[i][1] - points[j][1]).abs();
                let diff_sq = diff_x.pow(2) + diff_y.pow(2);
                *hashmap.entry(diff_sq).or_insert(0) += 1;
            }
            for (_, &freq) in hashmap.iter() {
                cnt += freq * (freq - 1);
            }
            hashmap.clear();
        }

        cnt
    }
}
