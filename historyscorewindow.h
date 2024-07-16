#ifndef HISTORYSCOREWINDOW_H
#define HISTORYSCOREWINDOW_H

#include "global.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QCoreApplication>
#include "qtmaterialscrollbar.h"
#include "simplebutton.h"

class HistoryscoreWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数
    explicit HistoryscoreWindow(QWidget *parent = nullptr);
    // 析构函数
    ~HistoryscoreWindow();
    // 设置UI
    void setupUI();
    // 从文件加载分数
    void loadScoresFromFile(const QString& filename);
    // 返回按钮公共属性
    HoverFillButton* returnButton;

private:
    // 分数表格控件
    QTableWidget* scoreTableWidget;
    // 垂直滚动条
    QtMaterialScrollBar* verticalScrollBar;

signals:

};

#endif // HISTORYSCOREWINDOW_H
