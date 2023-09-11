#include <iostream>
int main()
{
    int  x=10;
    int  a[3] = { 20,30,40 };
    int  y = 50;
    printf("x = %d   y=%d\n", x, y);
    a[-1] = 60;
    //a[3] = 70;
    printf("%p %p %p",&x,a,&y);
    printf("x = %d   y=%d\n", x, y);
    *(&y-4)=20;
    printf("%d",x);
    return 0;
}