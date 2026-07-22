/** 
 * The rand7() API is already defined for you.
 * @return a random integer in the range 1 to 7
 * fn rand7() -> i32;
 */

impl Solution {
    pub fn rand10() -> i32 {
        loop {
            let rows = rand7() - 1;
            let cols = rand7() - 1;
            let res = rows * 7 + cols;
            if res < 40 {
                return (res % 10) + 1;
            }
        }
    }
}
