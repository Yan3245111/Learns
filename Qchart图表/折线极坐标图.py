import sys
import random
import math

from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt
from PyQt5.QtChart import QLineSeries, QPolarChart, QChart, QChartView, QValueAxis


class MyPolarWindow(QWidget):
    def __init__(self, parent=None):
        super(MyPolarWindow, self).__init__(parent)
        self.setWindowTitle("散点极坐标图")
        # 创建图表
        polarChart = QPolarChart()
        chartView = QChartView()

        # 创建Series
        scatterSeries = QLineSeries()

        # 添加数据
        for value in range(1, 50):
            scatterSeries.append(value, random.random() * 10)
            # scatterSeries.append(QPointF(value, random.random()*10))

        scatterSeries.setName("折线极坐标图")

        polarChart.addSeries(scatterSeries)
        polarChart.setContentsMargins(0, 0, 0, 0)
        polarChart.setTheme(QChart.ChartThemeBlueCerulean)
        # polarChart.createDefaultAxes()

        # 设置 角向轴
        angularAxis = QValueAxis()
        angularAxis.setTickCount(9)
        angularAxis.setLabelFormat("%.2f")
        angularAxis.setShadesVisible(True)
        angularAxis.setShadesBrush(QBrush(QColor(230, 230, 255)))
        polarChart.addAxis(angularAxis, QPolarChart.PolarOrientationAngular)
        angularAxis.setRange(0, 20)  # 必须设置范围，否则图表无法显示

        # 设置 径向轴
        radialAxis = QValueAxis()
        radialAxis.setTickCount(5)
        radialAxis.setLabelFormat("%d")
        polarChart.addAxis(radialAxis, QPolarChart.PolarOrientationRadial)
        radialAxis.setRange(0, 10)

        chartView.setChart(polarChart)
        chartView.setFocusPolicy(Qt.NoFocus)
        chartView.setRenderHint(QPainter.Antialiasing)

        vbox = QVBoxLayout()
        vbox.addWidget(chartView)
        self.setLayout(vbox)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = MyPolarWindow()
    win.show()
    sys.exit(app.exec_())
