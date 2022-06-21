#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef struct node{
	int valid;	// valid means that there is road for 1, no road for 0;
	int state; // state represents if the node has been searched or not, and by whom, 0 not discovered, 1 discovered by s, 2 discovered by t
	int dis;	// the distance from the search origin, may it be s or t
} node;

int search(queue<int*> &Q, int by, int &p, int &d, vector<vector<node>> &Maze, int N, int M){
    int* root;
    if(Q.size() > 0)
        root = Q.front();
    else
        return 0;

    Q.pop();
    if(root[0] > 0 && Maze[root[0]-1][root[1]].valid == 1){
        if(Maze[root[0]-1][root[1]].state == 0){       // actions on undiscovered node
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0]-1;
            ptr[1] = root[1];
            Maze[ptr[0]][ptr[1]].state = by;
			Maze[ptr[0]][ptr[1]].dis = Maze[root[0]][root[1]].dis + 1;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]-1][root[1]].state != by){    // actions if the node from another origin is discovered.
            d = Maze[root[0]][root[1]].dis + Maze[root[0]-1][root[1]].dis + 1; // return the total distance
			return 1;
        }
    }
    if(root[0] < N-1 && Maze[root[0]+1][root[1]].valid == 1){
        if(Maze[root[0]+1][root[1]].state == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0]+1;
            ptr[1] = root[1];
            Maze[ptr[0]][ptr[1]].state = by;
			Maze[ptr[0]][ptr[1]].dis = Maze[root[0]][root[1]].dis + 1;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]+1][root[1]].state != by){
			d = Maze[root[0]][root[1]].dis + Maze[root[0]+1][root[1]].dis + 1;
            return 1;
        }
    }
    if(root[1] > 0 && Maze[root[0]][root[1]-1].valid == 1){
        if(Maze[root[0]][root[1]-1].state == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0];
            ptr[1] = root[1]-1;
            Maze[ptr[0]][ptr[1]].state = by;
			Maze[ptr[0]][ptr[1]].dis = Maze[root[0]][root[1]].dis + 1;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]][root[1]-1].state != by){
			d = Maze[root[0]][root[1]].dis + Maze[root[0]][root[1]-1].dis + 1;
            return 1;
        }
    }
    if(root[1] < M-1 && Maze[root[0]][root[1]+1].valid == 1){
        if(Maze[root[0]][root[1]+1].state == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0];
            ptr[1] = root[1]+1;
            Maze[ptr[0]][ptr[1]].state = by;
			Maze[ptr[0]][ptr[1]].dis = Maze[root[0]][root[1]].dis + 1;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]][root[1]+1].state != by){
			d = Maze[root[0]][root[1]].dis + Maze[root[0]][root[1]+1].dis + 1;
            return 1;
        }
    }
    free(root);
    return 0;
}

void find_path(int S[2], int T[2], vector<vector<node>> &Maze, int N, int M){
    queue<int*> Qs;
    queue<int*> Qt;
    int ps = 1, pt = 1;
	int d;
    Qs.push(S);
    Qt.push(T);
    int i = 0;
    int found = 0;
    while(Qs.size() != 0 && Qt.size() != 0){
        if(ps < pt){
            found = search(Qs, 1, ps, d, Maze, N, M);
        }else{
            found = search(Qt, 2, pt, d, Maze, N, M);
        }

        /*
        cout << "===================================\n";
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                cout << Maze[i][j].state << " ";
            }
            cout << endl;
        }
        */

        if(found == 1){
            cout << d;	// +1 for the unaccounted last step
            return;
        }
    }
    cout << -1;
    return;
}

int main(){
    int N, M;
    int* S = (int*)malloc(sizeof(int) * 2);
    int* T = (int*)malloc(sizeof(int) * 2);
    cin >> N >> M;
    cin >> S[0] >> S[1] >> T[0] >> T[1];
    S[0]--;
    S[1]--;
    T[0]--;
    T[1]--;
    vector<vector<node>> Maze(N, vector<node>(M));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> Maze[i][j].valid;
            Maze[i][j].state = 0;
			Maze[i][j].dis = 0;
        }
    }
    
    find_path(S, T, Maze, N, M);


    return 0;
}
