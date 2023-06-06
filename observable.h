#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include "observable_global.h"
#include <QObject>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <QCoreApplication>

template <typename T> class OBSERVABLE_EXPORT Observable
{
public:
    using Observer = std::function<void(const T &)>;
    Observable<T>(){}
    void subscribe(const Observer &observer){
        observers.push_back(observer);
    }

    void next(const T &value){
        for (const auto &observer : observers){
            observer(value);
        }
    }

private:
    std::vector<Observer> observers;
};


template <typename T> class OBSERVABLE_EXPORT DataStore{
public:
    DataStore<T>(){}

    void setValue(const T &value){
        data = value;
        observable.next(value);
    }

    const T &getValue() const{
        return data;
    }

    Observable<T> &getObservable(){
        return observable;
    }

private:
    T data;
    Observable<T> observable;
};


// QSettingsWrapper
class OBSERVABLE_EXPORT QSettingsWrapper : public QObject
{
    Q_OBJECT
public:
    QSettingsWrapper(QObject *parent = nullptr) : QObject(parent){}

    void setValue(const QString &key, const QVariant &value)
    {
        settings.setValue(key, value);
        emit preferenceChanged(key, value);
    }

    QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant()) const
    {
        return settings.value(key, defaultValue);
    }

signals:
    void preferenceChanged(const QString &key, const QVariant &value);

private:
    QSettings settings;
};

#endif // OBSERVABLE_H
