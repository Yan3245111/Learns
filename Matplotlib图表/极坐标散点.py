import numpy as np
import matplotlib.pyplot as plt

from pylab import mpl

mpl.rcParams['font.sans-serif'] = ['FangSong']  # 指定仿宋中文字体防止文字乱码

r = 2 * np.random.rand(100)  # 生成100个服从“0~1”均匀分布的随机样本值
theta = 2 * np.pi * np.random.rand(100)  # 生成角度
area = 100 * r ** 2  # 生成面积
colors = theta  # 生成颜色
ax = plt.subplot(111, projection='polar')
c = ax.scatter(theta, r, c=colors, s=area, cmap='cool', alpha=0.75)
# xxx.scatter为绘制散点图函数
plt.title('极坐标散点图')
plt.show()
