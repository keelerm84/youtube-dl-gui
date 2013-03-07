#include "downloaditem.h"

DownloadItem::DownloadItem(DownloadProperties properties, QTreeWidget * parent) :
  QTreeWidgetItem(parent), properties(properties), isDownloading(false), isDownloaded(false), error("") {
  updateDisplay();
}

DownloadItem::~DownloadItem() {
}

DownloadProperties DownloadItem::getProperties() {
  return properties;
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

void DownloadItem::setDownloadComplete() {
  isDownloaded = true;
  setIcon(0, QIcon(":/images/complete-16.png"));
}

void DownloadItem::setDownloadInProgress() {
  isDownloading = true;
  setIcon(0, QIcon(":/images/downloading-16.png"));
}

void DownloadItem::setError(QString _error) {
  error = _error;
  setToolTip(0, error);
  setIcon(0, QIcon(":/images/error-16.png"));
}
