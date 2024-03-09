//Redraiment����÷��׮�ĸ��֡�Redraiment����ѡ������һ����㣬��ǰ����
//��ֻ�ܴӵʹ����ߴ���׮���ߡ�
//��ϣ���ߵĲ�����࣬������Redraiment�о�������ߵĲ�����

//����������У���һ����̬�滮����
#include<iostream>
#include<vector>
using namespace std;

//dp[i]��ʾ���ǵ�arr[i]ʱ����������еĳ��ȣ���ʼ��ȫΪ1��
//ʹ��˫��ѭ����j����arr[],�������С����ô������dp[i]��ֵ,
/*
# ÷��׮_��̬�滮
# ���ڳ�ʼ��
# ���� dp �д洢�Ŷ�Ӧ nums λ�õ�׮�����������Դ�����ʱ��Ĭ��Ϊ 1����Ϊ��ǰ׮�������һ����
# ����״̬ת�Ʒ���
# ���� nums[j] < nums[i]����ɨ�� i ǰ���׮��
# ����б� i С�Ļ���ʹ��״̬ת�Ʒ��� dp[i] = max(dp[i], dp[j] + 1)��
# ���̵���˼�ǡ����������ǰ��ĳ��׮��׮j���� ׮i С����ô���Ǹ�׮���� ׮i �Ļ���Ȼ�Ͷ���һ����
# �������������֮��Ĳ��� dp[j] + 1 ����ǰ�洢������� dp[i] �Ƚ�һ�£�
# ѡ����ķŽ�ȥ��
*/
int lis(vector<int>& arr) 
{
    vector<int> dp(arr.size(), 1); 
    int max = 1;
    for (int i = 1; i < arr.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = (dp[i]>dp[j] + 1)?dp[i]:dp[j]+1; 
                max = max > dp[i] ? max : dp[i]; //������󳤶�
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
        for (int i = 0; i < n; i++) //����
            cin >> arr[i];
        cout << lis(arr) << endl; //��������������г���
    }
    return 0;
}
