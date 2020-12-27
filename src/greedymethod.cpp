#include<iostream>
#include<algorithm>
#include<cstring>
#include "Knapsack.h"

using namespace std;

bool cmpByProfit(Item a, Item b) {
    return a.p > b.p;
}

bool cmpByProfitDensity(Item a, Item b) {
    return (double)a.p / a.w > (double)b.p / b.w;
}

void Knapsack::gdByProfit() const {
    Item* temp = new Item[num];
    bool* ans = new bool[num];
    for (int i = 0; i < num; i++) {
        temp[i] = item[i];
        ans[i] = 0;
        //printf("%d %d %d\n",temp[i].index,temp[i].p,temp[i].w);
    }//initial

    sort(temp, temp + num, cmpByProfit);//sort by profit
    int cc = 0, cp = 0;
    for (int i = 0; i < num; i++) {
        if (cc + temp[i].w <= c) {
            cc += temp[i].w;
            cp += temp[i].p;
            ans[temp[i].index] = 1;
        }
    }//greedy method

    cout << "Greedy by profit:";
    for (int i = 0; i < num;i++) {
        cout << " " << ans[i];
    }
    cout << endl << "Used capacity: " << cc << "\t" << "Current profit: " << cp << endl << endl;
    //print answer
    delete[] temp;
    delete[] ans;
}//按价值贪心


void Knapsack::gdByProfitDensity() const {
    Item* temp = new Item[num];
    bool* ans = new bool[num];
    for (int i = 0; i < num; i++) {
        temp[i] = item[i];
        ans[i] = 0;
    }//initial

    sort(temp, temp + num, cmpByProfitDensity);//sort by profit density;
    int cc = 0, cp = 0;
    for (int i = 0; i < num; i++) {
        if (cc + temp[i].w <= c) {
            cc += temp[i].w;
            cp += temp[i].p;
            ans[temp[i].index] = 1;
        }
    }//greedy method

    cout << "Greedy by profit density:";
    for (int i = 0; i < num;i++) {
        cout << " " << ans[i];
    }
    cout << endl << "Used capacity: " << cc << "\t" << "Current profit: " << cp << endl << endl;
    //print answer
    delete[] temp;
    delete[] ans;
}//按价值密度贪心


void K_greed(Item* item, bool* bestans, bool* nowans, int num, int c, int& bestp) {
    int cc = 0;
    int cp = 0;
    for (int i = 0; i < num; i++) {
        if (nowans[i]) {
            cc += item[i].w;
            cp += item[i].p;
        }
    }//检测选择的物品是否符合条件
    //cout << cp << "test" << endl;
    if (cc > c) return;
    Item* temp = new Item[num];
    bool* ans = new bool[num];
    for (int i = 0; i < num; i++) {
        temp[i] = item[i];
        ans[i] = nowans[i];
    }

    sort(temp, temp + num, cmpByProfitDensity);
    for (int i = 0; i < num; i++) {
        if (!ans[temp[i].index] && cc + temp[i].w <= c) {
            cc += temp[i].w;
            cp += temp[i].p;
            ans[temp[i].index] = 1;
        }
    }//对剩下的物品按价值密度贪心

    if (cp > bestp) {
        bestp = cp;
        for (int i = 0; i < num;i++)
            bestans[i] = ans[i];
    }//更新当前k下的最优答案
    delete[] temp;
    delete[] ans;
}

void K_Choose(Item* item, bool* bestans, bool* nowans, int num, int ck, int c, int& bestp, int j) {
    if (ck == 0) {
        K_greed(item, bestans, nowans, num, c, bestp);
        return;
    }
    for (int i = j; i < num; i++) {
        if (nowans[i] != 1) {
            nowans[i] = 1;
            K_Choose(item, bestans, nowans, num, ck - 1, c, bestp, i + 1);
            nowans[i] = 0;
        }
    }
}//递归地选择ck个物品

void Knapsack::K_optimal(int k) const {
    if (k < 0) {
        cout << "invalid k" << endl;
        exit(0);
    }
    if (k > num) {
        cout << "let k = " << num << endl;
        k = num;
    }//输入k

    bool* nowans = new bool[num];      //当前答案
    bool* kbestans = new bool[num]; //K_optimal的最优解
    bool* bestans = new bool[num];  //对于k=0,1,2...的最优答案
    int kbestp = 0;                 //能装最多的价值
    int bestp = 0;                  //对于k=0,1,2...的能装最多价值

    for (int ck = 0; ck <= k;ck++) {
        memset(nowans,0,sizeof(bool)*num);
        memset(bestans,0,sizeof(bool)*num);
        
        bestp = 0;//初始化

        K_Choose((Item*)item, bestans, nowans, num, ck, c, bestp, 0);//进行选择

        cout << "For k = " << ck << " :" << endl;
        cout << "s" << ck << " =";
        for (int i = 0; i < num;i++) {
            cout << " " << bestans[i];
        }
        cout << endl << "p" << ck << ": " << bestp << endl;//输出对于k=0,1,2...的答案

        if (bestp > kbestp) {
            kbestp = bestp;
            for (int i = 0; i < num;i++)
                kbestans[i] = bestans[i];
        }//更新最优答案
    }

    cout << "K-optimal(" << "k = " << k << "):";
    int cc = 0;
    for (int i = 0; i < num;i++) {
        cout << " " << kbestans[i];
        if (kbestans[i]) cc += item[i].w;
    }
    cout << endl << "Used capacity: " << cc << "\t" << "Current profit: " << kbestp << endl << endl;//输出最优解

    delete[] nowans;
    delete[] kbestans;
    delete[] bestans;
}
