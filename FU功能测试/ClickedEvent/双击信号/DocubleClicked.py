import sys
from PyQt5 import QtGui
from PyQt5.QtWidgets import QPushButton, QMainWindow, QApplication, QLabel


class OneLabel(QLabel):

    def __init__(self, parent: QMainWindow):
        super().__init__(parent)
        self.setParent(parent)

    def mouseDoubleClickEvent(self, a0: QtGui.QMouseEvent) -> None:
        print("Label Double Clicked")


class OnePushbutton(QPushButton):

    def __init__(self, parent: QMainWindow):
        super().__init__(parent)
        self.setParent(parent)

    def mouseDoubleClickEvent(self, a0: QtGui.QMouseEvent) -> None:
        print("Push Button Double Clicked")


class Gui(QMainWindow):

    def __init__(self):
        super().__init__()
        # self._label = OneLabel(parent=self)
        # self._label.move(100, 50)
        # self._label.resize(100, 50)
        # self._label.setText("Hello")

        self._btn = OnePushbutton(parent=self)
        self._btn.setText("双击")
        self._btn.resize(100, 50)
        self._btn.move(100, 50)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = Gui()
    gui.show()
    app.exec_()
