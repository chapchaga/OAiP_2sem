#pragma once
#include <QWidget>
#include <QVector>
#include <memory>
#include "shape.h"
#include "shapegroup.h"
#include "animationsequence.h"

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget* parent=nullptr);

    enum Tool { Select, DrawCircle, DrawTriangle, DrawRectangle, DrawSquare,
                DrawRhombus, DrawStar5, DrawStar6, DrawStar8, DrawHexagon, DrawArrow };

    void setTool(Tool t) { m_tool=t; clearSelection(); }
    Tool tool() const { return m_tool; }

    void groupSelected();
    void ungroupSelected();
    void deleteSelected();

    QVector<std::shared_ptr<Shape>>& shapes() { return m_shapes; }
    QVector<std::shared_ptr<Shape>> selectedShapes() const;

    // Animation sequences
    void addSequence(std::shared_ptr<AnimationSequence> seq) { m_sequences.append(seq); }
    QVector<std::shared_ptr<AnimationSequence>>& sequences() { return m_sequences; }
    void playSequence(int index);
    bool isAnimating() const { return m_animating; }

    // Serialization
    void saveToFile(const QString& path);
    void loadFromFile(const QString& path);

    void clearAll();
    void clearSelection();

signals:
    void selectionChanged();
    void shapesChanged();
    void animationFinished();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    QVector<std::shared_ptr<Shape>> m_shapes;
    QVector<std::shared_ptr<AnimationSequence>> m_sequences;
    Tool m_tool { Select };

    // Drawing state
    bool m_drawing { false };
    QPointF m_startPt, m_curPt;

    // Drag state
    bool m_dragging { false };
    QPointF m_dragStart;
    QVector<QPointF> m_dragOrigPos; // original centroids

    bool m_animating { false };

    std::shared_ptr<Shape> createShape(const QPointF& center, const QPointF& end) const;
    void drawRubberBand(QPainter& p) const;

    // Play sequence helpers
    void playStep(std::shared_ptr<AnimationSequence> seq, int stepIdx,
                  QVector<QPointF> originalPositions);
};
