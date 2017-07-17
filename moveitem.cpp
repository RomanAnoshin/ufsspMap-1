#include "moveitem.h"


MoveItem::MoveItem(QObject *parent): QObject(parent), QGraphicsItem()
{
    setFlags(QGraphicsItem::ItemIsMovable);
    color=QColor(Qt::red);
}

MoveItem::~MoveItem()
{

}

QRectF MoveItem::boundingRect() const
{
    return QRectF (-2,-2,5,5);
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(color);
    painter->setBrush(color);
    painter->drawEllipse(-2,-2,5,5);
    Q_UNUSED(option);
    Q_UNUSED(widget);

}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
    Q_UNUSED(event);
}

int MoveItem::type() const
{
    return 123;
}

void MoveItem::setColor(QColor color)
{
    this->color=color;
}
