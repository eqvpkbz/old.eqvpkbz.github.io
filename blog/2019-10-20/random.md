---
title: 随机数初探
description: 探究随机数的科学用法
create: 2019.10.20
modified: 2019.10.20
tags: random
top: 0
location: .
index: true
template: template
---

[TOC]

# 随机数初探

在各种各样的考试中，我们经常会碰见各种各样的情况，诸如:

- `wori`，我明明打的是正解啊!
- `wori`，我过了大样例啊!

等等情况，这种情况您可能需要对拍这种方式来解决问题，但是也有人说:

- `wori`，我明明拍过了`1e5`组数据啊!!!

那八成就是随机数或者暴力打挂了

本文主要讲述随机数的科学使用

## Random

```cpp
#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
typedef long long ll;
inline ll Rand(ll lef,ll rig){return rand() % (rig - lef + 1) + lef;}
int main()
{
    srand(time(0));
    ll lef = 21474836488, rig = 21474836490;
    printf("%lld",Rand(lef,rig));
    return 0;
}
```

## default_random_engine

```cpp
#include <random>
#include <ctime>
using namespace std;
typedef long long ll;

ll Rand(const ll lef, const ll rig)
{
    static std::default_random_engine e(time(NULL));
    static std::uniform_int_distribution<ll> u(lef, rig);
    return u(e);
}
int main()
{
    ll lef = 21474836488,rig = 21474836490;
    printf("%lld ",Rand(lef, rig));
    return 0;
}
```

## mt19937

```cpp
#include<random>
#include<ctime>
std::mt19937 rnd(time(0));
int main()
{
    printf("%lld\n",rnd());
    return 0;
}
```