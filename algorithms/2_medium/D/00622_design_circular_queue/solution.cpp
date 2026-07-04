class MyCircularQueue {
    size_t len;
    size_t cap;
    size_t start_idx;
    vector<int> arr;
public:
    MyCircularQueue(int k) {
        assert(k > 0);
        arr = vector<int>(k, 0),
        len = 0,
        cap = k;  
        start_idx = 0;
    }

    bool enQueue(int value) {
         if (isFull()) {
            return false;
        }
        arr[(start_idx + len) % cap] = value;
        len += 1;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        start_idx = (start_idx + 1) % cap;
        len -= 1;
        return true;
    }

    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return arr[start_idx];
    }

    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return arr[(start_idx + len + cap - 1) % cap];
    }

    bool isEmpty() {
        return len == 0;
    }

    bool isFull() {
        return len == cap;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
