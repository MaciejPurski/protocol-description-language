f = open("test1.bin", "wb")

def packet_a(msg):
	f.write(bytearray({0x01}))
	f.write(msg)

def packet_b(msg):
	f.write(bytearray({0x02}))
	f.write(msg)

packet_a("aaaaaaaa")
packet_b("bbbbbb")
packet_a("aaaaaaaa")
packet_b("bbbbbb")
packet_b("bbbbbb")
