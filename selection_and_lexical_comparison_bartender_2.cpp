#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

typedef struct {
    string name;
    int num;
} ctail;


void swap(vector<ctail> &arr, int a, int b){
    int t_num;
    string t_name;
    t_name = arr[a].name;
    t_num = arr[a].num;

    arr[a].name = arr[b].name;
    arr[a].num = arr[b].num;
    arr[b].name = t_name;
    arr[b].num = t_num;
} 

// lexigraphical order comparison
int lex_com(string a, string b, int i){
    if(a[i] < b[i]){
        return 1;
    }else if(a[i] == b[i]){
        return lex_com(a, b, i+1);
    }else{
        return 0;
    }
}

int partition(vector<ctail> &arr, int p, int r)
{
    int i = p;
    for(int j = p; j < r; ++j){
        //cout << arr[j].base << " " << arr[r].base << endl;
        if(arr[j].num > arr[r].num){
            //cout << "swap" << endl;
            swap(arr, i, j);
            ++i;
        }else if(arr[j].num == arr[r].num){
            if( lex_com(arr[j].name, arr[r].name, 0) ){       
                swap(arr, i, j);
                ++i;
            }
        }
    }
    swap(arr, i, r);

    return i;
}

string kthBiggest(vector<ctail> &arr, int p, int r, int k)
{
    int q = partition(arr, p, r);

    //cout << q << endl;
    int index = q-p;
    if(index == k-1){
        //cout << "q == k" << endl;
        return arr[q].name;
    }else if(index > k-1){
        //cout << "q > k" << endl;
        return kthBiggest(arr, p, q-1, k);
    }else{
        //cout << "q < K" << endl;
        return kthBiggest(arr, q+1, r, k-(index+1)); // k-(q+1-p)
    }
}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    vector<string> namelist(N);
    vector<ctail> list;
    map<string, int> stoc;
    std::map<string,int>::iterator it;
    for(int i = 0; i < N; ++i){
        cin >> namelist[i];
        
        it = stoc.find(namelist[i]);
        if (it != stoc.end()){
            ++list[it->second].num;
        }

        if (it == stoc.end()){
            ctail tmp;
            tmp.name = namelist[i];
            tmp.num = 1;
            list.push_back(tmp);
            stoc[namelist[i]] = list.size()-1;
        }
    }

    int list_size = list.size();
/*
    for(int i = 0; i < list_size; ++i){
        cout << list[i].name << " " << list[i].num << endl;
    }
*/

    cout << kthBiggest(list, 0, list_size-1, K);
    return 0;
    
}