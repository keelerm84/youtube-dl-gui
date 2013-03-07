#include <QStringList>
#include <QTextStream>
#include "youtubevideoformatretriever.h"

YouTubeVideoFormatRetriever::YouTubeVideoFormatRetriever(DownloadProperties properties) : YouTubeDl(properties) {
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
}

YouTubeVideoFormatRetriever::~YouTubeVideoFormatRetriever() {
}

void YouTubeVideoFormatRetriever::getDesiredFormat() {
  process->start(settings.getProgram(), QStringList() << "-q" << "--list-formats" << properties.getUrl());
}

void YouTubeVideoFormatRetriever::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
  if ( 0 != exitCode ) {
    emit error(generateErrorMessage());
  } else {
    QTextStream stream(process->readAllStandardOutput());
    QRegExp formatRE("^\\d+\\s+:\\s+" + properties.getVideoFormat() + "\\s+.*");

    while ( !stream.atEnd() ) {
      QString line = stream.readLine();

      if ( !formatRE.exactMatch(line) ) continue;

      emit success(line.left(line.indexOf(":")).trimmed().toInt());
      return;
    }

    emit error("This video does not support the requested video format.");
  }
}
