from struct import *

f = open("test2.bin", "wb")

packet_a = '=B i i 6b 4s'
packet_b = '=B h h 6b'
packet_c = '=B 2b'

buf = pack(packet_a, 0x01, 1, 2,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, "abc")

f.write(buf)
f.write(pack(packet_b, 0x02, 3, 4, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b))

f.write(pack(packet_b, 0x02, 3, 4, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b))


f.write(pack(packet_a, 0x01, 1, 2,  0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, "abc"))

