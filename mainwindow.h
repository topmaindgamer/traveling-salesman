#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool matrixcheck();
    void pic();
    void lines(int x1,int y1,int x2, int y2);
    int least(int c);
    void mincost(int city);
private slots:

    void on_horizontalSlider_sliderMoved(int position);

    void on_Bmat_clicked();

    void on_Bok_clicked();

    void on_Bres_clicked();

    void on_Bclear_clicked();



private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse[20];
    QGraphicsItem *linea;
};
#endif // MAINWINDOW_H
