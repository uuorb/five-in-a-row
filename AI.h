#ifndef AI_H
#define AI_H

#include <QComboBox>
#include "BiPlay.h"
#include <stdlib.h>
#include <cstdlib>
#include <QTime>
#include <ctime>
#include <memory.h>
#include <stdio.h>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
class AiGame : public DoGame
{
public:
    AiGame();

public slots:

protected:
    virtual void mousePressEvent(QMouseEvent *event);

private:
    void ComMoveChess();

private:

};

#endif //AI_H
