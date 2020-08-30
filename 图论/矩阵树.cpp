//��������������
//����\sum_{Tree} \prod_{e �� Tree} num(e)

ll gauss(int n, ll K[][N]) {//�����K��n-1��˳������ʽ
    ll res = 1;
    for (int i = 1; i <= n - 1; i++) {//ö�����Խ����ϵ�i��Ԫ��
        for (int j = i + 1; j <= n - 1; j++) {//ö��ʣ�µ���
            while (K[j][i]) {//շת���
                int t = K[i][i] / K[j][i];
                for (int k = i; k <= n - 1; k++)//תΪ������
                    K[i][k] = (K[i][k] - t * K[j][k] + mod) % mod;
                swap(K[i], K[j]);//����i��j����
                res = -res;//ȡ��
            }
        }
        res = (res * K[i][i]) % mod;
    }
    return (res + mod) % mod;
}

int n, m;
int K[N][N];

int main() {

    for (int i = 1; i <= m; i++) {
        int u, v; ll w; scanf("%d%d%lld", &u, &v, &w);
        K[u][u]++, K[v][v]++, K[u][v]--, K[v][u]--;
    }

    ll ans = gauss(n, K);

    return 0;
}