#ifndef _DOWNLOAD_QUEUE_
#define _DOWNLOAD_QUEUE_

#include <QTreeWidget>
#include "downloaditem.h"
#include "../lib/downloadproperties.h"

enum DOWNLOAD_QUEUE_COLUMNS { STATUS, TITLE, FORMAT, VIDEO_FORMAT, AUDIO_FORMAT };

class DownloadQueue : public QTreeWidget
{
  Q_OBJECT

public:
  DownloadQueue(QWidget * parent = 0);
  ~DownloadQueue();

  void addTopLevelItem(DownloadItem * item);

protected slots:
  void setItemTitle(QString url, QString title);
  void clearFinished();
  void remove();
  void promote();
  void demote();
};

#endif /* _DOWNLOAD_QUEUE_ */
