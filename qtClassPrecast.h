#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtClassPrecast.h"
#include "precastingWidget.h"

class qtClassPrecast : public QWidget
{
    Q_OBJECT

public:
    qtClassPrecast(QWidget *parent = nullptr);
    ~qtClassPrecast();
    precastingWidget* pcMain;
private:
    Ui::qtClassPrecastClass ui;
private slots:
    void testSETclicked();
};
