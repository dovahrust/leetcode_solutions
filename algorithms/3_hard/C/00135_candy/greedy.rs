impl Solution {
    pub fn candy(ratings: Vec<i32>) -> i32 {
        assert!(ratings.len() <= 2 * 10_000);
        let len = ratings.len();
        let mut vec = vec![1_i32; len];
        let mut cnt = 0_i32;

        for i in 1..len {
            if ratings[i - 1] < ratings[i] {
                vec[i] = vec[i - 1] + 1;
            }
        }

        for i in (1..len).rev() {
            if ratings[i - 1] > ratings[i] {
                vec[i - 1] = vec[i - 1].max(vec[i] + 1);
            }
            cnt += vec[i - 1];
        }
        cnt += vec[len - 1];

        cnt
    }
}
