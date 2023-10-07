#include<iostream>
using namespace std;

int main(void)
{
    const int c_val=1000;
    int* p_val=(int*)&c_val;
    *p_val=10990;

// 确实可以使用 修改 const 

}