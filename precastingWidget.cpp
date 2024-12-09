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
    this->setWindowFlags((Qt::FramelessWindowHint|Qt::Tool|Qt::WindowStaysOnTopHint));
    this->setAttribute(Qt::WA_TranslucentBackground);
    calc_tm = new QTimer(this);
    connect(calc_tm, &QTimer::timeout, this, &precastingWidget::trigCheck);
    calc_tm->start(19);
    ui.hint_dist_tr0->adjustSize();
    ui.hint_dist_tr1->adjustSize();
    ui.hint_subjName->adjustSize();
    ui.hint_timeNum->adjustSize();
    ui.mainFrame->close();
    pnt = new QPainter(this);
    this->close();
}

precastingWidget::~precastingWidget(){
    calc_tm->stop();
}
void precastingWidget::trigCheck() {
    // qDebug() << "TRIGGERED";
    // checkActivity(); // update();
    if(calcAnimation())
        this->repaint();
}
/* Returns:
   true if needs update
   false ....
*/
bool precastingWidget::checkActivity()
{
    // DelayMS(2000);
    DelayMS(2000);
    if (E_STAT == IDLE) E_STAT = PREDISPR;
    else E_STAT = PREENTER;
    return true;
    // throw new NotImplementedException();
}

bool precastingWidget::calcAnimation()
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
        return true;
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
        return true;
        break;
    case PREDISPR:
        // TODO: set hint text hidden
        ui.mainFrame->close();
        E_STAT = DISAPPEARING;
        return true;
        break;
    case POSTDISPR:
        // TODO: set this hidden
        this->hide();
        E_STAT = DISAPPEAR;
        tmp_frmcnt = 0;
        return true;
        break;
    case DISAPPEARING:
        // cur_width = min_length + dspr_lenpf * (dspr_frames - tmp_frmcnt);
        cur_width = min_length + (p_width - min_length) * (dspr_frames - tmp_frmcnt) / dspr_frames;
        ++tmp_frmcnt;
        if (tmp_frmcnt >= dspr_frames)E_STAT = POSTDISPR;
        return true;
        break;
    case IDLE:
    case DISAPPEAR:
    default:
        return checkActivity();
        break;
    }
    return false;
}

void precastingWidget::paintEvent(QPaintEvent* ev) {
    if (!pnt)return;
    pnt->begin(this);
    pnt->setRenderHint(QPainter::Antialiasing);
    pnt->setPen(QColor(0,0,0,220));
    pnt->setBrush(QColor(0,0,0,255));
    _frameFinish = false;
    // p_width to be changed by calcAnimation()
    // NB typoe(restore
    // 2shift before this //
    // Black BG parlhxg
    QPointF pl_pnts[] = {
        QPointF(p_slantDelta + p_LRMargin, 0),
        QPointF(cur_width - p_LRMargin, 0),
        QPointF(cur_width - p_slantDelta - p_LRMargin, p_height),
        QPointF(p_LRMargin, p_height) };
    // this.Width = ;
    _fr_width = cur_width + p_LRMargin;
    //qDebug() << "BF SETW";
    this->setFixedWidth(_fr_width);
    //qDebug() << "BF MOVE";
    pnt->drawPolygon(pl_pnts, 4);
    // BG END
    pnt->setBrush(QColor(255,255,255, 250));
    pnt->setPen(QColor(255,255,255, 250));
    // L WHITE BORDER
    QPointF pl_pnts1[] = {
        QPointF(p_slantDelta + p_LRMargin, 0),
        QPointF(p_slantDelta + p_LRMargin+10, 0),
        QPointF(p_LRMargin+10, p_height),
        QPointF(p_LRMargin, p_height) };
    pnt->drawPolygon(pl_pnts1, 4);
    // L END
    // R WHITE BORDER
    QPointF pl_pnts2[] = {
        QPointF(cur_width - p_LRMargin-10, 0),
        QPointF(cur_width - p_LRMargin, 0),
        QPointF(cur_width - p_slantDelta - p_LRMargin, p_height),
        QPointF(cur_width - p_slantDelta - p_LRMargin-10, p_height) };
    pnt->drawPolygon(pl_pnts2, 4);
    // R END
    this->move(
        (  scrGmt.width()
         - _fr_width      ) / 2, 0);
    //qDebug() << "BF SETW";
    pnt->end();
    _frameFinish = true;
}