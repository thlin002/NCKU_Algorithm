#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	int N;
	cin >> N;
	vector<int> a(N);
	for(int i = 0; i < N; ++i){
		cin >> a[i];
	}

	if(N == 1){
		cout << 0;
		return 0;
	}

	int max = 0;
	int min = 1000000001;
	for(int i = 0; i < N; ++i){
		if(a[i] > max)
			max = a[i];
		if(a[i] < min)
			min = a[i];
	}

	//cout << "hello before push" << endl;  // endl flush out stream
	float s_Intval = (float)(max - min)/(N-1);
	vector<vector<int>> s(N);
	vector<int> slot_max(N,0);
	vector<int> slot_min(N,1000000001);
	vector<int> non_empty;

	int slot_loc; 
	for(int i = 0; i < N; ++i){
		slot_loc = (int)((a[i]-min)/s_Intval);
		s[slot_loc].push_back(a[i]);
		if(s[slot_loc].size() == 1)
			non_empty.push_back(slot_loc);		
		if(a[i] > slot_max[slot_loc])
			slot_max[slot_loc] = a[i];
		if(a[i] < slot_min[slot_loc])
			slot_min[slot_loc] = a[i];
	}
	//cout << "hello after push" << endl;
	/*
	for(int i = 0; i < non_empty.size(); ++i){
		cout << non_empty[i];
	}
	cout << endl;
	*/
	int gap = 0;
	//int jmp;
	for(int i = 0; i < non_empty.size()-1; ++i){
		if( gap < slot_min[non_empty[i+1]] - slot_max[non_empty[i]]){
			gap = slot_min[non_empty[i+1]] - slot_max[non_empty[i]];
		}
		
		/*
		if(s[i].size() != 0 ){
			// go around the empty slots
			jmp = 1;
			while(s[i+jmp].size() == 0){
				++jmp;
			}
			
			if(gap < slot_min[i+jmp] - slot_max[i])
				gap = slot_min[i+jmp] - slot_max[i];
		}
		*/
	}
	cout << gap;

/*
	for(int i = 0; i < N; ++i){
		cout << ap[i];
	}
*/

	return 0;
}
