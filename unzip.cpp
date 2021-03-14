#include <bits/stdc++.h>

using namespace std;

struct Tree {
    char ch = -1;
    int left = -1;
    int right = -1;
    int parent = -1;
};

FILE* inf;
FILE* outf;

int main() {
    inf = fopen("output.txt", "rb");
    outf = fopen("res.txt", "wb");

    char n;
    fscanf(inf, "%c", &n);

    Tree tree[512];
    for (int i = 0; i < n; ++i) {
        char ch, left, right, parent;
        fscanf(inf, "%c%c%c%c", &ch, &left, &right, &parent);

        tree[i].ch = ch;
        tree[i].left = left;
        tree[i].right = right;
        tree[i].parent = parent;
    }

    unsigned char a;
    int cur = n - 1;
    while (fscanf(inf, "%c", &a) != -1) {
        for (int i = 7; i >= 0; --i) {
            if ((a >> i)%2 == 1) {
                cur = tree[cur].right;
            }
            else {
                cur = tree[cur].left;
            }
            if (tree[cur].ch != -1) {
                if (tree[cur].ch == 0) {
                    break;
                }
                fprintf(outf, "%c", tree[cur].ch);
                cur = n - 1;
            }
        }
    }
    
    fclose(inf);
    fclose(outf);

    return 0;
}
