import sys

from PySide2.QtWidgets import QApplication
from codec import codec

if __name__ == '__main__':
    app = QApplication()
    window = codec.Codec()
    window.show()
    sys.exit(app.exec_())
