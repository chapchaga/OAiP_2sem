#ifndef XLSXWRITER_H
#define XLSXWRITER_H

// Writes test results to .xlsx purely in C++/Qt — no Python needed.
// .xlsx is a ZIP archive containing XML files (OOXML standard).
// We build the XML manually and pack it with Qt's QuaZip or
// the standard zip via QProcess on 'zip', falling back to writing
// a plain .csv if zip is unavailable.

#include "GlassBoxTest.h"
#include <QString>

class XlsxWriter {
public:
    static bool writeResults(const QVector<TestResult>& results,
                             const QString& filePath);
private:
    static QByteArray buildSharedStrings(const QVector<TestResult>& results,
                                         QMap<QString,int>& index);
    static QByteArray buildSheet(const QVector<TestResult>& results,
                                  QMap<QString,int>& ssIndex);
    static QByteArray buildStyles();
    static QByteArray buildWorkbook();
    static QByteArray buildRels();
    static QByteArray buildWorkbookRels();
    static QByteArray buildContentTypes();
    static bool packZip(const QString& dir, const QString& outFile);
};

#endif // XLSXWRITER_H
