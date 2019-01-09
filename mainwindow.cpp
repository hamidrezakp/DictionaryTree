#include "mainwindow.h"
#include "QInputDialog"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  insertDemo();
  loadData();
  ui->list_words->setAlternatingRowColors(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void
MainWindow::insertDemo()
{
  g.insert("apple", "سیب");
  g.insert("orange", "پرتقال");
  g.insert("iran", "ایران");
  g.insert("tehran", "تهران");
  g.insert("shiraz", "شیراز");
  g.insert("laptop", "لپتاپ");
  g.insert("sound", "صدا");
  g.insert("zoo", "باغ وحش");
  g.insert("city", "شهر");
  g.insert("road", "جاده");
  g.insert("class", "کلاس");
  g.insert("cinama", "سینما");
  g.insert("footbal", "فوتبال");
  g.insert("basketball", "بسکتبال");
  g.insert("swiming", "شنا کردن");
  g.insert("food", "غذا");
  g.insert("drink", "نوشیدنی");
  g.insert("wine", "شراب");
  g.insert("smile", "خندیدن");
  g.insert("table", "میز");
  g.insert("mouse", "موش");
  g.insert("cat", "گربه");
  g.insert("website", "تارنما");
  g.insert("programming", "برنامه نویسی");
  g.insert("work", "کار کردن");
  g.insert("power", "قدرت");
  g.insert("electricity", "الکتریسیته");
  g.insert("keyboard", "صفحه کلید");
  g.insert("green", "سبز");
  g.insert("red", "قرمز");
  g.insert("end", "انتها");
}

void
MainWindow::loadData()
{
  ui->list_words->clear();
  _List words = g.listAll();
  QHashIterator<QString, QString> i(words);
  while (i.hasNext()) {
    i.next();
    ui->list_words->addItem(i.key() + "\t\t" + i.value());
  }
}

void
MainWindow::on_btn_remove_clicked()
{
  g.remove(ui->list_words->currentItem()->text().split("\t\t")[0]);
  loadData();
  ui->lbl_word->setText("Word : ");
  ui->lbl_meaning->setText("Meaning : ");
  ui->btn_remove->setEnabled(false);
  ui->btn_remove->setStyleSheet("color:gray;");
  ui->list_words->setFocus();
}

void
MainWindow::on_le_query_editingFinished()
{
  ui->list_words->clearSelection();
  if (ui->le_query->text().length() == 0) {
    ui->btn_add->setEnabled(false);
    loadData();
    return;
  } else {
    QString meaning = g.search(ui->le_query->text());
    ui->list_words->clear();
    if (meaning.length() != 0) {
      ui->list_words->addItem(ui->le_query->text() + "\t\t" + meaning);
      ui->list_words->setCurrentRow(0);
      on_list_words_itemClicked(ui->list_words->item(0));
      return;
    } else
      ui->btn_add->setEnabled(true);
  }
}

void
MainWindow::on_list_words_itemClicked(QListWidgetItem* item)
{
  ui->lbl_word->setText("Word : " + item->text().split("\t\t")[0]);
  ui->lbl_meaning->setText("Meaning : " + item->text().split("\t\t")[1]);
  ui->btn_remove->setEnabled(true);
  ui->btn_remove->setStyleSheet("color:red;");
}

void
MainWindow::on_btn_add_clicked()
{
  bool ok = false;
  QString value = QInputDialog::getText(this,
                                        "Adding a new word",
                                        ui->le_query->text() + " Meaning : ",
                                        QLineEdit::Normal,
                                        "",
                                        &ok);
  if (ok && !value.isEmpty())
    g.insert(ui->le_query->text(), value);
  loadData();
  ui->le_query->setText("");
  ui->btn_add->setEnabled(false);
}
