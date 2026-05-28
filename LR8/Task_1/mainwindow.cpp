#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QStringList>
#include <stdexcept>

static const int NODE_R = 22;
static const int LEVEL_H = 70;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), tree(new BST()) {
    ui->setupUi(this);

    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(ui->btnFind, &QPushButton::clicked, this, &MainWindow::onFind);
    connect(ui->btnTraverse, &QPushButton::clicked, this, &MainWindow::onTraverse);
    connect(ui->btnInsertSubtree, &QPushButton::clicked, this, &MainWindow::onInsertSubtree);
    connect(ui->btnRemoveSubtree, &QPushButton::clicked, this, &MainWindow::onRemoveSubtree);
    connect(ui->btnRemoveBranch, &QPushButton::clicked, this, &MainWindow::onRemoveBranch);
    connect(ui->btnInsertAt, &QPushButton::clicked, this, &MainWindow::onInsertAt);
    connect(ui->btnLCA, &QPushButton::clicked, this, &MainWindow::onLCA);
    connect(ui->btnClear, &QPushButton::clicked, this, &MainWindow::onClear);

    ui->graphicsView->setScene(new QGraphicsScene(this));
    drawTree();
}

MainWindow::~MainWindow() {
    delete ui;
    delete tree;
}

void MainWindow::log(const QString& msg) {
    ui->logOutput->appendPlainText(msg);
}

void MainWindow::onAdd() {
    int val = ui->spinValue->value();
    tree->add(val);
    log(QString("add(%1) — узел добавлен").arg(val));
    drawTree();
}

void MainWindow::onRemove() {
    int val = ui->spinValue->value();
    bool ok = tree->remove(val);
    log(ok ? QString("remove(%1) — узел удалён").arg(val)
           : QString("remove(%1) — узел не найден").arg(val));
    drawTree();
}

void MainWindow::onFind() {
    int val = ui->spinValue->value();
    Node* node = tree->find(val);
    log(node ? QString("find(%1) — найден").arg(val)
             : QString("find(%1) — не найден").arg(val));
}

void MainWindow::onTraverse() {
    auto vals = tree->traverse();
    QStringList parts;
    for (int v : vals) parts << QString::number(v);
    log("traverse (inorder): [" + parts.join(", ") + "]");
}

void MainWindow::onInsertSubtree() {
    int parent = ui->spinParent->value();
    bool asLeft = ui->checkLeft->isChecked();
    QString text = ui->editSubtree->text().trimmed();
    if (text.isEmpty()) { log("Ошибка: введите значения поддерева"); return; }

    BST* sub = new BST();
    for (const QString& s : text.split(' ', Qt::SkipEmptyParts))
        sub->add(s.toInt());

    bool ok = tree->insertSubtree(parent, sub, asLeft);
    delete sub;
    log(ok ? QString("insertSubtree в %1 (%2) — выполнено").arg(parent).arg(asLeft ? "лево" : "право")
           : QString("insertSubtree: узел %1 не найден").arg(parent));
    drawTree();
}

void MainWindow::onRemoveSubtree() {
    int val = ui->spinValue->value();
    BST* removed = tree->removeSubtree(val);
    if (removed) {
        auto vals = removed->traverse();
        QStringList parts;
        for (int v : vals) parts << QString::number(v);
        log(QString("removeSubtree(%1) — удалено поддерево: [%2]").arg(val).arg(parts.join(", ")));
        delete removed;
    } else {
        log(QString("removeSubtree(%1) — узел не найден").arg(val));
    }
    drawTree();
}

void MainWindow::onRemoveBranch() {
    int val = ui->spinValue->value();
    bool ok = tree->removeBranch(val);
    log(ok ? QString("removeBranch(%1) — ветвь удалена").arg(val)
           : QString("removeBranch(%1) — узел не найден").arg(val));
    drawTree();
}

void MainWindow::onInsertAt() {
    int parent = ui->spinParent->value();
    int val = ui->spinValue->value();
    bool asLeft = ui->checkLeft->isChecked();
    bool ok = tree->insertAt(parent, val, asLeft);
    log(ok ? QString("insertAt(%1 → %2, %3) — выполнено").arg(parent).arg(val).arg(asLeft ? "лево" : "право")
           : QString("insertAt: узел %1 не найден").arg(parent));
    drawTree();
}

void MainWindow::onLCA() {
    QString text = ui->editLCA->text().trimmed();
    QStringList parts = text.split(' ', Qt::SkipEmptyParts);
    if (parts.size() < 2) { log("Ошибка: введите два значения"); return; }
    int a = parts[0].toInt(), b = parts[1].toInt();
    try {
        int lca = tree->lowestCommonAncestor(a, b);
        log(QString("LCA(%1, %2) = %3").arg(a).arg(b).arg(lca));
    } catch (std::exception& e) {
        log(QString("LCA ошибка: %1").arg(e.what()));
    }
}

void MainWindow::onClear() {
    delete tree;
    tree = new BST();
    log("Дерево очищено");
    drawTree();
}

struct DrawInfo {
    Node* node;
    double x;
    int depth;
};

static void calcPositions(Node* node, double x, int depth, double spread,
                          std::vector<DrawInfo>& out) {
    if (!node) return;
    out.push_back({node, x, depth});
    calcPositions(node->left,  x - spread, depth + 1, spread / 2, out);
    calcPositions(node->right, x + spread, depth + 1, spread / 2, out);
}

void MainWindow::drawTree() {
    QGraphicsScene* scene = ui->graphicsView->scene();
    scene->clear();

    if (!tree->getRoot()) {
        scene->addText("Дерево пусто");
        return;
    }

    std::vector<DrawInfo> positions;
    calcPositions(tree->getRoot(), 0, 0, 160, positions);

    double minX = 1e9, maxX = -1e9;
    int maxDepth = 0;
    for (auto& d : positions) {
        minX = std::min(minX, d.x);
        maxX = std::max(maxX, d.x);
        maxDepth = std::max(maxDepth, d.depth);
    }

    double offsetX = -minX + NODE_R * 2;
    double sceneW = maxX - minX + NODE_R * 4;
    double sceneH = (maxDepth + 1) * LEVEL_H + NODE_R * 2;

    scene->setSceneRect(0, 0, sceneW, sceneH);

    auto getPos = [&](const DrawInfo& d) -> QPointF {
        return QPointF(d.x + offsetX, d.depth * LEVEL_H + NODE_R + 10);
    };

    for (auto& d : positions) {
        if (d.node->left) {
            DrawInfo* child = nullptr;
            for (auto& c : positions) if (c.node == d.node->left) { child = &c; break; }
            if (child) {
                QPointF p1 = getPos(d), p2 = getPos(*child);
                auto* line = scene->addLine(p1.x(), p1.y(), p2.x(), p2.y(),
                                            QPen(QColor(100,100,100), 1.5));
                line->setZValue(0);
            }
        }
        if (d.node->right) {
            DrawInfo* child = nullptr;
            for (auto& c : positions) if (c.node == d.node->right) { child = &c; break; }
            if (child) {
                QPointF p1 = getPos(d), p2 = getPos(*child);
                auto* line = scene->addLine(p1.x(), p1.y(), p2.x(), p2.y(),
                                            QPen(QColor(100,100,100), 1.5));
                line->setZValue(0);
            }
        }
    }

    for (auto& d : positions) {
        QPointF pos = getPos(d);
        QColor fill = (d.depth == 0) ? QColor(52, 120, 200) : QColor(70, 160, 90);
        auto* ellipse = scene->addEllipse(pos.x() - NODE_R, pos.y() - NODE_R,
                                          NODE_R * 2, NODE_R * 2,
                                          QPen(Qt::white, 1.5), QBrush(fill));
        ellipse->setZValue(1);

        auto* text = scene->addText(QString::number(d.node->value));
        text->setDefaultTextColor(Qt::white);
        QFont f = text->font();
        f.setBold(true);
        f.setPointSize(9);
        text->setFont(f);
        QRectF br = text->boundingRect();
        text->setPos(pos.x() - br.width() / 2, pos.y() - br.height() / 2);
        text->setZValue(2);
    }

    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
