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

        //P.gdByProfit();
        //P.gdByProfitDensity();
        //P.K_optimal(K);
        //P.dp();
        //P.Backtracking();
        //P.FIFO();
        //P.LC();

        cout << "-------------------------------------------\n";
    }
    return 0;
}
