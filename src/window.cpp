#include "window.h"

#include <QPushButton>
#include <QApplication>
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


Window::Window(QWidget *parent) :
  QWidget(parent)
{
  setFixedSize(GRID_SIZE << GRID_MAGN, (GRID_SIZE << GRID_MAGN) + BAR_HEIGHT);

  m_buttonStep = new QPushButton("step", this);
  m_buttonStep->setGeometry(BAR_PADDING, (GRID_SIZE << GRID_MAGN) + BAR_PADDING, BUTTON_WIDTH, BAR_HEIGHT - 2*BAR_PADDING);
  QObject::connect(m_buttonStep, SIGNAL(clicked()), this, SLOT(slotButtonStepPressed()));

  m_buttonReset = new QPushButton("reset", this);
  m_buttonReset->setGeometry(2 * BAR_PADDING + BUTTON_WIDTH, (GRID_SIZE << GRID_MAGN) + BAR_PADDING, BUTTON_WIDTH, BAR_HEIGHT - 2 * BAR_PADDING);
  QObject::connect(m_buttonReset, SIGNAL(clicked()), this, SLOT(slotButtonResetPressed()));

  m_fpsCounter = new QLabel(this);
  m_fpsCounter->setGeometry((GRID_SIZE << GRID_MAGN) - BAR_PADDING - BUTTON_WIDTH, (GRID_SIZE << GRID_MAGN) + BAR_PADDING, BUTTON_WIDTH, BAR_HEIGHT - 2 * BAR_PADDING);;
  m_fpsCounter->setText("-");

  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(slotButtonStepPressed()));
  timer->start(50);

  m_paintWidget = new PaintWidget(this);
  QObject::connect(m_paintWidget, SIGNAL(signalFpsCalculated(double)), this, SLOT(slotRefreshFpsCounter(double)));
}

void Window::slotButtonStepPressed()
{
  m_paintWidget->tick();
}

void Window::slotButtonResetPressed()
{
  m_paintWidget->reset();
}

void Window::slotRefreshFpsCounter(double fps)
{
  
  m_fpsCounter->setText(QString::fromStdString(std::to_string(fps)));
}




