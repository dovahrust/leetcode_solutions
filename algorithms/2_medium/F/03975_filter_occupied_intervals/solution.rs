impl Solution {
    #[inline(always)]
    fn insert_to_res(res: &mut Vec<Vec<i32>>, lo: i32, hi: i32, free_start: i32, free_end: i32) {
        if hi < free_start || lo > free_end {
            res.push(vec![lo, hi]);
        } else {
            if lo < free_start {
                res.push(vec![lo, free_start - 1]);
            }

            if hi > free_end {
                res.push(vec![free_end + 1, hi]);
            }
        }
    }

    pub fn filter_occupied_intervals(mut occupied_intervals: Vec<Vec<i32>>, free_start: i32, free_end: i32) -> Vec<Vec<i32>> {
        occupied_intervals.sort_unstable_by(|a, b| {
            a[0].cmp(&b[0])
        });

        let (mut lo, mut hi) = (occupied_intervals[0][0], occupied_intervals[0][0]);
        let mut res: Vec<Vec<i32>> = Vec::default();

        for o in occupied_intervals {
            if o[0] <= hi + 1 {
                hi = hi.max(o[1]);
            } else {
                Self::insert_to_res(&mut res, lo, hi, free_start, free_end);
                (lo, hi) = (o[0], o[1]);
            }
        }

        Self::insert_to_res(&mut res, lo, hi, free_start, free_end);

        res
    }
}
