impl Solution {
    pub fn minimum_effort(mut tasks: Vec<Vec<i32>>) -> i32 {
        tasks.sort_unstable_by_key(|x| x[0] - x[1]);

        let mut total_energy = 0_i32;
        let mut remain = 0_i32;

        for t in tasks {
            let actual = t[0];
            let minimum = t[1];
            assert!(actual <= minimum);
            if minimum > remain {
                total_energy += minimum - remain;
                remain = minimum;
            }
            remain -= actual;
        }

        total_energy
    }
}
