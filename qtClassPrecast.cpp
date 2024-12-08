#include "qtClassPrecast.h"
#include "settingsPage.h"
#include "precastingWidget.h"

qtClassPrecast::qtClassPrecast(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

qtClassPrecast::~qtClassPrecast()
{}

void qtClassPrecast::testSETclicked() {
    this->close();
    // settingsPage* stp = new settingsPage(this);
    // stp->show();
    // precasting{age}
    pcMain = new precastingWidget(this);
    qDebug() << "BEFORE  SHOW";
    pcMain->show();
    qDebug() << "BE  SHOW";
    QEventLoop tlp;
    // connect(pcMain, SIGNAL(finished(int)), &tlp, SLOT(quit()));
    tlp.exec();
    // pcMain->exec();
}