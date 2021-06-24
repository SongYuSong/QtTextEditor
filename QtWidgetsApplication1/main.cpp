#include "QtWidgetsApplication1.h"
#include "QtLoginClass.h"

#include <QtWidgets/QApplication>
//#include <QtCore/QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    QtLoginClass qlc;
    if (qlc.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
}
