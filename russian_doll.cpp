#include <iostream>
#include <vector>
using namespace std;

	
int compar (const void* a, const void* b){
    if ( *(int*)a <  *(int*)b ) 
        return 1;
    else if ( *(int*)a == *(int*)b ) 
        return 0;
    else
        return -1;
}

int russian_doll(int* arr, vector<int> pnt, int N){
    vector<int> set;
    vector<int> pnt_nxt;
    set.push_back(arr[pnt[0]]);
    int k = 0;
    for(int i = 1; i < N; ++i){
        if(arr[pnt[i]] < set[k]){
            set.push_back(arr[pnt[i]]);
            ++k;
        }else if(arr[pnt[i]] == set[k]){
            pnt_nxt.push_back(pnt[i]);
        }
    }
    for(int i = set.size()-1; i >= 0; --i){
        cout << set[i] << " ";
    }
    cout << endl;
    if(pnt_nxt.size()!=0){
        return russian_doll(arr, pnt_nxt, pnt_nxt.size());
    }else{
        return 0;
    }
}


int main(){
    int N;
    cin >> N;
    int* M = (int*)malloc(sizeof(int)*N);
    vector<int> P(N);
    
    for(int i = 0; i < N; ++i){
        cin >> M[i];
        P[i] = i;
    }   
    
    qsort(M, N, sizeof(int), compar);
/*
    for(int i = 0; i < N; ++i){
        cout << M[i] << " ";
    }
*/

    russian_doll(M, P, N);

}
