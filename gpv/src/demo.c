/* $Id: demo.c,v 1.1 2004/09/18 20:34:59 rsavoye Exp $ */

/*
 * demo.c
 *
 * Copyright (C) 2000 EMC Capital Management, Inc.
 *
 * Developed by Jon Trowbridge <trow@gnu.org>.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

/* #include <gnome.h> */

#include <libgnome/gnome-defs.h>
#include <libgnome/gnome-config.h>
#include <libgnomeui/gnome-init.h>

#include <libguppi/guppi-memory.h>
#include <libguppi/guppi-debug.h>
#include <libguppitank/guppi-tank.h>

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
main (gint argc, gchar * argv[])
{
  gint i;
  GuppiObject *title_obj;
  GuppiObject *pie_obj;

  GtkWidget *win;
  GtkWidget *swin;
  GtkWidget *vbox;
  GtkWidget *w;

  gnome_init ("silly_demo", "0.0", argc, argv);
  guppi_tank_init ();
  guppi_set_verbosity (GUPPI_VERY_VERBOSE);

  win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize (win, 400, 300);

  swin = gtk_scrolled_window_new (NULL, NULL);
  gtk_container_add (GTK_CONTAINER (win), swin);

  vbox = gtk_vbox_new (FALSE, 3);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (swin), vbox);

  for (i=0; i<2; ++i)
    gtk_box_pack_start (GTK_BOX (vbox), 
			gtk_label_new ("foo"),
			FALSE, FALSE, 1);

  pie_obj = guppi_object_new ("barchart",
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
				4 * 72, 3 * 72,
				"title", "Pet Behavior Study",
				"subtitle",
				"This is an example of a subtitle",
				"subobject", pie_obj, NULL);

  w = guppi_object_build_widget (title_obj);

  guppi_unref (title_obj);

  gtk_box_pack_start (GTK_BOX (vbox), w, FALSE, FALSE, 1);
  gtk_widget_set_usize (w, 400, 300);
  gtk_widget_show (w);

  gtk_widget_show_all (win);

  gtk_signal_connect (GTK_OBJECT (win),
		      "delete_event",
		      GTK_SIGNAL_FUNC (delete_event_cb),
		      NULL);
  
  gtk_main ();

  return 0;
}



/* $Id: demo.c,v 1.1 2004/09/18 20:34:59 rsavoye Exp $ */
