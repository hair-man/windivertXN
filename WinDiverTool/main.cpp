#include <QApplication>

#include "DivertMainWin.h"
#include "ToolCommon.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	DivertMainWin DWM;

	DWM.show();

	return a.exec();
}
