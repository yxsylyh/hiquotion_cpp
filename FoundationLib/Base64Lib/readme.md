# Base64 编解码类

主要方法：Encode 和 Decode。

# 示例代码

## Encode and Decode

```java

CBase64 base64;

// 原始字符串（也可以是字节数组）
char *orig="hello world!";
long origLen=strlen(orig);
printf("orig string is %s", orig);

// base64 后的字符串
char *encode=new char[origLen*2];
memset(encode, 0x00, origLen*2);
long encodeLen=0;
base64::Encode((const unsigned char *)orig, origLen, encode, &encodeLen);
printf("encode string is %s", encode);

// 解base64 后的字符串
char *decode=new char[encodeLen];
memset(decode, 0x00, encodeLen);
long decodeLen=0;
base64::Decode((const char *)decode, encodeLen, (unsigned char *)decode, &decodeLen);
print("decode string is %s", decode);

delete encode;
delete decode;

```
