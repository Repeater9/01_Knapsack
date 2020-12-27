#include <iostream>
#include <string>
#include "Knapsack.h"
#include <time.h>
#include <iomanip>

using namespace std;

void traceback(int n, int vacancy, int **fArray, int *x, const Item *item)
{
    for(int i = 0;i < n - 1;i++)
    {
        if(fArray[i][vacancy] == fArray[i + 1][vacancy])
        {
            x[i] = 0;
        }
        else
        {
            x[i] = 1;
            vacancy -= item[i].w;
        }
        //last one
        x[n - 1] = (fArray[n - 1][vacancy] > 0) ? 1 : 0;
    }
}

int f(int i, int n, int vacancy, int **fArray, const Item *item)
{
    //already computed
    if(fArray[i][vacancy] > 0)
        return fArray[i][vacancy];
    
    //last one
    if(i == n - 1)
    {
        fArray[i][vacancy] = (vacancy >= item[i].w) ? item[i].p : 0;
        return fArray[i][vacancy];
    }

    //can take
    if(vacancy >= item[i].w)
    {
        int take = item[i].p + f(i + 1, n, vacancy - item[i].w, fArray, item);
        int notake = f(i + 1, n, vacancy, fArray, item);
        if(take > notake)
        {
            fArray[i][vacancy] = take;
        }
        else
        {
            fArray[i][vacancy] = notake;
        }
        return fArray[i][vacancy];
    }

    //can't take
    fArray[i][vacancy] = f(i + 1, n, vacancy, fArray, item);
    return fArray[i][vacancy];
}

void Knapsack::dp() const
{
    clock_t start, end;
    double duration;
    start = clock();
    int **fArray = new int*[num];
    for(int i = 0;i < num;i++)
        fArray[i] = new int [c + 1];

    for(int i = 0; i < num ; i++)
    {
        for(int j = 0; j < num; j++)
        {
            fArray[i][j] = 0;
        }
    }
    int result = f(0, num, c, fArray, item);
    int *x = new int [num];
    traceback(num, c, fArray, x, item);
    printf("Dp result:\n");
    for(int i = 0; i < num; i++)
    {
        printf("%d ", x[i]);
    }
    printf("\n");
    printf("Total Value: %d\n",result);
    delete []x;

    for(int i = 0;i < num;i++)
        delete []fArray[i];
    delete []fArray;

    end = clock();
    duration = (double) (end - start) / CLOCKS_PER_SEC;
    cout << "Run time: " << fixed << setprecision(4) << duration << "s" << endl;
    printf("\n");
}