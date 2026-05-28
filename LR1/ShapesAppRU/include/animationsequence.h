#pragma once
#include "animationstep.h"
#include <QObject>
#include <QVector>
#include <QJsonObject>

class AnimationSequence : public QObject {
    Q_OBJECT
public:
    explicit AnimationSequence(const QString& name="Sequence", QObject* parent=nullptr);

    QString name() const { return m_name; }
    void setName(const QString& n) { m_name=n; }

    void addStep(const AnimationStep& step);
    void removeStep(int index);
    void clear();
    int count() const { return m_steps.size(); }
    const AnimationStep& step(int i) const { return m_steps[i]; }
    const QVector<AnimationStep>& steps() const { return m_steps; }

    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

private:
    QString m_name;
    QVector<AnimationStep> m_steps;
};
