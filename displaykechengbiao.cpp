
#include "displaykechengbiao.h"
#include "ui_displaykechengbiao.h"

#include <QScroller>
#include <QPixmap>
#include <QDateTime>
#include <QMessageBox>
#include <QAndroidJniObject>

DisplayKeChengBiao::DisplayKeChengBiao(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DisplayKeChengBiao)
{
    ui->setupUi(this);

    m_model = new DisplayKeChengBiaoModel();
    ui->tableView->setModel(m_model);

    this->resetData();
    this->setWindowFlags(Qt::Window);

    connect(ui->btn_saveAsPicture, SIGNAL(clicked()), this, SLOT(saveAsPicture()));

    QScroller::grabGesture(ui->tableView, QScroller::LeftMouseButtonGesture);
}

DisplayKeChengBiao::~DisplayKeChengBiao()
{
    delete ui;
}

void DisplayKeChengBiao::show()
{
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();

    // 防止有的行过小，不好看
    for (int i(0); i != 7; ++i)
        if (ui->tableView->rowHeight(i) < 120)
            ui->tableView->setRowHeight(i, 120);

    QDialog::show();
}

void DisplayKeChengBiao::resetData()
{
    m_model->resetData();

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}

void DisplayKeChengBiao::setData(const int &time, const QString &type)
{
    m_model->setData(time, type);
}

void DisplayKeChengBiao::saveAsPicture()
{
    QAndroidJniObject storageDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
    QAndroidJniObject storagePath = storageDir.callObjectMethod("getAbsolutePath", "()Ljava/lang/String;");
    QString saveFile = storagePath.toString() + "/ZhuMa-Curriculum-" + QString::number(QDateTime::currentMSecsSinceEpoch() / 1000 % 10000000) + ".png";

    int w(ui->tableView->verticalHeader()->width()), h(ui->tableView->horizontalHeader()->height());
    for (int i(0); i != 5; ++i)
        w += ui->tableView->columnWidth(i);
    for (int i(0); i != 7; ++i)
        h += ui->tableView->rowHeight(i);

    QSize oldFrameSize = this->size();
    ui->tableView->setMinimumSize(w, h);
    ui->tableView->setMaximumSize(w, h);

    QPixmap pixmap(w, h);
    ui->tableView->render(&pixmap, QPoint(), QRegion(0, 0, w, h));

    ui->tableView->setMinimumSize(0, 0);
    this->setMinimumSize(oldFrameSize);
    this->setMaximumSize(oldFrameSize);
    this->adjustSize();

    if (pixmap.save(saveFile))
    {
        QMessageBox::information(this, "保存成功！", saveFile);
    }
    else
    {
        QMessageBox::information(this, "保存失败！", "文件写入失败。");
    }
}
