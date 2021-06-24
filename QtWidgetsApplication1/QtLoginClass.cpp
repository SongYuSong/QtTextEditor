#include "QtLoginClass.h"

#include <qmessagebox.h>

QtLoginClass::QtLoginClass(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.lineEdit_usr->setFocus();
}

QtLoginClass::~QtLoginClass()
{
}

void QtLoginClass::on_pushButton_ok_clicked() {
	if (ui.lineEdit_usr->text() == ("abc") && ui.lineEdit_pwd->text() == ("123")) 
	{
		accept();
	}
	else
	{
		QMessageBox::warning(this, ("warning"), ("user name or password error!"), QMessageBox::Yes);
		ui.lineEdit_usr->clear();
		ui.lineEdit_pwd->clear();
		ui.lineEdit_usr->setFocus();
	}
}