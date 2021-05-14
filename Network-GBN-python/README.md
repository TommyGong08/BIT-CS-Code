# 计网GBN实验【python版本】

## 概述
采用Go-back-N算法的文件传输(基于UDP协议)。该算法将数据打包成多个包发送给receiver,如果包丢失,sender会重新发送整个滑动窗口的数据给receiver。
数据包的格式如下:   
```bash
   包序号       数据内容     循环冗余校验码  
|   seq    |     data    |   checksum    |
|  4 Bytes |             |     4 Bytes   |
```

使用CRC校验码作为checksum,receiver会对data+checksum进行验证,结果正确发送ACK,校验错误丢弃整个包。

## 使用

* **先** 开启接收方:
`python receiver.py [filename of the file to write to]`
* **再** 开启发送方:
`python sender.py [filename of file to read from]`
* test文件下有用于测试的文件

