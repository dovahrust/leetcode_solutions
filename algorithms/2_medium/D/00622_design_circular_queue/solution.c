typedef struct {
    size_t len;
    size_t cap;
    size_t start_idx;
    int arr[];
} MyCircularQueue;

bool myCircularQueueIsEmpty(MyCircularQueue* obj);
bool myCircularQueueIsFull(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k)
{
    assert(k > 0);
    MyCircularQueue* obj = malloc(sizeof(*obj) + sizeof(int) * (size_t)k);
    assert(obj != NULL);
    obj->len = 0;
    obj->cap = (size_t)k;
    obj->start_idx = 0;
    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value)
{
    if (myCircularQueueIsFull(obj)) {
        return false;
    }
    obj->arr[(obj->start_idx + obj->len) % obj->cap] = value;
    obj->len += 1;
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj)
{
    if (myCircularQueueIsEmpty(obj)) {
        return false;
    }
    obj->start_idx = (obj->start_idx + 1) % obj->cap;
    obj->len -= 1;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj)
{
     if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->arr[obj->start_idx];
}

int myCircularQueueRear(MyCircularQueue* obj)
{
    if (myCircularQueueIsEmpty(obj)) {
        return -1;
    }
    return obj->arr[(obj->start_idx + obj->len + obj->cap - 1) % obj->cap];
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj)
{
    return obj->len == 0;
}

bool myCircularQueueIsFull(MyCircularQueue* obj)
{
    return obj->len == obj->cap;
}

void myCircularQueueFree(MyCircularQueue* obj)
{
    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/
