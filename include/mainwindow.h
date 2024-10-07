#include <QMainWindow>
#include <QStackedWidget>
#include "playerwidget.h"
#include "videoplayer.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
protected:
    PlayerWidget* m_pAudio;
    VideoPlayer* m_pVideo;
    QStackedWidget* m_pStack;
    bool m_bPaused;

protected slots:
    void keyPressEvent(QKeyEvent* event) override;

    void slotChangeTitle(QString);
    void slotSwitchWidget(QString);
    void slotFullScreen();
    void slotNormalScreen();


};













#endif //MAINWINDOW_H
