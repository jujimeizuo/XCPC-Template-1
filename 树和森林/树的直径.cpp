//����ֱ�����ʣ�
//1��ֱ�����˵�һ��������Ҷ�ӽڵ�
//2�������������Զ�ĵ�һ����ֱ����һ���˵㣬�������̰����ֱ����������ȷ�Կ��Եó�
//3�������������������һ����ֱ�����˵�Ϊ(u,v)(u,v)���ڶ�����ֱ�����˵�Ϊ(x,y)(x,y)����һ���߽����������ӣ���ô������ֱ��һ����u,v,x,y,u,v,x,y,�е�������
//4������һ�����������һ������Ͻ�һ��Ҷ�ӽڵ㣬��ô����ı�ֱ����һ���˵�
//5����һ�������ڶ���ֱ������ô��Щֱ������һ���ҽ�������Щֱ�����е�

//P3761 [TJOI2017]����
//��ȥ��һ�����ٹ�·�����������޽�һ��һ���ĸ��ٹ�·(����ͨ����һ������ʹ�������������������֮������ͨ������С
//ֻ��ÿ��ȥ��һ��·����ѯ������ͨ������ֱ�������İ뾶
//����Ϊ ������ͨ�������ֱ�� �� ���İ뾶֮�� ����Сֵ

const int MAX = 5e3;
int N;
int dis[MAX], tag[MAX], ans, half;
//tag����������Ƿ�Ҫ�ֿ�


struct edge {
    int nxt, to, w;
} e[MAX << 1];

int head[MAX], tot;

void add(int u, int v, int w) {
    e[++tot].to = v;
    e[tot].w = w;
    e[tot].nxt = head[u];
    head[u] = tot;
}

void init() {
    tot = 0;
    memset(head, 0, sz(head));
    memset(tag, 0, sz(tag));
}

pii dfs(int u, int fa) {//��������ֱ��
    pii mx = make_pair(dis[u], u);
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa && !tag[v]) {
            dis[v] = dis[u] + e[i].w;
            mx = max(mx, dfs(v, u));
        }
    return mx;
}

pii getD(int start) {//����������㿪ʼ, ��������ֱ���������˵�, ����Ϊdis[second]
    dis[start] = 0;
    start = dfs(start, 0).second;
    dis[start] = 0;
    return make_pair(start, dfs(start, 0).second);
}

bool findHalf(int u, int fa, int d, int totLen, int end) {//�������İ뾶
    if (u == end) {
        half = min(half, max(totLen - d, d));
        return true;
    }
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa && !tag[v]) {
            if (findHalf(v, u, d + e[i].w, totLen, end)) {
                half = min(half, max(totLen - d, d));
                return true;
            }
        }
    return false;
}

pii getHalf(int s) {//�õ�ֱ���Ͱ뾶
    pii t = getStartEnd(s); int totLen = dis[t.second];
    half = INF; findHalf(t.first, 0, 0, totLen, t.second);
    return make_pair(totLen, half);
}

bool solve(int u, int fa, int end) {
    if (u == end) return true;
    for (int i = head[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
        if (v != fa) {
            if (solve(v, u, end)) {
                //����v��������ֱ����һ�룬����u��������ֱ����һ��
                //��������..����С��
                tag[v] = 1; pii h1 = getHalf(u); tag[v] = 0;
                tag[u] = 1; pii h2 = getHalf(v); tag[u] = 0;
                int n1 = h1.first, n2 = h2.first, n3 = h1.second + h2.second + e[i].w;
                ans = min(ans, max(max(n1, n2), n3));
                tag[v] = tag[u] = 0;
                return true;
            }
        }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N;
    init();
    for (int i = 1; i < N; i++) {
        int u, v, w; cin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }
    ans = INF;
    pii t = getStartEnd(1);
    int start = t.first, end = t.second;
    solve(start, 0, end);
    cout << ans << endl;

    return 0;
}