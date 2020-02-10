---
title: 矩阵快速幂重学
description: 可用于求递推式
create: 2019.10.27
modified: 2019.10.27
tags: algorithm
location: .
top: 0
index: true
template: template
---

[TOC]

# 矩阵快速幂重学

### 快速幂

利用二进制的方式来进行实现

$2^0= 2^0$

$2^1 = 2^1$

$2^2=2^2$

$2^3 = 2^2*2$

$2^4  =2^4$

$2^5 = 2^4*2$

$2^6 = 2 ^ 4 * 2 ^ 2$

$2^7 = 2^4*2^2*2$

所以我们可以看出来的是

二进制位上我们现在只有当某一位是１的时候才乘

举个例子

$$2^{15} =2^{(1111)_2} = 2^{(1000)_2}*2^{(100)_2}*2^{(10)_2}*2^{(1)_2}=2^8*2^4*2^2*2^1 $$

$$2^{10} = 2 ^ {(1010)_2} = 2 ^ {(1000)_2} * 2 ^ {(10)_2} = 2 ^ 8 * 2 ^ 2$$

所以原来$O(b)$复杂度一下降低到了$O(logb)$

```cpp
inline int pow(int a,int b)
{
    int r=1,base=a;
    while(b)
    {
        if(b&1) r*=base;//如果当前位是1，那么直接相乘
        base*=base;//不管是什么数字下一位都需要再乘一次(2的倍数)
        b>>=1;//移到下一位
    }
    return r;//返回结果
}
```

### 矩阵乘法

定义矩阵乘法的运算方式是:

$$c_{ij} = \quad\sum_{k=1}^na_{ik} *b_{kj} $$

举个例子

$$\begin{pmatrix}a_1&a_2&a_3
\\b_1&b_2&b_3\end{pmatrix} \begin{pmatrix}c_1\\c_2\\c_3\end{pmatrix} = \begin{pmatrix}a_1c_1+a_2c_2+a_3c_3\\b_1c_1+b_2c_2+b_3c_3\end{pmatrix}$$

$$\therefore \begin{pmatrix}1&2&3
\\4&5&6\end{pmatrix} \begin{pmatrix}7\\8\\9\end{pmatrix} = \begin{pmatrix}1 * 7 + 2 * 8 + 3 * 9\\4 * 7 + 5 * 8 + 6 * 9\end{pmatrix}$$

$$\therefore \begin{pmatrix}1&2&3
\\4&5&6\end{pmatrix} \begin{pmatrix}7\\8\\9\end{pmatrix} = \begin{pmatrix}50\\122\end{pmatrix}$$

```cpp
int n;//矩阵大小

void Up(int &x, int y) { x = (x + y) % mod; }//简单定义 += 

struct Matrix
{
	int a[n][n];//矩阵
	friend Matrix operator *(const Matrix x, const Matrix y)//定义矩阵类型的乘法
	{
		Matrix c;//定义新的矩阵用来存储结果
		memset(c.a, 0, sizeof(c.a));//初始化
		for(int i = 0; i < n;i ++)//进行枚举
			for(int j = 0; j < n;j ++)
				for(int k = 0; k < n;k ++)
					Up(c.a[i][j], x.a[i][k] * y.a[k][j] % mod);//相乘 
		return c;//返回答案矩阵
	}
};
```

### 如何利用矩阵乘法计算

在计算递推式的时候，我们可以把递推式构建成矩阵乘法的样子

比如形如下列递推式的递推式:

$$f(n) = a * f(n - 1) + b * f(n - 2)$$

我们可以考虑构造成:

$$\begin{pmatrix}a&b\\1&0\end{pmatrix} \begin{pmatrix}f(n - 1)\\f(n - 2)\end{pmatrix} = \begin{pmatrix}f(n)\\f(n - 1)\end{pmatrix}$$

然后就有:

$$\begin{pmatrix}a&b\\1&0\end{pmatrix} \begin{pmatrix}f(n - 1)\\f(n - 2)\end{pmatrix} = \begin{pmatrix}f(n)\\f(n - 1)\end{pmatrix}$$

$$\because\begin{pmatrix}a&b\\1&0\end{pmatrix} \begin{pmatrix}f(n - 2)\\f(n - 3)\end{pmatrix} = \begin{pmatrix}f(n - 1)\\f(n - 2)\end{pmatrix}$$

$$\therefore \begin{pmatrix}a&b\\1&0\end{pmatrix}^2 \begin{pmatrix}f(n - 2)\\f(n - 3)\end{pmatrix} = \begin{pmatrix}f(n)\\f(n - 1)\end{pmatrix}$$

$$\begin{pmatrix}a&b\\1&0\end{pmatrix}^3 \begin{pmatrix}f(n - 3)\\f(n - 4)\end{pmatrix} = \begin{pmatrix}f(n)\\f(n - 1)\end{pmatrix}$$

$$\begin{pmatrix}a&b\\1&0\end{pmatrix}^{n-1} \begin{pmatrix}f(1)\\f(0)\end{pmatrix} = \begin{pmatrix}f(n)\\f(n - 1)\end{pmatrix}$$

然后构造起来的道理是这样，但是真正的矩阵是什么样子的还得自己知道怎么推然后再去做

假如给你一个形如$f(n) = a * f(n - 1) + b * f(n - 2） + c * f(n - 3)$你要是不会推还是会`GG`的

然后因为有的时候$dp$的递推式也可以用矩阵来加速，所以用处很大

### 矩阵乘法快速幂

前一部分的模板

```cpp
void Up(int &x, int y) { x = (x + y) % mod; }//简单定义+=

struct Matrix
{
	int a[n][n];
	friend Matrix operator *(const Matrix x, const Matrix y)//定义矩阵乘法
	{
		Matrix c;
		memset(c.a, 0, sizeof(c.a));
		for(int i = 0; i < n; i ++)
			for(int j = 0; j < n; j ++)
				for(int k = 0; k < n; k ++)
					Up(c.a[i][j], x.a[i][k] * y.a[k][j] % mod); 
		return c;
	}
};

Matrix Qpow(Matrix x, int timer)//矩阵快速幂
{
	Matrix base;//定义结果矩阵
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			base.a[i][j] = 0;
	for(int i = 0; i < n; i ++) base.a[i][i] = 1;
	for(; timer; timer >>= 1, x = x * x)
		if(timer & 1) base = base * x;
	return base;
}
```

### PROB

- [Luogu P1962 斐波那契数列](https://www.luogu.org/problemnew/show/P1962)
