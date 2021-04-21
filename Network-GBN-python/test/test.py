def crc16(x, invert):
    wCRCin = 0x0000
    wCPoly = 0x1021
    for byte in x:
        if type(byte) is str:     # 这里做了个判断可以直接传入字符串，但存在意义不大
            wCRCin ^= (ord(byte) << 8)
        else:
            wCRCin ^= ((byte) << 8)
        for i in range(8):
            if wCRCin & 0x8000:
                wCRCin = (wCRCin << 1) ^ wCPoly
            else:
                wCRCin = (wCRCin << 1)

    #wCRCin = wCRCin & 0xffff
    s = hex(wCRCin).upper()
    #return s
    return s[-2:] + s[-4:-2] if invert == True else s[-4:-2] + s[-2:]

if __name__ == '__main__':
    var = [0x01,0x02,0x03,0x04]
    var1 = bytearray.fromhex("01020304")  #将hexstring 转化为 字节数组。

    print(crc16(var,False))
    print(crc16(var1, False))