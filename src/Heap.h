#ifndef __HEAP_H__
#define __HEAP_H__

#define LEFT(i) 2 * i
#define RIGHT(I) 2 * i + 1
#define PARENT(i) i / 2
#define INT_NEG_INF 0x80000000
#define INT_INF 0x7fffffff

#define MAX_HEAP 0
#define MIN_HEAP 1

typedef struct {
    int cost;
    int isPreviousSelected;
    int number;
    int weight;
    int pre;
}Node;

class Heap{
public:
    Heap();
    Heap(Node *Base, int Length, int Size, int Type);
    bool compare(int a, int b);
    void setLength(int Length);
    void setHeapSize(int Size);
    void setHeapBase(Node *Base);
    int getHeapLength() const;
    int getHeapSize() const;
    Node *getHeapBase() const;
    void heapAdjust(int i);
    void buildHeap();
    void heapSort();
    int topValue() const;
    void extractTop(Node &p);
    void changeElement(int i, int key);
    void insert(Node p);

private:
    Node *heapBase;
    int length;
    int heapSize;
    int type;
};

#endif