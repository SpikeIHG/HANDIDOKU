/**
 * @file new_start.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-09-08
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 * 
 */
//! 类 一  
// 1. 设计类 花时间确定类的成员以及基本的接口 即成员函数
//2 this 顶层指针 隐藏参数 默认使用的 const 内外的定义都要记得加 可以重载
// 3 inline与定义的位置
// 4 友元声明 前向声明 注意友元不是函数声明 
// 5 构造函数就是初始化控制函数 无return 默认初始化控制 直接初始化
//6 发生的情形 默认初始化情形 没有指定值的显示初始化非static块作用域  值初始化 T() 局部静态static无初始值 默认与值初始胡都是默认构造
// 7 多次重复 或者 不断更新调bug的代码写成 小函数 多写小函数 并考虑inline
// 8 使用值初始化列表 并且最好记得提供类内初始值 只能 用 {} = 不能（）
// 9 默认构造函数 是无形参的构造函数 可以有默认形参 
// 10 委托构造 写一个多形参的 去 定义其他
// 11 隐式类型转换 explicit 关键词 转换机制 只能一步 用于辅助拷贝初始化或者是赋值 函数调用 通常是很重要的类型
// 12 explicit抑制  就只能明确()调用 vector(10)； 认可用于显示 类类型转化 只用一个形参的 构造函数
// 13 mutable static 类外定义



//! 类 二
//1 拷贝控制成员 析构函数 
// 2 三五原则 对称之美 先看是否需要析构函数 了解虚构函数函数体是单独作用的 其余都是隐式析构 有析构基本就需要定义拷贝//
// 3 定义了拷贝初始 就要定义拷贝赋值
//4 = default =delete 阻止 防止默认生成 =defau't只能用于几个控制成员 =delete可以用于所有函数
// 5 类成员中 的 const 与 引用成员 必须要自己指定 默认合成会删除
// 6 析构函数 不能是 删除的
// 7 浅拷贝 即是行为像指针的类 深拷贝 即 是行为像值的类
// 8 编写拷贝构造函数 析构函数 先 赋值 综合了析构与拷贝初始化 先析构然后初始化且要保证自赋值正确
//9 解决方案 就是先将左侧保存下来 或是先进行自己的检查 是否是自付值
// 10 swap函数 当需要参与sort的类时 可以借助标准的库swap函数 编程风格 重要的优化手段
// c++11 标准 移动 右值引用 绑定到右值中 右值短暂 左值持久 &&  注意 任何变量都是 左值
// 12 std::move 得到右值引用
// 13 编写移动构造函数 noexcpet && 形参 保证移动后的源可析构 
// 14 默认只在没有任何的拷贝构造成员 且能移动时 生成 有 拷贝就不会合成移动 同样有移动就不会自动合成拷贝
// 15 移动迭代器 make_move_iterator(iter)返回一个右值引用 改变该引用的行为
// 16 对成员函数进行移动重载 void mF(const X&); void mF(X&&);
// 17 引用限定符 必须同时出现在定义与声明处 在const后面 && & 指定this限定this的性质 同时重载时const与引用限定符同时出现时
// 则要么所有重载都有 & 要么都没有


//! 类三 重载运算符
//1 应该尽量把自定义运算符与内置类型靠近
//2 应该 定义对应的一系列运算符
//3 注意返回值 引用还是值 bool
//4 要求 作为非成员函数时 必须有一个类类型的形参
// 5 

#include<iostream>
using namespace std;

ostream&operator<<(ostream&,const Widget&);
istream&operator>>(istream&is,Widget &item);
Widget operator+(const Widget&lhs,const Widget&rhs);
bool operator==(const Widget&lhs,Widget&rhs);
bool operator!=(const Widget&lhs,const Widget&rhs);

class Widget{
    friend ostream&operator<<(ostream&,const Widget&);
    friend istream&operator>>(istream&is,Widget &item);
    friend Widget operator+(const Widget&lhs,const Widget&rhs);
    friend bool operator==(const Widget&lhs,Widget&rhs);
    friend bool operator!=(const Widget&lhs,const Widget&rhs);

private:
    string name_;
    string hometown_;
    double age_{18};
    double property{0};
public:
    string tell_home(void)const{return hometown_;}
    string tell_name(void)const{return name_;}
    inline Widget&operator+=(const Widget&rhs);
};

// 第一个<< 减少改变打印格式 一定为非成员函数
ostream&operator<<(ostream&os,const Widget&item)
{
    os<<item.tell_name()<<" is come from "<<item.tell_home();
    return os;
}
//? 输入操作时尽量能够使 错误发生时进行恢复 可以结合 流控制信息
istream&operator>>(istream&is,Widget &item)
{
    string name,home;
    cout<<"enter the name and home first!\n";
    is>>name>>home;
    if(is)
        {
            item.name_=name;
            item.hometown_=home;
        }
    else
    item=Widget();
    return is;
}

inline Widget&Widget::operator+=(const Widget&rhs)
{
    property+=rhs.property;
    return *this;
}


// ! 算术重载 使用符合运算符来定义
Widget operator+(const Widget&lhs,const Widget&rhs)
{
    Widget sum=lhs;
    sum+=rhs;
    return sum;
}

// == ！= 配套的 然后满足传递性 并且语义充分
bool operator==(const Widget&lhs,const Widget&rhs)
{
    return lhs.tell_home()==rhs.tell_home() &&
            lhs.tell_name()==rhs.tell_name();
}

bool operator!=(const Widget&lhs,const Widget&rhs)
{
    return !(lhs==rhs);
}

int main(void)
{


    return 0;
}

