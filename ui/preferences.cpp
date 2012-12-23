#include <QFileDialog>
#include <QMessageBox>
#include "ui_preferences.h"
#include "preferences.h"
#include "../util/settings.h"

Preferences::Preferences(QWidget * parent) : QDialog(parent), isDirty(false), ui(new Ui::Preferences) {
  ui->setupUi(this);
  connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(savePreferences()));
  connect(ui->btnBrowse, SIGNAL(clicked()), this, SLOT(browseDownloadDirectory()));

  populateUi();

  connect(ui->cmbAudioFormat, SIGNAL(currentIndexChanged(int)), this, SIGNAL(dirty()));
  connect(ui->cmbVideoFormat, SIGNAL(currentIndexChanged(int)), this, SIGNAL(dirty()));
  connect(this, SIGNAL(dirty()), this, SLOT(setDirty()));
}

Preferences::~Preferences() {
}

void Preferences::reject() {
  if ( ! isDirty || confirmClose() ) {
    accept();
  }
}

bool Preferences::confirmClose() {
  int answer = QMessageBox::question(this, tr("Unsaved Changes"),
                                     tr("You have made changes which have not been saved.  Are you sure you want to discard these changes?"),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  return ( QMessageBox::Yes == answer );
}

void Preferences::savePreferences() {
  settings.setDownloadLocation(ui->txtDownload->text());
  settings.setAudioFormat(ui->cmbAudioFormat->currentText());
  settings.setVideoFormat(ui->cmbVideoFormat->currentText());
}

void Preferences::populateUi() {
  ui->txtDownload->setText(settings.getDownloadLocation());
  ui->cmbAudioFormat->addItems(settings.supportedAudioFormats());
  ui->cmbVideoFormat->addItems(settings.supportedVideoFormats());

  int audioIndex = ui->cmbAudioFormat->findText(settings.getAudioFormat());
  ui->cmbAudioFormat->setCurrentIndex(-1 == audioIndex ? 1 : audioIndex);

  int videoIndex = ui->cmbVideoFormat->findText(settings.getVideoFormat());
  ui->cmbVideoFormat->setCurrentIndex(-1 == videoIndex ? 1 : videoIndex);
}

void Preferences::browseDownloadDirectory() {
  QString path = QFileDialog::getExistingDirectory(this, tr("Please choose a directory to store downloaded files."), settings.getDownloadLocation());

  if ( false == path.isNull() ) {
    ui->txtDownload->setText(path);
    emit dirty();
  }
}

void Preferences::setDirty() {
  isDirty = true;
}
