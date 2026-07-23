// Definition for a binary tree node.
// #[derive(Debug, PartialEq, Eq)]
// pub struct TreeNode {
//   pub val: i32,
//   pub left: Option<Rc<RefCell<TreeNode>>>,
//   pub right: Option<Rc<RefCell<TreeNode>>>,
// }
// 
// impl TreeNode {
//   #[inline]
//   pub fn new(val: i32) -> Self {
//     TreeNode {
//       val,
//       left: None,
//       right: None
//     }
//   }
// }

#[derive(Clone, Copy)]
enum States {
    NotSeenX,
    LeftX,
    RightX,
}

use std::rc::Rc;
use std::cell::RefCell;
use std::collections::VecDeque;
impl Solution {
    pub fn btree_game_winning_move(root: Option<Rc<RefCell<TreeNode>>>, n: i32, x: i32) -> bool {
        assert!(n > 0 && x > 0 && x<= n && root.is_some());
        let target = (n / 2) + 1;
        let mut res = (0_i32, 0_i32, 0_i32);
        let mut q: VecDeque<(Rc<RefCell<TreeNode>>, States)> = VecDeque::with_capacity(n as usize);
        q.push_back((root.unwrap(), States::NotSeenX));

        while let Some((node_rc, state)) = q.pop_front() {
            let node = node_rc.borrow();
            if node.val != x {
                match state {
                    States::NotSeenX => {
                        res.0 += 1;
                        if res.0 >= target {
                            return true;
                        }
                    },
                    States::LeftX => {
                        res.1 += 1;
                        if res.1 >= target {
                            return true;
                        }
                    },
                    States::RightX => {
                        res.2 += 1;
                        if res.2 >= target {
                            return true;
                        }
                    },
                }
                if let Some(left) = node.left.as_ref() {
                    q.push_back((left.clone(), state));
                }
                if let Some(right) = node.right.as_ref() {
                    q.push_back((right.clone(), state));
                }
            } else {
                if let Some(left) = node.left.as_ref() {
                    q.push_back((left.clone(), States::LeftX));
                }
                if let Some(right) = node.right.as_ref() {
                    q.push_back((right.clone(), States::RightX));
                }
            }
        }

        false
    }
}
