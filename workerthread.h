#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QVector>

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread();

protected:
    void run() override;

public slots:
    void updateScene(const QVector<int>& newValues);

signals:
    void sceneUpdateRequested(const QVector<int>& newValues);

private:
    QVector<int> generateNewValues();

};

#endif // WORKERTHREAD_H
