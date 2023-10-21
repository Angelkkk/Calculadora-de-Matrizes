#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <matriz.h>
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QPixmap>
#include <QIcon>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_criarA_clicked();

    void on_pushButton_criarB_clicked();

    void on_pushButton_soma_clicked();

    void on_pushButton_subtracao_clicked();

    void on_pushButton_multiplicacao_clicked();

    void on_pushButton_TS_clicked();

    void on_pushButton_TI_clicked();

    void on_pushButton_simetrico_clicked();

    void on_pushButton_transposta_clicked();

    void on_pushButton_identidade_clicked();

    void on_pushButton_pot_clicked();

    void on_pushButton_multint_clicked();

    void on_pushButton_igual_clicked();

    void on_pushButton_diff_clicked();

private:
    Ui::MainWindow *ui;
    ams::Matriz *matA, *matB;
    QValidator *validator;
};
#endif // MAINWINDOW_H
