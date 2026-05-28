#include "MainWindow.h"

#include <QDoubleValidator>
#include <QGroupBox>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <cmath>

#include "Car.h"
#include "Exceptions.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    auto* mainLayout = new QHBoxLayout(central);

    canvas_ = new CanvasWidget(central);
    mainLayout->addWidget(canvas_, 1);

    QWidget* panel = new QWidget(central);
    panel->setMinimumWidth(320);
    mainLayout->addWidget(panel, 0);

    auto* panelLayout = new QVBoxLayout(panel);
    panelLayout->setAlignment(Qt::AlignTop);

    // --- Создание объекта ---
    auto* createBox = new QGroupBox(QStringLiteral("Создание"), panel);
    auto* createLayout = new QVBoxLayout(createBox);

    QPushButton* createRectBtn = new QPushButton(QStringLiteral("Создать прямоугольник"), createBox);
    QPushButton* createCarBtn = new QPushButton(QStringLiteral("Создать автомобиль"), createBox);

    createLayout->addWidget(createRectBtn);
    createLayout->addWidget(createCarBtn);

    panelLayout->addWidget(createBox);

    // --- Ввод чисел ---
    auto* inputBox = new QGroupBox(QStringLiteral("Ввод параметров"), panel);
    auto* inputLayout = new QGridLayout(inputBox);

    inputLayout->addWidget(new QLabel(QStringLiteral("x"), inputBox), 0, 0);
    inputLayout->addWidget(new QLabel(QStringLiteral("y"), inputBox), 0, 1);
    inputLayout->addWidget(new QLabel(QStringLiteral("dx"), inputBox), 1, 0);
    inputLayout->addWidget(new QLabel(QStringLiteral("dy"), inputBox), 1, 1);

    xEdit_ = new QLineEdit(inputBox);
    yEdit_ = new QLineEdit(inputBox);
    dxEdit_ = new QLineEdit(inputBox);
    dyEdit_ = new QLineEdit(inputBox);

    xEdit_->setPlaceholderText(QStringLiteral("например, 100"));
    yEdit_->setPlaceholderText(QStringLiteral("например, 80"));
    dxEdit_->setPlaceholderText(QStringLiteral("например, 20"));
    dyEdit_->setPlaceholderText(QStringLiteral("например, 10"));

    auto* v = new QDoubleValidator(-1e6, 1e6, 3, this);
    v->setNotation(QDoubleValidator::StandardNotation);
    xEdit_->setValidator(v);
    yEdit_->setValidator(v);

    auto* v2 = new QDoubleValidator(-1e6, 1e6, 3, this);
    v2->setNotation(QDoubleValidator::StandardNotation);
    dxEdit_->setValidator(v2);
    dyEdit_->setValidator(v2);

    inputLayout->addWidget(xEdit_, 0, 0);
    inputLayout->addWidget(yEdit_, 0, 1);
    inputLayout->addWidget(dxEdit_, 1, 0);
    inputLayout->addWidget(dyEdit_, 1, 1);

    panelLayout->addWidget(inputBox);

    // --- Операции ---
    auto* opsBox = new QGroupBox(QStringLiteral("Операции"), panel);
    auto* opsLayout = new QVBoxLayout(opsBox);

    QPushButton* setPosBtn = new QPushButton(QStringLiteral("Установить позицию"), opsBox);
    QPushButton* moveBtn = new QPushButton(QStringLiteral("Переместить"), opsBox);
    QPushButton* toggleDoorsBtn = new QPushButton(QStringLiteral("Открыть/закрыть двери"), opsBox);
    QPushButton* toggleHeadlightsBtn = new QPushButton(QStringLiteral("Включить/выключить фары"), opsBox);
    QPushButton* updateBtn = new QPushButton(QStringLiteral("Обновить"), opsBox);

    opsLayout->addWidget(setPosBtn);
    opsLayout->addWidget(moveBtn);
    opsLayout->addWidget(toggleDoorsBtn);
    opsLayout->addWidget(toggleHeadlightsBtn);
    opsLayout->addWidget(updateBtn);

    panelLayout->addWidget(opsBox);

    statusLabel_ = new QLabel(QStringLiteral("Создайте фигуру."), panel);
    panelLayout->addWidget(statusLabel_);

    panelLayout->addStretch(1);

    auto showError = [this](const std::exception& e)
    {
        QMessageBox::critical(this, QStringLiteral("Ошибка"), e.what());
    };

    QObject::connect(createRectBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            createRectangle();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(createCarBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            createCar();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(setPosBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            const double x = readRequiredDouble(xEdit_, QStringLiteral("x"));
            const double y = readRequiredDouble(yEdit_, QStringLiteral("y"));
            requireFigure().setPosition(x, y);
            statusLabel_->setText(QStringLiteral("Позиция обновлена."));
            canvas_->update();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(moveBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            const double dx = readRequiredDouble(dxEdit_, QStringLiteral("dx"));
            const double dy = readRequiredDouble(dyEdit_, QStringLiteral("dy"));
            requireFigure().moveBy(dx, dy);
            statusLabel_->setText(QStringLiteral("Фигура перемещена."));
            canvas_->update();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(toggleDoorsBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            Car* car = dynamic_cast<Car*>(figure_.get());
            if (!car)
            {
                throw FigureException(QStringLiteral("Двери доступны только для автомобиля.").toStdString());
            }
            car->toggleDoors();
            statusLabel_->setText(QStringLiteral("Двери переключены."));
            canvas_->update();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(toggleHeadlightsBtn, &QPushButton::clicked, this, [this, showError]()
    {
        try
        {
            Car* car = dynamic_cast<Car*>(figure_.get());
            if (!car)
            {
                throw FigureException(QStringLiteral("Фары доступны только для автомобиля.").toStdString());
            }
            car->toggleHeadlights();
            statusLabel_->setText(QStringLiteral("Фары переключены."));
            canvas_->update();
        }
        catch (const std::exception& e)
        {
            showError(e);
        }
    });

    QObject::connect(updateBtn, &QPushButton::clicked, this, [this]()
    {
        canvas_->update();
    });
}

MovingRectangle& MainWindow::requireFigure()
{
    if (!figure_)
    {
        throw FigureException(QStringLiteral("Сначала создайте фигуру кнопкой «Создать прямоугольник» или «Создать автомобиль».").toStdString());
    }
    return *figure_;
}

double MainWindow::readRequiredDouble(QLineEdit* edit, const QString& fieldName)
{
    const QString txt = edit->text().trimmed();
    if (txt.isEmpty())
    {
        throw ValidationError(QStringLiteral("Поле «%1» пустое.").arg(fieldName).toStdString());
    }

    bool ok = false;
    const double v = txt.toDouble(&ok);
    if (!ok || !std::isfinite(v))
    {
        throw ValidationError(QStringLiteral("Поле «%1» должно содержать число.").arg(fieldName).toStdString());
    }

    return v;
}

void MainWindow::createRectangle()
{
    figure_ = std::make_unique<MovingRectangle>();
    canvas_->setFigure(figure_.get());
    statusLabel_->setText(QStringLiteral("Создан прямоугольник."));
    canvas_->update();
}

void MainWindow::createCar()
{
    figure_ = std::make_unique<Car>();
    canvas_->setFigure(figure_.get());
    statusLabel_->setText(QStringLiteral("Создан автомобиль."));
    canvas_->update();
}

