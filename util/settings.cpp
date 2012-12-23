#include <QDesktopServices>
#include "settings.h"

Settings::Settings() {
}

Settings::~Settings() {
}

QString Settings::getOrganizationName() {
  return "Tortugas Consulting, LLC.";
}

QString Settings::getOrganizationDomain() {
  return "tortugas-llc.com";
}

QString Settings::getApplicationName() {
  return "youtube-dl-gui";
}

QString Settings::getApplicationVersion() {
  return "0.1";
}


void Settings::setDownloadLocation(QString path) {
  settings.setValue("directories/audio", path);
}

QString Settings::getDownloadLocation() {
  QDesktopServices services;
  return settings.value("directories/audio", services.storageLocation(QDesktopServices::MusicLocation)).toString();
}

void Settings::setAudioFormat(QString format) {
  settings.setValue("audio/format", format);
}

QString Settings::getAudioFormat() {
  return settings.value("audio/format", "best").toString();
}

QStringList Settings::supportedAudioFormats() {
  return QStringList() <<  "aac" << "best" << "m4a" << "mp3" << "vorbis" << "wav";
}
