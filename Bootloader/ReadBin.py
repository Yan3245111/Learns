import math
import struct


with open("2UProject.bin", "rb") as fp:
    data = fp.read()
    all_data = bytes.fromhex(data.hex())
    pkt_length = math.ceil(len(all_data) / 992)
    for i in range(pkt_length):
        one_cmd = struct.pack("!H", i) + all_data[i * 992: (i + 1) * 992]
        if i < 10:
            print(one_cmd)

    fp.close()
