#include <QApplication>
#include <QDebug>
#include <X11/Xlib.h>
#include <QPaintDevice>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xrender.h>
#include <X11/extensions/Xdamage.h>

#include <QPixmap>
#include <QWidget>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    // Picture frontBuffer;
    // XRenderPictFormat *format;
    // Window rootWindow;
    // int depth;

    // Display *dpy = XOpenDisplay( getenv("DISPLAY") );
    // rootWindow = XRootWindow( dpy, XDefaultScreen( dpy ) );

    // depth = DefaultDepth( dpy, DefaultScreen(dpy) );

    // // Redirect all the windows
    // XCompositeRedirectSubwindows( dpy, rootWindow, CompositeRedirectManual );

    // // Get the format
    // format = XRenderFindVisualFormat( dpy, DefaultVisual( dpy, DefaultScreen(dpy) ) );

    // XRenderPictureAttributes pa;
    // pa.subwindow_mode = IncludeInferiors;

    // // Creating front buffer
    // frontBuffer = XRenderCreatePicture( dpy, rootWindow, format, CPSubwindowMode, &pa );

    // uint nwindows;
    // Window root_return, parent_return, *windows;

    // XQueryTree( dpy, rootWindow, &root_return,
    //                 &parent_return, &windows, &nwindows );

    // for ( uint i = 0; i < nwindows; i++ ) {
    //         XWindowAttributes attr;
    //         if ( !XGetWindowAttributes( dpy, windows[i], &attr ) )
    //                 continue;

    //         Pixmap pix = XCompositeNameWindowPixmap( dpy, windows[i] );

    //         Picture pic = XRenderCreatePicture( dpy, pix, format, 0, 0 );
               
    //         QPixmap pixmap(540, 900);
    //         XRenderComposite( dpy, PictOpSrc, pic, None, pixmap.x11PictureHandle(),
    //                                       0, 0, 0, 0, 0 , 0, 540, 900 );
    //         pixmap.save( QString::number( i )+".png", "PNG" );
    //     }
    // }
    // XFree( windows );
    // return app.exec();
}