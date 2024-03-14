# 192.168.50.250
#
# 账号姓名 密码123456
#
# 链接:https://pan.baidu.com/s/159Ubqy9W0HEKju-AZUlmHw?pwd=wks8

#公司内网
# 10.22.50.246

import math

num = 20
pri_range = 0.2
pri = 100
pw = 35
data = 200
result = 1e10

# pw = (math.sin((i - 1) / (num - 1) * 2 * math.pi) *  100 * pri_range / 2 + pri) * 0.9
# num = (pw / 0.9 + pri) * 2 / pri_range / 100

for i in range(1, num + 1):
    data = data if data <= math.sin((i - 1) / (num - 1) * 2 * math.pi) * 100 * pri_range / 2 + pri else math.sin((i - 1) / (num - 1) * 2 * math.pi) * 100 * pri_range / 2 + pri
    if result > data:
        result = data
    print(data)
a = math.sin(20)
print(a)
b = math.radians(a)
c = math.degrees(b)
print(b, c)
