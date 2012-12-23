#include <QApplication>
#include "ui/youtubedlgui.h"
#include "util/settings.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Settings settings;

  a.setOrganizationName(settings.getOrganizationName());
  a.setOrganizationDomain(settings.getOrganizationDomain());
  a.setApplicationName(settings.getApplicationName());
  a.setApplicationVersion(settings.getApplicationVersion());

  YouTubeDlGui mainWindow;
  mainWindow.show();

  return a.exec();
}
