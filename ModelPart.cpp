/**     @file ModelPart.cpp
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Template for model parts that will be added as treeview items
  *
  *     P Evans 2022
  */

#include "ModelPart.h"
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkSTLReader.h>
#include <vtkPolyDataMapper.h>
#include <vtkColor.h>

  /* Commented out for now, will be uncommented later when you have
   * installed the VTK library
   */
   //#include <vtkSmartPointer.h>
   //#include <vtkDataSetMapper.h>



ModelPart::ModelPart(const QList<QVariant>& data, ModelPart* parent)
    : m_itemData(data), m_parentItem(parent) {

    /* You probably want to give the item a default colour */
    stlReader = nullptr;
}


ModelPart::~ModelPart() {
    qDeleteAll(m_childItems);
}


void ModelPart::appendChild(ModelPart* item) {
    /* Add another model part as a child of this part
     * (it will appear as a sub-branch in the treeview)
     */
    item->m_parentItem = this;
    m_childItems.append(item);
}


ModelPart* ModelPart::child(int row) {
    /* Return pointer to child item in row below this item.
     */
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int ModelPart::childCount() const {
    /* Count number of child items
     */
    return m_childItems.count();
}


int ModelPart::columnCount() const {
    /* Count number of columns (properties) that this item has.
     */
    return m_itemData.count();
}

QVariant ModelPart::data(int column) const {
    /* Return the data associated with a column of this item
     *  Note on the QVariant type - it is a generic placeholder type
     *  that can take on the type of most Qt classes. It allows each
     *  column or property to store data of an arbitrary type.
     */
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}


void ModelPart::set(int column, const QVariant& value) {
    /* Set the data associated with a column of this item
     */
    if (column < 0 || column >= m_itemData.size())
        return;

    m_itemData.replace(column, value);
}


ModelPart* ModelPart::parentItem() {
    return m_parentItem;
}


int ModelPart::row() const {
    /* Return the row index of this item, relative to it's parent.
     */
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ModelPart*>(this));
    return 0;
}

//void ModelPart::setColour(const unsigned char R, const unsigned char G, const unsigned char B) {
//    m_colorR = R;
//    m_colorG = G;
//    m_colorB = B;
//
//    // You may want to update the color in your rendering system (e.g., VTK) here
//    // Example: set the color of the VTK actor
//   
//    this->GetProperty()->SetColor(getColourR, getColourG, getColourB);actor->GetProperty()->SetColor(0, 0, 1);
//}

void ModelPart::setColor(QColor clr) {
    color = clr;
}

bool ModelPart::getVisibility(void)
{
    return isVisible;
}

QColor ModelPart::getColor(void)
{
    return color;
}
const QString ModelPart::getName(void) {
    return Name;
}


unsigned char ModelPart::getColourR() {
    /* This is a placeholder function that will be used in the next worksheet */

    /* As the name suggests ... */
    return m_colorR;   // needs updating
}

unsigned char ModelPart::getColourG() {
    /* This is a placeholder function that will be used in the next worksheet */

    /* As the name suggests ... */
    return m_colorG;   // needs updating
}


unsigned char ModelPart::getColourB() {
    /* This is a placeholder function that will be used in the next worksheet */

    /* As the name suggests ... */
    return m_colorB;   // needs updating
}


void ModelPart::setVisible(bool isVisible)
{
    /* Set the visibility based on the input value */
    this->isVisible = isVisible;

    if (isVisible) {
        set(1, "true");
    }
    else {
        set(0, "false");
    }
}


void ModelPart::setName(QString name)
{
    set(0, name);
}

void ModelPart::loadSTL(QString fileName) {
    /* This is a placeholder function that will be used in the next worksheet */

    /* 1. Use the vtkSTLReader class to load the STL file
     *     https://vtk.org/doc/nightly/html/classvtkSTLReader.html
     */
     // The mapper is responsible for pushing the geometry into the graphics
   // library. It may also do color mapping, if scalars or other attributes are
   // defined.
     stlReader = vtkSmartPointer<vtkSTLReader>::New();
     stlReader->SetFileName(fileName.toStdString().c_str());
     stlReader->Update();
     /* 2. Initialise the part's vtkMapper */
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(stlReader->GetOutputPort());
     /* 3. Initialise the part's vtkActor and link to the mapper */
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
}

vtkSmartPointer<vtkActor> ModelPart::getActor() {
    /* This is a placeholder function that will be used in the next worksheet */
    
    /* Needs to return a smart pointer to the vtkActor to allow
     * part to be rendered.
     */
    return actor;
    }

     vtkActor* ModelPart::getNewActor() {
         /* This is a placeholder function that will be used in the next worksheet.
          * The default mapper/actor combination can only be used to render the part in
          * the GUI, it CANNOT also be used to render the part in VR. This means you need
          * to create a second mapper/actor combination for use in VR - that is the role
          * of this function. */


          /* 1. Create new mapper */
        
          /* 2. Create new actor and link to mapper */
         
          /* 3. Link the vtkProperties of the original actor to the new actor. This means
           *    if you change properties of the original part (colour, position, etc), the
             changes will be reflected in the GUI AND VR rendering.*/
                
         
            // See the vtkActor documentation, particularly the GetProperty() and SetProperty() functions.

           /* The new vtkActor pointer must be returned here */
           return nullptr;
       }

     //VTKLighting
