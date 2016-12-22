/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -c DBusAdaptor -a dbusadaptor.h:dbusadaptor.cpp harbour.slackfish.xml
 *
 * qdbusxml2cpp is Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "dbusadaptor.h"
#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*
 * Implementation of adaptor class DBusAdaptor
 */

DBusAdaptor::DBusAdaptor(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DBusAdaptor::~DBusAdaptor()
{
    // destructor
}

void DBusAdaptor::activate(const QString &channelId)
{
    // handle method call harbour.slackfish.activate
    QMetaObject::invokeMethod(parent(), "activate", Q_ARG(QString, channelId));
}
