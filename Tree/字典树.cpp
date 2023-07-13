#include <algorithm>
#include <string.h>
#include <cstdio>

using namespace std;

const int MAXN = 1000 + 10;
const int maxnode = 100005;
const int sigma_size = 26;
char str[MAXN][25]; // 单词对应
int tot;  // 单词编号
int ch[maxnode][sigma_size];
char val[maxnode];  // 节点 v 的访问次数

struct Trie{
    int sz; // 节点编号
    Trie() { sz = 1; memset(ch[0], 0, sizeof ch[0]);}
    int idx(char c) {return c - 'a';}
    void insert(char s[]){
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; ++i){
            int c = idx(s[i]);
            if (!ch[u][c]){
                memset(ch[sz], 0, sizeof ch[sz]);
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            val[ch[u][c]]++;
        }
    }

    // 最短前缀
    void query(char s[]){
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++){
            putchar(s[i]);
            int c = idx(s[i]);
            if (val[ch[u][c]] == 1) return;
            u = ch[u][c];
        }
    }
};
