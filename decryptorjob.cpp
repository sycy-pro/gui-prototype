#include "decryptorjob.h"

#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QtMath>
#include <algorithm>

const char *DecryptorJob::A_LOWER = "abcdefghijklmnopqrstuvwxyz";
const char *DecryptorJob::A_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *DecryptorJob::A_NUMBERS = "1234567890";
const char *DecryptorJob::A_SPECIAL = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

DecryptorJob::DecryptorJob() {}

void DecryptorJob::setInputFile(const QString& _inputFile) {
    inputFile = _inputFile;
}

void DecryptorJob::setOutputDir(const QString& _outputDir) {
    outputDir = _outputDir;
}

void DecryptorJob::setAlphabetFlags(bool lower, bool upper, bool numbers, bool special, bool space, QString custom, bool order) {
    useLower = lower;
    useUpper = upper;
    useNumbers = numbers;
    useSpecial = special;
    useSpace = space;
    A_CUSTOM = custom;
    shuffle = order;
}

void DecryptorJob::setKnownPassword(QString password) {
    knownPassword = password;
}

void DecryptorJob::cancel() {
    cancelRequest = true;
}

void DecryptorJob::run() {
    cancelRequest = false;
    progress = 0;
    updateStatus(tr("Decryption started"), StatusLevel::INFO);

    QFile input(inputFile);
    updateStatus(tr("Loading file..."), StatusLevel::DEBUG);
    if(!input.open(QFile::ReadOnly)) {
        updateStatus(tr("Couldn't open the file"), StatusLevel::ERROR);
        return;
    }
    updateStatus(tr("File loaded"), StatusLevel::SUCCESS);

    char buffer[BLOCKLEN];
    QDataStream stream(&input);

    // Get encrypted PDF header
    int read = stream.readRawData(buffer, BLOCKLEN);
    if(read != BLOCKLEN) {
        updateStatus(tr("File appears to be empty"), StatusLevel::ERROR);
        return;
    }

    QByteArray latinKnownPassword = knownPassword.toLatin1();
    char knownPasswordBuffer[KEYLEN + 1];
    memset(knownPasswordBuffer, 0, KEYLEN+1);
    strncpy(knownPasswordBuffer, latinKnownPassword.data(), KEYLEN);

    if(bruteForcePassword(buffer, knownPasswordBuffer)) {
        updateStatus(tr("Brute force successful"), StatusLevel::SUCCESS);
        updateStatus(tr("Password: ") + knownPasswordBuffer, StatusLevel::INFO);
    }
    else {
        updateStatus(tr("Brute force failed"), StatusLevel::ERROR);
        updateStatus(tr("Decryption aborted"), StatusLevel::ERROR);
        return;
    }

    updateStatus(tr("Decryption finished"), StatusLevel::SUCCESS);
}

void DecryptorJob::teaDecrypt(uint32_t v[2], uint32_t k[4]) const {
    constexpr uint32_t delta = 0x9E3779B9;

    for(uint32_t i = 0, sum = 0xC6EF3720; i < 32; ++i) {
        v[1] -= ((v[0] << 4) + k[2]) ^ (v[0] + sum) ^ ((v[0] >> 5) + k[3]);
        v[0] -= ((v[1] << 4) + k[0]) ^ (v[1] + sum) ^ ((v[1] >> 5) + k[1]);
        sum -= delta;
    }
}

bool DecryptorJob::bruteForcePassword(const char block[BLOCKLEN], char password[KEYLEN + 1])
{
    uint32_t v[BLOCKLEN / 4];  // Value
    uint32_t k[KEYLEN / 4];    // Key

    // Position of NULL terminator
    const int start = strlen(password);

    QByteArray latinCustom = A_CUSTOM.toLatin1();
    char *customAlphabet = latinCustom.data();

    char *alphabet;
    int ALEN = 1 + strlen(customAlphabet);

    updateStatus(tr("Generating alphabet:"), StatusLevel::INFO);
    if(useLower) {
        ALEN += strlen(A_LOWER);
        updateStatus(tr("Using lowercase letters"), StatusLevel::INFO);
    }
    if(useUpper) {
        ALEN += strlen(A_UPPER);
        updateStatus(tr("Using uppercase letters"), StatusLevel::INFO);
    }
    if(useNumbers) {
        ALEN += strlen(A_NUMBERS);
        updateStatus(tr("Using numbers"), StatusLevel::INFO);
    }
    if(useSpecial) {
        ALEN += strlen(A_SPECIAL);
        updateStatus(tr("Using special characters"), StatusLevel::INFO);
    }
    if(useSpace) {
        ALEN += 1;
        updateStatus(tr("Using space character"), StatusLevel::INFO);
    }

    alphabet = (char*) malloc(ALEN);
    memset(alphabet, 0x00, ALEN);

    if(strlen(customAlphabet) != 0) {
        strcat(alphabet, customAlphabet);
        updateStatus(tr("Using custom characters: ") + A_CUSTOM, StatusLevel::INFO);
    }
    if(useLower)    strcat(alphabet, A_LOWER);
    if(useUpper)    strcat(alphabet, A_UPPER);
    if(useNumbers)  strcat(alphabet, A_NUMBERS);
    if(useSpecial)  strcat(alphabet, A_SPECIAL);
    if(useSpace)    strcat(alphabet, " ");

    if(shuffle) {
        updateStatus(tr("Shuffling generated alphabet"), StatusLevel::INFO);
        std::random_shuffle(alphabet, alphabet + ALEN);
    }

    // Setup index table
    int idx[KEYLEN + 1];
    memset(idx, 0x00, sizeof(int) * (KEYLEN + 1));

    const unsigned long long cycles = pow(ALEN, KEYLEN - start);
    const unsigned long long updateStep = cycles / 400;
    unsigned long long tries = 0;

    bool success = false;

    do {
        memcpy(k, password, KEYLEN);
        memcpy(v, block, BLOCKLEN);
        teaDecrypt(v, k);

        if(v[0] == PDFHEADER) {
            memcpy(password, k, KEYLEN);
            success = true;
            break;
        }

        if(cancelRequest)
            break;

        for(int i = start; i < KEYLEN; ++i) {
            if(idx[i] == ALEN) {
                idx[i] = 0;
                idx[i+1] += 1;
            }

            password[i] = alphabet[idx[i]];
        }

        idx[start] += 1;

        if(++tries % updateStep == 0) {
            double progress = (tries / (double)cycles) * 100.0;
            QString statusMsg = QString("%1 / %2 (%3%) --- %4").arg(tries).arg(cycles).arg(progress, 0, 'g', 2).arg(password);
            updateStatus(statusMsg, StatusLevel::INFO);
            updateProgress(progress = (int)progress);
        }

    } while(!idx[KEYLEN]);

    updateProgress(progress = 100);
    free(alphabet);

    return success;
}
