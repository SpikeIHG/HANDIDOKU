#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

const int N=2e5+5;
const int INF=1e10;

inline int read()
{
    int f=1,x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>'0'&&ch<'9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

struct dot{
    int x,y,type;
    bool operator <(const dot a)const{return x<a.x;}
}points[N],temp[N];
// 定义了重载运算符后 我们可以直接使用sort 了 然后在每一次递归时对y排序
double dist(const dot&a,const dot&b)
{
    if(a.type==b.type)
    return INF;
    double dx=a.x-b.x;
    double dy=a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}

double dfs(int l,int r)
{
    if(l>=r)return INF;     // 递归边界
    int mid=(l+r)>>1;
    double mid_x=points[mid].x; // 因为会改变所以先存下来
    double res=min(dfs(l,mid),dfs(mid+1,r));
    // 归并排序的合并
    {
        int k=0;
        int i=l,j=mid+1;
        while(i<=mid&&j<=r)
        {
            if(points[i].y<points[j].y)temp[k++]=points[i++];
            else temp[k++]=points[j++];
        }
        while(i<=mid)temp[k++]=points[i++];
        while(j<=r)temp[k++]=points[j++];
        for(int i=0,j=l;i<k;++i,++j)points[j]=temp[i];
    }
    int k=0;
    for(int i=l;i<=r;i++){
        if(points[i].x>=mid_x-res&&points[i].x<=mid_x+res)temp[k++]=points[i];
    }

    for(int i=0;i<k;++i)
        for(int j=i-1;j>=0&&temp[i].y-temp[i].y<res;j--)
            res=min(res,dist(temp[i],temp[j]));
    return res;
}
int T;
int n;

int main(void)
{
    T=read();
    while(T--)
    {
        n=read();
        for(int i=0;i<n;++i){
            points[i].x=read();points[i].y=read();
            points[i].type=0;
        }
        for(int i=n;i<n*2;++i){
            points[i].x=read();points[i].y=read();
            points[i].type=1;
        }
        sort(points,points+2*n);
        printf("%.3f",dfs(0,2*n-1));
    }

    return 0;


}