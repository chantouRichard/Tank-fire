#ifndef PASS_H
#define PASS_H
#include<QPushButton>
#include <QWidget>

namespace Ui {
class pass;
}

class pass : public QWidget
{
    Q_OBJECT

public:
    QPushButton * backbtn;

    explicit pass(QWidget *parent = nullptr);
    ~pass();

    //布尔数组
    bool pass_judge[4]={false};

signals:
    void back();

private:
    Ui::pass *ui;
};

#endif // PASS_H
