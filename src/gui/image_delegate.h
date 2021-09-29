#pragma once

#include <QAbstractItemDelegate>
#include <QSize>
#include <QPixmap>
#include <QPainter>

class ImageDelegate : public QAbstractItemDelegate {
    Q_OBJECT

    public:
        ImageDelegate(QObject *parent = nullptr);

        void paint(QPainter *painter, const QStyleOptionViewItem &option,
                   const QModelIndex& index) const;

        QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

        void getImage(const QString& link);
};
