#include "startwidget.h"
#include <QPainter>
#include <QPixmap>
#include <QFont>
#include <QFile>
//#include <QMouseEvent>

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(533,754); //界面大小
    //QCursor cursor;//设置鼠标外观
    //cursor.setShape(Qt::PointingHandCursor);
    //setCursor(cursor);

    //setWindowFlags(Qt::FramelessWindowHint);//隐藏标题栏

    Player = new DoGame;
    AiPlayer = new AiGame;
    setWindowIcon(QIcon(":/images/logo.ico"));

    QFile file(":/qss/qss/startQss.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);

    QFont font("Microsoft YaHei",13,QFont::Bold);

    ToComputer = new QPushButton(tr("人机对战"),this);
    ToComputer->setFont(font);
    ToComputer->setGeometry(229,510,100,33);

    ToPlayer = new QPushButton(tr("玩家对战"),this);
    ToPlayer->setFont(font);
    ToPlayer->setGeometry(229,560,100,33);

    //SetGame = new QPushButton(tr("游戏设置"),this);

    ExitGame = new QPushButton(tr("退出游戏"),this);
    ExitGame->setFont(font);
    ExitGame->setGeometry(229,610,100,33);



    connect(ToPlayer,SIGNAL(clicked()),Player,SLOT(show()));
    connect(ToPlayer,SIGNAL(clicked()),this,SLOT(close()));//同时关闭窗口
    connect(ExitGame,SIGNAL(clicked()),this,SLOT(close()));

    connect(ToComputer,SIGNAL(clicked()),AiPlayer,SLOT(show()));
    connect(ToComputer,SIGNAL(clicked()),this,SLOT(close()));
}

void StartWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage image;
    image.load(":/images/images/backGround.jpg");
    painter.drawImage(QPoint(0,0),image);
}
