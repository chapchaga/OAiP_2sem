#pragma once
#include <QMainWindow>
#include "Map.h"
#include "Set.h"
#include "HashTable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onMapInsert();
    void onMapErase();
    void onMapFind();
    void onMapClear();

    void onSetInsert();
    void onSetErase();
    void onSetContains();
    void onSetClear();

    void onHashInsert();
    void onHashErase();
    void onHashFind();
    void onHashClear();

private:
    Ui::MainWindow* ui;

    Map<int, QString> map_;
    Set<int>          set_;
    HashTable<int, QString> hashTable_;

    void refreshMapView();
    void refreshSetView();
    void refreshHashView();
};
