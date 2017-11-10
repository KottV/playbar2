/*
*   Author: audoban <audoban@openmailbox.org>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Library General Public License as
*   published by the Free Software Foundation; either version 2 or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details
*
*   You should have received a copy of the GNU Library General Public
*   License along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef PLAYBAR_H
#define PLAYBAR_H

#include <QAction>

#include <KActionCollection>
#include <Plasma/DataEngine>
#include <Plasma/DataEngineConsumer>

#include "configdialog.h"

using namespace Plasma;

class PlayBar : public QObject, public Plasma::DataEngineConsumer {
    Q_OBJECT
public:

    PlayBar(KSharedConfigPtr &config, QObject *parent = 0);

    virtual ~PlayBar();

    inline const QString &source() const {
        return mpris2_source;
    }

    inline void setSource(const QString &source) {
        if (!m_mpris2Engine)
            m_mpris2Engine = dataEngine(MPRIS2);
        else
            m_mpris2Engine->disconnectSource(mpris2_source, this);

        mpris2_source = source.trimmed();
        if (!mpris2_source.isEmpty()) {
            m_mpris2Engine->connectSource(mpris2_source, this);
        }
    }

    const DataEngine::Data &data();

    inline void startAction(const QString &name) const;
    inline void seek(qlonglong us) const;


public slots:
    void dataUpdated(const QString &sourceName, const Plasma::DataEngine::Data &data);

 public slots:
    void action_playPause();
    void action_stop();
    void action_next();
    void action_previous();
    void action_forward();
    void action_backward();
    void action_raise();
    void showSettings();

private:
    KSharedConfigPtr m_config;
    ConfigDialog *m_configDialog {nullptr};
    KActionCollection *m_collection {nullptr};
    DataEngine* m_mpris2Engine {nullptr};
    DataEngine::Data *m_data {nullptr};

    const char * const MPRIS2 {"mpris2"};
    qlonglong m_currentPosition {0};

    QAction *m_playpause;
    QAction *m_stop;
    QAction *m_next;
    QAction *m_previous;
    QAction *m_forward;
    QAction *m_backward;
    QAction *m_raise;

    QString mpris2_source {"@multiplex"};
};

#endif // PLAYBAR_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on;
