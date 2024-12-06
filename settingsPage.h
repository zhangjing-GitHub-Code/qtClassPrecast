#pragma once

#include <QMainWindow>
#include "ui_settingsPage.h"

class settingsPage : public QMainWindow
{
	Q_OBJECT

public:
	settingsPage(QWidget *parent = nullptr);
	~settingsPage();

private:
	Ui::settingsPageClass ui;
};
