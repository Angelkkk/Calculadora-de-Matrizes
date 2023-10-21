#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //validação de inteiros

    validator = new QIntValidator(-9,9,this);
    ui->lineEdit_linhasA->setValidator(validator);
    ui->lineEdit_colunasA->setValidator(validator);
    ui->lineEdit_linhasB->setValidator(validator);
    ui->lineEdit_colunasB->setValidator(validator);
    ui->lineEdit_pot->setValidator(validator);
    ui->lineEdit_multint->setValidator(validator);

    //stylesheet

    setStyleSheet("QMainWindow{ background-color: #121f2d; }"
                  "QMessageBox{}"
                  "QInputDialog{}");

    //pixmaps

    QPixmap code(":/imgs/img/code.png");
   ui->label_code->setPixmap(code.scaled(31,31,Qt::KeepAspectRatio,Qt::SmoothTransformation));
   ui->label_code_4->setPixmap(code.scaled(31,31,Qt::KeepAspectRatio,Qt::SmoothTransformation));
   ui->label_code_6->setPixmap(code.scaled(31,31,Qt::KeepAspectRatio,Qt::SmoothTransformation));

   //align
   ui->lineEdit_linhasA->setAlignment(Qt::AlignRight);
   ui->lineEdit_colunasA->setAlignment(Qt::AlignRight);
   ui->lineEdit_linhasB->setAlignment(Qt::AlignRight);
   ui->lineEdit_colunasB->setAlignment(Qt::AlignRight);
   ui->lineEdit_pot->setAlignment(Qt::AlignCenter);
   ui->lineEdit_multint->setAlignment(Qt::AlignCenter);

   //icones

   QIcon save(":/imgs/img/save.png");
   ui->pushButton_criarA->setIcon(save);
   ui->pushButton_criarB->setIcon(save);
   QIcon soma(":/imgs/img/soma.png");
   ui->pushButton_soma->setIcon(soma);
   QIcon menos(":/imgs/img/menos.png");
   ui->pushButton_subtracao->setIcon(menos);
   QIcon mult(":/imgs/img/mult.png");
   ui->pushButton_multint->setIcon(mult);
   ui->pushButton_multiplicacao->setIcon(mult);
   QIcon up(":/imgs/img/up.png");
   ui->pushButton_TS->setIcon(up);
   QIcon down(":/imgs/img/down.png");
   ui->pushButton_TI->setIcon(down);
   QIcon simetrico(":/imgs/img/simetrico.png");
   ui->pushButton_simetrico->setIcon(simetrico);
   QIcon transposta(":/imgs/img/transposta.png");
   ui->pushButton_transposta->setIcon(transposta);
   QIcon identidade(":/imgs/img/identidade.png");
   ui->pushButton_identidade->setIcon(identidade);
   QIcon potencia(":/imgs/img/potencia.png");
   ui->pushButton_pot->setIcon(potencia);
   QIcon igual(":/imgs/img/igual.png");
   ui->pushButton_igual->setIcon(igual);
   QIcon diff(":/imgs/img/diff.png");
   ui->pushButton_diff->setIcon(diff);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete matA;
    delete matB;
    delete validator;
}


void MainWindow::on_pushButton_criarA_clicked()
{
    try {
        int LinhasA = ui->lineEdit_linhasA->text().toInt();
        int ColunasA = ui->lineEdit_colunasA->text().toInt();
        matA = new ams::Matriz(LinhasA,ColunasA);
        for(int linhas=0; linhas < matA->getLinhas(); linhas++){
            for(int colunas=0; colunas < matA->getColunas(); colunas++){
                QString aux = "Matriz A["+QString::number(linhas)+"]["+QString::number(colunas)+"]:";
                int valor = QInputDialog::getInt(this,"Matriz", aux);
                matA->setElemento(linhas, colunas, valor);
            }
        }
        ui->textEdit_matrizA->clear();
        QString saida = "Matriz A: \n" + QString::fromStdString(matA->getMatriz());
            ui->textEdit_matrizA->setAlignment(Qt::AlignCenter);
        ui->textEdit_matrizA->append(saida);

    } catch (std::bad_alloc &) {
        QMessageBox::information(this, "ERRO","memoria insuficiente");
    }
    catch (std::string msg) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(msg));
    }
}



void MainWindow::on_pushButton_criarB_clicked()
{
    try {
        int LinhasB = ui->lineEdit_linhasB->text().toInt();
        int ColunasB = ui->lineEdit_colunasB->text().toInt();
        matB = new ams::Matriz(LinhasB,ColunasB);
        for(int linhas=0; linhas < matB->getLinhas(); linhas++){
            for(int colunas=0; colunas < matB->getColunas(); colunas++){
                QString aux = "Matriz A["+QString::number(linhas)+"]["+QString::number(colunas)+"]:";
                int valor = QInputDialog::getInt(this,"Matriz", aux);
                matB->setElemento(linhas, colunas, valor);
            }
        }
        ui->textEdit_matrizB->clear();
        QString saida = "Matriz B: \n" + QString::fromStdString(matB->getMatriz());
            ui->textEdit_matrizB->setAlignment(Qt::AlignCenter);
        ui->textEdit_matrizB->append(saida);

    } catch (std::bad_alloc &) {
        QMessageBox::information(this, "ERRO","memoria insuficiente");
    }
    catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}



void MainWindow::on_pushButton_soma_clicked()
{

        try {
            if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada. Não foi possível realizar a soma.");
            ams::Matriz mataux = *matA + *matB;
            QString saida = "Matriz Resultante: \n" + QString::fromStdString(mataux.getMatriz());
            ui->textEdit->clear();
            ui->textEdit->setAlignment(Qt::AlignCenter);
            ui->textEdit->append(saida);
        } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}

void MainWindow::on_pushButton_subtracao_clicked()
{
        ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada. Não foi possível realizar a subtração.");
        ams::Matriz mataux = *matA - *matB;
        QString saida = "Matriz Resultante: \n" + QString::fromStdString(mataux.getMatriz());
        ui->textEdit->setAlignment(Qt::AlignCenter);

    ui->textEdit->append(saida);
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_multiplicacao_clicked()
{
    ui->textEdit->clear();
try {
    if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada. Não foi possível realizar a multiplicação.");
    ams::Matriz mataux = *matA * *matB;
    QString saida = "Matriz Resultante: \n" + QString::fromStdString(mataux.getMatriz());
    ui->textEdit->setAlignment(Qt::AlignCenter);

ui->textEdit->append(saida);
} catch (std::string erro) {
    QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
}
}

void MainWindow::on_pushButton_TS_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if (matA->TriangularSuperior()) ui->textEdit->append("▲ A matriz A é Triangular Superior");
        else ui->textEdit->append("✖ A matriz A NÃO é Triangular Superior");
        if (matB->TriangularSuperior()) ui->textEdit->append("▲ A matriz B é Triangular Superior");
        else ui->textEdit->append("✖ A matriz B NÃO é Triangular Superior");
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_TI_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if (matA->TriangularInferior()) ui->textEdit->append("▼ A matriz A é Triangular Inferior");
        else ui->textEdit->append("✖ A matriz A NÃO é Triangular Inferior");
        if (matB->TriangularInferior()) ui->textEdit->append("▼ A matriz B é Triangular Inferior");
        else ui->textEdit->append("✖ A matriz B NÃO é Triangular Inferior");
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_simetrico_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if (matA->Simetrica()) ui->textEdit->append("⇅ A matriz A é Simétrica");
        else ui->textEdit->append("✖ A matriz A NÃO é Simétrica");
        if (matB->Simetrica()) ui->textEdit->append("⇅ A matriz B é Simétrica");
        else ui->textEdit->append("✖ A matriz B NÃO é Simétrica");
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_transposta_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        QString saida = 0;
        saida += "Matriz A transposta: \n" + QString::fromStdString(matA->calcularTransposta().getMatriz());
        saida += "\nMatriz B transposta: \n" + QString::fromStdString(matB->calcularTransposta().getMatriz());
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(saida);
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_identidade_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if (matA->Identidade()) ui->textEdit->append("➀ A matriz A é Identidade");
        else ui->textEdit->append("✖ A matriz A NÃO é Identidade");
        if (matB->Identidade()) ui->textEdit->append("➀ A matriz B é Identidade");
        else ui->textEdit->append("✖ A matriz B NÃO é Identidade");
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_pot_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if(ui->lineEdit_pot->text().isEmpty()) throw std::string("Insira um valor para a potenciação");
        ams::Matriz matAuxA = *matA^ui->lineEdit_pot->text().toInt();
        ams::Matriz matAuxB = *matB^ui->lineEdit_pot->text().toInt();
        QString saida = "";
        saida += "Matriz A elevado a " + ui->lineEdit_pot->text() + ":\n" + QString::fromStdString(matAuxA.getMatriz());
        saida += "Matriz B elevado a " + ui->lineEdit_pot->text() + ":\n" + QString::fromStdString(matAuxB.getMatriz());
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(saida);
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_multint_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        if(ui->lineEdit_multint->text().isEmpty()) throw std::string("Insira um valor para a multiplicação");
        ams::Matriz matAuxA = *matA*ui->lineEdit_multint->text().toInt();
        ams::Matriz matAuxB = *matB*ui->lineEdit_multint->text().toInt();
        QString saida = "";
        saida += "Matriz A multiplicada por " + ui->lineEdit_multint->text() + ":\n" + QString::fromStdString(matAuxA.getMatriz());
        saida += "Matriz B multiplicada por " + ui->lineEdit_multint->text() + ":\n" + QString::fromStdString(matAuxB.getMatriz());
        ui->textEdit->setAlignment(Qt::AlignCenter);
        ui->textEdit->append(saida);
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_igual_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        ui->textEdit->setText(QString::fromStdString(*matA == *matB));
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}


void MainWindow::on_pushButton_diff_clicked()
{
    ui->textEdit->clear();
    try {
        if (ui->textEdit_matrizA->document()->isEmpty() || ui->textEdit_matrizB->document()->isEmpty()) throw std::string("Uma das matrizes não foi criada.");
        ui->textEdit->setText(QString::fromStdString(*matA != *matB));
    } catch (std::string erro) {
        QMessageBox::information(this, "ERRO", QString::fromStdString(erro));
    }
}

