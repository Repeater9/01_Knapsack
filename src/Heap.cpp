#include "Heap.h"

void swap(Node &a,Node &b)
{
    Node temp = a;
    a = b;
    b = temp;
}

bool Heap::compare(int a,int b) //type决定了我们建最大堆还是最小堆
{
    if(type == MAX_HEAP)
        return a > b;
    else
        return a < b;
}

Heap::Heap()
{
    heapBase = nullptr;
    length = 0;
    heapSize = 0;
    type = MAX_HEAP;
}

Heap::Heap(Node *Base, int Length, int Size,int Type)
{
    heapBase = Base;
    length = Length;
    heapSize = Size;
    type = Type;
}

void Heap::setLength(int Length)
{
    length = Length;
}

void Heap::setHeapSize(int Size)
{
    heapSize = Size;
}

void Heap::setHeapBase(Node *Base)
{
    heapBase = Base;
}

int Heap::getHeapLength() const
{
    return length;
}

int Heap::getHeapSize() const
{
    return heapSize;
}

Node *Heap::getHeapBase() const
{
    return heapBase;
}

void Heap::heapAdjust(int i)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int temp;
    if(l <= heapSize && compare(heapBase[l].cost,heapBase[i].cost))
    {
        temp = l;
    }
    else
        temp = i;
    if(r <= heapSize && compare(heapBase[r].cost,heapBase[temp].cost))
    {
        temp = r;
    }
    if(temp != i)
    {
        swap(heapBase[i],heapBase[temp]);
        heapAdjust(temp);
    }
}

void Heap::buildHeap()
{
    int i;
    for(i = length / 2;i >= 1;i--)
    {
        heapAdjust(i);
    }
}

void Heap::heapSort()
{
    int temp = heapSize;
    int i;
    for(i = length;i >= 2;i--)
    {
        swap(heapBase[1],heapBase[i]);
        heapSize--;
        heapAdjust(1);
    }
    heapSize = temp;                            //恢复heapSize
}

int Heap::topValue() const
{
    return heapBase[1].cost;
}

void Heap::extractTop(Node &p)
{
    if(heapSize < 1)
        return;
    p.cost = heapBase[1].cost;
    p.weight = heapBase[1].weight;
    p.isPreviousSelected = heapBase[1].isPreviousSelected;
    p.number = heapBase[1].number;
    p.pre = heapBase[1].pre;
    heapBase[1] = heapBase[heapSize];
    heapSize--;
    length--;
    heapAdjust(1);
}

void Heap::changeElement(int i,int key)
{
    if(!compare(key,heapBase[i].cost))
    {
        return;
    }
    heapBase[i].cost = key;
    while(i > 1 && compare(heapBase[i].cost, heapBase[PARENT(i)].cost))
    {
        swap(heapBase[PARENT(i)],heapBase[i]);
        i = PARENT(i);
    }
}

void Heap::insert(Node p)
{
    heapSize++;
    length++;
    heapBase[heapSize] = p;
    if(type == MAX_HEAP)
    {
        heapBase[heapSize].cost = INT_NEG_INF;
    }
    else heapBase[heapSize].cost = INT_INF;
    changeElement(heapSize,p.cost);
}