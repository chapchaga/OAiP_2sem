#include "XlsxWriter.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QMap>
#include <QDateTime>

// ---------------------------------------------------------------
// Escape XML special characters
// ---------------------------------------------------------------
static QString xmlEsc(const QString& s) {
    QString r = s;
    r.replace("&",  "&amp;");
    r.replace("<",  "&lt;");
    r.replace(">",  "&gt;");
    r.replace("\"", "&quot;");
    r.replace("'",  "&apos;");
    return r;
}

// ---------------------------------------------------------------
// Write a file inside the temp directory
// ---------------------------------------------------------------
static bool writeFile(const QString& path, const QByteArray& data) {
    QFile f(path);
    QDir().mkpath(QFileInfo(path).absolutePath());
    if (!f.open(QIODevice::WriteOnly)) return false;
    f.write(data);
    f.close();
    return true;
}

// ---------------------------------------------------------------
// [Content_Types].xml
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildContentTypes() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
        "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
        "<Default Extension=\"xml\"  ContentType=\"application/xml\"/>"
        "<Override PartName=\"/xl/workbook.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>"
        "<Override PartName=\"/xl/worksheets/sheet1.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>"
        "<Override PartName=\"/xl/sharedStrings.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sharedStrings+xml\"/>"
        "<Override PartName=\"/xl/styles.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>"
        "</Types>\n"
    );
}

// ---------------------------------------------------------------
// _rels/.rels
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildRels() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
        "<Relationship Id=\"rId1\""
        " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\""
        " Target=\"xl/workbook.xml\"/>"
        "</Relationships>\n"
    );
}

// ---------------------------------------------------------------
// xl/_rels/workbook.xml.rels
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildWorkbookRels() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
        "<Relationship Id=\"rId1\""
        " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\""
        " Target=\"worksheets/sheet1.xml\"/>"
        "<Relationship Id=\"rId2\""
        " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings\""
        " Target=\"sharedStrings.xml\"/>"
        "<Relationship Id=\"rId3\""
        " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\""
        " Target=\"styles.xml\"/>"
        "</Relationships>\n"
    );
}

// ---------------------------------------------------------------
// xl/workbook.xml
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildWorkbook() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
        " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
        "<sheets>"
        "<sheet name=\"Glass Box Tests\" sheetId=\"1\" r:id=\"rId1\"/>"
        "</sheets>"
        "</workbook>\n"
    );
}

// ---------------------------------------------------------------
// xl/styles.xml
// Style index map:
//   0 = default
//   1 = bold white on blue  (header)
//   2 = green fill          (ok row)
//   3 = red fill            (fail row)
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildStyles() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<styleSheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"

        // Fonts: 0=normal, 1=bold white
        "<fonts count=\"2\">"
        "<font><sz val=\"11\"/><name val=\"Calibri\"/></font>"
        "<font><b/><color rgb=\"FFFFFFFF\"/><sz val=\"11\"/><name val=\"Calibri\"/></font>"
        "</fonts>"

        // Fills: 0=none, 1=gray(unused), 2=blue header, 3=green ok, 4=red fail
        "<fills count=\"5\">"
        "<fill><patternFill patternType=\"none\"/></fill>"
        "<fill><patternFill patternType=\"gray125\"/></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FF2E75B6\"/></patternFill></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FFC6EFCE\"/></patternFill></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FFFF4444\"/></patternFill></fill>"
        "</fills>"

        // Borders: 0=none
        "<borders count=\"1\">"
        "<border><left/><right/><top/><bottom/><diagonal/></border>"
        "</borders>"

        // CellStyleXfs
        "<cellStyleXfs count=\"1\">"
        "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\"/>"
        "</cellStyleXfs>"

        // CellXfs: 0=normal, 1=header(bold white/blue), 2=ok(green), 3=fail(red)
        "<cellXfs count=\"4\">"
        "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\" xfId=\"0\"/>"
        "<xf numFmtId=\"0\" fontId=\"1\" fillId=\"2\" borderId=\"0\" xfId=\"0\" applyFont=\"1\" applyFill=\"1\"/>"
        "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"3\" borderId=\"0\" xfId=\"0\" applyFill=\"1\"/>"
        "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"4\" borderId=\"0\" xfId=\"0\" applyFill=\"1\"/>"
        "</cellXfs>"

        "</styleSheet>\n"
    );
}

// ---------------------------------------------------------------
// xl/sharedStrings.xml  — collect all unique strings
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildSharedStrings(const QVector<TestResult>& results,
                                            QMap<QString,int>& idx) {
    // Collect in order: headers first, then data
    QStringList ordered;
    auto addStr = [&](const QString& s) {
        if (!idx.contains(s)) { idx[s] = ordered.size(); ordered.append(s); }
    };
    addStr("Тест"); addStr("Эталон (правильный ответ)"); addStr("ok?");
    for (const TestResult& r : results) {
        addStr(r.testName);
        addStr(r.expected);
        addStr(r.passed ? QString("ok") : QString("fail"));
    }

    QString xml = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
                  "<sst xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
                  " count=\"" + QString::number(ordered.size()) + "\""
                  " uniqueCount=\"" + QString::number(ordered.size()) + "\">";
    for (const QString& s : ordered)
        xml += "<si><t xml:space=\"preserve\">" + xmlEsc(s) + "</t></si>";
    xml += "</sst>\n";
    return xml.toUtf8();
}

// ---------------------------------------------------------------
// xl/worksheets/sheet1.xml
// ---------------------------------------------------------------
QByteArray XlsxWriter::buildSheet(const QVector<TestResult>& results,
                                   QMap<QString,int>& ssIndex) {
    // Column letters
    auto col = [](int c) -> QString {
        return QString(QChar('A' + c));
    };
    // Shared-string cell: <c r="A1" t="s" s=styleIdx><v>ssIdx</v></c>
    auto ssCell = [&](int row, int colIdx, const QString& text, int style) -> QString {
        int si = ssIndex.value(text, 0);
        return QString("<c r=\"%1%2\" t=\"s\" s=\"%3\"><v>%4</v></c>")
            .arg(col(colIdx)).arg(row).arg(style).arg(si);
    };

    QString xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
        "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"
        "<sheetView workbookViewId=\"0\"><selection activeCell=\"A1\"/></sheetView>"
        // Column widths
        "<cols>"
        "<col min=\"1\" max=\"1\" width=\"40\" customWidth=\"1\"/>"
        "<col min=\"2\" max=\"2\" width=\"30\" customWidth=\"1\"/>"
        "<col min=\"3\" max=\"3\" width=\"10\" customWidth=\"1\"/>"
        "</cols>"
        "<sheetData>";

    // Header row (style 1 = bold blue)
    xml += "<row r=\"1\">";
    xml += ssCell(1, 0, "Тест", 1);
    xml += ssCell(1, 1, "Эталон (правильный ответ)", 1);
    xml += ssCell(1, 2, "ok?", 1);
    xml += "</row>";

    // Data rows
    for (int i = 0; i < results.size(); i++) {
        int row = i + 2;
        const TestResult& r = results[i];
        int style = r.passed ? 2 : 3;   // 2=green, 3=red
        QString status = r.passed ? "ok" : "fail";
        xml += QString("<row r=\"%1\">").arg(row);
        xml += ssCell(row, 0, r.testName, style);
        xml += ssCell(row, 1, r.expected, style);
        xml += ssCell(row, 2, status,     style);
        xml += "</row>";
    }

    xml += "</sheetData></worksheet>\n";
    return xml.toUtf8();
}

// ---------------------------------------------------------------
// Pack temp dir into zip using system 'zip' command
// ---------------------------------------------------------------
bool XlsxWriter::packZip(const QString& dir, const QString& outFile) {
    QFile::remove(outFile);
    QProcess proc;
    proc.setWorkingDirectory(dir);
    // zip -r outFile . -x "*.DS_Store"
    proc.start("zip", QStringList() << "-r" << outFile << ".");
    if (!proc.waitForFinished(15000)) return false;
    return proc.exitCode() == 0 && QFile::exists(outFile);
}

// ---------------------------------------------------------------
// Main entry point
// ---------------------------------------------------------------
bool XlsxWriter::writeResults(const QVector<TestResult>& results,
                               const QString& filePath) {
    // Build temp directory
    QString tmpDir = QDir::temp().filePath(
        "xlsx_" + QString::number(QDateTime::currentMSecsSinceEpoch()));
    QDir().mkpath(tmpDir);

    QMap<QString,int> ssIndex;
    QByteArray ss   = buildSharedStrings(results, ssIndex);
    QByteArray sheet = buildSheet(results, ssIndex);

    // Write all parts
    bool ok = true;
    ok &= writeFile(tmpDir + "/_rels/.rels",                    buildRels());
    ok &= writeFile(tmpDir + "/[Content_Types].xml",            buildContentTypes());
    ok &= writeFile(tmpDir + "/xl/workbook.xml",                buildWorkbook());
    ok &= writeFile(tmpDir + "/xl/styles.xml",                  buildStyles());
    ok &= writeFile(tmpDir + "/xl/sharedStrings.xml",           ss);
    ok &= writeFile(tmpDir + "/xl/worksheets/sheet1.xml",       sheet);
    ok &= writeFile(tmpDir + "/xl/_rels/workbook.xml.rels",     buildWorkbookRels());
    if (!ok) return false;

    // Pack into xlsx (which is a zip)
    bool packed = packZip(tmpDir, filePath);

    // Cleanup temp dir
    QDir(tmpDir).removeRecursively();
    return packed;
}
