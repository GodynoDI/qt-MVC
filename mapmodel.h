#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include <QDebug>

class MapModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MapModel(QObject *parent = nullptr);
    ~MapModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void addItem(int key, const QString &value);
    void removeItem(int key);

private:
    QMap<int, QString> qmap;
};

#endif // MAPMODEL_H
