#pragma once

#include <QtWidgets/QWidget>
#include "ui_qtClassPrecast.h"

class qtClassPrecast : public QWidget
{
    Q_OBJECT

public:
    qtClassPrecast(QWidget *parent = nullptr);
    ~qtClassPrecast();

private:
    Ui::qtClassPrecastClass ui;
private slots:
    void testSETclicked();
};
