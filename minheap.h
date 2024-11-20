#include <stdlib.h>
#include <math.h>

typedef struct {
    int content;
    int prior;
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriQueue, *APriQueue;


APriQueue makeQueue(int capacity) {
    APriQueue h = (APriQueue) malloc(sizeof(PriQueue));
    h->elem = (ItemType *) malloc(capacity * sizeof(ItemType));
    h->capacity = capacity;
    h->size = 0;
    return h;
}

void free_q(APriQueue q) {
    free(q->elem);
    free(q);
}

int getLeftChild(int i) {
    return 2 * i + 1;
}

int getRightChild(int i) {
    return 2 * i + 2;
}

int getParent(int i) {
    return floor((i - 1) / 2);
}

void siftUp(APriQueue h, int idx) {
    int parent = getParent(idx);

    while (parent >= 0 && h->elem[parent].prior > h->elem[idx].prior) {
        ItemType aux = h->elem[parent];
        h->elem[parent] = h->elem[idx];
        h->elem[idx] = aux;

        idx = parent;
        parent = getParent(idx);
    }
}

void insert(APriQueue h, ItemType x) {
    int p = 0, pozitie = 0;
    for (int i = 0 ; i < h->size; i++) {
        if (x.content == h->elem[i].content) {
            p++;
            if (x.prior < h->elem[i].prior){
                pozitie = i;
                break;
            }
        }
    }
    if (p != 0) {
        for (int i = pozitie ; i < h->size - 1; i++) 
            h->elem[i] = h->elem[i + 1];
        h->elem[h->size-1] = x;
        siftUp(h, h->size - 1);
    }
    if (p == 0) {
        if (h->size == h->capacity) {
            h->capacity *= 2;
            h->elem = (ItemType *) realloc(h->elem, h->capacity * sizeof(ItemType));
        }
        h->elem[h->size] = x;
        h->size++;
        siftUp(h, h->size - 1);
    }
}

ItemType getMin(APriQueue h) {
    return h->elem[0];
}

void siftDown(APriQueue h, int idx) {
    int leftChild = getLeftChild(idx);
    int rightChild = getRightChild(idx);
    int smallest = idx;

    if (leftChild < h->size && h->elem[leftChild].prior < h->elem[smallest].prior) {
        smallest = leftChild;
    }

    if (rightChild < h->size && h->elem[rightChild].prior < h->elem[smallest].prior) {
        smallest = rightChild;
    }

    if (smallest != idx) {
        ItemType aux = h->elem[smallest];
        h->elem[smallest] = h->elem[idx];
        h->elem[idx] = aux;

        siftDown(h, smallest);
    }
}

ItemType removeMin(APriQueue h) {
    ItemType min = getMin(h);
    ItemType last = h->elem[h->size - 1];
    h->size--;
    h->elem[0] = last;
    siftDown(h, 0);

    return min;
}