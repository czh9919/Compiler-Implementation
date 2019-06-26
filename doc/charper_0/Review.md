# Review data structures and algorithms

## Trie

若存在一个字符串集合为$\{a,to,tea,ted,ten,i,in,inn\}$,每个单词的结束位置对应一个“单词节点”。反过来，从根节点到每个单词节点的路径上所有字母链接而成的字符串就是该节点所对应的字符串。在程序上，将根节点编号为0， 然后把其他结点编号为从1开始的正整数，然后用一个数组来保存每个结点的所有子节点，然后用下标直接存取。

具体来说，可以用ch[i][j]保存结点i的那个编号为结点子节点。什么叫“编号为j”呢？比如， 若是处理全部由小写字母组成的字符串，把所有小写字母按照字典序编号为0，1，2……，则ch[i][0]表示结点i的子节点a。如果这个子节点不存在，，则ch[i][0]=0。用sigma_size表示字符集的大小，比如，当字符集为全体小写字母时，sigma_size=26。

使用Trie的时候，往往需要在单词结点的上附加信息，其中val[i]表示结点i所对应的附加信息。例如，如果每个字符串有一个权值，就可以把这个权值保存在val[i]中。。简单起见，下面代码中假定权值大于0，因此val[i]>0,因此val[i]>0当前仅当结点i是单词结点。

Trie的定义和插入代码如下。

```cpp
//字母表为全体小写字母的Trie
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
```

## KMP算法

假设文本是一个长度为n的字符串T，模板是一个长度为m的字符串P，且m<=n.需要求出模板在文本中的所有匹配点i. 即满足T[i]=P[0], T[i+1]=P[1],...,T[m-1]=P[m-1]的非负整数i(注意字符串下标从0开始)

假定在匹配过程中发现不同，则成为**失配**，正常的暴力算法（朴素算法）会把模板串右移一位，然后重新匹配。

KMP算法则认为，如果某个位置已经比较过一次了，就不应该再比较一次了。考虑一个例子：

    P:abcab
    T:abcacababcab

我们发现前四位匹配成功了，但第5位适配了，而这时，我们选择将P往右移三位，这就是KMP算法的精髓。也就是失配函数的写法。

```cpp
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

void KMP(char* T,char *P,int *f){
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
```

## AC自动机

在模式匹配问题中，如果模板串有多个，我们就得把所有模板建成一个大的状态转移图(AC自动机)，由Trie和失配边组成。

```cpp
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
```
