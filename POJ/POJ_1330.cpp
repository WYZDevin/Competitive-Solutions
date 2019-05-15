#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int LOGMAX = 15;
const int MAX = 10010;
int tree[MAX], dp[MAX][LOGMAX], dep[MAX], in[MAX], N;
vector<int> adj[MAX];

void init(){
    for(int i = 0 ; i < MAX ; i ++){
        tree[i] = -1;
        dep[i] = 0;
        in[i] = 0;
        adj[i].clear();
    }
    for(int i = 0 ; i < MAX ; i ++){
        for(int j = 0 ; j < LOGMAX ; j ++){
            dp[i][j] = -1;
        }
    }
}
void set_dep(int cur){
    int size = adj[cur].size();
    for(int i = 0 ; i < size ; i ++){
        dep[adj[cur][i]] = dep[cur] + 1;
        set_dep(adj[cur][i]);
    }
}
void build_tree(){
    for(int i = 1 ; i < LOGMAX ; i ++){
        for(int j = 1 ; j <= N ; j ++){
            if(dp[j][i - 1] != -1){
                dp[j][i] = dp[dp[j][i - 1]][i - 1];
            }
        }
    }
}
int lca(int a, int b){
    if(dep[a] > dep[b])
        swap(a, b);
    while(dp[b][0] != -1 && dep[b] > dep[a]){
        b = dp[b][0];
        //System.out.println(na + " " + nb + "lca");
    }
    if(a == b) return a;
    while(a != b && dep[b] > 0 && dep[a] > 0){
        b = dp[b][0];
        a = dp[a][0];
    }
    return a;
}
void solve(){
    int a, b;
    scanf("%d", &N);

    for(int i = 0 ; i < N - 1 ; i ++){
        scanf("%d %d", &a, &b);
        tree[b] = a;
        adj[a].push_back(b);
        in[b] = 1;
    }
    scanf("%d %d", &a, &b);
    int root = -1;
    for(int i = 0 ; i <= N ; i ++){
        dp[i][0] = tree[i];
        if(!in[i]){
            root = i;
        }
    }
    set_dep(root);
    build_tree();
    printf("%d\n", lca(a, b));


}
int main() {
    int n;
    cin >> n;
    while(n--){
        init();
        solve();
    }
}