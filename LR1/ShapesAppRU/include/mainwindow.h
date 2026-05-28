#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QDockWidget>
#include "canvas.h"
#include "animationsequence.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr);

private slots:
    void onSelectionChanged();
    void onShapesChanged();
    void onAddAnimStep();
    void onPlayAnim();
    void onNewAnim();
    void onRemoveAnimStep();
    void onFillColor();
    void onStrokeColor();
    void onSave();
    void onLoad();
    void onClearAll();
    void onDeleteSelected();
    void onGroupSelected();
    void onUngroupSelected();
    void onAnimFinished();

private:
    Canvas* m_canvas;
    // Tools panel
    QWidget* buildToolsPanel();
    // Properties panel
    QDockWidget* m_propDock;
    QLabel* m_shapeInfoLabel;
    QPushButton* m_fillBtn, *m_strokeBtn;
    QDoubleSpinBox* m_xSpin, *m_ySpin;
    QDoubleSpinBox* m_angleSpin, *m_scaleSpin;
    QPushButton* m_moveBtn, *m_rotateBtn, *m_scaleBtn;
    QSpinBox* m_durationSpin;

    // Animation panel
    QDockWidget* m_animDock;
    QListWidget* m_seqList;
    QListWidget* m_stepList;
    QComboBox* m_stepTypeCombo;
    QDoubleSpinBox* m_stepDxSpin, *m_stepDySpin, *m_stepAngleSpin, *m_stepFactorSpin;
    QSpinBox* m_stepDurSpin;
    QPushButton* m_playAnimBtn;
    int m_currentSeqIdx = -1;

    void updatePropertiesPanel();
    void updateAnimPanel();
    void setupStyleSheet();
};
