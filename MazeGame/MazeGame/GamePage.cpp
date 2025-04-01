#include "GamePage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QGraphicsLineItem>
#include <QMessageBox>

GamePage::GamePage(QWidget* parent)
    : QWidget(parent),
    mazeView(new QGraphicsView(this)),
    mazeScene(new QGraphicsScene(this)),
    generateButton(new QPushButton("生成迷宫", this)),
    startButton(new QPushButton("开始游戏", this)),
    exitButton(new QPushButton("退出游戏", this)),
    //sizeSpinBox(new QSpinBox(this)),
    rowSpinBox(new QSpinBox(this)),
    colSpinBox(new QSpinBox(this)),
    algorithmComboBox(new QComboBox(this)),
    currentPathIndex(0),  // 初始化为显示第一条路径
    pathInfoText(new QTextEdit(this)),  // 这里分配内存
    maze(nullptr)
{  
    // 设置文本框属性
    pathInfoText->setReadOnly(true);
    pathInfoText->setFixedWidth(150);
    pathInfoText->setFixedHeight(300);
    pathInfoText->setStyleSheet(
        "QTextEdit {"
        "   background-color: #f8f9fa;"      // 浅灰色背景
        "   border: 2px solid #ced4da;"      // 浅灰色边框
        "   border-radius: 8px;"             // 圆角效果
        "   padding: 5px;"                   // 内边距
        "   font: 16px 'Segoe UI';"          // 字体设置
        "   color: #2d3436;"                 // 字体颜色
        "}"
        "QScrollBar:vertical {"
        "   border: none;"
        "   background: #f8f9fa;"            // 滚动条背景
        "   width: 10px;"                    // 滚动条宽度
        "   margin: 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #adb5bd;"            // 滚动条手柄颜色
        "   border-radius: 4px;"
        "}"
    );
    setStyleSheet(
        "QPushButton {"
        "   background-color: #4CAF50;"      // 按钮底色
        "   border: none;"
        "   color: white;"
        "   padding: 12px 24px;"
        "   text-align: center;"
        "   text-decoration: none;"
        "   font-size: 16px;"
        "   border-radius: 8px;"
        "   margin: 4px;"
        "}"
    );
    // 在StartPage和GamePage的构造函数中都添加
    setAutoFillBackground(true); // 必须设置才能显示背景
    setupUI();
    setupConnections();
}

GamePage::~GamePage()
{
    delete maze; 
}

void GamePage::setupUI()
{
    setMinimumSize(800, 600);

    // 设置迷宫视图
    mazeView->setScene(mazeScene);
    mazeView->setRenderHint(QPainter::Antialiasing);
    mazeView->setRenderHint(QPainter::SmoothPixmapTransform);
    mazeView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 设置迷宫大小
    rowSpinBox->setRange(5, 15);
    colSpinBox->setRange(5, 15);
    rowSpinBox->setValue(5);
    colSpinBox->setValue(5);

    // 设置算法选择下拉框
    algorithmComboBox->addItem("非递归算法");
    algorithmComboBox->addItem("递归算法");

    // 设置按钮
    generateButton->setStyleSheet("padding: 10px; font-size: 16px;");
    startButton->setStyleSheet("padding: 10px; font-size: 16px;");
    exitButton->setStyleSheet("padding: 10px; font-size: 16px;");

    // 布局管理
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* controlLayout = new QHBoxLayout;

    nextPathButton = new QPushButton("Next", this);
    nextPathButton->setVisible(false); 
    controlLayout->addWidget(nextPathButton);
    connect(nextPathButton, &QPushButton::clicked, this, &GamePage::onShowNextPath);

    controlLayout->addWidget(new QLabel("行数："));
    controlLayout->addWidget(rowSpinBox);
    controlLayout->addWidget(new QLabel("列数："));
    controlLayout->addWidget(colSpinBox);
    controlLayout->addWidget(new QLabel("算法选择："));
    controlLayout->addWidget(algorithmComboBox);

    controlLayout->addWidget(generateButton);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(exitButton);

    // 创建一个垂直布局并将迷宫和按钮布局放入
    QVBoxLayout* layoutForMazeAndControl = new QVBoxLayout;

    layoutForMazeAndControl->addWidget(mazeView, 0, Qt::AlignCenter);  // 迷宫居中显示
    layoutForMazeAndControl->addLayout(controlLayout);

    mainLayout->addLayout(layoutForMazeAndControl);  // 将迷宫和控件布局添加到主布局
    setLayout(mainLayout);
}

void GamePage::setupConnections()
{
    connect(generateButton, &QPushButton::clicked, this, &GamePage::onGenerateMaze);
    connect(startButton, &QPushButton::clicked, this, &GamePage::onStartGame);
    connect(exitButton, &QPushButton::clicked, this, &GamePage::onExitGame);
}

void GamePage::onGenerateMaze()
{
    int rows = rowSpinBox->value();
    int cols = colSpinBox->value();
    if (maze) delete maze;
    maze = new Maze(rows, cols);  
    maze->generateRandomMaze();  // 调用后端生成迷宫
    drawMaze();  // 根据新迷宫重绘
    pathInfoText->clear();
}

void GamePage::drawPath() {
    int cellSize = 30;

    QLinearGradient pathGradient(0, 0, 0, 1);
    pathGradient.setColorAt(0, QColor("#2ecc71"));
    pathGradient.setColorAt(1, QColor("#27ae60"));
    pathGradient.setCoordinateMode(QGradient::ObjectMode);

    QPen pathPen(Qt::green, 3);
    pathPen.setCapStyle(Qt::RoundCap);

    // 清除旧路径（通过标记 "path" 识别）
    for (auto item : mazeScene->items()) {
        if (item->data(0) == "path") {
            mazeScene->removeItem(item);
            delete item;
        }
    }

    if (algorithmComboBox->currentIndex() == 0) {  // 非递归路径
        auto pathTriplets = maze->getPathTriplets(); 
        QPointF prevPos;
        for (const auto& triplet : pathTriplets) {
            int row = get<0>(triplet);
            int col = get<1>(triplet);
            QPointF center(col * cellSize + cellSize / 2, row * cellSize + cellSize / 2);
            // 绘制路径点
            auto dot = mazeScene->addEllipse(center.x() - 3, center.y() - 3, 6, 6, pathPen, Qt::green);
            dot->setData(0, "path");
            // 绘制连接线
            if (!prevPos.isNull()) {
                mazeScene->addLine(QLineF(prevPos, center), pathPen)->setData(0, "path");
            }
            prevPos = center;
        }
    }
    else {  // 递归路径
        if (!maze->getAllPaths().empty()) {
            const auto& path = maze->getAllPaths()[currentPathIndex-1];  // 使用当前路径索引
            QPointF prevPos;
            for (const auto& p : path) {
                int row = p.first, col = p.second;
                QPointF center(col * cellSize + cellSize / 2, row * cellSize + cellSize / 2);
                auto dot = mazeScene->addEllipse(center.x() - 3, center.y() - 3, 6, 6, pathPen, Qt::green);
                dot->setData(0, "path");
                if (!prevPos.isNull()) {
                    mazeScene->addLine(QLineF(prevPos, center), pathPen)->setData(0, "path");
                }
                prevPos = center;
            }
            if (currentPathIndex == maze->getAllPaths().size()) {
                QMessageBox::information(this, "提示", "已显示所有路径！");
            }
        }
    }
}

void GamePage::showPathInfo() {
    if (algorithmComboBox->currentIndex() == 0) {
        auto triplets = maze->getPathTriplets();
        QString info;
        for (const auto& t : triplets) {
            info += QString("(%1, %2, %3)\n")
                .arg(get<0>(t))
                .arg(get<1>(t))
                .arg(get<2>(t));
        }
        pathInfoText->setText(info);
    }
}

void GamePage::onStartGame() {
    if (!maze) {
        QMessageBox::warning(this, "错误", "请先生成迷宫！");
        return;
    }

    bool found = false;
    int algorithm = algorithmComboBox->currentIndex();
    nextPathButton->setVisible(algorithm == 1);
    pathInfoText->setVisible(algorithm == 0); // 控制文本框可见性

    if (algorithm == 0) {  // 非递归
        found = maze->findPathNonRecursive(0, 0, maze->getRows() - 1, maze->getCols() - 1);
        currentPathIndex = 0; // 非递归不需要路径索引
    }
    else {               // 递归
        maze->findAllPathsRecursive(0, 0, maze->getRows() - 1, maze->getCols() - 1);
        found = !maze->getAllPaths().empty();
        currentPathIndex = 1; // 重置索引 
    }

    if (found) {
        drawPath();
        showPathInfo();
    }
    else {
        QMessageBox::information(this, "提示", "没有找到路径！");
    }
}

void GamePage::onExitGame(){close();}

void GamePage::drawMaze()
{
    mazeScene->clear();  // 清空场景
    if (!maze) return;

    int cellSize = 30;  // 每个格子的固定大小
    int rows = maze->getRows();
    int cols = maze->getCols();

    // 计算迷宫的整体像素大小
    int mazeWidth = cols * cellSize;
    int mazeHeight = rows * cellSize;

    // 设置场景大小，确保完整显示迷宫
    mazeScene->setSceneRect(0, 0, mazeWidth, mazeHeight);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int x = col * cellSize;
            int y = row * cellSize;

            // 创建迷宫格子
            QGraphicsRectItem* cell = mazeScene->addRect(x, y, cellSize, cellSize);
            cell->setPen(QPen(Qt::black));
            cell->setBrush(maze->getMaze()[row][col] == 1 ? Qt::red : Qt::white);
        }
    }
    // 添加 "起点" 
    QGraphicsTextItem* startLabel = mazeScene->addText("起点");
    startLabel->setDefaultTextColor(QColor("#2980b9"));
    startLabel->setFont(QFont("Arial", 8, QFont::Bold));
    startLabel->setTextWidth(cellSize);  // 限制宽度
    startLabel->setPos(cellSize * 0.2, cellSize * -0.1);  // 让文字稍微靠上

    // 添加 "终点" 
    QGraphicsTextItem* endLabel = mazeScene->addText("终点");
    endLabel->setDefaultTextColor(QColor("#27ae60"));
    endLabel->setFont(QFont("Arial", 8, QFont::Bold)); 
    endLabel->setTextWidth(cellSize);
    endLabel->setPos((cols - 1) * cellSize + cellSize * 0.2, (rows - 1) * cellSize + cellSize * -0.1);  // 让文字稍微靠上

    // 让 QGraphicsView 居中显示迷宫
    mazeView->setScene(mazeScene);
    mazeView->setAlignment(Qt::AlignCenter);
    mazeView->centerOn(mazeWidth / 2, mazeHeight / 2);

    // 调整 QGraphicsView 大小，使其正好能放下迷宫
    int viewWidth = qMin(mazeWidth + 20, 800);  // 最大宽度 800，防止窗口过大
    int viewHeight = qMin(mazeHeight + 20, 600); // 最大高度 600，防止窗口过大
    mazeView->setFixedSize(viewWidth, viewHeight);
}

void GamePage::onShowNextPath() {
    if (currentPathIndex < maze->getAllPaths().size()) {
        ++currentPathIndex;
        drawPath();   
    }
    else {
        QMessageBox::information(this, "提示", "已显示所有路径！");
    }
}

void GamePage::resizeEvent(QResizeEvent* event) {
    QPixmap bg(":/MazeGame/image/game.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 强制拉伸填充窗口
    QPalette palette;
    palette.setBrush(QPalette::Window, bg);
    this->setPalette(palette);
    QWidget::resizeEvent(event);  // 保证事件处理继续执行
}