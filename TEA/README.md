# TEA算法

[toc]

## TEA算法介绍

TEA(Tiny Encryption Algorithm), 一次可以加密64 bit(8 byte, 或2 int_32)，使用一个128 bit(16 byte, 或4 int_32)的key。使用一个delta常数，通常为```0x9E3779B9```。推荐迭代轮数为64轮，最少32轮。

## 加密

### 加密过程图示（一轮）

<img src="/home/chenxiaoquan233/Temp/teaEnc.png" alt="1" style="zoom: 25%;" />

### 公式表示

$$
L' = ((R << 4) + K[0]) \oplus (R + delta_i) \oplus ((R >> 5) + K[1]) + L
$$

$$
R' = ((L' << 4) + K[2]) \oplus (L' + delta_i) \oplus ((L' >> 5) + K[3]) + R
$$

## 解密

解密过程即是加密过程的逆过程

### 公式表示

$$
R = R' - ((L' << 4) + K[2]) \oplus (L' + delta_i) \oplus ((L' >> 5) + K[3])
$$

$$
L' = L - ((R << 4) + K[0]) \oplus (R + delta_i) \oplus ((R >> 5) + K[1])
$$