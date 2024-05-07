#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <qcheckbox.h>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QColorDialog>
#include <qcolor.h>

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
 
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &OptionDialog::onCheckBoxToggled);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &OptionDialog::on_lineEdit_textChanged);
    connect(ui->updateModelPartColor, &QPushButton::clicked, this, &OptionDialog::updateModelPartColor);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &OptionDialog::saveSettings);
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &OptionDialog::updateModelPartVisibility);
}

OptionDialog::~OptionDialog()
{
    delete ui;
}
void OptionDialog::onCheckBoxToggled()
{
     isVisible = ui->checkBox->isChecked();

     if (isVisible) {
         // Checkbox is checked
         qDebug() << "Checkbox is checked. isVisible is now true.";
     }
     else {
         // Checkbox is unchecked
         qDebug() << "Checkbox is unchecked. isVisible is now false.";
     }
}

 void OptionDialog::on_lineEdit_textChanged(const QString& text)
 {
     lineEditText = text;
 }

 void OptionDialog::setProperties(ModelPart* Pointer, bool isVisible, const QString& lineEditText, const QColor& modelColor)
 {
     ptr = Pointer;
     color = modelColor;
     ui->checkBox->setChecked(isVisible);
     ui->lineEdit->setText(lineEditText);
 }

 void OptionDialog::updateModelPartName(const QString& name) {
     Name = ui->lineEdit->text();
 }
 void OptionDialog::updateModelPartColor() {
     QColor newColor = QColorDialog::getColor(color, this, "Select color", QColorDialog::DontUseNativeDialog);
     if (newColor != color) color = newColor;
 }
 void OptionDialog::updateModelPartVisibility(int state) {
     if (state == Qt::Checked) isVisible = true;
     else isVisible = false;
 }

 void OptionDialog::saveSettings() {
     ptr->setColor(color);
     ptr->setVisible(ui->checkBox->isChecked());
     ptr->setName(ui->lineEdit->text());
     emit settingsSaved();
 }


 void OptionDialog::loadSettings() {
     color = ptr->getColor();
     Name = ptr->getName();
     ui->lineEdit->setText(Name);
     isVisible = ptr->getVisibility();
     ui->checkBox->setChecked(isVisible);
 }