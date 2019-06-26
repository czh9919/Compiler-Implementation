#include <bits/stdc++.h>
using namespace std;
#define maxnode 100
#define sigma_size 26
struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode]; //表示是否中间结点
    int sz;
    Trie()
    {
        sz = 1; //结点总数
        memset(ch[0], 0, sizeof(ch[0]));
    }
    int idx(char c)
    {
        return c - 'a';
    }

    //插入字符串s，附加信息为v。注意v必须为非0，因为0代表“本结点不是单词结点”
    void insert(char *s, int v)
    {
        int u = 0;
        int n = strlen(s);
        for (int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if (!ch[u][c])
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    //查找字符串s，附加信息为v
    int search(char *s, int v)
    {
        int u = 0;
        int n = strlen(s);
        int flag = 1;
        for (int i = 0; i < n - 1; i++)
        {
            int c = idx(s[i]);
            if (ch[u][c] == 0 || val[ch[u][c]] != 0)
            {
                flag = 0;
                return 0;
            }
            u = ch[u][c];
        }
        if (val[n] == v && flag)
        {
            return 1;
        }
        return 0;
    }
};
int main(int argc, char const *argv[])
{
    Trie T;
    char *string = "hello";
    T.insert(string, 1);
    cout << T.search(string, 1);
    return 0;
}
