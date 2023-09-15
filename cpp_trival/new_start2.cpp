/**
 * @file new_start2.cpp
 * @author spikeIHG (lanruo864@gmail.com)
 * @brief OOP 面向对象编程 开始了
 * @version 1.0
 * @date 2023-09-12
 * 
 * For Ms.Winter 
 * Le vent se lève, il faut tenter de vivre.
 */

//! OOP
// 1 纯虚函数 =0 不用定义  含有纯虚函数的类的抽象基类 作为一个抽象基类 无法定义这样的对象
// 2 重构 refactoring 常见的就是在继承体系中引入一个中间的抽象基类
// 3 继承的访问性质 由两个部分决定  一个是继承访问限定符 public private protected
//4 决定的是派生类对基类的成员使用  不对
// 5 分清楚一个概念就是 我们的用户 派生类的友元以及成员是一类 用户  同时直接使用派生类又是一类用户
// 6 因此 基类的访问限制符 控制的是拍摄了类型本身的访问限制 protect 就是派生类及其友元可以使用 而private 派生类也无法使用
// 7 public可以使用的 但是不能通过具体的成员访问 ！！！


#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Base{
private:
    double prize{0.0};
    string isbn;

public:
    Base()=default;
    virtual ~Base()=default;

};


class Deri:public Base{
private:
    string author;    

};

class Quote{
public: 
    Quote()=default;        // !定义一个默认的构造函数           no need to do the extra job
    Quote(const string&bookno,double sales_price):
                isbn_(bookno),price_(sales_price){}
    virtual ~Quote()=default;               //! 必要的
    virtual double net_price(size_t n ){return n*price_;}

protected:
    double price_{0};           // !attention the order of the variables declaration and the standard name principles 
private:
    string isbn_;
};


class Bulk_Quote final:public Quote {
public:
    Bulk_Quote()=default;
    Bulk_Quote(const )


private:

};





int main(void)
{



}