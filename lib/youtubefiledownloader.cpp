#include <QStringList>
#include "youtubefiledownloader.h"
#include "youtubevideoformatretriever.h"

YouTubeFileDownloader::YouTubeFileDownloader(DownloadProperties properties) : YouTubeDl(properties) {
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
}

YouTubeFileDownloader::~YouTubeFileDownloader() {
}

void YouTubeFileDownloader::getFile() {
  if ( properties.isVideoDownloadEnabled() ) {
    retrieveVideoFormat();
  } else {
    retrieveFile();
  }
}

void YouTubeFileDownloader::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
  if ( 0 != exitCode ) {
    emit error(generateErrorMessage());
  } else {
    emit success(properties);
  }
}

QStringList YouTubeFileDownloader::generateArguments() {
  QStringList arguments;

  if ( properties.isVideoDownloadEnabled() ) {
    arguments << "--keep-video" << "--format" << QString::number(videoFormat);
  }

  if ( properties.isAudioDownloadEnabled() ) {
    arguments << "--extract-audio" << "--audio-format" << properties.getAudioFormat();
  }

  QString title = properties.getTitle().replace(QRegExp("[\\/:*?\"<>|]"), "") + ".%(ext)s";

  arguments << "--output" << title << properties.getUrl();

  return arguments;
}

void YouTubeFileDownloader::retrieveFile() {
  process->setWorkingDirectory(settings.getDownloadLocation());
  process->start(settings.getProgram(), generateArguments());
}

void YouTubeFileDownloader::retrieveVideoFormat() {
  YouTubeVideoFormatRetriever * videoFormatRetriever = new YouTubeVideoFormatRetriever(properties);

  connect(videoFormatRetriever, SIGNAL(error(QString)), this, SIGNAL(error(QString)));
  connect(videoFormatRetriever, SIGNAL(error(QString)), videoFormatRetriever, SLOT(deleteLater()));
  connect(videoFormatRetriever, SIGNAL(success(int)), this, SLOT(setVideoFormatValue(int)));
  connect(videoFormatRetriever, SIGNAL(success(int)), videoFormatRetriever, SLOT(deleteLater()));

  videoFormatRetriever->getDesiredFormat();
}

void YouTubeFileDownloader::setVideoFormatValue(int format) {
  videoFormat = format;
  retrieveFile();
}
