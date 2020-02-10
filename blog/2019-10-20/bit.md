---
title: 位运算初探
description: 一些位运算可以很妙妙的用
create: 2019.10.20
modified: 2019.10.20
tags:   二进制
top: 0
location: .
index: true
template: template
---

[TOC]

# 位运算初探

有关位运算的相关操作

## 交换两个变量的值

```cpp
a ^= b;
b ^= a;
a ^= b;
```

就是无第三方变量且不使用指针的情况下交换两个变量的值

~~但是没什么必要吧~~

## 二进制相关

确定一个数字的二进制的第一个$1$在什么位置

```cpp
#define lowbit(x) ((x) & (-x))
```
```
Input: x = 32
Output: 32

Input: x = 31
Output: 1
```
计算一个数字的二进制中有多少个$1$

```cpp
int x,cnt  = 0;
while(x)
{
    cnt ++;
    x -= lowbit(x);
}
```

取二进制的最后一位
```cpp
int last = x & 1;
```

可以用来判断奇偶性

## 真题:

[CF上的一道Div2的C题](http://codeforces.com/problemset/problem/1186/C)

~~此题被OFN和YYZ一眼秒~~

考虑两个$01$串的不同位置的个数是奇数还是偶数

其实只要算出两个串中$1$的个数就好了，我们令两个$01$串分别是$A$串和$B$串，$1$的个数分别是$lena$和$lenb$，令两个串中都是$1$的位置个数有$cnt$个，最后不同的位置个数有$ans$个，则有$ans = lena + lenb - cnt * 2$;稍稍对其进行一个奇偶性的分析，我们可以讨论得到

$lena$为奇数，$lenb$为奇数时，因为$lena + lenb$一定是偶数，又因为$cnt * 2$是偶数，所以$ans$一定会是偶数

$lena$为奇数，$lenb$为偶数时，因为$lena + lenb$一定是奇数，又因为$cnt * 2$是偶数，所以$ans$一定会是奇数

$lena$为偶数，$lenb$为奇数时，因为$lena + lenb$一定是奇数，又因为$cnt * 2$是偶数，所以$ans$一定会是奇数

$lena$为偶数，$lenb$为偶数时，因为$lena + lenb$一定时偶数，又因为$cnt * 2$是偶数，所以$ans$一定会是偶数

然后我们考虑异或这个操作，使得最后方便操作，其实我们可以直接用最后一位来算，然后与$B$串进行异或

最后我们在做的时后可以用一个前缀和使复杂度在$O(n)$

~~不知道为什么这题有FFT的标签~~
