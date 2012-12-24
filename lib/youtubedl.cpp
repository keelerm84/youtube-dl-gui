#include "youtubedl.h"

YouTubeDl::YouTubeDl(DownloadProperties properties) : properties(properties) {
  process = new QProcess;
}

YouTubeDl::~YouTubeDl() {
  delete process;
}

QString YouTubeDl::generateErrorMessage() {
  QString error;

  switch(process->error()) {
  case QProcess::FailedToStart:
    error = QObject::tr("The process failed to start.");
    break;
  case QProcess::Crashed:
    error = QObject::tr("The process crashed while attempting to run.");
    break;
  case QProcess::Timedout:
    error = QObject::tr("The process has timed out.");
    break;
  case QProcess::WriteError:
    error = QObject::tr("The process has encountered a write error");
    break;
  case QProcess::ReadError:
    error = QObject::tr("The process has encountered a read error.");
    break;
  case QProcess::UnknownError:
    error = QObject::tr("The process has encountered an unknown error.");
    break;
  }

  return error;
}
