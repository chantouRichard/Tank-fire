#include "historyscorewindow.h"
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QScrollBar>
#include <QLabel>
#include <QFontDatabase>
#include <QPalette>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>

HistoryscoreWindow::HistoryscoreWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUI();
}

HistoryscoreWindow::~HistoryscoreWindow()
{
    delete scoreTableWidget;
    delete returnButton;
}

void HistoryscoreWindow::setupUI()
{
    // 设置窗口标题
    this->setWindowTitle("历史分数记录");

    // 去除标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 设置窗口大小
    this->setFixedSize(2000, 1200); // 根据背景图片的分辨率调整

    // 设置整个窗口的背景图片
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/1/Res/res/score_back.png"))); // 引用资源文件中的背景图片
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    // 创建透明的主窗口部件
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet(
                "QWidget {"
                "   background-color: rgba(0, 0, 0, 150);" // 透明黑色背景，透明度60%
                "}");
    this->setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 添加顶部透明区域 - 图片上移的逻辑语句块
    QWidget* topSpacer = new QWidget(centralWidget);
    topSpacer->setFixedHeight(100); // 你可以调整这个值来改变图片向上移动的距离
    topSpacer->setStyleSheet("background: transparent;");
    mainLayout->addWidget(topSpacer);

    // 创建分数表格
    scoreTableWidget = new QTableWidget(centralWidget);
    scoreTableWidget->setStyleSheet(
                "QTableWidget {"
                "   background-color: rgba(255, 255, 255, 180);" // 白色半透明背景
                "   color: black;"                         // 字体颜色为黑色
                "   border: none;"                         // 无边框
                "   gridline-color: rgba(0, 0, 0, 50);"    // 网格线颜色
                "}"
                "QTableWidget::item {"
                "   padding: 10px;"      // 单元格内边距
                "}"
                "QTableWidget::item:selected {"
                "   background-color: rgba(30, 144, 255, 150);" // 选中行背景颜色
                "   color: black;"             // 选中行文字颜色
                "}"
                "QHeaderView::section {"
                "   background-color: rgba(255, 255, 255, 0);"  // 表头背景透明
                "   color: white;"             // 表头字体颜色
                "   font-size: 32px;"          // 表头字体大小
                "   font-family: 'Verdana', sans-serif;"  // 表头字体
                "   border: none;"                         // 无边框
                "}"
                );

    // 设置表格中的字体样式
    QFont font("Verdana", 24, QFont::Bold); // 设置字体为 Verdana，大小24，加粗
    scoreTableWidget->setFont(font);

    // 设置表头
    scoreTableWidget->setColumnCount(2);
    scoreTableWidget->setHorizontalHeaderLabels(QStringList() << "玩家名称" << "得分");
    scoreTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 设置表头视图的字体样式
    QFont headerFont("Verdana", 32, QFont::Bold); // 设置表头字体为 Verdana，大小32，加粗
    scoreTableWidget->horizontalHeader()->setFont(headerFont);
    scoreTableWidget->verticalHeader()->setVisible(false); // 隐藏行号

    scoreTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    scoreTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    scoreTableWidget->setDragEnabled(true);
    scoreTableWidget->setDragDropMode(QAbstractItemView::InternalMove);

    // 启用滚动条并设置隐藏/显示效果
    verticalScrollBar = new QtMaterialScrollBar(scoreTableWidget);
    scoreTableWidget->setVerticalScrollBar(verticalScrollBar);

    QPropertyAnimation *animationShow = new QPropertyAnimation(verticalScrollBar, "opacity");
    animationShow->setDuration(500);
    animationShow->setStartValue(0.0);
    animationShow->setEndValue(1.0);

    QPropertyAnimation *animationHide = new QPropertyAnimation(verticalScrollBar, "opacity");
    animationHide->setDuration(500);
    animationHide->setStartValue(1.0);
    animationHide->setEndValue(0.0);

    connect(verticalScrollBar, &QScrollBar::valueChanged, this, [animationShow, animationHide]() {
        animationShow->start();
        animationHide->start();
    });

    mainLayout->addWidget(scoreTableWidget);

    // 创建返回按钮
    returnButton = new QPushButton("返回", centralWidget);
    returnButton->setStyleSheet(
                "QPushButton {"
                "   font-size: 32px;"
                "   font-weight: bold;"
                "   color: white;"
                "   border: 2px solid #FFD700;"  // 边框颜色
                "   border-radius: 10px;"        // 圆角
                "   background-color: rgba(0, 0, 0, 0);" // 内部颜色透明
                "   padding: 8px;"
                "}"
                "QPushButton:hover {"
                "   border-color: #FFA500;"
                "}"
                "QPushButton:pressed {"
                "   border-color: #FF8C00;"
                "}"
                );

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(returnButton);

    mainLayout->addLayout(buttonLayout);

    // 加载分数记录
    QString scoreFilename = QCoreApplication::applicationDirPath() + score_filename; // 修改为实际的文件路径
    loadScoresFromFile(scoreFilename);
}

void HistoryscoreWindow::loadScoresFromFile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件：" << filename;
        return;
    }
    else
        qDebug() << "成功打开文件：" << filename;

    QList<QPair<QString, int>> scores; // 用于存储分数记录的列表

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList data = line.split(":");
        if (data.size() == 2) {
            QString playerName = data[0];
            int score = data[1].toInt();
            qDebug() << "读取到玩家：" << playerName << " 得分：" << score;
            scores.append(qMakePair(playerName, score));
        } else {
            qDebug() << "读取行格式错误：" << line;
        }
    }

    file.close();

    // 按分数降序排序
    std::sort(scores.begin(), scores.end(), [](const QPair<QString, int>& a, const QPair<QString, int>& b) {
        return a.second > b.second;
    });

    // 显示所有记录
    scoreTableWidget->setRowCount(scores.size());

    for (int i = 0; i < scores.size(); ++i)
    {
        QTableWidgetItem* playerNameItem = new QTableWidgetItem(scores[i].first);
        QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(scores[i].second));

        playerNameItem->setTextAlignment(Qt::AlignCenter);
        scoreItem->setTextAlignment(Qt::AlignCenter);

        scoreTableWidget->setItem(i, 0, playerNameItem);
        scoreTableWidget->setItem(i, 1, scoreItem);
    }
}
