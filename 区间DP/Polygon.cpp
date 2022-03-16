#include <bits/stdc++.h>

using namespace std;
#define FOR(i, x, y) for (decay<decltype(y)>::type i = (x), _##i = (y); i <= _##i; ++i)
#define FORD(i, x, y) for (decay<decltype(x)>::type i = (x), _##i = (y); i >= _##i; --i)

// poj1179 多边形游戏,环形DP拆成2倍的链
int N;
const int MAXN = 50+10;
const int INF=0x3f3f3f3f;

int num[MAXN*2], op[MAXN*2];
int dpMAX[MAXN*2][MAXN*2];
int dpMIN[MAXN*2][MAXN*2];
inline int calc(int type,int a,int b){return type?a*b:a+b;}
int main(){
    freopen("in.txt", "r", stdin);
    freopen("out.txt","w", stdout);
    memset(dpMAX, 0xcf, sizeof(dpMAX));
    memset(dpMIN, 0x3f,sizeof(dpMIN));
    scanf("%d",&N);
     FOR(i,1,N){
        char o[2];
        scanf("%s", o);op[i]=op[N+i]=(o[0]=='x');
        scanf("%d",&num[i]); num[N+i]=num[i];
    }
    FOR(i,1,2*N)dpMAX[i][i]=dpMIN[i][i]=num[i];
   
    FOR(len,2,N){
        FOR(l,1,2*N-len+1){
            int r=len+l-1;
            for(int k=l;k<r;k++){
                int tmp1 = calc(op[k+1],dpMAX[l][k],dpMAX[k+1][r]);
                int tmp2 = calc(op[k+1],dpMIN[l][k],dpMIN[k+1][r]);
                dpMAX[l][r]=max(dpMAX[l][r],tmp1);
                dpMIN[l][r]=min(dpMIN[l][r],tmp1);
                dpMAX[l][r]=max(dpMAX[l][r],tmp2);
                dpMIN[l][r]=min(dpMIN[l][r],tmp2);
                int tmp3 = calc(op[k+1],dpMAX[l][k],dpMIN[k+1][r]);
                int tmp4 = calc(op[k+1],dpMIN[l][k],dpMAX[k+1][r]);
                dpMIN[l][r]=min(dpMIN[l][r],tmp3);
                dpMIN[l][r]=min(dpMIN[l][r],tmp4);
            }
        }
    }
    int ans=-INF;
    FOR(i,1,N){
        ans=max(dpMAX[i][i+N-1],ans);

    }
    
    printf("%d\n",ans);
    FOR(i,1,N){
        if(ans==dpMAX[i][i+N-1]){
            cout<<i<<" ";
        }
    }
    return 0;
}