#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;


// 核心思想就是构造一个分块矩阵 根据递推式求解 实际
// 操作就是求解一个2*n 方阵的连续乘法



int main(void)
{
    cin.tie(0);
    cout.tie(0);
    std::ios::sync_with_stdio(0);




}

#include <iostream>
#include <cstring>
#include <cstdio>
#define ll long long

using namespace std;

struct DT{
	ll n, m;
	ll aed[70][70];
}A, B, Bc;
ll n, Mod, k;

DT operator * (DT a, DT b){
	DT c;
	memset (c.aed, 0, sizeof (c.aed));
	c.n = a.n, c.m = b.m;
	for (int k = 1; k <= a.m; k++)
		for (int i = 1; i <= c.n; i++)
			for (int j = 1; j <= c.m; j++)
				c.aed[i][j] = (c.aed[i][j] + a.aed[i][k] * b.aed[k][j] % Mod) % Mod;
	return c;
}

void power (ll x){
	if (x == 1)
	{
		B = Bc;
		return;
	}
	power (x / 2);
	B = B * B;
	if (x % 2)
		B = B * Bc;
}

int main(){
	scanf ("%lld%lld%lld", &n, &k, &Mod);
	A.n = A.m = Bc.m = Bc.n = n * 2;
	//A = A 和 J1；J2 = Bc和B
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			scanf ("%lld", &A.aed[i][j]);
			Bc.aed[i][j] = A.aed[i][j];//J2的左上角是A数组
		}
	for (int i = 1; i <= n; i++)
		Bc.aed[i][i + n] = Bc.aed[i + n][i + n] = 1;//J2的右上角和右下角是单位矩阵
	power (k);
	A = A * B;
	for (int i = 1; i <= n; i++)
	{
		for (int j = n + 1; j <= n * 2; j++)
			printf ("%lld ", A.aed[i][j]);
		printf ("\n");
	}
}
