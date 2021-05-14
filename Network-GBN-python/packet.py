# packet.py - function:make packet and extract packet
import libscrc
"""
简单的CRC16计算示例：
    CRC16校验码计算方法如下：
    1、初始化CRC值为0xFFFF
    2、被检验数的第1字节跟CRC的低8位异或，将结果放入CRC的低8位（CRC的高8位不变）
    3、CRC右移1位，若移出的为0继续右移;为1CRC寄存器跟生成多项式（倒序后的值）异或（X16+X15+X2+1 <--> 0x8005 >>> 0xA0001)
    4、重复步骤3,8次第1字字数据处理完成
    5、取被检验数据的下1字节，进行2、3、4步;至到整个数据检验完成
    6、将最后的CRC值,高低字节交换
"""

wCRCin = 0x0000
wCPoly = 0x1021
POLY = 0x10

def cal_checksum(data):
    global wCRCin
    global wCPoly

    for byte in data:
        wCRCin ^= ((byte) << 8)
        for i in range(8):
            if wCRCin & 0x8000:
                wCRCin = (wCRCin << 1) ^ wCPoly
            else:
                wCRCin = (wCRCin << 1)

    # wCRCin = wCRCin & 0xffff
    s = hex(wCRCin).upper()
    # return s
    return s[-4:-2] + s[-2:]


# 后面字符串data是byte类型， 十六进制
def make(seq_num, data=b'', is_checksum=False):
    # print("set seq_num",seq_num)
    seq_bytes = seq_num.to_bytes(4, byteorder='little', signed=True)

    # 加checksum
    if is_checksum is True:
        # 用自己写的check_sum 函数
        # check_sum = cal_checksum(data)
        # new_data = data + bytes(check_sum, encoding="utf8")

        # 用libscrc
        data = b'\x00' + data
        # print(data)
        crc16 = libscrc.ibm(data, POLY)  # poly=0x10 (Normal)
        crc16 = crc16.to_bytes(4, byteorder='little', signed=False)
        # print(data)
        full_data = data + crc16
        # print(full_data)
        # print(crc16)
        # print("###########")
        # print(full_data)
        seq_bytes = seq_bytes + full_data
        # print("!!!!!!!!!!!")
        # print(seq_bytes)

    # 不加checksum
    else:
        seq_bytes = seq_bytes + data

    return seq_bytes


# Creates an empty packet
def make_empty():
    return b''

# CRC码的校验，将得到的CRC码用约定的G(X)去除，余数为0，结果正确
def check_CRC(raw_data):
    m = int.from_bytes(raw_data, byteorder='little', signed=False)
    reminder = m % POLY
    # 如果余数为0， checksum检验正确
    if reminder == 0:
        final_data = raw_data[1:-4]

    # 如果余数不为0，报错 不发送ACK
    else:
        final_data = ''
    return final_data


# Extracts sequence number, data and checksum from a non-empty packet
def extract(packet, is_checksum = False):
    # 有checksum的情况，解析checksum
    if is_checksum is True:
        # 循环冗余码位于最后四个字节
        seq_num = int.from_bytes(packet[0:4], byteorder='little', signed=True)
        raw_data = packet[4:]
        final_data = check_CRC(raw_data)
        print(final_data)

    else:
        seq_num = int.from_bytes(packet[0:4], byteorder = 'little', signed=True)
        final_data = packet[4:]
    return seq_num, final_data
