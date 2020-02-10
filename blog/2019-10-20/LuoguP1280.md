---
title: [题解]LuoguP1280尼克的任务
description: 一道比较好的dp题
create: 2019.10.20
modified: 2019.10.20
tags:   solution 
        dp
top: 0
location: .
index: true
template: template
---

[TOC]

# LuoguP1280尼克的任务

## 状态转移方程

易发现当$f[i]$所代表的是$i ~ n$的最大空余时间时，可以倒着转移状态

即有

无任务时 
$$f[i] = f[i + 1] + 1;$$

有任务时
$$f[i] = max{f[i],f[i + a[num].len]}$$

## code

```cpp
/*
f[i] => 从 i 到 n 时刻的最大空余时间
易推得:
f[i] = f[i + 1] + 1; //无任务时
f[i] = max{f[i],f[i + a[num].len]} // 有任务时分别枚举取最大值
*/

#include<cstdio>  
#include<algorithm>  
using namespace std;
#define maxn 10005
int n,k,cnt[maxn],num = 1,f[maxn];// 从第一个任务开始枚举，所以num = 1;
struct work
{
    int start,len;// 开始时间和延续时长
}a[maxn];
inline bool cmp(work a,work b){return a.start > b.start;} // 自定义cmp,根据开始时间排序
int main()
{
    scanf("%d %d",&n,&k);
    for(int i = 1;i <= k;i ++)  
    {  
        scanf("%d %d",&a[i].start,&a[i].len);
        cnt[a[i].start] ++; // 在该时间开始的任务数量 + 1
    }
    sort(a + 1,a + k + 1,cmp); // 根据开始的时间排序
    for(int i = n;i >= 1;i --) // 倒序搜索
    {
        if(!cnt[i]) f[i] = f[i + 1] + 1; //无任务时
        else // 有任务时
        {
            for(int j = 1;j <= cnt[i];j++)  // 枚举任务数量
            {
                if(f[i + a[num].len] > f[i]) f[i] = f[i + a[num].len];
                num ++; // 枚举下一个任务
            }
        }
    }
    printf("%d",f[1]);// 输出1 - n的最大空闲时间
    return 0;
}
```
