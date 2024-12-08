#include "precastingWidget.h"

precastingWidget::precastingWidget(QWidget *parent)
	: QWidget(parent)
{
    qDebug() << "before ui";
	ui.setupUi(this);
    qDebug() << "aft ui";
    ent_lenpf = (p_width - min_length) / ent_frames;
    dspr_lenpf = (p_width - min_length) / dspr_frames;
    qDebug() << "bef getscr";
    priScr = QGuiApplication::primaryScreen();
    qDebug() << "bef getheo";
    scrGmt = priScr->geometry();
    E_STAT = ENTERING;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    calc_tm = new QTimer(this);
    connect(calc_tm, &QTimer::timeout, this, &precastingWidget::trigCheck);
    calc_tm->start(19);
    ui.hint_dist_tr0->adjustSize();
    ui.hint_dist_tr1->adjustSize();
    ui.hint_subjName->adjustSize();
    ui.hint_timeNum->adjustSize();
    ui.mainFrame->close();
    this->close();
}

precastingWidget::~precastingWidget()
{}
void precastingWidget::trigCheck() {
    // qDebug() << "TRIGGERED";
    // checkActivity(); // update();
    calcAnimation();
    this->repaint();
}
void precastingWidget::checkActivity()
{
    // DelayMS(2000);
    DelayMS(2000);
    if (E_STAT == IDLE) E_STAT = PREDISPR;
    else E_STAT = PREENTER;
    // throw new NotImplementedException();
}

void precastingWidget::calcAnimation()
{
    switch (E_STAT)
    {
    case PREENTER:
        // TODO: set this visible OK
        // reenter lose sth this-¡·
        // lost that is this->shoew?sheow????xsb
        this->show();
        E_STAT = ENTERING;
        tmp_frmcnt = 0;
        break;
    case ENTERING:
        cur_width = min_length + (p_width - min_length) * tmp_frmcnt / ent_frames;
        ++tmp_frmcnt;
        if (tmp_frmcnt > ent_frames)
        {
            E_STAT = IDLE;
            cur_width = p_width;
            // if(E_STAT==animStat.IDLE)
            // set hints text visible OK
            ui.mainFrame->show();
            tmp_frmcnt = 0;
        }
        break;
    case PREDISPR:
        // TODO: set hint text hidden
        ui.mainFrame->close();
        E_STAT = DISAPPEARING;
        break;
    case POSTDISPR:
        // TODO: set this hidden
        this->hide();
        E_STAT = DISAPPEAR;
        tmp_frmcnt = 0;
        break;
    case DISAPPEARING:
        // cur_width = min_length + dspr_lenpf * (dspr_frames - tmp_frmcnt);
        cur_width = min_length + (p_width - min_length) * (dspr_frames - tmp_frmcnt) / dspr_frames;
        ++tmp_frmcnt;
        if (tmp_frmcnt >= dspr_frames)E_STAT = POSTDISPR;
        break;
    case IDLE:
    case DISAPPEAR:
    default:
        checkActivity();
        break;
    }
}

void precastingWidget::paintEvent(QPaintEvent* ev) {
    //qDebug() << "BEING CALLED";
    
    //qDebug() << "SFT CALC";
	QPainter pnt(this);
    pnt.setRenderHint(QPainter::Antialiasing);
    pnt.setBrush(QColor(0, 0, 0, 255));
    _frameFinish = false;
    // p_width to be changed by calcAnimation()
    /* auto plu = new QPoint(p_slantDelta + p_LRMargin, 0),
         pru = new QPoint(cur_width - p_LRMargin, 0),
         prd = new QPoint(cur_width - p_slantDelta - p_LRMargin, p_height),
         pld = new QPoint(p_LRMargin, p_height);
    */
    QPointF pl_pnts[4] = {
        QPointF(p_slantDelta + p_LRMargin, 0),
        QPointF(cur_width - p_LRMargin, 0),
        QPointF(cur_width - p_slantDelta - p_LRMargin, p_height),
        QPointF(p_LRMargin, p_height) };
    // this.Width = ;
    _fr_width = cur_width + p_LRMargin;
    //qDebug() << "BF SETW";
    this->setFixedWidth(_fr_width);
    //qDebug() << "BF MOVE";
    pnt.drawPolygon(pl_pnts, 4);
    this->move(
        (  scrGmt.width()
         - _fr_width      ) / 2, 0);
    //qDebug() << "BF SETW";
    _frameFinish = true;
}