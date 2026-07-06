impl Solution {
    pub fn can_complete_circuit(gas: Vec<i32>, cost: Vec<i32>) -> i32 {
        assert!(gas.len() == cost.len());
        let len = gas.len();
        let sum_gas = gas.iter().map(|x| *x).sum::<i32>();
        let sum_cost = cost.iter().map(|x| *x).sum::<i32>();
        if sum_gas < sum_cost { 
            return -1;
        }

        let mut diff_sum = 0_i32;
        let mut selected_idx = 0_usize;

        for i in 0..len {
            if diff_sum < 0 {
                diff_sum = 0;
                selected_idx = i;
            }
            diff_sum += gas[i] - cost[i];
        }

        selected_idx.try_into().unwrap()
    }
}
