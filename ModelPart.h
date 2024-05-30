//begin Modelpart.h
/**     @file ModelPart.h
  *
  *     EEEE2076 - Software Engineering & VR Project
  *
  *     Edward Taylor 2024
  */

#ifndef VIEWER_MODELPART_H
#define VIEWER_MODELPART_H

#include <QString>
#include <QList>
#include <QVariant>

    /**
    * VTK headers 
    */
    #include <vtkSmartPointer.h>
    #include <vtkMapper.h>
    #include <vtkActor.h>
    #include <vtkSTLReader.h>
    #include <vtkColor.h>
#include <QColorDialog>

class ModelPart {
public:
    /** 
    Constructor
     */
    ModelPart(const QList<QVariant>& data, ModelPart* parent = nullptr);

    /** Destructor
      * Needs to free array of child items
      */
    ~ModelPart();

    /** Add a child to this item.
      * @param item Pointer to child object (must already be allocated using new)
      */
    void appendChild(ModelPart* item);

    /** Return child at position 'row' below this item
      * @param row is the row number (below this item)
      * @return pointer to the item requested.
      */
    ModelPart* child(int row);
    int row() const;

    /** Return number of children to this item
      * @return number of children
      */
    int childCount() const;

    /** Return the data item at a particular column for this item.
      * i.e. either part name of visibility
      * used by Qt when displaying tree
      * @param column is column index
      * @return the QVariant (represents string)
      */
    QVariant data(int column) const;
    int columnCount() const;


    /** Default function required by Qt to allow setting of part
      * properties within treeview.
      * @param column is the index of the property to set
      * @param value is the value to apply
      */
    void set(int column, const QVariant& value);

    /** Get pointer to parent item
      * @return pointer to parent item
      */
    ModelPart* parentItem();

    /**
    *   Sets the colour that is returned from the option dialog
    */
    void setColor(QColor clr);
    QColor getColor();
    double getColorR();
    double getColorG();
    double getColorB();
    double getColorA();



    /**
    *   Sets the name that is returned from the option dialog
    */
    void setName(QString name);
    const QString getName(void);

    /**
    *   Sets the visibility that is returned from the option dialog (true or false)
    */
    void setVisible(bool isVisible);

    void loadSTL(QString fileName);

 
    bool getVisibility(void);

    vtkSmartPointer<vtkActor> getActor();

    vtkActor* getNewActor();

private:
    QList<ModelPart*>                           m_childItems;       /**< List (array) of child items */
    QList<QVariant>                             m_itemData;         /**< List (array of column data for item */
    ModelPart* m_parentItem;                                        /**< Pointer to parent */
    QColor                                      colour = Qt::white;
    QString                                     name;

    bool                                        visibility;          /**< True/false to indicate if should be visible in model rendering */

     vtkSmartPointer<vtkSTLReader>               stlReader;               /**< Datafile from which part loaded */
     vtkSmartPointer<vtkMapper>                  mapper;             /**< Mapper for rendering */
     vtkSmartPointer<vtkActor>                   actor;              /**< Actor for rendering */
     vtkColor3<unsigned char>                  color;
};

#endif

//end Modelpart.h
