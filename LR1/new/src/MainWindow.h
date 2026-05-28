#pragma once

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <memory>

#include "CanvasWidget.h"

class Car;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override = default;

private:
    CanvasWidget* canvas_ = nullptr; // владелец: MainWindow
    std::unique_ptr<MovingRectangle> figure_;

    QLineEdit* xEdit_ = nullptr;
    QLineEdit* yEdit_ = nullptr;
    QLineEdit* dxEdit_ = nullptr;
    QLineEdit* dyEdit_ = nullptr;

    QLabel* statusLabel_ = nullptr;

    MovingRectangle& requireFigure();
    double readRequiredDouble(QLineEdit* edit, const QString& fieldName);

    void createRectangle();
    void createCar();
};

