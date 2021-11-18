// paintwidget.h

#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <iostream>
#include <chrono>

#define GRID_SIZE 150
#define GRID_VAL_MAX 16
#define GRID_MAGN 2
#define FPS_AVERAGE_FRAME_COUNT 30

class PaintWidget : public QWidget
{
  Q_OBJECT

public:
  PaintWidget(QWidget *parent = 0);

private:
  int grid[GRID_SIZE][GRID_SIZE];
  int fpsFrameCounter = 0;
  std::chrono::time_point<std::chrono::steady_clock> start;

public slots:
  void reset();
  void tick();

signals:
  void signalFpsCalculated(double fps);

private:
  void paintEvent(QPaintEvent *);
  void countFrame();
  void randomizeGrid();
};

QColor getColor(int value, int maxValue);

#endif // WINDOW_H