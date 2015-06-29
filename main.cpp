#include <QApplication>
#include <startwidget.h>
#include <QTextCodec>
int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    StartWidget w;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    w.show();
    return app.exec();
}
