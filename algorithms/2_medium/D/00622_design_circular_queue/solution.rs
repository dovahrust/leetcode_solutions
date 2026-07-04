struct MyCircularQueue {
    arr: Vec<i32>,
    len: usize,
    cap: usize,
    start_idx: usize,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MyCircularQueue {
    fn new(k: i32) -> Self {
        Self {
            arr: vec![0_i32; k as usize],
            len: 0_usize,
            cap: k as usize,
            start_idx: 0_usize,
        }
    }

    fn en_queue(&mut self, value: i32) -> bool {
        if self.is_full() {
            return false;
        }
        self.arr[(self.start_idx + self.len) % self.cap] = value;
        self.len += 1;
        true
    }

    fn de_queue(&mut self) -> bool {
        if self.is_empty() {
            return false;
        }
        self.start_idx = (self.start_idx + 1) % self.cap;
        self.len -= 1;
        true
    }

    fn front(&self) -> i32 {
        if self.is_empty() {
            return -1;
        }
        self.arr[self.start_idx]
    }

    fn rear(&self) -> i32 {
        if self.is_empty() {
            return -1;
        }
        self.arr[(self.start_idx + self.len + self.cap - 1) % self.cap]
    }

    fn is_empty(&self) -> bool {
        self.len == 0
    }

    fn is_full(&self) -> bool {
        self.len == self.cap
    }
}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * let obj = MyCircularQueue::new(k);
 * let ret_1: bool = obj.en_queue(value);
 * let ret_2: bool = obj.de_queue();
 * let ret_3: i32 = obj.front();
 * let ret_4: i32 = obj.rear();
 * let ret_5: bool = obj.is_empty();
 * let ret_6: bool = obj.is_full();
 */
