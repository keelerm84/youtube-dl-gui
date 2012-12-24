#include "downloaditem.h"

DownloadItem::DownloadItem(DownloadProperties properties, QTreeWidget * parent) : QTreeWidgetItem(parent), properties(properties) {
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
    format = "Video & Audio";
  } else if ( ! properties.isVideoDownloadEnabled() && properties.isAudioDownloadEnabled() ) {
    format = "Audio Only";
  } else {
    format = "Video Only";
  }

  setText(1, properties.getTitle());
  setText(2, format);
  setText(3, properties.isVideoDownloadEnabled() ? properties.getVideoFormat() : "n/a");
  setText(4, properties.isAudioDownloadEnabled() ? properties.getAudioFormat() : "n/a");
}
