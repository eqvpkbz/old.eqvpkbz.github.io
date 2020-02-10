---
title: manjaro系统初探
description: manjaro系统安装及初始化全过程
create: 2020.1.29
modified: 2020.2.7
tags: Linux
location: .
top: 0
index: true
template: template
---

[TOC]

# manjaro系统初探

其实`manjaro`各方面都挺香的

我觉得可以吊打`ubuntu`

好的，接下来记录一下安装的过程

首先和`ubuntu`的刻录软件一样，用的是[rufus](https://rufus.ie/)

刻录好之后安装就行

### 更换国内源

```
sudo pacman -Syy
sudo pacman-mirrors -i -c China -m rank  #选清华源即可
sudo pacman -Syyu
```

添加`Arch`的国内源

```
sudo pacman -S vim
sudo vim /etc/pacman.conf
```

在文件末尾添加

```
[archlinuxcn]
SigLevel = Optional TrustedOnly
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
```
然后
```
sudo pacman -Syy && sudo pacman -S archlinuxcn-keyring
```

### 安装git

```
sudo pacman -S git
git config --global user.name "Eqvpkbz"
git config --global user.email "2581505024@qq.com"
```

### 安装zsh

```
sudo pacman -S zsh
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
```

### 输入法

```
sudo pacman -S yay fcitx-sogoupinyin fcitx-im fcitx-configtool
sudo pacman -S fcitx-skin-material yay
yay -S fcitx-qt4
```

设置中文输入法环境变量，编辑~/.xprofile文件，增加下面几行(如果文件不存在，则新建)

```
export GTK_IM_MODULE=fcitx
export QT_IM_MODULE=fcitx
export XMODIFIERS="@im=fcitx"
```

打开`fcitx配置`-`附加组件`, 取消选定`经典皮肤`

### 常用软件安装
```
sudo pacman -S screenfetch
sudo pacman -S deepin-picker deepin-screen-recorder deepin-screenshot deepin-system-monitor
sudo pacman -S gdb gcc make cmake clang nodejs npm maven
sudo pacman -S pycharm-professional visual-studio-code-bin
sudo pacman -S google-chrome unrar unzip p7zip
sudo pacman -S wps-office pencil gimp netease-cloud-music
sudo pacman -S aria2 filezilla albert net-tools
yay -S tree typora lemon-lime
```

### 安装中文字体
```
sudo pacman -S wqy-zenhei
sudo pacman -S wqy-bitmapfont
sudo pacman -S wqy-microhei
sudo pacman -S ttf-wps-fonts
sudo pacman -S adobe-source-han-sans-cn-fonts
sudo pacman -S adobe-source-han-serif-cn-fonts
```

### Skype

```
sudo pacman -S gnome-keyring
yay -S skype
```

然后登录skype的时候，输完密码会提示创建密钥环，此时不输任何密码，直接继续(不加密操作，可以让后面登录不用输密码)

值得一提的是`KDE Wallet`不能取消，不然每次网络密码要重输

### TIM

#### 安装TIM

```
sudo pacman -S gnome-settings-daemon
sudo  cp  /etc/xdg/autostart/org.gnome.SettingsDaemon.XSettings.desktop   ~/.config/autostart
yay -S deepin-wine-tim 
```
然后安装即可

#### 修改内置IE浏览器

因为`deepin-wine`内部似乎还打包了一个`ie浏览器`，但是什么内容都显示不出来

所以我们可以把`ie浏览器`改成系统的浏览器，比如`google-chrome`

1. 找到`iexplore.exe`的位置，一般在`/home/用户名/.deepinwine/Deepin-TIM/drive_c/Program Files/Internet Explorer/`，在此处打开终端

先备份

```
mv iexplore.exe iexplore.exe.backup
```

2. 找到自己正在用的浏览器的位置，创建软连接

```
ln -s $(which google-chrome-stable) iexplore.exe
```

### 个性化

`KDE`的`konsole`可以自定义终端背景

`Ubuntu`弱爆了!!!

[终端主题](https://github.com/fengT-T/Mikuconsole)