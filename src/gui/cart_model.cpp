#include "cart_model.h"

#include <QStandardItem>

CartModel::CartModel(QObject *parent) : QAbstractTableModel(parent) {}

void CartModel::setCoats(const QVector<Trenchcoat>& _coats) {
    coats = _coats;
}

int CartModel::rowCount(const QModelIndex &parent) const {
    return coats.size();
}

int CartModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant CartModel::data(const QModelIndex &index, int role) const {
    if (coats.empty() || !index.isValid() || index.row() >= coats.size() || role != Qt::DisplayRole)
        return QVariant();

    switch (index.column()) {
        case 0:
            return QString::number(coats[index.row()].price());

        case 1:
            return QString::fromStdString(coats[index.row()].size());

        case 2:
            return QString::fromStdString(coats[index.row()].color());

        case 3:
            return QString::fromStdString(coats[index.row()].photoLink());

        case 4:
            return QString::number(coats[index.row()].quantity());
    }

    return QVariant();
}

QVariant CartModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QStringList headerLabels = { "Price", "Size", "Color", "Image", "Quantity" };

    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    return headerLabels[section];
}
