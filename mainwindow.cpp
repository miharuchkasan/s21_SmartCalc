#include "mainwindow.h"

#include <QLabel>
#include <QString>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->widget->xAxis->setRange(-20, 20);
  ui->widget->yAxis->setRange(-20, 20);
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);

  connect(ui->pushButton0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_Clear, SIGNAL(clicked()), this, SLOT(del()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(x_symbol()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digit_dot()));
  connect(ui->pushButton_graph, SIGNAL(clicked()), this, SLOT(graph_res()));
  connect(ui->pushButton_leftskobka, SIGNAL(clicked()), this,
          SLOT(all_operations()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_percent, SIGNAL(clicked()), this,
          SLOT(all_operations())); // unari
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(all_operations()));
  // connect(ui->pushButton_plusmin, SIGNAL(clicked()),this,
  // SLOT(digit_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(digit_numbers()));
  connect(ui->pushButton_rightsckobka, SIGNAL(clicked()), this,
          SLOT(all_operations()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digit_numbers()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_result, SIGNAL(clicked()), this, SLOT(digit_result()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(all_operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(all_operations()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_str = ui->res->text() + button->text();
  ui->res->setText(new_str);
}

void MainWindow::digit_dot() {
  if (!(ui->res->text().endsWith('.')))
    ui->res->setText(ui->res->text() + ".");
}

void MainWindow::all_operations() {
  QPushButton *button = (QPushButton *)sender();

  QString new_label;

  new_label = ui->res->text();

  if (button->text() == "/" && !(ui->res->text().endsWith("÷")) &&
      !(ui->res->text().endsWith("/"))) {
    new_label += "/";
  } else if (button->text() == "*" && !(ui->res->text().endsWith("*"))) {
    new_label += "*";
  } else if (button->text() == "+" && !(ui->res->text().endsWith("+"))) {
    new_label += "+";
  } else if (button->text() == "-" && !(ui->res->text().endsWith("-"))) {
    new_label += "-";
  } else if (button->text() == "^" && !(ui->res->text().endsWith("^"))) {
    new_label += "^";
  } else if (button->text() == "mod" && !(ui->res->text().endsWith("mod"))) {
    new_label += "mod";
  } else if (button->text() == "(") {
    new_label += "(";
  } else if (button->text() == ")") {
    new_label += ")";
  } else if (button->text() == "sin" && !(ui->res->text().endsWith("sin"))) {
    new_label += "sin";
  } else if (button->text() == "cos" && !(ui->res->text().endsWith("cos"))) {
    new_label += "cos";
  } else if (button->text() == "tan" && !(ui->res->text().endsWith("tan"))) {
    new_label += "tan";
  } else if (button->text() == "log" && !(ui->res->text().endsWith("log"))) {
    new_label += "log";
  } else if (button->text() == "asin" && !(ui->res->text().endsWith("asin"))) {
    new_label += "asin";
  } else if (button->text() == "acos" && !(ui->res->text().endsWith("acos"))) {
    new_label += "acos";
  } else if (button->text() == "atan" && !(ui->res->text().endsWith("atan"))) {
    new_label += "atan";
  } else if (button->text() == "ln" && !(ui->res->text().endsWith("ln"))) {
    new_label += "ln";
  } else if (button->text() == "+/-") {
    new_label += "*(-1)";
  }

  ui->res->setText(new_label);
}

void MainWindow::digit_result() {
  QVector<double> x, y;
  char str[512] = {0};
  QByteArray barr = ui->res->text().toLocal8Bit().constData();
  s21_strlcpy(str, barr, 255);
  int check = string_check(str);
  if (strlen(str) < 3) {
    ui->res->setText("Empty line");
  } else if (check == 1) {
    ui->res->setText("Invalid Input");
  } else if (check == 2) {
    ui->res->setText("Press 'graph' to work with 'X'");
  } else {
    element *stack = NULL;
    element *resultat = NULL;
    s21_parcer(str, &stack);
    reverse_stack(&stack, &resultat);
    double result = r_polish_notation(&resultat);

    QString numberResult = QString::number(result, 'g', 10);
    ui->res->setText(numberResult);
    //        if(str) delete(str);
    free(stack);
    free(resultat);
    free_stack(stack);
    free_stack(resultat);
  }
  //    delete(str);
}

void MainWindow::graph_res() {
  double x_min, x_max, x_step;

  x_min = ui->x_min->text().toDouble();
  x_max = ui->x_max->text().toDouble();
  x_step = ui->x_step->text().toDouble();

  QVector<double> x, y;
  char str[512] = {0};
  QByteArray barr = ui->res->text().toLocal8Bit().constData();
  s21_strlcpy(str, barr, 255);
  ui->res->clear();
  if (string_check(str) == 2) {
    element *stack = NULL;
    element *resultat = NULL;
    if (!x_min || !x_max || !x_step) {
      x_min = -12;
      x_max = 12;
      x_step = 0.5;
    }
    double X = x_min;
    while (X <= x_max) {
      x.push_back(X);

      s21_parcer(str, &stack);
      set_x_value(X, stack);
      reverse_stack(&stack, &resultat);
      y.push_back(r_polish_notation(&resultat));

      X += x_step;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
    free_stack(stack);
    free_stack(resultat);
  }
}

void MainWindow::del() {
  ui->res->setText("");
  ui->res->clear();
  ui->x_min->clear();
  ui->x_max->clear();
  ui->x_step->clear();
  for (int g = 0; g < ui->widget->graphCount(); g++) {
    ui->widget->graph(g)->data().data()->clear();
  }
  ui->widget->replot();
  ui->widget->xAxis->setRange(-20, 20);
  ui->widget->yAxis->setRange(-20, 20);
}

void MainWindow::x_symbol() {
  QString new_label;

  if (!(ui->res->text().endsWith("x")))
    new_label = ui->res->text() + "x";

  ui->res->setText(new_label);
}

void MainWindow::on_pushButton_clicked() { Credit.show(); }
