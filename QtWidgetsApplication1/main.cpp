#include "QtWidgetsApplication1.h"
#include "QtLoginClass.h"

#include <QtWidgets/QApplication>
//#include <QtCore/QTextCodec>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtLoginClass qlc;
    if (qlc.exec() == QDialog::Accepted)
    {
        QtWidgetsApplication1 w;
        w.show();
        return a.exec();
    }
    else
        return 0;
}
