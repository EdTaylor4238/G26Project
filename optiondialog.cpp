#include "optiondialog.h"
#include "ui_optiondialog.h"
#include <qcheckbox.h>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QColorDialog>
#include "mainwindow.h"
#include <qcolor.h>

OptionDialog::OptionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OptionDialog)
{
    ui->setupUi(this);
    // Initialize isVisible to the initial state of the checkbox 
 
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &OptionDialog::onCheckBoxToggled);
    /*connect(ui->RedSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &OptionDialog::onRedSpinBoxValueChanged);
    connect(ui->GreenSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &OptionDialog::onGreenSpinBoxValueChanged);
    connect(ui->BlueSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &OptionDialog::onBlueSpinBoxValueChanged);*/
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

 //void OptionDialog::onRedSpinBoxValueChanged(int value)
 //{
 //    red = value;
 //}

 //void OptionDialog::onGreenSpinBoxValueChanged(int value)
 //{
 //    // Implement the green spin box slot
 //    // You can use 'value' to get the new value of the green spin box
 //    // Update your logic accordingly
 //    green = value;
 //}

 //void OptionDialog::onBlueSpinBoxValueChanged(int value)
 //{
 //    // Implement the blue spin box slot
 //    // You can use 'value' to get the new value of the blue spin box
 //    // Update your logic accordingly
 //    blue = value;
 //}

 void OptionDialog::on_lineEdit_textChanged(const QString& text)
 {
     // Implement the line edit slot
     // You can use 'text' to get the new text value
     // Update your logic accordingly
     // Example: update a variable with the text value
     lineEditText = text;
 }

 void OptionDialog::setProperties(bool isVisible, int red, int green, int blue, const QString& lineEditText)
 {
     // Set the values to the UI widgets
     ui->checkBox->setChecked(isVisible);
     /*ui->RedSpinBox->setValue(red);
     ui->GreenSpinBox->setValue(green);
     ui->BlueSpinBox->setValue(blue);*/
     ui->lineEdit->setText(lineEditText);
 }

 //void OptionDialog::accept()
 //{
 //    // Save the values before accepting the dialog
 //    isVisible = ui->checkBox->isChecked();
 //     = ptr->setColor(color);
 //    lineEditText = ui->lineEdit->text();
 //    // Call the base class implementation to close the dialog
 //    QDialog::accept();
 //}

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

 void OptionDialog::set_ptr(ModelPart* Pointer) {
     ptr = Pointer;
 }