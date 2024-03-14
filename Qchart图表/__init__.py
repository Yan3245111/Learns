from PyQt5 import QtWidgets, QtCore
from pyqtgraph import PlotWidget, plot
import pyqtgraph as pg
import sys  # We need sys so that we can pass argv to QApplication
import os
from random import randint

# image = np.random.normal(size=(500, 400))
# plt1 = pg.PlotWidget()
# plt1_imageitem = pg.ImageItem(image)
# plt1.addItem(plt1_imageitem)
# roi_circle = pg.CircleROI([250, 250], [120, 120], pen=pg.mkPen('r',width=2))
# # roi_circle.sigRegionChanged.connect(circle_update)
# plt1.addItem(roi_circle)
# plt1.show()

# if __name__ == '__main__':
#     # pyqtgraph.examples.run()
#     pg.mkQApp().exec_()  # 执行函数
# from PyQt5 import QtWidgets, QtCore
# from pyqtgraph import PlotWidget, plot
# import pyqtgraph as pg
# import sys  # We need sys so that we can pass argv to QApplication
# import os
# from random import randint


class MainWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        self.graphWidget = pg.PlotWidget()
        self.setCentralWidget(self.graphWidget)
        roi_circle = pg.CircleROI([250, 250], [120, 120], pen=pg.mkPen('r', width=2))
        self.graphWidget.addItem(roi_circle)

        self.x = list(range(100))  # 100 time points
        self.y = [randint(0, 100) for _ in range(100)]  # 100 data points

        self.graphWidget.setBackground('w')

        pen = pg.mkPen(color=(255, 0, 0))
        self.data_line = self.graphWidget.plot(self.x, self.y, pen=pen)

        self.timer = QtCore.QTimer()
        self.timer.setInterval(50)
        self.timer.timeout.connect(self.update_plot_data)
        self.timer.start()

    def update_plot_data(self):
        self.x = self.x[1:]  # Remove the first y element.
        self.x.append(self.x[-1] + 1)  # Add a new value 1 higher than the last.

        self.y = self.y[1:]  # Remove the first
        self.y.append(randint(0, 100))  # Add a new random value.

        self.data_line.setData(self.x, self.y)  # Update the data.


app = QtWidgets.QApplication(sys.argv)
w = MainWindow()
w.show()
sys.exit(app.exec_())
