import libscrc

data = b'\x00\x01\x02'
data2 = b'\x00\x45\x00\x00\x3c\x00\x00\x00\x00\x40\x11\x00\x00\xc0\xa8\x2b\xc3\x08\x08\x08\x08\x11'
data3 = b'\x45\x00\x00\x3c\x00\x00\x00\x00\x40\x11\x00\x00\xc0\xa8\x2b\xc3\x08\x08\x08\x08\x11'
data4 = b'\x00' + data3
crc16 = libscrc.ibm(data, 0x10)    # poly=0x10 (Normal)
crc16 = crc16.to_bytes(4, byteorder='little', signed=False)
print(data)
full_data = data + crc16
print(full_data)
print(crc16)
m = int.from_bytes(full_data, byteorder='little', signed=False)
print(m)
print(int(0x10))
print(m % int(0x10))