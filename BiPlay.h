#ifndef DOGAME_H
#define DOGAME_H
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QBrush>
#include <QImage>
#include <QFile>
#include <QDebug>
#include <QToolTip>
#include <QTileRules>
#include <QLCDNumber>
#include <QDialog>
#include <QFont>
#include <QPen>
#include <QComboBox>
#include <Qsound>


class DoGame : public QWidget
{
    Q_OBJECT

public:
    explicit DoGame(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *event);//鼠标事件
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    
signals:
    
public slots:
    void closeGame();//结束游戏
    void clearqipan();//重置棋盘

public:

public:
    //StartWidget *start;
    QDialog *winDialog;
    QSound *SoundMovechess;//
    QPushButton *yes;
    QLabel *showchess[225];//用标签来显示棋子
    QPushButton *startGame;//开始按钮
    QPushButton *endGame;//结束按钮
    QPushButton *withdraw;//悔棋
    QPushButton *degree; //难度
    //QPushButton *takeAdvance;
    //Qpushbutton *setGame;
    int chess[15][15];//记录棋子的位置
    int clickcount;//记录点击次数来判断显示棋子的颜色
    QPoint offset;//记录鼠标的位置
    QComboBox *diffculty;
    int rex,rey;
    int sum;//记录棋子的最大相连个数
    int win;
    int x1,y1,x2,y2;
    int fiveLink[4];
    void movechess(int x,int y);
    int isWin(int x, int y);
    int f1(int x, int y);
    int f2(int x, int y);
    int f3(int x, int y);
    int f4(int x, int y);
};


#endif // DOGAME_H
