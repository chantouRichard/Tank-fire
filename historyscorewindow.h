#ifndef HISTORYSCOREWINDOW_H
#define HISTORYSCOREWINDOW_H

#include "global.h"
#include <QMainWindow>
#include <QPushButton>
#include <QTableWidget>
#include <QCoreApplication>
#include "qtmaterialscrollbar.h"
#include"simplebutton.h"
class HistoryscoreWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HistoryscoreWindow(QWidget *parent = nullptr);
    ~HistoryscoreWindow();
    void setupUI();
    void loadScoresFromFile(const QString& filename);
    HoverFillButton* returnButton; // 返回按钮公共属性

private:
    QTableWidget* scoreTableWidget;
    QtMaterialScrollBar* verticalScrollBar;    

signals:

};

#endif // HISTORYSCOREWINDOW_H
