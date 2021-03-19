//
// Created by snovving on 2021/3/19.
//

#ifndef EX1_BIGINTMORE_H
#define EX1_BIGINTMORE_H

#include "BigInt.h"

BigInt GCD(BigInt a, BigInt b) {
    return a == "0" ? b : GCD(b % a, a);
}

// 快速幂算幂模
BigInt MOD_FAST(BigInt a, BigInt n, BigInt b) {
    BigInt temp;
    if (n == 0) return 1 % b;
    if (n == 1) return a % b;
    temp = MOD_FAST(a, n / 2, b);
    temp = temp * temp % b;
    if (n % 2 == 1) temp = temp * a % b;
    return temp;
}

// 乘法逆-扩展欧几里得算法
BigInt EXTGCD(BigInt a, BigInt b, BigInt &x, BigInt &y) {
    BigInt d(a);

    if (b != "0") {
        d = EXTGCD(b, a % b, y, x);
        y = y - (a / b) * x;
    } else {
        x = "1";
        y = "0";
    }
    return d;
}

// 乘法逆
BigInt MOD_INV(BigInt a, BigInt m) {
    BigInt x, y;
    EXTGCD(a, m, x, y);
    if (x < 0) {
        x = abs(x);
        x = m - x;
    }
    return (m + x % m) % m;
}

// Miller-Rabin 素性检测算法
bool MR(BigInt n) {
    BigInt a, s = 0, num;
    BigInt t = n - 1, mm = n - 1;
    // 判断 t 是否为奇数，否则右移
    while (t % 2 == 0) {
        //右移一位
        t = t / 2;
        s++;
    }
    srand((unsigned) time(0));
    a = rand();
    num = MOD_FAST(a, t, n);

    //判断第一个式子 a^t mod n=1
    if (num == 1) {
        return true;
    }
    //进行 s 次判断
    for (int i = 0; i < s; i++) {
        if (num == mm)return true;
        else num = MOD_FAST(num, 2, n);
    }
    return false;
}

#endif //EX1_BIGINTMORE_H
