// 
//   Copyright (C) 2003 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

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

GdkPixmap *pixmap=NULL;
GtkWidget **plots;
GtkWidget **buttons;
GtkPlotData *dataset[5];
gint nlayers = 0;

#define MAXNODES 50000

extern gdouble function(GtkPlot *plot, GtkPlotData *data,
                        gdouble x, gdouble y, gboolean *err);


GtkWidget *
new_layer(GtkWidget *canvas)
{
 gchar label[10];

 nlayers++;

 buttons = (GtkWidget **)g_realloc(buttons, nlayers * sizeof(GtkWidget *));
 plots = (GtkWidget **)g_realloc(plots, nlayers * sizeof(GtkWidget *));

 sprintf(label, "%d", nlayers);
 
 buttons[nlayers-1] = gtk_toggle_button_new_with_label(label);
/* gtk_button_set_relief(GTK_BUTTON(buttons[nlayers-1]), GTK_RELIEF_NONE);
*/
 gtk_widget_set_usize(buttons[nlayers-1], 20, 20);
 gtk_fixed_put(GTK_FIXED(canvas), buttons[nlayers-1], (nlayers-1)*20, 0);
 gtk_widget_show(buttons[nlayers-1]);

 plots[nlayers-1] = gtk_plot3d_new_with_size(NULL, .70, .70);

 gtk_widget_show(plots[nlayers-1]);

 return plots[nlayers-1];
}

void
rotate_x(GtkWidget *button, gpointer data)
{
 GtkPlot3D *active_plot;

 active_plot = GTK_PLOT3D(gtk_plot_canvas_get_active_plot(GTK_PLOT_CANVAS(data)));

 gtk_plot3d_rotate_x(active_plot, 10.);

 gtk_plot_canvas_paint(GTK_PLOT_CANVAS(data));
 gtk_plot_canvas_refresh(GTK_PLOT_CANVAS(data));
}

void
rotate_y(GtkWidget *button, gpointer data)
{
 GtkPlot3D *active_plot;

 active_plot = GTK_PLOT3D(gtk_plot_canvas_get_active_plot(GTK_PLOT_CANVAS(data)));

 gtk_plot3d_rotate_y(active_plot, 10.);

 gtk_plot_canvas_paint(GTK_PLOT_CANVAS(data));
 gtk_plot_canvas_refresh(GTK_PLOT_CANVAS(data));
}

void
rotate_z(GtkWidget *button, gpointer data)
{
 GtkPlot3D *active_plot;

 active_plot = GTK_PLOT3D(gtk_plot_canvas_get_active_plot(GTK_PLOT_CANVAS(data)));

 gtk_plot3d_rotate_z(active_plot, 10.);

 gtk_plot_canvas_paint(GTK_PLOT_CANVAS(data));
 gtk_plot_canvas_refresh(GTK_PLOT_CANVAS(data));
}

void
open_activate (GtkMenuItem *menuitem, gpointer user_data)
{
}

void
save_activate (GtkMenuItem *menuitem, gpointer user_data)
{
}

void
saveas_activate (GtkMenuItem *menuitem, gpointer user_data)
{
}

void
print_activate (GtkMenuItem *menuitem, gpointer user_data)
{
}

void
close_activate (GtkMenuItem *menuitem, gpointer user_data)
{
}

void
exit_activate (GtkMenuItem *menuitem, gpointer user_data)
{
  gtk_main_quit();
}

void
stub_activate (GtkMenuItem *menuitem, gpointer user_data)
{
  g_print("Stub routine called, doing nothing...");
}

static GnomeUIInfo File_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_OPEN_ITEM    (open_activate,   NULL),
  GNOMEUIINFO_MENU_SAVE_ITEM    (save_activate,   NULL),
  GNOMEUIINFO_MENU_SAVE_AS_ITEM (saveas_activate, NULL),
  GNOMEUIINFO_MENU_PRINT_ITEM   (print_activate,  NULL),
  GNOMEUIINFO_MENU_CLOSE_ITEM   (close_activate,  NULL),
  GNOMEUIINFO_MENU_EXIT_ITEM    (exit_activate,   NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo X_beam_irradiation_uiinfo[] =
{
  {
    GNOME_APP_UI_ITEM, "Beam Irradiation",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "Diffuse Irradiation",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "Ambient Temperature",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "Sun Elevation",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "AOI",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "Wind Speed",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, "Altitude",
    NULL,
    (gpointer) stub_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo x_axis_menu_uiinfo[] =
{
  {
    GNOME_APP_UI_RADIOITEMS, NULL, NULL, X_beam_irradiation_uiinfo,
    NULL, NULL, GNOME_APP_PIXMAP_NONE, NULL, 0,
    (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar_uiinfo[] =
{
  GNOMEUIINFO_MENU_FILE_TREE (File_menu_uiinfo),
  {
    GNOME_APP_UI_SUBTREE, "X Axis",
    NULL,
    x_axis_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
#if 0
  {
    GNOME_APP_UI_SUBTREE, "Y Axis",
    NULL,
    y_axis_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_SUBTREE, "Z Axis",
    NULL,
    z_axis_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
#endif
  GNOMEUIINFO_END
};

GtkWidget *
create_plotwin(void)
{
  GtkWidget *main_window;
  GtkWidget *vbox1;
  GtkWidget *scroll_window;
  GtkWidget *menubar;

  GtkWidget *active_plot;
  GtkWidget *canvas;
  GtkWidget *button;
  GtkWidget *surface;
  gdouble *x,*y,*z;
  gint page_width, page_height;
  gfloat scale = 1.;
#if 0
  gint cnt= 0;
  char buffer[1000];
  gdouble xmin=1e99;
  gdouble xmax=-1e99;
  gdouble ymin=1e99;
  gdouble ymax=-1e99;
  gdouble zmin=1e99;
  gdouble zmax=-1e99;
  gdouble dx,dy,dz;
#endif
  
  page_width = GTK_PLOT_LETTER_W * scale;
  page_height = GTK_PLOT_LETTER_H * scale;
  
  main_window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(main_window), "GtkPlot3D Demo");
  gtk_widget_set_usize(main_window,550,650);
  gtk_container_border_width(GTK_CONTAINER(main_window),0);
  
  gtk_signal_connect (GTK_OBJECT (main_window), "destroy",
                      GTK_SIGNAL_FUNC (exit_activate), NULL);
  
  vbox1=gtk_vbox_new(FALSE,0);
  gtk_container_add(GTK_CONTAINER(main_window),vbox1);

  menubar = gtk_menu_bar_new ();

  gtk_widget_ref (menubar);
  gtk_object_set_data_full (GTK_OBJECT (main_window), "menubar", menubar,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (menubar);
  gtk_box_pack_start (GTK_BOX (vbox1), menubar, FALSE, FALSE, 0);


  //  gnome_app_fill_menu (GTK_MENU_SHELL (menubar), menubar_uiinfo, NULL, FALSE, 0);

  
  scroll_window=gtk_scrolled_window_new(NULL, NULL);
  gtk_container_border_width(GTK_CONTAINER(scroll_window),0);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_window),
                                 GTK_POLICY_ALWAYS,GTK_POLICY_ALWAYS);
  gtk_box_pack_start(GTK_BOX(vbox1),scroll_window, TRUE, TRUE,0);
  
  canvas = gtk_plot_canvas_new(page_width, page_height, 1.);
  GTK_PLOT_CANVAS_SET_FLAGS(GTK_PLOT_CANVAS(canvas), GTK_PLOT_CANVAS_DND_FLAGS);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll_window), canvas);

  active_plot = new_layer(canvas);

  gtk_plot_canvas_add_plot(GTK_PLOT_CANVAS(canvas),
                           GTK_PLOT(active_plot), .10, .06);
  
  gtk_plot3d_axis_set_minor_ticks(GTK_PLOT3D(active_plot), GTK_PLOT_AXIS_X, 1);
  gtk_plot3d_axis_set_minor_ticks(GTK_PLOT3D(active_plot), GTK_PLOT_AXIS_Y, 1);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot), 
                             GTK_PLOT_SIDE_XY, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot), 
                             GTK_PLOT_SIDE_XZ, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot), 
                             GTK_PLOT_SIDE_YX, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot), 
                             GTK_PLOT_SIDE_YZ, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot), 
                             GTK_PLOT_SIDE_ZX, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  gtk_plot3d_axis_show_ticks(GTK_PLOT3D(active_plot),
                             GTK_PLOT_SIDE_ZY, 
                             GTK_PLOT_TICKS_OUT, GTK_PLOT_TICKS_OUT);
  
  x= y= z= NULL;
  surface = gtk_plot_surface_new_function((GtkPlotFunc3D) function);
  gtk_plot_surface_set_xstep(GTK_PLOT_SURFACE(surface), .025);
  gtk_plot_surface_set_ystep(GTK_PLOT_SURFACE(surface), .025);
  gtk_plot_data_set_legend(GTK_PLOT_DATA(surface), "cos ((r-r\\s0\\N)\\S2\\N)");
  gtk_plot_add_data(GTK_PLOT(active_plot), GTK_PLOT_DATA(surface));
  
  gtk_plot3d_autoscale(GTK_PLOT3D(active_plot));
  gtk_widget_show(surface);
  
  button = gtk_button_new_with_label("Rotate X");
  gtk_fixed_put(GTK_FIXED(canvas), button, 80, 0);
  
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
                     GTK_SIGNAL_FUNC(rotate_x), canvas);
  
  button = gtk_button_new_with_label("Rotate Y");
  gtk_fixed_put(GTK_FIXED(canvas), button, 160, 0);
  
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
                     GTK_SIGNAL_FUNC(rotate_y), canvas);
  
  button = gtk_button_new_with_label("Rotate Z");
  gtk_fixed_put(GTK_FIXED(canvas), button, 240, 0);
  
  gtk_signal_connect(GTK_OBJECT(button), "clicked",
                     GTK_SIGNAL_FUNC(rotate_z), canvas);
  
  gtk_widget_show_all(main_window);
  
  gtk_plot_canvas_export_ps_with_size(GTK_PLOT_CANVAS(canvas), "demo3d.ps", 
                                      0, 0, GTK_PLOT_PSPOINTS,
                                      GTK_PLOT_LETTER_W, GTK_PLOT_LETTER_H);
  gtk_main();
  
  return(0);
}
