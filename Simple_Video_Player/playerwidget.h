#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QDial>


class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void setFile(QString fileName);
    void eventHandler(QKeyEvent* event);
    QSize sizeHint() const override;

protected:
    QMediaPlayer* m_pmp;
    QVBoxLayout* m_pvbxMainLayout;
    QHBoxLayout* m_phbxPlayControls;
    QHBoxLayout* m_phbxTimeControls;
    QPushButton* m_pcmdOpen;
    QSlider* m_psldVolume;
    QPushButton* m_pcmdPlay;
    QSlider* m_psldPosition;
    QLabel* m_plblCurrent;
    QLabel* m_plblRemain;

    const int defVol = 50;
    const QStringList videoExtensions = {"mp4", "avi", "mkv", "mov", "flv", "wmv", "webm"};
    const QStringList audioExtensions = { "mp3", "wav", "aac", "flac", "ogg", "m4a", "wma", "alac", "aiff", "amr", "ape"};

    QString msecsToString(qint64 n);
    QString fileChanged();
    void changeIcon();

    bool isPressed();
    void setPressed(bool state);

protected slots:
    virtual void slotOpen();
    void slotPlayPressed();
    void slotSetVol(int);
    void slotSetSliderPos(qint64);
    void slotSetMediaPos(int);
    void slotSetDuration(qint64);
    void slotPause();

signals:
    void changeTitle(QString title);
    void changeWindow(QString file);
};

#endif // PLAYERWIDGET_H
