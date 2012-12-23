#include <QStringList>
#include <QHeaderView>
#include "downloadqueue.h"

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
