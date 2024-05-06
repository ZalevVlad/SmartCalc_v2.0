#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->groupBox_functions->setVisible(false);
  connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this,
          SLOT(on_buttonGroup_clicked(QAbstractButton*)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_expand_clicked() {
  ui->groupBox_functions->setVisible(!ui->groupBox_functions->isVisible());
}

void output_add_line(QString line, QTextBrowser* text) {
  text->insertPlainText(line);
  text->setTextCursor(text->textCursor());
}

void MainWindow::on_pushButton_equal_clicked() {
  double x = 0;
  bool x_input_ok;
  x = ui->textEdit_x_input->toPlainText().toDouble(&x_input_ok);

  try {
    double num = controller.calculate(ui->calc_input->text().toStdString(), x);
    if (std::isfinite(x)) {
      output_add_line(ui->calc_input->text(), ui->textBrowser);
      output_add_line(" = ", ui->textBrowser);
      output_add_line(QString::number(num, 'g', 7) + '\n', ui->textBrowser);
    } else {
      throw std::runtime_error("Wrong expression");
    }
  } catch (std::exception& e) {
    output_add_line(QString("Wrong expression\n"), ui->textBrowser);
  }
}

void MainWindow::on_actionGraphic_triggered() {
  ui->stackedWidget->setCurrentWidget(ui->page);
  ui->stackedWidget_3->setCurrentWidget(ui->page_5);
  ui->stackedWidget_4->setCurrentWidget(ui->page_8);
}

void MainWindow::on_actionBase_triggered() {
  ui->stackedWidget->setCurrentWidget(ui->page);
  ui->stackedWidget_3->setCurrentWidget(ui->page_4);
  ui->stackedWidget_4->setCurrentWidget(ui->page_7);
}

void MainWindow::on_actionCredit_triggered() {
  ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void MainWindow::on_actionDeposit_triggered() {
  ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void MainWindow::on_buttonGroup_clicked(QAbstractButton* btn) {
  ui->calc_input->setText(ui->calc_input->text() + btn->text());
}

#define LIMITS_ARE_FINITE 4
void MainWindow::on_pushButton_plot_clicked() {
  ui->label_graph_err_out->setText("");
  bool limits_ok;
  int count = 0;
  double xMin = ui->lineEdit_xMin->text().toDouble(&limits_ok);
  count += limits_ok;
  double xMax = ui->lineEdit_xMax->text().toDouble(&limits_ok);
  count += limits_ok;
  double yMin = ui->lineEdit_yMin->text().toDouble(&limits_ok);
  count += limits_ok;
  double yMax = ui->lineEdit_yMax->text().toDouble(&limits_ok);
  count += limits_ok;
  if (count == LIMITS_ARE_FINITE && xMin < xMax && yMin < yMax) {
    int xPixels = ui->axes->size().width(), yPixels = ui->axes->size().height();
    double deltax = (xMax - xMin) / xPixels;
    std::vector<double> stdx, stdy;
    try {
      controller.calculate_vec(ui->calc_input->text().toStdString(), xMin, xMax,
                               xPixels, stdx, stdy);
      QVector<double> x = QVector<double>::fromStdVector(stdx);
      QVector<double> y = QVector<double>::fromStdVector(stdy);
      ui->axes->addGraph();
      ui->axes->graph(0)->setData(x, y, true);
      ui->axes->xAxis->setRange(xMin, xMax);
      ui->axes->yAxis->setRange(yMin, yMax);
      ui->axes->replot();
    } catch (std::exception& e) {
      ui->label_graph_err_out->setText("Wrong expresion");
    }
  } else {
    ui->label_graph_err_out->setText("Wrong limits");
  }
}

void MainWindow::on_pushButton_delete_clicked() { ui->calc_input->setText(""); }

void MainWindow::on_pushButton_15_clicked() {
  deposit_input_ui.setModal(true);
  connect(&deposit_input_ui, &deposit_input::send_paylist, this,
          &MainWindow::recieve_deposits);
  deposit_input_ui.exec();
}

void MainWindow::on_pushButton_16_clicked() {
  withdrawals_input_ui.setModal(true);
  connect(&withdrawals_input_ui, &withdrawals_input::send_paylist, this,
          &MainWindow::recieve_withdrawals);
  withdrawals_input_ui.exec();
}

void MainWindow::recieve_deposits(std::list<s21::pay>& deposits_list) {
  this->deposits_list = deposits_list;
}

void MainWindow::recieve_withdrawals(std::list<s21::pay>& withdrawals_list) {
  this->withdrawals_list = withdrawals_list;
}

int get_period_type(const QString& str) {
  int res = 0;
  if (str == "лет") {
    res = s21::YEARS;
  } else if (str == "месяцев") {
    res = s21::MONTHS;
  } else if (str == "дней") {
    res = s21::DAYS;
  }
  return res;
}

int get_payments_periodicity_type(const QString& str) {
  int res = 0;
  if (str == "раз в год") {
    res = s21::YEARS;
  } else if (str == "раз в месяц") {
    res = s21::MONTHS;
  } else if (str == "каждый день") {
    res = s21::DAYS;
  } else if (str == "в конце срока") {
    res = s21::ONCE;
  }
  return res;
}

void MainWindow::on_pushButton_calc_deposit_clicked() {
  s21::date start = {.day = ui->dateEdit->date().day(),
                     .month = ui->dateEdit->date().month(),
                     .year = ui->dateEdit->date().year()};
  double deposit_amount = ui->doubleSpinBox_3->value();
  int period = ui->spinBox->value();
  int period_type = get_period_type(ui->comboBox_3->currentText());
  double interest_rate = ui->spinBox_3->value();
  double tax_rate = ui->spinBox_4->value();
  int payments_periodicity = 1;
  int payments_periodicity_type =
      get_payments_periodicity_type(ui->comboBox_4->currentText());
  int interest_capitalization = ui->radioButton->isChecked();

  s21::deposit deposit;
  try {
    controller.deposit_calc(start, deposit_amount, period, period_type,
                            interest_rate, tax_rate, payments_periodicity,
                            payments_periodicity_type, interest_capitalization,
                            deposits_list, withdrawals_list, deposit);
    ui->label_accured_interest->setText(
        QString::number(deposit.accrued_interest, 'f', 2));
    ui->label_tax_amount->setText(QString::number(deposit.tax_amount, 'f', 2));
    ui->label_final_amount->setText(
        QString::number(deposit.final_amount, 'f', 2));
  } catch (std::exception& e) {
    QMessageBox::critical(this, "Error message", "Error!");
  }
}

void MainWindow::on_pushButton_calc_credit_clicked() {
  double credit_amount = ui->doubleSpinBox_credit_amount->value();
  int months = 0;
  if (ui->comboBox->currentText() == "лет") {
    months = ui->spinBox_credit_term->value() * 12;
  } else if (ui->comboBox->currentText() == "месяцев") {
    months = ui->spinBox_credit_term->value();
  }
  double interest_rate = ui->doubleSpinBox_interest_rate->value();
  s21::date dt = s21::get_date();
  dt.day = 1;
  s21::credit_pays credit_pays;

  int err = 0;
  if (ui->comboBox_payments_type->currentText() == "Аннуитентные") {
    controller.annuity_payment_calc(credit_amount, months, interest_rate,
                                    credit_pays);
  } else if (ui->comboBox_payments_type->currentText() ==
             "Дифференцированные") {
    controller.differentiated_credit_calc(credit_amount, months, interest_rate,
                                          &dt, credit_pays);
  }

  if (!err) {
    ui->tableWidget->setRowCount(0);
    QString buf;
    QTableWidgetItem* item;

    for (int i = 0; i < credit_pays.pays_count; i++) {
      ui->tableWidget->insertRow(ui->tableWidget->rowCount());

      buf.sprintf("%d.%d.%d", dt.day, dt.month, dt.year);
      item = new QTableWidgetItem;
      item->setText(buf);
      ui->tableWidget->setItem(i, 0, item);

      buf.sprintf("%.2f", credit_pays.pays[i]);
      item = new QTableWidgetItem;
      item->setText(buf);
      ui->tableWidget->setItem(i, 1, item);
      dt = add_months(dt, 1);
    }
  } else {
    QMessageBox::critical(this, "Error message", "Invalid input!");
  }
}
