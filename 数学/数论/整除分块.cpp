
int calc(int n, int m) {
    //\sum_{i = 1} ^ {m} n / i
    //����ȡ��
    for (int l = 1, r; l <= m; l = r + 1) {
        if (n / l) r = min(m, n / (n / l));
        else r = m;
        //[l, r]֮��� n / l �����
    }

    //����ȡ��
    for (int l = 1, r; l <= m; l = r + 1) {
        int t = (n + l - 1) / l;
        if (t == 1) r = m;
        else r = min(m, (n - 1) / (t - 1));
        //[l, r]֮��� (n + l - 1) / l �����
    }

}

