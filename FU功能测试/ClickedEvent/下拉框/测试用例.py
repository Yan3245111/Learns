# QMenuBar/QMenu/QAction的使用(菜单栏）
from PyQt5.QtWidgets import QMenuBar, QMenu, QAction, QLineEdit, QStyle, QFormLayout, QVBoxLayout, QWidget, \
    QApplication, QHBoxLayout, QPushButton, QMainWindow, QGridLayout, QLabel
from PyQt5.QtCore import QDir
from PyQt5.QtGui import QIcon, QPixmap, QFont
from PyQt5.QtCore import QDate

import sys


class WindowClass(QMainWindow):

    def __init__(self, parent=None):
        super(WindowClass, self).__init__(parent)
        self.menubar = self.menuBar()  # 获取窗体的菜单栏

        self.file = self.menubar.addMenu("系统菜单")
        self.file.addAction("New File")

        self.save = QAction("Save", self)
        self.save.setShortcut("Ctrl+S")  # 设置快捷键
        self.file.addAction(self.save)

        self.edit = self.file.addMenu("Edit")
        self.edit.addAction("copy")  # Edit下这是copy子项
        self.edit.addAction("paste")  # Edit下设置paste子项

        self.quit = QAction("Quit", self)  # 注意如果改为：self.file.addMenu("Quit") 则表示该菜单下必须柚子菜单项；会有>箭头
        self.file.addAction(self.quit)
        self.file.triggered[QAction].connect(self.processtrigger)
        self.setWindowTitle("Menu Demo")

    def processtrigger(self, qaction):
        print(qaction.text() + " is triggered!")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    win = WindowClass()
    win.show()
    sys.exit(app.exec_())
