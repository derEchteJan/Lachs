// paintwidget.cpp

#include "paintwidget.h"

#pragma warning(push, 1) // disable warnings for third party headers
#include <QPainter>
#include <QColor>
#include <iostream>
#include <chrono>
#pragma warning(pop)

#define GRID_FOREACH(_x, _y, _block) for(int _x = 0; _x < GRID_SIZE; _x++) { for(int _y = 0; _y < GRID_SIZE; _y++) _block; }

static QColor getColor(int value, int maxValue);
static QColor randomColor();

PaintWidget::PaintWidget(QWidget* parent) :
	QWidget(parent)
{
	setFixedSize(GRID_SIZE << GRID_MAGN, GRID_SIZE << GRID_MAGN);
	randomizeGrid();
}

// SLOTS

void PaintWidget::tick()
{
	int copy[GRID_SIZE][GRID_SIZE];
	GRID_FOREACH(x, y, copy[x][y] = grid[x][y]);
	GRID_FOREACH(x, y, {
						 int nextValue = (copy[x][y] + 1) % GRID_VAL_MAX;
						 if (
						 nextValue == copy[(x + 1) % GRID_SIZE][y]
						 || nextValue == copy[(x - 1) % GRID_SIZE][y]
						 || nextValue == copy[x][(y + 1) % GRID_SIZE]
						 || nextValue == copy[x][(y - 1) % GRID_SIZE]
						 )
						 {
							 grid[x][y] = nextValue;
						 }
					 });
	repaint();
}

void PaintWidget::reset()
{
	randomizeGrid();
	repaint();
}

// PRIVATE

void PaintWidget::paintEvent(QPaintEvent*)
{
	QPainter p;
	p.begin(this);
	int ringBufI = 0;
	int ringBuf[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; i++)
	{
		ringBuf[i] = grid[GRID_SIZE - 1][i];
	}
	GRID_FOREACH(x, y, p.fillRect(x << GRID_MAGN, y << GRID_MAGN, 1 << GRID_MAGN, 1 << GRID_MAGN, QBrush(getColor(grid[x][y], GRID_VAL_MAX), Qt::SolidPattern)));
	p.end();
	countFrame();
}

void PaintWidget::countFrame()
{
	fpsFrameCounter++;
	if (fpsFrameCounter >= FPS_AVERAGE_FRAME_COUNT)
	{
		clock_t fpsCalcEnd = clock();
		float fps = float(fpsFrameCounter) / (float(fpsCalcEnd - fpsCalcStart) / CLOCKS_PER_SEC);
		//std::cout << "frames: " << fpsFrameCounter << ", seconds: " << (float(fpsCalcEnd - fpsCalcStart) / CLOCKS_PER_SEC) << std::endl;
		std::cout << "fps: " << fps << std::endl;
		emit signalFpsCalculated(fps);
		fpsFrameCounter = 0;
		fpsCalcStart = fpsCalcEnd;
	}
}

void PaintWidget::randomizeGrid()
{
	srand((unsigned)time(NULL));
	GRID_FOREACH(x, y, grid[x][y] = rand() % (GRID_VAL_MAX + 1) )
}

// FUNCTIONS

static QColor getColor(int value, int maxValue)
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
	int colors[3] = { 0, 0, 0 };
	colors[chunkIndex % 3] = fadeColorValue;
	colors[2 - chunkIndex / 2 % 3] = 0x0;
	colors[(3 - ((chunkIndex + 5) % 6) / 2) % 3] = 0xFF;
	return QColor(colors[0], colors[1], colors[2]);
}

static QColor randomColor()
{
	srand((unsigned)time(NULL));
	return QColor(rand() % 0xFF, rand() % 0xFF, rand() % 0xFF);
}
