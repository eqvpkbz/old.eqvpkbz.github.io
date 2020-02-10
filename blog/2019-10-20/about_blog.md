---
title: 博客搭建教程
description: 搭建个人博客全过程
create: 2019.10.20
modified: 2020.1.30
tags: Blog
top: 233
location: .
index: true
template: template
---

[TOC]

# 博客相关

博客是在[riteme大佬](https://riteme.site/)的博客生成器的基础上，加以添加功能的

然后发现有些部分还是要手动的觉得不太方便于是就用常用语言`C++`处理了一下，现在可以自动生成`index.md`和`posts.md`了

## 如何自己搭一个这样的博客

搭载平台: $Linux$

原作者项目地址: [here](https://github.com/riteme/riteme.github.io)

我的项目地址: [here](https://github.com/eqvpkbz/eqvpkbz.github.io)

### 配置环境

首先先安装最新的`python 3`$(>= 3.7)$

然后要用`pip3`安装下列东西:

```
Python Markdown (要求版本 == 2.6.11)
Pygments (用于提供代码高亮)
css-html-js-minify (压缩 HTML 源码)
Beautiful Soup 4
lxml / html5lib
```
安装的命令行
```bash
pip3 install Markdown==2.6.11 --user
pip3 install css-html-js-minify --user
pip3 install beautifulsoup4 --user
pip3 install Pygments --user
pip3 install html5lib --user
```
可以考虑安装lxml，因为原来的`riteme`是用的`lxml`，我用的是`html5lib`
```bash
sudo apt-get install libxml2-dev libxslt-dev
sudo apt-get install python3-lxml 
pip3 install lxml
```

### 拉取源码

```cpp
git clone https://github.com/eqvpkbz/eqvpkbz.github.io.git
```

然后把`.gitignore`文件去掉，新建一个github的仓库

### 个性化

`HTML`的模板在`templates/`下，请自行修改

然后还有`favicon.png`用来做`logo`

`search.html`也需要自己修改，因为有特定的标签所以生成时不会再生成

博客的文章在`blog/`里面

然后还有`index.md`,`posts.md`,`links.md`,`about.md`需要修改

`update.cpp`里面上传的方式可以按照情况更改，见[Here](https://zhuanlan.zhihu.com/p/34625448)

## 小操作

要写一篇新的文章:

```bash
python3 pagegen.py -n "file_name" -t
```

需要生成全站文章

```bash
python3 sitegen.py
```

生成`index.md`和`posts.md`

```bash
g++ maker.cpp -o maker
./maker
```

生成全站文章并推送到github上

```bash
g++ update.cpp -o update
./update
```