#ifndef _YOUTUBE_DL_GUI_H
#define _YOUTUBE_DL_GUI_H

#include <QMainWindow>
#include "../util/downloadmanager.h"

namespace Ui {
  class YouTubeDlGui;
}

class YouTubeDlGui : public QMainWindow
{
  Q_OBJECT

public:
  YouTubeDlGui(QWidget * parent = 0);
  ~YouTubeDlGui();

protected slots:
  void showAbout();
  void showPreferences();
  void toggleAdvancedVisiblity();
  void enableAdvancedProperties();
  void addDownload();

protected:
  void populateUi();

  DownloadManager * manager;

private:
  Ui::YouTubeDlGui * ui;
};

#endif /* _YOUTUBE_DL_GUI_H */
