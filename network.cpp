#include "network.h"

Network::Network() {

}

QList<QString> Network::aliveHosts() {
    // TODO: make this function non-blocking

    QList<QNetworkAddressEntry> entries = listInterfaces();

    std::function<bool(const QString&)> isHostAlive = [](const QString &host) -> bool {
        QStringList parameters;
        #if defined(WIN32)
            parameters << "-n" << "1";
        #else
            parameters << "-c 1";
            parameters << "-W" << ".5";
        #endif
            parameters << host;

        int code = QProcess::execute("ping", parameters);

        return code == 0;
    };

    QList<QString> hosts_to_check;
    foreach(QNetworkAddressEntry entry, entries) {
        hosts_to_check.append(hostsInSubnet(entry));
    }

    QList<bool> alive = QtConcurrent::blockingMapped(hosts_to_check, isHostAlive);

    QList<QString> results;
    for(int i = 0; i < hosts_to_check.length(); i++) {
        if(alive[i]) results.append(hosts_to_check[i]);
    }

    return results;
}
