// // #include<iostream>
// // #include<algorithm>
// // #define INF 0x3f3f3f3f
// // #define Cnt 100010
// // using namespace std;

// // int dx[]={1,0,-1,0};
// // int dy[]={0,1,0,-1};

// // int x[Cnt],y[Cnt];
// // struct node{
// //     int x,y;
// // }a[Cnt];

// // int main(void)
// // {
// //     cin.tie(0);cout.tie(0);
// //     std::ios::sync_with_stdio(0);

// //     int N;
// //     cin>>N;
// //     for(int i=1;i!=N+1;++i){
// //     cin>>x[i]>>y[i];
// //     a[i].x=x[i];
// //     a[i].y=y[i];
// //     }
// //     sort(x+1,x+N+1);
// //     sort(y+1,y+N+1);
// //     if(N%2)
// //     {
// //         int temp=(N/2)+1;
// //         for(int i=1;i!=N+1;++i)
// //         {
// //             int min=INF;
// //             if(a[i].x==x[temp]&&a[i].y==y[temp])
// //             {
// //                 for(int i=0;i!=4;++i)
// //                 {
// //                     int xx=a[i].x+dx[i];
// //                     int yy=a[i].y+dy[i];
// //                     for(int k=1;k!=N+1;++k)

// //                 }
// //             }
// //         }
// //     }
// //     else
// //     {

// //     }
    
// // }


// #include<iostream>
// #include<cstdio>
// #include<cstring>
// #include<cmath>
// #include<algorithm>
// #include<string>
// #include<cstdlib>
// #include<queue>
// #include<set>
// #include<vector>
// #define INF 0x3f3f3f3f
// #define PI acos(-1.0)
// #define N 10001
// #define MOD 123
// #define E 1e-6
// using namespace std;
// int dx[4]={0,1,0,-1};
// int dy[4]={1,0,-1,0};
// struct Node{
// 	int x;
//     int y;
// }a[N];
// int x[N],y[N];
// int minn,plan;
// int main()
// {
 
//     int n;
//     scanf("%d",&n);
// 	for(int i=1;i<=n;i++)
// 	{
// 		scanf("%d%d",&a[i].x,&a[i].y);
// 		x[i]=a[i].x;
// 		y[i]=a[i].y;
// 	}
 
// 	sort(x+1,x+n+1);//对x排序
// 	sort(y+1,y+n+1);//对y排序
 
// 	if(n%2)//n为奇数时
// 	{
// 		int temp=(n/2)+1;
// 		for(int i=1;i<=n;i++)
// 		{
// 			if(a[i].x==x[temp]&&a[i].y==y[temp])//若点为给出点
// 			{
// 				int Min=INF;
// 				for(int l=0;l<4;l++)//枚举四个方向
// 				{
// 					int xx=x[temp]+dx[l];
// 					int yy=y[temp]+dy[l];
// 					int sum=0;
// 					for(i=1;i<=n;i++)//求最小的距离
// 					  sum+=abs(a[i].x-xx)+abs(a[i].y-yy);
// 					if(sum<Min)
//                     {
//                         Min=sum;
//                         plan=1;
//                     }
// 					else if (sum==Min)
//                         plan++;
// 				}
// 				printf("%d %d\n",Min,plan);
// 				return 0;
// 			}
// 			else//若点不为给出点
//             {
//                 minn+=abs(a[i].x-x[temp])+abs(a[i].y-y[temp]);//记录最小距离
//                 plan=1;//方案数为1
//             }
// 		}
// 		printf("%d %d\n",minn,plan);
// 	}
// 	else//n为偶数时
// 	{
// 		int temp1=n/2,temp2=n/2+1;
// 		plan=(x[temp2]-x[temp1]+1)*(y[temp2]-y[temp1]+1);//令方案数等于点的个数
// 		for(int i=1;i<=n;i++)
// 		{
// 			minn+=abs(a[i].x-x[temp1])+abs(a[i].y-y[temp1]);//记录最小距离
// 			int x0=a[i].x,y0=a[i].y;
// 			if (x[temp1]<=x0&&x0<=x[temp2]&&y[temp1]<=y0&&y0<=y[temp2])//更新方案数
//                 plan--;
// 		}
// 		printf("%d %d\n",minn,plan);
// 	}
// 	return 0;
// }

