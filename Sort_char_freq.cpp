#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct label{
    int code = 0;
    int count = 0;
};

void count_sort(vector<struct label>& A, vector<struct label>& B, int N, int l, int mode){
    vector<int> cnt(N, 0);
    if(mode == 0){
        for(int i = 0; i < l; ++i){
            ++cnt[A[i].code];
        }
        for(int i = 1; i < N; ++i){
            cnt[i] = cnt[i] + cnt[i-1]; 
        }
        for(int i = 0; i < l; ++i){
            B[cnt[A[i].code]-1] = A[i];
            --cnt[A[i].code];
        }
    } else{
        //cout << "start" << endl;
        for(int i = 0; i < l; ++i){
            ++cnt[A[i].count];
        }
        //cout << "counting done" << endl;
        for(int i = 1; i < N; ++i){
            cnt[i] = cnt[i] + cnt[i-1]; 
        }
        //cout << "cumulating done" << endl;
        for(int i = 0; i < l; ++i){
            B[l-cnt[A[i].count]] = A[i];
            --cnt[A[i].count];
        }
        //cout << "rearrange done" << endl;
    }
}

int main(){
    string s;
    cin >> s;
    int length = s.size()/sizeof(char);
    vector<struct label> info(length);
    vector<struct label> temp(length);
    int count[128];
    for(int i = 0; i < 128; ++i){
        count[i] = 0;
    }

    //vector<vector<int>> order(length);

    for(int i = 0; i < length; ++i){
        int code = (int)s[i];
        ++count[code];
    }
    for(int i = 0; i < length; ++i){
        info[i].code = (int)s[i];
        info[i].count = count[(int)s[i]];
    }
    /*
    for(int i = 0; i < length; ++i){
        cout << (char)info[i].code;
    }
    cout << endl;
    */
    
    count_sort(info, temp, 128, length, 0);
    /*
    for(int i = 0; i < length; ++i){
        cout << (char)temp[i].code << " / count: " << temp[i].count << " ///";
    }
    cout << endl;
    */
    count_sort(temp, info, 500000, length, 1);
    
    for(int i = 0; i < length; ++i){
        cout << (char)info[i].code;
    }
}