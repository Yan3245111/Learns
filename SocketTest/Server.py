import time
import socket
import struct
import threading


class OneServer:

    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._socket.bind(("127.0.0.1", 5005))
        self._thread = threading.Thread(target=self._working, daemon=True)
        self._thread.start()

    def _working(self):
        self._socket.listen()
        conn, ip = self._socket.accept()
        while 1:
            head1 = conn.recv(1)
            if head1 == b'':
                continue
            if head1 == b'\x7e':
                print(f"HEAD1={head1}")
                head2 = conn.recv(1)
                if head2 == b'\x7e':
                    cmd_no = struct.unpack("b", conn.recv(1))[0]
                    cmd_len = struct.unpack("!h", conn.recv(2))[0]
                    data = conn.recv(cmd_len)
                    tail = conn.recv(2)
                    print(f"CMD_NO={cmd_no}, CMD_LEN={cmd_len}, DATA={data}, TAIL={tail}")
                    if tail == b'\xe7\xe7':
                        print("接收结束")
                    else:
                        print("包尾ERROR")
            #     else:
            #         print("ERROR")
            # else:
            #     print('ERROR')


if __name__ == '__main__':
    one_server = OneServer()
    while 1:
        time.sleep(1)
