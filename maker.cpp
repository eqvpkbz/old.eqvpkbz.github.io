#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<dirent.h>
#include<algorithm>
#include<vector>
#include<sstream>
using namespace std;
#define INF 2147483647

//-------------------------------------------------------------------------------------------------------------------------------

int LEN;
struct FE{bool md = 0;string files_name,Time,title,description,Top,url,YEAR,MONTH,DAY;int year = 0,month = 0,day = 0;};
bool cmp(FE A,FE B)
{
    if(A.Top != B.Top) return A.Top > B.Top;
    else if(A.Time != B.Time) return A.Time > B.Time;
    else return A.files_name > B.files_name;
}
bool cmp1(FE A,FE B)
{
    if(A.Time != B.Time) return A.Time > B.Time;
    else if(A.Top != B.Top) return A.Top > B.Top;
    else return A.files_name > B.files_name;
}
vector<FE> files;//file_name
string BASEPATH;

namespace GETDATE
{
    inline string convert(int num)
    {
        string str;
        stringstream s;
        s << num;
        s >> str;
        return str;
    }
    inline string DATE()
    {
        time_t tt;time(&tt);
        tt = tt + 8*3600;
        tm* t= gmtime(&tt);
        string DATE = "modified: " + convert(t->tm_year + 1900) + "." + convert(t->tm_mon + 1) + "." + convert(t->tm_mday);
        return DATE;
    }
}

//-------------------------------------------------------------------------------------------------------------------------------

namespace GETINFORMATION
{
    inline int check(string a)
    {
        int len = a.size(),i1 = len - 9,i2 = len - 3;
        if(i2 < 0) return 0;
        if(a[i2] == '.')
        {
            int i = i2;
            if(a[i + 1] == 'm' && a[i + 2] == 'd') return 1;
        }
        if(i1 < 0) return 0;
        if(a[i1] == '.')
        {
            int i = i1;
            if(a[i + 1] == 'm' && a[i + 2] == 'a' && a[i + 3] == 'r' && a[i + 4] == 'k'
            && a[i + 5] == 'd' && a[i + 6] == 'o' && a[i + 7] == 'w' && a[i + 8] == 'n') return 2;
        }
        return 0;
    }
    inline void getinformation(string way,string File_name,int kind)
    {
        FE ans;
        if(kind == 2) ans.md = 1;
        ans.files_name = File_name;
        freopen(way.data(),"r",stdin);
        int times = 0;
        while(times < 2)
        {
            string a;cin >> a;
            if(a[1] == '-') times ++;
            if(a.find("description:") != a.npos) getchar(),getline(cin,ans.description);
            else if(a.find("title:") != a.npos) getchar(),getline(cin,ans.title);
            else if(a.find("top:") != a.npos) getchar(),getline(cin,ans.Top);
            else if(a.find("modified:") != a.npos)
            {
                getchar();string relay;getline(cin,relay);int x = 0,len = relay.length();
                while(x < len){if(relay[x] < 48 || relay[x] > 57) x ++;else break;}
                while(x < len){if(relay[x] >= 48 && relay[x] <= 57) ans.year = ans.year * 10 + relay[x] - 48,ans.YEAR += relay[x],x ++;else break;}
                while(x < len){if(relay[x] < 48 || relay[x] > 57) x ++;else break;}
                while(x < len){if(relay[x] >= 48 && relay[x] <= 57) ans.month = ans.month * 10 + relay[x] - 48,ans.MONTH += relay[x],x ++;else break;}
                while(x < len){if(relay[x] < 48 || relay[x] > 57) x ++;else break;}
                while(x < len){if(relay[x] >= 48 && relay[x] <= 57) ans.day = ans.day * 10 + relay[x] - 48,ans.DAY += relay[x],x ++;else break;}
                if(ans.month < 10)
                {
                    if(ans.day < 10) relay.insert(relay.end() - 3,'0'),relay.insert(relay.end() - 1,'0');
                    else relay.insert(relay.end() - 4,'0');
                }
                else if(ans.day < 10) relay.insert(relay.end() - 1,'0');
                ans.Time = relay;
            }
        }
        fclose(stdin);
        way.erase(0,LEN);
        if(ans.md) ans.files_name.erase(ans.files_name.end() - 8,ans.files_name.end()),way.erase(way.end() - 8,way.end());
        else ans.files_name.erase(ans.files_name.end() - 2,ans.files_name.end()),way.erase(way.end() - 2,way.end());
        if(!ans.description.length()) ans.description = "懒得描述了QAQ,请直接看文章";
        ans.url = way + "html",files.push_back(ans);
        return ;
    }
    void getFiles(string cate_dir)
    {
        DIR *dir;
        struct dirent *ptr;
        char base[1000];
        if ((dir=opendir(cate_dir.c_str())) == NULL){perror("Open dir error...");exit(1);}
        while ((ptr=readdir(dir)) != NULL)
        {
            if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir
                continue;
            else if(ptr->d_type == 8)
            {
                string temp = ptr->d_name;
                string file_way = cate_dir + "/" + temp;
                int len = cate_dir.length(),result = check(temp);
                if(result == 1) getinformation(file_way,temp,1);
                else if(result == 2) getinformation(file_way,temp,2);
            }
            else if(ptr->d_type == 10) continue;
            else if(ptr->d_type == 4)    ///dir
            {
                string a = ptr->d_name;
                getFiles(cate_dir + "/" + a);
            }
        }
        closedir(dir);
        return ;
    }
};

//-------------------------------------------------------------------------------------------------------------------------------

namespace INDEX
{
    const int DEFAULT_NUMBER=10;
    inline void generate_index(string title,string description,string file_url)
    {
        string SHELL = "echo -n `cat " + BASEPATH + "/index_confirm/first.txt` >> index.md";system(SHELL.data());
        SHELL = "echo -n \"" + title + "\" >> index.md";system(SHELL.data());
        SHELL = "echo -n `cat " + BASEPATH + "/index_confirm/Mid_f.txt` >> index.md";system(SHELL.data());
        SHELL = "echo -n \"" + description + "\" >> index.md";system(SHELL.data());
        SHELL = "echo -n `cat " + BASEPATH + "/index_confirm/Mid_t.txt` >> index.md";system(SHELL.data());
        SHELL = "echo -n \"" + file_url + "\" >> index.md";system(SHELL.data());
        SHELL = "cat " + BASEPATH + "/index_confirm/last.txt >> index.md";system(SHELL.data());
        return ;
    }
    inline void make_index()
    {
        sort(files.begin(), files.end(), cmp);
        puts("(info) Generating index...");
        string SHELL = "cp " + BASEPATH + "/index_confirm/head.txt -f index.md";system(SHELL.data());
        SHELL = "echo " + GETDATE::DATE() + " >> index.md";system(SHELL.data());
        SHELL = "cat " + BASEPATH + "/index_confirm/tail.txt >> index.md";system(SHELL.data());
        int SIZE = files.size();
        int Min = min(DEFAULT_NUMBER,SIZE);
        for(int i = 0;i < Min;i ++)
            generate_index(files[i].title,files[i].description,files[i].url);
        SHELL = "cat " + BASEPATH + "/index_confirm/finally.txt >> index.md";system(SHELL.data());
        puts("(info) Already make index!");
        return ;
    }
};

//-------------------------------------------------------------------------------------------------------------------------------

namespace POSTS
{
    #define MAXY 999999
    #define MAXM 15
    bool Mark[MAXY][MAXM];
    inline void generate_posts(string title,string description,string file_url,int num)
    {
        if(!Mark[files[num].year][0]){string Shell = "echo \"### " + files[num].YEAR + "\" >> posts.md";system(Shell.data());Mark[files[num].year][0] = 1;}
        if(!Mark[files[num].year][files[num].month])
        {
            string Shell = "echo \"#### " + files[num].YEAR + "-" + files[num].MONTH + "\" >> posts.md";
            system(Shell.data());Mark[files[num].year][files[num].month] = 1;
        }
        string line = "* [" + title + "](" + file_url + "): " + description;
        string SHELL = "echo \"" + line + "\" >> posts.md";
        system(SHELL.data());
        return ;
    }
    inline void make_posts()
    {
        sort(files.begin(),files.end(),cmp1),puts("(info) Generating posts...");
        string SHELL = "cp " + BASEPATH + "/posts_confirm/head.txt -f posts.md";system(SHELL.data());
        SHELL = "echo " + GETDATE::DATE() + " >> posts.md";system(SHELL.data());
        SHELL = "cat " + BASEPATH + "/posts_confirm/tail.txt >> posts.md";system(SHELL.data());
        for(int i = 0;i < files.size();i ++)
            generate_posts(files[i].title,files[i].description,files[i].url,i);
        puts("(info) Already make posts!");
        return ;
    }
};

//-------------------------------------------------------------------------------------------------------------------------------

namespace WORK
{
    inline void work()
    {
        DIR *dir;char basePath[100];memset(basePath, '\0', sizeof(basePath));
        getcwd(basePath, 999);
        LEN = strlen(basePath);
        BASEPATH = basePath;
        string DEAFULT_PATH = basePath;
        DEAFULT_PATH += "/blog";
        GETINFORMATION::getFiles(DEAFULT_PATH);
        INDEX::make_index(),POSTS::make_posts();
        return ;
    }
};

//-------------------------------------------------------------------------------------------------------------------------------

int main()
{
    WORK::work();
    return 0;
}

