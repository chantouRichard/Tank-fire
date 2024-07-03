#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>

namespace Ui {
class level1;
}

class level1 : public QWidget
{
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    ~level1();

signals:
    void back();
private:
    Ui::level1 *ui;
};

#endif // LEVEL1_H
