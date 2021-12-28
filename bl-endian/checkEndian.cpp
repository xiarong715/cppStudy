#include <stdio.h>

int main1(int argc, char *argv[]) {
    unsigned data = 0x12345678;
    unsigned char *p = (unsigned char *)&data;
    printf("%#x, %#x, %#x, %#x\n", p[0], p[1], p[2], p[3]);
    if (p[0] == 0x78) printf("little-endian\n");
    else printf("big-endian\n");
    return 0;
}

int main2(int argc, char *argv[]) {
    unsigned char arr[4] = {0x11, 0x22, 0x33, 0x44};
    unsigned *p = (unsigned *)arr;
    printf("%#x\n", *p);
    return 0;
}

// DBO: LE
int main3(int argc, char *argv[]) {
    unsigned char arr[4] = {0x12, 0x34, 0x56, 0x78};  // data little endian      sample: 0x3412 0x7856
    unsigned char to[4] = {0};
    printf("%#x, %#x\n", *((unsigned short *)arr), *((unsigned short *)arr + 1));
    unsigned char *fromBuf = static_cast<unsigned char *>(arr);
    unsigned char *toBuf = static_cast<unsigned char *>(to);
    int iMix = 0;
    int mixLen = sizeof(arr);
    while(iMix < mixLen) {
        unsigned short sampleFrom = fromBuf[iMix]; // 处理字节序时，使用无符号
        sampleFrom |= fromBuf[iMix + 1] << 8;   // host little endian 或 host big endian， 根据音频数据大小端取出正确的值
        short sample = sampleFrom + 1;          // 运算时，使用有符号
        unsigned short sampleTo = static_cast<short>(sample);   // 不用管sampleTo此时在内存中的存储方式，而按照音频数据字节序，把结果写入内存就行
        toBuf[iMix++] = sampleTo & 0xff;
        toBuf[iMix++] = sampleTo >> 8 & 0xff;
    }
    printf("%#x, %#x\n", *((unsigned short *)to), *((unsigned short *)to + 1));

    return 0;
}

// HBO: 大端或小端，在内存中才会体现；根据音频数据的大小端，拼出正确的值，赋给变量，进行运算（混音或调节音量）， 保存音频数据时，按照音数据原有的大小端存入内存
// 不管host byte order，因为根据音频数据的大小端读取了正确的值；不用管该值在内存中如何存放；
// DBO: big endian
int main(int argc, char *argv[]) {
    unsigned char arr[4] = {0x12, 0x34, 0x56, 0x78};  // data big endian     sample: 0x1234 0x5678
    unsigned char to[4] = {0};
    unsigned char *fromBuf = static_cast<unsigned char *>(arr);
    unsigned char *toBuf = static_cast<unsigned char *>(to);
    int iMix = 0;
    int mixLen = sizeof(arr);
    while(iMix < mixLen) {
        // 读取正确的值
        unsigned short sampleFrom = fromBuf[iMix] << 8 & 0xff00;
        sampleFrom |= fromBuf[iMix + 1] & 0xff;
        // 运算，使用有符号
        short sample = sampleFrom + 1;
        // 根据音频数据的大小端存入内存，转换字节序，使用无符号
        unsigned short sampleTo = static_cast<unsigned short>(sample);  // 不用管sampleTo此时在内存中的存储方式，而按照音频数据字节序，把结果写入内存就行
        toBuf[iMix++] = sampleTo >> 8 & 0xff;
        toBuf[iMix++] = sampleTo & 0xff;
    }
    printf("%#x, %#x, %#x, %#x\n", to[0], to[1], to[2], to[3]);
    return 0;
}

// 小端：低字节在低地址，高字节在高地址
// 大端：高字节在低地址，低字节在高地址；（内存中存放顺序与书写顺序一致）
