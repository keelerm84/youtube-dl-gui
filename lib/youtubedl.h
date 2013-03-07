#ifndef _YOUTUBE_DL_H
#define _YOUTUBE_DL_H

#include <QProcess>
#include <QString>
#include "downloadproperties.h"
#include "../util/settings.h"

class YouTubeDl : public QObject
{
  Q_OBJECT

public:
  YouTubeDl(DownloadProperties properties);
  ~YouTubeDl();

signals:
  void error(QString error);

protected:
  QString generateErrorMessage();

  QProcess * process;
  Settings settings;
  DownloadProperties properties;
};

#endif /* _YOUTUBE_DL_H */
