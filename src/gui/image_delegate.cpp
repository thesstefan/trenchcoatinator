#include "image_delegate.h"
#include <QPixmap>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QShortcut>
#include <QStyledItemDelegate>

static QString getPath(QString& link) {
    return "data/" + link.remove(QChar('/'));
}

ImageDelegate::ImageDelegate(QObject *parent) : QAbstractItemDelegate(parent) {}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem& option,
                              const QModelIndex& index) const {
    return QSize(200, 250);
}

void ImageDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem& option,
                          const QModelIndex &index) const {
    if (index.column() != 3) {
        QStyledItemDelegate().paint(painter, option, index);

        return;
    }

    QString link = index.data(Qt::DisplayRole).toString();

    QPixmap pixmap(getPath(link));
    painter->drawPixmap(option.rect, pixmap);
}
