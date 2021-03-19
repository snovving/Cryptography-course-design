#include<iostream>
#include<string>

using namespace std;

//右移的时候，高位一定要补零，而不是补充符号位
#define shift(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

// 4 个 32bit 初始向量
#define A 0x67452301
#define B 0xefcdab89
#define C 0x98badcfe
#define D 0x10325476

//strByte 的长度
unsigned int strlength;

//A,B,C,D的临时变量
unsigned int atemp;
unsigned int btemp;
unsigned int ctemp;
unsigned int dtemp;

//常量ti unsigned int(abs(sin(i+1))*(2pow32))
const unsigned int k[] = {
        //第一轮
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        //第二轮
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        //第三轮
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        //第四轮
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

//向左位移数
const unsigned int s[] = {
        //第一轮
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
        //第二轮
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
        //第三轮
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
        //第四轮
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const char str16[] = "0123456789abcdef";

void mainLoop(unsigned int M[]) {
    unsigned int f, g;
    unsigned int a = atemp;
    unsigned int b = btemp;
    unsigned int c = ctemp;
    unsigned int d = dtemp;

    //64次操作
    for (unsigned int i = 0; i < 64; i++) {
        //第一轮
        if (i < 16) {
            f = F(b, c, d);
            g = i;
        }
            //第二轮
        else if (i < 32) {
            f = G(b, c, d);
            g = (5 * i + 1) % 16;
        }
            //第三轮
        else if (i < 48) {
            f = H(b, c, d);
            g = (3 * i + 5) % 16;
        }
            //第四轮
        else {
            f = I(b, c, d);
            g = (7 * i) % 16;
        }

        unsigned int tmp = d;
        d = c;
        c = b;
        b = b + shift((a + f + k[i] + M[g]), s[i]);
        a = tmp;

    }

    atemp = a + atemp;
    btemp = b + btemp;
    ctemp = c + ctemp;
    dtemp = d + dtemp;
}


// 数据填充
unsigned int *add(string str) {
    // 分组数 str.length() 返回字节数
    // 消息处理后长度为 512 整数倍少 64 bit
    unsigned int num = ((str.length() + 8) / 64) + 1;

    // 16 个子块 512/32=16
    unsigned int *strByte = new unsigned int[num * 16];

    // 所有 512bit 消息块的子块数
    strlength = num * 16;

    // 初始化子块
    for (unsigned int i = 0; i < num * 16; i++)
        strByte[i] = 0;

    for (unsigned int i = 0; i < str.length(); i++) {
        strByte[i >> 2] |= (str[i]) << ((i % 4) * 8);
    }

    // 尾部最后四字节，添加 1
    strByte[str.length() >> 2] |= 0x80 << (((str.length() % 4)) * 8);

    // 最后 64 位小端序，添加长度
    strByte[num * 16 - 2] = str.length() * 8;
    return strByte;
}

string changeHex(int a) {
    int b;
    string str1;
    string str = "";
    for (int i = 0; i < 4; i++) {
        str1 = "";
        b = ((a >> i * 8) % (1 << 8)) & 0xff;   //逆序处理每个字节
        for (int j = 0; j < 2; j++) {
            str1.insert(0, 1, str16[b % 16]);
            b = b / 16;
        }
        str += str1;
    }
    return str;
}

string getMD5(string source) {
    atemp = A;
    btemp = B;
    ctemp = C;
    dtemp = D;

    // 消息初始化处理
    unsigned int *strByte = add(source);

    // 每个 512 比特消息块
    for (unsigned int i = 0; i < strlength / 16; i++) {
        unsigned int num[16];
        // 16 次操作
        for (unsigned int j = 0; j < 16; j++)
            num[j] = strByte[i * 16 + j];
        mainLoop(num);
    }
    return changeHex(atemp).append(changeHex(btemp)).append(changeHex(ctemp)).append(changeHex(dtemp));
}

int main() {
    string m;
    cout << "[+] Please enter the string to be encrypted:" << endl;
    cin >> m;
    string c = getMD5(m);
    cout << "[*] 32-bit lowercase encryption result:" << endl;
    cout << c << endl;
    return 0;
}
