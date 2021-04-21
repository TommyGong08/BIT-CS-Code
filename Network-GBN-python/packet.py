# packet.py - function:make packet and extract packet
wCRCin = 0x0000
wCPoly = 0x1021

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

# Creates a packet from a sequence number and byte data
# 后面字符串data是byte类型， 十六进制
def make(seq_num, data=b''):
    # print("set seq_num",seq_num)
    seq_bytes = seq_num.to_bytes(4, byteorder='little', signed = True)

    # data_binary
    # print(data)
    check_sum = cal_checksum(data)
    # print(check_sum)
    new_data = data + bytes(check_sum, encoding="utf8")
    print(new_data)
    return seq_bytes + new_data

# def new_make(seq_num, data = b'')

# Creates an empty packet
def make_empty():
    return b''

# Extracts sequence number and data from a non-empty packet
def extract(packet):
    seq_num = int.from_bytes(packet[0:4], byteorder = 'little', signed=True)
    return seq_num, packet[4:]
