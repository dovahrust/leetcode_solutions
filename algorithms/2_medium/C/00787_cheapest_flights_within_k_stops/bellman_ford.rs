impl Solution {
    const MAX_ALLOWED_PRICE: i32 = 10_000;
    const MAX_ALLOWED_N: i32 = 100;
    const MAX_ALLOWED_FLIGHTS: i32 = (Self::MAX_ALLOWED_N * (Self::MAX_ALLOWED_N - 1)) / 2;
    const INF: i32 = i32::MAX / 2; 

    pub fn find_cheapest_price(n: i32, flights: Vec<Vec<i32>>, src: i32, dst: i32, k: i32) -> i32 {
        assert!(k >= 0 && k < n && n <= Self::MAX_ALLOWED_N && flights.len() <= Self::MAX_ALLOWED_FLIGHTS as usize);
        assert!(src >= 0 && src < n && dst >= 0 && dst < n && src != dst);

        let mut buff = vec![Self::INF; 2 * (n as usize)];
        let (mut curr, mut next) = buff.split_at_mut(n as usize);
        curr[src as usize] = 0;
        next[src as usize] = 0;

        for _ in 0..=k {
            for f in &flights {
                let (u, v, w) = (f[0], f[1], f[2]);
                assert!(u >= 0 && u < n && v >=0 && v < n && w >= 1 && w <= Self::MAX_ALLOWED_PRICE);
                next[v as usize] = next[v as usize].min(curr[u as usize] + w);
            }
            (curr, next) = (next, curr);
        }

        if curr[dst as usize] == Self::INF { -1 } else { curr[dst as usize] }
    }
}
