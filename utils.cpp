#include "utils.h"

void DelayMS(unsigned ms) {
	QTime _tar = QTime::currentTime().addMSecs(ms);
	while (QTime::currentTime() < _tar)
		// QCoreApplication::preo
		QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}