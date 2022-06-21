#include<iostream>
#include<vector>
#include<queue>
using namespace std;


int search(queue<int*> &Q, int by, int &p, vector<vector<vector<int>>> &Maze, int N, int M){
    int* root;
    if(Q.size() > 0)
        root = Q.front();
    else
        return 0;

    Q.pop();
    
    if(root[0] > 0 && Maze[root[0]-1][root[1]][0] == 1){
        if(Maze[root[0]-1][root[1]][1] == 0){       // actions on undiscovered node
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0]-1;
            ptr[1] = root[1];
            Maze[root[0]-1][root[1]][1] = by;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]-1][root[1]][1] != by){    // actions if the node is discovered by from another origin.
            return 1;
        }
    }
    if(root[0] < N-1 && Maze[root[0]+1][root[1]][0] == 1){
        if(Maze[root[0]+1][root[1]][1] == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0]+1;
            ptr[1] = root[1];
            Maze[root[0]+1][root[1]][1] = by;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]+1][root[1]][1] != by){
            return 1;
        }
    }
    if(root[1] > 0 && Maze[root[0]][root[1]-1][0] == 1){
        if(Maze[root[0]][root[1]-1][1] == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0];
            ptr[1] = root[1]-1;
            Maze[root[0]][root[1]-1][1] = by;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]][root[1]-1][1] != by){
            return 1;
        }
    }
    if(root[1] < M-1 && Maze[root[0]][root[1]+1][0] == 1){
        if(Maze[root[0]][root[1]+1][1] == 0){
            int* ptr = (int*)malloc(sizeof(int) * 2);
            ptr[0] = root[0];
            ptr[1] = root[1]+1;
            Maze[root[0]][root[1]+1][1] = by;
            Q.push(ptr);
            ++p;
        }else if(Maze[root[0]][root[1]+1][1] != by){
            return 1;
        }
    }
    free(root);
    return 0;
}

void find_path(int S[2], int T[2], vector<vector<vector<int>>> &Maze, int N, int M){
    queue<int*> Qs;
    queue<int*> Qt;
    int ps = 1, pt = 1;
    Qs.push(S);
    Qt.push(T);
    int i = 0;
    int found = 0;
    while(Qs.size() != 0 && Qt.size() != 0){
        if(ps < pt){
            found = search(Qs, 1, ps, Maze, N, M);
        }else{
            found = search(Qt, 2, pt, Maze, N, M);
        }

        /*
        cout << "ps = " << ps << "  Pt = " << pt << endl;
        cout << "===================================\n";
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < M; ++j){
                cout << Maze[i][j][1] << " ";
            }
            cout << endl;
        }
        */

        if(found == 1){
            cout << "Success!";
            return;
        }
    }
    cout << "Fail!";
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
    vector<vector<vector<int>>> Maze(N, vector<vector<int>>(M, vector<int>(2)));
    for(int i = 0; i < N; ++i){
        for(int j = 0; j < M; ++j){
            cin >> Maze[i][j][0];
            Maze[i][j][1] = 0;  // node[i][j][k]: [i]: x coord, [j]: y coord, [k]: 0 not discovered, 1 discovered by s, 2 discovered by t
        }
    }
    
    find_path(S, T, Maze, N, M);


    return 0;
}
