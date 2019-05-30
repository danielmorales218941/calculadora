#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double Num1;
    bool CadNums = false;

private slots:
    void Presionar_numero();
    void on_btnPunto_released();
    void on_btnBorrar_released();
    void on_btnIgual_released();
    void Presionar_boton_operacion();
    void on_btnMasMenos_clicked();
};

#endif // MAINWINDOW_H
