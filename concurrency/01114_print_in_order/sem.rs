#[derive(Clone)]
struct Sem {
    count: Arc<(Mutex<usize>, Condvar)>,
}

impl Sem {
    fn new(val: usize) -> Self {
        Self {
            count: Arc::new((Mutex::new(val), Condvar::new())),
        }
    }

    fn wait(&self) {
        let (lock, cv) = &*self.count;
        let mut count = lock.lock().unwrap();
        while *count == 0 {
            count = cv.wait(count).unwrap();
        }
        *count = 0;
    }

    fn post(&self) {
        let (lock, cv) = &*self.count;
        let mut count = lock.lock().unwrap();
        *count = 1;
        cv.notify_one();
    }
}


struct Foo {
    states: [Sem; 3],
}

impl Foo {
    fn new() -> Self {
        Foo {
            states: [Sem::new(1), Sem::new(0), Sem::new(0)],
        }
    }

    fn first<F>(&self, print_first: F)
    where
        F: FnOnce(),
    {
        self.states[0].wait();
        // Do not change this line
        print_first();
        self.states[1].post();
    }

    fn second<F>(&self, print_second: F)
    where
        F: FnOnce(),
    {
        self.states[1].wait();
        // Do not change this line
        print_second();
        self.states[2].post();
    }

    fn third<F>(&self, print_third: F)
    where
        F: FnOnce(),
    {
        self.states[2].wait();
        // Do not change this line
        print_third();
        self.states[0].post();
    }
}
