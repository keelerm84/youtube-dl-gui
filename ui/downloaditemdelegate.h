#ifndef _DOWNLOAD_ITEM_DELEGATE_H
#define _DOWNLOAD_ITEM_DELEGATE_H

#include <QStyledItemDelegate>
#include "downloadqueue.h"

namespace Ui {
  class DownloadItemDelegate;
}

class DownloadItemDelegate : public QStyledItemDelegate
{
public:
  DownloadItemDelegate(DownloadQueue * parent = 0);
  ~DownloadItemDelegate();

  QWidget * createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
  void setEditorData ( QWidget * editor, const QModelIndex & index ) const;
  void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
  void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

protected:
  DownloadQueue * queue;
};

#endif /* _DOWNLOAD_ITEM_DELEGATE_H */
