from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QMainWindow, QApplication

from FU功能测试.ScreenChange.UI.ui_log import Ui_LogScreen
from FU功能测试.ScreenChange.UI.ui_test import Ui_MainWindow


class Window1(QMainWindow):

    def __init__(self):
        super().__init__()
        self._ui = Ui_MainWindow()
        self._ui.setupUi(self)


class Gui(QMainWindow):

    def __init__(self):
        super().__init__()
        self._win = Window1()
        self._ui = Ui_LogScreen()
        self._ui.setupUi(self)
        self.show()
        self._timer = QTimer()
        self._timer.setSingleShot(True)
        self._timer.singleShot(5000, self._launch)
        self._timer.start()

    def _launch(self):
        self.hide()
        self._win.show()


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    win = Gui()
    win.show()
    sys.exit(app.exec_())
