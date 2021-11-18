// main.cpp

#include <QApplication>
#include <iostream>
#include "window.h"


int main(int argc, char **argv)
{
  std::cout << "Hello World!\n";
  QApplication app(argc, argv);

  Window window;
  window.show();

  return app.exec();
}