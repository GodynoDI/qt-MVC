#include "mapmodel.h"


MapModel::MapModel(QObject *parent) : QAbstractItemModel(parent)
{
}

MapModel::~MapModel()
{
}

QModelIndex MapModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || column < 0 || row >= rowCount() || column >= columnCount())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex MapModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int MapModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return qmap.size();
}

int MapModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 1;
}

QVariant MapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    int row = index.row();
    QMap<int, QString>::const_iterator it = qmap.constBegin() + row;

    return QString::number(it.key()) + " " + it.value();
}

bool MapModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (!index.isValid() || role != Qt::EditRole || !value.toString().contains(' '))
        return false;
    QStringList keyVal = index.data().toString().split(' ');
    qDebug() << "keyVal[0] " << keyVal[0];
    if(keyVal.count()!= 2)
        return false;
    int key = keyVal[0].toInt();
    keyVal = value.toString().split(' ');
    if(keyVal.count()!= 2)
        return false;

    bool keyDigit;
    int newKey = value.toString().split(' ')[0].toInt(&keyDigit);
    if(!keyDigit || (key!=newKey && qmap.contains(newKey)))
        return false;
    qDebug() << "removed key " << key;

    this->removeItem(key);

    this->addItem(newKey,value.toString().split(' ')[1]);
    qDebug() << "added key " << newKey;
    qDebug() << "added value " << value.toString().split(' ')[1];
    emit dataChanged(index, index);
    return true;
}

void MapModel::addItem(int key, const QString &value)
{
    if (qmap.contains(key))
        return;

    int row = qmap.size();
    qmap.insert(key, value);

    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
}

void MapModel::removeItem(int key)
{
    if (!qmap.contains(key))
        return;

    int row = 0;
    for (QMap<int, QString>::const_iterator it = qmap.constBegin(); it != qmap.constEnd(); ++it, ++row) {
        if (it.key() == key)
            break;
    }

    qmap.remove(key);

    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
}

Qt::ItemFlags MapModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}
