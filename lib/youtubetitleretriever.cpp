#include <QStringList>
#include "youtubetitleretriever.h"

YouTubeTitleRetriever::YouTubeTitleRetriever(DownloadProperties properties) : YouTubeDl(properties) {
  connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(processFinished(int, QProcess::ExitStatus)));
}

YouTubeTitleRetriever::~YouTubeTitleRetriever() {
}

void YouTubeTitleRetriever::getTitle() {
  process->start(settings.getProgram(), QStringList() << "--get-title" << properties.getUrl());
}

void YouTubeTitleRetriever::processFinished(int exitCode, QProcess::ExitStatus exitStatus) {
  if ( exitStatus == QProcess::CrashExit ) {
    emit error(generateErrorMessage(), properties);
  } else {
    QString title = process->readAllStandardOutput();
    properties.setTitle(title.replace(QString("\n"), QString("")));
    emit success(properties);
  }
}
