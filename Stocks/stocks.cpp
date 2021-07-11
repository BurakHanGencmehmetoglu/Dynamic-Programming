#include <iostream>
#include <vector>
#include <random>
#include <chrono>   




int get_max_index(int* arr,int index) {
    int max = arr[1];
    int max_index = 1;
    for (int i=1;i<index;i++){
        if (arr[i] > max) {
            max = arr[i];
            max_index = i;
        }
    }
    return max_index;
}




int BuyStocks (int**& market, int n1, int n2, vector<int>& solution)
{
    int profit = 0;
    
    if (n1==n2)
    {
        for (int i=0;i<n1;i++) {
            solution.push_back(i);
            profit += market[i][i];
        }
        return profit;
    }
    
    else {
        int** s = new int*[n1+1];
        for (int i=0;i<=n1;i++)
            s[i] = new int[n2+1];
        for (int i=0;i<=n2;i++)
            s[0][i] = 0;
        for (int i=0;i<=n1;i++)
            s[i][0] = 0;
        for (int i=1;i<=n1;i++) {
            for (int j=1;j<=n2;j++)
                s[i][j] = -100000;
        }
        for (int i=1;i<=n1;i++) {
            for (int j=i;j<=n2-(n1-i);j++) {
                int max = -100000;
                for (int k=i-1;k<=j-1;k++) {
                    if (market[i-1][j-1] + s[i-1][k] > max) {
                        max = market[i-1][j-1] + s[i-1][k];
                        s[i][j] = max;
                    }
                    else {
                        continue;
                    }
                }
            }
        }

        profit = s[n1][get_max_index(s[n1],n2+1)];
        
        int limit_index = n2+1;
        
        for (int i=n1;i>=1;i--)
        {
            int new_limit = get_max_index(s[i],limit_index);
            solution.insert(solution.begin(),new_limit-1);
            limit_index = new_limit; 
        }
        
        for (int i=0;i<=n1;i++)
            delete [] s[i];
        delete [] s;        
        return profit;  
    }
}