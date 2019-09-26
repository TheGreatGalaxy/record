#include <stdlib.h> 
#include <stdio.h> 
#include <iostream>
#include <X11/Xlib.h> 
#include <time.h>
#include <unistd.h>
// #include <X11/Xh> 
#include <X11/extensions/Xcomposite.h> 
#include <X11/extensions/Xrender.h> 
//g++ capture_window.cpp -l/usr/lib/x86_64-linux-gnu/libX11.so -l/usr/lib/x86_64-linux-gnu/libXcomposite.so -l/usr/lib/x86_64-linux-gnu/libXrender.so

int main(int argc, char const *argv[])
{

 Display *display = XOpenDisplay (NULL); 
 XID xid = atoi(argv[1]);
//  XID xid = 67109443;
 std::cout<<"xid: "<<xid <<std::endl;
 // xdotool search --name "World of Warcraft" | head -1 
 // Check if Composite extension is enabled 
 int event_base_return; 
 int error_base_return; 
 if (XCompositeQueryExtension (display, &event_base_return, &error_base_return)) 
 printf ("COMPOSITE IS ENABLED!\n"); 
 // Requests the X server to direct the hierarchy starting at window to off-screen storage 
 XCompositeRedirectWindow (display, xid, CompositeRedirectAutomatic); 
 // Preventing the backing pixmap from being freed when the window is hidden/destroyed 
 // If you want the window contents to still be available after the window has been destroyed, 
 // or after the window has been resized (but not yet redrawn), you can increment the backing 
 // pixmaps ref count to prevent it from being deallocated. 
 Pixmap pixmap = XCompositeNameWindowPixmap (display, xid); 
 // Get window attributes 
 XWindowAttributes attr; 
 Status s = XGetWindowAttributes (display, xid, &attr); 
 if (s == 0) 
   printf ("Fail to get window attributes!\n"); 
 // Extract the data 
 XRenderPictFormat *format = XRenderFindVisualFormat (display, attr.visual); 
 std::cout<<"attr: "<<attr.width<<" "<<attr.height<<" "<<attr.depth<<std::endl;
 int width = attr.width; 
 int height = attr.height; 
 int depth = attr.depth; 
 // What we need to do now is to create an XRender Picture for the window, 
 // which we'll need to draw it with the Render extension. 
 // A picture is a basically a handle to a server side struct with some 
 // additional information about a drawable (in this case a window), 
 // such as its format, which clipping region should be used when 
 // drawing it (if any), whether it should be tiled etc. 
 XRenderPictureAttributes pa; 
 pa.subwindow_mode = IncludeInferiors; 
 Picture picture = XRenderCreatePicture (display, xid, format, CPSubwindowMode, &pa); 
 // We now have all the information we need in order to be able to draw the window 
 // using the Xrender extension, and we've created and prepared a source picture 
 // for the window for this purpose. 
 // The Xrender function we'll use to draw the window is XRenderComposite(). 
 Display *display1 = XOpenDisplay (NULL); 
 if(display1==NULL){
   printf("cannot open display1!\n");
 }
 int s = DefaultScreen(display1);
 Window w = XCreateSimpleWindow(display1,RootWindow(display1,s),10,10,720,480,0,
                                  BlackPixel(display1,s),WhitePixel(display1,s));



 return 0; 
}