#ifndef STARTWIDGET_H
#define STARTWIDGET_H
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <Qsound>
#include "BiPlay.h"
#include "ai.h"

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    
signals:
    
public slots:

private:
    QPushButton *ToComputer;//人机对战按钮
    QPushButton *ToPlayer;//玩家对战
    //QPushButton *SetGame;//设置
    QPushButton *ExitGame;//退出
    DoGame *Player;
    AiGame *AiPlayer;
    AiGame *b;
};

#endif // STARTWIDGET_H
