#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectImg(QListWidgetItem*)));    
    m_database.init(ImageDatabaseFile);//初始化图片数据库
    getAllImg();
    inDatabase = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getAllImg()
{
    QFile file(ImageList);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "载入图片名"<<ImageList<<"打开失败!";
        return ;
    }

    ui->listWidget->clear();
    QTextStream in(&file);
    int id = 0;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(line.length()>0)
        {
            QString filter = line.right(4);
            if( (filter != "jpg") && (filter != "jpeg") &&(filter != "png") &&(filter != "JPEG") )//筛选为图片的文件
            {
                continue;
            }
        }
        //显示图片名
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(QString::number(id,10)+"."+line);//显示形式：id.图片名
        ui->listWidget->addItem(item);
        id++;
    }
}

void MainWindow::selectImg(QListWidgetItem *toAdd)
{
    //选中并显示图片
    QStringList list = toAdd->text().split('.');
    selected = "image/" + list[1];
    selectedID = list[0].toInt();
    ui->lineEdit->setText(list[1]+".JPEG");
    QPixmap pix(selected);
    ui->selected->setPixmap(pix.scaled(ui->selected->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    inDatabase = true;
}

void MainWindow::selectLocal(QString got)
{
    //选中并显示图片
    selected = got;
    ui->lineEdit->setText(got);
    QPixmap pix(selected);
    ui->selected->setPixmap(pix.scaled(ui->selected->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    inDatabase = false;
}

void MainWindow::on_Search_clicked()
{
    int k = 10;//默认k=10
    if(!(ui->inputK->text().length()==0))
        k = ui->inputK->text().toInt();

    double p[Dimension];
    if(inDatabase)
    {
        selected = selected + ".JPEG";
    }

    QStringList args;
    args.append(ExtractHist);
    args.append(selected);
    args.append(QString::number(k));
    QProcess::execute(QString("Python.exe"), args);

    QFile file(ExtractResult);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug() << "error!";
    }
    QTextStream in(&file);
    QString line = in.readLine();
    QStringList list = line.split(' ');
    for(int i = 1; i <= Dimension; i++)
        p[i-1] = list[i].toDouble();
    ui->listWidget->clear();
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setViewMode  (QListWidget::IconMode);
    ui->listWidget->setIconSize  (QSize(300,300));
    ui->listWidget->setGridSize  (QSize(300,300));
    ui->listWidget->setSpacing(10);
    ui->listWidget->setResizeMode(QListWidget::Adjust);

    QVector<int> queryResult = m_database.knnQuery(p, k);//返回knn查询结果，按照相关性从大到小排序，queryResult中的每个元素对应一个整数编号id
    double feature[Dimension];
    QString name;

    foreach (int id, queryResult)
    {
        m_database.getFeature(id,feature);
        name = m_database.getLabel(id);

        QListWidgetItem *item = new QListWidgetItem;
        QPixmap pix("image/"+name);
        item->setIcon(pix.scaled(QSize(300,300),Qt::KeepAspectRatio,Qt::SmoothTransformation));//显示图片
        //item->setText("Distance to the query point:"+QString::number(distance(p, feature)));
        ui->listWidget->addItem(item);
        qDebug()<<"Hit:编号="<<id<<"特征向量="<<std::vector<double>(feature, feature+Dimension) << "与查询点的距离平方为："<<distance(p, feature);
    }
}

void MainWindow::on_pushButton_clicked()
{
    //getAllImg();//读入所有图片
}

void MainWindow::on_selectLocal_clicked()
{
    //定义文件对话框类
    fileDialog = new QFileDialog();
    connect(fileDialog, SIGNAL(fileSelected(QString)), this, SLOT(selectLocal(QString)));
    fileDialog->show();
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("Open image"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp *.JPEG)"));
}
