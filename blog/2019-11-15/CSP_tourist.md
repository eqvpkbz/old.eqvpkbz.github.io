---
title: CSP2019游记
description: 被省三劝退役了
create: 2019.11.15
modified: 2019.11.18
tags: tourist
location: .
top: 1
index: true
template: template
---

[TOC]

# CSP2019游记

## Day -1

去试机了，键盘是附中大机房一毛一样的键盘，而且还要更加顺滑一些

手打了一个`zkw + dijkstra`然后就被李总赶走了

模板没打完，我要完了

## Day 0

![](https://s2.ax1x.com/2019/11/15/MUyUv8.png)

在学校里面打模板

发现好几道题目都是没开`long long`或者没有取模导致样例都不过

感觉状态其实也没有自己想的那么好

### Day 1

心态可能有点超级爆炸吧

#### T1

可能出题人还是照顾了一下考生吧?

$n \leqslant 64$

拿到T1看到数据范围就知道要开`unsigned long long`，`HNOI2018D1T1`的教训还是记得的(~~因为没开unsigned long long丢了10分~~)

然后看完题就知道了$O(n)$的做法，还算是一道简单的签到题吧

所以我开了`unsigned long long`写左移为什么被提醒超出`type's width`？？？

其实是因为`(1 << n)`的时候`1`是作为`int`值来进行运算的

然后我用快速幂为什么得出结果都是`0`直到算$n = 32$才好???

~~这是怎么溢出的啊`QAQ`，明明全程开的`unsigned long long`~~

下考之后想起可能是函数返回值用的`int`?

然后心态炸裂了,就直接莽了高精度

最后看到源代码`140`行，当场就觉得`T1`考这样是怎么说???

最后用掉了`1h`，起身上厕所去，然后用了`5 min`(有麓山的在上厕所不能进去)

**UPD on Day2: Day1T1似乎高精乘写挂了**

#### T2

一开始的时候看到了子串，所以以为是从叶节点到根节点的括号串，所以就有多个括号串

用了一个栈维护一下，然后树上操作就好了

写完发现自己错了，然后将`(())`与`()`的情况分开讨论了一下，发现微调还是可以做的

然后就统计了一下`(())`单个嵌套的次数，并且按照一个括号串来处理

最后发现自己没有考虑括号串连续不连续的问题，改了一下，更新了之前的文件交了上去

然后考试结束前`30min`发现题意理解错了，怪不得对拍怎么都不出问题，样例怎么都过不去

所以就发现实际上是一个前缀，然后认为前缀就可以直接维护一个`dp`在线操作就好

结果就成功的爆零了，稍微微调了一下发现可以过小样例，所以就直接交了

提交时间: `2019.11.16 11:59:51`,现在想想还是有点后怕

#### T3

不会，上来直接莽一个暴力，就是枚举每一条边的顺序

链和菊花图的部分分没想，不过其实应该是可做的

但是我发现暴力都是错的啊$!!!!!$然后我心态就真的炸了

最后发现暴力里面交换之后还是不对，必须要再维护一个值来进行交换

所以改了一手，测试样例发现: 原先对的部分错了，原先错的部分对了

我真的自闭了啊啊啊啊啊啊

然后就去一直刚`T2`了，我第一次觉得自己可以被`T1`玩得这么没心态

后面下了考场之后似乎可以考虑在某个部分分下思考贪心就做得出来

人都给它整自闭了

#### 后记

下午还觉得自己`T1`还算比较稳的，应该能过吧

然后晚饭过后有一个朋友过来跟我讲我`Day1`怎么爆零了(对话如下)


```
B: 您今天是怎么考的啊
A: 没打好吧，可能Day1真就爆零了，被T1搞自闭了
B: 那要是我的话就不止是自闭了
A: 您怎么知道我成绩的？您测了我代码？
B: 是的，本来没打算说的
A: 那我真自闭了
B: 原来你还没有自测啊
B: 我错了，我真的错了
```

于是乎，我晚上在家里哭了两场，要不是有家父安抚还有自己的心态还算可以的话，第二天可能就在考场上直接哭了吧

### Day 2

~~翻盘可能失败，因为不知道盘是什么样子~~

![](https://s2.ax1x.com/2019/11/17/Mrltdx.png)

#### T1

看起来像是昨天下考之后看的悬线法`dp`?

不会，打个暴力找找规律，发现在`a[i][j] < 2`的时候爆搜比较好做？

其实可以直接把`a[i][j]`变成多个菜品就好？

然后敲了暴力之后觉得`T2`更可做，做`T2`去了

#### T2

`dp`

随便敲敲找出$O(n ^ 3)$的$dp$转移式

一开始的时候以为贪心就能过，然后调了`30min`，然后发现不能做，就直接上了`dp`

然后似乎可以套两层优化到一个比较好的复杂度？

#### T3

似乎可以针对每个点来思考对于这个点来说有多少条边可以在删除之后使得这个点成为这个子树的重心

然后想了想，似乎是可以线性转移的？

但是没时间了，心态就很爆炸了

### CSP后记

今年考得的确超出了大部分人的预期了吧

回家之后又哭了一场，真是心态不好

回到机房之后高二学长都安慰说还有一年

但是还是很可惜啊，不然就可以有`250+`了

现在当务之急的还是要把文化课补上来

~~其实他们也没学多少东西的说~~