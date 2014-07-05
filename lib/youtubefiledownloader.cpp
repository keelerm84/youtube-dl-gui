#include <QStringList>
#include "youtubefiledownloader.h"

YouTubeFileDownloader::YouTubeFileDownloader(DownloadProperties properties) : YouTubeDl(properties) {
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
}

YouTubeFileDownloader::~YouTubeFileDownloader() {
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
    arguments << "--keep-video" << "--format" << properties.getVideoFormat();
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
