#include "mainwindow.h"
#include "VRRenderThread.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include "optiondialog.h"
#include<qcheckbox.h>
#include <QAbstractItemModel>
#include "vtkCylinderSource.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkPolyDataMapper.h"
#include "vtkCamera.h"
#include <vtkRenderer.h>
#include <vtkLight.h>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->addAction(ui->actionItem_Options);
    /* Create/allocate the ModelList */
    this->partList = new ModelPartList("Parts List");

    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);

    // Create and configure a scene light
// ... Add actors here (not shown)

// Render the scene
 /* This needs adding to MainWindow constructor */
    /* Link a render window with the Qt widget */
renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
ui->VTKwidget->setRenderWindow(renderWindow);

// Add light to renderer after rendering (important for VTK)

    /* Add a renderer */
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();


    // **Create temporary cylinder geometry (replace with CAD model loading later)**
    vtkNew<vtkCylinderSource> cylinder; // Create a cylinder source object
    cylinder->SetResolution(8);         // Set the number of facets (sides)

    // Create mapper for cylinder
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());  // Connect the cylinder source to the mapper

    // Create actor for cylinder with color and rotation
    vtkNew<vtkActor> cylinderActor;
    cylinderActor->SetMapper(cylinderMapper);                        // Set the mapper for the actor
    cylinderActor->GetProperty()->SetColor(1.0, 0.0, 0.35);            // Set the color to red
    cylinderActor->RotateX(30.0);                                      // Rotate around X-axis
    cylinderActor->RotateY(-45.0);                                     // Rotate around Y-axis

    // Add actor to renderer
    renderer->AddActor(cylinderActor);

    /* Reset Camera (probably needs to go in its own function that is called whenever
    model is changed) */
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    // Connect the statusUpdateMessage signal to the showMessage slot of the status bar
    connect(this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage);
    // Connect the first button to handleButton
    connect(ui->pushButton, &QPushButton::released, this, &MainWindow::handleButton);
    // Connect the second button to handleButton2
    connect(ui->pushButton2, &QPushButton::released, this, &MainWindow::handleButton2);
    // Connect the tree view click event to handleTreeClicked
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleTreeClicked);
    // Assuming you have a tree view named ui->treeView
    connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::handleOptionDialog);
    connect(ui->lightingSlider, &QAbstractSlider::sliderMoved, this, &MainWindow::on_lightingSlider_sliderMoved);

    //connect(ui->treeView, &QTreeView::clicked, this, &MainWindow::on_actionItem_Options_triggered);

    /* Create / allocate the ModelList */
    this->partList = new ModelPartList("Parts List");

    /* Link it to the tree view in the GUI */
    ui->treeView->setModel(this->partList);

    /* Manually create a model tree - there are much better and more flexible ways of doing this,
     * e.g. with nested functions. This is just a quick example as a starting point. */
    ModelPart* rootItem = this->partList->getRootItem();

    /* Add 3 top level items */
    for (int i = 0; i < 3; i++) {
        /* Creates strings for both data columns */
        QString name = QString("TopLevel %1").arg(i);
        QString visible("true");

        /* Create child item */
        ModelPart* childItem = new ModelPart({ name, visible });

        /* Append to tree top-level */
        rootItem->appendChild(childItem);

        /* Add 5 sub-items */
        for (int j = 0; j < 5; j++) {
            QString name = QString("Item %1,%2").arg(i).arg(j);
            QString visible("true");

            ModelPart* childChildItem = new ModelPart({ name, visible });

            /* Append to parent */
            childItem->appendChild(childChildItem);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleButton()
{
    // Emit the statusUpdateMessage signal to update the status bar
    emit statusUpdateMessage("View is reset", 100); // 100 milliseconds timeout
    renderer->ResetCamera();
}

void MainWindow::handleButton2()
{
    // Emit the statusUpdateMessage signal to update the status bar
    ui->treeView->clearSelection();
    emit statusUpdateMessage("VR", 300); // 3000 milliseconds timeout
    VRRenderer = new VRRenderThread();
    VRRenderer->start();
}

void MainWindow::handleTreeClicked(const QModelIndex& index) {

    /* Get a pointer to the item from the index */
    ModelPart* selectedItem = static_cast<ModelPart*>(index.internalPointer());

    /* In this case, we will retrieve the name string from the internal QVariant data array */
    QString itemName = selectedItem->data(0).toString();

    emit statusUpdateMessage("Selected item: " + itemName, 3000);
}

// Slot function added to MainWindow.cpp
void MainWindow::on_actionOpen_File_triggered() {
    QStringList fileList = QFileDialog::getOpenFileNames(
        this,
        tr("Open File"),
        "C:\\",
        tr("STL Files (*.stl);;Text Files (*.txt)"));

    //emit statusUpdateMessage("Selected file: " + fileName, 3000);

    // Check if a file was selected
    if (fileList.isEmpty()) {
        // Do something when no file is selected, e.g., show a message
        statusBar()->showMessage(tr("No file selected."));
        return;
    }

    /* Create strings for both data columns */
       /* Manually create a model tree - there are much better and more flexible ways of doing this,
       e.g., with nested functions. This is just a quick example as a starting point. */
       //ModelPart* rootItem = this->partList->getRootItem();


    QString visible("true");

    /* Create child item when havent selected an item adds to root*/
    ModelPart* childItem = {};//new ModelPart({ fileName, visible });

    /* Append to tree top-level adds neew itemw hen there is already  */
    //rootItem->appendChild(childItem);
    // Get the index of the selected item in the tree view
    //QModelIndex index = ui->treeView->currentIndex();

    for (int n = 0; n < fileList.length(); n++)
    {
        QList<QVariant> data{ fileList[n], visible };
        QModelIndex parent;
        QModelIndex newIndex = partList->appendChild(parent, data);

        childItem = static_cast<ModelPart*>(newIndex.internalPointer());

        // Update the tree view to reflect the changes
        ui->treeView->update();

        childItem->loadSTL(fileList[n]);
        updateRender();
        emit statusUpdateMessage((n + 1) + "/" + (int)fileList.length(), 10);
    }
    emit statusUpdateMessage("Done :)", 10);
}

void MainWindow::updateRender() {
    renderer->RemoveAllViewProps();
    for (int i = 0; i < partList->rowCount(QModelIndex()); i++) {

        updateRenderFromTree(partList->index(i, 0, QModelIndex()));
    }
    updateRenderFromTree(partList->index(0, 0, QModelIndex()));
    renderer->ResetCamera();
    renderer->Render();
}
void MainWindow::updateRenderFromTree(const QModelIndex& index) {
    if (index.isValid()) {
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        /* Retrieve actor from selected part and add to renderer */
        vtkSmartPointer<vtkActor> actor = selectedPart->getActor();
        if (actor) {
            renderer->AddActor(actor);
            emit statusUpdateMessage("Added actor to renderer", 3000);
        }
    }
    /* Check to see if this part has any children */
    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) {
        return;
    }

    /* Loop through children and add their actors */
    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
}

void MainWindow::handleOptionDialog()
{
    OptionDialog dialog(this);
    QModelIndex selectedIndex = ui->treeView->currentIndex();
    // Ensure the index is valid before proceeding
    if (selectedIndex.isValid()) {
        // Get the corresponding ModelPart
        ModelPart* selectedItem = static_cast<ModelPart*>(selectedIndex.internalPointer());

        // Pass the current values to the OptionDialog constructor
        dialog.setProperties(selectedItem, selectedItem->getVisibility(), selectedItem->data(0).toString(), selectedItem->getColor());
        dialog.saveSettings();
        if (dialog.exec() == QDialog::Accepted) {
            // Set the visibility of the item based on dialog.isVisible (true for visible, false for invisible)
            selectedItem->setVisible(dialog.isVisible);
            selectedItem->setColor(dialog.color);
            selectedItem->setName(dialog.lineEditText);

            QString boolString = selectedItem->getVisibility() ? "true" : "false";
            QString statusMessage = QString("Visibility: %1")
                .arg(boolString);

            // You may need to update the view after changing the data
            ui->treeView->update();

            emit statusUpdateMessage(statusMessage, 3000);
        }
        else {
            // Handle the case where the selected index is not valid
            emit statusUpdateMessage("No item selected in the tree view", 3000);
        }
    }
    else {
        emit statusUpdateMessage("OptionDialog rejected", 3000);
    }
    updateRender();
}

void MainWindow::on_lightingSlider_sliderMoved(float position)
{
    renderer->GetLights()->InitTraversal();
    vtkLight* light = renderer->GetLights()->GetNextItem();
    light->SetIntensity(position / 100);
}

