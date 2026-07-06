use std::collections::VecDeque;

impl Solution {
    const INF: u16 = u16::MAX / 2;

    #[inline(always)]
    fn calc_diff(s1: &[u8], s2: &[u8]) -> i32 {
        let mut diff = 0;
        let n = s1.len();
        debug_assert!(s1.len() == s2.len());
        for i in 0..n {
            if s1[i] != s2[i] {
                diff += 1;
            }
        }
        diff
    }

    pub fn ladder_length(begin_word: String, end_word: String, word_list: Vec<String>) -> i32 {
        assert!(word_list.len() <= 5_000);
        debug_assert!(begin_word != end_word);
        if !word_list.iter().any(|x| x == &end_word) { return 0; }

        let mut buff = vec![Self::INF; 2 * word_list.len()];
        let (mut avaiables, mut costs) = buff.split_at_mut(word_list.len());
        for i in 0..word_list.len() { avaiables[i] = i as u16; }
        let mut hi = avaiables.len();
        let mut lo = 0_usize;
        let mut q: VecDeque<u16> = VecDeque::new();

        while lo < hi {
            let diff = Self::calc_diff(begin_word.as_bytes(), word_list[avaiables[lo] as usize].as_bytes());
            if diff == 1 {
                costs[avaiables[lo] as usize] = 2;
                q.push_back(avaiables[lo]);
                hi -= 1;
                avaiables[lo] = avaiables[hi];
            } else if diff == 0 {
                costs[avaiables[lo] as usize] = 0;
                hi -= 1;
                avaiables[lo] = avaiables[hi];
            } else {
                lo += 1;
            }
        }

        while let Some(i_u16) = q.pop_front() {
            let i = i_u16 as usize;
            let curr_cost = costs[i];
            let mut lo = 0_usize;
            while lo < hi {
                let diff = Self::calc_diff(word_list[i].as_bytes(), word_list[avaiables[lo] as usize].as_bytes());
                if diff == 1 {
                    costs[avaiables[lo] as usize] = curr_cost + 1;
                    q.push_back(avaiables[lo]);
                    hi -= 1;
                    avaiables[lo] = avaiables[hi];
                } else {
                    lo += 1;
                }
            }
        }

        for (i, w) in word_list.iter().enumerate() {
            if Self::calc_diff(end_word.as_bytes(), w.as_bytes()) == 0 {
                if costs[i] == Self::INF {
                    return 0;
                } else {
                    return costs[i] as i32;
                }
            }
        }

        unreachable!()
    }
}
