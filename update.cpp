/*
 Update Site & Git Push Helper
 Written By Eqvpkbz
 */

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
using namespace std;
inline bool check()
{
    char c = getchar();
    if(c == 'Y' || c == 'y') return true;
    else return false;
}
int main()
{
    printf("Need generate this site?(Y/N): ");
    if(check()){system("g++ maker.cpp -o maker && ./maker");system("python3 sitegen.py");puts("Done.\n\n");}
    else puts("Skipped!");
    system("git add .");
    string s = "git commit -m \"Blog Update\"";
    system(s.data());
    system("git pull origin master");
    system("git push -u origin master");
    return 0;
}
