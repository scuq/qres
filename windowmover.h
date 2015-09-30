#ifndef WINDOWMOVER_H
#define WINDOWMOVER_H

#include <QObject>

#include <QtCore/QRegExp>
#include <windows.h>
#include <winuser.h>







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
    static void setBlankBorders(bool blankborders);
    static void setGameKeepalive(bool gamekeepalive);

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
    static bool blankborders;
    static bool gamekeepalive;


};

#endif // WINDOWMOVER_H