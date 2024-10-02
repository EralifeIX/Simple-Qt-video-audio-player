#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QObject>
#include <QVideoWidget>

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event) override;             //detect is video source clicked by mouse, then send signal to the video player
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    bool isFullScreen();
    void setFullScreen(bool state);

    bool m_state;

signals:
    void fullScreen();
    void normalScreen();
    void pause();   //detecting if screen pressed once (pause signal to video player)


};

#endif // VIDEOWIDGET_H
