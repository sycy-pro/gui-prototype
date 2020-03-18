# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'codecfTWUab.ui'
##
## Created by: Qt User Interface Compiler version 5.14.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide2.QtCore import (QCoreApplication, QMetaObject, QObject, QPoint,
    QRect, QSize, QUrl, Qt)
from PySide2.QtGui import (QBrush, QColor, QConicalGradient, QCursor, QFont,
    QFontDatabase, QIcon, QLinearGradient, QPalette, QPainter, QPixmap,
    QRadialGradient)
from PySide2.QtWidgets import *


class Ui_Codec(object):
    def setupUi(self, Codec):
        if Codec.objectName():
            Codec.setObjectName(u"Codec")
        Codec.resize(600, 450)
        self.centralwidget = QWidget(Codec)
        self.centralwidget.setObjectName(u"centralwidget")
        self.globalLayout = QVBoxLayout(self.centralwidget)
        self.globalLayout.setObjectName(u"globalLayout")
        self.layout1 = QHBoxLayout()
        self.layout1.setObjectName(u"layout1")
        self.actionsGroupBox = QGroupBox(self.centralwidget)
        self.actionsGroupBox.setObjectName(u"actionsGroupBox")
        self.verticalLayout = QVBoxLayout(self.actionsGroupBox)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.actionEncrypt = QRadioButton(self.actionsGroupBox)
        self.actionsButtonGroup = QButtonGroup(Codec)
        self.actionsButtonGroup.setObjectName(u"actionsButtonGroup")
        self.actionsButtonGroup.addButton(self.actionEncrypt)
        self.actionEncrypt.setObjectName(u"actionEncrypt")

        self.verticalLayout.addWidget(self.actionEncrypt)

        self.actionDecrypt = QRadioButton(self.actionsGroupBox)
        self.actionsButtonGroup.addButton(self.actionDecrypt)
        self.actionDecrypt.setObjectName(u"actionDecrypt")
        self.actionDecrypt.setChecked(True)

        self.verticalLayout.addWidget(self.actionDecrypt)


        self.layout1.addWidget(self.actionsGroupBox)

        self.filesGroupBox = QGroupBox(self.centralwidget)
        self.filesGroupBox.setObjectName(u"filesGroupBox")
        self.gridLayout = QGridLayout(self.filesGroupBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.labelDestination = QLabel(self.filesGroupBox)
        self.labelDestination.setObjectName(u"labelDestination")

        self.gridLayout.addWidget(self.labelDestination, 1, 0, 1, 1)

        self.editSource = QLineEdit(self.filesGroupBox)
        self.editSource.setObjectName(u"editSource")

        self.gridLayout.addWidget(self.editSource, 0, 1, 1, 1)

        self.browseDestination = QPushButton(self.filesGroupBox)
        self.browseDestination.setObjectName(u"browseDestination")
        icon = QIcon()
        icon.addFile(u"../../downloads/dir.png", QSize(), QIcon.Normal, QIcon.Off)
        self.browseDestination.setIcon(icon)

        self.gridLayout.addWidget(self.browseDestination, 1, 2, 1, 1)

        self.labelSource = QLabel(self.filesGroupBox)
        self.labelSource.setObjectName(u"labelSource")

        self.gridLayout.addWidget(self.labelSource, 0, 0, 1, 1)

        self.browseSource = QPushButton(self.filesGroupBox)
        self.browseSource.setObjectName(u"browseSource")
        icon1 = QIcon()
        icon1.addFile(u"../../downloads/file.svg", QSize(), QIcon.Normal, QIcon.Off)
        self.browseSource.setIcon(icon1)

        self.gridLayout.addWidget(self.browseSource, 0, 2, 1, 1)

        self.editDestination = QLineEdit(self.filesGroupBox)
        self.editDestination.setObjectName(u"editDestination")

        self.gridLayout.addWidget(self.editDestination, 1, 1, 1, 1)


        self.layout1.addWidget(self.filesGroupBox)


        self.globalLayout.addLayout(self.layout1)

        self.layout2 = QHBoxLayout()
        self.layout2.setObjectName(u"layout2")
        self.buttonAction = QPushButton(self.centralwidget)
        self.buttonAction.setObjectName(u"buttonAction")

        self.layout2.addWidget(self.buttonAction)

        self.progressBar = QProgressBar(self.centralwidget)
        self.progressBar.setObjectName(u"progressBar")
        self.progressBar.setEnabled(False)
        self.progressBar.setValue(0)

        self.layout2.addWidget(self.progressBar)


        self.globalLayout.addLayout(self.layout2)

        Codec.setCentralWidget(self.centralwidget)
        self.statusbar = QStatusBar(Codec)
        self.statusbar.setObjectName(u"statusbar")
        Codec.setStatusBar(self.statusbar)
#if QT_CONFIG(shortcut)
        self.labelDestination.setBuddy(self.editDestination)
        self.labelSource.setBuddy(self.editSource)
#endif // QT_CONFIG(shortcut)
        QWidget.setTabOrder(self.actionEncrypt, self.actionDecrypt)
        QWidget.setTabOrder(self.actionDecrypt, self.editSource)
        QWidget.setTabOrder(self.editSource, self.browseSource)
        QWidget.setTabOrder(self.browseSource, self.editDestination)
        QWidget.setTabOrder(self.editDestination, self.browseDestination)
        QWidget.setTabOrder(self.browseDestination, self.buttonAction)

        self.retranslateUi(Codec)

        QMetaObject.connectSlotsByName(Codec)
    # setupUi

    def retranslateUi(self, Codec):
        Codec.setWindowTitle(QCoreApplication.translate("Codec", u"SYCY Codec", None))
        self.actionsGroupBox.setTitle(QCoreApplication.translate("Codec", u"Actions", None))
        self.actionEncrypt.setText(QCoreApplication.translate("Codec", u"Encrypt", None))
        self.actionDecrypt.setText(QCoreApplication.translate("Codec", u"Decrypt", None))
        self.filesGroupBox.setTitle(QCoreApplication.translate("Codec", u"Files", None))
        self.labelDestination.setText(QCoreApplication.translate("Codec", u"Destination", None))
#if QT_CONFIG(tooltip)
        self.editSource.setToolTip(QCoreApplication.translate("Codec", u"This should be an absolute path", None))
#endif // QT_CONFIG(tooltip)
        self.editSource.setPlaceholderText(QCoreApplication.translate("Codec", u"Source file path", None))
#if QT_CONFIG(tooltip)
        self.browseDestination.setToolTip(QCoreApplication.translate("Codec", u"Browse directories", None))
#endif // QT_CONFIG(tooltip)
        self.browseDestination.setText("")
        self.labelSource.setText(QCoreApplication.translate("Codec", u"Source", None))
#if QT_CONFIG(tooltip)
        self.browseSource.setToolTip(QCoreApplication.translate("Codec", u"Browse files", None))
#endif // QT_CONFIG(tooltip)
        self.browseSource.setText("")
#if QT_CONFIG(tooltip)
        self.editDestination.setToolTip(QCoreApplication.translate("Codec", u"This should be an absolute path", None))
#endif // QT_CONFIG(tooltip)
        self.editDestination.setPlaceholderText(QCoreApplication.translate("Codec", u"Destination directory", None))
        self.buttonAction.setText(QCoreApplication.translate("Codec", u"Start", None))
    # retranslateUi

