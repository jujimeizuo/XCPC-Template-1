﻿//查包含在x1,y1,x2,y2为左下角和右上角的矩形里面权值之和
//K-D Tree 二维划分树
int N, ans, rt, WD, tot, top, rub[MAX];

struct node {
    int x[2], w;
} p[MAX];

struct K_D_tree {
    int ls, rs, siz, mn[2], mx[2], sum;
    //mn[0], mx[0] -> x的取值范围
    //mn[1], mx[1] -> y的取值范围
    node tmp;
} t[MAX];

int operator < (const node &a, const node &b) { return a.x[WD] < b.x[WD]; }

int newnode() {
    if (top) return rub[top--];
    else return ++tot;
}

void push_up(int u) {
    for (int i = 0; i <= 1; i++) {//更新x, y的取值范围
        t[u].mn[i] = t[u].mx[i] = t[u].tmp.x[i];
        if (lc) {//左子树的最大最小值
            t[u].mn[i] = min(t[u].mn[i], t[lc].mn[i]);
            t[u].mx[i] = max(t[u].mx[i], t[lc].mx[i]);
        }
        if (rc) {//右子树的最大最小值
            t[u].mn[i] = min(t[u].mn[i], t[rc].mn[i]);
            t[u].mx[i] = max(t[u].mx[i], t[rc].mx[i]);
        }
    }
    t[u].sum = t[lc].sum + t[rc].sum + t[u].tmp.w;
    t[u].siz = t[lc].siz + t[rc].siz + 1;
}

int build(int l, int r, int wd) {
    if (l > r) return 0;
    int u = newnode();
    WD = wd; nth_element(p + l, p + m, p + r + 1);
    t[u].tmp = p[m];
    t[u].ls = build(l, m - 1, wd ^ 1);
    t[u].rs = build(m + 1, r, wd ^ 1);
    push_up(u);
    return u;
}

void pia(int u, int num) {//拍扁回炉重做
    if (lc) pia(lc, num);
    p[t[lc].siz + num + 1] = t[u].tmp, rub[++top] = u;
    if (rc) pia(rc, t[lc].siz + num + 1);
}

void check(int &u, int wd) {//检查是否平衡，不平衡则需要重建
    if (t[u].siz * alpha < t[lc].siz || t[u].siz * alpha < t[rc].siz) pia(u, 0), u = build(1, t[u].siz, wd);
}

void insert(int &u, node tp, int wd) {//插入点
    if (!u) {
        u = newnode();
        lc = rc = 0, t[u].tmp = tp;
        push_up(u);
        return;
    }
    if (tp.x[wd] < t[u].tmp.x[wd]) insert(lc, tp, wd ^ 1);
    else insert(rc, tp, wd ^ 1);
    push_up(u);
    check(u, wd);
}

bool in(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {//完全被包含
    return (x1 <= X1 && X2 <= x2 && y1 <= Y1 && Y2 <= y2);
}

bool out(int x1, int y1, int x2, int y2, int X1, int Y1, int X2, int Y2) {//完全无交集
    return (x1 > X2 || x2 < X1 || y1 > Y2 || y2 < Y1);
}

int query(int u, int x1, int y1, int x2, int y2) {
    if (!u) return 0;
    int res = 0;
    if (in(x1, y1, x2, y2, t[u].mn[0], t[u].mn[1], t[u].mx[0], t[u].mx[1])) return t[u].sum;
    if (out(x1, y1, x2, y2, t[u].mn[0], t[u].mn[1], t[u].mx[0], t[u].mx[1])) return 0;
    if (in(x1, y1, x2, y2, t[u].tmp.x[0], t[u].tmp.x[1], t[u].tmp.x[0], t[u].tmp.x[1])) res += t[u].tmp.w;
    res += query(lc, x1, y1, x2, y2) + query(rc, x1, y1, x2, y2);
    return res;
}

void init() {
    ans = rt = top = tot = 0;
}

int main() {

    init();
    scanf("%d", &N);
    while (1) {
        int op; scanf("%d", &op);
        if (op == 3) break;
        if (op == 2) {
            int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            printf("%d\n", ans = query(rt, x1 ^ ans, y1 ^ ans, x2 ^ ans, y2 ^ ans));
        }
        else {
            int x, y, w; scanf("%d%d%d", &x, &y, &w);
            insert(rt, node{x ^ ans, y ^ ans, w ^ ans}, 0);
        }
    }


    return 0;
}