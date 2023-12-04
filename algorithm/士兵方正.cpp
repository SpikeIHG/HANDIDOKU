#include<iostream>
#include<algorithm>
using namespace std;

typedef struct pos{
    int x,y;
}POS;

POS matrices[10010];

bool cmpx(POS a,POS b)
{
    return a.x<b.x;
}

bool cmpy(POS a,POS b)
{
    return a.y<b.y;
}

int main(void)
{
    cin.tie(0);
    std::ios::sync_with_stdio(0);
    int n;
    int ans=0;
    int mid_v;
    cin>>n;
    for(int i=0;i<n;++i)
    cin>>matrices[i].x>>matrices[i].y;
    sort(matrices,matrices+n-1,cmpx);
    if(n%2)
    mid_v=matrices[n/2].x;
    else
    mid_v=(matrices[n/2].x+matrices[n/2-1].x)/2;
    for(int i=0;i<n;++i)
    ans+=abs(mid_v-matrices[i].x);
    sort(matrices,matrices+n-1,cmpy);
    if(n%2)
    mid_v=matrices[n/2].y;
    else
    mid_v=(matrices[n/2].y+matrices[n/2-1].y)/2;
    for(int i=0;i<n;++i)
    ans+=abs(mid_v-matrices[i].y);


    cout<<ans;

    return 0;

}

// 原理就是将每个士兵在x 轴移动的距离进行中位数寻找最小值