---
title: [题解]LuoguP1006传纸条
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

# [题解]LuoguP1006传纸条

本题题面见 [LuoguP1006](https://www.luogu.org/problemnew/show/P1006)

其实可以将纸条的两次传递看作是一次传递两张纸条，且路径不能相交

## 找规律

![](https://s2.ax1x.com/2019/06/26/ZZHidK.png)

对比上图我们不难发现:

当第一张纸条与第二张纸条传递了同样多的次数时在同一条直线上(本就应该如此)，但是可以推论出此条直线的斜率是1

因为每次移动只能让纸条的横坐标或者是纵坐标增加一个单位，而不管怎么移，两种选择都会在一条斜率为1的直线上，如下图所示

![](https://s2.ax1x.com/2019/06/26/ZZHcl9.png)

同时，因为每次移动是在一条直线上向下推进，所以只有可能是相同步数后两张纸条在同一斜率为1的直线上

## 建立状态转移方程

用$f(i,j,k)$表示这一步的横纵坐标之和为$i$(步数)，第一张纸条纵坐标为$j$，第二张纸条纵坐标为$k$(因为路径不重合，所以$j \ne k$，不妨令$j < k$) 

则有每个状态可以从以下4种情况转移而来：

1. 第一张纸条从上面转移过来，第二张纸条从上面转移过来

$$f(i,j,k)=max(f(i,j,k),f(i-1,j-1,k-1)+a[j][i-j]+a[k][i-k])$$

1. 第一张纸条从上面转移过来，第二张纸条从左边转移过来

$$f(i,j,k)=max(f(i,j,k),f(i-1,j-1,k)+a[j][i-j]+a[k][i-k])$$

3. 第一张纸条从左边转移过来，第二张纸条从上面转移过来

$$f(i,j,k)=max(f(i,j,k),f(i-1,j,k-1)+a[j][i-j]+a[k][i-k])$$

4. 第一张纸条从左边转移过来，第二张纸条从左边转移过来

$$f(i,j,k)=max(f(i,j,k),f(i-1,j,k)+a[j][i-j]+a[k][i-k])$$

不难看出里面都将$f(i,j,k)$与转移之前的作了比较，而且都有$a[j][i-j]$与$a[k][i-k]$

同时注意状态转移方程的条件:

没有越界，而且纸条没有重合,由于一开始数组中都是0，不进行越界判断也无妨，但是纸条重合的判断必须有，即只有$k - 1 > j$时才能从第3种情况转移过来

## 一点小优化

注意到四种状态转移都有$f(i - 1)$这一维，所以可以搞一个滚动数组减小空间复杂度,需要注意的就是由于状态都是由更小的$j$或$k$转移而来，$j$和$k$都需要倒序枚举，防止状态在转移之前被修改。

## 代码构造

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 205
int n,m,f[maxn][maxn],a[maxn][maxn];
inline int min(int a,int b){return a < b ? a : b;}
int main()
{
    #ifndef ONLINE_JUDGE
        freopen("main.in","r",stdin);
        freopen("main.out","w",stdout);
    #endif

    scanf("%d %d",&n,&m);
    for(int i = 1;i <= n;i ++)
        for(int j = 1;j <= m;j ++)
            scanf("%d",&a[i][j]);

    f[1][2] = a[1][2] + a[2][1];

    for(int i = 4;i < n + m;i ++)
    {
        int Min1 = min(i - 2,n),Min2 = min(i - 1,n);
        
        for(int j = Min1;j >= 1;j --)
        {
            for(int k = Min2;k > j;k --)
            {
                if(j > 1) f[j][k] = max(f[j][k],f[j - 1][k]);
                if(j > 1 && k > 1) f[j][k] = max(f[j][k],f[j - 1][k - 1]);
                if(k - 1 > j) f[j][k] = max(f[j][k],f[j][k - 1]);
                f[j][k] += a[j][i - j] + a[k][i - k];
            }
        }
    }
    printf("%d",f[n - 1][n]);
    
    #ifndef ONLINE_JUDGE
        fclose(stdin);
        fclose(stdout);
    #endif
    
    return 0;
}
```

## 致谢

受[Dalao的题解](https://ouuan.blog.luogu.org/solution-p1006)的影响而写出的题解，因为一开始觉得比较晦涩难懂，所以就重写了一篇给自己一个总结
