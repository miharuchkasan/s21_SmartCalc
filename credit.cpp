#include "credit.h"

#include <QLabel>
#include <QString>

#include "ui_credit.h"

credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  ui->radioButton_ann->setChecked(true);
  connect(ui->pushButton_res_credit, SIGNAL(clicked()), this,
          SLOT(credit_result()));
}

credit::~credit() { delete ui; }

void credit::credit_result() {
  // char* str = new char(ui->res->text().length());
  // char* str = new char(ui->res->text().length());
  // char* str = new char(ui->res->text().length());
  // char* str = new char(ui->res->text().length());

  result res = {0};
  double x_sum, x_percent;
  int x_time;
  int mode = 1;
  if (ui->radioButton_ann->isChecked()) {
    mode = 0;
  }
  x_sum = ui->x_sum->text().toDouble();
  x_time = ui->x_time->text().toDouble();
  x_percent = ui->x_percent->text().toDouble();

  res = credit_res(x_sum, x_time, x_percent, mode);
  //    QString pMax = QString::number(res.monthly_payment_max, 'g', 10);
  //    QString pMin = QString::number(res.monthly_payment_min, 'g', 10);
  //    QString overPay = QString::number(res.overpayment, 'g', 10);
  //    QString allPay = QString::number(res.all_payment, 'g', 10);
  ui->m_pay_max->setText(QString::number(res.monthly_payment_max));
  ui->m_pay_min->setText(QString::number(res.monthly_payment_min));
  ui->overpay->setText(QString::number(res.overpayment));
  ui->all_pay->setText(QString::number(res.all_payment));
  res = {0};
}
