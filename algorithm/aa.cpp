
// // #include <iostream>
// // using namespace std;
// // struct A { 
// //     A() { cout << 'A'; }
// // };
// // struct B {
// //     B() { cout << 'B'; }
// // };

// // struct C:A {
// //     C() { cout << 'C'; }
// // };
// // struct D:A,B {
// //     D() { cout << 'D'; }
// // };
// // struct E :A,B,virtual C{
// //     D  d;
// //     E() { cout << 'E'; }
// // };
// // struct F:A,virtual B,virtual C,D,E{
// //     C  c, d;
// //     E  e;
// //     F() { cout << 'F'; }
// // };

// // int main()
// // {
// //     A  a; cout << '\n';
// //     B  b; cout << '\n';
// //     C  c; cout << '\n';
// //     D  d; cout << '\n';
// //     E  e; cout << '\n';
// //     F  f; cout << '\n';
// //     return 0;
// // }


// #include<iostream>
// using namespace std;

// struct A{A(){cout<<'A';}};
// struct B{B(){cout<<'B';}};
// struct C:virtual A{B b;C(){cout<<'C';}};
// struct D:A,C,virtual B
// {
//     D(){cout<<'D';}
// };

// int main(void)
// {
//     D a;

//     return 0;
// }


#include <iostream>
using namespace std;
struct A { A( ) { cout << 'A'; } };
struct B { A a; B( ) { cout << 'B'; } };
struct C : virtual A { C( ) { cout << 'C'; } };
struct D : B, virtual C { D( ) { cout << 'D'; } };
struct E :  A, virtual D {
    D  d;
    E( )  { cout << 'E'; }
};
struct F : B, virtual C, virtual D, E{
    D d;  E e;
    F( ) { cout << 'F'; }
};

