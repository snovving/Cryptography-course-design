#include <iostream>
#include <string>

using namespace std;


int gcd(int n, int m) {
    int r, temp;
    if (n < m) {
        temp = n;
        n = m;
        m = temp;
    }
    while (m != 0) {
        r = n % m;
        n = m;
        m = r;
    }
    return n;
}


int main() {
    string Z = "计算机学院网络工程信息安全，我们热爱中华人民共和国。大家";
    string C = "和院程安我爱计";
    string res;

    int clen = C.length() / 2;
    int zlen = Z.length() / 2;
    int p, a, b, c, pos[clen];

    // 查找 C 在 Z 中的位置
    for (int i = 0; i < clen; i++) {
        for (int j = 0; j < zlen; j++) {
            if (Z[2 * j] == C[2 * i] && Z[2 * j + 1] == C[2 * i + 1]) {
                pos[i] = j;
            }
        }
    }

    // 爆破 a
    for (a = 2; a < 28; a++) {

        // 判断 a 是否可逆
        if (gcd(a, 28) == 1) {

            // 求出 a 的逆元 p
            for (p = 2; p < 28; p++) {
                if ((a * p) % 28 == 1) break;
            }

            // 爆破 b
            for (b = 0; b < 28; b++) {
                // 清空每一次的结果
                res.clear();
                // 解密
                for (int i = 0; i < clen; i++) {
                    // 特别注意小于 0 的情况，这与 py 不同，因为我们需要加上两字节
                    c = (p * (pos[i] - b)) % 28;
                    if (c >= 0) {
                        res = res + Z[2 * c] + Z[2 * c + 1];
                    } else {
                        c = c + 28;
                        res = res + Z[2 * c] + Z[2 * c + 1];
                    }
                }

                cout << "当 a=" << a << ",b=" << b << " 时，解密结果为：" << res << endl;
            }
        }
    }
}