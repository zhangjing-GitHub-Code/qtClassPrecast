#pragma once

#include <QWidget>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>
#include <QTimer>
#include <QJsonDocument>
#include "utils.h"
#include "ui_precastingWidget.h"

class precastingWidget : public QWidget
{
	Q_OBJECT

    struct CTActv
    {
        enum type { CLASS, REST, IDLE };
        QTime actStart, actEnd;
    };
    enum animStat
    {
        DISAPPEAR,
        PREENTER,
        ENTERING,
        PREDISPR,
        POSTDISPR,
        DISAPPEARING,
        IDLE
    };
private:
    animStat E_STAT;
    int p_width = 425,
        cur_width = 50,
        p_slantDelta = 25;
    const int
        p_height = 60,
        p_LRMargin = 5;
    int tmp_frmcnt = 0,
        ent_frames = 90,
        dspr_frames = 74,
        min_length = 90;
    int ent_lenpf = 0,
        dspr_lenpf = 0;
    int
        FPS = 1000/20;
    volatile bool _frameFinish = false;
    volatile int _fr_width = 100 ;
    bool _isLoaded=false;

    QScreen* priScr;// = QGuiApplication::primaryScreen();
    QRect    scrGmt;// = priScr->geometry();

public:
	precastingWidget(QWidget *parent = nullptr);
	~precastingWidget();

	void paintEvent(QPaintEvent* ev);

private slots:
    void trigCheck();

private:
    QPainter* pnt;// (this);
    QTimer *calc_tm;
    bool calcAnimation();
    // void checkAcvitity();
    bool checkActivity();
	Ui::precastingWidgetClass ui;
};
