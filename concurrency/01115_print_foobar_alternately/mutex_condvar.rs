struct FooBar {
    n: usize,
    state: Mutex<u8>,
    cv: Condvar,
}

impl FooBar {
    fn new(n: usize) -> Self {
        FooBar { 
            n: n, 
            state: Mutex::new(0),
            cv: Condvar::new(),
        }
    }

    fn foo<F>(&self, print_foo: F)
    where
        F: Fn(),
    {
        for _ in 0..self.n {
            let mut state = self.state.lock().unwrap();
            while *state != 0 {
                state = self.cv.wait(state).unwrap();
            }
            // printFoo() outputs "foo". Do not change or remove this line.
            print_foo();
            *state = 1;
            self.cv.notify_all();
        }
    }

    fn bar<F>(&self, print_bar: F)
    where
        F: Fn(),
    {
        for _ in 0..self.n {
            let mut state = self.state.lock().unwrap();
            while *state != 1 {
                state = self.cv.wait(state).unwrap();
            }
            // printBar() outputs "bar". Do not change or remove this line.
            print_bar();
            *state = 0;
            self.cv.notify_all();
        }
    }
}
