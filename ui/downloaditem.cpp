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
  QString title = 0 == properties.title ? properties.url : properties.title;
  QString format;

  if ( properties.downloadVideo && ! properties.downloadAudio ) {
    format = "Video & Audio";
  } else if ( ! properties.downloadVideo && properties.downloadAudio ) {
    format = "Audio Only";
  } else {
    format = "Video Only";
  }

  setText(1, title);
  setText(2, format);
  setText(3, properties.downloadVideo ? properties.videoFormat : "n/a");
  setText(4, properties.downloadAudio ? properties.audioFormat : "n/a");
}
