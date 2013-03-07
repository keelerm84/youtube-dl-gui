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
  connect(titleRetriever, SIGNAL(error(QString)), titleRetriever, SLOT(deleteLater()));
  connect(titleRetriever, SIGNAL(success(QString, QString)), this, SLOT(setItemTitle(QString, QString)));
  connect(titleRetriever, SIGNAL(success(QString, QString)), titleRetriever, SLOT(deleteLater()));
  titleRetriever->getTitle();
}

void DownloadQueue::setItemTitle(QString url, QString title) {
  foreach(QTreeWidgetItem * item, findItems(url, Qt::MatchExactly, 1)) {
    DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);
    downloadItem->setTitle(title);
  }
}
