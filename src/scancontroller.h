/***************************************************************************
 *   Copyright (C) 2003-2005 by The amaroK Developers                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA  02111-1307, USA.          *
 ***************************************************************************/

#ifndef AMAROK_SCANCONTROLLER_H
#define AMAROK_SCANCONTROLLER_H

#include <qobject.h>     //baseclass
#include <qxml.h>        //baseclass

class DbConnection;
class KProcIO;

/**
 * @author Mark Kretschmann <markey@web.de>
 */
class ScanController : public QObject, public QXmlDefaultHandler
{
    Q_OBJECT

    public:
        ScanController( QObject* parent, bool incremental, const QStringList& folders = QString::null );
        ~ScanController();

        static ScanController* instance() { return s_instance; }

    private slots:
        void slotReadReady();
        void slotProcessExited();

    private:
        void initIncrementalScanner();
        bool startElement( const QString&, const QString &localName, const QString&, const QXmlAttributes &attrs );

        static ScanController* s_instance;

        DbConnection* const m_db;
        KProcIO*            m_scanner;
        QStringList         m_folders;

        QXmlInputSource  m_source;
        QXmlSimpleReader m_reader;

        bool m_incremental;
        int  m_steps;
        int  m_totalSteps;
};


#endif // AMAROK_SCANCONTROLLER_H

