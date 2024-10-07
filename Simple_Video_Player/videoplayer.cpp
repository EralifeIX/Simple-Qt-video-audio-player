#include <videoplayer.h>
#include <QStyle>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>



VideoPlayer::VideoPlayer(QWidget* parent) : PlayerWidget(parent)
{
    m_pcmdOpen = new QPushButton("&Open");
    m_pcmdOpen->setFocusPolicy(Qt::NoFocus);
    m_pcmdOpen->setMaximumSize(70,40);
    m_pcmdOpen->setGeometry(QRect(QPoint(1300,100), QSize(70, 40)));

    m_pcmdPlay = new QPushButton;
    m_pcmdPlay->setFocusPolicy(Qt::NoFocus);
    m_pcmdPlay->setMaximumSize(40,40);

    m_psldVolume = new QSlider;
    m_psldPosition = new QSlider;
    m_plblCurrent = new QLabel(msecsToString(0));
    m_plblRemain = new QLabel(msecsToString(0));
    m_pmp = new QMediaPlayer;
    m_pvbxMainLayout = new QVBoxLayout;
    m_phbxPlayControls = new QHBoxLayout;

    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));

    m_psldPosition->setFocusPolicy(Qt::NoFocus);
    m_psldPosition->setRange(0, 100);
    m_psldPosition->setOrientation(Qt::Horizontal);

    m_psldVolume->setFocusPolicy(Qt::NoFocus);
    m_psldVolume->setRange(0,100);
    m_psldVolume->setValue(50);
    m_psldVolume->setOrientation(Qt::Horizontal);
    m_psldVolume->setMaximumWidth(100);


    m_pvw = new VideoWidget;
    m_pmp->setVideoOutput(m_pvw);
    m_pmp->setAudioOutput(new QAudioOutput);
    m_pmp->audioOutput()->setVolume(0.5);

    connect(m_pcmdOpen, SIGNAL(clicked()), SLOT(slotOpen()));                               // control buttons
    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlayPressed()));

    connect(m_psldVolume, SIGNAL(sliderMoved(int)), SLOT(slotSetVol(int)));                 //volume slider
    connect(m_psldPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPos(int)));          //position slider

    connect(m_pmp, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPos(qint64)));        // video rewind control
    connect(m_pmp, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));

    connect(m_pvw, SIGNAL(fullScreen()),SLOT(slotHideControl()));                           // toggle fullscreen
    connect(m_pvw, SIGNAL(normalScreen()),SLOT(slotShowControl()));

    connect(m_pvw, SIGNAL(pause()), SLOT(slotPause()));

    // Layout

    m_phbxPlayControls->addWidget(m_plblCurrent);
    m_phbxPlayControls->addWidget(m_pcmdOpen);
    m_phbxPlayControls->addWidget(m_pcmdPlay);
    m_phbxPlayControls->addWidget(m_plblRemain);
    m_phbxPlayControls->addWidget(m_psldVolume);
    m_phbxPlayControls->setContentsMargins(10, 0, 10, 0);

    m_pvbxMainLayout->addWidget(m_pvw);
    m_pvbxMainLayout->addWidget(m_psldPosition);
    m_pvbxMainLayout->addLayout(m_phbxPlayControls);
    m_pvbxMainLayout->setContentsMargins(0, 0, 0, 0);

    cleanLayout(layout()); //clean created by base class layout
    setLayout(m_pvbxMainLayout);

}

void VideoPlayer::slotOpen() {
    QString file = QFileDialog::getOpenFileName(this, "Open File");
    QFileInfo fileInfo(file);

    if(!file.isEmpty() && videoExtensions.contains(fileInfo.suffix())){
        m_pmp->setSource(QUrl::fromLocalFile(file));
        m_pcmdPlay->setEnabled(true);
        changeIcon();
        emit changeTitle(fileChanged());
    }
    else if(!file.isEmpty() && audioExtensions.contains(fileInfo.suffix())){
        emit changeWindow(file);
    }
}


void VideoPlayer::cleanLayout(QLayout* layout){
    QLayoutItem * item;
    QLayout * sublayout;
    QWidget * widget;

    while ((item = layout->takeAt(0))) {
        if ((sublayout = item->layout()) != 0) {cleanLayout(sublayout);}
        else if ((widget = item->widget()) != 0) {widget->hide(); delete widget;}
        else {delete item;}
    }
    delete layout;

}

VideoWidget* VideoPlayer::getVideoWiget(){
    return m_pvw;
}

QSize VideoPlayer::sizeHint() const {
    return QSize(1280, 720);
}


void VideoPlayer::slotHideControl(){

    m_psldPosition->hide();
    hideLayout(m_phbxPlayControls);
}

void VideoPlayer::slotShowControl(){
    m_psldPosition->show();
    showLayout(m_phbxPlayControls);
}


void VideoPlayer::hideLayout(QLayout* layout){
    if (!layout)
        return;

    QWidget* widget;
    QLayout* child;
    for(int i = 0; i < layout->count(); i++){
        widget = layout->itemAt(i)->widget();
        if(widget)
            widget->hide();
        //if there sublayuts
        child = layout->itemAt(i)->layout();
        hideLayout(child);
    }
}

void VideoPlayer::showLayout(QLayout* layout){
    if (!layout)
        return;

    QWidget* widget;
    QLayout* child;
    for(int i = 0; i < layout->count(); i++){
        widget = layout->itemAt(i)->widget();
        if(widget)
            widget->show();
        //if there sublayuts
        child = layout->itemAt(i)->layout();
        showLayout(child);
    }
}




















