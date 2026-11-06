#include "R34Clock.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QTime>
#include <array>
#include <QString>
#include <QTimer>
#include <QWindow>
#include <QMouseEvent>
#include <QKeySequence>
#include <QShortcut>


R34Clock::R34Clock(QWidget *parent) : QWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    // закрытие по Alt+F4
    QShortcut *closeShortcut = new QShortcut(QKeySequence(Qt::ALT | Qt::Key_F4), this);
    connect(closeShortcut, &QShortcut::activated, qApp, &QCoreApplication::quit);

    // закрытиые по Esc
    QShortcut *escShortcut = new QShortcut(QKeySequence(Qt::Key_Escape), this);
    connect(escShortcut, &QShortcut::activated, qApp, &QCoreApplication::quit);

    for (int i = 0; i < 4; ++i) {
        digitLabels[i] = new QLabel(this);
        digitLabels[i]->setAttribute(Qt::WA_TransparentForMouseEvents);
        movie[i] = nullptr;
    }

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);


    setLayout(layout);

    colon = new QLabel(":", this);
    colon->setAttribute(Qt::WA_TransparentForMouseEvents);
    colon->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "   color: white;"
        "}"
        );

    layout->addWidget(digitLabels[0]);
    layout->addWidget(digitLabels[1]);
    layout->addWidget(colon);
    layout->addWidget(digitLabels[2]);
    layout->addWidget(digitLabels[3]);

    timer = new QTimer(this);
    timer->setInterval(10000);
    connect(timer, &QTimer::timeout, this, &R34Clock::updateTime);
    timer->start(0);

    updateTime();
}

void R34Clock::updateTime() {
    QTime now = QTime::currentTime();
    std::array <int, 4> curdigits = {
        now.hour() / 10,
        now.hour() % 10,
        now.minute() / 10,
        now.minute() % 10
    };
    for (int i = 0; i < 4; i++) {
        if (digits[i] != curdigits[i]) {
            digits[i] = curdigits[i];

            if (movie[i]) {
                movie[i]->stop();
                delete movie[i];
            }

            QString path = QString("numbers/%1.gif").arg(digits[i]);
            movie[i] = new QMovie(path);
            movie[i]->setCacheMode(QMovie::CacheAll);

            digitLabels[i]->setMovie(movie[i]);
            movie[i]->start();
        }
    }
}

void R34Clock::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        windowHandle()->startSystemMove();
    }
}

