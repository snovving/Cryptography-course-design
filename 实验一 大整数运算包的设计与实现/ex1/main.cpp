#include <iostream>
#include "BigInt.h"
#include "BigIntMore.h"

using namespace std;

int main() {
    char ch;
    // 左 右 模
    BigInt s1, s2, s3, res;
    // 素性检测
    BigInt n;
    bool flag = true;

    cout << "                                 .__                " << endl
         << "  ______ ____   _______  _____  _|__| ____    ____  " << endl
         << " /  ___//    \\ /  _ \\  \\/ /\\  \\/ /  |/    \\  / ___\\ " << endl
         << " \\___ \\|   |  (  <_> )   /  \\   /|  |   |  \\/ /_/  >" << endl
         << "/____  >___|  /\\____/ \\_/    \\_/ |__|___|  /\\___  / " << endl
         << "     \\/     \\/                           \\//_____/  " << endl << endl;

    cout << "[+] Please enter the symbol of the operation to be performed first." << endl
         << "[+] Then enter the two operands and modulus (if needed):" << endl;

    while (cin >> ch) {
        switch (ch) {
            case '+':
                cin >> s1 >> s2 >> s3;
                res = (s1 + s2) % s3;
                break;
            case '-':
                cin >> s1 >> s2 >> s3;
                res = (s1 - s2) % s3;
                break;
            case '*':
                cin >> s1 >> s2 >> s3;
                res = (s1 * s2) % s3;
                break;
            case '/':
                cin >> s1 >> s2 >> s3;
                res = (s1 / s2) % s3;
                break;
            case '%':
                cin >> s1 >> s2 >> s3;
                res = (s1 % s2) % s3;
                break;
            case '^':
                cin >> s1 >> s2 >> s3;
                res = MOD_FAST(s1, s2, s3);
                break;
            case 'G':
                cin >> s1 >> s2;
                res = GCD(s1, s2);
                break;
            case 'R':
                cin >> s1 >> s3;
                res = MOD_INV(s1, s3);
                break;
            case 'M':
                n = 0;
                flag = true;
                srand((unsigned) time(0));
                n = rand();
                if (n % 2 == 0) {
                    n += 1;
                }
                while (flag) {
                    if (MR(n)) {
                        flag = false;
                        cout << "[*] Generate prime number " << n << " through miller rabin primality test." << endl;
                    } else {
                        n += 2;
                    }
                }
                break;
            default :
                break;
        }
        if (ch != 'M') {
            cout << res << endl;
        }
    }
    return 0;
}
