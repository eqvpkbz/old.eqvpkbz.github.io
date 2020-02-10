---
title: 数论学习
description: 数论相关的东西
create: 2019.10.20
modified: 2019.11.8
tags: math
top: 0
location: .
index: true
template: template
---

[TOC]

# 数论学习

更新一些关于数论的知识点

## *具体数学*

### 数学归纳法

#### 格式:

1. 证明当$n$的值为初值时的式子成立 (基础$(basic)$)
2. 假设当$n = k$时原式成立，即有 : ....
3. 则当$n = k + 1$时，论证式子恒成立 (归纳$(induction)$)

***

#### e.g. 1：

> 数学归纳法证明等差数列存在$a_n = a_1 + (n - 1)d$

当$n = 2$时,$a_2 = a_1 + d$,满足定义式: $a_n = a_{n - 1} + d$

假设$n = k$时,$a_k = a_1 + (k - 1)d$成立，则$n = k + 1$时,$a_{k + 1} = a_k + d = a_1 + (k - 1)d + d = a_1 + kd$

所以当$n \geqslant 2$时,$a_n = a_1 + (n - 1)d$ $\qquad \blacksquare$
***

#### e.g. 2:

> 数学归纳法证明平面上的$n$条直线最多界定的区域个数$Ln = \dfrac{n(n + 1)}{2} + 1 , n \geqslant 0$

存在递推式:

$L_0 = 1$

$L_n = L_{n - 1} + n,n > 0$

当$n = 1$时，$L_1 = 1 + 1 = L_0 + 1$,满足递推式

假设$n = k$时，$L_k = \dfrac{k(k + 1)}{2} + 1$成立，则$n = k + 1$时，$L_{k + 1} = \dfrac{k(k + 1)}{2} + 1 + (k + 1)=\dfrac{(k + 1)(k + 2)}{2} + 1$

所以当$n \geqslant 1$时，$Ln = \dfrac{n(n + 1)}{2} + 1 , n \geqslant 0$ $\qquad \blacksquare$