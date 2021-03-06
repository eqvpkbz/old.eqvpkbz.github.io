from libs.utility import *

# For sitegen.py
UPDATE_MAP_FILE = "map.json"
DATABASE_LOCATION = "content.json"
TIPUESEARCH_DATABASE_LOCATION = "scripts/tipuesearch_content.js"
SITEMAP_LOCATION = "sitemap.txt"
TEMPLATES_FOLDER = "templates/"
BLOG_FOLDER = "blog/"
SITE_DOMAIN = "https://eqvpkbz.github.io/"

# For pagegen.py
WORDS_PER_MINUTE = 250
BEAUTIFUL_SOUP_PARSER = "lxml"
GITHUB_LOCATION = "https://github.com/eqvpkbz/eqvpkbz.github.io/blob/master"
SITE_DOMAIN = "https://eqvpkbz.github.io/"
DEFAULT_TEMPLATE = "template"
DEFAULT_TOP = "0"

#For template
STAT_TEMPLATE = "{word} 字 / 约 {time}"

# For metainfo
# 如果默认值在这里设置为 None，则表示该参数在文档中不能缺省
METAINFO_DEFAULTS = {
    "title": None,  # 文章标题
    "description": "",  # 文章简单摘要
    "create": today(),  # 创建日期
    "modified": today(),  # 修改日期
    "tags": ["No Tag"],  # 文章标签
    "location": ".",  # HTML 存放位置。"." 表示和 Markdown 文件同目录
    "top": DEFAULT_TOP, # 文章置顶程度
    "index": True,  # 表示是否加入搜索索引
    "template": DEFAULT_TEMPLATE  # 页面模板
}

# "#" 开头的项目会调用同名的函数来获得扩展
MARKDOWN_EXTENSIONS = [
    "markdown.extensions.fenced_code",
    "markdown.extensions.footnotes",
    "markdown.extensions.tables",
    "markdown.extensions.codehilite",
    "markdown.extensions.toc",
    "markdown.extensions.smart_strong",
    "markdown.extensions.nl2br",
    "markdown.extensions.meta",
    "markdown.extensions.smarty",
    "markdown.extensions.attr_list",
    "#latex_friendly",
    #"#new_tab_on_links",
    "#tasklist",
    "#del_ins"
]

MARKDOWN_CONFIG = {
    "markdown.extensions.codehilite": {
        "linenums": True,
        "guess_lang": False
    }
}
