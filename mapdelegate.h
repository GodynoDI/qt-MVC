#ifndef MAPDELEGATE_H
#define MAPDELEGATE_H

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include "mapmodel.h"

class MapDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit MapDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MAPDELEGATE_H
