use std::collections::HashMap;

impl Solution {
    pub fn subdomain_visits(cpdomains: Vec<String>) -> Vec<String> {
        let mut hashmap: HashMap<&str, u32> = HashMap::new();
        for d in &cpdomains {
            let (cnt_str, domain) = d.split_once(' ').unwrap();
            let cnt: u32 = cnt_str.parse().expect("invalid input");
            let mut sub = domain;
            loop {
                *hashmap.entry(sub).or_insert(0) += cnt;
                if let Some((_, remains)) = sub.split_once('.') {
                    sub = remains;
                } else {
                    break;
                }
            }
        }

        let mut res: Vec<String> = Vec::with_capacity(hashmap.len());
        for (s, freq) in hashmap {
            res.push(format!("{} {}", freq, s));
        }

        res
    }
}
