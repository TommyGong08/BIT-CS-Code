# receiver.py - The receiver in the reliable data transer protocol
import packet
import socket
import sys
import random

DROP_PROB = 8
BUFFER_SIZE = 1024
RECEIVER_ADDR = ('localhost', 7120)

# Receive packets from the sender
def receive(sock, filename):
    # Open the file for writing
    try:
        file = open(filename, 'wb')
    except IOError:
        print('Unable to open', filename)
        return
    
    expected_num = 0
    while True:
        # Get the next packet from the sender
        pkt, addr = sock.recvfrom(BUFFER_SIZE)
        print("收到数据data", packet)
        if not pkt:
            break
        seq_num, data = packet.extract(pkt, True)
        if data == '':
            continue
        print('Got packet', seq_num)
        
        # Send back an ACK
        if seq_num == expected_num:
            print('Got expected packet')
            print('Sending ACK', expected_num)
            pkt = packet.make(expected_num)
            if random.randint(0, DROP_PROB) > 0:
                sock.sendto(pkt, addr)

            expected_num += 1
            file.write(data)
        else:
            print('Sending ACK', expected_num - 1)
            pkt = packet.make(expected_num - 1)
            if random.randint(0, DROP_PROB) > 0:
                sock.sendto(pkt, addr)

    file.close()

# Main function
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Expected filename as command line argument')
        exit()
        
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(RECEIVER_ADDR) 
    filename = sys.argv[1]
    print(sock)
    receive(sock, filename)
    sock.close()
