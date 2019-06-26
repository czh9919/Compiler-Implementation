#include<bits/stdc++.h>
using namespace std;

//状态转移图的构造
void getFail(char*P,int f[]){
    int m = strlen(P);
    f[0] = 0;
    f[1] = 0;
    for (int i = 1; i < m; i++)
    {
        int j = f[i];
        while (j&&P[i]!=P[j])
        {
            j = f[j];
        }
        f[i + 1] = P[i] == P[j] ? j + 1 : 0;
    }

}

void KMP(char* T,char *P,int f[]){
    int n = strlen(T);
    int m = strlen(P);
    getFail(P, f);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j&&P[j]!=T[i])
        {
            j = f[j];
        }
        if(P[j]==T[i])
            j++;
        if(j==m)
            printf("%d\n", i - m + 1);
    }

}


int main(int argc, char const *argv[])
{
    int f[100] = {0};
    KMP("abcacababacabc", "abacabc",f);
    return 0;
}
