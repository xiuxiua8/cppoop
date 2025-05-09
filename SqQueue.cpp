#define MaxSize 50

typedef int ElemType;

typedef struct {
    ElemType data[MaxSize];
    int front, rear;
}SqQueue;

void InitQueue(SqQueue &Q);
bool QueueEmpty(SqQueue Q);
bool EnQueue(SqQueue &Q, ElemType x);
bool DeQueue(SqQueue &Q, ElemType &x);
bool GetHead(SqQueue Q, ElemType &x);
void DestroyQueue(SqQueue &Q);

void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

bool QueueEmpty(SqQueue Q) {
    return Q.front == Q.rear;
}

bool EnQueue(SqQueue &Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front)
        return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue&Q, ElemType &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

bool GetHead(SqQueue Q, ElemType &x) {
    if (Q.front == Q.rear)
        return false;
    x = Q.data[Q.front];
    return true;
}

void DestroyQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

int size(SqQueue Q) {
    return (Q.rear - Q.front + MaxSize) % MaxSize;
}   





