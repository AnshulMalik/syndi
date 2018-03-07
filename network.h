#ifndef NETWORK_H
#define NETWORK_H

#include <QList>
#include <QString>
#include <QtConcurrent>
#include <QProcess>
#include <QThread>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QtMath>

class Network {
    public:
        static QList<QString> aliveHosts();
        Network();
    private:
        static QList<QNetworkAddressEntry> listInterfaces() {
            QList<QNetworkAddressEntry> valid_interfaces;

            QList<QNetworkInterface> interfs = QNetworkInterface::allInterfaces();
            foreach(QNetworkInterface interf, interfs) {
                QList<QNetworkAddressEntry> entries= interf.addressEntries();
                foreach(QNetworkAddressEntry entry, entries) {
                    QHostAddress addr = entry.ip();

                    if(!addr.isLinkLocal() && addr.toString() != "127.0.0.1" && addr.toString() != "::1") {
                        qDebug() << addr.toString();
                        valid_interfaces.append(entry);
                    }
                }
            }

            return valid_interfaces;
        }
        static QList<QString> hostsInSubnet(QNetworkAddressEntry entry) {
            QHostAddress addr = entry.ip();
            QHostAddress subnet = entry.netmask();
            QList<QString> hosts;
            int num_hosts = qPow(2, 32 - entry.prefixLength()) - 1;

            unsigned start = addr.toIPv4Address() & subnet.toIPv4Address();
            for(unsigned short i = 1; i < num_hosts; i++) {
                unsigned cur_addr_int = start + i;
                QHostAddress cur_addr = *(new QHostAddress(cur_addr_int));
                hosts.append(cur_addr.toString());
            }

            return hosts;
        }
};

#endif // NETWORK_H
