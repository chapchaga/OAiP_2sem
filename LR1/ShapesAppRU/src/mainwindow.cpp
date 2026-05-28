#include "mainwindow.h"
#include "animationstep.h"
#include <QToolBar>
#include <QAction>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QListWidget>
#include <QGroupBox>
#include <QScrollArea>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QInputDialog>
#include <QSplitter>
#include <cmath>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Редактор фигур");
    resize(1200, 750);
    setupStyleSheet();

    m_canvas = new Canvas(this);
    setCentralWidget(m_canvas);

    connect(m_canvas, &Canvas::selectionChanged, this, &MainWindow::onSelectionChanged);
    connect(m_canvas, &Canvas::shapesChanged, this, &MainWindow::onShapesChanged);
    connect(m_canvas, &Canvas::animationFinished, this, &MainWindow::onAnimFinished);

    // ── Меню ──
    auto fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction("Новый", this, &MainWindow::onClearAll, QKeySequence::New);
    fileMenu->addAction("Открыть...", this, &MainWindow::onLoad, QKeySequence::Open);
    fileMenu->addAction("Сохранить...", this, &MainWindow::onSave, QKeySequence::Save);

    auto editMenu = menuBar()->addMenu("Правка");
    editMenu->addAction("Удалить", this, &MainWindow::onDeleteSelected, QKeySequence::Delete);
    editMenu->addAction("Сгруппировать (Ctrl+G)", this, &MainWindow::onGroupSelected, QKeySequence("Ctrl+G"));
    editMenu->addAction("Разгруппировать (Ctrl+Shift+G)", this, &MainWindow::onUngroupSelected, QKeySequence("Ctrl+Shift+G"));

    // ── Панель инструментов ──
    auto toolbar = addToolBar("Инструменты");
    toolbar->setIconSize({24,24});
    toolbar->setMovable(false);
    toolbar->setStyleSheet("QToolBar{background:#2b2d30;border:none;spacing:4px;padding:4px;}"
                           "QToolButton{color:black;background:#e8eaf0;border-radius:5px;padding:4px 8px;font-weight:600;font-size:12px;}"
                           "QToolButton:checked{background:#4a90d9;color:white;}"
                           "QToolButton:hover{background:#c5cae9;}");

    auto makeAction=[&](const QString& name, Canvas::Tool tool){
        auto a=toolbar->addAction(name);
        a->setCheckable(true);
        connect(a, &QAction::triggered, [=](bool checked){
            if(checked){ m_canvas->setTool(tool);
                for(auto* act:toolbar->actions()) if(act!=a) act->setChecked(false);
            } else { m_canvas->setTool(Canvas::Select); }
        });
        return a;
    };

    auto selAct=makeAction("▷ Выбор", Canvas::Select);
    selAct->setChecked(true);
    toolbar->addSeparator();
    makeAction("● Круг",        Canvas::DrawCircle);
    makeAction("△ Треугольник", Canvas::DrawTriangle);
    makeAction("▭ Прямоугольник", Canvas::DrawRectangle);
    makeAction("□ Квадрат",     Canvas::DrawSquare);
    makeAction("◇ Ромб",        Canvas::DrawRhombus);
    makeAction("✦ Звезда 5",    Canvas::DrawStar5);
    makeAction("✶ Звезда 6",    Canvas::DrawStar6);
    makeAction("✸ Звезда 8",    Canvas::DrawStar8);
    makeAction("⬡ Шестиугольник", Canvas::DrawHexagon);
    makeAction("➤ Стрелка",     Canvas::DrawArrow);
    toolbar->addSeparator();
    toolbar->addAction("🗗 Сгруппировать", this, &MainWindow::onGroupSelected)->setShortcut(QKeySequence("Ctrl+G"));
    toolbar->addAction("⇥ Разгруппировать", this, &MainWindow::onUngroupSelected);
    toolbar->addAction("🗑 Удалить", this, &MainWindow::onDeleteSelected);

    // ── Панель свойств ──
    m_propDock = new QDockWidget("Свойства", this);
    m_propDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    auto propWidget = new QWidget;
    auto propLayout = new QVBoxLayout(propWidget);
    propLayout->setSpacing(8);
    propLayout->setContentsMargins(8,8,8,8);

    m_shapeInfoLabel = new QLabel("Ничего не выбрано");
    m_shapeInfoLabel->setWordWrap(true);
    m_shapeInfoLabel->setStyleSheet("font-weight:600;color:#3a3a5c;padding:4px;background:#eef;border-radius:4px;");
    propLayout->addWidget(m_shapeInfoLabel);

    // Цвета
    auto colorGroup=new QGroupBox("Цвета");
    auto colorLayout=new QHBoxLayout(colorGroup);
    m_fillBtn=new QPushButton("Заливка");
    m_strokeBtn=new QPushButton("Обводка");
    colorLayout->addWidget(m_fillBtn);
    colorLayout->addWidget(m_strokeBtn);
    propLayout->addWidget(colorGroup);

    // Трансформации
    auto transGroup=new QGroupBox("Трансформация");
    auto transForm=new QFormLayout(transGroup);

    m_xSpin=new QDoubleSpinBox; m_xSpin->setRange(-9999,9999); m_xSpin->setDecimals(1);
    m_ySpin=new QDoubleSpinBox; m_ySpin->setRange(-9999,9999); m_ySpin->setDecimals(1);
    m_angleSpin=new QDoubleSpinBox; m_angleSpin->setRange(-720,720); m_angleSpin->setSuffix("°");
    m_scaleSpin=new QDoubleSpinBox; m_scaleSpin->setRange(0.01,10); m_scaleSpin->setValue(1.5); m_scaleSpin->setSingleStep(0.1);
    m_durationSpin=new QSpinBox; m_durationSpin->setRange(100,5000); m_durationSpin->setValue(600); m_durationSpin->setSuffix(" мс");

    transForm->addRow("Центр X:", m_xSpin);
    transForm->addRow("Центр Y:", m_ySpin);
    transForm->addRow("Поворот:", m_angleSpin);
    transForm->addRow("Масштаб:", m_scaleSpin);
    transForm->addRow("Длительность:", m_durationSpin);

    auto btnRow=new QHBoxLayout;
    m_moveBtn=new QPushButton("Переместить"); m_rotateBtn=new QPushButton("Повернуть"); m_scaleBtn=new QPushButton("Масштаб");
    btnRow->addWidget(m_moveBtn); btnRow->addWidget(m_rotateBtn); btnRow->addWidget(m_scaleBtn);
    transForm->addRow(new QWidget, btnRow);
    propLayout->addWidget(transGroup);

    propLayout->addStretch();
    m_propDock->setWidget(propWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_propDock);

    // ── Панель анимации ──
    m_animDock = new QDockWidget("Анимационные последовательности", this);
    m_animDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    auto animWidget=new QWidget;
    auto animLayout=new QVBoxLayout(animWidget);
    animLayout->setSpacing(6); animLayout->setContentsMargins(8,8,8,8);

    auto animTopRow=new QHBoxLayout;
    auto newSeqBtn=new QPushButton("+ Новая последовательность");
    m_playAnimBtn=new QPushButton("▶ Воспроизвести");
    m_playAnimBtn->setStyleSheet("background:#2ecc71;color:white;font-weight:700;");
    animTopRow->addWidget(newSeqBtn); animTopRow->addWidget(m_playAnimBtn);
    animLayout->addLayout(animTopRow);

    m_seqList=new QListWidget; m_seqList->setMaximumHeight(80);
    animLayout->addWidget(new QLabel("Последовательности:"));
    animLayout->addWidget(m_seqList);

    animLayout->addWidget(new QLabel("Шаги последовательности:"));
    m_stepList=new QListWidget; m_stepList->setMaximumHeight(100);
    animLayout->addWidget(m_stepList);

    auto stepGroup=new QGroupBox("Добавить шаг");
    auto stepForm=new QFormLayout(stepGroup);
    m_stepTypeCombo=new QComboBox;
    m_stepTypeCombo->addItems({"Перемещение","Поворот","Масштаб","Сгруппировать","Разгруппировать"});
    m_stepDxSpin=new QDoubleSpinBox; m_stepDxSpin->setRange(-500,500); m_stepDxSpin->setPrefix("Δx:");
    m_stepDySpin=new QDoubleSpinBox; m_stepDySpin->setRange(-500,500); m_stepDySpin->setPrefix("Δy:");
    m_stepAngleSpin=new QDoubleSpinBox; m_stepAngleSpin->setRange(-720,720); m_stepAngleSpin->setSuffix("°");
    m_stepFactorSpin=new QDoubleSpinBox; m_stepFactorSpin->setRange(0.1,5); m_stepFactorSpin->setValue(1.5); m_stepFactorSpin->setSingleStep(0.1);
    m_stepDurSpin=new QSpinBox; m_stepDurSpin->setRange(100,5000); m_stepDurSpin->setValue(600); m_stepDurSpin->setSuffix(" мс");

    stepForm->addRow("Тип:", m_stepTypeCombo);
    stepForm->addRow("Delta X:", m_stepDxSpin);
    stepForm->addRow("Delta Y:", m_stepDySpin);
    stepForm->addRow("Угол:", m_stepAngleSpin);
    stepForm->addRow("Коэффициент:", m_stepFactorSpin);
    stepForm->addRow("Длительность:", m_stepDurSpin);

    auto stepBtns=new QHBoxLayout;
    auto addStepBtn=new QPushButton("+ Добавить шаг");
    auto remStepBtn=new QPushButton("- Удалить");
    stepBtns->addWidget(addStepBtn); stepBtns->addWidget(remStepBtn);
    stepForm->addRow(stepBtns);
    animLayout->addWidget(stepGroup);
    animLayout->addStretch();
    m_animDock->setWidget(animWidget);
    addDockWidget(Qt::LeftDockWidgetArea, m_animDock);

    // Статусная строка
    statusBar()->showMessage("Готово — выберите инструмент и нарисуйте фигуру на холсте");

    // Connections
    connect(m_fillBtn, &QPushButton::clicked, this, &MainWindow::onFillColor);
    connect(m_strokeBtn, &QPushButton::clicked, this, &MainWindow::onStrokeColor);
    connect(m_moveBtn, &QPushButton::clicked, [this]{
        auto sel=m_canvas->selectedShapes();
        if(sel.isEmpty()) return;
        for(auto& s:sel) s->animateMove(QPointF(m_xSpin->value()-s->centroid().x(), m_ySpin->value()-s->centroid().y()), m_durationSpin->value());
    });
    connect(m_rotateBtn, &QPushButton::clicked, [this]{
        auto sel=m_canvas->selectedShapes();
        if(sel.isEmpty()) return;
        QPointF center=m_canvas->selectedShapes().first()->centroid();
        for(auto& s:sel) s->animateRotate(m_angleSpin->value(), center, m_durationSpin->value());
    });
    connect(m_scaleBtn, &QPushButton::clicked, [this]{
        auto sel=m_canvas->selectedShapes();
        if(sel.isEmpty()) return;
        QPointF center=sel.first()->centroid();
        for(auto& s:sel) s->animateScale(m_scaleSpin->value(), center, m_durationSpin->value());
    });

    connect(newSeqBtn, &QPushButton::clicked, this, &MainWindow::onNewAnim);
    connect(addStepBtn, &QPushButton::clicked, this, &MainWindow::onAddAnimStep);
    connect(remStepBtn, &QPushButton::clicked, this, &MainWindow::onRemoveAnimStep);
    connect(m_playAnimBtn, &QPushButton::clicked, this, &MainWindow::onPlayAnim);
    connect(m_seqList, &QListWidget::currentRowChanged, [this](int row){
        m_currentSeqIdx=row; updateAnimPanel();
    });
}

void MainWindow::setupStyleSheet() {
    setStyleSheet(
        "QMainWindow{background:#f0f2f5;}"
        "QDockWidget{background:#fff;font-weight:600;}"
        "QDockWidget::title{background:#2b2d30;color:white;padding:6px;font-size:13px;}"
        "QGroupBox{font-weight:700;color:#3a3a5c;border:1px solid #d0d3e0;border-radius:6px;margin-top:8px;padding-top:4px;}"
        "QGroupBox::title{subcontrol-origin:margin;left:8px;padding:0 4px;}"
        "QPushButton{background:#4a5568;color:black;border:none;border-radius:5px;padding:5px 12px;"
                    "font-weight:600;font-size:12px;}"
        "QPushButton:hover{background:#5a6578;}"
        "QPushButton:pressed{background:#3a4558;}"
        "QDoubleSpinBox,QSpinBox,QComboBox{border:1px solid #c0c4d0;border-radius:4px;"
                                          "padding:3px 6px;background:white;color:black;}"
        "QLabel{color:#2d3748;font-size:12px;}"
        "QListWidget{border:1px solid #d0d3e0;border-radius:4px;background:white;color:black;}"
        "QListWidget::item:selected{background:#4a90d9;color:white;}"
        "QMenuBar{background:#2b2d30;color:white;}"
        "QMenuBar::item{padding:4px 12px;}"
        "QMenuBar::item:selected{background:#4a90d9;}"
        "QMenu{background:white;color:black;border:1px solid #ccc;}"
        "QMenu::item:selected{background:#4a90d9;color:white;}"
        "QStatusBar{background:#2b2d30;color:white;font-size:11px;}"
    );
}

void MainWindow::onSelectionChanged() {
    updatePropertiesPanel();
}

void MainWindow::onShapesChanged() {
    updatePropertiesPanel();
}

void MainWindow::updatePropertiesPanel() {
    auto sel=m_canvas->selectedShapes();
    if(sel.isEmpty()){
        m_shapeInfoLabel->setText("Ничего не выбрано");
        return;
    }
    QString info;
    for(auto& s:sel){
        info+=QString("<b>%1</b><br>Площадь: %2<br>Периметр: %3<br>Центр масс: (%4, %5)<br><br>")
            .arg(s->typeName())
            .arg(s->area(),0,'f',1)
            .arg(s->perimeter(),0,'f',1)
            .arg(s->centroid().x(),0,'f',1)
            .arg(s->centroid().y(),0,'f',1);
    }
    m_shapeInfoLabel->setText(info.trimmed());
    if(!sel.isEmpty()){
        m_xSpin->setValue(sel.first()->centroid().x());
        m_ySpin->setValue(sel.first()->centroid().y());
        m_fillBtn->setStyleSheet(QString("background:%1;color:black;font-weight:600;").arg(sel.first()->fillColor().name()));
        m_strokeBtn->setStyleSheet(QString("background:%1;color:%2;font-weight:600;")
            .arg(sel.first()->strokeColor().name())
            .arg(sel.first()->strokeColor().lightness()<128?"white":"black"));
    }
}

void MainWindow::updateAnimPanel() {
    m_stepList->clear();
    if(m_currentSeqIdx<0||m_currentSeqIdx>=m_canvas->sequences().size()) return;
    auto seq=m_canvas->sequences()[m_currentSeqIdx];
    for(int i=0;i<seq->count();i++)
        m_stepList->addItem(QString("%1. %2").arg(i+1).arg(seq->step(i).describe()));
}

void MainWindow::onFillColor() {
    auto sel=m_canvas->selectedShapes();
    if(sel.isEmpty()) return;
    QColor c=QColorDialog::getColor(sel.first()->fillColor(), this, "Цвет заливки");
    if(c.isValid()) for(auto& s:sel) s->setFillColor(c);
    updatePropertiesPanel();
}

void MainWindow::onStrokeColor() {
    auto sel=m_canvas->selectedShapes();
    if(sel.isEmpty()) return;
    QColor c=QColorDialog::getColor(sel.first()->strokeColor(), this, "Цвет обводки");
    if(c.isValid()) for(auto& s:sel) s->setStrokeColor(c);
    updatePropertiesPanel();
}

void MainWindow::onSave() {
    QString path=QFileDialog::getSaveFileName(this,"Сохранить сцену","","Файлы фигур (*.shapes);;Все файлы (*)");
    if(!path.isEmpty()) m_canvas->saveToFile(path);
}

void MainWindow::onLoad() {
    QString path=QFileDialog::getOpenFileName(this,"Открыть сцену","","Файлы фигур (*.shapes);;Все файлы (*)");
    if(!path.isEmpty()){ m_canvas->loadFromFile(path); updateAnimPanel(); }
}

void MainWindow::onClearAll() {
    if(QMessageBox::question(this,"Очистить","Удалить все фигуры?")==QMessageBox::Yes)
        m_canvas->clearAll();
}

void MainWindow::onDeleteSelected() { m_canvas->deleteSelected(); }
void MainWindow::onGroupSelected()  { m_canvas->groupSelected(); }
void MainWindow::onUngroupSelected(){ m_canvas->ungroupSelected(); }

void MainWindow::onNewAnim() {
    bool ok;
    QString name=QInputDialog::getText(this,"Новая последовательность","Название:", QLineEdit::Normal,"Последовательность", &ok);
    if(!ok||name.isEmpty()) return;
    auto seq=std::make_shared<AnimationSequence>(name);
    m_canvas->addSequence(seq);
    m_seqList->addItem(name);
    m_seqList->setCurrentRow(m_seqList->count()-1);
}

void MainWindow::onAddAnimStep() {
    if(m_currentSeqIdx<0||m_currentSeqIdx>=m_canvas->sequences().size()) return;
    auto seq=m_canvas->sequences()[m_currentSeqIdx];
    AnimationStep step;
    int t=m_stepTypeCombo->currentIndex();
    step.type=(AnimationStep::Type)t;
    step.delta={m_stepDxSpin->value(),m_stepDySpin->value()};
    step.angle=m_stepAngleSpin->value();
    step.factor=m_stepFactorSpin->value();
    step.durationMs=m_stepDurSpin->value();
    seq->addStep(step);
    updateAnimPanel();
}

void MainWindow::onRemoveAnimStep() {
    if(m_currentSeqIdx<0) return;
    auto seq=m_canvas->sequences()[m_currentSeqIdx];
    int row=m_stepList->currentRow();
    if(row>=0){ seq->removeStep(row); updateAnimPanel(); }
}

void MainWindow::onPlayAnim() {
    if(m_currentSeqIdx<0) return;
    m_playAnimBtn->setEnabled(false);
    m_playAnimBtn->setText("⏳ Воспроизведение...");
    statusBar()->showMessage("Анимация воспроизводится...");
    m_canvas->playSequence(m_currentSeqIdx);
}

void MainWindow::onAnimFinished() {
    m_playAnimBtn->setEnabled(true);
    m_playAnimBtn->setText("▶ Воспроизвести");
    statusBar()->showMessage("Анимация завершена — фигуры возвращены на исходные позиции");
}
