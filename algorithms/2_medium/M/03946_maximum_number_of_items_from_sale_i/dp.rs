impl Solution {
    pub fn maximum_sale_items(items: Vec<Vec<i32>>, budget: i32) -> i32 {
        assert!(budget >= 1 && budget<= 1500);
        assert!(items.iter().all(|x| x[0] >= 1 && x[0] <= 1500));
        let max = items.iter().map(|x| x[0]).max().unwrap();
        let items_len = items.len();
        let mut buff = vec![0_i32; (2 * (max + 1) + 2 * (budget + 1)) as usize];
        let (mut extra, mut remain_buff) = buff.split_at_mut(1 + max as usize);
        let (mut freqs, mut remain_buff) = remain_buff.split_at_mut(1 + max as usize);
        let (mut curr, mut next) = remain_buff.split_at_mut((budget + 1) as usize);

        for i in 0..items_len {
            freqs[items[i][0] as usize] += 1;
        }

        for i in 1..=max {
            let mut curr = i;
            while curr <= max {
                extra[i as usize] += freqs[curr as usize];
                curr += i; 
            }
        }

        for i in 0..items_len {
            let price_i = items[i][1];
            if price_i > budget {
                continue;
            }
            let cnt = extra[items[i][0] as usize];
            for j in price_i..=budget {
                next[j as usize] = curr[j as usize].max(curr[(j - price_i) as usize] + cnt)
                                                   .max(next[(j - price_i) as usize] + 1);
            }
            for idx in 0..curr.len() {
                curr[idx] = next[idx];
            }
        }

        curr[budget as usize]
    }
}
