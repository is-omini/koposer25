#ifndef TERMINALSYSTEM_H
#define TERMINALSYSTEM_H

#include <QDebug>
#include <QString>

inline QDebug Debug() {
	return qDebug().nospace() << "[MY_DEBUG] ";
}

#endif