#ifndef _YOUTUBE_TITLE_RETRIEVER_H
#define _YOUTUBE_TITLE_RETRIEVER_H

#include "youtubedl.h"
#include "downloadproperties.h"

class YouTubeTitleRetriever : public YouTubeDl
{
  Q_OBJECT

public:
  YouTubeTitleRetriever(DownloadProperties properties);
  ~YouTubeTitleRetriever();

  void getTitle();

signals:
  void success(QString url, QString title);

protected slots:
  void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif /* _YOUTUBE_TITLE_RETRIEVER_H */
