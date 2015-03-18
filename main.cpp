#include "countermainwindow.h"
#include <QApplication>
#include <QException>
#include <QDebug>

int main(int argc, char *argv[])
{
    int res=-1;

    try
    {
        QApplication a(argc, argv);
        CounterMainWindow window;
        window.show();

        res = a.exec();
    }
    catch(QException &e)
    {
        qCritical() << QString("Exception: %1").arg( e.what() );
    }
    catch(...)
    {
        qCritical() << QString("Unhandled Exception");
    }

    return res;
}
