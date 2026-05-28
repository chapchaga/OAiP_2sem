#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QComboBox>
#include <QCheckBox>

class shape;
class triangle;
class circle;
class ellipse;
class Polygon;
class rectangle;
class square;
class rhombus;
class star;
class shapegraphicsitem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCreateShape();
    void onShapeSelected();
    void onMove();
    void onRotate();
    void onScale();
    void onTimerTick();
    void onSceneSelectionChanged();

    // Слоты для анимации
    void onAnimationStep();
    void onAnimationFinished();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *m_scene;
    QList<shape*> m_shapes;
    QList<shapegraphicsitem*> m_items;
    shape* m_selectedShape;
    QTimer* m_animationTimer;

    QComboBox* m_starPointsCombo;
    QCheckBox* m_animationCheckBox;  // чекбокс для анимации

    void setupConnections();
    void updateShapeInfo();
    void showError(const QString& message);
    void redrawScene();
    shapegraphicsitem* createGraphicsItem(shape* shapePtr);
};

#endif
