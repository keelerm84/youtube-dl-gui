#ifndef _DOWNLOAD_PROPERTIES_
#define _DOWNLOAD_PROPERTIES_

#include <QString>

class DownloadProperties {
public:
  DownloadProperties(QString url);
  ~DownloadProperties();

  void enableVideoDownload(bool enable);
  bool isVideoDownloadEnabled();

  void enableAudioDownload(bool enable);
  bool isAudioDownloadEnabled();

  void setVideoFormat(QString format);
  QString getVideoFormat();

  void setVideoFormatValue(int format);
  int getVideoFormatValue();

  void setAudioFormat(QString format);
  QString getAudioFormat();

  void setTitle(QString _title);
  QString getTitle();

  QString getUrl();

protected:
  bool downloadAudio;
  bool downloadVideo;

  QString videoFormat;
  int videoFormatValue;
  QString audioFormat;

  QString url;
  QString title;
};

#endif /* _DOWNLOAD_PROPERTIES_ */
