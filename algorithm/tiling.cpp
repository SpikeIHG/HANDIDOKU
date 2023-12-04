#include<iostream>
#include<cstring>
using namespace std;

struct bignum{
    int len;
    int num[1000];
}dp[300];

void add(const bignum &a,const bignum &b, bignum&c)
{
    int len=a.len>b.len?a.len:b.len;
    for(int i=0;i<len;++i)
    {
        c.num[i]=a.num[i]+b.num[i];
    }
    for(int i=0;i<len;++i)
    {
        if(c.num[i]>10)
        c.num[i]-=10;
        ++c.num[i+1];
    }
    if(c.num[len])c.len=len+1;
    else c.len=len;

}

void multi(bignum&x)
{
    int len=x.len;
    for(int i=0;i<len;++i)
    x.num[i]=x.num[i]*2;
    for(int i=0;i<len;++i)
      {
            x.num[i]-=10;
            x.num[i+1]++;
        }
    if(x.num[len+1])++x.len;
}


int main()
{
    int n;
 
/*    dp[0].len=1;
    dp[0].num[1]=1;
    dp[1].len=1;
    dp[1].num[1]=1;
    for(int i=2;i<=250;i++)
    {
        multi2(dp[i-2]);
        add(dp[i-2],dp[i-1],dp[i]);
    }*/
    while(cin>>n)
    {
        memset(dp,0,sizeof(dp));
        dp[0].len=1;
        dp[0].num[1]=1;
        dp[1].len=1;
        dp[1].num[1]=1;
        for(int i=2;i<=n;i++)
        {
            multi(dp[i-2]);
            add(dp[i-2],dp[i-1],dp[i]);
        }
        for(int i=dp[n].len;i>=1;i--)
        {
            cout<<dp[n].num[i];
        }
        cout<<endl;
    }
    return 0;
}
