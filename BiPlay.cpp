#include "BiPlay.h"
#include <QMessageBox>
#include <QSound>
#include <QIcon>



DoGame::DoGame(QWidget *parent) :

    QWidget(parent),clickcount(0),win(0)
{
    this->resize(800,510);
    setWindowFlags(Qt::FramelessWindowHint);//隐藏标题栏
    setWindowIcon(QIcon(":/images/logo.ico"));

    SoundMovechess = new QSound(":/images/images/moves_sound.wav");


    startGame = new QPushButton(this);
    startGame->setGeometry(650,360,40,40);
    QFile startStyle(":/qss/qss/startPushButton.qss");//设置开始按钮的样式
    startStyle.open(QFile::ReadOnly);
    QString startStyleSheet = tr(startStyle.readAll());
    startGame->setStyleSheet(startStyleSheet);

    endGame = new QPushButton(this);
    endGame->setGeometry(700,360,40,40);
    QFile endStyle(":/qss/qss/endPushButton.qss");//设置结束按钮的样式
    endStyle.open(QFile::ReadOnly);
    QString endStyleSheet = tr(endStyle.readAll());
    endGame->setStyleSheet(endStyleSheet);

    withdraw = new QPushButton(this);
    withdraw->setGeometry(750,360,40,40);
    QFile withdrawStyle(":/qss/qss/withdrawPushButton.qss");//设置悔棋按钮的样式
    withdrawStyle.open(QFile::ReadOnly);
    QString withdrawStyleSheet = tr(withdrawStyle.readAll());
    withdraw->setStyleSheet(withdrawStyleSheet);

    diffculty = new QComboBox(this);
    diffculty->setGeometry(640,160,150,20);
    QFile diffculyStyle(":/qss/qss/diffculy.qss");//
    diffculyStyle.open(QFile::ReadOnly);
    QString diffculyStyleSheet = tr(diffculyStyle.readAll());
    diffculty->setStyleSheet(diffculyStyleSheet);

    diffculty->addItem(QWidget::tr("难度1－只会防守"));
    diffculty->addItem(QWidget::tr("难度2－尝试进攻"));
    diffculty->addItem(QWidget::tr("难度3－Todo采用博弈树"));
    diffculty->addItem(QWidget::tr("难度4－Todo博弈树层数增加"));
    diffculty->addItem(QWidget::tr("难度5－Todo加入棋谱"));

    for(int i=0; i<225; i++)//初始化棋子，并隐藏
    {
        showchess[i] = new QLabel(this);
        showchess[i]->hide();
    }
    for(int i=0; i<15; i++)//初始化棋盘上的棋子
    {
        for(int j=0; j<15; j++)
        {
            chess[i][j] = 0;//1为有，0为无
        }
    }

    win = 0;

    setMouseTracking(true);//鼠标追踪

    connect(endGame,SIGNAL(clicked()),this,SLOT(closeGame()));//结束按钮结束
    connect(startGame,SIGNAL(clicked()),this,SLOT(clearqipan()));//开始按钮开始游戏，并初始化棋盘
    connect(withdraw,SIGNAL(clicked()),this,SLOT(clearqipan()));//开始按钮开始游戏，并初始化棋盘


}


void DoGame::mousePressEvent(QMouseEvent *event)//鼠标按下事件，下棋
{
    int x;
    int y;
    if(event->button() == Qt::LeftButton)
    {
        offset = event->pos();//获取鼠标的坐标

        if(!win && offset.rx()>186&&offset.rx()<600&&offset.ry()>39&&offset.ry()<445)//棋盘区域
        {
            if(chess[(offset.rx()-210)/27][(offset.ry()-60)/27])//如果鼠标点击的地方有旗子
            {
                return;
            }
            x = (offset.rx()-210)/27;
            y = (offset.ry()-60)/27;

            if (offset.ry() > 415 && !chess[x][14])//补偿最后一格的误差
                y = 14;

            clickcount++;//根据点击次数判断是白棋还是黑棋
            movechess(x,y);//下棋子
            qDebug()<<x<<y<<win;
            win = isWin(x,y);
            if(win){//如果没有赢，则显示棋子
                if(clickcount%2)
                    QMessageBox::information(this, "BlackWin", "BlackWin", QMessageBox::Ok);
                else
                    QMessageBox::information(this, "WhiteWin", "WhiteWin", QMessageBox::Ok);
                }
        }
    }
}

void DoGame::movechess(int x,int y)//根据鼠标点击坐标下棋
{
    SoundMovechess->play();
    showchess[clickcount]->setVisible(true);
    //棋子的位置

    if(clickcount%2) //偶数为黑棋
    {
        showchess[clickcount]->setPixmap(QPixmap(":/images/images/blackchess.png"));
        showchess[clickcount-1]->setPixmap(QPixmap(":/images/images/whitechess.png"));
        chess[x][y] = 9;
    }
    else//白棋
    {
        showchess[clickcount]->setPixmap(QPixmap(":/images/images/whitechess.png"));
        showchess[clickcount-1]->setPixmap(QPixmap(":/images/images/blackchess.png"));
        chess[x][y] = 10;
    }

    showchess[clickcount]->setGeometry(x*27+203,y*27+54,24,24);//棋子的位置
}

void DoGame::mouseReleaseEvent(QMouseEvent *)
{

}

void DoGame::paintEvent(QPaintEvent *)//背景
{
    QPainter painter(this);
    QImage image;
    image.load(":/images/images/gamewidget.png");
    painter.drawImage(QPoint(0,0),image);
}

void DoGame::clearqipan()//初始化棋盘
{
    for(int i=0; i<225; i++)
    {
        showchess[i]->hide();
    }
    for(int i=0; i<15; i++)
    {
        for(int j=0; j<15; j++)
        {
            chess[i][j] = 0;
        }
    }
    clickcount = 0;
    win = 0;

}

void DoGame::mouseMoveEvent(QMouseEvent *event)//鼠标移动事件
{
    QString pos = QString("%1,%2").arg(event->pos().x()).arg(event->pos().y());//读取光标坐标
    QToolTip::showText(event->pos(),pos,this);

}

void DoGame::closeGame()//结束游戏
{
    clearqipan();
    this->close();
}

//1->赢
int DoGame::isWin(int x, int y)
{
     return f1(x, y) || f2(x, y) || f3(x, y) || f4(x ,y);
}

int DoGame::f1(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if( y - i >= 0 &&
           y + 4 - i <= 0xF &&
           chess[x][y - i] == chess[x][y + 1 - i] &&
           chess[x][y - i] == chess[x][y + 2 - i] &&
           chess[x][y - i] == chess[x][y + 3 - i] &&
           chess[x][y - i] == chess[x][y + 4 - i])
        return 1;
    }
    return 0;
}

int DoGame::f2(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if(x - i >= 0 &&
           x + 4 - i <= 0xF &&
           chess[x - i][y] == chess[x + 1 - i][y] &&
           chess[x - i][y] == chess[x + 2 - i][y] &&
           chess[x - i][y] == chess[x + 3 - i][y] &&
           chess[x - i][y] == chess[x + 4 - i][y])
           return 1;
    }
    return 0;
}

int DoGame::f3(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if((x - i >= 0) &&
           (y - i >= 0) &&
           (x + 4 - i <= 0xF) &&
           (y + 4 - i <= 0xF) &&
           (chess[x - i][y - i] == chess[x + 1 - i][y + 1 - i])&&
           (chess[x - i][y - i] == chess[x + 2 - i][y + 2 - i])&&
           (chess[x - i][y - i] == chess[x + 3 - i][y + 3 - i])&&
           (chess[x - i][y - i] == chess[x + 4 - i][y + 4 - i]))
           return 1;
    }
    return 0;
}

int DoGame::f4(int x, int y)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        if((x + i <= 0xF) &&
           (y - i >= 0  ) &&
           (x - 4 + i >= 0) &&
           (y + 4 - i <= 0xF) &&
           (chess[x + i][y - i] == chess[x - 1 + i][y + 1 - i]) &&
           (chess[x + i][y - i] == chess[x - 2 + i][y + 2 - i]) &&
           (chess[x + i][y - i] == chess[x - 3 + i][y + 3 - i]) &&
           (chess[x + i][y - i] == chess[x - 4 + i][y + 4 - i]))
           return 1;
    }
    return 0;
}


