//请实现一个计票统计系统。你会收到很多投票，
//其中有合法的也有不合法的，请统计每个候选人得票的数量以及不合法的票数。

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int is_valild(string vates, vector<pair<string, int>> candidates)
{
	for (int i = 0; i < candidates.size(); i++) {
		if (vates.compare(candidates[i].first) == 0)
			return i;
	}
	return -1;
}

int main() 
{
	int n_candi;
	while (cin >> n_candi) {
		vector<pair<string, int>> candidates;
		vector<string> votes;
		for (int i = 0; i < n_candi; i++) {
			string candi;
			cin >> candi;
			candidates.push_back(pair<string, int>(candi,0));
		}
		int n_votes;
		cin >> n_votes;
		int Invaild = 0;
		for (int i = 0; i < n_votes; i++) {
			string vote;
			cin >> vote;
			int identify = is_valild(vote, candidates);
			if (identify==-1) {
				Invaild++;
			}
			else {
				candidates[identify].second++;
			}
		}

		for (int i = 0; i < candidates.size(); i++) {
			cout << candidates[i].first << " : " << candidates[i].second << endl;
		}
		cout << "Invalid : " << Invaild << endl;
	}

	return 0;
}