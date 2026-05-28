#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDoubleValidator>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <cmath>
#include "shape.h"
#include "polygon.h"
#include "triangle.h"
#include "circle.h"
#include "ellipse.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "star.h"
#include "shapegraphicsitem.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_selectedShape(nullptr)
    , m_animationTimer(new QTimer(this))
{
    ui->setupUi(this);
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    connect(m_scene, &QGraphicsScene::selectionChanged,
            this, &MainWindow::onSceneSelectionChanged);
    ui->shapeTypeCombo->clear();
    ui->shapeTypeCombo->addItem("Треугольник");
    ui->shapeTypeCombo->addItem("Круг");
    ui->shapeTypeCombo->addItem("Ромб");
    ui->shapeTypeCombo->addItem("Квадрат");
    ui->shapeTypeCombo->addItem("Прямоугольник");
    ui->shapeTypeCombo->addItem("Звезда");
    ui->shapeTypeCombo->addItem("Шестиугольник");
    ui->shapeTypeCombo->addItem("Эллипс");
    m_starPointsCombo = new QComboBox(this);
    m_starPointsCombo->addItem("5 лучей");
    m_starPointsCombo->addItem("6 лучей");
    m_starPointsCombo->addItem("8 лучей");
    m_starPointsCombo->setCurrentIndex(0);
    m_starPointsCombo->setVisible(false);
    QVBoxLayout* mainLayout = new QVBoxLayout(ui->centralwidget);
    QHBoxLayout* shapeLayout = new QHBoxLayout();
    shapeLayout->addWidget(new QLabel("Тип фигуры:"));
    shapeLayout->addWidget(ui->shapeTypeCombo);
    mainLayout->addLayout(shapeLayout);
    QHBoxLayout* starLayout = new QHBoxLayout();
    starLayout->addWidget(new QLabel("Лучи звезды:"));
    starLayout->addWidget(m_starPointsCombo);
    mainLayout->addLayout(starLayout);
    QHBoxLayout* coordLayout = new QHBoxLayout();
    coordLayout->addWidget(new QLabel("X:"));
    coordLayout->addWidget(ui->xLineEdit);
    coordLayout->addWidget(new QLabel("Y:"));
    coordLayout->addWidget(ui->yLineEdit);
    mainLayout->addLayout(coordLayout);
    QHBoxLayout* paramLayout = new QHBoxLayout();
    paramLayout->addWidget(new QLabel("Параметр 1:"));
    paramLayout->addWidget(ui->param1LineEdit);
    paramLayout->addWidget(new QLabel("Параметр 2:"));
    paramLayout->addWidget(ui->param2LineEdit);
    mainLayout->addLayout(paramLayout);
    mainLayout->addWidget(ui->createButton);
    QHBoxLayout* moveLayout = new QHBoxLayout();
    moveLayout->addWidget(new QLabel("dx:"));
    moveLayout->addWidget(ui->dxLineEdit);
    moveLayout->addWidget(new QLabel("dy:"));
    moveLayout->addWidget(ui->dyLineEdit);
    moveLayout->addWidget(ui->moveButton);
    mainLayout->addLayout(moveLayout);
    QHBoxLayout* rotateLayout = new QHBoxLayout();
    rotateLayout->addWidget(new QLabel("Угол:"));
    rotateLayout->addWidget(ui->angleLineEdit);
    rotateLayout->addWidget(ui->rotateButton);
    mainLayout->addLayout(rotateLayout);
    QHBoxLayout* scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(new QLabel("Коэффициент:"));
    scaleLayout->addWidget(ui->factorLineEdit);
    scaleLayout->addWidget(ui->scaleButton);
    mainLayout->addLayout(scaleLayout);
    mainLayout->addWidget(ui->animationCheckBox);
    mainLayout->addWidget(ui->areaLabel);
    mainLayout->addWidget(ui->perimeterLabel);
    mainLayout->addWidget(ui->centerLabel);
    mainLayout->addWidget(new QLabel("Список фигур:"));
    mainLayout->addWidget(ui->shapeList, 1);
    mainLayout->addWidget(ui->graphicsView, 5);
    QDoubleValidator* validator = new QDoubleValidator(this);
    ui->xLineEdit->setValidator(validator);
    ui->yLineEdit->setValidator(validator);
    ui->param1LineEdit->setValidator(validator);
    ui->param2LineEdit->setValidator(validator);
    ui->dxLineEdit->setValidator(validator);
    ui->dyLineEdit->setValidator(validator);
    ui->angleLineEdit->setValidator(validator);
    ui->factorLineEdit->setValidator(validator);
    ui->xLineEdit->setPlaceholderText("X координата");
    ui->yLineEdit->setPlaceholderText("Y координата");
    ui->param1LineEdit->setPlaceholderText("Радиус/сторона");
    ui->param2LineEdit->setPlaceholderText("Второй параметр");
    ui->dxLineEdit->setPlaceholderText("смещение X");
    ui->dyLineEdit->setPlaceholderText("смещение Y");
    ui->angleLineEdit->setPlaceholderText("угол в градусах");
    ui->factorLineEdit->setPlaceholderText("коэффициент");
    m_animationTimer->setInterval(50);
    setupConnections();
    connect(ui->shapeTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index) {
                if (m_starPointsCombo) {
                    m_starPointsCombo->setVisible(index == 5);
                }
            });
}
MainWindow::~MainWindow()
{
    qDeleteAll(m_shapes);
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::onCreateShape);
    connect(ui->shapeList, &QListWidget::itemClicked, this, &MainWindow::onShapeSelected);
    connect(ui->moveButton, &QPushButton::clicked, this, &MainWindow::onMove);
    connect(ui->rotateButton, &QPushButton::clicked, this, &MainWindow::onRotate);
    connect(ui->scaleButton, &QPushButton::clicked, this, &MainWindow::onScale);
    connect(m_animationTimer, &QTimer::timeout, this, &MainWindow::onTimerTick);
}

void MainWindow::showError(const QString& message)
{
    QMessageBox::warning(this, "Ошибка", message);
}

shapegraphicsitem* MainWindow::createGraphicsItem(shape* shapePtr)
{
    shapegraphicsitem* item = new shapegraphicsitem(shapePtr);
    m_scene->addItem(item);
    return item;
}

void MainWindow::redrawScene()
{
    m_scene->clear();
    m_items.clear();

    for (shape* shapePtr : m_shapes) {
        shapegraphicsitem* item = createGraphicsItem(shapePtr);
        m_items.append(item);
    }
}

void MainWindow::onCreateShape()
{
    try {
        if (ui->xLineEdit->text().isEmpty() ||
            ui->yLineEdit->text().isEmpty() ||
            ui->param1LineEdit->text().isEmpty()) {
            showError("Заполните поля X, Y и первый параметр!");
            return;
        }

        double x = ui->xLineEdit->text().toDouble();
        double y = ui->yLineEdit->text().toDouble();
        double param1 = ui->param1LineEdit->text().toDouble();
        double param2 = ui->param2LineEdit->text().toDouble();
        int shapeType = ui->shapeTypeCombo->currentIndex();
        shape* newShape = nullptr;
        switch (shapeType) {
        case 0: {
            double side = param1;
            double height = side * sqrt(3) / 2;
            QPointF p1(x, y - height * 2/3);
            QPointF p2(x - side/2, y + height/3);
            QPointF p3(x + side/2, y + height/3);
            newShape = new triangle(p1, p2, p3);
            break;
        }
        case 1:
            newShape = new circle(QPointF(x, y), param1);
            break;

        case 2:
            newShape = new rhombus(QPointF(x, y), param1, param2 > 0 ? param2 : param1);
            break;

        case 3:
            newShape = new square(QPointF(x, y), param1);
            break;

        case 4:
            newShape = new rectangle(QPointF(x, y), param1, param2 > 0 ? param2 : param1);
            break;

        case 5: {
            double outerRadius = param1;
            double innerRadius = (param2 > 0) ? param2 : outerRadius * 0.45; // 0.45 для классической звезды

            int points = 5;
            if (m_starPointsCombo && m_starPointsCombo->isVisible()) {
                QString text = m_starPointsCombo->currentText();
                if (text == "6 лучей") points = 6;
                else if (text == "8 лучей") points = 8;
                else points = 5;
            }
            newShape = new star(QPointF(x, y), outerRadius, innerRadius, points);
            break;
        }
        case 6: {
            double radius = param1;
            QVector<QPointF> vertices;
            int points = 6;
            for (int i = 0; i < points; i++) {
                double angle = i * 2 * M_PI / points - M_PI / 2;
                double px = x + radius * cos(angle);
                double py = y + radius * sin(angle);
                vertices.append(QPointF(px, py));
            }
            newShape = new Polygon(vertices);
            break;
        }
        case 7:
            newShape = new ellipse(QPointF(x, y), param1, param2 > 0 ? param2 : param1);
            break;

        default:
            showError("Неизвестный тип фигуры");
            return;
        }
        if (newShape) {
            m_shapes.append(newShape);
            shapegraphicsitem* item = createGraphicsItem(newShape);
            m_items.append(item);
            QString itemText = QString("%1 #%2")
                                   .arg(newShape->getName())
                                   .arg(m_shapes.size());
            ui->shapeList->addItem(itemText);

            ui->xLineEdit->clear();
            ui->yLineEdit->clear();
            ui->param1LineEdit->clear();
            ui->param2LineEdit->clear();

            m_scene->update();
        }
    } catch (const std::exception& e) {
        showError(QString("Ошибка: %1").arg(e.what()));
    }
}

void MainWindow::onShapeSelected()
{
    int currentRow = ui->shapeList->currentRow();

    if (currentRow >= 0 && currentRow < m_items.size()) {
        for (auto item : m_items) {
            item->setSelected(false);
        }
        m_items[currentRow]->setSelected(true);
        m_scene->update();
    }
}

void MainWindow::onSceneSelectionChanged()
{
    QList<QGraphicsItem*> selected = m_scene->selectedItems();

    if (selected.isEmpty()) {
        m_selectedShape = nullptr;
    } else {
        shapegraphicsitem* item = dynamic_cast<shapegraphicsitem*>(selected.first());
        if (item) {
            m_selectedShape = item->getShape();
            int index = m_items.indexOf(item);
            if (index >= 0) {
                ui->shapeList->setCurrentRow(index);
            }
        }
    }

    updateShapeInfo();
}

void MainWindow::updateShapeInfo()
{
    if (!m_selectedShape) {
        ui->areaLabel->setText("Площадь: ---");
        ui->perimeterLabel->setText("Периметр: ---");
        ui->centerLabel->setText("Центр: ---");
        return;
    }
    double area = m_selectedShape->area();
    double perimeter = m_selectedShape->perimeter();
    QPointF center = m_selectedShape->center();
    ui->areaLabel->setText(QString("Площадь: %1").arg(area, 0, 'f', 2));
    ui->perimeterLabel->setText(QString("Периметр: %1").arg(perimeter, 0, 'f', 2));
    ui->centerLabel->setText(QString("Центр: (%1, %2)")
                                 .arg(center.x(), 0, 'f', 2)
                                 .arg(center.y(), 0, 'f', 2));
}

void MainWindow::onMove()
{
    if (!m_selectedShape) {
        showError("Сначала выберите фигуру!");
        return;
    }
    if (ui->dxLineEdit->text().isEmpty() || ui->dyLineEdit->text().isEmpty()) {
        showError("Введите dx и dy!");
        return;
    }
    double dx = ui->dxLineEdit->text().toDouble();
    double dy = ui->dyLineEdit->text().toDouble();
    QPointF currentCenter = m_selectedShape->center();
    QPointF newCenter(currentCenter.x() + dx, currentCenter.y() + dy);
    if (ui->animationCheckBox && ui->animationCheckBox->isChecked()) {
        int duration = 1000;
        connect(m_selectedShape, &shape::transformStep, this, &MainWindow::onAnimationStep, Qt::UniqueConnection);
        connect(m_selectedShape, &shape::transformFinished, this, &MainWindow::onAnimationFinished, Qt::UniqueConnection);
        m_selectedShape->animateMove(QPointF(dx, dy), duration);
    } else {
        m_selectedShape->moveCenter(newCenter);
        updateShapeInfo();
        m_scene->update();
    }
}
void MainWindow::onRotate()
{
    if (!m_selectedShape) {
        showError("Сначала выберите фигуру!");
        return;
    }
    if (ui->angleLineEdit->text().isEmpty()) {
        showError("Введите угол поворота!");
        return;
    }
    double angle = ui->angleLineEdit->text().toDouble();
    QPointF centerPoint = m_selectedShape->center();
    if (ui->animationCheckBox && ui->animationCheckBox->isChecked()) {
        int duration = 1000;
        connect(m_selectedShape, &shape::transformStep, this, &MainWindow::onAnimationStep, Qt::UniqueConnection);
        connect(m_selectedShape, &shape::transformFinished, this, &MainWindow::onAnimationFinished, Qt::UniqueConnection);
        m_selectedShape->animateRotate(angle, duration);
    } else {
        m_selectedShape->rotate(angle, centerPoint);
        updateShapeInfo();
        m_scene->update();
    }
}

void MainWindow::onScale()
{
    if (!m_selectedShape) {
        showError("Сначала выберите фигуру!");
        return;
    }
    if (ui->factorLineEdit->text().isEmpty()) {
        showError("Введите коэффициент масштабирования!");
        return;
    }
    double factor = ui->factorLineEdit->text().toDouble();
    if (factor <= 0) {
        showError("Коэффициент должен быть положительным!");
        return;
    }
    QPointF centerPoint = m_selectedShape->center();

    if (ui->animationCheckBox && ui->animationCheckBox->isChecked()) {
        int duration = 1000;
        connect(m_selectedShape, &shape::transformStep, this, &MainWindow::onAnimationStep, Qt::UniqueConnection);
        connect(m_selectedShape, &shape::transformFinished, this, &MainWindow::onAnimationFinished, Qt::UniqueConnection);
        m_selectedShape->animateScale(factor, duration);
    } else {
        m_selectedShape->scale(factor, centerPoint);
        updateShapeInfo();
        m_scene->update();
    }
}

void MainWindow::onAnimationStep()
{
    m_scene->update();
    updateShapeInfo();
}

void MainWindow::onAnimationFinished()
{
    if (m_selectedShape) {
        disconnect(m_selectedShape, &shape::transformStep, this, &MainWindow::onAnimationStep);
        disconnect(m_selectedShape, &shape::transformFinished, this, &MainWindow::onAnimationFinished);
    }
    updateShapeInfo();
    m_scene->update();
}

void MainWindow::onTimerTick()
{
}
