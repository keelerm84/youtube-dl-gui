#ifndef _DOWNLOAD_QUEUE_
#define _DOWNLOAD_QUEUE_

#include <QTreeWidget>
#include "downloaditem.h"
#include "../lib/downloadproperties.h"

class DownloadQueue : public QTreeWidget
{
  Q_OBJECT

public:
  DownloadQueue(QWidget * parent = 0);
  ~DownloadQueue();

  void addTopLevelItem(DownloadItem * item);

protected slots:
  void setItemTitle(DownloadProperties properties);
};

#endif /* _DOWNLOAD_QUEUE_ */
