#include <QMessageBox>
#include "ui_youtubedlgui.h"
#include "youtubedlgui.h"
#include "preferences.h"

YouTubeDlGui::YouTubeDlGui(QWidget * parent) : QMainWindow(parent), ui(new Ui::YouTubeDlGui) {
  ui->setupUi(this);
  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
  connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(showPreferences()));
}

YouTubeDlGui::~YouTubeDlGui() {
}

void YouTubeDlGui::showAbout() {
  QMessageBox::about(this, tr("About YouTubeDlGui"),
                     tr("This is a GUI front-end to the extremely useful youtube-dl program, and a C++ port of the excellent youtube-dl-gui.py script.<br/><br/>Authored by Matthew M. Keeler ( @keelerm )"));
}

void YouTubeDlGui::showPreferences() {
  Preferences preferences(this);
  preferences.exec();
}
