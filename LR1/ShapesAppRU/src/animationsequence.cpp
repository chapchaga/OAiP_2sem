#include "animationsequence.h"
#include <QJsonArray>

AnimationSequence::AnimationSequence(const QString& name, QObject* parent)
    : QObject(parent), m_name(name) {}

void AnimationSequence::addStep(const AnimationStep& step) { m_steps.append(step); }
void AnimationSequence::removeStep(int index) {
    if(index>=0 && index<m_steps.size()) m_steps.removeAt(index);
}
void AnimationSequence::clear() { m_steps.clear(); }

QJsonObject AnimationSequence::toJson() const {
    QJsonObject obj;
    obj["name"]=m_name;
    QJsonArray arr;
    for(auto& s:m_steps) arr.append(s.toJson());
    obj["steps"]=arr;
    return obj;
}

void AnimationSequence::fromJson(const QJsonObject& obj) {
    m_name=obj["name"].toString();
    m_steps.clear();
    for(auto v:obj["steps"].toArray())
        m_steps.append(AnimationStep::fromJson(v.toObject()));
}
