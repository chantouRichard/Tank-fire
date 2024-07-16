#include "mygraphicspicitem.h"
#include <QPainter>

GraphicsPicItem::GraphicsPicItem(const QPixmap &pixmap)
    : QGraphicsPixmapItem(pixmap), m_selected(false)
{
}

void GraphicsPicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_selected = !m_selected;
    update();
    emit clicked(); // Emit the clicked signal
    QGraphicsPixmapItem::mousePressEvent(event);
}

void GraphicsPicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    if (m_selected)
    {
        QPen pen(QColor(243, 248, 241),3); // 设置边框颜色和宽度
        painter->setPen(pen);
        painter->drawRoundedRect(boundingRect(), 10, 10); // 画圆角矩形，10 为圆角半径a
    }
}

void GraphicsPicItem::setSelected(bool selected)
{
    m_selected = selected;
    update();
}

bool GraphicsPicItem::isSelected() const
{
    return m_selected;
}
