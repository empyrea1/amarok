/****************************************************************************************
 * Copyright (c) 2009 Casey Link <unnamedrambler@gmail.com>                             *
 * Copyright (c) 2009 Nikolaj Hald Nielsen <nhn@kde.org>                                *
 * Copyright (c) 2009 Mark Kretschmann <kretschmann@kde.org>                            *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 2 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#ifndef LASTFMTREEMODEL_H
#define LASTFMTREEMODEL_H

#include "core/meta/Meta.h"
#include "WeightedStringList.h"

#include <QAbstractItemModel>

#include <User.h>

class QNetworkReply;

namespace LastFm
{
enum Type
{
    Root = 0,
    MyRecommendations,
    PersonalRadio,
    MixRadio,
    NeighborhoodRadio,
    //         RecentlyPlayed,
    //         RecentlyLoved,
    //         RecentlyBanned,
    TopArtists,
    MyTags,
    Friends,
    Neighbors,

    //         History,

    RowCount,

    MyTagsChild,
    FriendsChild,
    NeighborsChild,
    ArtistsChild,
    RecentlyBannedTrack,
    RecentlyPlayedTrack,
    RecentlyLovedTrack,
    HistoryStation,

    UserChildPersonal,
    UserChildNeighborhood,

    TypeUnknown
};

enum Role
{
    StationUrlRole = Qt::UserRole,
    UrlRole,
    TrackRole,
    TypeRole
};

enum SortOrder
{
    MostWeightOrder,
    AscendingOrder,
    DescendingOrder
};


}

class LastFmTreeItem;
class KUrl;
class WsReply;


class LastFmTreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit LastFmTreeModel ( const QString &username, QObject *parent = 0 );
    ~LastFmTreeModel();

    QVariant data ( const QModelIndex &index, int role ) const;
    Qt::ItemFlags flags ( const QModelIndex &index ) const;
    QVariant headerData ( int section, Qt::Orientation orientation,
                          int role = Qt::DisplayRole ) const;
    QModelIndex index ( int row, int column,
                        const QModelIndex &parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex &index ) const;
    int rowCount ( const QModelIndex &parent = QModelIndex() ) const;
    int columnCount ( const QModelIndex &parent = QModelIndex() ) const;
    int avatarSize () const;
    void prepareAvatar ( QPixmap& avatar, int size );

    void sortTags ( WeightedStringList tagsToSort, Qt::SortOrder sortOrder );
    void sortTags ( Qt::SortOrder sortOrder );

    virtual QMimeData* mimeData( const QModelIndexList &indices ) const;

private slots:
    void onAvatarDownloaded( const QString& username, QPixmap );
    void slotAddNeighbors();
    void slotAddFriends();
    void slotAddTags();
    void slotAddTopArtists();

private:
    void setupModelData( LastFmTreeItem *parent );
    void emitRowChanged( int parent, int child = -1 );

    LastFmTreeItem *m_rootItem;
    LastFmTreeItem *m_myTags;
    LastFmTreeItem *m_myFriends;
    LastFmTreeItem *m_myNeighbors;
    LastFmTreeItem *m_myTopArtists;

    QString m_userName;
    lastfm::User m_user;

    QStringList m_friends;
    QStringList m_neighbors;
    WeightedStringList m_tags;

    QHash<QString, QIcon> m_avatars;
    int m_avatarSize;

    QMap< QString, QNetworkReply* > m_jobs;

    QIcon avatar( const QString &username, const KUrl &avatarUrl ) const;
    QString mapTypeToUrl ( LastFm::Type type, const QString &key = "" );

    void appendUserStations ( LastFmTreeItem* item, const QString& user );
};

class LastFmTreeItem
{
public:
    LastFmTreeItem ( const LastFm::Type &type, const QVariant &data, LastFmTreeItem *parent = 0 );
    LastFmTreeItem ( const QString &url, const LastFm::Type &type, const QVariant &data, LastFmTreeItem *parent = 0 );
    explicit LastFmTreeItem ( const LastFm::Type &type, LastFmTreeItem *parent = 0 );
    LastFmTreeItem ( const QString &url, const LastFm::Type &type, LastFmTreeItem *parent = 0 );
    ~LastFmTreeItem();

    void appendChild ( LastFmTreeItem *child );

    LastFmTreeItem *child ( int row );
    int childCount() const;
    int columnCount() const;
    QVariant data () const;
    int row() const;
    LastFmTreeItem *parent();
    Meta::TrackPtr track() const;
    LastFm::Type type() const
    {
        return mType;
    }

    KUrl avatarUrl() const
    {
        return avatar;
    }
    void setAvatarUrl( const KUrl &url )
    {
        avatar = url;
    }

private:
    QList<LastFmTreeItem*> childItems;
    LastFm::Type mType;
    LastFmTreeItem *parentItem;
    QVariant itemData;
    QString mUrl;
    KUrl avatar;
};

#endif
