#include "deposit_input.h"

#include "ui_deposit_input.h"

deposit_input::deposit_input(QWidget* parent)
    : QDialog(parent), ui(new Ui::deposit_input) {
  ui->setupUi(this);
}

deposit_input::~deposit_input() { delete ui; }

void deposit_input::on_pushButton_save_clicked() {
  bool correct = 1;
  QTableWidgetItem* cell;
  s21::pay pay;
  s21::date dt;
  double amnt;
  static QRegularExpression re("^(\\d\\d)\\.(\\d\\d)\\.(\\d\\d\\d\\d)$");
  QRegularExpressionMatch match;
  //    Node* pays_head = NULL;
  std::list<s21::pay> pays;
  for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
    cell = ui->tableWidget->item(i, 0);
    if (cell) {
      match = re.match(cell->text());
      if (match.hasMatch()) {
        dt.day = match.captured(1).toInt();
        dt.month = match.captured(2).toInt();
        dt.year = match.captured(3).toInt();

        if (date_is_correct(dt)) {
          pay.dt = dt;
        } else {
          correct = 0;
        }
      } else {
        correct = 0;
      }
    } else {
      correct = 0;
    }

    cell = ui->tableWidget->item(i, 1);
    if (correct && cell) {
      amnt = cell->text().toDouble(&correct);
      if (correct && amnt > 0) {
        pay.amount = amnt;
      } else {
        correct = 0;
      }
    } else {
      correct = 0;
    }

    if (correct) {
      pays.push_back(pay);
      //            pays_push(&pays_head,pay);
    }
  }
  if (correct) {
    emit send_paylist(pays);
    //        emit send_paylist(pays_head);
    this->close();
  } else {
    QMessageBox::critical(this, "Error message",
                          "Invalid input! Data cannot be saved!");
  }
}

void deposit_input::on_pushButton_del_clicked() {
  int current_row = ui->tableWidget->currentRow();
  if (current_row) {
    ui->tableWidget->removeRow(current_row);
  } else
    (ui->tableWidget->removeRow(ui->tableWidget->rowCount() - 1));
}

void deposit_input::on_pushButton_add_clicked() {
  ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}
