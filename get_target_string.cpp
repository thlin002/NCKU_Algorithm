#include<iostream>
#include<string>
using namespace std;

int main(){
    int T;
    cin >> T;
    for(int i = 0; i < T; ++i){
        string s;
        string t;
        cin >> s >> t;
        int loop_cnt = 0;
        int t_ind = 0;
        int t_flag;
        while(t_ind <= t.length()-1){    
            t_flag = 0;
            for(int j = 0; j < s.length(); ++j){
                if(s[j] == t[t_ind]){
                    t_flag = 1;
                    if(t_ind <= t.length()-1){
                        ++t_ind;
                    }                        
                }
            }
            if(t_flag){
                ++loop_cnt;
            }else{
                break;   
            }
        }
        if(t_flag)
            cout << loop_cnt << endl;
        else
            cout << -1 << endl;
    }  
    
    return 0;
}   