#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calculadora");

    //Establecer el mismo metodo (canal o slot) para los botones 0-9
    connect(ui->btn0,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn1,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn2,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn3,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn4,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn5,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn6,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn7,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn8,SIGNAL(released()),this,SLOT(Presionar_numero()));
    connect(ui->btn9,SIGNAL(released()),this,SLOT(Presionar_numero()));

    //Establecer el mismo metodo (canal o slot) para los botones de operación (+-x/)
    connect(ui->btnMas,SIGNAL(released()),this,SLOT(Presionar_boton_operacion()));
    connect(ui->btnResta,SIGNAL(released()),this,SLOT(Presionar_boton_operacion()));
    connect(ui->btnMultiplicacion,SIGNAL(released()),this,SLOT(Presionar_boton_operacion()));
    connect(ui->btnDividir,SIGNAL(released()),this,SLOT(Presionar_boton_operacion()));


    //Esta propiedad (setCheckable) permite que los botones sean verificables
    ui->btnMas->setCheckable(true);
    ui->btnResta->setCheckable(true);
    ui->btnMultiplicacion->setCheckable(true);
    ui->btnDividir->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Un numero es presionado
void MainWindow::Presionar_numero()
{
    //Aqui se construye el objeto boton del digito presionado (0-9)
    QPushButton * boton = (QPushButton*)sender();

    double lblNum;
    QString lblNuevonum;

    //NUMERO A MOSTRAR EN PANTALLA:

    //Si es el primer digito presionado
    if(
        (ui->btnMas->isChecked() ||
        ui->btnResta->isChecked() ||
        ui->btnMultiplicacion->isChecked() ||
        ui->btnDividir->isChecked())
        && (!CadNums))
    {        
        lblNum = boton->text().toDouble();
        CadNums = true;
        lblNuevonum = QString::number(lblNum,'g',15);
    }
    //Si hay más de un digito siempre entra aqui
    else
    {
        //Si se esta escribiendo un número decimal
        if(
            ui->lblResultado->text().contains('.')
            && boton->text() == "0")
        {
            lblNuevonum = ui->lblResultado->text() + boton->text();

        }
        else
        {
            lblNum = (ui->lblResultado->text() + boton->text()).toDouble();
            lblNuevonum = QString::number(lblNum,'g',15);
        }
    }

    //Mostrar número escrito
    ui ->lblResultado->setText(lblNuevonum);
}


//Agregar punto decimal
void MainWindow::on_btnPunto_released()
{
    //Valida que solo se use un punto
    if (!(ui->lblResultado->text().contains('.')))
    {
        ui->lblResultado->setText(ui->lblResultado->text() + ".");
    }
}


//Guardar operacion a ejecutar y guardar primer número
void MainWindow::Presionar_boton_operacion()
{
    //Aqui se construye el objeto boton del digito presionado (+-x/)
    QPushButton *boton = (QPushButton*)sender();
    Num1 = ui->lblResultado->text().toDouble();
    boton->setChecked(true);
}

//Igual
void MainWindow::on_btnIgual_released()
{
    double lblNum, Num2;
    QString lblNuevonum;

    //Obtener segundo número
    Num2 = ui->lblResultado->text().toDouble();

    //Validar si es suma
    if(ui->btnMas->isChecked())
    {
        lblNum = Num1 + Num2;
        lblNuevonum = QString::number(lblNum,'g',15);
        ui->lblResultado->setText(lblNuevonum);
        ui->btnMas->setChecked(false);
    }
    //Validar si es una resta
    else if (ui->btnResta->isChecked())
    {
        lblNum = Num1 - Num2;
        lblNuevonum = QString::number(lblNum,'g',15);
        ui->lblResultado->setText(lblNuevonum);
        ui->btnResta->setChecked(false);
    }
    //Validar si es una multiplicación
    else if (ui->btnMultiplicacion->isChecked())
    {
        lblNum = Num1 * Num2;
        lblNuevonum = QString::number(lblNum,'g',15);
        ui->lblResultado->setText(lblNuevonum);
        ui->btnMultiplicacion->setChecked(false);

    }
    //Valida si es una división
    else if (ui->btnDividir->isChecked())
    {
        //Validar si es una división por cero
        if(Num2 == 0)
        {
            ui->lblResultado->setText("Math ERROR");
        }
        else
        {
            lblNum = Num1 / Num2;
            lblNuevonum = QString::number(lblNum,'g',15);
            ui->lblResultado->setText(lblNuevonum);
            ui->btnDividir->setChecked(false);
        }
    }
    CadNums = false;
}


//Poner el signo negativo
void MainWindow::on_btnMasMenos_clicked()
{
    double lblNum;
    QString lblNuevonum;

    lblNum = ui->lblResultado->text().toDouble();
    lblNum = lblNum * -1;
    lblNuevonum = QString::number(lblNum,'g',15);
    ui->lblResultado->setText(lblNuevonum);
}

//Reiniciar calculadora
void MainWindow::on_btnBorrar_released()
{
    ui->btnMas->setChecked(false);
    ui->btnResta->setChecked(false);
    ui->btnMultiplicacion->setChecked(false);
    ui->btnDividir->setChecked(false);

    CadNums = false;
    ui->lblResultado->setText("0");
}

