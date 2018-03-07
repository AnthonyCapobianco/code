//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <iostream>

class Drug
{
 private:
    std::string name;
    int *doses;
 public:
    Drug(std::string drugName, int drugDoses[])
    {
        name = drugName;
        doses = drugDoses;
    }
    void doStuff()
    {
        std::cout << name << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Drug arr[] = Drug { ritalin("Ritalin", (int[]) {5,10,15,20})
                 , Drug concerta("Concerta", (int[]) {36, 72})
                 };

    ritalin.doStuff();
    /*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
    */
}
