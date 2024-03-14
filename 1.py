import math
from matplotlib import pyplot as plt

# 3U 正弦滑变PRI NUM
# pw = (math.sin((i - 1) / (num - 1) * 2 * math.pi) *  100 * pri_range / 2 + pri) * 0.9

num = 4
pw = 90
pri = 100
pri_range = 10
res_list = list()


def get_pw():
    a = 1e12
    pw = 90
    aa = 1
    for i in range(1, num):
        result = math.sin((i - 1) / (num - 1) * 2 * math.pi) * 100 * pri_range / 200 + pri
        print(f"RES={result}")
        if a > result:
            a = result
            aa = i
        res_list.append(result)
    pw = pw if pw < a * 0.9 else a * 0.9
    print(pw, a, aa)
    # 使用PW倒退NUM
    d = math.sin((aa - 1) / (num - 1) * 2 * math.pi)
    print(d)
    b = (pw / 0.9 - pri) * 200 / pri_range / 100
    print(b)
    # plt.plot(res_list)
    # plt.show()


def get_num():  # 听我说谢谢你 因为有你 公式错误 李老师
    for i in range(1, num):
        a = math.asin((pw / 0.9 - pri) / 0.5 * pri_range / 200)
        result = 2 * math.pi * (i - 1) / (math.asin((pw / 0.9 - pri) / 0.5 * pri_range) * 180 / math.pi)
        print(f"NUM={result}")


def get_num1():
    a = (pw / 0.9 - pri) * 200 / pri_range / 100
    for i in range(1, num + 1):
        hu = (i - 1) / (num - 1) * 2 * math.pi
        angle = hu / math.pi * 360
        print(a, hu, angle)


if __name__ == '__main__':
    get_pw()
    # get_num1()
    # pw = (math.sin((i - 1) / (num - 1) * 2 * math.pi) *  100 * pri_range / 200 + pri) * 0.9
