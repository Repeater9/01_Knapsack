#ifndef __KNAPSACK_H__
#define __KNAPSACK_H__

#define MAX_NUM 30
#define NUM_OF_DATASET 8
#define NUM_OF_FILE 3

typedef struct{
    int w, p, index;//物品重量，价值和编号。
}Item;

class Knapsack{
public:
    Knapsack(int caseindex);
    void gdByProfit() const;
    void gdByProfitDensity() const;
    void K_optimal(int k) const;
    void FIFO() const;
    void LC() const;
    void Backtracking() const;
    void dp() const;
    void printinfo() const;
    
private:
    int c, num;         //背包大小和物品个数
    //int ans[MAX_NUM];
    Item item[MAX_NUM];         //背包物品
};

#endif