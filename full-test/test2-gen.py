from struct import *

f = open("test2.bin", "wb")

packet_a = '=B i i 6b 4s'
packet_b = '=B h h 6b'
packet_c2 = '=B I 2b'
packet_c4 = '=B I 4b'

def a():
	buf = pack(packet_a, 0x01, 1, 2,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, "abc")
	f.write(buf)

def b():
	f.write(pack(packet_b, 0x02, 3, 4, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b))

def c():
	f.write(pack(packet_c2, 0x03, 1, 0x0b, 0x0b))


a()
a()
a()
b()
c()
b()
c()

