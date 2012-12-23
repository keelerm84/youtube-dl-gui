#ifndef _DOWNLOAD_ITEM_
#define _DOWNLOAD_ITEM_

#include <QTreeWidget>
#include <QTreeWidgetItem>

struct DownloadProperties {
  DownloadProperties() :
    downloadAudio(false), downloadVideo(true), videoFormat("video"), audioFormat("best"), url(""), title("") {}

  bool downloadAudio;
  bool downloadVideo;

  QString videoFormat;
  QString audioFormat;

  QString url;
  QString title;
};

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
