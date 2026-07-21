use std::sync::atomic::{AtomicU8, Ordering};

struct FooBar {
    n: usize,
    state: AtomicU8,
}

impl FooBar {
    fn new(n: usize) -> Self {
        FooBar { n: n, state: AtomicU8::new(0) }
    }

    fn foo<F>(&self, print_foo: F)
    where
        F: Fn(),
    {
        for i in 0..self.n {
            while self.state.load(Ordering::Acquire) != 0 {
                std::hint::spin_loop();
            }
            // printFoo() outputs "foo". Do not change or remove this line.
            print_foo();
            self.state.store(1, Ordering::Release);
        }
    }

    fn bar<F>(&self, print_bar: F)
    where
        F: Fn(),
    {
        for i in 0..self.n {
            while self.state.load(Ordering::Acquire) != 1 {
                std::hint::spin_loop();
            }
            // printBar() outputs "bar". Do not change or remove this line.
            print_bar();
            self.state.store(0, Ordering::Release);
        }
    }
}
