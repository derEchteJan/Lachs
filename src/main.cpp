// main.cpp

#include <QApplication>
#include <QPushButton>
#include <iostream>

int main(int argc, char **argv)
{
  std::cout << "Hello World!\n";
  QApplication app(argc, argv);
  
  QPushButton button;
  button.setText("My text");
  button.setToolTip("A tooltip");
  button.show();

  return app.exec();
}