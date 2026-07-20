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
use std::rc::Rc;
use std::cell::RefCell;
impl Solution {
    fn dfs(node_rc: &Rc<RefCell<TreeNode>>, parent_sum: i32, limit: i32) -> bool {
        let mut node = node_rc.borrow_mut();
        let new_sum = parent_sum + node.val;

        match (node.left.as_ref(), node.right.as_ref()) {
            (Some(left), Some(right)) => {
                let should_delete_left = Self::dfs(left, new_sum, limit);
                let should_delete_right = Self::dfs(right, new_sum, limit);

                if should_delete_left {
                    node.left.take();
                }

                if should_delete_right {
                    node.right.take();
                }

                return should_delete_left && should_delete_right;
            },
            (Some(left), None) => {
                let should_delete_left = Self::dfs(left, new_sum, limit);

                if should_delete_left {
                    node.left.take();
                }

                return should_delete_left;
            },
            (None, Some(right)) => {
                let should_delete_right = Self::dfs(right, new_sum, limit);

                if should_delete_right {
                    node.right.take();
                }

                return should_delete_right;
            },
            (None, None) => {
                return new_sum < limit;
            }
        }
    }

    pub fn sufficient_subset(root_rc_opt: Option<Rc<RefCell<TreeNode>>>, limit: i32) -> Option<Rc<RefCell<TreeNode>>> {
        if let Some(root_rc) = root_rc_opt {
            let should_delete_root = Self::dfs(&root_rc, 0, limit);
            if should_delete_root {
                return None;
            }
            return Some(root_rc);
        }

        None
    }
}
