#include <iostream>
#include<memory>
using namespace std;
class SET {
    int  maxsize;  // 集合中最多能存放的元素个数
    int  used;     // 当前实际存放的元素个数
    int* elem;     // 指向存放元数的空间
public:
    explicit SET(int num);  // 初始化集合能存放 num 个元素
    SET(const SET& s);  // 对象构造
    int insert(int v);  // 将 v 插入到集合中，成功 返回1，否则返回 0
                        // 集合中不能有相同元素，也不能在满员状态下再插入
    int remove(int v);  // 删除成功返回 1；否则返回 0
    int has(int v);     // 集合中存在v ，返回1，否则返回 0
    void displayInfo(); // 显示集合中的元素

    bool empty()const{return used==0;}  // 判断是不是空集

    int insertNoRestrict(int v);    // 无限制插入
    bool merge(const SET&);
    bool compare(const SET&)const;
    ~SET()=default;
};

SET::SET(int num):maxsize(num),used(0),elem(new int[num])
{
#ifdef DEBUG
cout<<"X(int)<<'\n";
#endif // DEBUG
}

/// @brief 深拷贝
/// @param rhs 
SET::SET(const SET&rhs):maxsize(rhs.maxsize),used(rhs.used)
{
    elem=new int [maxsize];
    for(int i=0;i<rhs.used;++i)
        elem[i]=rhs.elem[i];
}

int SET::insert(int v)
{
    int i{0};
    if(used==maxsize)
    return 0;

    for(i=0;i<used;++i)
        if(elem[i]==v)
            break;
    if(i==used)
    elem[used++]=v;
    else
    return 0;

    return 1;
}

int SET::remove(int v)
{
    if(!used)
    return 0;

    int i{0};
    for(i=0;i<used;++i)
    if(elem[i]==v)
    break;
    if(i==used)
    return 0;

    for(;i<used-1;++i)
    elem[i]=elem[i+1];
    --used;
    return 1;
}

int SET::has(int v)
{
    int i{0};
    for(i=0;i<used;++i)
    if(elem[i]==v)
        break;
    if(i==used)
    return 0;
    return 1;
}

void SET::displayInfo(void)
{
    for(int i=0;i<used;++i)
    cout<<elem[i]<<' ';
}

int SET::insertNoRestrict(int v)
{
    if(used<maxsize)
    return insert(v);
    else
    {
        maxsize+=5;
        elem=(int*)realloc(elem,maxsize);
        return insert(v);
    }
}

bool SET::merge(const SET&rhs)
{
    for(int i=0;i<rhs.used;++i)
    insertNoRestrict(rhs.elem[i]);
    return 1;
}

bool SET::compare(const SET&rhs)const
{
    if(rhs.used==used)
    {
        for(int i=0;i<rhs.used;++i){
            int flag{1};
            for(int j=0;j<used;++j)
                if(elem[j]==rhs.elem[i])
                    flag=0;
            if(flag)
            return 0;
        }
        return 1;
    }
    return 0;
}

int main()
{
  
   // 编写测例，要求创建一个能放 10个元素的集合  test
   // 向 test中依次插入 5,6,7,6,4
   // 从test 中删除 元素 5,8
   // 显示 test 中的元素信息
   // 用 test 构造另外一个 集合 aset;
   // 显示 aset 中元素的信息
   // 测试两个集合是否相同
   // 集合合并操作的测试
   SET myset(10);
   myset.insert(5);
   myset.insert(6);
   myset.insert(7);
   myset.insert(6);
   myset.insert(4);
   myset.remove(5);
   myset.remove(8);

   myset.displayInfo();
    cout<<'\n';
   SET urset(myset);
   urset.displayInfo();

    if(urset.compare(myset))
        cout<<"two sets is equivalent\n";
    else
        cout<<"Not equal\n";

    myset.merge(urset);
    myset.displayInfo();
    
    return 0;

}

