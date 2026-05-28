#pragma once
#include <QMainWindow>
#include "bst.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAdd();
    void onRemove();
    void onFind();
    void onTraverse();
    void onInsertSubtree();
    void onRemoveSubtree();
    void onRemoveBranch();
    void onInsertAt();
    void onLCA();
    void onClear();

private:
    Ui::MainWindow* ui;
    BST* tree;

    void refreshDisplay();
    void log(const QString& msg);
    void drawTree();
};
