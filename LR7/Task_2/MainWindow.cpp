#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabels({"Key", "Author", "Title", "Year", "Language"});
    ui->treeWidget->setColumnWidth(0, 60);
    ui->treeWidget->setColumnWidth(1, 140);
    ui->treeWidget->setColumnWidth(2, 200);
    ui->treeWidget->setColumnWidth(3, 60);

    connect(ui->btnAdd,             &QPushButton::clicked, this, &MainWindow::onAddBook);
    connect(ui->btnRemove,          &QPushButton::clicked, this, &MainWindow::onRemoveBook);
    connect(ui->btnFind,            &QPushButton::clicked, this, &MainWindow::onFindBook);
    connect(ui->btnBalance,         &QPushButton::clicked, this, &MainWindow::onBalance);
    connect(ui->btnClear,           &QPushButton::clicked, this, &MainWindow::onClear);
    connect(ui->btnPreOrder,        &QPushButton::clicked, this, &MainWindow::onTraversePreOrder);
    connect(ui->btnInOrder,         &QPushButton::clicked, this, &MainWindow::onTraverseInOrder);
    connect(ui->btnPostOrder,       &QPushButton::clicked, this, &MainWindow::onTraversePostOrder);
    connect(ui->btnNodesPerLevel,   &QPushButton::clicked, this, &MainWindow::onNodesPerLevel);

    populateSampleData();
    rebuildTreeView();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::populateSampleData() {
    std::vector<Book> samples = {
        {5,  "Knuth D.",       "The Art of Computer Programming", 1968, "English"},
        {3,  "Stroustrup B.",  "The C++ Programming Language",    2013, "English"},
        {8,  "Tolkien J.R.R.", "The Lord of the Rings",           1954, "English"},
        {1,  "Pushkin A.S.",   "Eugene Onegin",                   1833, "Russian"},
        {7,  "Orwell G.",      "1984",                            1949, "English"},
        {2,  "Bulgakov M.",    "The Master and Margarita",        1967, "Russian"},
        {10, "Martin R.",      "Clean Code",                      2008, "English"},
        {6,  "Dostoevsky F.",  "Crime and Punishment",            1866, "Russian"},
        {4,  "Hemingway E.",   "The Old Man and the Sea",         1952, "English"},
        {9,  "Lem S.",         "Solaris",                         1961, "Polish"},
    };
    for (auto& b : samples) tree.insert(b);
}

void MainWindow::appendOutput(const QString& text) {
    ui->memoOutput->appendPlainText(text);
}

QString bookToString(const Book& b) {
    return QString("[%1] %2 — \"%3\" (%4, %5)")
        .arg(b.key)
        .arg(QString::fromStdString(b.author))
        .arg(QString::fromStdString(b.title))
        .arg(b.year)
        .arg(QString::fromStdString(b.language));
}

void MainWindow::buildTreeViewItem(QTreeWidgetItem* parent, TreeNode* node) {
    if (!node) return;

    QTreeWidgetItem* item = parent
        ? new QTreeWidgetItem(parent)
        : new QTreeWidgetItem(ui->treeWidget);

    item->setText(0, QString::number(node->data.key));
    item->setText(1, QString::fromStdString(node->data.author));
    item->setText(2, QString::fromStdString(node->data.title));
    item->setText(3, QString::number(node->data.year));
    item->setText(4, QString::fromStdString(node->data.language));

    buildTreeViewItem(item, node->left);
    buildTreeViewItem(item, node->right);

    item->setExpanded(true);
}

void MainWindow::rebuildTreeView() {
    ui->treeWidget->clear();
    buildTreeViewItem(nullptr, tree.getRoot());
    ui->treeWidget->expandAll();
}

void MainWindow::onAddBook() {
    bool ok;
    int key = ui->spinKey->value();
    QString author   = ui->editAuthor->text().trimmed();
    QString title    = ui->editTitle->text().trimmed();
    int year         = ui->spinYear->value();
    QString language = ui->editLanguage->text().trimmed();

    if (author.isEmpty() || title.isEmpty() || language.isEmpty()) {
        QMessageBox::warning(this, "Input error", "Please fill in all fields.");
        return;
    }

    Book b;
    b.key      = key;
    b.author   = author.toStdString();
    b.title    = title.toStdString();
    b.year     = year;
    b.language = language.toStdString();

    tree.insert(b);
    rebuildTreeView();
    appendOutput(QString("Added: %1").arg(bookToString(b)));
}

void MainWindow::onRemoveBook() {
    int key = ui->spinSearchKey->value();
    if (!tree.find(key)) {
        QMessageBox::information(this, "Not found", QString("Key %1 not found.").arg(key));
        return;
    }
    tree.remove(key);
    rebuildTreeView();
    appendOutput(QString("Removed key: %1").arg(key));
}

void MainWindow::onFindBook() {
    int key = ui->spinSearchKey->value();
    const Book* b = tree.find(key);
    if (!b) {
        appendOutput(QString("Key %1: not found.").arg(key));
    } else {
        appendOutput(QString("Found: %1").arg(bookToString(*b)));
    }
}

void MainWindow::onBalance() {
    tree.balanceTree();
    rebuildTreeView();
    appendOutput("Tree balanced.");
}

void MainWindow::onClear() {
    tree.clear();
    rebuildTreeView();
    ui->memoOutput->clear();
    appendOutput("Tree cleared.");
}

void MainWindow::onTraversePreOrder() {
    appendOutput("--- Pre-order (root, left, right) ---");
    tree.traversePreOrder([this](const Book& b) {
        appendOutput(bookToString(b));
    });
}

void MainWindow::onTraverseInOrder() {
    appendOutput("--- In-order (ascending by key) ---");
    tree.traverseInOrder([this](const Book& b) {
        appendOutput(bookToString(b));
    });
}

void MainWindow::onTraversePostOrder() {
    appendOutput("--- Post-order (left, right, root) ---");
    tree.traversePostOrder([this](const Book& b) {
        appendOutput(bookToString(b));
    });
}

void MainWindow::onNodesPerLevel() {
    std::vector<int> levels = tree.nodesPerLevel();
    if (levels.empty()) {
        appendOutput("Tree is empty.");
        return;
    }
    appendOutput("--- Nodes per level ---");
    for (int i = 0; i < (int)levels.size(); ++i) {
        appendOutput(QString("Level %1: %2 node(s)").arg(i + 1).arg(levels[i]));
    }
}
