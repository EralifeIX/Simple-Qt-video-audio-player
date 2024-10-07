#include "mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent){
    m_pAudio = new PlayerWidget(this);
    m_pVideo = new VideoPlayer(this);
    m_bPaused = false;
    m_pStack = new QStackedWidget(this);

    m_pStack->addWidget(m_pAudio);
    m_pStack->addWidget(m_pVideo);
    m_pStack->setCurrentIndex(0);

    setCentralWidget(m_pStack);
    resize(350, 120);

    connect(m_pAudio, SIGNAL(changeTitle(QString)), SLOT(slotChangeTitle(QString)));
    connect(m_pAudio, SIGNAL(changeWindow(QString)), SLOT(slotSwitchWidget(QString)));

    connect(m_pVideo, SIGNAL(changeTitle(QString)), SLOT(slotChangeTitle(QString)));
    connect(m_pVideo, SIGNAL(changeWindow(QString)), SLOT(slotSwitchWidget(QString)));

    connect(m_pVideo->getVideoWiget(), SIGNAL(fullScreen()),SLOT(slotFullScreen()));                           // toggle fullscreen
    connect(m_pVideo->getVideoWiget(), SIGNAL(normalScreen()),SLOT(slotNormalScreen()));
}

void MainWindow::slotChangeTitle(QString title){
    setWindowTitle(title);
}
void MainWindow::slotSwitchWidget(QString title)
{
    int curIndex = m_pStack->currentIndex();
    int nextIndex = (curIndex == 0) ? 1 : 0;
    m_pStack->setCurrentIndex(nextIndex);

    QWidget* temp = m_pStack->currentWidget();
    if(dynamic_cast<VideoPlayer*>(temp))
    {
        m_pVideo->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        m_pAudio->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }
    else if(dynamic_cast<PlayerWidget*>(temp))
    {
        m_pAudio->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        m_pVideo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }

    m_pStack->adjustSize();
    resize(temp->sizeHint());
    dynamic_cast<PlayerWidget*>(temp)->setFile(title); //PLayerWidget is base class, both cases will work
}

void MainWindow::keyPressEvent(QKeyEvent* event){
    QWidget* temp = m_pStack->currentWidget();
    dynamic_cast<PlayerWidget*>(temp)->eventHandler(event);
}


void MainWindow::slotFullScreen(){
    showFullScreen();
}

void MainWindow::slotNormalScreen(){
    showNormal();
}



















