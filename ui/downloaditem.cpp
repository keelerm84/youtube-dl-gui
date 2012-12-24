#include "downloaditem.h"

DownloadItem::DownloadItem(DownloadProperties properties, QTreeWidget * parent) : QTreeWidgetItem(parent), properties(properties), inProgress(false) {
  updateDisplay();
}

DownloadItem::~DownloadItem() {
}


void DownloadItem::setProperties(DownloadProperties _properties) {
  properties = _properties;
  updateDisplay();
}

DownloadProperties DownloadItem::getProperties() {
  return properties;
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

void DownloadItem::setInProgress(bool isInProgress) {
  inProgress = isInProgress;
  updateDisplay();
}

bool DownloadItem::isInProgress() {
  return inProgress;
}
