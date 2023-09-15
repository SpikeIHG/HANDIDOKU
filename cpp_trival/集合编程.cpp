#include <iostream>
using namespace std;
class SET {
    int  maxsize;  // 集合中最多能存放的元素个数
    int  used;     // 当前实际存放的元素个数
    int* elem;     // 指向存放元数的空间
public:
    SET(int num);  // 初始化集合能存放 num 个元素
    SET(const SET& s);  // 对象构造
    int insert(int v);  // 将 v 插入到集合中，成功 返回1，否则返回 0
                        // 集合中不能有相同元素，也不能在满员状态下再插入
    int remove(int v);  // 删除成功返回 1；否则返回 0
    int has(int v);     // 集合中存在v ，返回1，否则返回 0
    void displayInfo(); // 显示集合中的元素
    ~SET();
};

// 在 SET类中，增加成员一些成员函数
// (1) 判断与另外一个集合比较是否相同，返回bool 0或1
//     相同：集合中的元素全部一样，与元素排列顺序无关
// (2) 将指定的集合合并到当前集合中，集合中不能有相同元素
// (3) 判断一个集合是否为 空集，返回bool 0或1
// 选做题：集合大小能扩增，即取消 集合中最多能存放的元素个数的限制。
//         不要修改已定义的数据成员和函数成员，只是加一个 insertNoRestrict函数

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
}

