#include "Knapsack.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static int cw, cp, bestp, capacity, n;
static Item *temp;
static int *ans;
static int *x;

bool compare(Item a, Item b)
{
    return (double)a.p / a.w > (double)b.p / b.w;
}

double Bound(int i)
{
    int cLeft = capacity - cw;
    double b = (double)cp;
    while(i <= n - 1 && temp[i].w <= cLeft)
    {
        cLeft = cLeft - temp[i].w;
        b += (double)temp[i].p;
        i++;
    }
    if(i <= n - 1)
    {
        b += (double)cLeft * (double)temp[i].p / temp[i].w;
    }
    return b;
}

void Backtrack(int i)
{
    if(i == n)
    {
        int k;
        for(k = 0; k < n; k++)
        {
            ans[k] = x[k];
        }
        bestp = cp;
        return;
    }

    if(cw + temp[i].w <= capacity)
    {
        x[temp[i].index] = 1;
        cw += temp[i].w;
        cp += temp[i].p;
        Backtrack(i + 1);
        cp -= temp[i].p;
        cw -= temp[i].w;
        x[temp[i].index] = 0;
    }
    
    if(Bound(i + 1) > (double)bestp)
    {
        x[temp[i].index] = 0;
        Backtrack(i + 1);
    }
}

void Knapsack::Backtracking() const
{
    cw = cp = bestp = 0;
    capacity = c;
    n = num;
    temp = (Item *)malloc(num * sizeof(Item));
    ans = (int *)malloc(num * sizeof(int));
    x = (int *)malloc(num * sizeof(int));
    int i;
    for(i = 0;i < num;i++)
    {
        temp[i] = item[i];
        ans[i] = 0;
        x[i] = 0;
    }
    sort(temp, temp + num, compare);
    Backtrack(0);
    cout << "Backtracking result:\n";
    for(i = 0; i < num; i++)
    {
        cout << ans[i] << " ";
    }
    cout << "\nTotal value: " << bestp << endl;
    cout << endl;
    free(temp);
    free(ans);
    free(x);
}