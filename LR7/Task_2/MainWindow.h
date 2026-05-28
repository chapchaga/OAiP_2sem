#pragma once
#include <QMainWindow>
#include <QTreeWidgetItem>
#include "BinarySearchTree.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddBook();
    void onRemoveBook();
    void onFindBook();
    void onBalance();
    void onClear();
    void onTraversePreOrder();
    void onTraverseInOrder();
    void onTraversePostOrder();
    void onNodesPerLevel();

private:
    Ui::MainWindow* ui;
    LibraryTree tree;

    void rebuildTreeView();
    void populateSampleData();
    void appendOutput(const QString& text);
    void buildTreeViewItem(QTreeWidgetItem* parent, TreeNode* node);
};
