---
title: 初探splay
description: 平衡树学习
create: 2019.11.3
modified: 2019.11.3
tags: Data Structure
location: .
top: 0
index: true
template: template
---

[TOC]

# 初探splay

```cpp
#include<cctype>
#include<cstdio>
using namespace std;

#define debug(...) fprintf(stderr,__VA_ARGS__)
#define DEBUG printf("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %lld\n",__FUNCTION__,__LINE__)
#define file(FILE_NAME) freopen(FILE_NAME".in","r",stdin),freopen(FILE_NAME".out","w",stdout)
#define file_close fclose(stdin),fclose(stdout)

#define MAXBUF 2097152
#define FLUSHSIZE 1966080
#define Finline __inline__ __attribute__ ((always_inline))
char BUF[MAXBUF],*P1=BUF,*P2=BUF;
Finline int getc(){return P1==P2&&(P2=(P1=BUF)+fread(BUF,1,MAXBUF,stdin),P1==P2)?EOF:*P1++;}
inline int read()
{
    int ret = 0,f = 0;char ch = getc();
    while(!isdigit (ch)){if(ch == '-') f = 1;ch = getc();}
    while(isdigit (ch)){ret = ret * 10 + ch - 48;ch = getc();}
    return f?-ret:ret;
}
char buf[MAXBUF],print_buf[20];int p,p2=-1;
inline void flush(){fwrite(buf,1,p2+1,stdout),p2=-1;}
inline void write(int x)
{
    if(p2 > FLUSHSIZE) flush();
    if(x<0) buf[++ p2]=45,x = -x;
    do{print_buf[++ p] = x % 10 + 48;}while(x/=10);
    do{buf[++p2] = print_buf[p];}while(--p);
    buf[++p2]='\n';
}

const int N = 100005;
int rt, tot, fa[N], ch[N][2], val[N], cnt[N], sz[N];
struct SPLAY
{
	inline void maintain(int x){sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];}
	inline bool get(int x){return x == ch[fa[x]][1];}
	inline void clear(int x){ch[x][0] = ch[x][1] = fa[x] = val[x] = sz[x] = cnt[x] = 0;}
	inline void rotate(int x)
	{
		int y = fa[x], z = fa[y], chk = get(x);

		ch[y][chk] = ch[x][chk ^ 1];
		fa[ch[x][chk ^ 1]] = y;

		ch[x][chk ^ 1] = y;
		fa[y] = x,fa[x] = z;

		if(z) ch[z][y == ch[z][1]] = x;
		maintain(x),maintain(y);
	}
	void splay(int x)
	{
		for(int f = fa[x]; f = fa[x] ,f ; rotate(x))
			if(fa[f]) rotate(get(x) == get(f) ? f : x);
		rt = x;
	}
	void insert(int k)
	{
		if(!rt) //splay is empty
		{
			val[++ tot] = k,cnt[tot] ++;//set point
			rt = tot,maintain(rt);//set root
			return;
		}
		int cur = rt, f = 0;//insert from rt
		while(1)
		{
			if (val[cur] == k) //find out a point whose value is k
			{
				cnt[cur] ++;//size ++
				maintain(cur),maintain(f);//update
				splay(cur);//rotate to root
				break;
			}
			f = cur,cur = ch[cur][val[cur] < k];//find left / right subtree
			if(!cur)// find a empty position to insert
			{
				val[++ tot] = k,cnt[tot]++;
				fa[tot] = f,ch[f][val[f] < k] = tot;
				maintain(tot),maintain(f);//update
				splay(tot);
				break;
			}
		}
	}
	int rk(int k) //find k's rank
	{
		int res = 0, cur = rt;
		while(1)
		{
			if(k < val[cur]) cur = ch[cur][0];//find left subtree
			else //find right subtree
			{
				res += sz[ch[cur][0]];//add left subtree's size
				if(k == val[cur])//find out element
				{
					splay(cur);//rotate to root
					return res + 1;//return rank
				}
				res += cnt[cur];//add current point value
				cur = ch[cur][1];//find right subtree
			}
		}
	}
	int kth(int k)
	{
		int cur = rt;
		while(1)
		{
			if(ch[cur][0] && k <= sz[ch[cur][0]])
				cur = ch[cur][0]; //find left subtree
			else
			{
				k -= cnt[cur] + sz[ch[cur][0]]; //find right subtree
				if(k <= 0) return val[cur];//return current point value
				cur = ch[cur][1];//find right subtree
			}
		}
	}
	int pre()//find root's predecessor
	{
		int cur = ch[rt][0];//find left subtree
		while(ch[cur][1]) cur = ch[cur][1];//find right subtree
		return cur;
	}
	int nxt()
	{
		int cur = ch[rt][1];//find right subtree
		while (ch[cur][0]) cur = ch[cur][0];//find left subtree
		return cur;
	}
	void del(int k)
	{
		rk(k);
		if(cnt[rt] > 1) //have many same point
		{
			cnt[rt]--;//delete one and update
			maintain(rt);
			return;
		}
		if(!ch[rt][0] && !ch[rt][1]) //have no left / right son
		{
			clear(rt);//delete
			rt = 0;
			return;
		}
		if(!ch[rt][0]) //only have right son
		{
			int cur = rt;
			rt = ch[rt][1];
			fa[rt] = 0;
			clear(cur);
			return;
		}
		if(!ch[rt][1]) //only have left son
		{
			int cur = rt;
			rt = ch[rt][0];
			fa[rt] = 0;
			clear(cur);
			return;
		}
		int x = pre(), cur = rt;
		splay(x),fa[ch[cur][1]] = x;//right son's father is x's predecessor
		ch[x][1] = ch[cur][1];//x's predecessor 's right son is x's right son
		clear(cur),maintain(rt);
	}
}tree;

int main()
{
	#ifndef ONLINE_JUDGE
		file("splay");
	#endif

	int n = read(), opt, x;
	for(int i = 0;i < n;i ++)
	{
		opt = read(),x = read();
		if(opt == 1) tree.insert(x);
		else if(opt == 2) tree.del(x);
		else if(opt == 3) write(tree.rk(x));
		else if(opt == 4) write(tree.kth(x));
		else if(opt == 5) tree.insert(x),write(val[tree.pre()]), tree.del(x);
		else tree.insert(x), write(val[tree.nxt()]),tree.del(x);
	}
	flush();

	#ifndef ONLINE_JUDGE
		file_close;
	#endif
	return 0;
}
```
