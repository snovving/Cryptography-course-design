Z = "计算机学院网络工程信息安全，我们热爱中华人民共和国。大家"
C = "和院程安我爱计"
pos = []


def gcd(n, m):
    if n < m:
        temp = n
        n = m
        m = temp
    while m != 0:
        r = n % m
        n = m
        m = r
    return n


if __name__ == '__main__':
    # 查找 C 的每个字符在 Z 中的位置，并存到 pos 列表中
    for i in C:
        pos.append(Z.find(i))
    # 爆破 a
    for a in range(2, 28):
        # 判断 a 是否可逆
        if gcd(a, 28) == 1:
            # 求 a 的逆元
            for b in range(2, 28):
                if (a * b) % 28 == 1:
                    p = b
                    break
            # 爆破 b
            for b in range(0, 28):
                # 注意清空每一次的解密结果
                res = ""
                for i in pos:
                    i = p * (i - b) % 28
                    res += Z[i]
                print(f"当 a={a},b={b} 时，解密结果为：{res}")
