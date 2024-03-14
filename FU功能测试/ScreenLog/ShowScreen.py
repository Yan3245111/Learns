from PyQt5.QtWidgets import QMainWindow, QApplication

from FU功能测试.ScreenLog.UI.ui_log import Ui_LogScreen


class Gui(QMainWindow):

    def __init__(self):
        super(Gui, self).__init__()
        self._ui = Ui_LogScreen()
        self._ui.setupUi(self)


if __name__ == '__main__':
    import sys
    app = QApplication(sys.argv)
    win = Gui()
    win.show()
    sys.exit(app.exec_())
