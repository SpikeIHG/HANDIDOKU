#include<stdio.h>
int flags[100000];
int a;
int main(void)
{
    int m;
    int n;
    int flag=0;
    scanf("%d",&m);
    for(int i=0;i<m;++i)
    {
        scanf("%d",&a);
    flags[40000+a]=1;
    }
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        scanf("%d",&a);
    if(flags[50000-a])
    {flag=1;
    break;
    }
    }
    if(flag)
    printf("YES");
    else
    printf("NO");


    return 0;



}

