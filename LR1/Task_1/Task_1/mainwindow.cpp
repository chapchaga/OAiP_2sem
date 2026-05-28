#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    area = new RenderArea(this);

    QPushButton *doorBtn = new QPushButton("Дверь");
    QPushButton *lightBtn = new QPushButton("Фары");
    QPushButton *leftBtn = new QPushButton("Влево");
    QPushButton *rightBtn = new QPushButton("Вправо");
    QPushButton *stopBtn = new QPushButton("Стоп");

    layout->addWidget(stopBtn);
    layout->addWidget(area);
    layout->addWidget(doorBtn);
    layout->addWidget(lightBtn);
    layout->addWidget(leftBtn);
    layout->addWidget(rightBtn);

    setCentralWidget(central);

    connect(stopBtn, &QPushButton::clicked, area, &RenderArea::stop);
    connect(doorBtn, &QPushButton::clicked, area, &RenderArea::toggleDoor);
    connect(lightBtn, &QPushButton::clicked, area, &RenderArea::toggleLights);
    connect(leftBtn, &QPushButton::clicked, area, &RenderArea::moveLeft);
    connect(rightBtn, &QPushButton::clicked, area, &RenderArea::moveRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}
