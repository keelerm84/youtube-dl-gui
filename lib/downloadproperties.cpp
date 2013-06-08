#include "downloadproperties.h"

DownloadProperties::DownloadProperties(QString url) :
  downloadAudio(false), downloadVideo(true), videoFormat("mp4"), videoFormatValue(-1), audioFormat("best"), url(url), title("") {
}

DownloadProperties::~DownloadProperties() {
}

void DownloadProperties::enableVideoDownload(bool enable) {
  downloadVideo = enable;
}

bool DownloadProperties::isVideoDownloadEnabled() {
  return downloadVideo;
}

void DownloadProperties::enableAudioDownload(bool enable) {
  downloadAudio = enable;
}

bool DownloadProperties::isAudioDownloadEnabled() {
  return downloadAudio;
}

void DownloadProperties::setVideoFormat(QString format) {
  videoFormat = format;
}

QString DownloadProperties::getVideoFormat() {
  return videoFormat;
}

void DownloadProperties::setVideoFormatValue(int format) {
  videoFormatValue = format;
}

int DownloadProperties::getVideoFormatValue() {
  return videoFormatValue;
}

void DownloadProperties::setAudioFormat(QString format) {
  audioFormat = format;
}

QString DownloadProperties::getAudioFormat() {
  return audioFormat;
}

void DownloadProperties::setTitle(QString _title) {
  title = _title;
}

QString DownloadProperties::getTitle() {
  return ( 0 == title.length() ) ? url : title;
}

QString DownloadProperties::getUrl() {
  return url;
}
