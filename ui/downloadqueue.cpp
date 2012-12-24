#include <QStringList>
#include <QHeaderView>
#include "downloadqueue.h"
#include "../lib/youtubetitleretriever.h"

DownloadQueue::DownloadQueue(QWidget * parent) : QTreeWidget(parent) {
  setHeaderLabels(QStringList() << tr("Status") << tr("Title") << tr("Formats") << tr("Video Format") << tr("Audio Format"));
  header()->setResizeMode(0, QHeaderView::ResizeToContents);
  header()->setResizeMode(1, QHeaderView::ResizeToContents);
  header()->setResizeMode(2, QHeaderView::ResizeToContents);
  header()->setResizeMode(3, QHeaderView::ResizeToContents);
  header()->setResizeMode(4, QHeaderView::ResizeToContents);
}

DownloadQueue::~DownloadQueue() {
}

void DownloadQueue::addTopLevelItem(DownloadItem * item) {
  QTreeWidget::addTopLevelItem(item);

  YouTubeTitleRetriever * titleRetriever = new YouTubeTitleRetriever(item->getProperties());
  connect(titleRetriever, SIGNAL(error(QString, DownloadProperties)), titleRetriever, SLOT(deleteLater()));
  connect(titleRetriever, SIGNAL(success(DownloadProperties)), this, SLOT(setItemTitle(DownloadProperties)));
  connect(titleRetriever, SIGNAL(success(DownloadProperties)), titleRetriever, SLOT(deleteLater()));
  titleRetriever->getTitle();
}

void DownloadQueue::setItemTitle(DownloadProperties properties) {
  foreach(QTreeWidgetItem * item, findItems(properties.getUrl(), Qt::MatchExactly, 1)) {
    DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);
    downloadItem->setProperties(properties);
  }
}
