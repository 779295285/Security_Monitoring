#include <QApplication>
#include "view/beginwidget.h"

#include "view/main_widget.h"


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    BeginWidget test;
    //Main_Widget test;
    test.show();


    return a.exec();
}
