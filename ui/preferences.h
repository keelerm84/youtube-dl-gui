#ifndef _PREFERENCES_H
#define _PREFERENCES_H

#include <QDialog>
#include "../util/settings.h"

namespace Ui {
  class Preferences;
}

class Preferences : public QDialog
{
  Q_OBJECT

public:
  Preferences(QWidget * parent = 0);
  ~Preferences();

signals:
  void dirty();

protected slots:
  void reject();
  void savePreferences();
  void browseDownloadDirectory();
  void setDirty();

protected:
  bool confirmClose();
  void populateUi();
  Settings settings;
  bool isDirty;

private:
  Ui::Preferences * ui;
};

#endif /* _PREFERENCES_H */
