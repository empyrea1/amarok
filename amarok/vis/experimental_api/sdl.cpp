// Author: Max Howell <max.howell@methylblue.com>, (C) 2004
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include "./sdl.h"

using namespace amaroK;


Vis::SDL::Basic::Basic( DataType dt, bool notify, uint fps )
  : Vis::Implementation<SDL_Surface>( dt, notify, fps )
{}

void
Vis::SDL::Basic::init( uint w, uint h, Uint32 flags ) //virtual
{
    //TODO use exceptions, don't return values
    //TODO should we make the user call init() as well as exec()?

    if( SDL_Init( SDL_INIT_VIDEO ) == 0 )
    {
        std::atexit( SDL_Quit ); //will cleanup before we exit

        m_surface = SDL_SetVideoMode( w, h, 0, flags );

        if( m_surface == NULL )
        {
            std::cerr << "Unable to set video mode (" << SDL_GetError() << ")\n";
        }
    }
    else std::cerr << "Unable to initialise SDL (" << SDL_GetError() << ")\n";
}

void
Vis::SDL::Basic::drawPixel( SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B )
{
    //TODO if you call this 640x480 times you are wasting a lot of cycles on the if blocks!
    //TODO calculate this when the screen changes in this class, then drawPixel can be much quicker

    Uint32 color = SDL_MapRGB( screen->format, R, G, B );

    switch( screen->format->BytesPerPixel )
    {
    case 1: // Assuming 8-bpp
    {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;

        break;
    }

    case 2: // Probably 15-bpp or 16-bpp
    {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;

        break;
    }

    case 3: // Slow 24-bpp mode, usually not used
    {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;

        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
            bufp[0] = color;
            bufp[1] = color >> 8;
            bufp[2] = color >> 16;

        } else {

            bufp[2] = color;
            bufp[1] = color >> 8;
            bufp[0] = color >> 16;
        }

        break;
    }

    case 4: // Probably 32-bpp
    {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;

        break;
    }
    }
}


Vis::SDL::Convenience::Convenience( DataType dt, bool notification, uint fps )
  : SDL::Basic( dt, notification, fps )
{}

void
Vis::SDL::Convenience::render( SDL_Surface *screen )
{
    if ( SDL_MUSTLOCK(screen) )
    {
        if ( SDL_LockSurface(screen) < 0 )
        {
            return;
        }
    }

    doRender( screen );

    if ( SDL_MUSTLOCK(screen) )
    {
        SDL_UnlockSurface(screen);
    }

    SDL_Flip(screen);
}
