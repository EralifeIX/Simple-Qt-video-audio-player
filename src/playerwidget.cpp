#include "playerwidget.h"
#include <QStyle>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QAudioOutput>
#include <QKeyEvent>


PlayerWidget::PlayerWidget(QWidget *parent)
    : QWidget{parent}
{
    installEventFilter(this);

    m_pcmdOpen = new QPushButton("&Open");
    m_pcmdOpen->setFocusPolicy(Qt::NoFocus);
    m_pcmdPlay = new QPushButton;
    m_psldVolume = new QSlider;
    m_psldPosition = new QSlider;
    m_plblCurrent = new QLabel(msecsToString(0));
    m_plblRemain = new QLabel(msecsToString(0));
    m_pmp = new QMediaPlayer;
    m_pvbxMainLayout = new QVBoxLayout;
    m_phbxPlayControls = new QHBoxLayout;
    m_phbxTimeControls = new QHBoxLayout;

    m_pcmdPlay->setFocusPolicy(Qt::NoFocus);
    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));

    m_psldPosition->setFocusPolicy(Qt::NoFocus);
    m_psldPosition->setRange(0, 100);
    m_psldPosition->setOrientation(Qt::Horizontal);

    m_psldVolume->setFocusPolicy(Qt::NoFocus);
    m_psldVolume->setRange(0,100);
    m_psldVolume->setValue(50);
    m_psldVolume->setOrientation(Qt::Vertical);

    m_pmp->setAudioOutput(new QAudioOutput);
    m_pmp->audioOutput()->setVolume(0.5);

    connect(m_pcmdOpen, SIGNAL(clicked()), SLOT(slotOpen()));
    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlayPressed()));
    connect(m_psldVolume, SIGNAL(sliderMoved(int)), SLOT(slotSetVol(int)));
    connect(m_psldPosition, SIGNAL(sliderMoved(int)), SLOT(slotSetMediaPos(int)));
    connect(m_pmp, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPos(qint64)));
    connect(m_pmp, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));

    // Layout
    m_phbxPlayControls->addWidget(m_pcmdOpen);
    m_phbxPlayControls->addWidget(m_pcmdPlay);
    m_phbxPlayControls->addWidget(m_psldVolume);

    m_phbxTimeControls->addWidget(m_plblCurrent);
    m_phbxTimeControls->addWidget(m_psldPosition);
    m_phbxTimeControls->addWidget(m_plblRemain);

    m_pvbxMainLayout->addLayout(m_phbxPlayControls);
    m_pvbxMainLayout->addLayout(m_phbxTimeControls);
    setLayout(m_pvbxMainLayout);
}


QSize PlayerWidget::sizeHint() const {
    return QSize(320, 120);
}


QString PlayerWidget::msecsToString(qint64 n){
    qint64 hours = (n / (3600 * 1000));
    qint64 minutes = (n % (3600 *1000)) / (60 * 1000);
    qint64 seconds = (n % (60 * 1000)) / 1000;
    return QTime(hours,minutes, seconds).toString("hh:mm:ss");
}


void PlayerWidget::changeIcon(){
    if(m_pmp->playbackState() == QMediaPlayer::PlayingState)
        m_pcmdPlay->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaStop));

    else
        m_pcmdPlay->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
}


void PlayerWidget::slotOpen(){
    QString file = QFileDialog::getOpenFileName(this, "Open File");
    QFileInfo fileInfo(file);

    if(!file.isEmpty() && audioExtensions.contains(fileInfo.suffix())){
        m_pmp->stop();
        m_pmp->setSource(QUrl::fromLocalFile(file));
        m_pcmdPlay->setEnabled(true);
        changeIcon();
        emit changeTitle(fileChanged());
    }
    else if(!file.isEmpty() && videoExtensions.contains(fileInfo.suffix())){
        m_pmp->stop();
        emit changeWindow(file);
    }
}


void PlayerWidget::slotPlayPressed(){
    if(m_pmp->playbackState() == QMediaPlayer::PlayingState)
        m_pmp->stop();
    else
        m_pmp->play();
    changeIcon();
}


void PlayerWidget::slotSetVol(int n){
    float vol = n; //AudioOutut recieves values from 0 to 1
    vol /= 100;
    m_pmp->audioOutput()->setVolume(vol);
}


void PlayerWidget::slotSetMediaPos(int position){
    m_pmp->setPosition(position);
}


void PlayerWidget::slotSetDuration(qint64 duration){
    m_psldPosition->setRange(0, duration);
    m_plblCurrent->setText(msecsToString(0));
    m_plblRemain->setText(msecsToString(duration));
}


void PlayerWidget::slotSetSliderPos(qint64 n){
    m_psldPosition->setValue(n);
    m_plblCurrent->setText(msecsToString(n));
    int duration = m_psldPosition->maximum();
    m_plblRemain->setText(msecsToString(duration - n));
}


void PlayerWidget::slotPause(){
    if (m_pmp->playbackState() == QMediaPlayer::PlayingState) {
        m_pmp->pause();  // Only pause if it's currently playing
    }
    else{
        m_pmp->play();
    }
}


QString PlayerWidget::fileChanged(){
    QUrl fileUrl = m_pmp->source();
    QString fileName = QFileInfo(fileUrl.toLocalFile()).baseName();
    return(fileName + " Simple Video Player");
}

// This method called by Mainwindow class, when the file existance and type are already checked
void PlayerWidget::setFile(QString fileName){
    m_pmp->setSource(QUrl::fromLocalFile(fileName));
    emit changeTitle(fileChanged());
    m_pcmdPlay->setEnabled(true);
    changeIcon();
}


void PlayerWidget::eventHandler(QKeyEvent* event){
    switch (event->key()) {
    case Qt::Key_Up: {
        event->accept();
        qreal curVol = m_pmp->audioOutput()->volume();
        qreal newVol = curVol + 0.05;
        if (newVol > 1.0) newVol = 1.0; // Ensure volume doesn't exceed 100%

        m_psldVolume->setValue(newVol *100);
        m_pmp->audioOutput()->setVolume(newVol);
        break;
    }

    case Qt::Key_Down :{
        qreal curVol = m_pmp->audioOutput()->volume();
        qreal newVol = curVol - 0.05;
        if (newVol < 0.0) newVol = 0.0;  // Ensure volume doesn't go below 0%

        m_psldVolume->setValue(newVol *100);
        m_pmp->audioOutput()->setVolume(newVol);
        event->accept();
        break;
    }

    case Qt::Key_Left: {
        qint64 currentPosition = m_pmp->position();  // Get the current position in milliseconds
        qint64 newPosition = currentPosition - 5000;       // Add 5 seconds (5000 ms)
        if (newPosition < 0 )
            newPosition = 0;  // Ensure the new position doesn't exceed the duration

        m_pmp->setPosition(newPosition);
        event->accept();
        break;
    }
    case Qt::Key_Right :{
        qint64 currentPosition = m_pmp->position();  // same function as before
        qint64 newPosition = currentPosition + 5000;
        qint64 duration = m_pmp->duration();
        if (newPosition > duration)
            newPosition = duration;

        m_pmp->setPosition(newPosition);
        event->accept();
        break;
    }
    case Qt::Key_Space :{
        slotPause();
        break;
    }

    default:
         QWidget::keyPressEvent(event);
        break;
    }
}



























