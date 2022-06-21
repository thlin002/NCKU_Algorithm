#include <iostream>
#include <stack>
#include <set>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
using namespace std;

typedef set<int> mySet;
map<mySet, int> table;
vector<mySet> ind;

int conversion(mySet a){
    if(table.count(a)){
        return table[a];
    }else{
        
        ind.push_back(a);
        table.insert({a, ind.size()});
        return table[a];
        
       return 0;
    }
}

int main(){
    stack<int> s;
    vector<int> topSize;
    int N;
    cin >> N;
    for(int i = 0; i < N; ++i){
        mySet group;
        string cmd;
        cin >> cmd;
        if(cmd[0] == 'P'){
            s.push(conversion(group));
        }else if(cmd[0] == 'D'){
            s.push(s.top());
        }else{
            mySet tmp1(ind[s.top()-1]);
            s.pop();
            mySet tmp2(ind[s.top()-1]);
            s.pop();

            
            if(cmd[0] == 'U'){
                set_union(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(group, group.begin()));
            }else if(cmd[0] == 'I'){
                set_intersection(tmp1.begin(), tmp1.end(), tmp2.begin(), tmp2.end(), inserter(group, group.begin()));
            }else{
                
                group = tmp2;
                group.insert(conversion(tmp1));
                
                
            }
            s.push(conversion(group));
            
        }
        topSize.push_back(ind[s.top()-1].size());
    }
	for(int i = 0; i < N; ++i){
        cout << topSize[i] << endl;
    }

}
