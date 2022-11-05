// main.cpp

#pragma warning(push, 1) // disable warnings for third party headers
#include <QApplication>
#pragma warning(pop)

#include "window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Window window;
	window.show();
	return app.exec();
}
