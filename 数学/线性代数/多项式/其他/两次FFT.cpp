//原理
//记P(x) = F(x) + G(x)i
//P(x)^2 = F(x)^2 - G(x)^2 + 2F(x)G(x)i 
//故虚部/2就可得到F(x)G(x)

//快但是会丢失精度
//比如说F(x)的系数均在[1e6, 1e5]之间, G(x)的系数均在[1e5, 1e6]之间
//直接做FFT ,涉及的精度跨度上限是1e12
//假如使用三次变两次优化,由于平方项的存在,涉及的精度跨度上限是1e24, 严重掉精度

const int MAX = 4e6 + 10;
const double PI = acos(-1);

struct Complex {
    double a, b;
    Complex(double a = 0, double b = 0): a(a), b(b) {}
    Complex operator * (const Complex &rhs) { return Complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a); }
    Complex operator + (const Complex &rhs) { return Complex(a + rhs.a, b + rhs.b); }
    Complex operator - (const Complex &rhs) { return Complex(a - rhs.a, b - rhs.b); }
};

int N, M;
int n, tr[MAX];
Complex a[MAX];

void FFT(Complex *A, int type) {
    for (int i = 0; i < n; i++) if (i < tr[i]) swap(A[i], A[tr[i]]);
    for (int len = 2; len <= n; len <<= 1) {//区间长度
        int mid = len / 2;
        Complex Wn(cos(2 * PI / len), type * sin(2 * PI / len));//单位根
        for (int k = 0; k < n; k += len) {//每个子问题的起始点
            Complex w(1, 0);//omega
            for (int l = k; l < k + mid; l++) {
                Complex t = w * A[l + mid];
                A[l + mid] = A[l] - t;
                A[l] = A[l] + t;
                w = w * Wn;
            }
        }
    }

}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N; i++) scanf("%lf", &a[i].a);
    for (int i = 0; i <= M; i++) scanf("%lf", &a[i].b);//虚部

    n = 1; while (n <= N + M) n <<= 1;
    for (int i = 0; i < n; i++) tr[i] = (tr[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0);

    FFT(a, 1);
    for (int i = 0; i < n; i++) a[i] = a[i] * a[i];

    FFT(a, -1);

    for (int i = 0; i <= N + M; i++)
        printf("%d ", (int)(a[i].b / n / 2 + 0.5));


    return 0;
}