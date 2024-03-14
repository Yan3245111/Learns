from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QVBoxLayout
from PyQt5.QtChart import QPolarChart, QChartView, QValueAxis, QScatterSeries
import sys
import random
import math

from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5.QtWidgets import *
from PyQt5.QtCore import Qt
from PyQt5.QtChart import QScatterSeries, QPolarChart, QChart, QChartView, QValueAxis

# pip3 install QtChart


class Hello(QWidget):

    def __init__(self):
        super().__init__()
        self.polar = QPolarChart()
        chartView = QChartView(self.polar)

        layout = QVBoxLayout()
        layout.addWidget(chartView)

        # setting axis
        axisy = QValueAxis()
        axisx = QValueAxis()

        axisy.setRange(0, 500)
        axisy.setTickCount(4)
        self.polar.setAxisY(axisy)

        axisx.setRange(0, 360)
        axisx.setTickCount(5)
        self.polar.setAxisX(axisx)

        # Let's draw scatter series
        self.polar_series = QScatterSeries()
        self.polar_series.setMarkerSize(5.0)

        self.polar_series.append(0, 0)
        self.polar_series.append(360, 500)

        # Why not draw archimedes spiral
        for i in range(0, 360, 10):
            self.polar_series.append(i, i)

        self.polar.addSeries(self.polar_series)
        self.setLayout(layout)
        self.resize(500, 500)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = Hello()
    win.show()
    sys.exit(app.exec_())
