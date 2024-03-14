import numpy as np
import matplotlib.pyplot as plt

r = np.arange(0, 4 * np.pi, 0.01)  # 弧度值
y = np.linspace(0, 2, len(r))  # ⽬标值

ax = plt.subplot(111, projection='polar', facecolor='lightgreen')  # 定义极坐标
ax.plot(r, y, color='red')
ax.set_rmax(3)  # 设置半径最⼤值
ax.set_rticks([0.5, 1, 1.5, 2])  # 设置半径刻度
ax.set_rlabel_position(-22.5)  # 设置半径刻度位置
ax.grid(True)  # ⽹格线
ax.set_title("A line plot on a polar axis", va='center', ha='center', pad=30)
plt.show()
