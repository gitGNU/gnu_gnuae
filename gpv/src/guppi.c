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
#include "support.h"

#include <libgnome/gnome-defs.h>
#include <libgnome/gnome-config.h>
#include <libgnomeui/gnome-init.h>

#include <libguppi/guppi-memory.h>
#include <libguppi/guppi-debug.h>
#include <libguppitank/guppi-tank.h>

extern GtkWidget *MainWindow;
extern GtkWidget *vbox1;
extern GtkWidget *menubar1;
extern GtkWidget *scrolledwindow1;
extern GtkWidget *viewport1;
extern GtkWidget *drawingarea1;
extern GtkWidget *statusbar1;
extern GtkWidget *fixed3;


const gint rows = 5, cols = 2;

const double data[] = { 1, 2, 3, 4, 5,
  3, 4, 7, 3, 1
};


const gchar *row_labels[] = { "One", "Two", "Three", "Four", "Five" };
const gchar *col_labels[] = { "Dogs", "Cats" };

const gchar *col_colors[] = { "red", "blue" };

static void
bar_click_cb (gint r, gint c, gpointer user_data)
{
  g_message ("Clicked on bar corresponding to row %d, column %d", r, c);
}

static void
legend_click_cb (gint c, gpointer user_data)
{
  g_message ("Clicked on legend box corresponding to column %d", c);
}

static void
delete_event_cb (GtkWidget *w, GdkEvent *ev, gpointer foo)
{
  gtk_widget_destroy (w);
  guppi_tank_exit ();
}

int
guppi_main (double *x_data, double *y_data, int data_size)
{
  gint i;
  GuppiObject *title_obj;
  GuppiObject *gobj;

  GtkWidget *win;
  GtkWidget *swin;
  GtkWidget *vbox;
  GtkWidget *w;
  GtkWidget *gwid;
  GtkWidget *fixed;

  //  gint data_size = 100;
  //  double *x_data;
  //  double *y_data;

  
  guppi_tank_init ();
  /*  guppi_set_verbosity (GUPPI_VERBOSE); */
  /*  guppi_set_verbosity (GUPPI_VERY_VERBOSE); */

#if 1
  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (win, 400, 300);
  gtk_window_set_title(GTK_WINDOW(win), "NEC Tables");

#if 0
  swin = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (win), swin);

  vbox = gtk_vbox_new (FALSE, 3);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), vbox);
#endif
#else
  /*  win = lookup_widget(GTK_WIDGET(MainWindow), "scrolledwindow1"); */
  /*  vbox = lookup_widget(GTK_WIDGET(MainWindow), "viewport1"); */
  vbox = vbox1;
  /*   vbox = lookup_widget(GTK_WINDOW_TOPLEVEL, "vbox1"); */
  win = MainWindow;
  /*  win = lookup_widget(GTK_WINDOW_TOPLEVEL, "MainWindow");
  fixed = lookup_widget(GTK_WIDGET(win), "fixed3");
  */
  fixed = fixed3;
#endif
  
  for (i=0; i<2; ++i)
    /* gtk_box_pack_start (GTK_BOX (vbox), 
			gtk_label_new ("foo"),
			FALSE, FALSE, 1); */
#if 0
  gobj = guppi_object_new ("barchart",
			      4 * 72, 3 * 72,
			      "data_rows", rows,
			      "data_columns", cols,
			      "data", data,
			      "y_axis_label", "Something here",
			      "x_axis_label", "Some number",
			      "rotate_y_axis_labels", FALSE,
			      "row_labels", row_labels,
			      "column_labels", col_labels,
			      "column_colors", col_colors,
			      "bar_callback1", bar_click_cb,
			      "legend_callback1", legend_click_cb, NULL);

  title_obj = guppi_object_new ("title",
				5 * 72, 3 * 72,
				"title", "PV Panel Performance",
				"subtitle",
				"Data from Sandia Labs Module Database",
				"subobject", pie_obj, NULL);
#else
  //  x_data = guppi_new0 (double, data_size);
  //  y_data = guppi_new0 (double, data_size);

#if 0                           /* demo data */
  for (i = 0; i < data_size; ++i) {
    double t = i > 0 ? y_data[i - 1] : 0.7;
    x_data[i] = i;
    y_data[i] = 4 * t * (1 - t);
  }
#else  /* Wire resistance */
  for (i = 0; i < 15; i++) {
    //    x_data[i] = awglist[i];
    //    y_data[i] = _table8[i].uncoated;
    
    //    g_print("x_data[%d] = %g\n", i, x_data[i]);
    //    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }
#endif

  gobj = guppi_object_new ("scatter",
			   4 * 72, 3 * 72,
			   "data_size", 15,
			   "x_data", x_data,
			   "x_axis_label", "AWG",
			   "y_data", y_data,
			   "y_axis_label", "Resistance",
			   "color_rgba", 0x0000ff80,
			   "marker", "filled circle", NULL);

  //  guppi_free (x_data);
  //  guppi_free (y_data);

  title_obj = guppi_object_new ("title",
				4 * 72, 3 * 72,
				"title", "Wire Resistance Chart",
				"subobject", gobj, NULL);

#endif
  w = guppi_object_build_widget (title_obj);

  guppi_unref (title_obj);

#if 1
  //  gtk_box_pack_start (GTK_BOX (vbox), w, FALSE, FALSE, 1);
#else
  gtk_container_remove(GTK_CONTAINER(vbox), w);
  gtk_container_add(GTK_CONTAINER(fixed), w);
  /*  gtk_container_add(GTK_CONTAINER(drawingarea1), w); */
#endif
  
  gtk_widget_set_usize (w, 400, 300);
  //  gtk_widget_show (w);

  gtk_container_add (GTK_CONTAINER (win), w);
  gtk_widget_show_all (win);
  
  gtk_signal_connect (GTK_OBJECT (win),
                      "delete_event_cb",
                      GTK_SIGNAL_FUNC (delete_event_cb),
                      NULL);
                                                                               
 
  
#if 0
#if 1
  gtk_signal_connect (GTK_OBJECT (viewport1),
		      "delete_event",
		      GTK_SIGNAL_FUNC (delete_event_cb),
		      NULL);
#endif
#endif
  
  return 0;
}

