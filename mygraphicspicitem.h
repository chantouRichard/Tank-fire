#ifndef GRAPHICSPICITEM_H
#define GRAPHICSPICITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class GraphicsPicItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    GraphicsPicItem(const QPixmap &pixmap);

signals:
    void clicked(); // Define the clicked signal

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    bool m_selected;
    void setSelected(bool selected);
    bool isSelected() const;
};

#endif // GRAPHICSPICITEM_H
