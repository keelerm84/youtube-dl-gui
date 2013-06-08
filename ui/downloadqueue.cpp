#include <QStringList>
#include <QHeaderView>
#include "downloadqueue.h"
#include "../lib/youtubetitleretriever.h"
#include "downloaditemdelegate.h"

DownloadQueue::DownloadQueue(QWidget * parent) : QTreeWidget(parent) {
  setHeaderLabels(QStringList() << tr("Status") << tr("Title") << tr("Formats") << tr("Video Format") << tr("Audio Format"));
  header()->setResizeMode(0, QHeaderView::ResizeToContents);
  header()->setResizeMode(1, QHeaderView::ResizeToContents);
  header()->setResizeMode(2, QHeaderView::ResizeToContents);
  header()->setResizeMode(3, QHeaderView::ResizeToContents);
  header()->setResizeMode(4, QHeaderView::ResizeToContents);

  DownloadItemDelegate * delegate = new DownloadItemDelegate(this);
  setItemDelegate(delegate);
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

void DownloadQueue::clearFinished() {
  for(int i = 0; i < topLevelItemCount(); ++i) {
    DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(topLevelItem(i));
    if ( downloadItem->isComplete() ) {
      delete downloadItem;
    }
  }
}

void DownloadQueue::remove() {
  QTreeWidgetItem * item = currentItem();

  if ( 0 == item ) return;

  DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);

  if ( downloadItem->isComplete() || downloadItem->isAvailableForDownload() ) {
    delete downloadItem;
  }
}

void DownloadQueue::promote() {
  QTreeWidgetItem * item = currentItem();

  if ( 0 == item ) return;

  int row = currentIndex().row();

  if ( 0 == row ) return;

  takeTopLevelItem(row);
  insertTopLevelItem(row - 1, item);
  setCurrentItem(item);

}

void DownloadQueue::demote() {
  QTreeWidgetItem * item = currentItem();

  if ( 0 == item ) return;

  int row = currentIndex().row();

  if ( row == topLevelItemCount() - 1 ) return;

  takeTopLevelItem(row);
  insertTopLevelItem(row + 1, item);
  setCurrentItem(item);
}
