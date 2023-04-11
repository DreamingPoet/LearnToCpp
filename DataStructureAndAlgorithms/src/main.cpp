// 数据结构 = 个体的存储 + 个体与个体的关系存储

// 数据结构强调数据之间的关系，属于底层细节。
// 数据类型强调对数据的合法操作，也包括对数据结构的描述。

// 简单数据结构：整数的结构，字符的结构，数组的结构。
// 复杂数据结构：线性表，栈和队列，树，图
// 简单数据类型：整型，字符型，数组
// 复杂数据类型（抽象数据类型）：结构体，类

// 一、数据结构
// 1. 线性 - 线性表
// 线性表的顺序存储结构，其实就是用数组进行实现的
// 顺序存储结构下的常用操作：创建，查找，插入，删除等操作

// 线性表的链式存储结构（单向链表），单向链表下的常用操作，创建，查找，插入，删除等操作
// 存储下一个数据元素的地址（包含 数据域 和 指针域）
// 查找单链表中间结点，当用慢指针 slow 遍历列表时，让另一个指针 fast 的速度是它的两倍。当 fast 到达列表的末尾时，slow 必然位于中间。
// 可以有头结点，为了处理方便而设立，数据域无意义或者链表长度
// 顺序线性表优势在于查找方面；单链表的优势在于插入和删除。

// 双向链表的存在意义：可以反向遍历查找
// 双向链表的定义：每个结点有两个指针域，一个指向直接前驱，一个指向直接后继。

// 2. 线性 - 栈和队列（push， pop）
// 栈和队列都属于线性表的一种，只是限制了插入和删除的位置。
// 栈是一种先进后出（后进先出）的线性表。
// 顺序栈使用数组进行实现，数组头为栈底，数组尾为栈顶
// 链栈使用链表实现

// 队列是一种先进先出的线性表,队尾插入，队头删除
// 链队列使用链表实现

// 3. 线性 - 串（string）
// 串的顺序存储结构，使用一组地址连续的存储单元
// 串的链式存储

// 4. 线性 - 数组和广义表
// 5. 非线性 - 树
// 树
// 二叉树 - 所有节点最多只有左右两个子节点
// 完全二叉树 - 如果一个节点只有一个子节点，那么一定是左节点
// 满二叉树 - 所有节点都有左右两个子节点

// 链式存储 二叉链表

// 6. 非线性 - 图

// 算法 = 对存储数据的操作
// 算法的时间复杂度：
// n是问题输入规模，f(n)是对应的算法基本操作数量，记作O(f(n))。
// 一、算法
// 1. 查找
// 2. 排序

// 斐波那契函数
/**
 * param n 第n项
 * return 第n项的值
 */

#include <iostream>

template <class T>
int get_arr_length(T &array)
{
    return (sizeof(array) / sizeof(array[0]));
}

int Fbi(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return Fbi(n - 1) + Fbi(n - 2);
}

void PrintFbi()
{
    for (int i = 0; i < 40; i++)
    {
        std::cout << Fbi(i) << std::endl;
    }
}

int divide_search(int arr[], size_t arr_len, int target)
{
    // 左边界
    int l = 0;
    // 右边界
    int r = arr_len - 1;
    int mid = 0;
    while (l < r-1)
    {
        // 取中间值
        mid = (l + r) / 2;
        if (target < arr[mid])
        {
            // 右边界收缩
            r = mid;
        }
        else if (target > arr[mid])
        {
            // 左边界收缩
            l = mid;
        }
        else if (target = arr[mid])
        {
            return mid;
        }
    }
    return -1;
}

void test_divide_search()
{
    int arr[] = {1, 2, 4, 7, 8, 10, 14};
    int target = 14;
    int index = divide_search(arr, get_arr_length(arr), target);
    std::cout << index << std::endl;
}

int main()
{
    //   PrintFbi();
    test_divide_search();
}