---
title: ST表
description: 需要预处理的数据结构
create: 2019.10.20
modified: 2019.10.20
tags: Data_structure
top: 0
location: .
index: true
template: template
---

[TOC]

## ST表

### Introduction

很好的用二进制来优化了$RMQ$中的操作

### Body

定义一个数组$f[i][j]$表示数列中$[i,2 ^ j - 1]$这一段区间的极值

可得 
$$f[i][j] = max(f[i][j-1],f[i+2^{j-1}][j-1])$$

先说一下这个的正确性,因为我们知道
$$f[i][j] = max\{f[i,i+2^j-1]\}$$

且
$$[i,i+2^j-1] = [i,i+2^{j-1}-1],[i+2^{j-1},i+2^j-1]$$
其实也就是从中间分开，分成两个相等的区间
那么`f[i][0]`又是什么呢？
它就是每个数组对应的值
因为
$$f[i][0] = max\{f[i,i+2^j-1]\}$$
$$2^0 = 1$$
所以
$$f[i][0] = max\{f[i,i]\}$$
所以这个时候所有的`f[i][0]`都是当前节点的值
所以也就比较好理解了
然后还有一个比较重要的问题: `循环边界`
首先我们知道$i+2^j-1 \leqslant n$
所以因为是先枚举j，再枚举的i，所以这个时候就可以作为i的边界

那么$j$的边界呢？
$$\because i+2^j-1\leqslant n$$

所以当$i$最小为$1$时 
$$2^j \leqslant n $$

也就是
$j\leqslant \log_2{n}$

好了，那么下面就是主程序

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define maxn 1000005
int f[maxn][21];
int ask(int l,int r)
{
    int k=log2(r-l+1); 
    return max(f[l][k],f[r-(1<<k)+1][k]);
}
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&f[i][0]);
    int Max_j = log2(n);
    for(int j=1;j<=Max_j;j++)
        for(int i=1;i+(1<<j)-1<=n;i++)
            f[i][j]=max(f[i][j-1],f[i+(1<<(j-1))][j-1]); 
    for(int i=1;i<=m;i++)
    {
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",ask(l,r));
    }
    return 0;
}
```
### Conclusion

`ST`表方便便捷，支持$O(1)$查询，比较适合在不变的序列上查找最值

## Update - 2018.9.15

比较重要的一点是循环的顺序，如果`i`和`j`的位置没有搞好的话那么将会出很大的锅

~~今天考试的时候才发现这里有循环顺序错误啥的~~
