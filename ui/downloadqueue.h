#ifndef _DOWNLOAD_QUEUE_
#define _DOWNLOAD_QUEUE_

#include <QTreeWidget>

class DownloadQueue : public QTreeWidget
{
  Q_OBJECT

public:
  DownloadQueue(QWidget * parent = 0);
  ~DownloadQueue();
};

#endif /* _DOWNLOAD_QUEUE_ */
