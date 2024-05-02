#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ModelPart.h"
#include "ModelPartList.h"
#include <QFileDialog.h>
#include"optiondialog.h"
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
        
 public slots :
     void handleButton(); 
     void handleButton2();
     void handleTreeClicked(const QModelIndex& index);
     void startStopVRButton();
     void on_actionOpen_File_triggered();
     void handleOptionDialog();  // Add this slot
     void on_actionItem_Options_triggered();
     void updateRender();
     void updateRenderFromTree(const QModelIndex& index); 
     
signals:
    void statusUpdateMessage(const QString& message, int timeout);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startStopVRButton_toggled(bool checked);

private:
    ModelPartList* partList;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
