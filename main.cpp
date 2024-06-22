#include <QApplication>
#include <QListView>
#include "mapmodel.h"
#include "mapdelegate.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapModel mapModel;
    QListView mapView;
    mapView.setModel(&mapModel);

    MapDelegate mapDelegate;
    mapView.setItemDelegate(&mapDelegate);
    mapModel.addItem(1, "One");
    mapModel.addItem(2, "Two");
    mapModel.addItem(3, "Three");
    mapView.show();

    return a.exec();
}

