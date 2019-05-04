#include <QApplication>
#include "PanharmoniconWindow.h"

#include <QDateTime>
#include <QTextStream>

namespace {

QDateTime startTime;

qint64 timeSinceStart()
{
    return startTime.msecsTo(QDateTime::currentDateTime());
}

void appDebugOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    const char *levels = "DWCFIS";
    const QString format("%1 %2 %3\n");

    qint64 msecstotal = timeSinceStart();
    qint64 seconds = msecstotal / 1000;
    qint64 msecs = msecstotal % 1000;
    QString foo;
    char buf[1025] = {0};
    ::snprintf(buf, 1024, "%5lld.%03lld", seconds, msecs);

    QString out = format.arg(buf).arg(levels[type]).arg(msg);

    QTextStream(stderr) << out.toLocal8Bit();
    fflush(stderr);
}

}

int main(int argc, char *argv[])
{
    startTime = QDateTime::currentDateTime();
    qInstallMessageHandler(appDebugOutput);

    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);
    PanharmoniconWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
