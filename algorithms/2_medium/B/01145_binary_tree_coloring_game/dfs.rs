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
impl Solution {
    fn dfs(node_rc_opt: Option<&Rc<RefCell<TreeNode>>>, x: i32, state: States, res: &mut (i32, i32, i32)) {
        if let Some(node_rc) = node_rc_opt {
            let node = node_rc.borrow();
            if node.val != x {
                match state {
                    States::NotSeenX => res.0 += 1,
                    States::LeftX => res.1 += 1,
                    States::RightX => res.2 += 1,
                }
                Self::dfs(node.left.as_ref(), x, state, res);
                Self::dfs(node.right.as_ref(), x, state, res);
            } else {
                Self::dfs(node.left.as_ref(), x, States::LeftX, res);
                Self::dfs(node.right.as_ref(), x, States::RightX, res);
            }
        }
    }

    pub fn btree_game_winning_move(root: Option<Rc<RefCell<TreeNode>>>, n: i32, x: i32) -> bool {
        let mut res = (0_i32, 0_i32, 0_i32);
        Self::dfs(root.as_ref(), x, States::NotSeenX, &mut res);

        res.0 > res.1 + res.2 ||
        res.1 > res.0 + res.2 ||
        res.2 > res.0 + res.1
    }
}
