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

#include "PVPanel.h"
#include "support.h"
#include "SandiaCalc.h"

/* #include "NEC.h" */

GdkPixmap *pixmap=NULL;
GtkWidget **plots;
GtkWidget **buttons;
GtkPlotData *dataset[5];
GtkPlotData *nec_dataset;
gint nlayers = 0;

extern pvpanel_t *currentpv;

//static const double awglist[] = { 18, 16, 14, 12, 10, 8, 6, 4, 3, 2, 1,
//                        -1, -2, -3, -4,
//                        250, 300, 350, 400, 500, 600
// };

extern GtkWidget *MainWindow;
extern GtkWidget *PVWindow;
extern GtkWidget *PV2DWindow;
extern GtkWidget *PV3DWindow;
extern GtkWidget *canvas1;
extern GtkWidget *custom;
extern GtkWidget *scrolledwindow2;
extern GtkWidget *statusbar2;

extern pvpanel_t *currentpv;

void
quit ()
{
  gtk_main_quit();
}

#if 0
gdouble
nec_resistance(GtkPlot *plot, GtkPlotData *data, gdouble x, gdouble y,
               gboolean *err)
{
  gdouble z;
  *err = FALSE;
  
  //  z = resistance(x, y);
  /* z = (x*x + y*y) / 9.0;
   */
  
  return z;
}
#endif

gboolean
my_tick_label(GtkPlotAxis *axis, gdouble *tick_value, gchar *label, gpointer data)
{
  gboolean return_value = FALSE;

  if(*tick_value == 0.0){
    g_snprintf(label, 100, "custom label at 0.0");
    return_value = TRUE;
  }
  return return_value;
}

gdouble
function(GtkPlot *plot, GtkPlotData *data, gdouble x, gdouble y,
         gboolean *err)
{
  gdouble z;
  
  *err = FALSE;

#if 1
  z = cos(((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5))*24) / 4. + .5;
#endif
#if 0
  z = (x*x + y*y) / 9.0;
#endif
#if 0
  z = resistance(awglist[idx++], y);
#endif

  //  g_print("x = %g, y = %g, z = %g\n", x, y, z);
  
  return z;
}

gdouble
sandia_func(GtkPlot *plot, GtkPlotData *data, gdouble x, gboolean *err)
{
  gdouble y, yy;
  
  *err = FALSE;
  return sandia_calc_F2(x, currentpv->B0, currentpv->B1, currentpv->B2,
                      currentpv->B3, currentpv->B4, currentpv->B5);
}

gdouble
function_2d(GtkPlot *plot, GtkPlotData *data, gdouble x, gboolean *err)
{
  gdouble y, yy;
  
  *err = FALSE;
  y = (-.5+.3*sin(3.*x)*sin(50.*x));
  /* y = 100*pow(x,2);
     y = 1./(10*x);
  */
  yy = sandia_calc_AMa(x, 3000, 12.9);
  
  //  g_print("X data in = %g, YY data out = %g\n", x, yy);
  
  return y;
}

gdouble
gaussian(GtkPlot *plot, GtkPlotData *data, gdouble x, gboolean *err)
{
  gdouble y;
  *err = FALSE;
  y = .65*exp(-.5*pow(x-.5,2)/.02);

  return y;
}

gint
activate_plot(GtkWidget *widget, gpointer data)
{
  GtkWidget **widget_list = NULL;
  GtkWidget *active_widget = NULL;
  GtkWidget *canvas = NULL;
  gint n = 0;

  canvas = GTK_WIDGET(data);
  widget_list = buttons;
  active_widget = widget;

  while(n < nlayers)
    {
      if(widget_list[n] == active_widget){
        gtk_plot_canvas_set_active_plot(GTK_PLOT_CANVAS(canvas),
                                        GTK_PLOT(plots[n]));  
        GTK_BUTTON(buttons[n])->button_down = TRUE;
        GTK_TOGGLE_BUTTON(buttons[n])->active = TRUE;
        gtk_widget_set_state(buttons[n], GTK_STATE_ACTIVE);
      }else{
        GTK_BUTTON(buttons[n])->button_down = FALSE;
        GTK_TOGGLE_BUTTON(buttons[n])->active = FALSE;
        gtk_widget_set_state(buttons[n], GTK_STATE_NORMAL);
      }
      gtk_widget_queue_draw(buttons[n]);
      
      n++;
    }

  return TRUE;
}

GtkWidget *
new_3d_layer(GtkWidget *canvas)
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

GtkWidget *
new_2d_layer(GtkWidget *canvas)
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
  
  gtk_signal_connect(GTK_OBJECT(buttons[nlayers-1]), "toggled",
                     (GtkSignalFunc) activate_plot, canvas);
  
  plots[nlayers-1] = gtk_plot_new_with_size(NULL, .5, .25);
  gtk_widget_show(plots[nlayers-1]);
  
  activate_plot(buttons[nlayers-1],canvas);
  
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


#define MAXNODES 50000

int
gtkplot3d_main(void){

  GtkWidget *window1;
  GtkWidget *active_plot;
  GtkWidget *button;
  GtkWidget *surface;
  GtkWidget *scrollw1;
  GtkWidget *canvas;
  GtkWidget *Module;
  GList *Module_items = NULL;
  gint page_width, page_height;
  gdouble *x,*y,*z,*a;
  gfloat scale = 1.;
  gint n, i, nx, ny;
  char *prevname;
  int pvnames;
  pvpanel_t *pvp;
  
  page_width = GTK_PLOT_LETTER_W * scale;
  page_height = GTK_PLOT_LETTER_H * scale;
  
  // Read in the Sandia Modules database
  pvnames = read_module_data_csv("/home/rob/projects/gnu/gnuae/data/Modules.csv");

  gtk_window_set_title(GTK_WINDOW(PV3DWindow), "PV Module Explorer");
  gtk_widget_set_usize(PV3DWindow,550,650);
  gtk_container_border_width(GTK_CONTAINER(PV3DWindow),0);
  
  gtk_signal_connect (GTK_OBJECT (PV3DWindow), "destroy",
                      GTK_SIGNAL_FUNC (quit), NULL);
  
  scrollw1 = lookup_widget(GTK_WIDGET(PV3DWindow), "scrolledwindow4");
  
  canvas = lookup_widget(GTK_WIDGET(PV3DWindow), "custom2");
  
  GTK_PLOT_CANVAS_SET_FLAGS(GTK_PLOT_CANVAS(canvas), GTK_PLOT_CANVAS_DND_FLAGS);
  //  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrollw1), canvas);
  active_plot = new_3d_layer(canvas);

  gtk_plot_canvas_add_plot(GTK_PLOT_CANVAS(canvas),
                           GTK_PLOT(active_plot), .10, .06);

  x = (gdouble *)g_malloc(1600 * sizeof(gdouble));
  y = (gdouble *)g_malloc(1600 * sizeof(gdouble));
  z = (gdouble *)g_malloc(1600 * sizeof(gdouble));
  a = (gdouble *)g_malloc(1600 * sizeof(gdouble));
  n = 0;
  
  for(nx = 0; nx < 40; nx++) {
    for(ny = 0; ny < 40; ny++) {
      x[n]=0.025*(gdouble)nx;
      y[n]=0.025*(gdouble)ny;
      z[n]=cos(((x[n]-0.5)*(x[n]-0.5) + (y[n]-0.5)*(y[n]-0.5))*24) / 4. + .5;
      a[n]=(x[n]-0.5)*(x[n]-0.5) + (y[n]-0.5)*(y[n]-0.5);
      n++;
    }
  }
  
  surface = gtk_plot_surface_new();
  gtk_plot_surface_set_points(GTK_PLOT_SURFACE(surface),
                              x, y, z, NULL, NULL, NULL, 40, 40);
  
  gtk_plot_data_set_legend(GTK_PLOT_DATA(surface), "PV Module Data");
  //  gtk_plot_surface_use_amplitud(GTK_PLOT_SURFACE(surface), TRUE);
  gtk_plot_data_set_a(GTK_PLOT_DATA(surface), a);
  gtk_plot_data_gradient_set_visible(GTK_PLOT_DATA(surface), TRUE);
  
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_Z,
                          "Ambient Temperature");

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
  
  //  surface = gtk_plot_surface_new_function((GtkPlotFunc3D) function);
  //  gtk_plot_surface_set_xstep(GTK_PLOT_SURFACE(surface), .1);
  //  gtk_plot_surface_set_ystep(GTK_PLOT_SURFACE(surface), .1);

  //  gtk_plot3d_set_xrange(GTK_PLOT3D(active_plot), 0, 23);
  //  gtk_plot3d_set_yrange(GTK_PLOT3D(active_plot), 0, 45);
  //  gtk_plot3d_set_zrange(GTK_PLOT3D(active_plot), 0, 70);

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

  // Get the list of module names from the database, and make a combo
  // box so the user can select one panel for charting.
  Module = lookup_widget(GTK_WIDGET(PV3DWindow), "mod_combo_3d");
    
  // Sort the names. As there are multiple entries for each module,
  // depending on the size of the array, or the year of the tests, we
  // filter them all out.
  prevname = "start";
  for (i=0; i<pvnames; i++){
    pvp = get_pvpanel(i);
    if (strcmp(prevname, pvp->Model) != 0) {
      Module_items = g_list_append (Module_items, (gpointer) pvp->Model);
      prevname = pvp->Model;
    }
  }  
  gtk_combo_set_popdown_strings (GTK_COMBO (Module), Module_items);
  g_list_free (Module_items);
  gtk_fixed_put(GTK_FIXED(canvas), Module, 320, 0);
  
  gtk_widget_show_all(PV3DWindow);

  return(0);
}

/*  "symbol" (string - "NONE"|"SQUARE"|"CIRCLE"|"UP_TRIANGLE"|"DOWN_TRIANGLE"| "RIGHT_TRIANGLE"|"LEFT_TRIANGLE"|"DIAMOND"|"PLUS"| "CROSS"|"STAR"|"DOT"|"IMPULSE")
 * "color" (string - "red"|"green"|"blue"|"yellow"|"black"|"white")
 * "connector" (string - "NONE"|"STRAIGHT"|"SPLINE"|"HV_STEP"|"VH_STEP"|"MIDDLE_STEP")
 * GTK_PLOT_CONNECT_NONE
 * GTK_PLOT_CONNECT_STRAIGHT
 * GTK_PLOT_CONNECT_SPLINE
 * GTK_PLOT_CONNECT_HV_STEP
 * GTK_PLOT_CONNECT_VH_STEP
 * GTK_PLOT_CONNECT_MIDDLE_STEP
 */
void
build_2d_linechart(GtkWidget *active_plot, double *x_data, double *y_data,
                   int data_size)
{
  GdkColor color;
  GtkPlotAxis *axis;
  
  static gdouble px1[]={0., 0.2, 0.4, 0.6, 0.8, 1.0};
  static gdouble py1[]={.2, .4, .5, .35, .30, .40};
  static gdouble dx1[]={.2, .2, .2, .2, .2, .2};
  static gdouble dy1[]={.1, .1, .1, .1, .1, .1};

  static gdouble px2[]={0., -0.2, -0.4, -0.6, -0.8, -1.0};
  static gdouble py2[]={.2, .4, .5, .35, .30, .40};
  static gdouble dx2[]={.2, .2, .2, .2, .2, .2};
  static gdouble dy2[]={.1, .1, .1, .1, .1, .1};

  /* CUSTOM TICK LABELS */

  gtk_plot_axis_use_custom_tick_labels(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT, TRUE);
  axis = gtk_plot_get_axis(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT);
  gtk_signal_connect(GTK_OBJECT(axis), "tick_label", 
                     GTK_SIGNAL_FUNC(my_tick_label), NULL);

  dataset[0] = GTK_PLOT_DATA(gtk_plot_data_new());
  gtk_plot_add_data(GTK_PLOT(active_plot), dataset[0]);
  gtk_widget_show(GTK_WIDGET(dataset[0]));
#if 1
  gtk_plot_data_set_points(dataset[0], x_data, y_data, NULL, dy1, data_size);
#else
  gtk_plot_data_set_points(dataset[0], px1, py1, NULL, NULL, 6);
  // gtk_plot_data_set_points(dataset[0], px1, py1, dx1, dy1, 6);
#endif
  gdk_color_parse("red", &color);
  gdk_color_alloc(gdk_colormap_get_system(), &color); 

  gtk_plot_data_set_symbol(dataset[0],
                           GTK_PLOT_SYMBOL_DIAMOND,
                           GTK_PLOT_SYMBOL_EMPTY,
                           10, 2, &color, &color);
  gtk_plot_data_set_line_attributes(dataset[0],
                                    GTK_PLOT_LINE_SOLID,
                                    1, &color);

  gtk_plot_data_set_connector(dataset[0], GTK_PLOT_CONNECT_SPLINE);

  gtk_plot_data_show_yerrbars(dataset[0]);
  gtk_plot_data_set_legend(dataset[0], "Spline + EY");

  dataset[3] = GTK_PLOT_DATA(gtk_plot_data_new());
  gtk_plot_add_data(GTK_PLOT(active_plot), dataset[3]);
  gtk_widget_show(GTK_WIDGET(dataset[3]));
#if 1
  gtk_plot_data_set_points(dataset[3], px2, py2, NULL, NULL, 6);
#else
  gtk_plot_data_set_points(dataset[3], px2, py2, dx2, dy2, 6);
#endif
  gtk_plot_data_set_symbol(dataset[3],
                           GTK_PLOT_SYMBOL_SQUARE,
                           GTK_PLOT_SYMBOL_OPAQUE,
                           8, 2, 
                           &active_plot->style->black,
                           &active_plot->style->black);
  gtk_plot_data_set_line_attributes(dataset[3],
                                    GTK_PLOT_LINE_SOLID,
                                    4, &color);
  gtk_plot_data_set_connector(dataset[3], GTK_PLOT_CONNECT_STRAIGHT);

#if 0
  /* These draw lines from the connectors to the axis, which we don't want */
  gtk_plot_data_set_x_attributes(dataset[3], 
                                 GTK_PLOT_LINE_SOLID,
                                 0, &active_plot->style->black);
  gtk_plot_data_set_y_attributes(dataset[3], 
                                 GTK_PLOT_LINE_SOLID,
                                 0, &active_plot->style->black);
#endif
  
  gtk_plot_data_set_legend(dataset[3], "Line + Symbol");

 
  gdk_color_parse("blue", &color);
  gdk_color_alloc(gdk_colormap_get_system(), &color); 

  
  dataset[1] = gtk_plot_add_function(GTK_PLOT(active_plot), (GtkPlotFunc)function_2d);
  dataset[1]->x_step = 5;
  //  dataset[1]->y_step = 5;
  
  gtk_widget_show(GTK_WIDGET(dataset[1]));
  gtk_plot_data_set_line_attributes(dataset[1],
                                    GTK_PLOT_LINE_SOLID,
                                    0, &color);

  gtk_plot_data_set_legend(dataset[1], "Function Plot");

  /* This draws a visible grid on the plot */
  /*  gtk_plot_grids_set_visible(GTK_PLOT(active_plot), 1, -1, 1, -1); */
}

void
build_2d_barchart(GtkWidget *active_plot)
{
  GdkColor color;
  static double px2[] = {.1, .2, .3, .4, .5, .6, .7, .8};
  static double py2[] = {.012, .067, .24, .5, .65, .5, .24, .067};
  static double dx2[] = {.1, .1, .1, .1, .1, .1, .1, .1};

  dataset[4] = gtk_plot_add_function(GTK_PLOT(active_plot), (GtkPlotFunc)gaussian);
  gtk_widget_show(GTK_WIDGET(dataset[4]));
  gdk_color_parse("dark green", &color);
  gdk_color_alloc(gdk_colormap_get_system(), &color); 
  gtk_plot_data_set_line_attributes(dataset[4],
                                    GTK_PLOT_LINE_DASHED,
                                    2, &color);

  gtk_plot_data_set_legend(dataset[4], "Gaussian");


  gdk_color_parse("blue", &color);
  gdk_color_alloc(gdk_colormap_get_system(), &color); 
  /*
    GTK_PLOT(active_plot)->xscale = GTK_PLOT_SCALE_LOG10;
  */

  dataset[2] = GTK_PLOT_DATA(gtk_plot_bar_new(GTK_ORIENTATION_VERTICAL));
  gtk_plot_add_data(GTK_PLOT(active_plot), dataset[2]);
  gtk_widget_show(GTK_WIDGET(dataset[2]));
  gtk_plot_data_set_points(dataset[2], px2, py2, dx2, NULL, 8);

  gtk_plot_data_set_symbol(dataset[2],
                           GTK_PLOT_SYMBOL_NONE,
                           GTK_PLOT_SYMBOL_OPAQUE,
                           10, 2, &color, &color);

  gtk_plot_data_set_line_attributes(dataset[2],
                                    GTK_PLOT_LINE_NONE,
                                    1, &color);
  gtk_plot_data_set_legend(dataset[2], "V Bars");

}

int
gtkplot2d_main(double *x_data, double *y_data, int data_size)
{
  GtkWidget *scrollw1;
  GtkWidget *active_plot;
  GtkWidget *canvas;
  //GtkPlotCanvasChild *text;
  //GdkColor color;
  
  gtk_window_set_title(GTK_WINDOW(PV2DWindow), "PV Module Explorer");

  gtk_widget_set_usize(PV2DWindow,500,550);
  gtk_container_border_width(GTK_CONTAINER(PV2DWindow),0);
  
  gtk_signal_connect (GTK_OBJECT (PV2DWindow), "destroy",
                      GTK_SIGNAL_FUNC (quit), NULL);
  
  scrollw1 = lookup_widget(GTK_WIDGET(PV2DWindow), "scrolledwindow3");
  canvas = lookup_widget(GTK_WIDGET(PV2DWindow), "custom1");
  
  GTK_PLOT_CANVAS_SET_FLAGS(GTK_PLOT_CANVAS(canvas), GTK_PLOT_CANVAS_DND_FLAGS);
  
  active_plot = new_2d_layer(canvas);

  gtk_plot_set_range(GTK_PLOT(active_plot), -1., 1., -1., 1.4);
  //  gtk_plot_set_range(GTK_PLOT(active_plot), -1., 1., -1., 1.4);
  gtk_plot_legends_move(GTK_PLOT(active_plot), 0, 1.25);
  //  gtk_plot_legends_move(GTK_PLOT(active_plot), .500, .05);
  gtk_plot_set_legends_border(GTK_PLOT(active_plot), 0, 0);
  gtk_plot_axis_hide_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP);
  gtk_plot_axis_show_ticks(GTK_PLOT(active_plot), 3, 15, 3);
  gtk_plot_axis_set_ticks(GTK_PLOT(active_plot), GTK_PLOT_AXIS_X, .2, .2);

  gtk_plot_axis_set_ticks(GTK_PLOT(active_plot), GTK_PLOT_AXIS_Y, .5, .5);
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_BOTTOM, "Volts");
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_LEFT, "Amps");
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT, "Watts");

  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP, TRUE);
  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT, TRUE);
  gtk_plot_x0_set_visible(GTK_PLOT(active_plot), TRUE);
  gtk_plot_y0_set_visible(GTK_PLOT(active_plot), TRUE);
  gtk_plot_canvas_add_plot(GTK_PLOT_CANVAS(canvas), GTK_PLOT(active_plot), .15, .06);
  gtk_plot_axis_set_labels_suffix(GTK_PLOT(active_plot), GTK_PLOT_AXIS_LEFT, "%");
  //  gtk_plot_grids_set_visible(GTK_PLOT(active_plot), 1, -1, 1, -1);
 
  gtk_widget_show(active_plot);

  build_2d_linechart(active_plot, x_data, y_data, data_size);

#if 0
  active_plot = new_layer(canvas);
  gdk_color_parse("light yellow", &color);
  gdk_color_alloc(gtk_widget_get_colormap(active_plot), &color);
  gtk_plot_set_background(GTK_PLOT(active_plot), &color);
  
  gdk_color_parse("light blue", &color);
  gdk_color_alloc(gtk_widget_get_colormap(canvas), &color);
  gtk_plot_legends_set_attributes(GTK_PLOT(active_plot),
                                  NULL, 0,
                                  NULL,
                                  &color);
  gtk_plot_set_range(GTK_PLOT(active_plot), 0. , 1., 0., .85);
  /*
    gtk_plot_set_range(GTK_PLOT(active_plot), 0.1 , 100., 0., .85);
    gtk_plot_set_xscale(GTK_PLOT(active_plot), GTK_PLOT_SCALE_LOG10);
  */
  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP, TRUE);
  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT, TRUE);
  gtk_plot_grids_set_visible(GTK_PLOT(active_plot), TRUE, TRUE, TRUE, TRUE);
  gtk_plot_canvas_add_plot(GTK_PLOT_CANVAS(canvas), GTK_PLOT(active_plot), .15, .4);
  gtk_plot_axis_hide_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP);
  gtk_plot_axis_hide_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT);
  gtk_plot_set_legends_border(GTK_PLOT(active_plot), 2, 3);
  gtk_plot_legends_move(GTK_PLOT(active_plot), .58, .05);
  gtk_widget_show(active_plot);
  
  build_2d_barchart(active_plot);
#endif
}


int
nec_gtkplot(double *x_data, double *y_data, int data_size)
{
  GtkWidget *scrollw1;
  GtkWidget *active_plot;
  GtkWidget *canvas;
  GdkColor color;
  
  gtk_window_set_title(GTK_WINDOW(PV2DWindow), "PV Module Explorer");

  gtk_widget_set_usize(PV2DWindow,500,550);
  gtk_container_border_width(GTK_CONTAINER(PV2DWindow),0);

  scrollw1 = lookup_widget(GTK_WIDGET(PV2DWindow), "scrolledwindow3");
  canvas = lookup_widget(GTK_WIDGET(PV2DWindow), "custom1");
  
  GTK_PLOT_CANVAS_SET_FLAGS(GTK_PLOT_CANVAS(canvas), GTK_PLOT_CANVAS_DND_FLAGS);
  
  active_plot = new_2d_layer(canvas);

  g_print("X Min is %g, X Max is %g, Y Min is %g, Y Max is %g, Round is %g\n",
          x_data[0],
          x_data[data_size-1],
          y_data[0],
          y_data[data_size-1],
          rint(y_data[data_size-1])
          );
#if 1
  //  gtk_plot_set_range(GTK_PLOT(active_plot), 0., x_data[data_size-1], 0.,
  //                     (y_data[data_size-1]<1) ? 1. : y_data[data_size-1]);
  gtk_plot_set_range(GTK_PLOT(active_plot), x_data[0], x_data[data_size-1], y_data[0],
                     y_data[data_size-1]);
#else
  gtk_plot_set_range(GTK_PLOT(active_plot), 0., 90., 0.,
                     1.2);
#endif
  //  gtk_plot_set_range(GTK_PLOT(active_plot), -1., 1., -1., 1.4);
  gtk_plot_legends_move(GTK_PLOT(active_plot), 0, 1.25);
  //  gtk_plot_legends_move(GTK_PLOT(active_plot), .500, .05);
  gtk_plot_set_legends_border(GTK_PLOT(active_plot), 0, 0);
  gtk_plot_axis_hide_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP);
  gtk_plot_axis_show_ticks(GTK_PLOT(active_plot), 3, 15, 3);
  gtk_plot_axis_set_ticks(GTK_PLOT(active_plot), GTK_PLOT_AXIS_X, 10, 10);

  gtk_plot_axis_set_ticks(GTK_PLOT(active_plot), GTK_PLOT_AXIS_Y, .2, .2);
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_BOTTOM, "AOI");
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_LEFT,   "Isc");
  gtk_plot_axis_set_title(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT,  "Isc");

  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_TOP, TRUE);
  gtk_plot_axis_set_visible(GTK_PLOT(active_plot), GTK_PLOT_AXIS_RIGHT, TRUE);
  gtk_plot_x0_set_visible(GTK_PLOT(active_plot), TRUE);
  gtk_plot_y0_set_visible(GTK_PLOT(active_plot), TRUE);
  gtk_plot_canvas_add_plot(GTK_PLOT_CANVAS(canvas), GTK_PLOT(active_plot), .15, .06);
  //  gtk_plot_axis_set_labels_suffix(GTK_PLOT(active_plot), GTK_PLOT_AXIS_LEFT, "%");
  gtk_plot_grids_set_visible(GTK_PLOT(active_plot), 50, 0, 1, 0);
 
  gtk_widget_show(active_plot);

#if 1
  dataset[0] = GTK_PLOT_DATA(gtk_plot_data_new());
#else
  dataset[0] = GTK_PLOT_DATA(gtk_plot_bar_new(GTK_ORIENTATION_VERTICAL));
#endif

  gtk_plot_add_data(GTK_PLOT(active_plot), dataset[0]);
  gtk_widget_show(GTK_WIDGET(dataset[0]));
  gtk_plot_data_set_points(dataset[0], x_data, y_data, NULL, NULL, data_size);
  gdk_color_parse("red", &color);
  gdk_color_alloc(gdk_colormap_get_system(), &color); 

#if 1
  gtk_plot_data_set_symbol(dataset[0],
                           GTK_PLOT_SYMBOL_DIAMOND,
                           GTK_PLOT_SYMBOL_EMPTY,
                           10, 2, &color, &color);
  gtk_plot_data_set_line_attributes(dataset[0],
                                    GTK_PLOT_LINE_SOLID,
                                    1, &color);

  gtk_plot_data_set_connector(dataset[0], GTK_PLOT_CONNECT_SPLINE);

  gtk_plot_data_show_yerrbars(dataset[0]);
#else
  gtk_plot_data_set_symbol(dataset[0],
                           GTK_PLOT_SYMBOL_NONE,
                           GTK_PLOT_SYMBOL_FILLED,
                           1, 10, &color, &color);

  gtk_plot_data_set_line_attributes(dataset[0],
                                    GTK_PLOT_LINE_NONE,
                                    1, &color);
 
#endif
  gtk_plot_data_set_legend(dataset[0], "Cosine + Optical");

  /* This draws a visible grid on the plot */
  /*  gtk_plot_grids_set_visible(GTK_PLOT(active_plot), 1, -1, 1, -1); */

  return 1;
}
