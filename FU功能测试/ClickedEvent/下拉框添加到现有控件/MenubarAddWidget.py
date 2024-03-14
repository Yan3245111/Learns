import sys
from PyQt5.QtWidgets import QMenuBar, QAction, QMainWindow, QApplication

from FU功能测试.ClickedEvent.下拉框添加到现有控件.UI.UI import Ui_MainWindow


class Gui(QMainWindow):

    def __init__(self):
        super().__init__()
        self._ui = Ui_MainWindow()
        self._ui.setupUi(self)
        self._signal = self._ui.menubar.addMenu("基带调制")
        self._signal.addAction("信号1")
        self._signal.addAction("信号2")
        self._ui.menubar.setStyleSheet("QMenuBar {text-align: center;}")


if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = Gui()
    gui.show()
    app.exec_()
