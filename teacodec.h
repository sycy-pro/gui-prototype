#ifndef TEACODEC_H
#define TEACODEC_H

#include <QWidget>
#include "decryptorjob.h"
#include "statuslevel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TeaCodec; }
QT_END_NAMESPACE

class TeaCodec : public QWidget
{
    Q_OBJECT

public:
    TeaCodec(QWidget *parent = nullptr);
    ~TeaCodec();

private:
    Ui::TeaCodec *ui;

    DecryptorJob *decryptor;

    // Decryption handling
    bool isDecrypting;
    void actionButtonPressed();

    // File dialogs
    void browseSourceDialog();
    void browseDestinationDialog();

    // Status message formatting
    QString formatStatus(const QString& msg, StatusLevel lvl) const;

public slots:
    void dumpStatus(const QString& msg, StatusLevel lvl);

    void decryptionStarted();
    void decryptionFinished();
};
#endif // TEACODEC_H
