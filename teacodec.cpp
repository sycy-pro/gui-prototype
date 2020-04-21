#include "teacodec.h"
#include "ui_teacodec.h"

#include <QDebug>
#include <QFileDialog>

TeaCodec::TeaCodec(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TeaCodec)
{
    ui->setupUi(this);

    // Dialogs for input and output files
    connect(ui->buttonBrowseSource, &QPushButton::clicked, this, &TeaCodec::browseSourceDialog);
    connect(ui->buttonBrowseDestination, &QPushButton::clicked, this, &TeaCodec::browseDestinationDialog);

    // Action button
    connect(ui->buttonAction, &QPushButton::clicked, this, &TeaCodec::actionButtonPressed);

    // Decryptor
    decryptor = new DecryptorJob();
    connect(decryptor, &DecryptorJob::updateProgress, ui->progressBar, &QProgressBar::setValue);
    connect(decryptor, &DecryptorJob::updateStatus, this, &TeaCodec::dumpStatus);
    connect(decryptor, &DecryptorJob::started, this, &TeaCodec::decryptionStarted);
    connect(decryptor, &DecryptorJob::finished, this, &TeaCodec::decryptionFinished);
    isDecrypting = false;

    // Clear status button
    connect(ui->buttonClearStatus, &QPushButton::clicked, ui->statusDump, &QTextBrowser::clear);
}

TeaCodec::~TeaCodec()
{
    delete ui;
}

void TeaCodec::actionButtonPressed()
{
    if(!isDecrypting) {
        decryptor->setInputFile(ui->editSource->text());
        decryptor->setOutputDir(ui->editDestination->text());
        decryptor->setAlphabetFlags(ui->checkBoxLowercase->isChecked(), ui->checkBoxUppercase->isChecked(),
                                    ui->checkBoxNumbers->isChecked(), ui->checkBoxSpecial->isChecked(),
                                    ui->checkBoxSpace->isChecked(), ui->editCustomAlphabet->text(),
                                    ui->radioShuffle->isChecked());
        decryptor->setKnownPassword(ui->editKnownKey->text());
        decryptor->start();
    }
    else {
        decryptor->cancel();
    }
}

void TeaCodec::browseSourceDialog()
{
    QString sourceFile = QFileDialog::getOpenFileName(this, tr("Open encrypted PDF file"),
                                                      QDir::homePath(), tr("PDF files (*.pdf)"));

    if(sourceFile.size() != 0) {
        ui->editSource->setText(sourceFile);
        dumpStatus(tr("Selected encrypted PDF file: ") + sourceFile, StatusLevel::INFO);
    }
}

void TeaCodec::browseDestinationDialog()
{
    QString destinationDir = QFileDialog::getExistingDirectory(this, tr("Open destination directory"),
                                                               QDir::homePath());

    if(destinationDir.size() != 0) {
        ui->editDestination->setText(destinationDir);
        dumpStatus(tr("Selected output directory: ") + destinationDir, StatusLevel::INFO);
    }
}

QString TeaCodec::formatStatus(const QString& msg, StatusLevel lvl) const
{
    QString out = "<span style='color: %1'>[%2]</span> %3<br />";

    switch(lvl) {
    case StatusLevel::DEBUG:
        out = out.arg("#88498f").arg('#').arg(msg);
        break;
    case StatusLevel::INFO:
        out = out.arg("#6a8db7").arg('*').arg(msg);
        break;
    case StatusLevel::WARNING:
        out = out.arg("#ff9900").arg('!').arg(msg);
        break;
    case StatusLevel::ERROR:
        out = out.arg("#ff6542").arg('-').arg(msg);
        break;
    case StatusLevel::SUCCESS:
        out = out.arg("#8fe07b").arg('+').arg(msg);
        break;
    default:
        out = "";
    }

    return out;
}

void TeaCodec::dumpStatus(const QString &msg, StatusLevel lvl)
{
    QString level = ui->comboBoxStatusLevel->currentText();
    StatusLevel sl;
    if(level == "Debug") sl = StatusLevel::DEBUG;
    else if(level == "Info") sl = StatusLevel::INFO;
    else sl = StatusLevel::WARNING;

    if(sl <= lvl) {
        ui->statusDump->insertHtml(formatStatus(msg, lvl));
        ui->statusDump->ensureCursorVisible();
    }
}

void TeaCodec::decryptionStarted()
{
    ui->progressBar->setEnabled(true);
    ui->progressBar->setValue(0);
    ui->buttonAction->setText(tr("Cancel"));
    isDecrypting = true;
}

void TeaCodec::decryptionFinished()
{
    ui->progressBar->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->buttonAction->setText(tr("Decrypt"));
    isDecrypting = false;
}

