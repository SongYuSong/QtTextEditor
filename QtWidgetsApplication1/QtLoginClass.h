#pragma once

#include <QDialog>
#include "ui_QtLoginClass.h"

class QtLoginClass : public QDialog
{
	Q_OBJECT

public:
	QtLoginClass(QWidget *parent = Q_NULLPTR);
	~QtLoginClass();

private slots:
	void on_pushButton_ok_clicked();

private:
	Ui::QtLoginClass ui;
};
