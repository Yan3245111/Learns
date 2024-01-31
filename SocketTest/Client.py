import socket
import struct

tail = b'\xe7\xe7'
head = b'\x7e\x7e'


class OneClient:

    def __init__(self):
        self._client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._client.connect(("127.0.0.1", 5005))

    def send(self, data: bytes):
        self._client.send(data)

    def encode_data(self, cmd_no: int, param_no: int, data: int) -> bytes:
        tx_data = struct.pack("!h", param_no) + struct.pack("!q", data)
        tx_msg = head + struct.pack("!b", cmd_no) + struct.pack("!h", len(tx_data)) + tx_data + tail
        print(tx_msg)
        return tx_msg


if __name__ == '__main__':
    one_client = OneClient()
    data = one_client.encode_data(cmd_no=1, param_no=1, data=1)
    one_client.send(data)
