#include "QtWidgetsApplication1.h"

#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    is_unsasved = true;
    file_path = tr("δ����.txt");
    ui.setupUi(this);
    setWindowTitle(file_path);

    findDlg = new QDialog(this);
    findDlg->setWindowTitle(tr("����"));
    findLineEdit = new QLineEdit(findDlg);
    btn = new QPushButton(tr("������һ��"), findDlg);
    layout = new QVBoxLayout(findDlg);
    layout->addWidget(findLineEdit);
    layout->addWidget(btn);
    connect(btn, SIGNAL(clicked()), this, SLOT(showFindText()));

    statusLable = new QLabel;
    //statusLable->setFrameShape(QFrame::NoFrame);
    statusLable->setText(tr("<a href=\"https://www.baidu.com\">baidu.com</a>"));
    //statusLable->setTextFormat(Qt::AutoText);
    statusLable->setOpenExternalLinks(true);
    ui.statusBar->addPermanentWidget(statusLable);
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{
    delete layout;
    delete btn;
    delete findLineEdit;
    delete findDlg;
    delete statusLable;
}

void QtWidgetsApplication1::newfile()
{
    if (is_save())
    {
        is_unsasved = true;
        file_path = tr("δ����.txt");
        setWindowTitle(file_path);
        ui.textEdit->clear();
        ui.textEdit->setVisible(true);
    }
}

bool QtWidgetsApplication1::is_save()
{
    if (ui.textEdit->document()->isModified()) {
        QMessageBox box;
        box.setWindowTitle("����");
        box.setIcon(QMessageBox::Warning);
        box.setText(file_path + tr("��δ���棬�Ƿ񱣴棿"));
        QPushButton* yesbtn = box.addButton(tr("��(&Y)"), QMessageBox::YesRole);
        box.addButton(tr("��(&N)"), QMessageBox::NoRole);
        QPushButton* cancelbtn = box.addButton(tr("ȡ��"), QMessageBox::RejectRole);
        box.exec();

        if (box.clickedButton() == yesbtn)
            return save();
        else if (box.clickedButton() == cancelbtn)
            return false;
    }
    return true;
}

bool QtWidgetsApplication1::save()
{
    if (is_unsasved)
    {
        return save_as();
    }
    else
    {
        return savefile(file_path);
    }
}

bool QtWidgetsApplication1::save_as()
{
    QString new_name = QFileDialog::getSaveFileName(this, tr("���Ϊ"), file_path);
    if (new_name.isEmpty())
    {
        return false;
    }
    return savefile(new_name);
}

bool QtWidgetsApplication1::savefile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly|QFile::Text))
    {
        QMessageBox::warning(this, tr("���ĵ��༭��"), tr("�޷�д���ļ� %1��/n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << ui.textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    is_unsasved = false;
    ui.textEdit->document()->setModified(false);
    file_path = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(file_path);
    return true;
}

bool QtWidgetsApplication1::loadfile(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("���ĵ��༭��"), tr("�޷�д���ļ� %1��/n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui.textEdit->setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    file_path = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(file_path);
    is_unsasved = false;
    return true;
}

void QtWidgetsApplication1::on_action_New_triggered()
{
    newfile();
}

void QtWidgetsApplication1::on_action_Open_triggered()
{
    if (is_save())
    {
        QString filename = QFileDialog::getOpenFileName(this);
        if (!filename.isEmpty())
        {
            loadfile(filename);
            ui.textEdit->setVisible(true);
        }
    }
}

void QtWidgetsApplication1::on_action_Save_triggered()
{
    save();
}

void QtWidgetsApplication1::on_action_SaveAs_triggered()
{
    save_as();
}

void QtWidgetsApplication1::on_action_Close_triggered()
{
    if (is_save())
    {
        ui.textEdit->setVisible(false);
    }
}

void QtWidgetsApplication1::on_action_Exit_triggered()
{
    on_action_Close_triggered();
    qApp->quit();
}

void QtWidgetsApplication1::on_action_Undo_triggered()
{
    ui.textEdit->undo();
}

void QtWidgetsApplication1::on_action_Cut_triggered()
{
    ui.textEdit->cut();
}

void QtWidgetsApplication1::on_action_Copy_triggered()
{
    ui.textEdit->copy();
}

void QtWidgetsApplication1::on_action_Paste_triggered()
{
    ui.textEdit->paste();
}

void QtWidgetsApplication1::on_action_Search_triggered()
{
    findDlg->show();
}

void QtWidgetsApplication1::showFindText()
{
    QString str = findLineEdit->text();
    if (!ui.textEdit->find(str, QTextDocument::FindBackward))
    {
        QMessageBox::warning(this, tr("����"),
            tr("�Ҳ���%1").arg(str));
    }
}

void QtWidgetsApplication1::closeevent(QCloseEvent* event)
{
    if (is_save())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
