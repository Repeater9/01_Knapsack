#include "Knapsack.h"
#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

#define K 4

int main()
{
    int i;
    cout << "-------------------------------------------\n";
    for(i = 1 ;i <= 8; i++)
    {
        cout << "For dataset " << i << ":" << endl;
        Knapsack P(i);
        cout << endl;

        clock_t start, end;
        double duration;
        start = clock();

        //P.gdByProfit();
        //P.gdByProfitDensity();
        //P.K_optimal(K);
        //P.dp();
        //P.Backtracking();
        //P.FIFO();
        P.LC();

        end = clock();
        duration = (double) (end - start) / CLOCKS_PER_SEC;
        cout << "Run time: " << fixed << setprecision(4) << duration << "s" << endl;

        cout << "-------------------------------------------\n";
    }
    return 0;
}