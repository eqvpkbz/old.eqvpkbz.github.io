---
title: 浅析LIS & LCS
description: 希望能给部分OIer指点迷津
create: 2019.10.20
modified: 2019.10.20
tags: dp
top: 0
location: .
index: true
template: template
---

[TOC]

# 浅析$LIS \& LCS$

## $LIS$(最长上升子序列)

### 求长度

####  $dp$ - $O(n ^ 2)$

动态规划的做法

令$f[i]$表示以第$i$个元素结尾的$LIS$长度

则有: $f[i] = max(f[i],f[j] + 1),(a[j] < a[i],j < i)$

通过枚举$f[i]$与$f[j]$来不断转移状态，然后不断枚举更新最大值

$Code$:
```cpp
#include<cstdio>
using namespace std;
#define maxn 10005
int f[maxn],a[maxn];
int main()
{
    int n,Max = 0;
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    for(int i = 1;i <= n;i ++)
    {
        f[i]  = 1;
        for(int j = 1;j < i;j ++) 
            if(a[j] < a[i] && f[i] < f[j] + 1) f[i] = f[j] + 1;
    }
    for(int i = 1;i <= n;i ++) if(f[i] > Max) Max = f[i];
    printf("%d",Max);
    return 0;
}
```

该算法可以求出具体的最长上升子序列，但是在只要求最长上升子序列长度时，我们通常可以考虑更优的$O(n \ log_2 \ n)$的做法

#### $dp$+树状数组$O(n \ log_2 \ n)$

注意到我们在状态转移的时候要枚举$f[j]$的最大值来转移，我们可以考虑使用数据结构来维护从而优化一下，只要是支持单点修改和区间最值查询的数据结构都可以这么做，分块$(O(n \sqrt n))$和树状数组$(O(n \ log_2 \ n))$，线段树$(O(n \ log_2 \ n))$之类的都行，但是因为树状数组比较好写，所以我们只讲解树状数组的写法
1. 先按权值排序，排序之后再查询序号前最大的$f[j]$来转移，但是有一点要注意，我们求的是LIS，是严格上升的，所以我们遇到重复的权值的时候应该要放在最后一次性处理，不然后面的重复了的$f[]$就能够用前面相同的元素来转移，导致最后的答案是错误的
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 1000007
int n,Dp[maxn],Ans,Max[maxn];
struct Node{int w,i;}A[maxn];
#define lowbit(x) ((x) & (-x))
inline bool cmp(Node A , Node B){return A.w < B.w;}
inline void Update(int Pos , int w) 
{
    for(int i = Pos;i <= n; i += lowbit(i)) 
        Max[i] = max(Max[i] , w);
}
inline int Query(int Pos) 
{
    int Ret = 0;
    for(int i = Pos ; i ; i -= lowbit(i)) 
        Ret = max(Ret , Max[i]);
    return Ret;
}
int main() 
{
	scanf("%d" , &n);
	for(int i = 1;i <= n;i ++) scanf("%d" , &A[i].w) , A[i].i = i;
	sort(A + 1 , A + 1 + n ,cmp);
	int Last = 1;//为了处理权值相同时的情况
	for(int i = 1;i <= n;i ++) //确保权值的大小关系正确
	{
		if(A[i].w != A[i - 1].w && i - 1) //处理前面权值相同的情况
		{
			for(int j = Last;j <= i - 1;j ++) Update(A[j].i , Dp[j]); 
			//如果不是到了最后再更新的话,后面重复的就会用前面重复的值来更新
			Last = i;//处理完转移过来
		}
		Dp[i] = Query(A[i].i) + 1;//转移
		Ans = max(Ans , Dp[i]);
	}
	printf("%d" , Ans);
	return 0;
}
```
2. 维护$f[]$这个数组，但是用权值作为数组下标，然后不需要$sort$，顺序枚举就可以了，关于值的大小我们可以直接查找(树状数组)，注意到范围很大时，我们可以进行离散化
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 1000007
int n,ans,f[maxn];
struct Node{int val,num;}z[maxn]; 
#define lowbit(x) ((x) & (-x))
inline void modify(int x,int y)
{
	for(;x < maxn ;x += lowbit(x))
		f[x] = max(f[x],y);
	return ;
}
inline int query(int x)
{
	int res = 0;
	for(;x;x -= lowbit(x)) res = max(res,f[x]);
	return res;
} 
int main()
{
	scanf("%d",&n);
	for(int i = 1;i <= n;i ++) scanf("%d",&z[i].val);
	for(int i = 1;i <= n;i ++)
	{
		int Max = query(z[i].val - 1);
		modify(z[i].val , ++ Max);
		ans = max(ans,Max);
	}
	printf("%d",ans);
	return 0;
}
```
#### 贪心+二分$O(n \ log_2 \ n)$

贪心的做法

维护一个单调栈，然后根据栈定元素元素和当前元素作比较来选择最优策略，定义$stack[]$为单调栈，栈顶元素为$stack[top]$，当前序列的第$i$个元素为$a[i]$

1. 如果$stack[top] < a[i]$ 那么满足单调，可以直接压入栈中
2. 如果$stack[top] \geqslant a[i]$ 那么这个时候插入就不满足单调了，那么我们考虑在单调栈中进行二分查找，然后找到第一个$stack[j] \geqslant a[i]$进行替换即可

> Q:为什么进行替换这一贪心的策略是可行的?

> A: 因为这样做并没有增长栈的长度，而且这么一接下去就可以有更好的方案，其实感性的理解就是一个在栈中不止一个序列，可以理解为两条或者更多，但是在替换之后的元素的压入可以应用到每一条序列中作出贡献，比如下面的这个例子

$Input$:

```
5
1 4 2 5 3
```

稍稍根据上面的贪心决策不难推出这样的一个过程:

1. stack[1] = {1};
2. stack[2] = {1,4};
3. stack[2] = {1,2};
4. stack[3] = {1,2,5};
5. stack[3] = {1,2,3};

看到第$3$步中的替换过程，$4$变成了$2$，其实$4$也存在`{1,4,5}`这样的最长上升子序列，但是如果后面还有数字就没有$2$更优，在我们替换过后，$4$其实也在参与，但是因为我们发现的更加优越的$2$，所以$4$的贡献肯定比$2$的贡献要小，可以直接替换掉

##### $Warning$

该$O(n \ log_2 \ n)$算法其实不能求出具体的最长上升子序列，因为中间在替换的过程中就已经把原有的顺序给打乱了，对于替换掉的元素，不知道是否能够对于后面的最长上升子序列作出价值，所以是不可以的

$Code$:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100005
int a[maxn],d[maxn];
int main() 
{
    int n,len = 1;
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    d[1] = a[1];
    for(int i = 2; i <= n; i ++)
    {
        if(d[len] < a[i]) d[++ len] = a[i];
        else *lower_bound(d + 1 , d + 1 + len , a[i]) = a[i];
    }
    printf("%d",len);
    return 0;
}
```
### 求具体$LIS$序列

此题$dp - O(n ^ 2)$中的思想可以应用，相应的，我们可以再加上一个树状数组来优化算法的时间复杂度到$O(n \ log_2 \ n)$，通过记录一个结尾对应的序列中的前驱来优化算法的空间复杂度至$O(n)$，然后就十分的可做了，因为树状数组有两种写法，作者在此只写出一种做法的解法，另外一种解法可以让读者自行思考，不过最好是离散化一下
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define maxn 1000007
int n,Dp[maxn],Ans,Max[maxn],Max_num[maxn],pre[maxn],num = 0,a[maxn];
struct Node{int w,i;}A[maxn];
#define lowbit(x) ((x) & (-x))
inline bool cmp(Node A , Node B){return A.w < B.w;}
inline void Update(int Pos , int w,int Num) 
{
    for(int i = Pos;i <= n; i += lowbit(i)) 
        if(Max[i] < w) Max[i] = w,Max_num[i] = Pos;
    return ;
}
inline int Query(int Pos) 
{
    int Ret = 0;num = 0;
    for(int i = Pos ; i ; i -= lowbit(i)) 
        if(Ret < Max[i]) Ret = Max[i],num = Max_num[i];
    return Ret;
}
inline void Output(int first)
{
	if(!first) return ;
	else Output(pre[first]);
	printf("%d ",a[first]);
	return ;
}
int main() 
{
	scanf("%d" , &n);
	for(int i = 1;i <= n;i ++) scanf("%d",&a[i]),A[i].w = a[i],A[i].i = i;
	sort(A + 1 , A + 1 + n ,cmp);
	int Last = 1,first = 0;
	for(int i = 1;i <= n;i ++)
	{
		if(A[i].w != A[i - 1].w && i - 1)
		{
			for(int j = Last;j <= i - 1;j ++) Update(A[j].i , Dp[j],j); 
			Last = i;
		}
		Dp[i] = Query(A[i].i) + 1;
		pre[A[i].i] = num;
		if(Ans < Dp[i]) Ans = Dp[i],first = A[i].i;
	}
	printf("%d\n" , Ans);
	Output(first);
	return 0;
}
```

## $LCS$(最长公共子序列)

### 求长度

#### $O(nm)$

动态规划做法，其实原理很简单，就是看当前的位上是否匹配的问题，然后根据这个来转移状态

设有长度为$n$的串$S$与长度为$m$的串$T$，用$f[i,j]$表示$S$串前$i$个字符与$T$串前$j$个字符的$LCS$则有:

$f[i,j] = max(f[i - 1,j],f[i,j - 1],(f[i - 1,j - 1] + 1) * [S_i = T_j])$

也就是说，无论如何，一定有

$f[i,j] = max(f[i - 1,j],f[i,j - 1])$

讨论特殊情况:当$S_i = T_j$时

$f[i,j] = max(f[i,j],f[i - 1,j - 1] + 1)$

所以我们可以从这推出结果，然后$f[n,m]$就是最后的答案

因为$f[i]$总是会从$f[i - 1]$这一维度转移过来，所以我们可以考虑用滚动数组来优化空间复杂度

$Code$:
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int maxn = 5e3 + 7;

int n,m,tmp;
char a[maxn],b[maxn];
int f[2][maxn];

int main()
{
    scanf("%s",a + 1);
    n = strlen(a + 1);
    scanf("%s",b + 1);
    m = strlen(b + 1);
    int now = 0;
    for(int i = 0;i <= n;i ++)
    {
        now ^= 1;
        for(int j = 1;j <= m;j ++)
        {
            f[now][j] = max(f[now ^ 1][j],f[now][j - 1]);
            tmp = f[now ^ 1][j - 1] + 1;
            if(a[i] == b[j] && f[now][j] < tmp) f[now][j] = tmp;
        }
    }
    printf("%d",f[now][m]);
    return 0;
}
```

#### $O(n \ log_2 \ n)$

其实我先讲$LIS$是有原因的，我们可以尝试着去探求这两个问题之间的联系

如果我可以通过把这个原来的序列转化为另外一个序列然后求$LIS$来得到$LCS$就好了，那么怎么去转换这两个问题呢?

我们不难发现，$LIS$是用来求最长上升子序列的，所以当一个序列是升序排序，另外一个序列乱序时，求两个序列的$LCS$其实就是在求乱序序列的$LIS$，因为有一个序列是升序的，所以一定存在乱序序列的最长上升子序列与升序序列的序列有最长公共子序列，所以就可以求出来了

所以我们在一开始输入$A$序列的时候就将它序列中的元素逐一编号，然后再在B序列给对应的元素编上在$A$序列中的编号，也就是$B$序列中元素在$A$序列中的位置

比如说
```
1 5 4 3 2
5 3 1 2 4
```
编号之后就是
```
1 2 3 4 5
2 4 1 5 3
```

然后去求改变后的$B$序列的$LIS$就好了，也就是答案`2 4 5`，长度为$3$

##### $Warning$

1. 在两个序列有不同元素的时候，处理的时候要去掉不同的元素，否则$LIS$可能会包含另外一个序列没有的元素而导致答案错误

2. 在两个序列中有重复的元素时，不能用该方法处理

比如说:
```
abacc
cbabb
```

我们可以发现这两个序列的$LCS$是`ab`或`ba`长度为2

但是在处理赋值的过程中有点小麻烦
```
abacc
cbabb
```
```
1 2 3 4 5
5 2 3 2 2
```
我们发现在处理完的序列中有重复的数字，这是因为在第一次给$A$中的元素赋值的时候，我们对于重复的元素赋了两次值，于是就导致了序列中数字所对应的位置有多个，在处理过程中会覆盖掉

那你可能会说:我不覆盖掉不就是了

然后你这个$naive$的想法可能就会泡汤，因为在某些情况下，不管你怎么赋值，其实都不一定会是一个升序的序列，这个时候求另外一个序列的$LIS$就没有意义了，因为你本身的序列就不是升序，我求一遍升序就与另一个序列无关了

3. 该算法不能求出具体的$LCS$序列，所以如果题目要求出具体的子序列时不能使用该算法，原因同$LIS$的$n \ log_2 \ n$做法

$Code$:
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 100005
int a[maxn],b[maxn];
int d[maxn],stack[maxn],len = 0;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;i ++) 
    {
        scanf("%d",&a[i]);
        d[a[i]] = i + 1;
    }
    for(int i = 0;i < n;i ++) 
    {
        scanf("%d",&b[i]);
        b[i] = d[b[i]];
    }
    stack[1] = b[0],len = 1;
    for(int i = 0;i < n;i ++)
    {
        if(stack[len] < b[i]) stack[++ len] = b[i];
        else *upper_bound(stack + 1,stack + 1 + len,b[i]) = b[i];
    }
    printf("%d",len);
    return 0;
}
```

### 求具体$LCS$序列

我们可以考虑借鉴一下$LIS$的写法，记录前驱和最大值开头的数值，然后进行递归倒序输出，但是这个时候我们的$dp[]$不能用数据结构来优化，所以我们的算法是$O(nm)$的，具体代码请读者自行思考

## $LCIS$(最长公共上升子序列)

我们可以结合上面的$LIS$和$LCS$的思想来思考这个问题

$LIS:$

令$f[i]$表示以第$i$个元素结尾的$LIS$长度

则有: $f[i] = max(f[i],f[j] + 1),(a[j] < a[i],j < i)$

$LCS:$

设有长度为$n$的串$S$与长度为$m$的串$T$，用$f[i,j]$表示$S$串前$i$个字符与$T$串前$j$个字符的$LCS$则有:

$f[i,j] = max(f[i - 1,j],f[i,j - 1],(f[i - 1,j - 1] + 1) * [S_i = T_j])$

稍加组合思考我们可以发现:

当$f[i,j]$表示$A$序列前$i$个元素和$B$序列前$j$个元素的$LCIS$，$t$表示$LCIS$的结尾元素位置，则有:

$f[i,j] = f[i - 1,j],A_i \ne B_j$

$f[i,j] = max(f[i - 1,j],f[i - 1,t] + 1),A_i = B_j$

又发现$f[i]$这一维每次都是从$f[i - 1]$这一维转移过来，所以我们可以用滚动数组优化一下得到:

$f_i$代表序列$A$前$i$个元素与序列$B$的$LCIS$，$t$为结尾位置，有

$f_j = f_t + 1,A_i = B_j$

在计算$LCIS$的长度的过程中我们可以顺便记录前驱然后输出具体的序列，所以就可以用$O(nm)$的时间复杂度算出$LCIS$长度与$LCIS$的具体序列

$Code$:
```cpp
#include<cstdio>
using namespace std;
#define maxn 505
int a[maxn],b[maxn],f[maxn],pos[maxn];
void output(int x)
{
    if(!x) return;
    output(pos[x]);
    printf("%d ",b[x]);
}
int main() 
{
    int n,m,Max = 0;
    scanf("%d",&n);
    for(int i = 1;i <= n;i ++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i = 1;i <= m;i ++) scanf("%d",&b[i]);

    for(int i = 1,t = 0;i <= n;i ++,t = 0)
        for(int j = 1;j <= m;j ++) 
        {
            if(a[i] == b[j]) f[j] = f[t] + 1,pos[j] = t;//f[j] 的结尾
            if(a[i] > b[j] && f[t] < f[j]) t = j;// 保证t在结尾位置
        }
    for(int i = 1;i <= m;i ++)
        if(f[i] > f[Max]) Max = i;
    printf("%d\n",f[Max]);
    output(Max);
    return 0;
}
```
至此，我们已经讨论了$LIS$，$LCS$与$LCIS$三种基础的动态规划类型，算法与算法之间的联系可见一斑了

***

**致谢**

- 感谢洛谷上的部分优质题解，我从题解中找到了很多的思路，受教良多
- $Liang$_$Shine$_$Sky$ 大佬的指点
