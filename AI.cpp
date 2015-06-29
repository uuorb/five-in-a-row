#include "AI.h"
#include<QTime>
int Position(int x, int y, int value[15][15]);
void ChessScore(int chess[15][15],int score[15][15]);

void Robot(int *x,int *y,int *Sum,int value[][15]);
void ChessOne(int *x,int *y,int value[15][15]);
void Findscore(int *x,int *y,int chess[15][15]);
AiGame::AiGame()
{


}

//电脑第一次下子
void FindFirstChess(int *x,int *y,int value[15][15],int lx)
{
    int i,j;
    for (i=0;i<15;i++)
    {
        for(j=0;j<15;j++)
        {
            if (value[i][j] == 9)             //如果找到了玩家的棋子，在它的8个方的任意一点落子
            {

                if(lx == 0)
                {
                    *x = i+1;
                    *y = j+1;
                  if (Position(*x,*y,value)==0)
                      break;
                }
                else if(lx ==1)
                {
                    *x = i+1;
                    *y = j-1;
                    if (Position(*x,*y,value)==0) break;
                }
                else if(lx ==2)
                {
                    *x = i-1;
                    *y = j-1;
                    if (Position(*x,*y,value)==0) break;
                }
                else if(lx ==3)
                {
                    *x = i-1;
                    *y = j+1;
                    if (Position(*x,*y,value)==0) break;
                }
                else if(lx ==4)
                {
                    *x = i-1;
                    *y = j;//上
                    if (Position(*x,*y,value)==0) break;
                }
                else if(lx ==5)
                {
                    *x = i;
                    *y = j-1;//左
                    if (Position(*x,*y,value)==0) break;
                }
                else if(lx ==6)
                {
                    *x = i;
                    *y = j+1;//右
                    if (Position(*x,*y,value)==0) break;
                }
                else
                {
                    *x = i+1;
                    *y = j;//下
                    if (Position(*x,*y,value)==0) break;
                }
            }
        }
    }
}
int isEqua_Array(int A[9],int B[9],int i,int j){//判断两数组从i->j是否相等，若是，返回1，否则返回0
    int flag = 1;

    for (;i <= j ;i++){

        flag = flag &(!(A[i] xor B[i]));
    }
    return flag;
}
//常见的几种棋
int A[9] = {9,9,9,9,0,3,3,3,3};//0为空位,3为不用考虑
int a[9] = {10,10,10,10,0,3,3,3,3};

int B[9] = {3,3,3,3,0,9,9,9,9};
int b[9] = {3,3,3,3,0,10,10,10,10};
//活四

//活三
int C[9] = {3,9,9,9,0,3,3,3,3};
int c[9] = {3,10,10,10,0,3,3,3,3};
//-1,9,9,9,0,0,0,0,0
int D[9] = {3,3,3,3,0,9,9,9,3};
int d[9] = {3,3,3,3,0,10,10,10,3};
//
int E[9] = {3,3,3,9,0,9,10,3,3};
int e[9] = {3,3,3,10,0,10,9,3,3};
int F[9] = {3,3,9,9,0,9,3,3,3};
int f[9] = {3,3,10,10,0,10,3,3,3};

void evaluation_level1(int score[15][15][4],int chess[15][15]){
    int evaluate[4][9];
    int i,j,k,z;
    for(i = 0;i<15;i++)
        for(j = 0;j < 15;j++)
            for(k = 0;k<4;k++)
            score[i][j][k] = 0; //初始化

    for(i = 0;i<15;i++)
        for(j = 0;j < 15;j++){
            if(chess[i][j] == 0){//没有子
                for(k = 0;k <= 4;k++){
                if(i-k >= 0){ //生成evaluate的左半边
                    evaluate[0][4-k] = chess[i-k][j];//横
                    evaluate[1][4-k] = chess[i][j-k];//竖
                }
                else{    //-1表示碰壁
                    evaluate[0][4-k] = -1;
                    evaluate[1][4-k] = -1;
                    }
                if(i+k < 15){ //生成evaluate的左半边
                    evaluate[0][4+k] = chess[i+k][j];
                    evaluate[1][4+k] = chess[i][j+k];//竖
                }
                else{
                    evaluate[0][4+k] = -1;
                    evaluate[1][4+k] = -1;
                    }
                if ( ((i-k) >= 0 ) && ( (j-k) >= 0))
                    evaluate[2][4-k] = chess[i-k][j-k];//右斜
                else
                    evaluate[2][4-k] = -1;

                if(((i+k) < 15 ) && ((j+k) < 15))
                    evaluate[2][4+k] = chess[i+k][j+k];//右斜
                else
                    evaluate[2][4+k] = -1;
                /**********/
                if (( (i-k) >= 0 ) && ( (j+k) < 15))
                    evaluate[3][4-k] = chess[i-k][j+k];//左斜
                else
                    evaluate[3][4-k] = -1;

                if(((i+k) < 15 ) && ((j-k) > 15))
                    evaluate[3][4+k] = chess[i-k][j+k];//左斜
                else
                    evaluate[3][4+k] = -1;
                /******/
                for(z = 0;z < 4;z++)
                    evaluate[z][4] = 0;
            }
               //差一步就死的情况
            for(z = 0;z<4;z++){
            if (isEqua_Array(evaluate[z],C,1,4) || isEqua_Array(evaluate[z],D,4,7)||
                   isEqua_Array(evaluate[z],E,3,6) || isEqua_Array(evaluate[z],F,2,5))
                score[i][j][z] = 1000;
            //已经死等别人眼瞎的情况
            if (isEqua_Array(evaluate[z],A,0,4) || isEqua_Array(evaluate[z],B,4,8))//对该空子的上下4个点判断
                score[i][j][z] = 10000;
            }
        }
     }
}

void evaluation_level2(int score_level2[15][15][4][2],int chess[15][15]){//评价函数为自己＋别人
    int evaluate[4][9];
    int i,j,k,l,z;
    for(i = 0;i<15;i++)
        for(j = 0;j < 15;j++)
            for(k = 0;k<4;k++)
                for(l = 0;l<2;l++)
                    score_level2[i][j][k][l] = 0; //初始化

    for(i = 0;i<15;i++)
        for(j = 0;j < 15;j++){
            if(chess[i][j] == 0){//没有子
                for(k = 0;k <= 4;k++){
                if(i-k >= 0){ //生成evaluate的左半边
                    evaluate[0][4-k] = chess[i-k][j];//横
                    evaluate[1][4-k] = chess[i][j-k];//竖
                }
                else{    //-1表示碰壁
                    evaluate[0][4-k] = -1;
                    evaluate[1][4-k] = -1;
                    }
                if(i+k < 15){ //生成evaluate的左半边
                    evaluate[0][4+k] = chess[i+k][j];
                    evaluate[1][4+k] = chess[i][j+k];//竖
                }
                else{
                    evaluate[0][4+k] = -1;
                    evaluate[1][4+k] = -1;
                    }
                if ( ((i-k) >= 0 ) && ( (j-k) >= 0))
                    evaluate[2][4-k] = chess[i-k][j-k];//右斜
                else
                    evaluate[2][4-k] = -1;

                if(((i+k) < 15 ) && ((j+k) < 15))
                    evaluate[2][4+k] = chess[i+k][j+k];//右斜
                else
                    evaluate[2][4+k] = -1;
                /**********/
                if (( (i-k) >= 0 ) && ( (j-k) >= 0))
                    evaluate[3][4-k] = chess[i+k][j-k];//左斜
                else
                    evaluate[3][4-k] = -1;

                if(((i-k) >= 0 ) && ((j+k) < 15))
                    evaluate[3][4+k] = chess[i-k][j+k];//左斜
                else
                    evaluate[3][4+k] = -1;
                /******/
                for(z = 0;z < 4;z++)
                    evaluate[z][4] = 0;
            }
               //差一步就死的情况
            for(z = 0;z<4;z++){
            if (isEqua_Array(evaluate[z],C,1,4) || isEqua_Array(evaluate[z],D,4,7)||
                   isEqua_Array(evaluate[z],E,3,6) || isEqua_Array(evaluate[z],F,2,5))
                score_level2[i][j][z][0] = 20000;

            if (isEqua_Array(evaluate[z],c,1,4) || isEqua_Array(evaluate[z],d,4,7)||
                   isEqua_Array(evaluate[z],e,3,6) || isEqua_Array(evaluate[z],f,2,5))
                score_level2[i][j][z][1] = 5000;
            //已经死等别人眼瞎的情况
            if (isEqua_Array(evaluate[z],A,0,4) || isEqua_Array(evaluate[z],B,4,8))//对该空子的上下4个点判断
                score_level2[i][j][z][0] = 40000;
            if (isEqua_Array(evaluate[z],a,0,4) || isEqua_Array(evaluate[z],b,4,8))//对该空子的上下4个点判断
                score_level2[i][j][z][1] = 100000;
            }
        }
     }
}

void findMaxScore(int level ,int max_score[2],int chess[15][15]){//return Score[0] = x, Score[1] = y
    int i , j ;
    int tmp_x = 0;
    int tmp_y = 0;

    int tmp_max_score = 0;//最高分数
    int score_level1[15][15][4];
    int score_level2[15][15][4][2];
    memset(score_level1,0x0, sizeof(score_level1));
    memset(score_level2,0x0, sizeof(score_level2));
    int tmp_score = 0;
    int score_weight[15][15] = {
        {0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
        {1,2,3,4,5,6,7,8,7,6,5,4,3,2,1},
        {2,3,4,5,6,7,8,9,8,7,6,5,4,3,2},
        {3,4,5,6,7,8,9,10,9,8,7,6,5,4,3},
        {4,5,6,7,8,9 ,10,11,10,9,8,7,6,5,4},
        {5,6,7,8,9,10,11,12,11,10,9,8,7,6,5},
        {6,7,8,9,10,11,12,13,12,11,10,9,8,7,6},
        {7,8,9,10,11,12,13,14,13,12,11,10,9,8,7},
        {6,7,8,9,10,11,12,13,12,11,10,9,8,7,6},
        {5,6,7,8,9,10,11,12,11,10,9,8,7,6,5},
        {4,5,6,7,8,9,10,11,10,9,8,7,6,5,4},
        {3,4,5,6,7,8,9,10,9,8,7,6,5,4,3},
        {2,3,4,5,6,7,8,9,8,7,6,5,4,3,2},
        {1,2,3,4,5,6,7,8,7,6,5,4,3,2,1},
        {0,1,2,3,4,5,6,7,6,5,4,3,2,1,0}
    };
    switch(level){
        case 1:
            evaluation_level1(score_level1,chess);
            for(i = 0;i<15;i++)
                for(j = 0;j<15;j++){
                    tmp_score = score_level1[i][j][3]+
                                score_level1[i][j][2]+
                                score_level1[i][j][1]+
                                score_level1[i][j][0]+
                                score_weight[i][j];
                    if ((tmp_score >= tmp_max_score) &&(chess[i][j] == 0))
                    {
                        tmp_x = i;
                        tmp_y = j;
                        tmp_max_score = tmp_score;
                    }
                }
                max_score[0] = tmp_x;
                max_score[1] = tmp_y;
            break;
        case 2:
            memset(score_level2,0x0, sizeof(score_level2));
            evaluation_level2(score_level2,chess);
            for(i = 0;i<15;i++)
                for(j = 0;j<15;j++){
                    tmp_score = 0;
                    tmp_score = score_level2[i][j][3][0]+
                                score_level2[i][j][2][0]+
                                score_level2[i][j][1][0]+
                                score_level2[i][j][0][0]+
                                score_level2[i][j][3][1]+
                                score_level2[i][j][2][1]+
                                score_level2[i][j][1][1]+
                                score_level2[i][j][0][1]+
                                score_weight[i][j];

                    if ((tmp_score > tmp_max_score) &&(chess[i][j] == 0))
                    {
                        tmp_x = i;
                        tmp_y = j;
                        tmp_max_score = tmp_score;
                    }
                }
                max_score[0] = tmp_x;
                max_score[1] = tmp_y;
                qDebug()<<tmp_max_score;
            break;
    }


}

void robot_level2(int level,int *x,int *y,int chess[15][15]){//会进攻了
    int max_score[2];

    findMaxScore(level,max_score,chess);

    *x = max_score[0];
    *y = max_score[1];
    chess[*x][*y] = 10;
}

void robot_level1(int level,int *x,int *y,int chess[15][15]){//只会防守
    int max_score[2];

    findMaxScore(level,max_score,chess);

    *x = max_score[0];
    *y = max_score[1];
    chess[*x][*y] = 10;

}

//x,y的合法性判断

int Position(int x,int y,int chess[15][15])
{
    if(x>14||x<0||y>14||y<0)
        return 1; //超出范围
    if (chess[x][y] == 9||chess[x][y] == 10)
        return 2;           //存在棋子
    else
        return 0;           //返回 0 表示 坐标正常
}

//采用博弈树来分析
//调用c语言
void AiGame::ComMoveChess()
{
    if(!win){
     QPoint whiteGo;//电脑的颜色

     int x,y;
     int level = 2;
     x = 0;
     y = 0;
     int flag = 1;
     if(clickcount == 1){ //电脑第一次落子
         while(flag){
           int  flag_randomPick = qrand()%7;
            FindFirstChess(&x,&y,chess,flag_randomPick);
        if(Position(x,y,chess) == 0) //直到落子合法才使flag＝0退出循环
            flag = 0;
         }
     }
     else{
         switch(level){ //因为level是采用下拉框，所以不用做异值判断
            case 1:{
                    robot_level1(level,&x,&y,chess);//只会防守
                    break;
                }
            case 2:{
                    robot_level2(level,&x,&y,chess);//会适当进攻
                    break;
                }
            case 3:{
                    //todo
                    //采用棋谱
                    break;
               }
         }
     }
     clickcount++;
    movechess(x,y);
    win = isWin(x,y);
        if(win)
        {
            QMessageBox::information(this, "RobotWin", "RobotWin", QMessageBox::Ok);
            qDebug()<<"win";
        }
    }
    else
    {
        QMessageBox::information(this, "YouWin", "YouWin", QMessageBox::Ok);
        qDebug()<<"win";
    }
 }
void AiGame::mousePressEvent(QMouseEvent *event){
    int x;
    int y;
  if(event->button() == Qt::LeftButton){
    offset = event->pos();//获取鼠标的坐标
            //棋盘区域
            if(!win && offset.rx()>186&&offset.rx()<600&&offset.ry()>39&&offset.ry()<445)
            {
                    if(chess[(offset.rx()-210)/27][(offset.ry()-60)/27])//如果鼠标点击的地方有旗子
                        return;
                    x = (offset.rx()-210)/27;
                    y = (offset.ry()-60)/27;
                    if (offset.ry() > 415 && !chess[x][14])//补偿最后一格的误差
                        y = 14;

                    clickcount++;//记录步数

                    movechess(x,y);
                    win = isWin(x,y);
                    ComMoveChess();
                }
        }

};
