use std::collections::VecDeque;
impl Solution {
    const EXACT_GENE_LEN: usize = 8;
    const MAX_BANK_LEN: usize = 10;

    #[inline(always)]
    fn calc_diff(a: &[u8], b: &[u8]) -> i8 {
        let mut cnt = 0_i8;
        for i in 0..Self::EXACT_GENE_LEN {
            cnt += if a[i] == b[i] { 0 } else { 1 };
        }
        cnt
    }

    pub fn min_mutation(start_gene: String, end_gene: String, bank: Vec<String>) -> i32 {
        assert!(bank.len() <= Self::MAX_BANK_LEN);
        assert!(start_gene.len() == Self::EXACT_GENE_LEN && end_gene.len() == Self::EXACT_GENE_LEN &&
               bank.iter().all(|x| x.len() == Self::EXACT_GENE_LEN));

        let target = end_gene.as_bytes();
        if !bank.iter().any(|x| Self::calc_diff(target, x.as_bytes()) == 0) {
            return -1;
        }

        let mut bank_datas: Vec<_> = bank.iter().map(|x| x.as_bytes()).collect();
        let mut bank_datas_len = bank_datas.len();
        let mut q: VecDeque<&[u8]> = VecDeque::with_capacity(bank_datas.len());
        q.push_back(start_gene.as_bytes());

        let mut level = 0;
        while !q.is_empty() {
            let q_len = q.len();

            for _ in 0..q_len {
                let curr = q.pop_front().unwrap();
                if Self::calc_diff(curr, target) == 0 {
                    return level;
                }
                let mut i = 0;
                while i < bank_datas_len {
                    if Self::calc_diff(curr, bank_datas[i]) == 1 {
                        q.push_back(bank_datas[i]);
                        bank_datas[i] = bank_datas[bank_datas_len - 1];
                        bank_datas_len -= 1;
                    } else {
                        i += 1;
                    }
                }
            }

            level += 1;
        }

        -1
    }
}
