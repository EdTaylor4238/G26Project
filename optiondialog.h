#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>

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

    // Declaration for the accept function
    virtual void accept() override;

public slots:
    void onCheckBoxToggled();
    void onRedSpinBoxValueChanged(int value);
    void onGreenSpinBoxValueChanged(int value);
    void onBlueSpinBoxValueChanged(int value);
    //void onLineEditTextChanged(const QString& text);
    void on_lineEdit_textChanged(const QString& arg1);

signals:

private slots:

private:
    Ui::OptionDialog* ui;
};

#endif // OPTIONDIALOG_H
