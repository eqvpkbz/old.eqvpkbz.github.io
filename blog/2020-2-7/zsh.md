---
title: zsh插件推荐
description: zsh的一些提高生产力的插件
create: 2020.2.7
modified: 2020.2.7
tags: No Tag
location: .
top: 0
index: true
template: template
---

[TOC]

# zsh插件推荐

自带可开启: `history`, `extract`, `web-search`

### autojump
```
git clone git://github.com/joelthelion/autojump.git
cd /autojump
./install.py
vim ~/.zshrc
```
把以下代码加到尾部
```
[[ -s ~/.autojump/etc/profile.d/autojump.sh ]] && . ~/.autojump/etc/profile.d/autojump.sh
```

### zsh-autosuggestion
```
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
```

### zsh-syntax-highlighting
```
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
```

### 开启插件

打开`~/.zshrc`

找到`plugins`

改为

```
plugins=(
	git
	history
	extract
	web-search
	zsh-autosuggestions
	zsh-syntax-highlighting
)
```

即可