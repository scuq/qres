#include "windowmover.h"
#include <QDebug>

QRegExp windowMover::rxFindStr;
int windowMover::x = 0;
int windowMover::y = 0;
int windowMover::width = 300;
int windowMover::height = 300;
bool windowMover::repaint = true;
bool windowMover::borderless = false;
bool windowMover::maximize = false;
bool windowMover::blankborders = false;
bool windowMover::gamekeepalive = false;
int windowMover::waitforwindowseconds = 0;
int windowMover::delaywindowseconds = 0;
bool windowMover::moved = false;
QString windowMover::command = "";
QProcess windowMover::process;
QStringList windowMover::args;


bool windowMover::findWindow(QString windowFindRegexp) {



    if (windowMover::waitforwindowseconds > 0) {



        QTime dieTime= QTime::currentTime().addSecs(windowMover::waitforwindowseconds);

        while (QTime::currentTime() < dieTime) {




        if (windowMover::moved == false) {

            EnumWindows(EnumWinHandle, (LPARAM)(LPSTR)(windowFindRegexp.toStdString().c_str()));

        } else {

            break;
        }


        }

    } else {
            EnumWindows(EnumWinHandle, (LPARAM)(LPSTR)(windowFindRegexp.toStdString().c_str()));
    }


    return true;
}

void windowMover::setX(int x) {
    windowMover::x = x;

}

void windowMover::setY(int y) {
    windowMover::y = y;

}

void windowMover::setWidth(int width) {
    windowMover::width = width;

}

void windowMover::setHeight(int height) {
    windowMover::height = height;

}

void windowMover::setBorderless(bool borderless) {
    windowMover::borderless = borderless;

}

void windowMover::setMaximize(bool maximize)
{
    windowMover::maximize = maximize;
}

void windowMover::setBlankBorders(bool blankborders) {
    windowMover::blankborders = blankborders;

}


void windowMover::setGameKeepalive(bool gamekeepalive) {
    windowMover::gamekeepalive = gamekeepalive;

}

void windowMover::setWaitForWindow(int seconds)
{
    windowMover::waitforwindowseconds = seconds;
}

void windowMover::setDelayMoveWindow(int seconds)
{
    windowMover::delaywindowseconds = seconds;
}

void windowMover::executeCommand(QString command, QString cargs, QString windowFindRegexp)
{
    windowMover::command = command;

    args << cargs.split(" ");

    qDebug() << "Executing command:" << command << " with args: " << cargs;

    process.startDetached(command, args);



    Sleep(uint(250));

    qDebug() << "Sleeping 250ms";

    windowMover::findWindow(windowFindRegexp);

    return;

}

QString windowMover::getLastErrorMsg()
{

        LPWSTR bufPtr = NULL;
        DWORD err = GetLastError();
        FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                       FORMAT_MESSAGE_FROM_SYSTEM |
                       FORMAT_MESSAGE_IGNORE_INSERTS,
                       NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
        const QString result =
            (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                       QString("Unknown Error %1").arg(err);
        LocalFree(bufPtr);
        return result;

}




BOOL CALLBACK windowMover::EnumWinHandle(HWND hWnd, LPARAM lparam)
{
    TCHAR buff[1000];
    int buffsize=100;



    windowMover::rxFindStr.setCaseSensitivity(Qt::CaseInsensitive);
    windowMover::rxFindStr.setPattern(QString::fromUtf8((char*)lparam));




    if (!hWnd)
    {
        return TRUE;        // Not a window
    }
    if (!::IsWindowVisible(hWnd))
    {
        return TRUE;
    }



    GetWindowText(hWnd,buff,buffsize);

    if (QString::fromWCharArray(buff).count("qres") <= 0) {

        windowMover::rxFindStr.indexIn(QString::fromWCharArray(buff));


        if (windowMover::rxFindStr.cap(0).count() > 0) {

            if (windowMover::gamekeepalive == true)
            {
                 qDebug() << "gamekeepalive";
                //SendMessage(hWnd,0x000C,0,(LPARAM)"a");
               // SendMessage(hWnd,WM_KEYDOWN,(int)0x20,0x220001);
               // SendMessage(hWnd,WM_KEYUP,(int)0x20,0xC0220001);
                 BringWindowToTop(hWnd);
                 SetForegroundWindow(hWnd);

                //SendMessage(hWnd,WM_CHAR,'a', 0);
                 SendMessage(hWnd,WM_KEYDOWN,(int)0x20,0);
                 SendMessage(hWnd,WM_KEYUP,(int)0x20,0);

            } else {


            if (windowMover::blankborders == true)
            {
                 qDebug() << "blankborders";
                 LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
                 lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_EX_TOPMOST);
                 SetWindowLong(hWnd, GWL_STYLE, lStyle);

                 BringWindowToTop(hWnd);    //This is the function brings hwnd2 to top

                 SetForegroundWindow(hWnd); //doesn't work


            } else {


                if (windowMover::borderless == true)
                {
                    qDebug() << "borderless";
                    //SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
                     LONG lStyle = GetWindowLong(hWnd, GWL_STYLE);
                     lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_BORDER | WS_EX_COMPOSITED);
                     LONG lExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
                     lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);

                    SetWindowLong(hWnd, GWL_STYLE, lStyle);


                    SetWindowLong(hWnd, GWL_EXSTYLE, lExStyle);




                }



                qDebug() << "delaying move for " << QString::number(delaywindowseconds) << " seconds.";
                Sleep(uint(delaywindowseconds*1000));

                qDebug() << "Moved Window with Title: " << QString::fromWCharArray(buff) << " found: " << rxFindStr.cap(0) << " regex: " << windowMover::rxFindStr.pattern();



                MoveWindow(hWnd,windowMover::x,windowMover::y,windowMover::width,windowMover::height,windowMover::repaint);

                if (windowMover::maximize == true)
                {


                   ShowWindow(hWnd, SW_SHOWMAXIMIZED);



                }

                windowMover::moved = true;
            }
            }

        }



    }
    return TRUE;

}
