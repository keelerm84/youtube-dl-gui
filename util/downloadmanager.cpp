#include "downloadmanager.h"
#include "../lib/youtubefiledownloader.h"

DownloadManager::DownloadManager(DownloadQueue * queue, QObject * parent) : QObject(parent), queue(queue), download(0), inProgress(false) {
}

DownloadManager::~DownloadManager() {
}

void DownloadManager::downloadAll() {
  if ( inProgress ) return;
  inProgress = true;
  downloadFiles();
}

DownloadItem * DownloadManager::getNextDownloadItem() {
  for(int i = 0; i < queue->topLevelItemCount(); ++i) {
    QTreeWidgetItem * item = queue->topLevelItem(i);
    DownloadItem * downloadItem = dynamic_cast<DownloadItem *>(item);

    if ( downloadItem->isAvailableForDownload() ) {
      return downloadItem;
    }
  }

  return 0;
}

void DownloadManager::downloadFiles() {
  download = getNextDownloadItem();

  if ( 0 == download ) {
    inProgress = false;
    emit complete();
    return;
  }

  download->setDownloadInProgress();
  retrieveFile();
}

void DownloadManager::retrieveFile() {
  YouTubeFileDownloader * fileDownloader = new YouTubeFileDownloader(download->getProperties());
  connect(fileDownloader, SIGNAL(error(QString)), this, SLOT(error(QString)));
  connect(fileDownloader, SIGNAL(error(QString)), fileDownloader, SLOT(deleteLater()));

  connect(fileDownloader, SIGNAL(success(DownloadProperties)), this, SLOT(downloadSuccessful(DownloadProperties)));
  connect(fileDownloader, SIGNAL(success(DownloadProperties)), fileDownloader, SLOT(deleteLater()));

  fileDownloader->getFile();
}

void DownloadManager::downloadSuccessful(DownloadProperties properties) {
  download->setDownloadComplete();
  downloadFiles();
}

void DownloadManager::error(QString error) {
  download->setError(error);
  downloadFiles();
}
