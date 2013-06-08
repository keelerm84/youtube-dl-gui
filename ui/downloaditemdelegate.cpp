#include "downloaditemdelegate.h"
#include "../util/settings.h"
#include <QComboBox>
#include <QDebug>

DownloadItemDelegate::DownloadItemDelegate(DownloadQueue * parent) : QStyledItemDelegate(parent), queue(parent) {
}

DownloadItemDelegate::~DownloadItemDelegate() {
}

QWidget * DownloadItemDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const {
  Settings settings;
  QTreeWidgetItem * item = queue->topLevelItem(index.row());
  DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);

  if ( downloadItem->downloading() || downloadItem->isComplete() ) return 0;

  if ( VIDEO_FORMAT == index.column()  && downloadItem->getProperties().isVideoDownloadEnabled() ) {
    QComboBox * videoFormats = new QComboBox(parent);

    foreach(QString format, settings.supportedVideoFormats()) {
      videoFormats->addItem(format, format);
    }

    return videoFormats;
  } else if ( AUDIO_FORMAT == index.column()  && downloadItem->getProperties().isAudioDownloadEnabled() ) {
    QComboBox * audioFormats = new QComboBox(parent);

    foreach(QString format, settings.supportedAudioFormats()) {
      audioFormats->addItem(format, format);
    }

    return audioFormats;
  }

  return 0;
}

void DownloadItemDelegate::setEditorData ( QWidget * editor, const QModelIndex & index ) const {
  if ( VIDEO_FORMAT == index.column() || AUDIO_FORMAT == index.column() ) {
    QComboBox * formats = static_cast<QComboBox *>(editor);
    formats->setCurrentIndex(formats->findData(index.data(Qt::EditRole), Qt::EditRole));
  } else {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void DownloadItemDelegate::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const {
  QTreeWidgetItem * item = queue->topLevelItem(index.row());
  DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);
  DownloadProperties properties = downloadItem->getProperties();

  if ( VIDEO_FORMAT == index.column() ) {
    QComboBox * cmbPriority = static_cast<QComboBox *>(editor);
    int i = cmbPriority->currentIndex();

    QString videoFormat = cmbPriority->itemData(i, Qt::DisplayRole).toString();
    properties.setVideoFormat(videoFormat);

    model->setData(index, videoFormat, Qt::DisplayRole);
    model->setData(index, videoFormat, Qt::UserRole);
  } else if ( AUDIO_FORMAT == index.column() ) {
    QComboBox * cmbPriority = static_cast<QComboBox *>(editor);
    int i = cmbPriority->currentIndex();

    QString audioFormat = cmbPriority->itemData(i, Qt::DisplayRole).toString();
    properties.setAudioFormat(audioFormat);

    model->setData(index, audioFormat, Qt::DisplayRole);
    model->setData(index, audioFormat, Qt::UserRole);
  } else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }

  downloadItem->setProperties(properties);
}

void DownloadItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const {
    QStyledItemDelegate::paint(painter, option, index);
}
