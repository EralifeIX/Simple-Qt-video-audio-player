#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "playerwidget.h"
#include "videowidget.h"


class VideoPlayer : public PlayerWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget* parent = nullptr);
    [[nodiscard]] QSize sizeHint() const override;
    VideoWidget* getVideoWiget();

private:
    void cleanLayout(QLayout* layout);
    VideoWidget* m_pvw;
    void hideLayout(QLayout* layout);
    void showLayout(QLayout* layout);

protected slots:
    void slotOpen() override;
    void slotHideControl();
    void slotShowControl();
};

#endif // VIDEOPLAYER_H
