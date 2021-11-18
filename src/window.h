#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include "paintwidget.h"

#define BAR_HEIGHT 50
#define BAR_PADDING 10
#define BUTTON_WIDTH 80

class QPushButton;

class Window : public QWidget
{
  Q_OBJECT

public:
  Window(QWidget *parent = 0);

private:
  QPushButton *m_buttonStep = nullptr;
  QPushButton *m_buttonReset = nullptr;
  QLabel *m_fpsCounter = nullptr;
  PaintWidget *m_paintWidget = nullptr;

private slots:
  void slotButtonStepPressed();
  void slotButtonResetPressed();

public slots:
  void slotRefreshFpsCounter(double fps);

};

#endif // WINDOW_H