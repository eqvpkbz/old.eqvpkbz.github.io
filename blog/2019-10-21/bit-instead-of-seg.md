---
title: 树状数组实现线段树部分功能
description: 能够实现区间查询和区间修改的树状数组
create: 2019.10.21
modified: 2019.10.21
tags: Data Structure 
location: .
top: 0
index: true
template: template
---

[TOC]

# 树状数组实现线段树部分功能


> [P3372 【模板】线段树 1](https://www.luogu.org/problem/P3372)
> 
> 要求实现一个数据结构支持区间查询和区间修改

## 改装后的树状数组

```cpp
#include<cstdio>
using namespace std;
#define MAXN 100010
int n,m;long long tree1[MAXN],tree2[MAXN],k,K,pre = 0,now,Left,Right;
inline void update(int left,int right,long long w)
{
	Left = left * w,Right = right * w;
	for(int i = left;i <= n;i += i & -i) tree1[i] += w,tree2[i] += Left;
	for(int i = right;i <= n;i += i & -i) tree1[i] -= w,tree2[i] -= Right;
}
inline long long query(int left,int right) // 查询
{
	long long ans = 0;
	for(int i = right - 1;i >= 1;i -= i & -i) ans += tree1[i] * right - tree2[i];
	for(int i = left - 1;i >= 1;i -= i & -i) ans -= tree1[i] * left - tree2[i];
	return ans; // sum[right] - sum[left - 1]
}
int main()
{

	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;i ++)
	{
        scanf("%lld",&now);
		k = now - pre,pre = now,K = k * i,
        tree1[i] += k,tree2[i] += K; 
		for(int j = i + (i & -i);j <= n;j += j & -j) // 因为l == r所以可以直接build
			tree1[j] += k,tree2[j] += K;
	}
	while(m--)
    {
        int opt;scanf("%d",&opt);
		if(opt == 1)
        {
            int x,y;
			scanf("%d%d%lld",&x,&y,&k);
			update(x,y + 1,k);
		}
        else
        {
            int x,y;
			scanf("%d%d",&x,&y);
			printf("%lld\n",query(x,y + 1));
		}
	}
	return 0;
}
```
$tree1$表示差分数组,$tree2$表示差分数组 * 对应序号

由代码中的定义可得
```
tree1[1] = a[1];
tree1[2] = a[2] - a[1] + a[1];
tree1[3] = a[3] - a[2];
tree1[4] = a[4] - a[3] + a[3] - a[2] + a[2] - a[1] + a[1];
tree1[5] = a[5] - a[4];

tree2[1] = a[1] * 1;
tree2[2] = (a[2] - a[1]) * 2 + a[1] * 1;
tree2[3] = (a[3] - a[2]) * 3;
tree2[4] = (a[4] - a[3]) * 4 + (a[3] - a[2]) * 3 + (a[2] - a[1]) * 2 + a[1] * 1;
tree2[5] = (a[5] - a[4]) * 5;
```

化简得:

```
tree1[1] = a[1];
tree1[2] = a[2];
tree1[3] = a[3] - a[2];
tree1[4] = a[4];
tree1[5] = a[5] - a[4];

tree2[1] = a[1];
tree2[2] = a[2] * 2 - a[1];
tree2[3] = a[3] * 3 - a[2] * 3;
tree2[4] = a[4] * 4 - a[3] - a[2] - a[1];
tree2[5] = a[5] * 5 - a[4] * 5;

tree2[1] = tree1[1] * 1;
tree2[2] = tree1[2] * 2 - tree1[1];
tree2[3] = tree1[3] * 3;
tree2[4] = tree1[4] * 4 - tree1[3] - tree1[2] * 2 - tree1[1];
tree2[5] = tree1[5] * 5;
```

$n = 3$时有$\sum\limits_{i=1}^{n}a_i = tree1[1] + tree1[2] + （tree1[3] + tree1[2])$
```
tree1[1] + tree1[2] + tree1[3] + tree1[2]
= tree1[1] + 2 * tree1[2] + tree1[3]
= 4 * (tree1[2] + tree1[3]) - 2 * tree1[2] - 3 * tree1[3] + tree1[1]
= 4 * (tree1[2] + tree1[3]) - 2 * tree1[2] + tree1[1] - 3 * tree1[3]
= 4 * (tree1[2] + tree1[3]) - tree2[2] - tree2[3]
= 4 * (tree1[2] + tree1[3]) - (tree2[2] + tree2[3])
= (n + 1) * (tree1[n] + tree1[n - lowbit(n)] + ...) - (tree2[n] + tree2[n - lowbit(n)] + ...)
```

现在已经见到了其中所蕴含的端倪