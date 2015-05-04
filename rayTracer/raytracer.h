#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <QObject>

class RayTracer : public QObject
{
    Q_OBJECT
public:
    explicit RayTracer(QObject *parent = 0);

    QString getInFile() const;
    void setInFile(const QString &value);

    QString getOutFile() const;
    void setOutFile(const QString &value);

signals:

public slots:

private:
    QString inFile;
    QString outFile;
};

#endif // RAYTRACER_H
