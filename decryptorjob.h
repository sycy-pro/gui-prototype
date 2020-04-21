#ifndef DECRYPTORJOB_H
#define DECRYPTORJOB_H

#include <QThread>
#include "statuslevel.h"

class DecryptorJob : public QThread
{
    Q_OBJECT

public:
    DecryptorJob();

    void setInputFile(const QString& inputFile);
    void setOutputDir(const QString& outputDir);

    void setAlphabetFlags(bool lower, bool upper, bool numbers, bool special, bool space, QString custom, bool order);

    void setKnownPassword(QString password);

    void run();
    void cancel();

private:
    // Paths
    QString inputFile;
    QString outputDir;

    // Cancel button pressed
    bool cancelRequest;

    // Progress of decryption
    int progress;

    // Known part of the password
    QString knownPassword;

    // TEA constants
    static constexpr int BLOCKLEN = 8;
    static constexpr int KEYLEN = 16;

    // PDF header pattern
    static constexpr uint32_t PDFHEADER = 0x46445025;

    // Alphabets
    static const char *A_LOWER;
    static const char *A_UPPER;
    static const char *A_NUMBERS;
    static const char *A_SPECIAL;
    QString A_CUSTOM;

    // Alphabet flags
    bool useLower;
    bool useUpper;
    bool useNumbers;
    bool useSpecial;
    bool useSpace;
    bool shuffle;

    void teaDecrypt(uint32_t v[BLOCKLEN / 4], uint32_t k[KEYLEN / 4]) const;
    bool bruteForcePassword(const char block[BLOCKLEN], char password[KEYLEN + 1]);

signals:
    void updateStatus(const QString& msg, StatusLevel lvl);
    void updateProgress(int progress);
};
#endif // DECRYPTORJOB_H
