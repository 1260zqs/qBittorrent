/*
 * Bittorrent Client using Qt and libtorrent.
 * Copyright (C) 2015, 2023  Vladimir Golovnev <glassez@yandex.ru>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * In addition, as a special exception, the copyright holders give permission to
 * link this program with the OpenSSL project's "OpenSSL" library (or with
 * modified versions of it that use the same license as the "OpenSSL" library),
 * and distribute the linked executables. You must obey the GNU General Public
 * License in all respects for all of the code used other than "OpenSSL".  If you
 * modify file(s), you may extend this exception to your version of the file(s),
 * but you are not obligated to do so. If you do not wish to do so, delete this
 * exception statement from your version.
 */

#pragma once

#include <QHostAddress>
#include <QObject>
#include <QPointer>

#include "base/applicationcomponent.h"

namespace Http
{
    class Server;
}

namespace Net
{
    class DNSUpdater;
}

class WebApplication;

class WebUI final : public ApplicationComponent<QObject>
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(WebUI)

public:
    explicit WebUI(IApplication *app, const QByteArray &tempPasswordHash = {});

    bool isEnabled() const;
    bool isErrored() const;
    QString errorMessage() const;
    bool isHttps() const;
    QHostAddress hostAddress() const;
    quint16 port() const;

signals:
    void error(const QString &message);

private slots:
    void configure();

private:
    void setError(const QString &message);

    bool m_isEnabled = false;
    bool m_isErrored = false;
    QString m_errorMsg;
    QPointer<Http::Server> m_httpServer;
    QPointer<Net::DNSUpdater> m_dnsUpdater;
    QPointer<WebApplication> m_webapp;

    QByteArray m_tempPasswordHash;
    
    //private server
    void configurePrivate();
    bool m_isPrivateEnabled = false;
    QPointer<Http::Server> m_httpServerPrivate;
};
