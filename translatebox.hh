/* This file is (c) 2012 Tvangeste <i.4m.l33t@yandex.ru>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#ifndef TRANSLATEBOX_HH
#define TRANSLATEBOX_HH

#include "extlineedit.hh"
#include "wordlist.hh"

#include <QWidget>
#include <QListWidget>
#include <QFocusEvent>

class CompletionList : public WordList
{
  Q_OBJECT

public:
  CompletionList(QWidget *parent = 0);
  int preferredHeight() const;

#if defined(Q_OS_WIN)
  void focusOutEvent (QFocusEvent * event)  {
    if (event->reason() == Qt::ActiveWindowFocusReason)
      hide();
  }
#endif

public slots:
  bool acceptCurrentEntry();

private:
  virtual bool eventFilter( QObject *, QEvent * );
};

class TranslateBox : public QWidget
{
  Q_OBJECT

public:
  explicit TranslateBox(QWidget * parent = 0);
  void setPlaceholderText(const QString &text);
  QLineEdit * translateLine();
  WordList * wordList();
  void setText(QString text, bool showPopup=true)
  { setPopupEnabled( showPopup ); translate_line->setText( text ); setPopupEnabled( true ); }

signals:

public slots:
  void setPopupEnabled(bool enable);

private slots:
  void showPopup();
  void rightButtonClicked();

private:
  bool eventFilter(QObject *obj, QEvent *event);
  CompletionList * word_list;
  ExtLineEdit * translate_line;
  bool m_popupEnabled;
  // QCompleter * completer; // disabled for now
};

#endif // TRANSLATEBOX_HH
