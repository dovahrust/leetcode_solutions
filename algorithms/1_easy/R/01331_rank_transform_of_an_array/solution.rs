impl Solution {
    pub fn array_rank_transform(arr: Vec<i32>) -> Vec<i32> {
        let len = arr.len();
        assert!(len <= i32::MAX as usize);
        if len == 0 { return arr; }
        let mut idxs: Vec<i32> = (0..(len as i32)).into_iter().collect();
        idxs.sort_unstable_by_key(|i| arr[*i as usize]);

        let mut ranks = arr;
        let mut rank = 1_i32;
        let mut prev_val = ranks[idxs[0] as usize];
        for i in 0..len {
            if prev_val < ranks[idxs[i] as usize] {
                rank += 1;
            }

            prev_val = ranks[idxs[i] as usize];
            ranks[idxs[i] as usize] = rank;
        }

        ranks
    }
}
