#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->setFlow(QListView::LeftToRight);
    ui->listWidget->setViewMode  (QListWidget::IconMode);
    ui->listWidget->setIconSize  (QSize(200,200));
    ui->listWidget->setGridSize  (QSize(300,300));
    ui->listWidget->setSpacing(10);
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectImg(QListWidgetItem*)));    
    m_database.init(ImageDatabaseFile);//初始化图片数据库
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
        //item->setIcon(QPixmap("image/"+line));//显示图片
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
}

void MainWindow::selectLocal(QString got)
{
    //选中并显示图片
    selected = got;
    ui->lineEdit->setText(got);
    ui->listWidget->clear();
    QListWidgetItem *item = new QListWidgetItem;
    item->setIcon(QPixmap(got).scaled(QSize(200,200),Qt::KeepAspectRatio,Qt::SmoothTransformation));//显示图片
    item->setText(got);
    ui->listWidget->addItem(item);
}

void MainWindow::on_Search_clicked()
{
    //double p[Dimension];
    //readNthFeature(selectedID, p, ImageDatabaseFile);//从文件中读出id所对应的特征向量

    ui->listWidget->clear();
    double p[9]={3096, 1755, 5025, 2387, 1110, 2148, 2511, 1428, 2303};//测试代码
    QVector<int> queryResult = m_database.knnQuery(p, 10);//返回knn查询结果，按照相关性从大到小排序，queryResult中的每个元素对应一个整数编号id
    double feature[Dimension];
    QString name;

    foreach (int id, queryResult)
    {
        readNthFeature(id, feature, ImageDatabaseFile);//从文件中读出id所对应的特征向量
        readNthImageName(id,name,ImageList);//从文件中读出id所对应的图片名

        QListWidgetItem *item = new QListWidgetItem;
        item->setIcon(QPixmap("image/"+name).scaled(QSize(200,200),Qt::KeepAspectRatio,Qt::SmoothTransformation));//显示图片
        item->setText("Distance to the query point:"+QString::number(distance(p, feature)));
        ui->listWidget->addItem(item);
        qDebug()<<"Hit:编号="<<id<<"特征向量="<<std::vector<double>(feature, feature+Dimension) << "与查询点的距离平方为："<<distance(p, feature);
    }
}

void MainWindow::on_pushButton_clicked()
{
    getAllImg();//读入所有图片
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
