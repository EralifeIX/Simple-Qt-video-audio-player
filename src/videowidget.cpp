#include "videowidget.h"
#include <QMouseEvent>
#include <QMessageBox>

VideoWidget::VideoWidget(QWidget* parent) : QVideoWidget(parent) {}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton ){
        if(!isFullScreen()){
            setFullScreen(true);
            emit fullScreen();
    }
        else{
            setFullScreen(false);
            emit normalScreen();
        }
    }
}

void VideoWidget::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        emit pause();
    }
}


bool VideoWidget::isFullScreen(){
    return m_state;
}

void VideoWidget::setFullScreen(bool state){
    m_state = state;
}
