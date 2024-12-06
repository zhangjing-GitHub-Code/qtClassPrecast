#include "qtClassPrecast.h"
#include "settingsPage.h"

qtClassPrecast::qtClassPrecast(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
}

qtClassPrecast::~qtClassPrecast()
{}

void qtClassPrecast::testSETclicked() {
    this->close();
    settingsPage* stp = new settingsPage(this);
    stp->show();
}