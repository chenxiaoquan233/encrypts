# TEA算法

## TEA算法介绍

TEA(Tiny Encryption Algorithm), 一次可以加密64 bit(8 byte, 或2 int_32)，使用一个128 bit(16 byte, 或4 int_32)的key。使用一个delta常数，通常为```0x9E3779B9```。推荐迭代轮数为64轮，最少32轮。

## 加密

### 加密过程图示（两轮）

<img src="teaEnc.png" alt="1" width="280" />

### 伪码表示

L' = L + ((R << 4) + K[0]) ^ (R + delta_i) ^ ((R >> 5) + K[1])

R' = R + ((L' << 4) + K[2]) ^ (L' + delta_i) ^ ((L' >> 5) + K[3])

## 解密

解密过程即是加密过程的逆过程

### 伪码表示

R = R' - ((L' << 4) + K[2]) ^ (L' + delta_i) ^ ((L' >> 5) + K[3])

L' = L - ((R << 4) + K[0]) ^ (R + delta_i) ^ ((R >> 5) + K[1])