//Redraiment是走梅花桩的高手。Redraiment可以选择任意一个起点，从前到后，
//但只能从低处往高处的桩子走。
//他希望走的步数最多，你能替Redraiment研究他最多走的步数吗？

//最长上升子序列，是一个动态规划问题
#include<iostream>
#include<vector>
using namespace std;

//dp[i]表示的是到arr[i]时最长上升子序列的长度，初始化全为1；
//使用双层循环，j遍历arr[],如果出现小于那么就增加dp[i]的值,
/*
# 梅花桩_动态规划
# 关于初始化
# 数组 dp 中存储着对应 nums 位置的桩最大次数，所以创建的时候默认为 1，因为当前桩本身就是一步。
# 关于状态转移方程
# 其中 nums[j] < nums[i]，即扫描 i 前面的桩，
# 如果有比 i 小的话就使用状态转移方程 dp[i] = max(dp[i], dp[j] + 1)，
# 方程的意思是————如果前面某个桩（桩j）比 桩i 小，那么从那个桩踩上 桩i 的话自然就多了一步，
# 我们拿这个踩完之后的步数 dp[j] + 1 跟当前存储的最大步数 dp[i] 比较一下，
# 选个大的放进去。
*/
int lis(vector<int>& arr) 
{
    vector<int> dp(arr.size(), 1); 
    int max = 1;
    for (int i = 1; i < arr.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = (dp[i]>dp[j] + 1)?dp[i]:dp[j]+1; 
                max = max > dp[i] ? max : dp[i]; //更新最大长度
            }
        }
    }
    return max;
}

int main() 
{
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) //输入
            cin >> arr[i];
        cout << lis(arr) << endl; //计算最长递增子序列长度
    }
    return 0;
}
