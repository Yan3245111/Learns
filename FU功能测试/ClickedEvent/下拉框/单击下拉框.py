import sys
from PyQt5.QtWidgets import QMenuBar, QAction, QMainWindow, QApplication


class Gui(QMainWindow):

    def __init__(self):
        super().__init__()
        self._menu = QMenuBar(self)
        self._menu.resize(65, 25)
        self._menu.move(50, 50)
        self._signal = self._menu.addMenu("基带调制")
        self._signal.addAction("Hello")
        self._signal.addAction("Hello1")
        self._menu1 = self._signal.addMenu("MENU1")
        self._menu1.addAction("Haha")
        self._menu1.addAction("Haha1")
        self._action = QAction("wa", self)
        self._action.setShortcut("Ctrl+S")
        self._signal.addAction(self._action)
        self._signal.triggered[QAction].connect(self._signal_checked)

        self._menu1 = QMenuBar(self)
        self._menu1.resize(65, 25)
        self._menu1.move(100, 50)
        self._signal2 = self._menu1.addMenu("hhhhh")
        self._signal2.addAction("wwwwww")

    def _signal_checked(self, action: QAction):
        print(action.text())
        if action.text() == "Hello":
            print(1)
            # Change Window


if __name__ == '__main__':
    app = QApplication(sys.argv)
    gui = Gui()
    gui.show()
    app.exec_()
