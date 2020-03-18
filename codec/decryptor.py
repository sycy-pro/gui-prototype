from PySide2.QtCore import QThread, Signal, QObject


class _DecryptorSignals(QObject):
    sig_status_debug = Signal(str)
    sig_status_info = Signal(str)
    sig_status_success = Signal(str)
    sig_status_warning = Signal(str)
    sig_status_fail = Signal(str)
    sig_progress_update = Signal(int)


class Decryptor(QThread):
    def __init__(self, parent):
        super(Decryptor, self).__init__(parent)
        self._input_file = None
        self._output_dir = None

        self.signals = _DecryptorSignals()

        self.signals.sig_status_debug.connect(parent.status_dump.debug)
        self.signals.sig_status_info.connect(parent.status_dump.info)
        self.signals.sig_status_success.connect(parent.status_dump.success)
        self.signals.sig_status_warning.connect(parent.status_dump.warning)
        self.signals.sig_status_fail.connect(parent.status_dump.fail)
        self.signals.sig_progress_update.connect(parent.ui.progressBar.setValue)

        self._cancel_requested = False

    def set_input_file(self, input_file: str):
        self._input_file = input_file

    def set_output_dir(self, output_dir: str):
        self._output_dir = output_dir

    def cancel(self):
        self._cancel_requested = True

    def run(self):
        if self._input_file is None or self._output_dir is None:
            raise RuntimeError('Input file or output dir not specified')

        self.signals.sig_status_debug.emit('--- Module started ---')
        self.signals.sig_status_info.emit('Input file is: %s' % self._input_file)
        self.signals.sig_status_info.emit('Output dir is: %s' % self._output_dir)
        self.signals.sig_status_debug.emit('--- Decryption started ---')

        for i in range(1, 101):
            if self._cancel_requested:
                self._cancel_requested = False
                return
            if i % 10 == 0:
                self.signals.sig_status_info.emit('{}% progress'.format(i))
            self.signals.sig_progress_update.emit(i)
            self.msleep(50)

        self.signals.sig_status_success.emit('Decryption successful')
