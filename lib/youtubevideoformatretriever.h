#ifndef _YOUTUBE_VIDEO_FORMAT_RETRIEVER_H
#define _YOUTUBE_VIDEO_FORMAT_RETRIEVER_H

#include "youtubedl.h"
#include "downloadproperties.h"

class YouTubeVideoFormatRetriever : public YouTubeDl
{
  Q_OBJECT

public:
  YouTubeVideoFormatRetriever(DownloadProperties properties);
  ~YouTubeVideoFormatRetriever();

  void getDesiredFormat();

signals:
  void success(int format);

protected slots:
  void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif /* _YOUTUBE_VIDEO_FORMAT_RETRIEVER_H */
