#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "QListWidgetItem"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_remove_clicked();

    void on_le_query_editingFinished();

    void on_list_words_itemClicked(QListWidgetItem *item);

    void on_btn_add_clicked();

private:
    Ui::MainWindow *ui;
    Graph g;
    void insertDemo();
    void loadData();
};

#endif // MAINWINDOW_H
