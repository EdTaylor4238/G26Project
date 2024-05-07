#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "ModelPart.h"
#include "ui_optiondialog.h"
#include <QColorDialog> 
#include "mainwindow.h"


namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();
    QString lineEditText;
    ModelPart* ptr;
    QString Name = "Enter:";
    QColor color;
    bool isVisible = true;
    void setProperties(ModelPart* Pointer, bool isVisible, const QString& lineEditText, const QColor& color);

    // Declaration for the accept function
    //virtual void accept() override;

public slots:
    void onCheckBoxToggled();
    void on_lineEdit_textChanged(const QString& arg1);
    void updateModelPartName(const QString& name);
    void updateModelPartColor();
    void updateModelPartVisibility(int state);
    void saveSettings();
    void loadSettings();



signals:
    void settingsSaved();
private slots:

private:
    Ui::OptionDialog *ui;
};

#endif // OPTIONDIALOG_H
