from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget

from FU功能测试.ScreenSwitch.UI.ui_log import Ui_LogScreen
from FU功能测试.ScreenSwitch.UI.ui_test import Ui_MainWindow


class GuiLog:

    def __init__(self, parent: QMainWindow):
        self._widget = QWidget(parent)
        self._widget.resize(1920, 1080)
        self._ui = Ui_LogScreen()
        self._ui.setupUi(self._widget)
        self.set_gui_hidden(is_hidden=False)

    def set_gui_hidden(self, is_hidden: bool):
        self._widget.hide() if is_hidden else self._widget.show()


class GuiTest:

    def __init__(self, parent: QMainWindow):
        self._widget = QWidget(parent)
        self._widget.resize(1920, 1080)
        self._ui = Ui_MainWindow()
        self._ui.setupUi(self._widget)
        self.set_gui_hidden(is_hidden=True)

    def set_gui_hidden(self, is_hidden: bool):
        self._widget.hide() if is_hidden else self._widget.show()


class Gui(QMainWindow):

    def __init__(self):
        super(Gui, self).__init__()
        self.resize(1920, 1080)
        self._test = GuiTest(parent=self)
        self._log = GuiLog(parent=self)
        self._timer = QTimer()
        self._timer.singleShot(2000, self._switch_gui)

    def _switch_gui(self):
        self._test.set_gui_hidden(is_hidden=False)
        self._log.set_gui_hidden(is_hidden=True)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    win = Gui()
    win.show()
    sys.exit(app.exec_())
