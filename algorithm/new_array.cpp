#include <cstdio>
#include <algorithm>
using namespace std;
 
const int maxn = 1111111;
 
int n;
int x[maxn];
long long m;
 
bool C(int mid) {
    long long cnt = 0;
    for(int i = 0; i < n; i++)
        cnt += x+n-lower_bound(x+i+1, x+n, x[i]+mid);
    //lower_bound返回第一个大于等于xi+mid值的下标，原数列在其后面的都比xi+mid大
    //cnt计算所有差值比mid大的原数列组合个数
    return cnt <= m/2;      //等于号是因为，cnt计算的是比mid大的个数
}
 
int main() {
    while(~scanf("%d", &n)) {
        for(int i = 0; i < n; i++)
            scanf("%d", &x[i]);
        sort(x, x+n);
        m = n*(n-1)/2;      //新数列的个数就是C_N_2（组合数），N是原数列的个数
        int L = 0, R = *max_element(x, x+n); //r为最大元素
        while(R-L > 1) {
            int mid = (L+R)/2;
            if(C(mid)) R = mid;
            else L = mid;
        }
        printf("%d\n", L);
 
    }
    return 0;
}