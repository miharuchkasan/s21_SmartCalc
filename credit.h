#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

extern "C" {
#include "s21_calc.h"
}

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

private:
  Ui::credit *ui;
private slots:
  void credit_result();
};

#endif // CREDIT_H
