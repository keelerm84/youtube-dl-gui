#ifndef _SETTINGS_
#define _SETTINGS_

#include <QSettings>
#include <QString>
#include <QStringList>

class Settings
{
public:
  Settings();
  ~Settings();

  QString getOrganizationName();
  QString getOrganizationDomain();
  QString getApplicationName();
  QString getApplicationVersion();

  void setDownloadLocation(QString path);
  QString getDownloadLocation();

  void setAudioFormat(QString format);
  QString getAudioFormat();

  QStringList supportedAudioFormats();

protected:
  QSettings settings;
};

#endif /* _SETTINGS_ */
