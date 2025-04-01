#include "StartPage.h"
#include <QVBoxLayout>
#include <QLabel>

StartPage::StartPage(QWidget* parent)
    : QWidget(parent),
    startButton(new QPushButton(QString::fromUtf8("进入游戏"), this))

{   // 在StartPage和GamePage的构造函数中都添加
    setAutoFillBackground(true); // 必须设置才能显示背景
    setupUI();
    setupConnections();
}

StartPage::~StartPage(){}

void StartPage::setupUI()
{
    setMinimumSize(800, 600);  

    // 设置背景图片
    QPixmap bg(":/MazeGame/image/start.jpg");
    bg = bg.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, bg);
    this->setPalette(palette);

    // 设置字体样式
    QFont font("Microsoft YaHei", 28, QFont::Bold);
    QLabel* welcomeLabel = new QLabel(QString::fromUtf8("欢迎来到迷宫游戏"), this);
    welcomeLabel->setFont(font);
    welcomeLabel->setStyleSheet(
        "color: white;"
        "background-color: rgba(0, 0, 0, 150);"  // 添加半透明背景
        "padding: 10px;"
        "border-radius: 10px;"
    );

    // 按钮样式优化
    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: #3E8E41;"
        "border: 2px solid #ffffff;"
        "color: white;"
        "padding: 20px 40px;"
        "text-align: center;"
        "font-size: 20px;"
        "border-radius: 15px;"
        "cursor: pointer;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}"
    );

    // 重新调整布局，增加按钮与文字的间距
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addStretch(1);  // 增加上方空间
    mainLayout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
    mainLayout->addStretch(1);  // 在文字和按钮之间增加空白区域
    mainLayout->addWidget(startButton, 0, Qt::AlignCenter);
    mainLayout->addStretch(2);  // 增加按钮与底部的间距
    setLayout(mainLayout);
}

void StartPage::setupConnections()
{
    connect(startButton, &QPushButton::clicked, this, &StartPage::onStartButtonClicked);
}

void StartPage::onStartButtonClicked()
{
    GamePage* gamePage = new GamePage();
    gamePage->show();
    this->close(); 
}

