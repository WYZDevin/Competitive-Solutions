#include <bits/stdc++.h>
#define MAXN 20020

using namespace std;

int N, k;
int bi[MAXN], ci[MAXN];
int dp[MAXN];
void solve(){
    for(int i = 0 ; i <= k ; i ++)dp[i] = 0x3f3f3f3f;
    dp[0] = 0;
    for(int i = 1 ; i <= N ; i ++){
        for(int j = 1 ; j <= ci[i] ; j ++){
            for(int l = k ; l >= bi[i] * j; l --){
                dp[l] = min(dp[l - j * bi[i]] + j, dp[l]);
            }
        }
    }
}
void print(){
    for(int i = 0 ; i <= k ; i ++)
            printf("%d ", dp[i] != 0x3f3f3f3f ? dp[i] : 0);
    cout << "\n";
    for(int i = 0 ; i <= k ; i ++)
        printf("%d ", i);

}
int main(){
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; i ++){
        scanf("%d ", &bi[i]);
    }
    for(int i = 1 ; i <= N ; i ++){
        scanf("%d ", &ci[i]);
    }
    scanf("%d", &k);
    solve();
    //print();
    cout << dp[k] << endl;
}
