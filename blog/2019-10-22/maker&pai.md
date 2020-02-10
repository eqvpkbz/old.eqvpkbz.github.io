---
title: 数据生成器,对拍,多数据自动生成器
description: 十分有用的东西
create: 2019.10.22
modified: 2019.10.22
tags: tools
location: .
top: 0
index: true
template: template
---

[TOC]

# 对拍,多组数据自动生成器

### 使用平台

Linux,gcc,g++编译器

### 注意事项

记得标程，数据生成器和暴力别出问题了

另外数据生成器中的随机数改天会去看看的~~目前来看还是在鸽着的~~

### 对拍

#### 注释版

```cpp
#include<cstdio>
#include<cstdlib>
#include<sys/time.h>
using namespace std;
#define DEFAULT_NUM 100
#define sec 1000000
int main()
{
    system("g++ maker.cpp -o maker");
    system("g++ std.cpp -o std");
    system("g++ brute.cpp -o brute");
    for(int i = 1;i <= DEFAULT_NUM;i ++)
    {
        struct timeval STD_START,STD_END,MAKER_START,MAKER_END,BRUTE_START,BRUTE_END; //计算时间所需要的结构体

        gettimeofday(&MAKER_START,NULL);
        system("./maker > in");
        gettimeofday(&MAKER_END,NULL);
        long double MAKER_TIME = sec * (MAKER_END.tv_sec-MAKER_START.tv_sec) + MAKER_END.tv_usec - MAKER_START.tv_usec;
        printf("Make data %d : used %.2Lfus\n", i, MAKER_TIME); //造数据的程序计时

        gettimeofday(&STD_START,NULL);
        system("./std < in > sout");
        gettimeofday(&STD_END,NULL);
        long double STD_TIME = sec * (STD_END.tv_sec-STD_START.tv_sec) + STD_END.tv_usec - STD_START.tv_usec;
        printf("Run std in data %d : use %.2Lfus\n", i, STD_TIME); //标程计时

        gettimeofday(&BRUTE_START,NULL);
        system("./brute < in > bout");
        gettimeofday(&BRUTE_END,NULL);
        long double BRUTE_TIME = sec * (BRUTE_END.tv_sec-BRUTE_START.tv_sec) + BRUTE_END.tv_usec - BRUTE_START.tv_usec;
        printf("Run brute in data %d : use %.2Lfus\n", i, BRUTE_TIME);//暴力计时
        
        if(system("diff -Bb sout bout"))
        {
            puts("GG");
            exit(0);
        }
        printf("Passed %d ......\n",i);
        if(MAKER_TIME + STD_TIME + BRUTE_TIME < sec) system("sleep 1"); //如果时间超过1s就可以直接进行下一组数据
    }
    return 0;
}
```

#### 复制版

```cpp
#include<cstdio>
#include<cstdlib>
#include<sys/time.h>
using namespace std;
#define DEFAULT_NUM 100
#define sec 1000000
int main()
{
    system("g++ maker.cpp -o maker");
    system("g++ std.cpp -o std");
    system("g++ brute.cpp -o brute");
    for(int i = 1;i <= DEFAULT_NUM;i ++)
    {
        struct timeval STD_START,STD_END,MAKER_START,MAKER_END,BRUTE_START,BRUTE_END;

        gettimeofday(&MAKER_START,NULL);
        system("./maker > in");
        gettimeofday(&MAKER_END,NULL);
        long double MAKER_TIME = sec * (MAKER_END.tv_sec-MAKER_START.tv_sec) + MAKER_END.tv_usec - MAKER_START.tv_usec;
        printf("Make data %d : used %.2Lfus\n", i, MAKER_TIME);

        gettimeofday(&STD_START,NULL);
        system("./std < in > sout");
        gettimeofday(&STD_END,NULL);
        long double STD_TIME = sec * (STD_END.tv_sec-STD_START.tv_sec) + STD_END.tv_usec - STD_START.tv_usec;
        printf("Run std in data %d : use %.2Lfus\n", i, STD_TIME);

        gettimeofday(&BRUTE_START,NULL);
        system("./brute < in > bout");
        gettimeofday(&BRUTE_END,NULL);
        long double BRUTE_TIME = sec * (BRUTE_END.tv_sec-BRUTE_START.tv_sec) + BRUTE_END.tv_usec - BRUTE_START.tv_usec;
        printf("Run brute in data %d : use %.2Lfus\n", i, BRUTE_TIME);
        
        if(system("diff -Bb sout bout"))
        {
            puts("GG");
            exit(0);
        }
        printf("Passed %d ......\n",i);
        if(MAKER_TIME + STD_TIME + BRUTE_TIME < sec) system("sleep 1");
    }
    return 0;
}
```


### 多组数据自动生成器

#### 详细注释版

```cpp
#include<cstdio>
#include<ctime>
#include<string>
#include<cstdlib>
#include<sstream>
#include<unistd.h>
#include<sys/time.h>
using namespace std;

string I, ord1, ord2;
stringstream tmp;
string name = "seg";
#define sec 1000000
//sec就是一秒对应的微秒数
int l, r;

int main() 
{
    system("g++ std.cpp -o std"); //编译标程
    printf("please type the first l and r\n");
    while(scanf("%d%d", &l, &r) == 2) //输入数据的文件下标范围
    {
        system("g++ maker.cpp -o maker");//为了方便改了maker之后直接造数据
        for(int i = l; i <= r; i ++) 
        {
            tmp.clear(),tmp << i,tmp >> I; //将下标i倒序处理以便用来做文件名
            string ord1 = "./maker > " + name + I + ".in";
            string ord2 = "./std < " + name + I + ".in > " + name + I + ".out";
            struct timeval STD_START,STD_END,MAKER_START,MAKER_END; //计算时间所需要的结构体

            gettimeofday(&MAKER_START,NULL);
            system(ord1.data());
            gettimeofday(&MAKER_END,NULL);
            long double MAKER_TIME = sec * (MAKER_END.tv_sec-MAKER_START.tv_sec) + MAKER_END.tv_usec - MAKER_START.tv_usec;
            printf("Make data %d : used %.2Lfus\n", i, MAKER_TIME); //造数据的程序计时

            gettimeofday(&STD_START,NULL);
            system(ord2.data());
            gettimeofday(&STD_END,NULL);
            long double STD_TIME = sec * (STD_END.tv_sec-STD_START.tv_sec) + STD_END.tv_usec - STD_START.tv_usec; //标程计时
            printf("Run std in data %d : use %.2Lfus\n", i, STD_TIME);

            if(MAKER_TIME + STD_TIME < sec) system("sleep 1"); //如果时间超过1s就可以直接进行下一组数据
            for(int j = 1; j <= 10; j ++)
                puts("................");
            printf("Finish Make Data %d\n\n\n", i);
        }
        printf("Data %d to %d is finish\n", l, r);
        printf("please change maker.cpp and then type next l and r\n\n");
    }
    return 0;
}
```

#### 直接复制版

```cpp
#include<cstdio>
#include<ctime>
#include<string>
#include<cstdlib>
#include<sstream>
#include<unistd.h>
#include<sys/time.h>
using namespace std;

string I, ord1, ord2;
stringstream tmp;
string name = "seg";
#define sec 1000000
int l, r;

int main() 
{
    system("g++ std.cpp -o std");
    printf("please type the first l and r\n");
    while(scanf("%d%d", &l, &r) == 2) 
    {
        system("g++ maker.cpp -o maker");
        for(int i = l; i <= r; i ++) 
        {
            tmp.clear(),tmp << i,tmp >> I;
            string ord1 = "./maker > " + name + I + ".in";
            string ord2 = "./std < " + name + I + ".in > " + name + I + ".out";
            struct timeval STD_START,STD_END,MAKER_START,MAKER_END;

            gettimeofday(&MAKER_START,NULL);
            system(ord1.data());
            gettimeofday(&MAKER_END,NULL);
            long double MAKER_TIME = sec * (MAKER_END.tv_sec-MAKER_START.tv_sec) + MAKER_END.tv_usec - MAKER_START.tv_usec;
            printf("Make data %d : used %.2Lfus\n", i, MAKER_TIME);

            gettimeofday(&STD_START,NULL);
            system(ord2.data());
            gettimeofday(&STD_END,NULL);
            long double STD_TIME = sec * (STD_END.tv_sec-STD_START.tv_sec) + STD_END.tv_usec - STD_START.tv_usec;
            printf("Run std in data %d : use %.2Lfus\n", i, STD_TIME);

            if(MAKER_TIME + STD_TIME < sec) system("sleep 1");
            for(int j = 1; j <= 10; j ++)
                puts("................");
            printf("Finish Make Data %d\n\n\n", i);
        }
        printf("Data %d to %d is finish\n", l, r);
        printf("please change maker.cpp and then type next l and r\n\n");
    }
    return 0;
}
```