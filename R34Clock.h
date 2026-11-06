#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QTimer>
#include <array>
#include <QMouseEvent>
#include <QWindow>

class R34Clock : public QWidget {
public:
    R34Clock(QWidget *parent = nullptr);
private:
    std::array <QLabel*, 4> digitLabels;
    std::array <QMovie*, 4> movie;

    std::array <int, 4> digits = {-1, -1, -1, -1};
    QLabel* colon;
    QTimer *timer;

    void updateTime();
protected:
    void mousePressEvent(QMouseEvent *event) override;
};
