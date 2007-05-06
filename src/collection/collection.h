/*
 *  Copyright (c) 2007 Maximilian Kossick <maximilian.kossick@googlemail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef AMAROK_COLLECTION_H
#define AMAROK_COLLECTION_H

#include "amarok.h"
#include "amarok_export.h"
#include "plugin/plugin.h"
#include "querymaker.h"

#include <QObject>
#include <QString>

class Collection;

class AMAROK_EXPORT CollectionFactory : public QObject, public Amarok::Plugin
{
    Q_OBJECT
    public:
        CollectionFactory();
        virtual ~CollectionFactory();

        virtual void init() = 0;

    signals:
        void newCollection( Collection *newCollection );

};

class AMAROK_EXPORT Collection : public QObject
{
    Q_OBJECT
    public:

        Collection();
        virtual ~Collection();

        virtual QueryMaker * queryBuilder() = 0;
        virtual void startFullScan() { }

        virtual QString collectionId() const = 0;
        virtual QString prettyName() const = 0;

        virtual bool isSqlDatabase() const;
        virtual int sqlDatabasePriority() const;
        virtual QStringList query( const QString &query );
        virtual int insert( const QString &statement, const QString &table );

    signals:
        void remove();
};

#endif /* AMAROK_COLLECTION_H */
