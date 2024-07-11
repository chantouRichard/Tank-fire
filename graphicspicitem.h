#ifndef GRAPHICSPICITEM_H
#define GRAPHICSPICITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class MyGraphicsPicItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    MyGraphicsPicItem(const QPixmap &pixmap);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
signals:
    void pic_clicked(); // Define the clicked signal

private:
    bool m_selected;
};

#endif // GRAPHICSPICITEM_H
