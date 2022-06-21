#include<iostream>
#include<vector>
#include<map>
using namespace std;
/*
Some ideas, see the backup code file.
*/
struct hw{
	int score;
	int time;
};

map<int, int> table[10000];		// a map for each row in v 2-D vector
vector<int> ind;

int conversion(int i, int a){
    if(table[i].count(a)){
        return table[i][a];
    }else{
        
        ind.push_back(a);
        table[i].insert({a, ind.size()});
        return table[i][a];
        
       return 0;
    }
}


int knapsack(vector<struct hw> &st, vector<vector<int>> &v, int i, int m){
	
	if(i == 0 || m == 0){
		return 0;
	}
	if(v[i].size() >= m+1){	// the element has been constructed
		return v[i][table[i][m]-1];
	}else{
		if(st[i-1].time > m){
			//cout << "arr[i]: " << arr[i] << " w: " << w << " arr[i] > w,  i-1: " << i-1 << endl; 
			v[i].push_back(knapsack(st, v, i-1, m));
			
		}else{
			//cout << "index "<< i-1 << ": " << arr[i-1] << endl;
			//cout << "weight :"<< w-arr[i-1] << endl;
			int a = knapsack(st, v, i-1, m-st[i-1].time) + st[i-1].score;
			int b = knapsack(st, v, i-1, m);
			if(a > b){
				v[i].push_back(a);
				//cout << "a: " << a << endl;
			}else{
				v[i].push_back(b);
				//cout << "b: " << b << endl;
			}				
		}
		table[i][m] = v[i].size();
		return v[i][table[i][m]-1];
	}
}

int main(){
	int N;
	int M;
	cin >> N >> M;
	vector<struct hw> st(N);
	for(int i = 0; i < N; ++i){
		cin >> st[i].score >> st[i].time;
	}

	vector<vector<int>> v(N+1);

	int result = knapsack(st, v, N, M);
	cout << result;
	return 0;
}
