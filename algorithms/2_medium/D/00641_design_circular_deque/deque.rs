struct MyCircularDeque {
    buff: Vec<i32>,
    len: usize,
    head: usize,
    cap: usize,
}


/** 
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MyCircularDeque {

    fn new(k: i32) -> Self {
        assert!(k > 0);
        let mut buff = Vec::with_capacity(k as usize);
        unsafe { buff.set_len(k as usize); }
        Self {
            buff: buff,
            len: 0,
            head: 0, 
            cap: k as usize,
        }
    }

    fn insert_front(&mut self, val: i32) -> bool {
        if self.is_full() {
            return false;
        }
        let (head, cap) = (self.head, self.cap);
        let idx = (head + cap - 1) % cap;
        self.buff[idx] = val;
        self.head = idx;
        self.len += 1;
        true
    }

    fn insert_last(&mut self, val: i32) -> bool {
        if self.is_full() {
            return false;
        }
        let (head, len, cap) = (self.head, self.len, self.cap);
        let idx = (head + len) % cap;
        self.buff[idx] = val;
        self.len += 1;
        true
    }

    fn delete_front(&mut self) -> bool {
        if self.is_empty() {
            return false;
        }
        self.head = (self.head + 1) % self.cap;
        self.len -= 1;
        true
    }

    fn delete_last(&mut self) -> bool {
        if self.is_empty() {
            return false;
        }
        self.len -= 1;
        true
    }

    fn get_front(&self) -> i32 {
        if self.is_empty() {
            return -1;
        }
        self.buff[self.head]
    }

    fn get_rear(&self) -> i32 {
        if self.is_empty() {
            return -1;
        }
        self.buff[(self.head + self.len + self.cap - 1) % self.cap]
    }

    fn is_empty(&self) -> bool {
        self.len == 0
    }

    fn is_full(&self) -> bool {
        self.cap == self.len
    }
}

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * let obj = MyCircularDeque::new(k);
 * let ret_1: bool = obj.insert_front(value);
 * let ret_2: bool = obj.insert_last(value);
 * let ret_3: bool = obj.delete_front();
 * let ret_4: bool = obj.delete_last();
 * let ret_5: i32 = obj.get_front();
 * let ret_6: i32 = obj.get_rear();
 * let ret_7: bool = obj.is_empty();
 * let ret_8: bool = obj.is_full();
 */
