// 
//   Copyright (C) 2004 Free Software Foundation, Inc.
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtkextra/gtkplot.h>
#include <gtkextra/gtkplot3d.h>
#include <gtkextra/gtkplotdata.h>
#include <gtkextra/gtkplotsurface.h>
#include <gtkextra/gtkplotcsurface.h>
#include <gtkextra/gtkplotcanvas.h>
#include <gtkextra/gtkplotps.h>
#include <gtkextra/gtkplotprint.h>
#include <gnome.h>

gdouble
function(GtkPlot *plot, GtkPlotData *data,
         gdouble x, gdouble y, gboolean *err)
{
  gdouble z;
  *err = FALSE;                     
  z = cos(((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5))*24) / 4. + .5;
  /* z = (x*x + y*y) / 9.0; */
  
  return z;
}


int
main(int argc, char *argv[])
{
  GtkWidget *plotwin;
  
  gtk_init(&argc,&argv);
  
  plotwin = create_plotwin();
  
  exit(0);
}
