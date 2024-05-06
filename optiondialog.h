#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "ModelPart.h"
#include "ui_optiondialog.h"

namespace Ui {
class OptionDialog;
}

class OptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionDialog(QWidget *parent = nullptr);
    ~OptionDialog();
    bool isVisible;
    int red, green, blue;
    QString lineEditText;
    void setProperties(bool isVisible, int red, int green, int blue, const QString& lineEditText);
    void set_ptr(ModelPart* Pointer);

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
    ModelPart *ptr = nullptr;
    QString Name = "Enter:";
    QColor color;
};

#endif // OPTIONDIALOG_H
