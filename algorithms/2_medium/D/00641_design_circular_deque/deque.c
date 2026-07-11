typedef struct {
    size_t len;
    size_t head;
    size_t cap;
    int buff[];
} MyCircularDeque;

bool myCircularDequeIsEmpty(MyCircularDeque* obj);
bool myCircularDequeIsFull(MyCircularDeque* obj);

MyCircularDeque* myCircularDequeCreate(int k)
{
    assert(k > 0);
    MyCircularDeque* res = malloc(sizeof(*res) + (size_t)k * sizeof(int));
    assert(res != NULL);
    res->len = 0;
    res->cap = (size_t)k;
    res->head = 0;
    return res;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int val)
{
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    const size_t head = obj->head;
    const size_t cap = obj->cap;
    const size_t idx = (head + cap - 1) % cap;
    obj->buff[idx] = val;
    obj->head = idx;
    obj->len += 1;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int val)
{
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    const size_t head = obj->head;
    const size_t cap = obj->cap;
    const size_t len = obj->len;
    const size_t idx = (head + len) % cap;
    obj->buff[idx] = val;
    obj->len += 1;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    obj->head = (obj->head + 1) % obj->cap;
    obj->len -= 1;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    obj->len -= 1;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj)
{
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->buff[obj->head];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->buff[(obj->head + obj->len + obj->cap - 1) % obj->cap];
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj)
{
    return obj->len == 0;
}

bool myCircularDequeIsFull(MyCircularDeque* obj)
{
    return obj->len == obj->cap;
}

void myCircularDequeFree(MyCircularDeque* obj)
{
    free(obj);
}

/**
 * Your MyCircularDeque struct will be instantiated and called as such:
 * MyCircularDeque* obj = myCircularDequeCreate(k);
 * bool param_1 = myCircularDequeInsertFront(obj, value);
 
 * bool param_2 = myCircularDequeInsertLast(obj, value);
 
 * bool param_3 = myCircularDequeDeleteFront(obj);
 
 * bool param_4 = myCircularDequeDeleteLast(obj);
 
 * int param_5 = myCircularDequeGetFront(obj);
 
 * int param_6 = myCircularDequeGetRear(obj);
 
 * bool param_7 = myCircularDequeIsEmpty(obj);
 
 * bool param_8 = myCircularDequeIsFull(obj);
 
 * myCircularDequeFree(obj);
*/
