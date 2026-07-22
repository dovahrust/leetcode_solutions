use std::sync::Condvar;

struct Sem {
    mtx: Mutex<u8>,
    cv: Condvar,
}

impl Sem {
    fn new(init_state: u8) -> Self {
        Self {
            mtx: Mutex::new(init_state),
            cv: Condvar::new(),
        }
    }

    fn wait(&self) -> u8 {
        let mut count = self.mtx.lock().unwrap(); 
        while *count == 0 {
            count = self.cv.wait(count).unwrap();
        }
        let ret_val = *count;
        *count = 0;
        ret_val
    }

    fn post(&self, state: u8) {
        let mut count = self.mtx.lock().unwrap();
        *count = state;
        self.cv.notify_one();
    }
}

struct ZeroEvenOdd {
    n: i32,
    states: [Sem; 3],
}

impl ZeroEvenOdd {
    fn new(n: i32) -> Self {
        assert!(n >= 1);
        ZeroEvenOdd {
            n: n,
            states: [Sem::new(1), Sem::new(0), Sem::new(0)],
        }
    }

    // print_number(x) prints the integer x
    fn zero<F>(&self, print_number: F)
    where
        F: Fn(i32),
    {
        for _ in 0..self.n {
            let state = self.states[0].wait();
            print_number(0);
            self.states[state as usize].post(1);
        }
    }

    fn odd<F>(&self, print_number: F)
    where
        F: Fn(i32),
    {
        for curr in (1..=self.n).step_by(2) {
            self.states[1].wait();
            print_number(curr);
            self.states[0].post(2);
        }
    }

    fn even<F>(&self, print_number: F)
    where
        F: Fn(i32),
    {
        for curr in (2..=self.n).step_by(2) {
            self.states[2].wait();
            print_number(curr);
            self.states[0].post(1);
        }
    }
}
