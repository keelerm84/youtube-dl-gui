#ifndef _YOUTUBE_FILE_DOWNLOADER_H
#define _YOUTUBE_FILE_DOWNLOADER_H

#include "youtubedl.h"
#include "downloadproperties.h"

class YouTubeFileDownloader : public YouTubeDl
{
  Q_OBJECT

public:
  YouTubeFileDownloader(DownloadProperties properties);
  ~YouTubeFileDownloader();

  void retrieveFile();

signals:
  void success(DownloadProperties properties);

protected slots:
  void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
  QStringList generateArguments();
};

#endif /* _YOUTUBE_FILE_DOWNLOADER_H */
