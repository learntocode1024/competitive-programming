#include <cstdio>
#include <cstring>
#define max(a,b) ((a)>(b)?(a):(b))

typedef long long ll;
const int maxn=500000+10,inf=1000000*2;
int n,a[maxn];

struct Node{
    ll x,y;
    bool operator<(const Node &a)const{
        if(x!=a.x)return x<a.x;
        else return y>a.y;
    }
    bool operator>(const Node &a)const{
        return a<*this;
    }
    Node operator+(const Node &a)const{
        return (Node){x+a.x,y+a.y};
    }
}f[maxn],g[maxn];

int check(int mid){
    f[1]=(Node){a[1]+mid,1};
    g[1]=max(g[0],f[1]);
    for(int i=2;i<=n;++i){
        f[i]=g[i-2]+(Node){a[i]+mid,1};
        g[i]=max(g[i-1],f[i]);
    }
    // printf("%d %d\n",mid,g[n].y);
    return g[n].y;
}

int main(){
    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    int m;ll ans=0;scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",a+i);
    for(int l=-inf,r=0,mid;l<=r;){
        mid=(l+r)/2;
        if(check(mid)<=m){ans=g[n].x-(ll)m*mid;l=mid+1;}
        else r=mid-1;
    }
    printf("%lld\n",ans);
    // check(0);
// for(int i=1;i<=n;++i)
// 	printf("%lld %lld\n",f[i].x,f[i].y);
    return 0;
}