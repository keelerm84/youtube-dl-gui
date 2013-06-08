#include "downloaditem.h"

DownloadItem::DownloadItem(DownloadProperties properties, QTreeWidget * parent) :
  QTreeWidgetItem(parent), properties(properties), isDownloading(false), isDownloaded(false), error("") {
  updateDisplay();

  setFlags(flags() | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
}

DownloadItem::~DownloadItem() {
}

DownloadProperties DownloadItem::getProperties() {
  return properties;
}

void DownloadItem::setProperties(DownloadProperties _properties) {
  properties = _properties;
  error = "";

  // TODO Make use of QPixmapCache
  QPixmap px(16,16);
  px.fill(Qt::transparent);
  setIcon(0, QIcon(px));
}

void DownloadItem::setTitle(QString title) {
  properties.setTitle(title);
  updateDisplay();
}

void DownloadItem::setVideoFormatValue(int format) {
  properties.setVideoFormatValue(format);
}


void DownloadItem::updateDisplay() {
  QString format;

  if ( properties.isVideoDownloadEnabled() && ! properties.isAudioDownloadEnabled() ) {
    format = "Video";
  } else if ( ! properties.isVideoDownloadEnabled() && properties.isAudioDownloadEnabled() ) {
    format = "Audio";
  } else {
    format = "Video & Audio";
  }

  setText(1, properties.getTitle());
  setText(2, format);
  setText(3, properties.isVideoDownloadEnabled() ? properties.getVideoFormat() : "n/a");
  setText(4, properties.isAudioDownloadEnabled() ? properties.getAudioFormat() : "n/a");
}

bool DownloadItem::isAvailableForDownload() {
  return ( isDownloading || isDownloaded || 0 < error.length() ) ? false : true;
}

bool DownloadItem::isComplete() {
  return isDownloaded;
}

bool DownloadItem::downloading() {
  return isDownloading;
}

void DownloadItem::setDownloadComplete() {
  isDownloaded = true;
  setIcon(0, QIcon(":/images/complete.png"));
}

void DownloadItem::setDownloadInProgress() {
  isDownloading = true;
  setIcon(0, QIcon(":/images/downloading.png"));
}

void DownloadItem::setError(QString _error) {
  error = _error;
  setToolTip(0, error);
  setIcon(0, QIcon(":/images/error.png"));
  isDownloading = false;
}
