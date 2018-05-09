import sys
from struct import *

f = open("test4.bin", "wb")

packet_a = '=B 8s'
packet_b = '=B i'
packet_c = '=B 6b'
packet_d = '=B 2b 10s i4'

def a():
	f.write(pack(packet_a, 0x01, "abcd"))

def b():
	f.write(pack(packet_b, 0x02, 122))

def c():
	f.write(pack(packet_c, 0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06))

def d():
	f.write(pack(packet_d, 0x04, 0x02, 0x04, "abcdefghi", 123))


functions = {'a' : a, 'b' : b, 'c' : c, 'd' : d}

packet_input = raw_input()

for func in packet_input.split():
	if func in functions:
		functions[func]()
		print("called: " + func)
	else:
		print("Unkown packet name: " + func)
		exit(1)



