// paintwidget.cpp

#include "paintwidget.h"
#include <QPainter>
#include <QColor>
#include <iostream>
#include <chrono>

QColor randomColor();

PaintWidget::PaintWidget(QWidget *parent) :
  QWidget(parent)
{
  setFixedSize(GRID_SIZE << GRID_MAGN, GRID_SIZE << GRID_MAGN);
  randomizeGrid();
}

// SLOTS

void PaintWidget::tick()
{
  int copy[GRID_SIZE][GRID_SIZE];
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
      copy[x][y] = grid[x][y];

  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
    {
      int nextValue = (copy[x][y] + 1) % GRID_VAL_MAX;
      if (
        nextValue == copy[(x + 1) % GRID_SIZE][y]
        || nextValue == copy[(x - 1) % GRID_SIZE][y]
        || nextValue == copy[x][(y + 1) % GRID_SIZE]
        || nextValue == copy[x][(y - 1) % GRID_SIZE]
        )
        grid[x][y] = nextValue;
    }
  repaint();
}

void PaintWidget::reset()
{
  randomizeGrid();
  repaint();
}

// PRIVATE

void PaintWidget::paintEvent(QPaintEvent *)
{
  QPainter p;
  p.begin(this);
  int ringBufI = 0;
  int ringBuf[GRID_SIZE];
  for (int i = 0; i < GRID_SIZE; i++)
    ringBuf[i] = grid[GRID_SIZE - 1][i];

  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
    {
      p.fillRect(x << GRID_MAGN, y << GRID_MAGN, 1 << GRID_MAGN, 1 << GRID_MAGN, QBrush(getColor(grid[x][y], GRID_VAL_MAX), Qt::SolidPattern));
    }
  p.end();
  countFrame();
}

void PaintWidget::countFrame()
{
  fpsFrameCounter++;
  if (fpsFrameCounter >= FPS_AVERAGE_FRAME_COUNT)
  {
    auto finish = std::chrono::high_resolution_clock::now();
    unsigned long ns = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
    double fps = 1e9 * (double) fpsFrameCounter / (double) ns;
    std::cout << fps << " fps\n";
    start = std::chrono::high_resolution_clock::now();
    fpsFrameCounter = 0;
    emit signalFpsCalculated(fps);
  }
}

void PaintWidget::randomizeGrid()
{
  srand((unsigned) time(NULL));
  for (int x = 0; x < GRID_SIZE; x++)
    for (int y = 0; y < GRID_SIZE; y++)
      grid[x][y] = rand() % (GRID_VAL_MAX + 1);
      //grid[x][y] = (x + y) * (GRID_VAL_MAX+1) / 2 / GRID_SIZE % (GRID_VAL_MAX+1);
}

// SUBS

QColor getColor(int value, int maxValue)
{
  if (value > maxValue) return QColor(0xff, 0xff, 0xff);
  if (value < 0) return QColor(0x00, 0x00, 0x00);

  bool blackAndWhite = false;
  if (blackAndWhite)
  {
    int alpha = 0xFF * value / maxValue;
    return QColor(alpha, alpha, alpha);
  }

  int chunkSize = maxValue / 6;
  int chunkIndex = value / chunkSize;
  int chunkValue = value % chunkSize;
  int fadeColorValue = 0xFF * chunkValue / chunkSize;
  if (chunkIndex % 2 == 1)
    fadeColorValue = 0xFF - fadeColorValue;
  int colors[3] = {0, 0, 0};
  colors[chunkIndex % 3] = fadeColorValue;
  colors[2 - chunkIndex / 2 % 3] = 0x0;
  colors[(3 - ((chunkIndex + 5) % 6) / 2) % 3] = 0xFF;
  return QColor(colors[0], colors[1], colors[2]);
}

QColor randomColor()
{
  srand((unsigned) time(NULL));
  return QColor(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
}