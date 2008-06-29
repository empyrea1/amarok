/***************************************************************************
 *   Copyright (c) 2007  Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>    *
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

#ifndef AMAROKSERVICEBASE_H
#define AMAROKSERVICEBASE_H

#include "../collectionbrowser/CollectionTreeItem.h"
#include "../collectionbrowser/SingleCollectionTreeItemModel.h"
#include "Amarok.h"
#include "InfoParserBase.h"
#include "ServiceCollectionTreeView.h"
#include "ServiceMetaBase.h"
#include "amarok_export.h"
#include "collection/CollectionManager.h"
#include "plugin/plugin.h"

#include <KPluginInfo>
#include <KVBox>
#include <khtml_part.h>

#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QSplitter>

class ServiceBase;
class SearchWidget;
class KMenuBar;

/**
A virtual base class for factories for creating and handling the different types of service plugins

@author Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>
 */
class AMAROK_EXPORT ServiceFactory : public QObject, public Amarok::Plugin, public TrackProvider
{
    Q_OBJECT
    public:
        /**
         * Constructor.
         */
        ServiceFactory();

        /**
         * Destructor.
         */
        virtual ~ServiceFactory();

        /**
         * Initialize the service plugins of this type. Reimplemented by subclasses.
         */
        virtual void init() = 0;

        /**
         * Get the name of this service type. Reimplemented by subclasses.
         * @return The name.
         */
        virtual QString name() = 0;

        /**
         * Get a KConfigGroup object containing the config for this tyoe of service. Reimplemented by subclasses.
         * @return
         */
        virtual KConfigGroup config() = 0;

        /**
         * Get a KPluginInfo object containing the info about this plugin. Reimplemented by subclasses.
         * @return The plugin info.
         */
        virtual KPluginInfo info() = 0;

        /**
         * Get a best guess if a service of the type generated by this factory will be likely to be able to provide tracks
         * for a given url. This is needed in order to allow on.demand loading of service plugins to handle a url. Reimplemented by subclasses.
         * @param url The url to test.
         * @return A bool representing whether the ServiceFactory believes that a service of this kind can process the given url.
         */
        virtual bool possiblyContainsTrack( const KUrl &url ) const { Q_UNUSED( url ); return false; }

        /**
         * Attempt to create a Meta::Track object from a given url. This method is meant as a proxy that will forward this call to one or more
         * services managed by this factory. If init has not been called ( no services of this kind has been loaded ) they can now be loaded on
         * demand.
         * @param url The url to test.
         * @return A Meta::TrackPtr based one the url, or empty if nothing was known about the url.
         */
        virtual Meta::TrackPtr trackForUrl( const KUrl &url );

        /**
         * Clear the list of active services created by this factory. Used when unloading services.
         */
        void clearActiveServices();

    signals:
        /**
         * This signal is emmited whenever a new service has been loaded.
         * @param newService The service that has been loaded.
         */
        void newService( class ServiceBase *newService );

    protected:
        QList<ServiceBase *> m_activeServices;
};


/**
A composite widget used as a base for building service browsers. It contains a home button ( to return to the list of services ), a name label, a tree view, grouping and filtering widgets and other conviniences that handels much of the layout of a new service. Some of these items can be shown or hidden as needed.

@author Nikolaj Hald Nielsen <nhnFreespirit@gmail.com>
*/
class AMAROK_EXPORT ServiceBase : public KVBox
{
    Q_OBJECT

public:

     /**
      * Constructor.
      */
    ServiceBase( const QString &name );

    /**
     * Destructor.
     */
    ~ServiceBase();

    /**
     * Get the name of this service.
     * @return The name of the service.
     */
    QString getName();

    /**
     * Set a short description string for this service. This string is used to describe the service in the service browser.
     * @param shortDescription The description.
     */
    void setShortDescription( const QString &shortDescription );

    /**
     * Get the short description of this service.
     * @return The short description.
     */
    QString getShortDescription();

    /**
     * Set a long description of the service. This is for allowing users to get more detailed info a about a service.
     * @param longDescription The long description.
     */
    void setLongDescription( const QString &longDescription );

    /**
     * Get the long description of this service.
     * @return The long description.
     */
    QString getLongDescription();

    /**
     * Set the icon that will be used to identify this service.
     * @param icon The icon to use.
     */
    void setIcon( const QIcon &icon );

    /**
     * Get the icon of this service.
     * @return The icon
     */
    QIcon getIcon();

    /**
     * Set the SingleCollectionTreeItemModel that will be used to populate the tree view.
     * @param model The model.
     */
    void setModel( SingleCollectionTreeItemModel * model );

    /**
     * Get the model that is used for displaying items in the tree view.
     * @return The model.
     */
    SingleCollectionTreeItemModel * getModel();

    /**
     * Set if it should be possible to add the tracks shown in the tree view to the playlist. This method is a bit of a hack and might be removed!
     * @param playable Are tracks playlable.
     */
    void setPlayableTracks( bool playable );

    /**
     * Set the info parser that will be used to show information about selected items in the service info context applet.
     * @param infoParser The info parser to use.
     */
    void setInfoParser( InfoParserBase * infoParser );

    /**
     * Get the info parser used to show information about selected items in the service info context applet.
     * @return The info parser.
     */
    InfoParserBase * infoParser();

    /**
     * Return the Collection used by this service.
     * @return The collection.
     */
    virtual Collection * collection() = 0;

    /**
     * Do expensive initialization. This method is called when the service is first shown.
     */
    virtual void polish() = 0;

    /**
     * ??????
     * @return 
     */
    virtual bool updateContextView() { return false; }

    /**
     * Apply a filter to the tree view.
     * @param filter The filter to apply.
     */
    void setFilter( const QString &filter );

    /**
     * Returns a list of the messages that the current service accepts. Default impelentation does not
     * accept any.
     * @return A string containing a description of accepted messages.
     */
    virtual QString messages();

    /**
     * Send a message to this service. Default implementation returns an error as no messages are
     * accepted
     * @param message The message to send to the service
     * @return The reply to the message
     */
    virtual QString sendMessage( const QString &message );

    /**
     * Returns whether the service is ready or not.
     * @return true if the status is ready, false if it is not ready
     */
    bool serviceReady() const;
    //virtual void reset() = 0;

public slots:
    //void treeViewSelectionChanged( const QItemSelection & selected );
    /**
     * New info should be shown in the service info applet ( if present ).
     * @param infoHtml The html formnatted info to show.
     */
    void infoChanged ( const QString &infoHtml );

    /**
     * Set sorting in the tree view to be "Artist-Album".
     */
    void sortByArtistAlbum();

signals:
    /**
     * Signal emitted when the service wants to be hidden and the service browser list shown instead, for instance when the "Home" button is clicked.
     */
    void home();

    /**
     * Signal emitted when the selection in the tree view has changed ( and is only a single item ).
     * @param item The selected item
     */
    void selectionChanged( CollectionTreeItem * );

protected slots:
    /**
     * Slot called when the home button has been clicked
     */
    void homeButtonClicked();

    /**
     * Slot called when an intem in the tree view has been activated
     * @param index The index of the activated item
     */
    void itemActivated ( const QModelIndex & index );

     /**
     * Slot called when the selection in the tree view has changed ( and is only a single item ).
     * @param item The selected item
     */
    void itemSelected( CollectionTreeItem * item  );

        /**
     * Set sorting in the tree view to be "Artist".
         */
    void sortByArtist();

    /**
     * Set sorting in the tree view to be "Album".
     */
    void sortByAlbum();

    /**
     * Set sorting in the tree view to be "Genre-Artist".
     */
    void sortByGenreArtist();

    /**
     * Set sorting in the tree view to be "Genre-Artist-Album".
     */
    void sortByGenreArtistAlbum();

protected:
    /**
     * Generate info to show in the service info applet. useful for showing initial info before any items are selected and hence
     * trigger the info parser.
     * @param html 
     */
    virtual void generateWidgetInfo( const QString &html = QString() ) const;

    static ServiceBase *s_instance;
    ServiceCollectionTreeView *m_contentView;

    QPushButton *m_homeButton;

    KVBox       *m_topPanel;
    KVBox       *m_bottomPanel;
    bool         m_polished;

    QString      m_name;
    QString      m_shortDescription;
    QString      m_longDescription;
    QIcon        m_icon;

    bool m_serviceready;

    KUrl::List   m_urlsToInsert;

    InfoParserBase * m_infoParser;

    KMenuBar *m_menubar;
    QMenu *m_filterMenu;
    SearchWidget * m_searchWidget;

    //void addToPlaylist( CollectionTreeItem * item );

private: // need to move stuff here
     SingleCollectionTreeItemModel * m_model;
     QSortFilterProxyModel * m_filterModel;
};


#endif
