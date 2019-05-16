#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 300000
#define LOGMAX 19
int tree [MAX], step[MAX], dep[MAX], n, dp[MAX][LOGMAX];
char op;
vector<int> adj[MAX];
vector<pair<int, int>> q;
void init(){
    for(int i = 0 ; i < MAX ; i ++){
        for(int j = 1 ; j < LOGMAX ; j ++){
            dp[i][j] = -1;
        }
        dp[i][0] = tree[i];
    }
}
void set_dep(int cur){
    int size = adj[cur].size();
    for(int i = 0 ; i < size ; i ++){
        int num = adj[cur][i];
        dep[num] = dep[cur] + 1;
        set_dep(num);
    }
}
void build_tree(){
    for(int i = 1 ; i < LOGMAX ; i ++){
        for(int j = 1 ; j < MAX ; j ++){
            if(dp[j][i - 1] != -1){
                dp[j][i] = dp[dp[j][i - 1]][i - 1];
            }
        }
    }
}
int lca(int i, int j){
    if(dep[i] < dep[j])
        swap(i, j);

    for(int k = LOGMAX-1; k >= 0; k--){
        if(dp[i][k] != -1 && dep[dp[i][k]] >= dep[j])
            i = dp[i][k];
    }

    if(i == j)
        return i;

    for(int k = LOGMAX-1; k >= 0; k--){
        if(dp[i][k] != -1 && dp[j][k] != -1 && dp[i][k] != dp[j][k]){
            i = dp[i][k];
            j = dp[j][k];
        }
    }

    return dp[i][0];
}
void solve(){
    init();
    set_dep(0);
    build_tree();
    for(auto p: q){
        if(p.first == -1){
            printf("%d\n", p.second);
        }else{
            int na = step[p.first];
            int nb = step[p.second];
            int head = lca(na, nb);
            printf("%d\n", dep[head]);
        }
    }

}

void read(){
    scanf("%d", &n);
    for(int i = 0 ; i < MAX ; i ++)
        tree[i] = i;
    for(int i = 1, a, b; i <= n ; i ++){
        scanf(" %c ", &op);
        if(op == 'a'){
            scanf("%d", &a);
            tree[i] = step[a];
            adj[step[a]].push_back(i);
            step[i] = i;
        }else if (op == 'b'){
            scanf("%d", &a);
            int node = step[a];
            step[i] = tree[node];
            q.push_back(make_pair(-1, node));
        }else{
            scanf("%d %d", &a, &b);
            step[i] = step[a];
            q.push_back(make_pair(i, b));
        }
    }

}

int main() {
    read();
    solve();
    return 0;
}