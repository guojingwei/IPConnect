#include "server.h"

#include "controlcenter.h"
#include "connection.h"
#include "debug.h"
#include "interfaces/iclientmanager.h"

#include <QObject>
#include <QTcpServer>

namespace IPConnect
{

Server::Server(QObject* parent) : IServer(parent){}

Server::~Server(){}

void Server::start()
{
    if(listen(QHostAddress::Any, 2424))
		qCDebug(BASE) << "Server started on 2424";
    else
		qCDebug(BASE) << "Server Could not start on 2424";
}

void Server::incomingConnection(qintptr handle)
{
	qCDebug(BASE) << "handling connection with descriptor " << handle ;
	Connection *conn = new Connection();
	conn->setSocketDescriptor(handle);
	if(conn){
		ControlCenter::instance()->clientManager()->addClient(conn);
	}
}

}