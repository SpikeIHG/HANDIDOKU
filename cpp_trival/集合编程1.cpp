#include<stdio.h>

int main(void)
{
    int dividor_sum[1000]={0};
    int sum=0;
    for(int n=1;n<=1000;++n)
    {
        int i=0;
        for(int d=1;d<n;++d)
            if(n%d==0)
                dividor_sum[i++]=d;

        for(int i=0;i<1000;++i)
            sum+=dividor_sum[i];

        if(sum==n)
        printf("%d\n",n);
         for(int i=0;i<1000;++i)
         dividor_sum[i]=0;
        sum=0;
    }
    printf("\n");
    return 0;
}