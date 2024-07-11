#include "graphicspicitem.h"
#include <QPainter>

MyGraphicsPicItem::MyGraphicsPicItem(const QPixmap &pixmap)
    : QObject(), QGraphicsPixmapItem(pixmap), m_selected(false)
{
}

void MyGraphicsPicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_selected = !m_selected;
    update();
    emit this->pic_clicked();  // Emit the clicked signal
    QGraphicsPixmapItem::mousePressEvent(event);
}

void MyGraphicsPicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    if (m_selected)
    {
        QPen pen(Qt::yellow, 3); // Set border color and width
        painter->setPen(pen);
        painter->drawRect(boundingRect());
    }
}
