#include <vector>
#include <queue>
#include <string>
#include <iostream>

using namespace std;

#define MAXSIZE 26

typedef struct _ACNode
{
    _ACNode* fail;
    _ACNode* children[MAXSIZE];
    vector<int> exist;
    _ACNode() : fail(NULL), children{nullptr} {}
}node;

void build(node* root, vector<string> p);
void insert(node* root, const string& c);
void query(node* root, string s);
void print(const string s, int b, int e) {
    cout << b << "  ";
    for (int i = b; i < e; ++i) cout << s[i];
    cout << endl;
}

int main() {
    node* root = new node();

    build(root, { "hi", "she", "he" });
    query(root, "abshdbsiaoushebashidxzbuisadhesa");
}


void build(node* root, vector<string> p) {
    for (int i = 0; i < p.size(); ++i) {
        insert(root, p[i]);
    }

    queue<node*> q;
    // 初始化root的儿子，使其fail指向root
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            q.push(root->children[i]);
            root->children[i]->fail = root;
        }
    }

    // 层序遍历
    while (!q.empty()) {
        node *tnode = q.front();
        q.pop();
        for (int i = 0; i < MAXSIZE; i++) {
            if (tnode->children[i] != nullptr) {
                q.push(tnode->children[i]);
                node* ttnode = tnode->children[i]; // 子节点
                node* fafail = tnode->fail;     // 当前节点的fail节点
                while (fafail && fafail->children[i] == nullptr) {
                    fafail = fafail->fail;
                }
                // 如果是fail为空退出，则指向root，否侧fafail的孩子存在，fail指向它
                ttnode->fail = fafail ? fafail->children[i] : root;
                // 将对方exist数组添加到自己
                if (ttnode->fail->exist.size()) {
                    for (auto i : ttnode->fail->exist) {
                        ttnode->exist.push_back(i);
                    }
                }
            }
        }
    }
}

void query(node* root, string s) {
    node* tmp = root;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a'; // 获取字符下标
        while (tmp->children[c] == nullptr && tmp->fail) tmp = tmp->fail;
        if (tmp->children[c]) tmp = tmp->children[c]; // 找到了，则移动到孩子
        else continue;  // 否则 tmp 为root，直接进行下一轮查找
        // 当前节点是否存在单词
        if (tmp->exist.size()) {
            for (auto j : tmp->exist) {
                print(s, i - j + 1, i + 1);
            }
        }
    }
}

void insert(node* root, const string& c) {
    node* tmp = root;
    for (int i = 0, n = c.size(); i < n; ++i) {
        int index = c.at(i) - 'a';
        if (tmp->children[index] == nullptr) {
            tmp->children[index] = new node();
        }
        tmp = tmp->children[index];
    }
    tmp->exist.push_back(c.size());
}
