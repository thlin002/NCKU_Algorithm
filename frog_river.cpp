#include<iostream>
#include<vector>
using namespace std;

// If the frog wants to cross the river with a minimum distance hop, 
// when the frog encounters small rocks, it has to jump alternatively, 
// in other words, to skip a small rock immediately after steping on one.

struct rock{
    char s;
    int pos;
    int s_out; // -1: big rock, 0: small rock outbound, 1: small rock inbound
};

int crossing_gap(vector<struct rock> &rocks, int N, int len, int begin){        // N: the number of small rocks, len: the dist. between big rocks
    int max_dist = 0;
    // calculate the max distance hop in the outbound travel
    //cout << "outbound" << endl;
    int pre = begin;
    for(int i = begin+1; i <= begin+N+1; ++i){
        if(rocks[i].s_out == 1 || rocks[i].s_out == -1){
            int tmp_dist = rocks[i].pos - rocks[pre].pos;
            //cout << "rock i pos: " << rocks[i].pos << " | rock pre pos: " << rocks[pre].pos << " | tmp_dist: " << tmp_dist << "\n";
            if(tmp_dist > max_dist)
                max_dist = tmp_dist;
            pre = i;
        }
    }
    // calculate the max distance hop in the inbound travel
    //cout << "inbound" << endl;
    pre = begin;
    for(int i = begin+1; i <= begin+N+1; ++i){
        if(rocks[i].s_out == 0 || rocks[i].s_out == -1){
            int tmp_dist = rocks[i].pos - rocks[pre].pos;
            //cout << "rock i pos: " << rocks[i].pos << " | rock pre pos: " << rocks[pre].pos << " | tmp_dist: " << tmp_dist << "\n";
            if(tmp_dist > max_dist)
                max_dist = tmp_dist;
            pre = i;
        }
    }
    return max_dist;
}


int main(){
    int C;
    cin >> C;
    vector<int> max_dist(C, 0);
    for(int i = 0; i < C; ++i){
        //cout << "start input no.: " << i << endl;
        int N, r_len;;
        cin >> N >> r_len;
        vector<struct rock> rocks(N+2); // +2 plus the shores.
        vector<int> brock_ind(1, 0);

        // See the shore as a big rock
        rocks[0].s = 'b';
        rocks[0].pos = 0;
        rocks[0].s_out = -1;
        rocks[N+1].s = 'b';
        rocks[N+1].pos = r_len;
        rocks[N+1].s_out = -1;

        int small_ind = 0;      // index the small stones between big rocks
        for(int j = 1; j < N+1; ++j){       // 1- N+1 
            cin >> rocks[j].s >> rocks[j].pos;
            if(rocks[j].s == 'b'){
                brock_ind.push_back(j);
                small_ind = 0;
                rocks[j].s_out = -1;
            }else if(rocks[j].s == 's'){
                ++small_ind;
                if(small_ind % 2 == 1)
                    rocks[j].s_out = 1;
                else
                    rocks[j].s_out = 0;
            }
        }
        brock_ind.push_back(N+1);
        //cout <<  "done input no.: " << i <<endl;

        // break the problem into small problem. Each subproblem consists of small rocks between two big rocks
        for(int j = 0; j < brock_ind.size()-1; ++j){
            int N = brock_ind[j+1] - brock_ind[j] -1;
            int r_len = rocks[brock_ind[j+1]].pos - rocks[brock_ind[j]].pos;
            int tmp_dist = crossing_gap(rocks, N, r_len, brock_ind[j]);
            if(tmp_dist > max_dist[i])
                max_dist[i] = tmp_dist;
        }
    }
    
    for(int i = 0; i < C; ++i){
        cout << max_dist[i];
        if(i < C-1)
            cout << endl;
    }
    
    return 0;
}