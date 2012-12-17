/****************************************************************************************
 * Copyright (c) 2007 Nikolaj Hald Nielsen <nhn@kde.org>                                *
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

#ifndef AMAROKSERVICEBASE_H
#define AMAROKSERVICEBASE_H

#include "browsers/BrowserCategory.h"
#include "core/support/Amarok.h"
#include "core/support/PluginFactory.h"
#include "InfoParserBase.h"
#include "ServiceCollectionTreeView.h"
#include "ServiceMetaBase.h"
#include "amarok_export.h"
#include "core-impl/collections/support/CollectionManager.h"
#include "core-impl/meta/proxy/MetaProxy.h"
#include "widgets/PrettyTreeView.h"

#include <KPluginInfo>
#include <KVBox>

#include <QAbstractItemModel>
#include <QPushButton>
#include <QQueue>
#include <QSortFilterProxyModel>
#include <QSplitter>

class ServiceBase;
class SearchWidget;
class KMenuBar;
/**
A virtual base class for factories for creating and handling the different types of service plugins

@author Nikolaj Hald Nielsen <nhn@kde.org>
 */
class AMAROK_EXPORT ServiceFactory : public Plugins::PluginFactory, public Collections::TrackProvider
{
    Q_OBJECT
    public:
        /**
         * Constructor.
         */
        ServiceFactory( QObject *parent, const QVariantList &args );

        /**
         * Destructor.
         */
        virtual ~ServiceFactory();

        /**
         * Get the name of this service type. Reimplemented by subclasses.
         * @return The name.
         */
        virtual QString name() = 0;

        /**
         * Get a KConfigGroup object containing the config for this type of service. Reimplemented by subclasses.
         * @return
         */
        virtual KConfigGroup config() = 0;

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

        QList<ServiceBase *> activeServices() { return m_activeServices.toList(); }

    public slots:
        /**
         * The service is ready!
         */
        void slotServiceReady();

    signals:
        /**
         * This signal is emitted whenever a new service has been loaded.
         * @param newService The service that has been loaded.
         */
        void newService( ServiceBase *newService );

        /**
         * This signal is emitted whenever a service is removed. ServiceFactory deletes
         * the service in next event loop iteration.
         *
         * @param removedService The service that has been removed
         */
        void removeService( ServiceBase *newService );

    private slots:
        void slotNewService( ServiceBase *newService );
        void slotRemoveService( ServiceBase *service );

    private:
        QSet<ServiceBase *> m_activeServices;
        QQueue<MetaProxy::TrackPtr> m_tracksToLocate;
};


/**
A composite widget used as a base for building service browsers. It contains a home button ( to return to the list of services ), a name label, a tree view, grouping and filtering widgets and other conveniences that handle much of the layout of a new service. Some of these items can be shown or hidden as needed.

@author Nikolaj Hald Nielsen <nhn@kde.org>
*/
class AMAROK_EXPORT ServiceBase : public BrowserCategory
{
    Q_OBJECT

public:

     /**
      * Constructor.
      */
    ServiceBase( const QString &name, ServiceFactory* parent, bool useCollectionTreeView = true, const QString &m_prettyName = QString() );

    /**
     * Destructor.
     */
    ~ServiceBase();

    /**
     * Set the SingleCollectionTreeItemModel that will be used to populate the tree view.
     * @param model The model.
     */
    void setModel( QAbstractItemModel * model );

    /**
     * Get the model that is used for displaying items in the tree view.
     * @return The model.
     */
    QAbstractItemModel * model();

    /**
    * Set the SingleCollectionTreeItemModel that will be used to populate the tree view.
    * @param model The model.
    */
    void setView( QTreeView * model );

    /**
    * Get the model that is used for displaying items in the tree view.
    * @return The model.
    */
    QTreeView * view();

    /**
     * Set if it should be possible to add the tracks shown in the tree view to the playlist. This method is a bit of a hack and might be removed!
     * @param playable Are tracks playable.
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
    virtual Collections::Collection * collection() = 0;

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
     * Returns a list of the messages that the current service accepts. Default implementation does not
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

    /**
     * Returns the service's parent factory.
     * @return the service's Factory
     */
     ServiceFactory* parent() const;

     virtual QString filter() const;
     virtual QList<CategoryId::CatMenuId> levels() const;

public slots:
    //void treeViewSelectionChanged( const QItemSelection & selected );
    /**
     * New info should be shown in the service info applet ( if present ).
     * @param infoHtml The html formatted info to show.
     */
    void infoChanged ( const QString &infoHtml );

    /**
     * Set sorting in the tree view to be "Artist-Album".
     */
    void sortByArtistAlbum();

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

    void setLevels( const QList<CategoryId::CatMenuId> &levels );

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

    /**
     * Signal emitted when the service is ready to be used. You don't need to emit this
     * manually, just call setServiceReady() as appropriate.
     */
    void ready();

protected slots:
    /**
     * Slot called when an item in the tree view has been activated
     * @param index The index of the activated item
     */
    void itemActivated ( const QModelIndex & index );

     /**
     * Slot called when the selection in the tree view has changed ( and is only a single item ).
     * @param item The selected item
     */
    void itemSelected( CollectionTreeItem * item  );

protected:
    /**
     * Generate info to show in the service info applet. useful for showing initial info before any items are selected and hence
     * trigger the info parser.
     * @param html
     */
    virtual void generateWidgetInfo( const QString &html = QString() ) const;

    /**
     * sets serviceReady() and emits a signal ready() as appropriate.
     */
    void setServiceReady( bool ready );

    static ServiceBase *s_instance;
    QTreeView *m_contentView;
    ServiceFactory *m_parentFactory;

    KVBox       *m_topPanel;
    KVBox       *m_bottomPanel;
    bool         m_polished;

    bool m_useCollectionTreeView;

    KUrl::List   m_urlsToInsert;

    InfoParserBase * m_infoParser;

    KMenuBar *m_menubar;
    QMenu *m_filterMenu;
    SearchWidget * m_searchWidget;

    //void addToPlaylist( CollectionTreeItem * item );

private: // need to move stuff here
    bool m_serviceready;

    QAbstractItemModel *m_model;
    QSortFilterProxyModel *m_filterModel;
};

#define AMAROK_EXPORT_SERVICE_PLUGIN(libname, classname) \
K_PLUGIN_FACTORY(factory, registerPlugin<classname>();) \
K_EXPORT_PLUGIN(factory("amarok_service_" #libname))\

#endif
