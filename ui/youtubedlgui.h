#ifndef _YOUTUBE_DL_GUI_H
#define _YOUTUBE_DL_GUI_H

#include <QMainWindow>

namespace Ui {
  class YouTubeDlGui;
}

class YouTubeDlGui : public QMainWindow
{
  Q_OBJECT

public:
  YouTubeDlGui(QWidget * parent = 0);
  ~YouTubeDlGui();

protected:
  void populateUi();

protected slots:
  void showAbout();
  void showPreferences();
  void toggleAdvancedVisiblity();
  void enableAdvancedProperties();
  void addDownload();

private:
  Ui::YouTubeDlGui * ui;
};

#endif /* _YOUTUBE_DL_GUI_H */
