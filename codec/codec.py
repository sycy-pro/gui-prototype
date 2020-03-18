from PySide2.QtCore import QDir, Slot
from PySide2.QtWidgets import QMainWindow, QSizePolicy, QFileDialog

from pathlib import Path
from codec.decryptor import Decryptor
from codec.status_widget import StatusWidget
from ui import ui_codec


class Codec(QMainWindow):
    def __init__(self):
        super(Codec, self).__init__(None)
        self.ui = ui_codec.Ui_Codec()
        self.ui.setupUi(self)

        self.status_dump = StatusWidget(self)
        self.status_dump.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.ui.globalLayout.addWidget(self.status_dump)

        self.decryptor = Decryptor(self)
        self.decryptor.started.connect(self.action_started)
        self.decryptor.finished.connect(self.action_finished)

        self.ui.browseSource.clicked.connect(self.browse_source)
        self.ui.browseDestination.clicked.connect(self.browse_destination)

        self.ui.buttonAction.clicked.connect(self.action_button_clicked)
        self.performing_action = False

    def browse_source(self):
        source_file = QFileDialog.getOpenFileName(self, 'Open file',
                                                  QDir.homePath(),
                                                  'PDF files (*.pdf)')
        if len(source_file[0]) != 0:
            self.ui.editSource.setText(source_file[0])

    def browse_destination(self):
        dest_dir = QFileDialog.getExistingDirectory(self, 'Open directory',
                                                    QDir.homePath())
        if len(dest_dir) != 0:
            self.ui.editDestination.setText(dest_dir)

    @Slot(name='action_start')
    def action_started(self):
        self.ui.progressBar.setEnabled(True)
        self.ui.progressBar.setValue(0)
        self.ui.buttonAction.setText('Cancel')

    @Slot(name='action_finished')
    def action_finished(self):
        self.ui.buttonAction.setText('Start')

    def action_button_clicked(self):
        if self.decryptor.isRunning():
            self.decryptor.cancel()
        elif self.ui.actionDecrypt.isChecked():
            input_file = Path(self.ui.editSource.text())
            output_dir = Path(self.ui.editDestination.text())
            if not (input_file.is_file() and input_file.is_absolute()):
                raise RuntimeError('Input file is not a file or is not absolute')
            if not (output_dir.is_dir() and output_dir.is_absolute()):
                raise RuntimeError('Output directory is not a directory or is not absolute')

            self.decryptor.set_input_file(input_file)
            self.decryptor.set_output_dir(output_dir)
            self.decryptor.start()
        elif self.ui.actionEncrypt.isChecked():
            raise NotImplementedError('Encryption feature is not yet implemented')
