#ifndef XLSXWRITER_H
#define XLSXWRITER_H

/*
 * Минимальный XLSX-writer на чистом Qt5/Qt6 — без сторонних библиотек.
 * XLSX = ZIP-архив с XML-файлами внутри.
 * ZIP реализован вручную (stored, без сжатия).
 * CRC32 реализован встроенно.
 *
 * Стили ячеек (styleIdx):
 *   0 — обычный + тонкая рамка
 *   1 — заголовок (жирный, синий фон #4472C4, белый текст, центр)
 *   2 — ok       (зелёный фон #C6EFCE, тёмно-зелёный #276221, центр)
 *   3 — fail     (красный фон #FFC7CE, тёмно-красный #9C0006, центр)
 *   4 — жирный
 */

#include <QString>
#include <QStringList>
#include <QVector>
#include <QByteArray>
#include <QFile>
#include <stdexcept>

// ─────────────── Структуры ───────────────────────────────────────────

struct XlsxCell {
    QString value;
    int     styleIdx; // 0..4
    bool    isNumber; // если true — записывается как число, иначе как строка
};

struct XlsxRow   { QVector<XlsxCell> cells; };

struct XlsxSheet {
    QString          name;
    QVector<XlsxRow> rows;

    void addHeaderRow(const QStringList &headers) {
        XlsxRow row;
        for (const QString &h : headers)
            row.cells.append({ h, 1, false });
        rows.append(row);
    }

    void addRow(const QVector<XlsxCell> &cells) {
        XlsxRow row;
        row.cells = cells;
        rows.append(row);
    }
};

// ─────────────── ZIP / CRC32 ─────────────────────────────────────────

namespace XlsxDetail {

static quint32 crc32(const QByteArray &data) {
    quint32 crc = 0xFFFFFFFFu;
    for (unsigned char b : data) {
        crc ^= b;
        for (int k = 0; k < 8; ++k)
            crc = (crc >> 1) ^ (0xEDB88320u & -(crc & 1u));
    }
    return crc ^ 0xFFFFFFFFu;
}

static void u16(QByteArray &b, quint16 v) {
    b += char(v & 0xFF);
    b += char((v >> 8) & 0xFF);
}
static void u32(QByteArray &b, quint32 v) {
    b += char(v & 0xFF);
    b += char((v >> 8)  & 0xFF);
    b += char((v >> 16) & 0xFF);
    b += char((v >> 24) & 0xFF);
}

struct ZipEntry { QString name; QByteArray data; };

static QByteArray buildZip(const QVector<ZipEntry> &entries) {
    struct CDR { quint32 offset; quint32 crc; quint32 size; QByteArray name; };
    QVector<CDR> cdr;
    QByteArray zip;

    for (const ZipEntry &e : entries) {
        QByteArray nb = e.name.toUtf8();
        quint32 crcv  = crc32(e.data);
        quint32 sz    = (quint32)e.data.size();
        quint32 off   = (quint32)zip.size();
        cdr.append({ off, crcv, sz, nb });

        u32(zip, 0x04034B50u); u16(zip, 20);   u16(zip, 0);
        u16(zip, 0);           u16(zip, 0);    u16(zip, 0);
        u32(zip, crcv);        u32(zip, sz);   u32(zip, sz);
        u16(zip, (quint16)nb.size()); u16(zip, 0);
        zip += nb;
        zip += e.data;
    }

    quint32 cdOff = (quint32)zip.size();
    for (const CDR &c : cdr) {
        u32(zip, 0x02014B50u); u16(zip, 20);   u16(zip, 20);
        u16(zip, 0);           u16(zip, 0);    u16(zip, 0);  u16(zip, 0);
        u32(zip, c.crc);       u32(zip, c.size); u32(zip, c.size);
        u16(zip, (quint16)c.name.size()); u16(zip, 0); u16(zip, 0);
        u16(zip, 0); u16(zip, 0); u32(zip, 0); u32(zip, c.offset);
        zip += c.name;
    }
    quint32 cdSz = (quint32)zip.size() - cdOff;

    u32(zip, 0x06054B50u); u16(zip, 0); u16(zip, 0);
    u16(zip, (quint16)entries.size()); u16(zip, (quint16)entries.size());
    u32(zip, cdSz); u32(zip, cdOff);   u16(zip, 0);
    return zip;
}

// ─────────────── XML-части XLSX ──────────────────────────────────────

static QString esc(const QString &s) {
    QString r = s;
    r.replace("&", "&amp;");
    r.replace("<", "&lt;");
    r.replace(">", "&gt;");
    r.replace("\"", "&quot;");
    return r;
}

static QString colName(int col) {   // 0-based -> "A","B",...
    QString r;
    ++col;
    while (col > 0) { --col; r.prepend(QChar('A' + col % 26)); col /= 26; }
    return r;
}

static QByteArray contentTypes(int n) {
    QString s =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
        "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
        "<Default Extension=\"xml\"  ContentType=\"application/xml\"/>"
        "<Override PartName=\"/xl/workbook.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sheet.main+xml\"/>"
        "<Override PartName=\"/xl/styles.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.styles+xml\"/>"
        "<Override PartName=\"/xl/sharedStrings.xml\""
        " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.sharedStrings+xml\"/>";
    for (int i = 1; i <= n; ++i)
        s += QString("<Override PartName=\"/xl/worksheets/sheet%1.xml\""
                     " ContentType=\"application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml\"/>").arg(i);
    s += "</Types>";
    return s.toUtf8();
}

static QByteArray rootRels() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
        "<Relationship Id=\"rId1\""
        " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\""
        " Target=\"xl/workbook.xml\"/>"
        "</Relationships>");
}

static QByteArray wbRels(int n) {
    QString s =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">";
    for (int i = 1; i <= n; ++i)
        s += QString("<Relationship Id=\"rId%1\""
                     " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet\""
                     " Target=\"worksheets/sheet%1.xml\"/>").arg(i);
    s += QString("<Relationship Id=\"rId%1\""
                 " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/styles\""
                 " Target=\"styles.xml\"/>").arg(n + 1);
    s += QString("<Relationship Id=\"rId%1\""
                 " Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/sharedStrings\""
                 " Target=\"sharedStrings.xml\"/>").arg(n + 2);
    s += "</Relationships>";
    return s.toUtf8();
}

static QByteArray workbook(const QVector<XlsxSheet> &sheets) {
    QString s =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<workbook xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
        " xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
        "<sheets>";
    for (int i = 0; i < sheets.size(); ++i)
        s += QString("<sheet name=\"%1\" sheetId=\"%2\" r:id=\"rId%2\"/>")
                 .arg(esc(sheets[i].name)).arg(i + 1);
    s += "</sheets></workbook>";
    return s.toUtf8();
}

static QByteArray styles() {
    return QByteArray(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<styleSheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"

        // 4 шрифта
        "<fonts count=\"4\">"
        "<font><sz val=\"11\"/><name val=\"Arial\"/></font>"
        "<font><b/><sz val=\"11\"/><color rgb=\"FFFFFFFF\"/><name val=\"Arial\"/></font>"
        "<font><sz val=\"11\"/><color rgb=\"FF276221\"/><name val=\"Arial\"/></font>"
        "<font><sz val=\"11\"/><color rgb=\"FF9C0006\"/><name val=\"Arial\"/></font>"
        "</fonts>"

        // 5 заливок (первые 2 обязательны)
        "<fills count=\"5\">"
        "<fill><patternFill patternType=\"none\"/></fill>"
        "<fill><patternFill patternType=\"gray125\"/></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FF4472C4\"/></patternFill></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FFC6EFCE\"/></patternFill></fill>"
        "<fill><patternFill patternType=\"solid\"><fgColor rgb=\"FFFFC7CE\"/></patternFill></fill>"
        "</fills>"

        // 2 рамки
        "<borders count=\"2\">"
        "<border><left/><right/><top/><bottom/><diagonal/></border>"
        "<border>"
        "<left   style=\"thin\"><color rgb=\"FF000000\"/></left>"
        "<right  style=\"thin\"><color rgb=\"FF000000\"/></right>"
        "<top    style=\"thin\"><color rgb=\"FF000000\"/></top>"
        "<bottom style=\"thin\"><color rgb=\"FF000000\"/></bottom>"
        "<diagonal/></border>"
        "</borders>"

        "<cellStyleXfs count=\"1\"><xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"0\"/></cellStyleXfs>"

        // 5 стилей (0..4)
        "<cellXfs count=\"5\">"
        // 0 normal + border
        "<xf numFmtId=\"0\" fontId=\"0\" fillId=\"0\" borderId=\"1\" xfId=\"0\""
        " applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\"><alignment wrapText=\"1\"/></xf>"
        // 1 header
        "<xf numFmtId=\"0\" fontId=\"1\" fillId=\"2\" borderId=\"1\" xfId=\"0\""
        " applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\">"
        "<alignment horizontal=\"center\" wrapText=\"1\"/></xf>"
        // 2 ok (green)
        "<xf numFmtId=\"0\" fontId=\"2\" fillId=\"3\" borderId=\"1\" xfId=\"0\""
        " applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\">"
        "<alignment horizontal=\"center\"/></xf>"
        // 3 fail (red)
        "<xf numFmtId=\"0\" fontId=\"3\" fillId=\"4\" borderId=\"1\" xfId=\"0\""
        " applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\">"
        "<alignment horizontal=\"center\"/></xf>"
        // 4 bold
        "<xf numFmtId=\"0\" fontId=\"1\" fillId=\"0\" borderId=\"1\" xfId=\"0\""
        " applyFont=\"1\" applyFill=\"1\" applyBorder=\"1\"/>"
        "</cellXfs>"

        "</styleSheet>");
}

static QByteArray sharedStrings(const QVector<XlsxSheet> &sheets, QVector<QString> &out) {
    for (const XlsxSheet &sh : sheets)
        for (const XlsxRow &row : sh.rows)
            for (const XlsxCell &c : row.cells)
                if (!c.isNumber && !out.contains(c.value))
                    out.append(c.value);

    QString s = QString(
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<sst xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\""
        " count=\"%1\" uniqueCount=\"%1\">").arg(out.size());
    for (const QString &v : out)
        s += "<si><t xml:space=\"preserve\">" + esc(v) + "</t></si>";
    s += "</sst>";
    return s.toUtf8();
}

static QByteArray worksheet(const XlsxSheet &sh, const QVector<QString> &ssi) {
    int cols = 0;
    for (const XlsxRow &r : sh.rows)
        cols = qMax(cols, r.cells.size());

    // авто-ширины
    QVector<int> w(cols, 8);
    for (const XlsxRow &r : sh.rows)
        for (int c = 0; c < r.cells.size(); ++c)
            w[c] = qMax(w[c], qMin(r.cells[c].value.length() + 4, 60));

    QString s =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\">"
        "<sheetViews><sheetView workbookViewId=\"0\"/></sheetViews>"
        "<sheetFormatPr defaultRowHeight=\"15\"/>"
        "<cols>";
    for (int c = 0; c < cols; ++c)
        s += QString("<col min=\"%1\" max=\"%1\" width=\"%2\" customWidth=\"1\"/>")
                 .arg(c + 1).arg(w[c]);
    s += "</cols><sheetData>";

    for (int ri = 0; ri < sh.rows.size(); ++ri) {
        const XlsxRow &row = sh.rows[ri];
        s += QString("<row r=\"%1\">").arg(ri + 1);
        for (int ci = 0; ci < row.cells.size(); ++ci) {
            const XlsxCell &cell = row.cells[ci];
            QString ref = colName(ci) + QString::number(ri + 1);
            if (cell.isNumber) {
                s += QString("<c r=\"%1\" s=\"%2\"><v>%3</v></c>")
                         .arg(ref).arg(cell.styleIdx).arg(cell.value);
            } else {
                int idx = ssi.indexOf(cell.value);
                s += QString("<c r=\"%1\" s=\"%2\" t=\"s\"><v>%3</v></c>")
                         .arg(ref).arg(cell.styleIdx).arg(qMax(idx, 0));
            }
        }
        s += "</row>";
    }
    s += "</sheetData>";
    if (!sh.rows.isEmpty() && cols > 0)
        s += QString("<autoFilter ref=\"A1:%1%2\"/>")
                 .arg(colName(cols - 1)).arg(sh.rows.size());
    s += "</worksheet>";
    return s.toUtf8();
}

} // namespace XlsxDetail

// ─────────────── Публичный класс ─────────────────────────────────────

class XlsxWriter {
public:
    QVector<XlsxSheet> sheets;

    XlsxSheet &addSheet(const QString &name) {
        sheets.append(XlsxSheet());
        sheets.last().name = name;
        return sheets.last();
    }

    void save(const QString &path) const {
        using namespace XlsxDetail;

        QVector<QString> ssi;
        QByteArray ssXml = sharedStrings(sheets, ssi);

        QVector<ZipEntry> entries;
        entries.append({ "[Content_Types].xml",       contentTypes(sheets.size()) });
        entries.append({ "_rels/.rels",               rootRels() });
        entries.append({ "xl/workbook.xml",           workbook(sheets) });
        entries.append({ "xl/_rels/workbook.xml.rels",wbRels(sheets.size()) });
        entries.append({ "xl/styles.xml",             styles() });
        entries.append({ "xl/sharedStrings.xml",      ssXml });

        for (int i = 0; i < sheets.size(); ++i)
            entries.append({
                QString("xl/worksheets/sheet%1.xml").arg(i + 1),
                worksheet(sheets[i], ssi)
            });

        QByteArray zip = buildZip(entries);

        QFile f(path);
        if (!f.open(QIODevice::WriteOnly))
            throw std::runtime_error(
                QString("Не удалось создать файл: %1").arg(path).toStdString());
        f.write(zip);
    }
};

#endif // XLSXWRITER_H
