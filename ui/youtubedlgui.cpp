#include <QMessageBox>
#include <QUrl>
#include "../lib/downloadproperties.h"
#include "../util/settings.h"
#include "downloaditem.h"
#include "preferences.h"
#include "ui_youtubedlgui.h"
#include "youtubedlgui.h"

YouTubeDlGui::YouTubeDlGui(QWidget * parent) : QMainWindow(parent), ui(new Ui::YouTubeDlGui) {
  ui->setupUi(this);

  connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
  connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
  connect(ui->actionPreferences, SIGNAL(triggered()), this, SLOT(showPreferences()));

  connect(ui->btnAdd, SIGNAL(clicked(bool)), this, SLOT(addDownload()));
  connect(ui->btnCollapse, SIGNAL(clicked(bool)), this, SLOT(toggleAdvancedVisiblity()));
  connect(ui->btnClearFinished, SIGNAL(clicked(bool)), ui->tblDownloadQueue, SLOT(clearFinished()));
  connect(ui->btnRemove, SIGNAL(clicked(bool)), ui->tblDownloadQueue, SLOT(remove()));
  connect(ui->btnPromote, SIGNAL(clicked(bool)), ui->tblDownloadQueue, SLOT(promote()));
  connect(ui->btnDemote, SIGNAL(clicked(bool)), ui->tblDownloadQueue, SLOT(demote()));
  connect(ui->cmbDownloadOptions, SIGNAL(currentIndexChanged(QString)), this, SLOT(enableAdvancedProperties()));

  manager = new DownloadManager(ui->tblDownloadQueue, this);
  connect(ui->btnDownload, SIGNAL(clicked(bool)), manager, SLOT(downloadAll()));

  populateUi();

  ui->frameAdvanced->setVisible(false);
  enableAdvancedProperties();
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

void YouTubeDlGui::populateUi() {
  Settings settings;

  ui->cmbDownloadOptions->addItems(QStringList() << "Video Only" << "Audio Only" << "Video & Audio");

  ui->cmbAudioFormat->addItems(settings.supportedAudioFormats());
  ui->cmbVideoFormat->addItems(settings.supportedVideoFormats());

  int audioIndex = ui->cmbAudioFormat->findText(settings.getAudioFormat());
  ui->cmbAudioFormat->setCurrentIndex(-1 == audioIndex ? 1 : audioIndex);

  int videoIndex = ui->cmbVideoFormat->findText(settings.getVideoFormat());
  ui->cmbVideoFormat->setCurrentIndex(-1 == videoIndex ? 1 : videoIndex);
}

void YouTubeDlGui::toggleAdvancedVisiblity() {
  ui->frameAdvanced->setVisible(! ui->frameAdvanced->isVisible());

  QIcon collapseIcon = ui->frameAdvanced->isVisible() ? QIcon(":/images/collapse.png") : QIcon(":/images/expand-10x6.png");
  ui->btnCollapse->setIcon(collapseIcon);
  ui->lblAdvanced->setText(ui->frameAdvanced->isVisible() ? tr("Hide Advanced") : tr("Show Advanced"));
}

void YouTubeDlGui::enableAdvancedProperties() {
  QString downloadOption = ui->cmbDownloadOptions->currentText();

  ui->cmbVideoFormat->setEnabled(false);
  ui->cmbAudioFormat->setEnabled(false);

  if ( -1 != downloadOption.indexOf("Video")) {
    ui->cmbVideoFormat->setEnabled(true);
  }

  if ( -1 != downloadOption.indexOf("Audio")) {
    ui->cmbAudioFormat->setEnabled(true);
  }
}

void YouTubeDlGui::addDownload() {
  QUrl validator(ui->txtUrl->text());

  if ( 0 == ui->txtUrl->text().length() || ! validator.isValid() ) {
    QMessageBox::critical(this, tr("Invalid URL"), tr("The specified URL is invalid.  Please make sure you have specified the correct URL."), QMessageBox::Ok);
    return;
  }

  DownloadProperties properties(ui->txtUrl->text());
  properties.enableVideoDownload(ui->cmbVideoFormat->isEnabled());
  properties.enableAudioDownload(ui->cmbAudioFormat->isEnabled());

  properties.setVideoFormat(ui->cmbVideoFormat->currentText());
  properties.setAudioFormat(ui->cmbAudioFormat->currentText());

  ui->tblDownloadQueue->addTopLevelItem(new DownloadItem(properties));
  ui->txtUrl->setText("");
}
