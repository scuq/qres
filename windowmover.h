#ifndef WINDOWMOVER_H
#define WINDOWMOVER_H

#include <QObject>

#include <QtCore/QRegExp>
#include <windows.h>
#include <winuser.h>
#include <QTime>
#include <QProcess>
#include <QStringList>




class windowMover : public QObject
{
    Q_OBJECT
public:
    static windowMover &GetInstance(){
        static windowMover instance;
        return instance;
    }




    static bool findWindow(QString windowFindRegexp);
    static void setX(int x);
    static void setY(int y);
    static void setWidth(int width);
    static void setHeight(int height);
    static void setBorderless(bool borderless);
    static void setMaximize(bool maximize);
    static void setBlankBorders(bool blankborders);
    static void setGameKeepalive(bool gamekeepalive);
    static void setWaitForWindow(int seconds);
    static void setDelayMoveWindow(int seconds);
    static void executeCommand(QString command, QString cargs);

    static QString getLastErrorMsg();

signals:
    void finished();

public slots:

private:
    static BOOL CALLBACK EnumWinHandle(HWND hWnd, LPARAM lparam);
    static QRegExp rxFindStr;
    static int x;
    static int y;
    static int width;
    static int height;
    static bool repaint;
    static bool borderless;
    static bool maximize;
    static bool blankborders;
    static bool gamekeepalive;
    static int waitforwindowseconds;
    static int delaywindowseconds;
    static bool moved;
    static QString command;
    static QProcess process;
    static QStringList args;


};

#endif // WINDOWMOVER_H
