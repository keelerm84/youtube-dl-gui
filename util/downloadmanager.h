#ifndef _YOUTUBE_DOWNLOAD_MANAGER_H
#define _YOUTUBE_DOWNLOAD_MANAGER_H

#include <QObject>
#include "../ui/downloadqueue.h"
#include "../ui/downloaditem.h"

class DownloadManager : public QObject
{
  Q_OBJECT

public:
  DownloadManager(DownloadQueue * queue, QObject * parent = 0);
  ~DownloadManager();

signals:
  void complete();

protected slots:
  void downloadAll();
  void error(QString error);
  void downloadSuccessful(DownloadProperties properties);

protected:
  DownloadQueue * queue;
  DownloadItem * download;
  bool inProgress;

  DownloadItem * getNextDownloadItem();
  void downloadFiles();
};

#endif /* _YOUTUBE_DOWNLOAD_MANAGER_H */
