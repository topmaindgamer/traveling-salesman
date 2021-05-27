#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsTextItem>
#include <QTableWidget>
#include <QMessageBox>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::setFixedSize(830,565);
    ui->Bok->hide();
    ui->tableWidget->hide();
    ui->labelT->hide();
    ui->labelZ->hide();
    scene=new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    on_horizontalSlider_sliderMoved(3);
}


MainWindow::~MainWindow()
{
    delete ui;
}


bool reg=0,kf=0;
int result[100],result1[100];
int xx[20],yy[20];;
int minx=600,miny=600;;
int maxx=0,maxy=0;
int ary[100][100], next[100], cost = 0;
int ary2[1000];
int gl_i = 0;
QRandomGenerator *rg=QRandomGenerator::global();


void MainWindow::on_Bmat_clicked()
{

    if (kf)
    {
        scene->clear();
        for(int i=1;i<=ui->label->text().toInt();i++)
        {
            ellipse[i]=scene->addEllipse(xx[i], yy[i], 0, 0,QPen(), QBrush(Qt::SolidPattern));
        }
    }


    int n= ui->label->text().toInt();
    ui->label->hide();
    ui->label_2->hide();
    ui->Bmat->hide();
    ui->Bres->hide();
    ui->Bclear->hide();
    ui->horizontalSlider->hide();
    ui->graphicsView->hide();
    ui->labelT->hide();
    ui->labelZ->hide();
    ui->tableWidget->show();
    ui->Bok->show();
    ui->tableWidget->setFixedSize(n*60+19,n*30+25);
    MainWindow::setFixedSize(n*60+19,n*30+60);
    ui->Bok->move((n*60+19)/2-60,n*30+26);
    ui->tableWidget->setRowCount(n);
    ui->tableWidget->setColumnCount(n);


    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            QTableWidgetItem *a=new QTableWidgetItem(" ");
            ui->tableWidget->setItem(i,j,a);
            if(i==j){
            QTableWidgetItem *null=new QTableWidgetItem("*");
            null->setFlags(null->flags() ^ Qt::ItemIsEditable);
            ui->tableWidget->setItem(i,j,null);}
            ui->tableWidget->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    reg=1;

}


void MainWindow::on_Bok_clicked()
{
    if(matrixcheck()){
    MainWindow::setFixedSize(830,565);
    ui->label->show();
    ui->label_2->show();
    ui->Bmat->show();
    ui->Bres->show();
    ui->Bclear->show();
    ui->horizontalSlider->show();
    ui->graphicsView->show();
    ui->tableWidget->hide();
    ui->Bok->hide();}
    else QMessageBox::warning(this,"error","error");
}


void MainWindow::on_Bclear_clicked()
{
    reg=0;
    int n=ui->label->text().toInt();
    on_horizontalSlider_sliderMoved(n);
}


void MainWindow::on_Bres_clicked()
{
    if(matrixcheck()){
        int n=ui->label->text().toInt();
        int i, j;
        cost = 0;
        gl_i = 0;
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                    if(!(i==j)){
                        QTableWidgetItem *it=ui->tableWidget->item(i,j);
                    ary[i][j]=it->text().toInt();}
                next[i] = 0;
            }
            mincost(0); //passing 0 because starting vertex
            for (int i = 0; i <n; i++)
            {
                result[i] = ary2[i];
                result1[i] = ary2[i + 1];
            }
           ui->labelT->show();
           ui->labelZ->show();
           ui->labelZ->setText(QString::number(cost));
           pic();
           memset(ary, 0, sizeof ary);
           memset(next, 0, sizeof next);
           memset(ary2,0,sizeof ary2);
    }
    else QMessageBox::warning(this,"error","error");
}


void MainWindow::on_horizontalSlider_sliderMoved(int position)
{

    ui->label->setText(QString::number(position));
    scene->clear();
    for(int i=0;i<position;i++)
    {
        xx[i]=rg->bounded(10,500);
        yy[i]=200*i/4;
        if(xx[i]<minx) minx=xx[i];
        if(xx[i]>maxx) maxx=xx[i];
        if(yy[i]<miny) miny=yy[i];
        if(yy[i]>maxy) maxy=yy[i];
    }
    for(int i=1;i<=position;i++)
    {
        ellipse[i]=scene->addEllipse(xx[i], yy[i], 0, 0,QPen(), QBrush(Qt::SolidPattern));
    }
    reg=0;
    ui->labelT->hide();
    ui->labelZ->hide();

}


void MainWindow::pic()
{
    reg=1;
    int n=ui->label->text().toInt();
    QPen qline;qline.setColor(Qt::black);qline.setWidth(1);
    QFont font;font.setPixelSize(12); font.setBold(1);
    for(int i=0;i<n;i++)
    {
        lines
        (ellipse[result[i]]->rect().x()+4,
        ellipse[result[i]]->rect().y()+4,
        ellipse[result1[i]]->rect().x()+4,
        ellipse[result1[i]]->rect().y()+4);

        int textx=(ellipse[result[i]]->rect().x()+ellipse[result1[i]]->rect().x())/2;
        int texty=(ellipse[result[i]]->rect().y()+ellipse[result1[i]]->rect().y())/2;
        QTableWidgetItem *it=ui->tableWidget->item(result[i]-1,result1[i]-1);
        QGraphicsTextItem *text=scene->addText(it->text());
        text->setFont(font);
        text->setPos(textx,texty-7);

    }
    for(int i=1;i<=n;i++)
    {
        ellipse[i]=scene->addEllipse(xx[i], yy[i], 4, 4,QPen(), QBrush(Qt::SolidPattern));
    }
    kf=1;
}


void MainWindow::lines(int x1,int y1,int x2, int y2)
{
       QPen line;
       line.setColor(QColor(100,200,100));
       line.setWidth(2);

       QPen arr;
       arr.setColor(QColor(0,0,0));
       arr.setWidth(1);
       linea=scene->addLine(x1, y1, x2, y2,line);
}


bool MainWindow::matrixcheck()
{
    if(reg){
    int n=ui->label->text().toInt();
    for(int i=0;i<n;i++)
       for(int j=0;j<n;j++)
       {
           if(!(i==j))
           {
            QTableWidgetItem *it=ui->tableWidget->item(i,j);
           if(it->text()==" "||it->text().toInt()<=0) return 0;
           }
       }
    return 1;
    } else return 0;
}


int MainWindow::least(int c)
{
    int i, nc = 999;
    int min = 999, kmin;
    int n=ui->label->text().toInt();
    for (i = 0; i < n; i++)
    {
        if ((ary[c][i] != 0) && (next[i] == 0))
            if (ary[c][i] + ary[i][c] < min)
            {
                min = ary[i][0] + ary[c][i];
                kmin = ary[c][i];
                nc = i;
            }
    }

    if (min != 999)
        cost += kmin;

    return nc;
}


void MainWindow::mincost(int city)
{
    int ncity;

    next[city] = 1;
    ary2[gl_i] = city + 1;
    gl_i++;
    ncity = least(city);

    if (ncity == 999)
    {
        ncity = 0;
        ary2[gl_i] = ncity + 1;
        gl_i++;
        cost += ary[city][ncity];

        return;
    }
    mincost(ncity);
}
