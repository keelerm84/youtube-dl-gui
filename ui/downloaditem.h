#ifndef _DOWNLOAD_ITEM_
#define _DOWNLOAD_ITEM_

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "../lib/downloadproperties.h"

class DownloadItem : public QTreeWidgetItem
{
public:
  DownloadItem(DownloadProperties properties, QTreeWidget * parent = 0);
  ~DownloadItem();

  DownloadProperties getProperties();
  void setProperties(DownloadProperties _properties);
  void setTitle(QString title);
  void setVideoFormatValue(int format);

  void setDownloadInProgress();
  void setDownloadComplete();
  void setError(QString _error);

  bool isAvailableForDownload();
  bool isComplete();
  bool downloading();
  void updateDisplay();

protected:
  DownloadProperties properties;

  bool isDownloading;
  bool isDownloaded;
  QString error;
};

#endif /* _DOWNLOAD_ITEM_ */
