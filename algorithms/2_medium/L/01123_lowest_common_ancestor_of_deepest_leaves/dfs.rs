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
    fn dfs(h: u32, node_rc_opt: Option<&Rc<RefCell<TreeNode>>>, res: &mut (u32, Option<Rc<RefCell<TreeNode>>>)) -> u32 {
        if let Some(node_rc) = node_rc_opt {
            let node = node_rc.borrow();
            let h_left = Self::dfs(h + 1, node.left.as_ref(), res);
            let h_right = Self::dfs(h + 1, node.right.as_ref(), res);
            if h_left == h_right && h_left >= res.0 {
                res.0 = h_left;
                res.1 = Some(node_rc.clone());
            }
            return h_left.max(h_right);
        }

        h
    }

    pub fn lca_deepest_leaves(root_rc_opt: Option<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
        let mut res: (u32, Option<Rc<RefCell<TreeNode>>>) = (0, None);
        Self::dfs(0, root_rc_opt.as_ref(), &mut res);
        res.1
    }
}
