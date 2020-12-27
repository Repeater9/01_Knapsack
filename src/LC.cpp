#include "Heap.h"
#include "Knapsack.h"
#include<iostream>
#include<string>

using namespace std;

Node PriorityQueue[10000000];

Node temp[10000000];

void getAnswer(int *ans,int num,int count)
{
    int index = count - 1;
    int i;
    for(i = num - 1;i >= 0;i--)
    {
        ans[i] = temp[index].isPreviousSelected;
        index = temp[index].pre;
    }
}

void Knapsack::LC() const
{
    int count = 0;
    int *ans = (int *)malloc(num * sizeof(int));
    Node T;
    T.cost =  0;
    T.weight = 0;
    T.isPreviousSelected = -1;
    T.number = 0;
    T.pre = -1;
    Heap H(PriorityQueue,0,0,MIN_HEAP);
    H.insert(T);
    while(1)
    {
        Node p;
        H.extractTop(p);
        temp[count++] = p;
        if(p.number == num)
        {
            getAnswer(ans,num,count);
            break;
        }
        Node Next;
        int i;
        for(i = 0;i < 2;i++)
        {
            if(i == 0)
            {
                Next.cost = p.cost;
                Next.isPreviousSelected = 1;
                Next.weight = p.weight + item[p.number].w;
            }
            else
            {
                Next.cost = p.cost + item[p.number].p;
                Next.isPreviousSelected = 0;
                Next.weight = p.weight;
            }
            Next.number = p.number + 1;
            Next.pre = count - 1;
            if(Next.weight > c)
            {
                continue;
            }
            H.insert(Next);
        }
    }
    cout << "LC result:\n";
    int sum = 0;
    for(int i = 0;i < num;i++)
    {
        sum += ans[i] * item[i].p;
        cout << ans[i] << " ";
    }
    cout <<"\nTotal value: " << sum << endl;
    cout << endl;
    free(ans);
}
