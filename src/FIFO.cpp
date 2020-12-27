#include "Knapsack.h"
#include<string>
#include<queue>
#include <iostream>

using namespace std;

typedef struct node{
    int lowerBound;         //成本下界
    int upperBound;         //成本上界
    int number;             //结点对应的物品编号
    int weight;             //当前重量
    int isPreSelected;      //该结点之前的结点是否被选
    struct node* pre;       //前驱结点
}Node;

queue <Node*> Q;

void updateAnswer(int *ans,Node *p, Node *q)
{
    while(p != q)
    {
        ans[p->pre->number] = p->isPreSelected;
        p = p->pre;
    }
}

void Knapsack::FIFO() const
{
    int *ans = (int *)malloc(num * sizeof(int));
    int bestCost = 0;
    for(int i = 0;i < num;i++)                      //初始化最优成本值
    {
        bestCost += item[i].p;
    }
    Node *start = (Node *)malloc(sizeof(Node));
    start->lowerBound = 0;   start->upperBound = bestCost;
    start->number = 0;       start->weight = 0;
    start->isPreSelected = -1;
    Q.push(start);
    while(!Q.empty())
    {
        Node *Front = Q.front();
        Q.pop();
        if(Front->lowerBound == Front->upperBound)
        {
            updateAnswer(ans,Front,start);
            continue;
        }
        for(int i = 0;i < 2;i++)
        {
            Node *Next = (Node *)malloc(sizeof(Node));
            if(i == 0)
            {
                Next->lowerBound = Front->lowerBound;
                Next->upperBound = Front->upperBound - item[Front->number].p;
                Next->weight = Front->weight + item[Front->number].w;
                Next->isPreSelected = 1;
            }
            else
            {
                Next->lowerBound = Front->lowerBound + item[Front->number].p;
                Next->upperBound = Front->upperBound;
                Next->weight = Front->weight;
                Next->isPreSelected = 0;
            }
            if(Next->lowerBound > bestCost || Next->weight > c)
            {
                continue;
            }
            Next->number = Front->number + 1;
            Next->pre = Front;
            if(Next->upperBound < bestCost)
            {
                bestCost = Next->upperBound;
            }
            Q.push(Next);
        }
    }
    int sum = 0;
    cout << "FIFO result:\n";
    for(int i = 0;i < num;i++)
    {
        sum += ans[i] * item[i].p;
        cout<< ans[i] << " ";
    }
    cout << "\nTotal value: " << sum << endl;
    cout << endl;
    free(ans);
}