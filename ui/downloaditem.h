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

  void setProperties(DownloadProperties _properties);
  DownloadProperties getProperties();

protected:
  DownloadProperties properties;
  void updateDisplay();
};

#endif /* _DOWNLOAD_ITEM_ */
