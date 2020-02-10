#include<iostream>
#include<ctime>
#include<cstdio>

using namespace std;

int main() 
{

    time_t tt;time(&tt);
    tt = tt + 8*3600;
    tm* t= gmtime(&tt);
    printf("%d-%02d-%02d %02d:%02d:%02d\n",t->tm_year + 1900,t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

    return 0;
}
