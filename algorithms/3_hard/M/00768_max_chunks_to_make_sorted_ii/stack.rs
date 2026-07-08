impl Solution {
    pub fn max_chunks_to_sorted(mut arr: Vec<i32>) -> i32 {
        let len = arr.len();
        let mut stack_len = 0_usize;
        let mut max = i32::MIN;
        for i in 0..len {
            max = max.max(arr[i]);
            while stack_len > 0 && arr[stack_len - 1] > arr[i] {
                stack_len -= 1;
            }
            arr[stack_len] = max;
            stack_len += 1;
        }
        stack_len.try_into().unwrap()
    }
}
