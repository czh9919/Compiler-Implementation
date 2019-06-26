#include <bits/stdc++.h>
using namespace std;
#define maxn 100
#define SIGMA_SIZE 26
int val[maxn];
int last[maxn];
int ch[maxn][SIGMA_SIZE];
int f[maxn];
int idx(char c)
{
    return c - 'a';
}
void print(int j)
{
    if(j)
    {
        printf("%d:%d\n", j, val[j]);
        print(last[j]);
    }
}
void find(char *T)
{
    int n = strlen(T);
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        int c = idx(T[i]);
        while (j && !ch[j][c])
        {
            j = f[j];
        }
        j = ch[j][c];
        if (val[j])
        {
            print(j);
        }
        else if (last[j])
        {
            print(last[j]);
        }

    }
}
void getFail()
{
    queue<int> q;
    f[0] = 0;
    //初始化队列
    for (int c = 0; c < SIGMA_SIZE; c++)
    {
        int u = ch[0][c];
        if (u)
        {
            f[u] = 0;
            q.push(u);
            last[u] = 0;
        }
        while (!q.empty())
        {
            int r = q.front();
            q.pop();
            for (int c = 0; c < SIGMA_SIZE;c++)
            {
                int u = ch[u][c];
                if(!u)
                {
                    continue;
                }
                q.push(u);
                int v = f[r];
                while (v&&!ch[v][c])
                {
                    v = f[v];
                }
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }

    }

}
int main(int argc, char const *argv[])
{

    return 0;
}
