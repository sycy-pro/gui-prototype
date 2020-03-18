from PySide2.QtCore import Slot
from PySide2.QtWidgets import QTextBrowser


class StatusWidget(QTextBrowser):
    _debug_prefix = '<span style="color: #88498f">[&lt;/&gt;]</span>'
    _info_prefix = '<span style="color: #6a8db7">[*]</span>'
    _success_prefix = '<span style="color: #8fe07b">[+]</span>'
    _warning_prefix = '<span style="color: #ff9900">[!]</span>'
    _fail_prefix = '<span style="color: #ff6542">[-]</span>'

    def __init__(self, parent):
        super(StatusWidget, self).__init__(parent)
        self.setStyleSheet('* { font-family: "Noto Sans Mono"; }')

    def _dump(self, msg_type: str, msg: str):
        prefixes = {
            'debug': StatusWidget._debug_prefix,
            'info': StatusWidget._info_prefix,
            'success': StatusWidget._success_prefix,
            'warning': StatusWidget._warning_prefix,
            'fail': StatusWidget._fail_prefix
        }

        self.insertHtml(prefixes[msg_type] + ' ' + msg + '<br />')
        self.ensureCursorVisible()

    @Slot(str, name='debug')
    def debug(self, msg: str):
        self._dump('debug', msg)

    @Slot(str, name='info')
    def info(self, msg: str):
        self._dump('info', msg)

    @Slot(str, name='success')
    def success(self, msg: str):
        self._dump('success', msg)

    @Slot(str, name='warning')
    def warning(self, msg: str):
        self._dump('warning', msg)

    @Slot(str, name='fail')
    def fail(self, msg: str):
        self._dump('fail', msg)