#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QLineEdit>
#include <QDialog>
#include <QLabel>

#include "ui_QtWidgetsApplication1.h"

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget* parent = Q_NULLPTR);
    ~QtWidgetsApplication1();

    void newfile();
    bool is_save();
    bool save();
    bool save_as();
    bool savefile(const QString& filename);
    bool loadfile(const QString& filename);

private:
    Ui::QtWidgetsApplication1Class ui;
    
    QLineEdit* findLineEdit;
    QDialog* findDlg;
    QPushButton* btn;
    QVBoxLayout* layout;

    QLabel* statusLable;
    
    bool is_unsasved;
    QString file_path;

private slots:
    void on_action_New_triggered();
    void on_action_Save_triggered();
    void on_action_SaveAs_triggered();

    void on_action_Open_triggered();
    void on_action_Close_triggered();
    void on_action_Exit_triggered();

    void on_action_Undo_triggered();
    void on_action_Cut_triggered();
    void on_action_Copy_triggered();
    void on_action_Paste_triggered();

    void on_action_Search_triggered();

    void showFindText();

protected:
    void closeevent(QCloseEvent* event);

};
