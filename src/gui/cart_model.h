#include <QAbstractTableModel>

#include <QVector>
#include "../trenchcoat.h"

class CartModel : public QAbstractTableModel {
    Q_OBJECT

    private:
        QVector<Trenchcoat> coats;

    public:
        CartModel(QObject *parent = nullptr);
        void setCoats(const QVector<Trenchcoat>& coats);

        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};
