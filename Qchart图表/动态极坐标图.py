import sys
from PyQt5.QtCore import Qt, QPointF
from PyQt5.QtGui import QPainter, QBrush, QColor
from PyQt5.QtWidgets import QApplication, QMainWindow, QGraphicsView
from PyQt5.QtChart import (QChart, QChartView, QPolarChart, QScatterSeries,
                           QSplineSeries, QLineSeries, QAreaSeries, QValueAxis)


class MyChartView(QChartView):
    def __init__(self, parent=None):
        super(MyChartView, self).__init__(parent)

    def keyPressEvent(self, event):

        if event.key() == Qt.Key_Plus:
            self.chart().zoomIn()
        elif event.key() == Qt.Key_Minus:
            self.chart().zoomOut()
        elif event.key() == Qt.Key_Left:
            self.chart().scroll(-1.0, 0)
        elif event.key() == Qt.Key_Right:
            self.chart().scroll(1.0, 0)
        elif event.key() == Qt.Key_Up:
            self.chart().scroll(0, 1.0)
        elif event.key() == Qt.Key_Down:
            self.chart().scroll(0, -1.0)
        elif event.key() == Qt.Key_Space:
            self.switchChartType()
        else:
            QGraphicsView.keyPressEvent(self, event)

    def switchChartType(self):
        oldChart = self.chart()

        if oldChart.chartType() == QChart.ChartTypeCartesian:
            newChart = QPolarChart()
        else:
            newChart = QChart()

        axisRanges = []

        # 将图表序列和轴从旧图表移动到新图表
        seriesList = oldChart.series()
        axisList = oldChart.axes()

        for axis in axisList:
            axisRanges.append(QPointF(axis.min(), axis.max()))

        for series in seriesList:
            oldChart.removeSeries(series)

        for axis in axisList:
            oldChart.removeAxis(axis)
            align = axis.alignment()
            # bug fix
            if oldChart.chartType() == QChart.ChartTypeCartesian:
                if align == Qt.AlignBottom:
                    align = QPolarChart.PolarOrientationAngular
                else:
                    align = QPolarChart.PolarOrientationRadial

            newChart.addAxis(axis, align)

        for series in seriesList:
            newChart.addSeries(series)
            for axis in axisList:
                series.attachAxis(axis)

        for index, axis in enumerate(axisList):
            axis.setRange(axisRanges[index].x(), axisRanges[index].y())

        newChart.setTitle(oldChart.title())
        self.setChart(newChart)
        del oldChart


class DemoPolarChart(QMainWindow):
    def __init__(self, parent=None):
        super(DemoPolarChart, self).__init__(parent)

        # 设置窗口标题
        self.setWindowTitle('实战 Qt for Python: 极坐标演示')
        # 设置窗口大小
        self.resize(640, 480)

        self.createChart()

    def createChart(self):

        angularMin = -100
        angularMax = 100
        radialMin = -100
        radialMax = 100

        series1 = QScatterSeries()
        series1.setName('散点图')
        for i in range(angularMin, angularMax, 10):
            series1.append(i, (i / radialMax) * radialMax + 8.0)

        series2 = QSplineSeries()
        series2.setName('样条曲线')
        for i in range(angularMin, angularMax, 10):
            series2.append(i, (i / radialMax) * radialMax)

        series3 = QLineSeries()
        series3.setName('星星外边界线')
        ad = (angularMax - angularMin) / 8
        rd = (radialMax - radialMin) / 3 * 1.3
        series3.append(angularMin, radialMax)
        series3.append(angularMin + ad * 1, radialMin + rd)
        series3.append(angularMin + ad * 2, radialMax)
        series3.append(angularMin + ad * 3, radialMin + rd)
        series3.append(angularMin + ad * 4, radialMax)
        series3.append(angularMin + ad * 5, radialMin + rd)
        series3.append(angularMin + ad * 6, radialMax)
        series3.append(angularMin + ad * 7, radialMin + rd)
        series3.append(angularMin + ad * 8, radialMax)

        series4 = QLineSeries()
        series4.setName('星星内边界线')
        ad = (angularMax - angularMin) / 8
        rd = (radialMax - radialMin) / 3
        series4.append(angularMin, radialMax)
        series4.append(angularMin + ad * 1, radialMin + rd)
        series4.append(angularMin + ad * 2, radialMax)
        series4.append(angularMin + ad * 3, radialMin + rd)
        series4.append(angularMin + ad * 4, radialMax)
        series4.append(angularMin + ad * 5, radialMin + rd)
        series4.append(angularMin + ad * 6, radialMax)
        series4.append(angularMin + ad * 7, radialMin + rd)
        series4.append(angularMin + ad * 8, radialMax)

        series5 = QAreaSeries()
        series5.setName('星星区域')
        series5.setUpperSeries(series3)
        series5.setLowerSeries(series4)
        series5.setOpacity(0.5)

        # 创建图表
        chart = QPolarChart()
        chart.addSeries(series1)
        chart.addSeries(series2)
        chart.addSeries(series3)
        chart.addSeries(series4)
        chart.addSeries(series5)
        chart.setTitle('使用箭头键可以滚动,使用+/-键可以缩放,使用空格键可以切换图表类型.')

        angularAxis = QValueAxis()
        angularAxis.setTickCount(9)  # 第一个和最后一个刻度在0/360角度上同一位置
        angularAxis.setLabelFormat('%.1f')
        angularAxis.setShadesVisible(True)
        angularAxis.setShadesBrush(QBrush(QColor(249, 249, 255)))
        chart.addAxis(angularAxis, QPolarChart.PolarOrientationAngular)

        radialAxis = QValueAxis()
        radialAxis.setTickCount(9)
        radialAxis.setLabelFormat('%d')
        chart.addAxis(radialAxis, QPolarChart.PolarOrientationRadial)

        series1.attachAxis(radialAxis)
        series1.attachAxis(angularAxis)
        series2.attachAxis(radialAxis)
        series2.attachAxis(angularAxis)
        series3.attachAxis(radialAxis)
        series3.attachAxis(angularAxis)
        series4.attachAxis(radialAxis)
        series4.attachAxis(angularAxis)
        series5.attachAxis(radialAxis)
        series5.attachAxis(angularAxis)

        radialAxis.setRange(radialMin, radialMax)
        angularAxis.setRange(angularMin, angularMax)

        # 图表视图
        chartView = MyChartView()
        chartView.setChart(chart)
        chartView.setRenderHint(QPainter.Antialiasing)

        self.setCentralWidget(chartView)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = DemoPolarChart()
    window.show()
    sys.exit(app.exec())