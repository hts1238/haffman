#include <bits/stdc++.h>

using namespace std;

struct Damb {
    char ch;
    int n;
    int tri;
};

struct Tree {
    char ch = -1;
    int left = -1;
    int right = -1;
    int parent = -1;
};

struct Code {
    int code = 0;
    int length = 0;
};

FILE* inf;
FILE* outf;

char ch;
int numc[256];

int main() {
    inf = fopen("input.txt", "rb");
    outf = fopen("output.txt", "wb");

    while (fscanf(inf, "%c", &ch) != -1) {
        ++numc[ch];
    }
    numc[0] = 1;

    Damb damb[256];
    Tree tree[512];
    int l = 0;
    for (int i = 0; i < 256; ++i) {
        if (numc[i] > 0) {
            damb[l].ch = i;
            damb[l].n = numc[i];
            damb[l].tri = l;
            tree[l].ch = i;
            ++l;
        }
    }

    /*for (int i = 0; i < l; ++i) {
        //fprintf(outf, "%d: %d %d %d\n", i, damb[i].ch, damb[i].n, damb[i].tri);
    }*/

    int curl = l;
    int curi = l;
    for (int i = 0; i < l - 1; ++i) {
        Damb min1 = damb[0], min2 = damb[1];
        int i1 = 0, i2 = 1;
        if (min1.n > min2.n) {
            swap(min2, min1);
            swap(i1, i2);
        }
        for (int j = 2; j < curl; ++j) {
            if (damb[j].n < min1.n) {
                min2 = min1;
                i2 = i1;
                min1 = damb[j];
                i1 = j;
            }
            else if (damb[j].n < min2.n) {
                min2 = damb[j];
                i2 = j;
            }
        }
        //fprintf(outf, "\n");
        //fprintf(outf, "%d %d (%d, %d)\n", min1.ch, min1.n, min1.tri, i1);
        //fprintf(outf, "%d %d (%d, %d)\n\n", min2.ch, min2.n, min2.tri, i2);

        tree[curi].ch = -1;
        tree[curi].left = min1.tri;
        tree[curi].right = min2.tri;

        tree[min1.tri].parent = curi;
        tree[min2.tri].parent = curi;

        damb[i1].ch = -1;
        damb[i1].n = min1.n + min2.n;
        damb[i1].tri = curi;
        swap(damb[i2], damb[curl-1]);
        --curl;
        ++curi;

        /*for (int i = 0; i < curl; ++i) {
            //fprintf(outf, "%d: %d %d %d\n", i, damb[i].ch, damb[i].n, damb[i].tri);
        }
        //fprintf(outf, "\n");
        for (int i = 0; i < curi; ++i) {
            //fprintf(outf, "%d: %d %d %d %d\n", i, tree[i].ch, tree[i].left, tree[i].right, tree[i].parent);
        }*/
    }
    //fprintf(outf, "__________________________\n\n");

    Code code[256];
    for (int i = 0; i < l; ++i) {
        int c1 = 0, c2 = 0, len = 0;
        int p = tree[i].parent;
        int cur = i;
        while (p != -1) {
            c1 <<= 1;
            if (tree[p].right == cur) {
                ++c1;
            }
            else {
            }
            ++len;

            cur = p;
            p = tree[p].parent;
        }
        /*for (int j = 0; j < len; ++j) {
            c2 <<= 1;
            c2 += c1%2;
            c1 >>= 1;
        }*/ c2 = c1;
        code[tree[i].ch].code = c2;
        code[tree[i].ch].length = len;
        //fprintf(outf, "%d: %d %d\n", tree[i].ch, c2, len);
    }
    //fprintf(outf, "_______________________________\n\n");

    unsigned char a = curi;
    fwrite(&a, sizeof(char), 1, outf);
    for (int i = 0; i < curi; ++i) {
        unsigned char a1 = tree[i].ch;
        unsigned char a2 = tree[i].left;
        unsigned char a3 = tree[i].right;
        unsigned char a4 = tree[i].parent;

        fwrite(&a1, sizeof(char), 1, outf);
        fwrite(&a2, sizeof(char), 1, outf);
        fwrite(&a3, sizeof(char), 1, outf);
        fwrite(&a4, sizeof(char), 1, outf);
    }

    fclose(inf);
    inf = fopen("input.txt", "rb");

    a = 0;
    int k = 0;
    while (fscanf(inf, "%c", &ch) != -1) {
        int c = code[ch].code;
        int l = code[ch].length;

        for (int i = 0; i < l; ++i) {
            a <<= 1;
            a += c%2;
            c >>= 1;
            ++k;
            if (k == 8) {
                fwrite(&a, sizeof(char), 1, outf);
                k = 0;
            }
        }
    }
    int c = code[0].code;
    int ll = code[0].length;

    for (int i = 0; i < ll; ++i) {
        a <<= 1;
        a += c%2;
        c >>= 1;
        ++k;
        if (k == 8) {
            fwrite(&a, sizeof(char), 1, outf);
            k = 0;
        }
    }
    if (k > 0) {
        a <<= 8 - k;
        fwrite(&a, sizeof(char), 1, outf);
    }
    
    fclose(inf);
    fclose(outf);

    return 0;
}
