#include "canvas.h"
#include "circle.h"
#include "triangle.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "star.h"
#include "hexagon.h"
#include "arrow.h"

#include <QPainter>
#include <QMouseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QTimer>
#include <cmath>

Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    setMinimumSize(600,500);
    setMouseTracking(true);
    setStyleSheet("background:#f8f9fa;");
}

QVector<std::shared_ptr<Shape>> Canvas::selectedShapes() const {
    QVector<std::shared_ptr<Shape>> sel;
    for(auto& s:m_shapes) if(s->isSelected()) sel.append(s);
    return sel;
}

void Canvas::clearSelection() {
    for(auto& s:m_shapes) s->setSelected(false);
    emit selectionChanged();
    update();
}

void Canvas::deleteSelected() {
    m_shapes.erase(std::remove_if(m_shapes.begin(), m_shapes.end(),
        [](auto& s){ return s->isSelected(); }), m_shapes.end());
    emit shapesChanged(); update();
}

void Canvas::groupSelected() {
    auto sel=selectedShapes();
    if(sel.size()<2) return;
    auto grp=std::make_shared<ShapeGroup>();
    for(auto& s:sel) { grp->addShape(s); m_shapes.erase(std::remove(m_shapes.begin(),m_shapes.end(),s),m_shapes.end()); }
    grp->setSelected(true);
    connect(grp.get(), &Shape::changed, this, [this](){ update(); });
    m_shapes.append(grp);
    emit shapesChanged(); emit selectionChanged(); update();
}

void Canvas::ungroupSelected() {
    QVector<std::shared_ptr<Shape>> toAdd;
    QVector<std::shared_ptr<Shape>> toRemove;
    for(auto& s:m_shapes){
        if(!s->isSelected()) continue;
        if(auto g=std::dynamic_pointer_cast<ShapeGroup>(s)){
            for(auto& child:g->shapes()){ child->setSelected(true); toAdd.append(child); }
            toRemove.append(s);
        }
    }
    for(auto& s:toRemove) m_shapes.erase(std::remove(m_shapes.begin(),m_shapes.end(),s),m_shapes.end());
    for(auto& s:toAdd){
        connect(s.get(), &Shape::changed, this, [this](){ update(); });
        m_shapes.append(s);
    }
    emit shapesChanged(); emit selectionChanged(); update();
}

std::shared_ptr<Shape> Canvas::createShape(const QPointF& center, const QPointF& end) const {
    double dx=end.x()-center.x(), dy=end.y()-center.y();
    double r=std::sqrt(dx*dx+dy*dy);
    double w=std::abs(dx)*2, h=std::abs(dy)*2;
    if(r<5) r=40;
    if(w<10) w=80; if(h<10) h=60;
    std::shared_ptr<Shape> s;
    switch(m_tool){
    case DrawCircle:    s=std::make_shared<Circle>(center,r); break;
    case DrawTriangle:  s=std::make_shared<Triangle>(center+QPointF(0,-r),center+QPointF(-r*0.866,r*0.5),center+QPointF(r*0.866,r*0.5)); break;
    case DrawRectangle: s=std::make_shared<Rectangle>(center,w,h); break;
    case DrawSquare:    { double side=std::min(w,h); s=std::make_shared<Square>(center,side); break; }
    case DrawRhombus:   s=std::make_shared<Rhombus>(center,h,w); break;
    case DrawStar5:     s=std::make_shared<Star>(Star::Five,center,r,r*0.4); break;
    case DrawStar6:     s=std::make_shared<Star>(Star::Six,center,r,r*0.55); break;
    case DrawStar8:     s=std::make_shared<Star>(Star::Eight,center,r,r*0.6); break;
    case DrawHexagon:   s=std::make_shared<Hexagon>(center,r); break;
    case DrawArrow:     s=std::make_shared<Arrow>(center,w,h); break;
    default: break;
    }
    return s;
}

void Canvas::mousePressEvent(QMouseEvent* e) {
    QPointF pt=e->position();
    if(m_tool==Select){
        // Check if clicked on existing shape (back to front)
        bool hit=false;
        for(int i=m_shapes.size()-1;i>=0;i--){
            if(m_shapes[i]->contains(pt)){
                if(!(e->modifiers()&Qt::ControlModifier)) clearSelection();
                m_shapes[i]->setSelected(true);
                hit=true;
                // Setup drag
                m_dragging=true; m_dragStart=pt;
                m_dragOrigPos.clear();
                for(auto& s:m_shapes) m_dragOrigPos.append(s->centroid());
                break;
            }
        }
        if(!hit){ clearSelection(); }
        emit selectionChanged();
    } else {
        m_drawing=true; m_startPt=pt; m_curPt=pt;
    }
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent* e) {
    QPointF pt=e->position();
    if(m_dragging && (e->buttons()&Qt::LeftButton)){
        QPointF delta=pt-m_dragStart;
        for(auto& s:m_shapes) if(s->isSelected()) s->move(delta);
        m_dragStart=pt;
        update();
    } else if(m_drawing){
        m_curPt=pt; update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* e) {
    QPointF pt=e->position();
    if(m_dragging){ m_dragging=false; }
    if(m_drawing){
        m_drawing=false;
        auto s=createShape(m_startPt, pt);
        if(s){
            connect(s.get(), &Shape::changed, this, [this](){ update(); });
            m_shapes.append(s);
            emit shapesChanged();
        }
    }
    update();
}

void Canvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    // Grid
    p.setPen(QPen(QColor(220,225,230),1));
    for(int x=0;x<width();x+=20) p.drawLine(x,0,x,height());
    for(int y=0;y<height();y+=20) p.drawLine(0,y,width(),y);

    for(auto& s:m_shapes) s->draw(p);

    // Rubber band while drawing
    if(m_drawing && m_tool!=Select){
        p.setPen(QPen(Qt::darkBlue,1,Qt::DashLine));
        p.setBrush(QColor(100,149,237,40));
        p.drawRect(QRectF(m_startPt,m_curPt).normalized());
    }
}

void Canvas::clearAll() {
    m_shapes.clear(); emit shapesChanged(); update();
}

void Canvas::saveToFile(const QString& path) {
    QJsonArray arr;
    for(auto& s:m_shapes) arr.append(s->toJson());
    QJsonObject root; root["shapes"]=arr;
    // Save sequences
    QJsonArray seqArr;
    for(auto& seq:m_sequences) seqArr.append(seq->toJson());
    root["sequences"]=seqArr;
    QFile f(path);
    if(f.open(QIODevice::WriteOnly))
        f.write(QJsonDocument(root).toJson());
}

static std::shared_ptr<Shape> shapeFromJson2(const QJsonObject& obj) {
    QString t=obj["type"].toString();
    std::shared_ptr<Shape> s;
    if(t=="Circle")    { auto c=std::make_shared<Circle>(); c->fromJson(obj); s=c; }
    else if(t=="Triangle")   { auto c=std::make_shared<Triangle>(); c->fromJson(obj); s=c; }
    else if(t=="Square")     { auto c=std::make_shared<Square>(); c->fromJson(obj); s=c; }
    else if(t=="Rectangle")  { auto c=std::make_shared<Rectangle>(); c->fromJson(obj); s=c; }
    else if(t=="Rhombus")    { auto c=std::make_shared<Rhombus>(); c->fromJson(obj); s=c; }
    else if(t=="Star")       { auto c=std::make_shared<Star>(); c->fromJson(obj); s=c; }
    else if(t=="Hexagon")    { auto c=std::make_shared<Hexagon>(); c->fromJson(obj); s=c; }
    else if(t=="Arrow")      { auto c=std::make_shared<Arrow>(); c->fromJson(obj); s=c; }
    else if(t=="Group")      { auto c=std::make_shared<ShapeGroup>(); c->fromJson(obj); s=c; }
    return s;
}

void Canvas::loadFromFile(const QString& path) {
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) return;
    auto doc=QJsonDocument::fromJson(f.readAll());
    auto root=doc.object();
    m_shapes.clear();
    for(auto v:root["shapes"].toArray()){
        auto s=shapeFromJson2(v.toObject());
        if(s){ connect(s.get(), &Shape::changed, this, [this](){ update(); }); m_shapes.append(s); }
    }
    m_sequences.clear();
    for(auto v:root["sequences"].toArray()){
        auto seq=std::make_shared<AnimationSequence>();
        seq->fromJson(v.toObject());
        m_sequences.append(seq);
    }
    emit shapesChanged(); update();
}

void Canvas::playSequence(int index) {
    if(index<0||index>=m_sequences.size()) return;
    if(m_animating) return;
    m_animating=true;

    // Save original positions/states for revert
    QVector<QPointF> origPos;
    for(auto& s:m_shapes) origPos.append(s->centroid());

    auto seq=m_sequences[index];
    playStep(seq, 0, origPos);
}

void Canvas::playStep(std::shared_ptr<AnimationSequence> seq, int stepIdx,
                      QVector<QPointF> originalPositions) {
    if(stepIdx>=seq->count()){
        // Sequence done — revert to original positions
        int i=0;
        for(auto& s:m_shapes){
            if(i<originalPositions.size())
                s->setCentroid(originalPositions[i]);
            i++;
        }
        m_animating=false;
        emit animationFinished();
        update();
        return;
    }
    const AnimationStep& step=seq->step(stepIdx);
    auto sel=selectedShapes();
    if(sel.isEmpty()) sel=m_shapes.toList().toVector(); // apply to all if nothing selected

    int steps=std::max(1, step.durationMs/16);

    if(step.type==AnimationStep::Group){ groupSelected(); QTimer::singleShot(100,this,[=](){ playStep(seq,stepIdx+1,originalPositions); }); return; }
    if(step.type==AnimationStep::Ungroup){ ungroupSelected(); QTimer::singleShot(100,this,[=](){ playStep(seq,stepIdx+1,originalPositions); }); return; }

    // Count how many shapes are animating
    int* remaining=new int(sel.size());
    for(auto& s:sel){
        auto onStep=[this](){ update(); };
        auto onDone=[=]() mutable {
            (*remaining)--;
            if(*remaining<=0){
                delete remaining;
                playStep(seq,stepIdx+1,originalPositions);
            }
        };
        // We animate each shape manually
        QPointF stepDelta;
        double stepAngle=0, stepFactor=1;
        if(step.type==AnimationStep::Move){ stepDelta=step.delta/steps; }
        else if(step.type==AnimationStep::Rotate){ stepAngle=step.angle/steps; }
        else if(step.type==AnimationStep::Scale){ stepFactor=std::pow(step.factor,1.0/steps); }

        int interval=std::max(1, step.durationMs/steps);
        int* count=new int(0);
        QTimer* t=new QTimer(this);
        QPointF center=s->centroid();
        connect(t, &QTimer::timeout, this, [=]() mutable {
            if(step.type==AnimationStep::Move) s->move(stepDelta);
            else if(step.type==AnimationStep::Rotate) s->rotate(stepAngle, center);
            else if(step.type==AnimationStep::Scale) s->scale(stepFactor, center);
            update();
            if(++(*count)>=steps){
                t->stop(); t->deleteLater();
                delete count;
                onDone();
            }
        });
        t->start(interval);
    }
}
