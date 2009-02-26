/***************************************************************************
 *   Copyright (c) 2009  Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>    *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#include "MultiTrack.h"

#include "Debug.h"
#include "MultiSourceCapabilityImpl.h"

namespace Meta {

MultiTrack::MultiTrack( PlaylistPtr playlist )
    : QObject()
    , Track()
    , m_playlist( playlist )
    , m_index( 0 )
{
    DEBUG_BLOCK
    debug() << "playlist size: " << m_playlist->tracks().count();
    m_currentTrack = m_playlist->tracks()[ 0 ];
}


MultiTrack::~MultiTrack()
{
}


KUrl Meta::MultiTrack::first()
{
    m_index = 0;
    if ( m_playlist->tracks().count() > m_index ) {
        m_currentTrack = m_playlist->tracks()[ m_index ];
        return m_currentTrack->playableUrl();
    }

    return KUrl();
}

KUrl Meta::MultiTrack::next()
{
    m_index++;
    if ( m_playlist->tracks().count() > m_index ){
        m_currentTrack = m_playlist->tracks()[ m_index ];
        return m_currentTrack->playableUrl();
    }

    return KUrl();
}


int Meta::MultiTrack::current()
{
    return m_index;
}

QStringList Meta::MultiTrack::tracks()
{
    QStringList trackNames;
    foreach ( TrackPtr track, m_playlist->tracks() )
    {
        trackNames << track->prettyName();
    }

    return trackNames;
}

bool Meta::MultiTrack::hasCapabilityInterface(Meta::Capability::Type type) const
{
    return type == Meta::Capability::MultiSource;
}

Meta::Capability * Meta::MultiTrack::asCapabilityInterface(Meta::Capability::Type type)
{
    switch( type )
    {
        case Meta::Capability::MultiSource:
            return new MultiSourceCapabilityImpl( this );
        default:
            return 0;
    }
}

}

#include "MultiTrack.moc"

