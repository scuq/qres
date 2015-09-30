#include <QCoreApplication>
#include <QCommandLineParser>
#include <QTimer>
#include "windowmover.h"

#include <QDebug>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("qres");
    QCoreApplication::setApplicationVersion("1.0");



    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption WindowRegexpOption(QStringList() << "f" << "window-title",
            QCoreApplication::translate("main", "regexp to find window-title(s)"),
            QCoreApplication::translate("main", "regexp"));

    QCommandLineOption xPositionOption(QStringList() << "x" << "x-position",
            QCoreApplication::translate("main", "x position of window"),
            QCoreApplication::translate("main", "pos"));

    QCommandLineOption yPositionOption(QStringList() << "y" << "y-position",
            QCoreApplication::translate("main", "y position of window"),
            QCoreApplication::translate("main", "pos"));

    QCommandLineOption widthOption(QStringList() << "w" << "width",
            QCoreApplication::translate("main", "width of window"),
            QCoreApplication::translate("main", "width"));

    QCommandLineOption heightOption(QStringList() << "t" << "height",
            QCoreApplication::translate("main", "height of window"),
            QCoreApplication::translate("main", "height"));

    QCommandLineOption borderlessOption(QStringList() << "b" << "borderless",
            QCoreApplication::translate("main", "borderless"),
            QCoreApplication::translate("main", "borderless"));

    QCommandLineOption blankbordersOption(QStringList() << "a" << "blankborders",
            QCoreApplication::translate("main", "blankborders"),
            QCoreApplication::translate("main", "blankborders"));

    QCommandLineOption gameKeepaliveOption(QStringList() << "g" << "gamekeepalive",
            QCoreApplication::translate("main", "gamekeepalive"),
            QCoreApplication::translate("main", "gamekeepalive"));

    parser.addOption(xPositionOption);
    parser.addOption(yPositionOption);
    parser.addOption(widthOption);
    parser.addOption(heightOption);
    parser.addOption(WindowRegexpOption);
    parser.addOption(borderlessOption);
    parser.addOption(blankbordersOption);
    parser.addOption(gameKeepaliveOption);


    parser.process(a);

     QString windowRegexp = parser.value(WindowRegexpOption);
     QString xPosition = parser.value(xPositionOption);
     QString yPosition = parser.value(yPositionOption);
     QString width = parser.value(widthOption);
     QString height = parser.value(heightOption);
     QString borderless = parser.value(borderlessOption);
     QString blankborders = parser.value(blankbordersOption);
     QString gamekeepalive = parser.value(gameKeepaliveOption);

    // qDebug() << windowRegexp;
    // qDebug() << xPosition;
    // qDebug() << yPosition;
    // qDebug() << width;
    // qDebug() << height;





    windowMover::setX(xPosition.toInt());
    windowMover::setY(yPosition.toInt());
    windowMover::setWidth(width.toInt());
    windowMover::setHeight(height.toInt());

    if (borderless == "true") {
         windowMover::setBorderless(true);
    } else {
        windowMover::setBorderless(false);
    }

    if (blankborders == "true") {
         windowMover::setBlankBorders(true);
    } else {
        windowMover::setBlankBorders(false);
    }


    if (gamekeepalive == "true") {
         windowMover::setGameKeepalive(true);
    } else {
        windowMover::setGameKeepalive(false);
    }

     windowMover::findWindow(windowRegexp);




    QTimer::singleShot(800, &a, SLOT(quit()));
    return a.exec();
}
