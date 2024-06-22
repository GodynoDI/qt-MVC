#include "mapdelegate.h"
#include <QListWidget>
MapDelegate::MapDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

QWidget *MapDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QListWidget *editor = new QListWidget();
    QHBoxLayout *layout = new QHBoxLayout();
    QSpinBox *spinBox = new QSpinBox();
    QLineEdit *lineEdit = new QLineEdit();
    layout->addWidget(spinBox);
    layout->addWidget(lineEdit);
    editor->setLayout(layout);
    return editor;
}

void MapDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QList<QString> keyVal = index.data().toString().split(' ');
    int key = keyVal[0].toInt();
    QString value = keyVal[1];
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor->layout()->itemAt(0)->widget());
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor->layout()->itemAt(1)->widget());
    spinBox->setValue(key);
    lineEdit->setText(value);
}

void MapDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(editor->layout()->itemAt(0)->widget());
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor->layout()->itemAt(1)->widget());
    qDebug() << "lineEdit text " <<lineEdit->text();
    model->setData(index, QString::number(spinBox->value()) + ' ' + lineEdit->text(), Qt::EditRole);
}

void MapDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
