#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <math.h>
#include <gnome.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gtk/gtkstatusbar.h>
#include <gtkextra/gtkplot.h>
#include <gtkextra/gtkplot3d.h>
#include <gtkextra/gtkplotdata.h>
#include <gtkextra/gtkplotsurface.h>
#include <gtkextra/gtkplotcsurface.h>
#include <gtkextra/gtkplotcanvas.h>
#include <gtkextra/gtkplotps.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "system_data.h"

#include "NEC.h"
#include "PVPanel.h"
#include "SandiaCalc.h"
#include "Loads.h"
#include "Battery.h"
#include "Inverters.h"
#include "Combiners.h"
#include "Pumps.h"
#include "Chargers.h"
#include "Centers.h"

const int pixels_per_row = 20;
const int pixels_per_col = 90;

int gtkplot_main(void);
int nec_gtkplot(double *x_data, double *y_data, int data_size);
int gtkplot2d_main(double *x_data, double *y_data, int data_size);
int gtkplot3d_main(void);
int guppi_main (double *x_data, double *y_data, int data_size);
int gtk_stripchart(void);
void update_data(void);
void update_wiring(void);
// void update_loads(void);
void Popup_Warning (char *msg);
void update_watts_used(double watts);
void set_wiresize_items (GtkWidget *widget, gchar *item);
void set_wiretype_items (GtkWidget *widget, gchar *item);
void nec_update_awg(GtkWidget *widget);
void update_nec_loss_drop(void);
void update_nec_wire_ampacity(void);
void update_nec_conduit_size(void);
const char *awg2str(int);

GtkWidget *PVWindow;
GtkWidget *PV2DWindow;
GtkWidget *PV3DWindow;
GtkWidget *NECWin;
GtkWidget *PVBrowser;
GtkWidget *EditLoad;
GtkWidget *WiringWindow;
GtkWidget *PowerWindow;
GtkWidget *InverterWindow;
GtkWidget *ChargerWindow;
GtkWidget *CombinerWindow;
GtkWidget *BatteryWindow;
GtkWidget *WarningBox;
GtkWidget *DialogBox;
GtkWidget *FileDialog;
GtkWidget *AddPVWin;

static GList *Load_items = NULL;


pvpanel_t *currentpv;
struct gpv_panel *panel_data[100];
struct gpv_panel *currentgpv;
battery_t *current_battery = NULL;
inverter_t *current_inverter = NULL;
pump_t *current_pump = NULL;
charger_t *current_charger = NULL;
combiner_t *current_combiner = NULL;
center_t *current_center = NULL;
extern GList *Modules;

extern struct nec_table4 *_nec_table4s;

wire_data_t wiredata;

const double OLD_BATTERY_FACTOR = 0.8;

static const int awglist[] = { 18, 16, 14, 12, 10, 8, 6, 4, 3, 2, 1,
                               -1, -2, -3, -4,
                               250, 300, 350, 400, 500, 600, 0
};

static const char *awglabels[] = {
  "18", "16", "14", "12", "10", "8", "6", "4", "3", "2", "1",
  "1/0","2/0", "3/0", "4/0",
  "250", "300", "400", "500", "600", 0
};


static const char *wiretypes[] = { "RHH", "RHW", "RHW2", "THHN", "THHW", "THW",
                                 "THW2", "THWN", "THWN2", "XHHW", "XHHW2",
                                 "SE", "USE", "USE2", "TW", "UF", "TBS",
                                 "SA", "SIS", "FEP", "FEPB", "MI", "XHH",
                                   "ZW2", 0
};

struct gpv_data GPVData;

typedef enum { NOSTATE, SYSTEMOPEN, SYSTEMWRITE,
               LOADOPEN, LOADWRITE,
               PVOPEN, PVWRITE,
               BATTOPEN, BATTWRITE,
               CHARGERSOPEN, CHARGERSWRITE,
               COMBINOPEN, COMBINWRITE,
               INVERTOPEN, INVERTWRITE } filestate_t;

static filestate_t filestate;

const char *
awg2str(int awg)
{
  int i;
  
  for (i=0; awglist[i] != 0; i++) {
    if (awglist[i] == awg) {
      //      g_print("%d matches %s\n", awg, awglabels[i]);
      return awglabels[i];
    }
  }
  return (const char *)0;
}

int
str2awg(const char *awg)
{
  int i;
  
  for (i=0; awglist[i] != 0; i++) {
    if (strcmp(awglabels[i], awg) == 0) {
      //      g_print("%s matches %d\n", awg, awglist[i]);
      return awglist[i];
    }
  }
  
  return 0;
}

int
str2wiretype(const char *type)
{
  int value = 0;

  if (strcmp(type, "RHH") == 0) {
    value = RHH;
  }
  
  if (strcmp(type, "RHW") == 0) {
    value = RHW;
  }

  if (strcmp(type, "RHW2") == 0) {
    value = RHW2;
  }

  if (strcmp(type, "THHN") == 0) {
    value = THHN;
  }

  if (strcmp(type, "THHW") == 0) {
    value = THHW;
  }

  if (strcmp(type, "THW") == 0) {
    value = THW;
  }

  if (strcmp(type, "THW2") == 0) {
    value = THW2;
  }

  if (strcmp(type, "THW2") == 0) {
    value = THW2; 
  }

  if (strcmp(type, "THWN") == 0) {
    value = THWN;
  }

  if (strcmp(type, "THWN2") == 0) {
    value = THWN2;
  }

  if (strcmp(type, "XHHW") == 0) {
    value = XHHW;
  }

  if (strcmp(type, "XHHW2") == 0) {
    value = XHHW2;
  }

  if (strcmp(type, "SE") == 0) {
    value = SE;
  }

  if (strcmp(type, "USE") == 0) {
    value = USE;
  }

  if (strcmp(type, "USE2") == 0) {
    value = USE2;
  }

  if (strcmp(type, "TW") == 0) {
    value = TW;
  }

  if (strcmp(type, "UF") == 0) {
    value = UF;
  }

  if (strcmp(type, "TBS") == 0) {
    value = TBS;
  }

  if (strcmp(type, "SA") == 0) {
    value = SA;
  }

  if (strcmp(type, "SIS") == 0) {
    value = SIS;
  }

  if (strcmp(type, "FEP") == 0) {
    value = FEP;
  }

  if (strcmp(type, "FEPB") == 0) {
    value = FEPB;
  }

  if (strcmp(type, "MI") == 0) {
    value = MI;
  }

  if (strcmp(type, "XHH") == 0) {
    value = XHH;
  }

  if (strcmp(type, "ZW2") == 0) {
    value = ZW2;
  }

  return value;
}

/*
 * print a message in status line
 * bar is the number of the window
 * msg is the message itself
 */
void
UpdateStatusMsg(int bar, char *msg)
{
  GtkWidget *appbar1;
  gint id;
  
  switch (bar) {
  case 2:
    appbar1 = lookup_widget(GTK_WIDGET(PVWindow), "statusbar2");
    break;
  default:
    appbar1 = lookup_widget(GTK_WIDGET(MainWindow), "statusbar1");
    break;
  }
  
  id =  gtk_statusbar_get_context_id(GTK_STATUSBAR(appbar1), "update");
  gtk_statusbar_push(GTK_STATUSBAR(appbar1), id, msg);   
}

#if 0
void
UpdateLabel (int idx, char *text)
{
  GtkWidget *label;
  char tmp[50];
   
  sprintf (tmp, "DataPanelLabel%d", idx);
   
  // Only try to change the label if the Setup Menu window is open
  if (setupmenu != NULL) {
    label = lookup_widget(GTK_WIDGET(setupmenu), tmp);
    gtk_label_set_text(GTK_LABEL(label), text);
  }
}
#endif

void
on_file1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  PVWindow = create_pvdata ();

  UpdateStatusMsg(1, "New PV Data Window");

  gtk_widget_show (PVWindow);
}

void
on_new2_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Select a file name");
  FileDialog = create_fileselection();
  filestate = SYSTEMOPEN;

  gtk_widget_show(FileDialog);
#if 0
  GtkWidget *gtkplot;
  
  gtkplot = create_gtkplotwin();
  gtk_widget_show(gtkplot);
#endif
}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *about;
  about = create_about ();
  gtk_widget_show (about);
}

void
on_new_guppi_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; i < 15; i++) {
    x_data[i] = awglist[i];
    y_data[i] = _table8[i].uncoated;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
 // guppi_main(x_data, y_data, 30);

  free(x_data);
  free(y_data);  
}


void
on_new_gtkplot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "New GtkPlot Window");
  
  /*
  gtk_plot_set_drawable(GTK_PLOT(active_plot),
                        GTK_WIDGET(drawing_area)->window);
  gtk_plot_refresh(GTK_PLOT(active_plot),
                   GTK_WIDGET(drawing_area)->allocation)
  */   
  //  PV3DWindow = create_gtkplot3Dwin();
  //  PVWindow = create_pvdata();
  
  //  gtkplot_main();
}


void
on_new_stripchart1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_exit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  /* Save our current configuration */
  write_system("");

  /* */
  write_loads("");
  
  /* Quit this application */
  gtk_main_quit();
}


void
on_awg_vs_ohms1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; i < 15; i++) {
    x_data[i] = awglist[i];
    y_data[i] = _table8[i].uncoated;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
  // guppi_main(x_data, y_data, 30);

  free(x_data);
  free(y_data);  
}


void
on_temp_vs_ohms1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; i < 15; i++) {
    x_data[i] = awglist[i];
    y_data[i] = _table8[i].uncoated;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
  // guppi_main(x_data, y_data, 30);

  free(x_data);
  free(y_data);  
}


void
on_voltage_drop1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; i < 15; i++) {
    x_data[i] = awglist[i];
    y_data[i] = _table8[i].uncoated;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
  // guppi_main(x_data, y_data, 30);

  free(x_data);
  free(y_data);
}


void
on_voltage_loss1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; i < 15; i++) {
    x_data[i] = awglist[i];
    y_data[i] = _table8[i].uncoated;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
  // guppi_main(x_data, y_data, 30);

  free(x_data);
  free(y_data);
}


void
on_pv_temp_comp1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  // create_gtkplot3d();
  int i;
  double *x_data;
  double *y_data;

  x_data =  (double *)malloc(sizeof(double)*30);
  y_data =  (double *)malloc(sizeof(double)*30);

  for (i = 0; _table_690_7[i].compensation != 0 ; i++) {
    x_data[i] =  _table_690_7[i].lowtempF;
    y_data[i] =  _table_690_7[i].compensation;
    
    g_print("x_data[%d] = %g\n", i, x_data[i]);
    g_print("y_data[%d] = %g\n", i, y_data[i]);
  }

  UpdateStatusMsg(1, "New Guppi Window");
  // guppi_main(x_data, y_data, 5);

  free(x_data);
  free(y_data);
}

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_print1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#if 0
  gtk_plot_canvas_export_ps_with_size(GTK_PLOT_CANVAS(canvas), "demo3d.ps", 
                                      0, 0, GTK_PLOT_PSPOINTS,
                                      GTK_PLOT_LETTER_W, GTK_PLOT_LETTER_H);
#endif
}


void
on_close1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_X_beam_irradiation_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using Beam Irradiation");
}


void
on_X_diffuse_irradiation_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using Diffuse Irradiation");
}


void
on_X_ambient_temperature_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using Ambient Temperature");
}


void
on_X_sun_elevation_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using the Sun Elevation");
}


void
on_X_aoi_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using the AOI");
}


void
on_X_wind_speed_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using the Wind Speed");
}


void
on_X_altitude_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating X using the Altitude");
}


void
on_Y_isc_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Isc");
}


void
on_Y_imp_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Imp");
}


void
on_Y_vmp_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Vmp");
}


void
on_Y_voc_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Voc");
}


void
on_Y_tc_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Tc");
}


void
on_Y_power_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Power Output");
}


void
on_Y_efficiency_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Panel Efficiency");
}


void
on_Y_fill_factor_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Y using the Fill Factor");
}


void
on_Z_beam_irradiation_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using Beam Irradiation");
}


void
on_Y_diffuse_irradiation_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using Diffuse Irradiation");
}


void
on_Z_ambient_temperature_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using Ambient Temperature");
}


void
on_Z_sun_elevation_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using the Sun Elevation");
}


void
on_Z_aoi_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using the AOI");
}


void
on_Z_wind_speed_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using the Wind Speed");
}


void
on_Z_altitude_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "Recalculating Z using the Altitude");
}


void
on_new3_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_radio1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

GtkWidget*
make_gtk_plot_custom (gchar *widget_name, gchar *string1, gchar *string2,
                      gint int1, gint int2)
{
  g_print("%s unimplmented\n", __FUNCTION__);
#ifdef USE_GTKPLOT
  return gtk_plot_canvas_new(GTK_PLOT_LETTER_W, GTK_PLOT_LETTER_H, 1.);
#endif

  return (GtkWidget *)0;
}



void
on_exit2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

void
on_file2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_x_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_y_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_z_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

#ifdef USE_GTKPLOT
void
on_new_2d_plot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "New 2D GTK PLot Window");
  
  PV2DWindow =  create_gtkplot2Dwin();
  gtk_widget_show (PV2DWindow);

  static double x1[] = { 0., 0.2, 0.4, 0.6, 0.8, 1.0};
  static double y1[] = { .2, .4, .5, .35, .30, .40};
  /* double dx1[]={.2, .2, .2, .2, .2, .2}; */
  /* double dy1[]={.1, .1, .1, .1, .1, .1}; */

  gtkplot2d_main(x1, y1, 6);
}
#endif

GtkWidget*
make_gtk_plot_custom_3d (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2)
{
    g_print("%s unimplmented\n", __FUNCTION__);
#ifdef USE_GTKPLOT
    return gtk_plot_canvas_new(GTK_PLOT_LETTER_W, GTK_PLOT_LETTER_H, 1.);
#endif

    return (GtkWidget *)0;
}

#ifdef USE_GTKPLOT
void
on_new_3d_plot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  UpdateStatusMsg(1, "New GtkPlot Window");
  
  /*
  gtk_plot_set_drawable(GTK_PLOT(active_plot),
                        GTK_WIDGET(drawing_area)->window);
  gtk_plot_refresh(GTK_PLOT(active_plot),
                   GTK_WIDGET(drawing_area)->allocation)
  */   
  PV3DWindow = create_gtkplot3Dwin();
  //  PVWindow = create_pvdata();
  
  gtkplot3d_main();
}
#endif


void
on_table8_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label1;
  gchar *items[6], *buf;
  int i, rows = 0;

  table = create_col_list6();
  clist = lookup_widget(GTK_WIDGET(table), "clist3");

  gtk_clist_set_column_justification (GTK_CLIST (clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST (clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST (clist), 2, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST (clist), 3, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST (clist), 4, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST (clist), 5, GTK_JUSTIFY_CENTER);

  for (i=0; _table8[i].conductors>0; i++) {
    buf = g_malloc(7);
    if (_table8[i].awg > 0)
      sprintf(buf, "%d", _table8[i].awg);
    else
      sprintf(buf, "%d/0", abs(_table8[i].awg));
    items[0] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%d", _table8[i].conductors);
    items[1] = buf;
    
    buf = g_malloc(7);
    if (_table8[i].mils > 0)
      sprintf(buf, "%g", _table8[i].mils);
    else
      sprintf(buf, "-");
    items[2] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table8[i].dia);
    items[3] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table8[i].uncoated);
    items[4] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table8[i].coated);
    items[5] = buf;

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 8 - DC resistance at 167F");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*6,
                               pixels_per_row*rows);

  // Label the first column
  label1 = lookup_widget(GTK_WIDGET(table), "label53");
  gtk_label_set_text(GTK_LABEL(label1), "AWG");

  // Label the second column
  label1 = lookup_widget(GTK_WIDGET(table), "label54");
  gtk_label_set_text(GTK_LABEL(label1), "Conductors");

  // Label the third column
  label1 = lookup_widget(GTK_WIDGET(table), "label55");
  gtk_label_set_text(GTK_LABEL(label1), "Mils");

  // Label the fourth column
  label1 = lookup_widget(GTK_WIDGET(table), "label56");
  gtk_label_set_text(GTK_LABEL(label1), "Diameter");

  // Label the fifth column
  label1 = lookup_widget(GTK_WIDGET(table), "label57");
  gtk_label_set_text(GTK_LABEL(label1), "Uncoated");

  // Label the sixth column
  label1 = lookup_widget(GTK_WIDGET(table), "label58");
  gtk_label_set_text(GTK_LABEL(label1), "Coated");

  gtk_widget_show (table);
}


void
on_table690_7_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[3], *buf;
  int i, rows = 1;

  table = create_col_list3();
  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);

  for (i=0; _table_690_7[i].compensation>0; i++) {
    buf = g_malloc(5);
    sprintf(buf, "%d - %d", _table_690_7[i].lowtempC,
            _table_690_7[i].hightempC);
    items[0] = buf;
    
    buf = g_malloc(5);
    sprintf(buf, "%g",_table_690_7[i].compensation);
    items[1] = buf;

    buf = g_malloc(5);
    sprintf(buf, "%d - %d", _table_690_7[i].lowtempF,
            _table_690_7[i].hightempF);
    items[2] = buf;

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 609.7 - Voltage correction for Silicon PV Modules");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*3,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label59");
  gtk_label_set_text(GTK_LABEL(label), "Celcius");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label60");
  gtk_label_set_text(GTK_LABEL(label), "Compensation");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label61");
  gtk_label_set_text(GTK_LABEL(label), "Farenheit");

  gtk_widget_show (table);
}


void
on_conduit_size_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

/*
 * Open the NEC calculator
 */
void
on_nec_calculator_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  NECWin = create_neccalc();
  gtk_widget_show (NECWin);
}


void
on_table_310_15b2_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[3], *buf;
  int i, rows = 0;

  table = create_col_list3();
  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);

  for (i=0; _table_310_15B2[i].lowconductors>0; i++) {
    buf = g_malloc(7);
    sprintf(buf, "%d", _table_310_15B2[i].lowconductors);
    items[0] = buf;
    
    buf = g_malloc(7);
    if ( _table_310_15B2[i].highconductors == MAXINT)
      sprintf(buf, "41 or above");
    else
      sprintf(buf, "%d", _table_310_15B2[i].highconductors);
    items[1] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_15B2[i].adjust);
    items[2] = buf;
    

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 310.15B2 - Adjustment for more than 3 conductors");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*3,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label59");
  gtk_label_set_text(GTK_LABEL(label), "Low Conductors");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label60");
  gtk_label_set_text(GTK_LABEL(label), "High Conductors");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label61");
  gtk_label_set_text(GTK_LABEL(label), "Adjustment");


  gtk_widget_show (table);

}


void
on_table_310_15b6_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[3], *buf;
  int i, rows = 0;

  table = create_col_list3();
  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);

  for (i=0; _table_310_15B6[i].maxcurrent>0; i++) {
    buf = g_malloc(7);
    if (_table_310_15B6[i].copper > 0)
      sprintf(buf, "%d", _table_310_15B6[i].copper);
    else
      sprintf(buf, "%d/0", abs(_table_310_15B6[i].copper));
    items[0] = buf;
    
    buf = g_malloc(7);
    if (_table_310_15B6[i].aluminum > 0)
      sprintf(buf, "%d", _table_310_15B6[i].aluminum);
    else
      sprintf(buf, "%d/0", abs(_table_310_15B6[i].aluminum));
    items[1] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_15B6[i].maxcurrent);
    items[2] = buf;
    

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 310.15B6 - Conductor Types and sizes for single phase, 120/240VAC");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*3,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label59");
  gtk_label_set_text(GTK_LABEL(label), "Copper");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label60");
  gtk_label_set_text(GTK_LABEL(label), "Aluminum");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label61");
  gtk_label_set_text(GTK_LABEL(label), "Max Current");

  gtk_widget_show (table);
}


void
on_table_310_11_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[3], *buf;
  int i, rows = 1;

  table = create_col_list3();
  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);

  for (i=0; _table_310_11[i].lowconductors>0; i++) {
    buf = g_malloc(7);
    sprintf(buf, "%d", _table_310_11[i].lowconductors);
    items[0] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%d", _table_310_11[i].highconductors);
    items[1] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_11[i].adjust);
    items[2] = buf;

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 310.11 - Derating for conductors in conduit");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*3,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label59");
  gtk_label_set_text(GTK_LABEL(label), "Low Conductors");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label60");
  gtk_label_set_text(GTK_LABEL(label), "High Conductors");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label61");
  gtk_label_set_text(GTK_LABEL(label), "Adjustment");

  gtk_widget_show (table);
}


void
on_table_310_16_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[4], *buf;
  int i, rows = 0;

  table = create_col_list4();
  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);

  for (i=0; _table_310_16[i].awg!=0; i++) {
    buf = g_malloc(7);
    if (_table_310_16[i].awg > 0)
      sprintf(buf, "%d", _table_310_16[i].awg);
    else
      sprintf(buf, "%d/0", abs(_table_310_16[i].awg));
    items[0] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_16[i].R60C_140F);
    items[1] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_16[i].R75C_167F);
    items[2] = buf;

    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_16[i].R90C_194F);
    items[3] = buf;

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table),
          "NEC Table 310.16 - Allowable ampacities for 3 or less conductors");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*4,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label37");
  gtk_label_set_text(GTK_LABEL(label), "AWG");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label38");
  gtk_label_set_text(GTK_LABEL(label), "60C/140F");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label39");
  gtk_label_set_text(GTK_LABEL(label), "75C/167F");

  // Label the fourth column
  label = lookup_widget(GTK_WIDGET(table), "label40");
  gtk_label_set_text(GTK_LABEL(label), "90C/194F");

  gtk_widget_show (table);
}


void
on_table_310_17_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[4], *buf;
  int i, rows = 0;

  table = create_col_list4();

  clist = lookup_widget(GTK_WIDGET(table), "clist4");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);

  for (i=0; _table_310_17[i].awg!=0; i++) {
    buf = g_malloc(7);
    if (_table_310_17[i].awg > 0)
      sprintf(buf, "%d", _table_310_17[i].awg);
    else
      sprintf(buf, "%d/0", abs(_table_310_17[i].awg));
    items[0] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_17[i].R60C_140F);
    items[1] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_17[i].R75C_167F);
    items[2] = buf;

    buf = g_malloc(7);
    sprintf(buf, "%g", _table_310_17[i].R90C_194F);
    items[3] = buf;

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 310.17 - Allowable ampacities in free air");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*4,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label37");
  gtk_label_set_text(GTK_LABEL(label), "AWG");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label38");
  gtk_label_set_text(GTK_LABEL(label), "60C/140F");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label39");
  gtk_label_set_text(GTK_LABEL(label), "75C/167F");

  // Label the fourth column
  label = lookup_widget(GTK_WIDGET(table), "label40");
  gtk_label_set_text(GTK_LABEL(label), "90C/194F");

  gtk_widget_show (table);
}


void
on_table_690_31c_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *table, *clist;
  GtkWidget *label;
  gchar *items[6], *buf;
  int i, rows = 0;

  table = create_col_list6();
  clist = lookup_widget(GTK_WIDGET(table), "clist3");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 4, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 5, GTK_JUSTIFY_CENTER);

  for (i=0; _table_690_31C[i].hightempC>0; i++) {
    buf = g_malloc(8);
    if (_table_690_31C[i].lowtempC == 0)
      sprintf(buf, "%d", _table_690_31C[i].hightempC);
    else
      sprintf(buf, "%d-%d", _table_690_31C[i].lowtempC,
              _table_690_31C[i].hightempC);
    items[0] = buf;
    
    buf = g_malloc(7);
    if (_table_690_31C[i].R60C_140F > 0)
      sprintf(buf, "%g", _table_690_31C[i].R60C_140F);
    else
      sprintf(buf, "-");      
    items[1] = buf;
    
    buf = g_malloc(7);
    if (_table_690_31C[i].R75C_167F > 0)
      sprintf(buf, "%g", _table_690_31C[i].R75C_167F);
    else
      sprintf(buf, "-");
    items[2] = buf;
    
    buf = g_malloc(7);
    if (_table_690_31C[i].R90C_194F > 0)
      sprintf(buf, "%g", _table_690_31C[i].R90C_194F);
    else
      sprintf(buf, "-");
    items[3] = buf;
    
    buf = g_malloc(7);
    sprintf(buf, "%g", _table_690_31C[i].R105C_221F);
    items[4] = buf;
    
    buf = g_malloc(8);
    if (_table_690_31C[i].lowtempF == 0)
      sprintf(buf, "%d", _table_690_31C[i].hightempF);
    else
      sprintf(buf, "%d-%d", _table_690_31C[i].lowtempF,
              _table_690_31C[i].hightempF);
    items[5] = buf;    

    rows++;
    gtk_clist_append(GTK_CLIST (clist), items);
  }

  gtk_window_set_title (GTK_WINDOW (table), "NEC Table 690.31c - Correction Factrors");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*6,
                               pixels_per_row*rows);

  // Label the first column
  label = lookup_widget(GTK_WIDGET(table), "label53");
  gtk_label_set_text(GTK_LABEL(label), "Celcius");

  // Label the second column
  label = lookup_widget(GTK_WIDGET(table), "label54");
  gtk_label_set_text(GTK_LABEL(label), "60C(140F)");

  // Label the third column
  label = lookup_widget(GTK_WIDGET(table), "label55");
  gtk_label_set_text(GTK_LABEL(label), "75C(167F)");

  // Label the fourth column
  label = lookup_widget(GTK_WIDGET(table), "label56");
  gtk_label_set_text(GTK_LABEL(label), "90C(194F)");

  // Label the fifth column
  label = lookup_widget(GTK_WIDGET(table), "label57");
  gtk_label_set_text(GTK_LABEL(label), "105C(221F)");

  // Label the sixth column
  label = lookup_widget(GTK_WIDGET(table), "label58");
  gtk_label_set_text(GTK_LABEL(label), "Farenheit");

  gtk_widget_show (table);
}

void
on_fnec_fixed_map                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  //  g_print("NEC Fixed window mapped!!");

  // Set the default values for the calculations
}


void
on_pv_browser_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  GtkWidget *modlist, *entry;
  char buf[20];
  pvpanel_t *pvp;

  PVBrowser = create_PVBrowser();

  modlist = lookup_widget(GTK_WIDGET(PVBrowser), "combo1");
  gtk_combo_set_popdown_strings (GTK_COMBO (modlist), Modules);

  currentpv = pvp = get_pvpanel(0);

  /* Display the main parameters */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "material_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Material);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "material_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Material);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "area_e");
  sprintf(buf, "%g", pvp->Area);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Short Circuit Current */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Isco_e");
  sprintf(buf, "%g", pvp->Isco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Nominal current */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Impo_e");
  sprintf(buf, "%g", pvp->Impo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Nominal Voltage */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Vmpo_e");
  sprintf(buf, "%g", pvp->Vmpo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Open Circuit Voltage */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Voco_e");
  sprintf(buf, "%g", pvp->Voco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* number of cells in a series */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "series_e");
  sprintf(buf, "%d", pvp->Series_Cells);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* number of cells in parallel*/
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "parallel_e");
  sprintf(buf, "%d", pvp->Parallel_C_S);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* year of test */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "vintage_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Vintage);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "price_e");
  sprintf(buf, "$%g", pvp->Price);
  if (pvp->Price)
    gtk_entry_set_text(GTK_ENTRY(entry), buf);
  else
    gtk_entry_set_text(GTK_ENTRY(entry), "unknown");

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "description_e");
  gtk_text_set_word_wrap(GTK_TEXT (entry), TRUE);

  if (pvp->Description != NULL)
    gtk_text_insert (GTK_TEXT (entry),
                     NULL,  NULL, NULL,
                     pvp->Description, strlen(pvp->Description));
  
  /* Display the calculate values */

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C0_e");
  sprintf(buf, "%g", pvp->C0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C1_e");
  sprintf(buf, "%g", pvp->C1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C2_e");
  sprintf(buf, "%g", pvp->C2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C3_e");
  sprintf(buf, "%g", pvp->C3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C4_e");
  sprintf(buf, "%g", pvp->C4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C5_e");
  sprintf(buf, "%g", pvp->C5);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C6_e");
  sprintf(buf, "%g", pvp->C6);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C7_e");
  sprintf(buf, "%g", pvp->C7);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "fd_e");
  sprintf(buf, "%g", pvp->fd);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* second column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A0_e");
  sprintf(buf, "%g", pvp->A0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A1_e");
  sprintf(buf, "%g", pvp->A1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A2_e");
  sprintf(buf, "%g", pvp->A2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A3_e");
  sprintf(buf, "%g", pvp->A3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A4_e");
  sprintf(buf, "%g", pvp->A4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "b_e");
  sprintf(buf, "%g", pvp->b);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "n_e");
  sprintf(buf, "%g", pvp->n);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "a_e");
  sprintf(buf, "%g", pvp->a);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Tc_e");
  sprintf(buf, "%g", pvp->d_Tc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);


  /* third column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B0_e");
  sprintf(buf, "%g", pvp->B0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B1_e");
  sprintf(buf, "%g", pvp->B1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B2_e");
  sprintf(buf, "%g", pvp->B2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B3_e");
  sprintf(buf, "%g", pvp->B3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B4_e");
  sprintf(buf, "%g", pvp->B4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B5_e");
  sprintf(buf, "%g", pvp->B5);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Ixxo_e");
  sprintf(buf, "%g", pvp->Ixxo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Ixo_e");
  sprintf(buf, "%g", pvp->Ixo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* fourth column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "BVoco_e");
  sprintf(buf, "%g", pvp->BVoco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "mBVoc_e");
  sprintf(buf, "%g", pvp->mBVoc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "BVmpo_e");
  sprintf(buf, "%g", pvp->BVmpo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "mBVmp_e");
  sprintf(buf, "%g", pvp->mBVmp);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "aIsc_e");
  sprintf(buf, "%g", pvp->aIsc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "aImp_e");
  sprintf(buf, "%g", pvp->aImp);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  gtk_widget_show (PVBrowser);
}


void
on_pv_e_changed                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  int idx;
  gchar buf[50];
  gchar *ptr;
  pvpanel_t *pvp;

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "pv_e");

  /*
    The index number is the beginning of the entry text in square
    brackets []
  */
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  strcpy(buf, ptr);
  ptr = buf;
  ptr++;
  *strchr(ptr,']') = 0;
  idx = atoi(ptr);
  
  currentpv = pvp = get_pvpanel(idx);
  
  /* Display the main parameters */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "material_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Material);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "material_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Material);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "area_e");
  sprintf(buf, "%g", pvp->Area);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Short Circuit Current */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Isco_e");
  sprintf(buf, "%g", pvp->Isco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Nominal current */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Impo_e");
  sprintf(buf, "%g", pvp->Impo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Nominal Voltage */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Vmpo_e");
  sprintf(buf, "%g", pvp->Vmpo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Open Circuit Voltage */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Voco_e");
  sprintf(buf, "%g", pvp->Voco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* number of cells in a series */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "series_e");
  sprintf(buf, "%d", pvp->Series_Cells);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* number of cells in parallel*/
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "parallel_e");
  sprintf(buf, "%d", pvp->Parallel_C_S);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* year of test */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "vintage_e");
  gtk_entry_set_text(GTK_ENTRY(entry), pvp->Vintage);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "price_e");
  sprintf(buf, "%g", pvp->Price);
  if (pvp->Price)
    gtk_entry_set_text(GTK_ENTRY(entry), buf);
  else
    gtk_entry_set_text(GTK_ENTRY(entry), "unknown");

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "description_e");
  /* clear the existing text */
  gtk_text_backward_delete(GTK_TEXT (entry),
                           gtk_text_get_length(GTK_TEXT (entry)));
  
  if (pvp->Description != NULL)
    gtk_text_insert (GTK_TEXT (entry),
                     NULL,  NULL, NULL,
                     pvp->Description, strlen(pvp->Description));
  
  /* Display the calculate values */

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C0_e");
  sprintf(buf, "%g", pvp->C0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C1_e");
  sprintf(buf, "%g", pvp->C1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C2_e");
  sprintf(buf, "%g", pvp->C2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C3_e");
  sprintf(buf, "%g", pvp->C3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C4_e");
  sprintf(buf, "%g", pvp->C4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C5_e");
  sprintf(buf, "%g", pvp->C5);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C6_e");
  sprintf(buf, "%g", pvp->C6);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "C7_e");
  sprintf(buf, "%g", pvp->C7);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "fd_e");
  sprintf(buf, "%g", pvp->fd);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* second column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A0_e");
  sprintf(buf, "%g", pvp->A0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A1_e");
  sprintf(buf, "%g", pvp->A1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A2_e");
  sprintf(buf, "%g", pvp->A2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A3_e");
  sprintf(buf, "%g", pvp->A3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "A4_e");
  sprintf(buf, "%g", pvp->A4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "b_e");
  sprintf(buf, "%g", pvp->b);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "n_e");
  sprintf(buf, "%g", pvp->n);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "a_e");
  sprintf(buf, "%g", pvp->a);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Tc_e");
  sprintf(buf, "%g", pvp->d_Tc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);


  /* third column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B0_e");
  sprintf(buf, "%g", pvp->B0);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B1_e");
  sprintf(buf, "%g", pvp->B1);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B2_e");
  sprintf(buf, "%g", pvp->B2);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B3_e");
  sprintf(buf, "%g", pvp->B3);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B4_e");
  sprintf(buf, "%g", pvp->B4);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "B5_e");
  sprintf(buf, "%g", pvp->B5);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Ixxo_e");
  sprintf(buf, "%g", pvp->Ixxo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "Ixo_e");
  sprintf(buf, "%g", pvp->Ixo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* fourth column of values */
  entry = lookup_widget(GTK_WIDGET(PVBrowser), "BVoco_e");
  sprintf(buf, "%g", pvp->BVoco);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "mBVoc_e");
  sprintf(buf, "%g", pvp->mBVoc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "BVmpo_e");
  sprintf(buf, "%g", pvp->BVmpo);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "mBVmp_e");
  sprintf(buf, "%g", pvp->mBVmp);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "aIsc_e");
  sprintf(buf, "%g", pvp->aIsc);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(PVBrowser), "aImp_e");
  sprintf(buf, "%g", pvp->aImp);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  gtk_widget_show (PVBrowser);
}


void
on_wire_resistance_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int i;
  double f2;
  static double x1[11];
  static double y1[11];
  //  static double px1[] = { 0,  10,  20,  30,  40,  50,  60,  70,  80, 90 };
  //  static double px1[] = { 0., 0.2, 0.4, 0.6, 0.8, 1.0};
  //  static double py1[] = { 1, .99, .93, .89, .80, .70, .57, .40, .20, 0 };
  //  static double py1[] = { .2, .4, .5, .35, .30, .40};
  
  UpdateStatusMsg(1, "Graph NEC Table 8");

  PV2DWindow =  create_gtkplot2Dwin();
  gtk_widget_show (PV2DWindow);
  
  //  x1 = g_malloc(11);
  //  y1 = g_malloc(11);

  if (currentpv == 0) {
      currentpv = get_pvpanel(0);
  }
  for (i=0; i<10; i++) {
    f2 = sandia_calc_F2(i, currentpv->B0, currentpv->B1, currentpv->B2,
                        currentpv->B3, currentpv->B4, currentpv->B5);
    x1[i] = (double)i*10;
    y1[i] = (double)f2;
    g_print("X = %g, Y = %g\n", (double)i*10, f2);
  }
  
  /* double dx1[]={.2, .2, .2, .2, .2, .2}; */
  /* double dy1[]={.1, .1, .1, .1, .1, .1}; */

#ifdef USE_GTKPLOT  
  nec_gtkplot(x1, y1, 10);
#endif
}


void
on_wire_ampacity_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  static double x1[101];
  static double y1[101];
  GtkWidget *entry;
  gchar *ptr, buf[100];
  GtkSpinButton *spinv;
  int awg, distance, conductors, count;
  gdouble amps, loss, i;

  UpdateStatusMsg(1, "Temperature vs Resistance");

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  /* Get the numeric AWG value for the string value */
  awg = str2awg(ptr);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin2"));
  amps = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin3"));
  distance = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin4"));
  conductors = gtk_spin_button_get_value_as_int(spinv);

  PV2DWindow =  create_gtkplot2Dwin();
  gtk_widget_show (PV2DWindow);

  sprintf(buf, "Voltage Drop vs Temperature for #%s AWG", ptr);
  
  gtk_window_set_title(GTK_WINDOW(PV2DWindow), buf);

  count = 0;
  for (i=0.0; i<100.0; i+=5.0) {
    loss = nec_volt_loss(distance, awg, amps, i, conductors);
    x1[count] = i;
    y1[count] = loss;
    g_print("X[%d] = %g, Y[%d] = %g\n", count, x1[count], count, y1[count]);
    count++;
  }  

#ifdef USE_GTKPLOT  
  nec_gtkplot(x1, y1, count);
#endif
}


void
on_isc_x_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_aoi_y_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_isc_y_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_nominal_volts_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}


void
on_sun_per_day_changed                 (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}

void update_data(void)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gdouble val, amps, watts, volts, hours, series, parallel, total, pv_volts;
  gdouble time, usable, lowtemp, hightemp, min_amps, bseries, bparallel, btotal;
  gdouble factor, price, array_current;
  char buf[20];

  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  volts = gtk_spin_button_get_value_as_int(spinb);

  /* Get the total number of watts used by all the loads */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "watts_entry"));
  //  watts = gtk_spin_button_get_value_as_int(spinb);
  watts = calc_watts_total();
  gtk_spin_button_set_value(spinb, watts);

  /* Amps is watts/volts of course */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "amps_entry"));
  val = (gdouble)watts/volts;
  if (val > 0.0){
    gtk_spin_button_set_value(spinb, val);
  }
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "sun_per_day"));
  hours = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "pv_volts"));
  pv_volts = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);

  /* These are the other items that get updated when this item changes*/
  entry = lookup_widget(GTK_WIDGET(MainWindow), "current_entry");
  amps =  val/hours;
  sprintf(buf, "%3.4g", amps);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* We use the standardized 12 or 24 volts to calculate the panels in series */
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_series_e");
  if (currentgpv->Vmp < 24.0) {
    series = (pv_volts / 12);
  }
  else {
    series = (pv_volts / 24);
  }
  sprintf(buf, "%g", series);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Now calculate how many strings of panels are needed */
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_par_entry");
  parallel = rint((amps/currentgpv->Imp) + 0.5);
  //  parallel = rint(((amps/currentgpv->Imp)/(pv_volts/volts)) + 0.5);
  sprintf(buf, "%g", parallel);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "total_modules");
  total = series * parallel;
  sprintf(buf, "%g", total);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_cost_e");
  sprintf(buf, "$ %g", currentgpv->Price * total);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "array_entry");
  array_current = (currentgpv->Imp * parallel) * (pv_volts/volts);
  sprintf(buf, "%3.4g", array_current);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* These are the data inputs for the PV Array calculations */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "reserve_entry"));
  time = gtk_spin_button_get_value_as_int(spinb);
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "usable_entry"));
  usable = gtk_spin_button_get_value_as_int(spinb);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "capacity_entry");
  min_amps =  (val * time) * (100/usable);
  /* Batteries don't like cold. Adjust for the lowest temperature */
  factor = ((77 - lowtemp) * 0.67) * 0.01;
  // g_print("%g\n", factor);
  min_amps += min_amps * factor;
  sprintf(buf, "%g", min_amps);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  if (current_battery == NULL)
    current_battery = &batteries[0];

  entry = lookup_widget(GTK_WIDGET(MainWindow), "battery_series_entry");
  bseries = volts/current_battery->voltage;
  sprintf(buf, "%g", bseries);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "battery_parallel_entry");
  bparallel = (gdouble)rint((min_amps / (current_battery->rate20 *
                             OLD_BATTERY_FACTOR)) + 0.5);
  
  sprintf(buf, "%g", bparallel);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "total_batteries");
  btotal = bseries * bparallel;
  sprintf(buf, "%g", btotal);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "battery_cost_e");
  sprintf(buf, "$ %g", current_battery->price * btotal);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "battery_entry");
  sprintf(buf, "%g", (current_battery->rate20 * OLD_BATTERY_FACTOR) * bparallel);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "system_price_entry");
#if 0
  printf ("%g %g %g %g %g\n", ((current_inverter) ? current_inverter->price : 0.0 ),
    ((current_charger)  ?  current_charger->price   : 0.0),
    ((current_combiner) ?  current_combiner->price  : 0.0),
    ((currentgpv)        ? (total * currentgpv->Price) : 0.0),
    ((current_battery)  ? (current_battery->price * btotal) : 0.0));
#endif
  price = ((current_inverter) ? current_inverter->price : 0.0 )
    + ((current_charger)  ? current_charger->price : 0.0)
    + ((current_combiner) ? current_combiner->price : 0.0)
    + ((currentgpv) ?  total * currentgpv->Price : 0.0)
    + ((current_battery) ? (current_battery->price * btotal) : 0.0);
  sprintf(buf, "$ %g", price);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

#if 0
  if (current_charger) {
    if (array_current > current_charger->amperage) {
      Popup_Warning ("The Charger controller is too small for the array!");
    }
  }
#endif
}


void
on_reserve_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}


void
on_capacity_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}

#if 0
void
on_add_load_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  AddLoad =  create_LoadWin();

  UpdateStatusMsg(1, "New Add Load Window");

  gtk_widget_show (AddLoad);
}
#endif

void
on_display_loads_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  dump_loads();
}


void
on_save_loads_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  filestate = LOADWRITE;
  write_loads("");
}


void
on_save_as_loads_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  FileDialog = create_fileselection();

  filestate = LOADWRITE;
  
  gtk_widget_show(FileDialog);
}


void
on_open_loads_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  FileDialog = create_fileselection();
  filestate = LOADOPEN;

  gtk_widget_show(FileDialog);
}


void
init_data                              (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  char *prevname;
  int i, idx, pvnames;
  pvpanel_t *pvp;
  struct gpv_panel *gpv;
  GList *Module_items = NULL;
  GList *Battery_items = NULL;
  GList *Inverter_items = NULL;
  GList *Center_items = NULL;
  GList *Charger_items = NULL;
  GList *Combiner_items = NULL;

  // Grab the values as set by Glade. This way we don't have to set them twice
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  GPVData.nominal_voltage = gtk_spin_button_get_value_as_int(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "pv_volts"));
  GPVData.array_voltage = gtk_spin_button_get_value_as_int(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "sun_per_day"));
  GPVData.hours_of_sun = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "reserve_entry"));
  GPVData.reserve_time = gtk_spin_button_get_value_as_int(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "usable_entry"));
  GPVData.usable_capacity = gtk_spin_button_get_value_as_int(spinb);

  // These should be unset to start
  GPVData.current_needed = 0;
  GPVData.mod_series = 0;
  GPVData.mod_parallel = 0;
  GPVData.mod_total = 0;
  
  //  GPVData.battery;
  GPVData.capacity_needed = 0;
  GPVData.batt_series = 0;
  GPVData.batt_parallel = 0;
  GPVData.batt_total = 0;
  GPVData.wattage = 0;
  GPVData.amperage = 0;
  
  // Sort the names. As there are multiple entries for each module,
  // depending on the size of the array, or the year of the tests, we
  // filter them all out.
  pvnames = pv_data_size();
  
  prevname = "start";
  idx = 0;
  for (i=0; i<pvnames; i++){
    pvp = get_pvpanel(i);
    if (strcmp(prevname, pvp->Model) != 0) {
      Module_items = g_list_append (Module_items, (gpointer) pvp->Model);
      prevname = pvp->Model;
      gpv = g_malloc(sizeof(struct gpv_panel));
      gpv->Model = pvp->Model;
      gpv->Material = pvp->Material;
      gpv->Series_Cells = pvp->Series_Cells;
      gpv->Parallel_Cells = pvp->Parallel_C_S;
      gpv->Vmp = pvp->Vmpo;
      gpv->Voc = pvp->Voco;
      gpv->Price = pvp->Price;
      gpv->Imp = pvp->Impo;
      gpv->Isc = pvp->Isco;
      
      panel_data[idx++] = gpv;
    }
  }

  currentgpv = panel_data[0];
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pvcombo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Module_items);
  g_list_free (Module_items);

  // Battery combo box from database
  for (i=0; batteries[i].name != 0; i++){
    Battery_items = g_list_append (Battery_items, (gpointer)batteries[i].name);
  }
  current_battery = &batteries[0];
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "battery_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Battery_items);
  g_list_free (Battery_items);

  // Inverter combo box from database
  for (i=0; inverters[i].name != 0; i++){
    Inverter_items = g_list_append (Inverter_items, (gpointer)inverters[i].name);
  }
  current_inverter = &inverters[0];
  entry = lookup_widget(GTK_WIDGET(MainWindow), "inverter_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Inverter_items);
  g_list_free (Inverter_items);

  // Charger combo box from database
  for (i=0; chargers[i].name != 0; i++){
    Charger_items = g_list_append (Charger_items, (gpointer)chargers[i].name);
  }
  current_charger = &chargers[0];
  entry = lookup_widget(GTK_WIDGET(MainWindow), "charger_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Charger_items);
  g_list_free (Charger_items);

  // Combiner combo box from database
  for (i=0; combiners[i].name != 0; i++){
    Combiner_items = g_list_append (Combiner_items, (gpointer)combiners[i].name);
  }
  current_combiner = &combiners[0];
  entry = lookup_widget(GTK_WIDGET(MainWindow), "combiner_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Combiner_items);
  g_list_free (Combiner_items);

  // Power Center from database
  for (i=0; centers[i].name != 0; i++){
    Center_items = g_list_append (Center_items, (gpointer)centers[i].name);
  }
  current_center = &centers[0];
  entry = lookup_widget(GTK_WIDGET(MainWindow), "center_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Center_items);
  g_list_free (Center_items);

  memset(&wiredata,0,sizeof(wiredata));

  /* Read in the default config files */
  read_system("");
}

#if 0
void
populate_loads(void);
{
  GtkWidget *minutes_spin[100];
  GtkWidget *days_spin[100];
  GtkWidget *load_entry[100];

  idx = 0;  

  /* */
  load_entry = gtk_entry_new ();
  gtk_widget_ref (load_entry);
  gtk_object_set_data_full (GTK_OBJECT (ChooseLoads), "load_entry", load_entry,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (load_entry);
  gtk_fixed_put (GTK_FIXED (fixed8), load_entry, 8, 40);
  gtk_widget_set_uposition (load_entry, 8, 40);
  gtk_widget_set_usize (load_entry, 158, 22);
}
#endif

void
on_choose_loads_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

void
on_temp_changed                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}


void
on_pv_volts_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_data();
}


/* The user changed the battery in the Main Window */
void
on_battery_changed                     (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry2");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; batteries[i].name != 0 ; i++) {
    if (strcmp(batteries[i].name, ptr) == 0){
      current_battery = &batteries[i];
      update_data();
      break;
    }    
  }
}


void
on_pv_changed                          (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; panel_data[i] != 0 ; i++) {
    if (strcmp(panel_data[i]->Model, ptr) == 0){
      currentgpv = panel_data[i];
      update_data();
      break;
    }    
  }

}

void
on_wiring_sizes_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  WiringWindow = create_WiringWIndow();
  
  UpdateStatusMsg(1, "New Wiring Sizes Window");

  gtk_widget_show (WiringWindow);  
}

void
on_generate_parts_list_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_center_entry_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "center_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; centers[i].name != 0 ; i++) {
    if (strcmp(centers[i].name, ptr) == 0){
      current_center = &centers[i];
      update_data();
      break;
    }    
  }  
}


void
on_charger_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "charger_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; chargers[i].name != 0 ; i++) {
    if (strcmp(chargers[i].name, ptr) == 0){
      current_charger = &chargers[i];
      update_data();
      break;
    }
  }
}


void
on_inverter_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "inverter_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; inverters[i].name != 0 ; i++) {
    if (strcmp(inverters[i].name, ptr) == 0){
      current_inverter = &inverters[i];
      update_data();
      break;
    }    
  }
}


void
on_combiner_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combiner_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; combiners[i].name != 0 ; i++) {
    if (strcmp(combiners[i].name, ptr) == 0){
      current_combiner = &combiners[i];
      update_data();
      break;
    }    
  }  
}


void
on_inverters1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  InverterWindow = create_InverterBrowser();
  
  UpdateStatusMsg(1, "New Inverter Browser Window");

  gtk_widget_show (InverterWindow);
}


void
on_batteries_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  BatteryWindow = create_BatteryWindow();
  
  UpdateStatusMsg(1, "New Batteries Browser Window");

  gtk_widget_show (BatteryWindow);
}


void
on_charge_controllers_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  ChargerWindow = create_ChargerWindow();
  
  UpdateStatusMsg(1, "New Charge Controller Browser Window");

  gtk_widget_show (ChargerWindow);  
}

void
on_InverterBrowser_map                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  int i;
  GList *Inverter_items = NULL;

  for (i=0; inverters[i].name != 0; i++){
    Inverter_items = g_list_append (Inverter_items, (gpointer)inverters[i].name);
  }
  entry = lookup_widget(GTK_WIDGET(InverterWindow), "invert_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Inverter_items);
  g_list_free (Inverter_items);
}



void
on_inverter_model_changed              (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  char buf[100];
  int i;
  gchar *ptr;
  inverter_t *iptr;

  entry = lookup_widget(GTK_WIDGET(InverterWindow), "model");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  iptr = &inverters[0];
  for (i=0; inverters[i].name != 0 ; i++) {
    if (strcmp(inverters[i].name, ptr) == 0){
      iptr = &inverters[i];
      break;
    }    
  }
  
  entry = lookup_widget(GTK_WIDGET(InverterWindow), "invert_manufact_entry");
  gtk_entry_set_text(GTK_ENTRY(entry), iptr->manufacturer);  

  entry = lookup_widget(GTK_WIDGET(InverterWindow), "invert_input_entry");
  sprintf(buf, "%d ", iptr->voltage);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(InverterWindow), "invert_output_entry");
  sprintf(buf, "%d ", iptr->wattage);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "inverter_entry");
  sprintf(buf, "%s", iptr->name);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);  
}


void
on_charger_list_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  
  GtkWidget *entry;
  GtkToggleButton *toggle;
  char buf[100];
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "charger_list");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; chargers[i].name != 0 ; i++) {
    if (strcmp(chargers[i].name, ptr) == 0){
      current_charger = &chargers[i];
      break;
    }    
  }

  if (current_charger == NULL)
    current_charger = &chargers[0];
  
  /* update the entry on the Charger Controller Browser Window */
  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "man_entry");
  sprintf(buf, "%s", current_charger->manufacturer);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "voltsin_entry");
  sprintf(buf, "%d VDC", current_charger->volts_in);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "voltsout_entry");
  sprintf(buf, "%d VDC", current_charger->volts_out);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "maxamps_entry");
  sprintf(buf, "%d Amps", current_charger->amperage);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "maxvolts_entry");
  if (current_charger->openmax > 0) {
    sprintf(buf, "%g VDC", current_charger->openmax);
  } else {
    sprintf(buf, "no data");
  }
  
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "efficiency_entry");
  if (current_charger->efficiency != 1) {
    sprintf(buf, "%g %%", current_charger->efficiency * 100);
  } else {
    sprintf(buf, "No data");
  }
    gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "charger_price_entry");
  sprintf(buf, "$ %g", current_charger->price);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(ChargerWindow), "charger_lcd_check"));
  if (current_charger->lcd == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(ChargerWindow), "charger_mppt_check"));
  if  (current_charger->MPPT == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(ChargerWindow), "charger_pwm_check"));
  if  (current_charger->PWM == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(ChargerWindow), "charger_temp_check"));
  if  (current_charger->tempsensor == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(ChargerWindow), "charger_remote_check"));
  if  (current_charger->remote == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "charger_entry");
  sprintf(buf, "%s", current_charger->name);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

}


void
on_Charger_map                         (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  char buf[100];
  int i;
  GList *Charger_items = NULL;

  for (i=0; chargers[i].name != 0; i++){
     Charger_items = g_list_append (Charger_items, (gpointer)chargers[i].name);
  }

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "charger_list_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Charger_items);
  g_list_free (Charger_items);

  entry = lookup_widget(GTK_WIDGET(ChargerWindow), "charger_list");
  sprintf(buf, "%s", current_charger->name);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}


void
on_fixed12_map                         (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  int i;
  GList *Combiner_items = NULL;

  for (i=0; combiners[i].name != 0; i++){
     Combiner_items = g_list_append (Combiner_items, (gpointer)combiners[i].name);
  }

  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Combiner_items);
  g_list_free (Combiner_items);
}


void
on_pv_combiner_boxes_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  CombinerWindow = create_CombinerWindow();
  
  UpdateStatusMsg(1, "New PV Combiner Box Browser Window");

  gtk_widget_show (CombinerWindow);
}


void
on_combiner_browser__entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  char buf[100];
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; combiners[i].name != 0 ; i++) {
    if (strcmp(combiners[i].name, ptr) == 0){
      current_combiner = &combiners[i];
      break;
    }    
  }

  /* update the entry on the Combiner Controller Browser Window */
  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_man_entry");
  sprintf(buf, "%s", current_combiner->manufacturer);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_in_entry");
  sprintf(buf, "%d", current_combiner->circuits);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_out_entry");
  sprintf(buf, "%d", current_combiner->conductors);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(CombinerWindow), "combiner_price_entry");
  sprintf(buf, "$ %g", current_combiner->price);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combiner_entry");
  sprintf(buf, "%s", current_combiner->name);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}


void
on_battery_browser_map                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  char buf[100];
  int i;
  GList *Battery_items = NULL;

  for (i=0; batteries[i].name != 0; i++){
     Battery_items = g_list_append (Battery_items, (gpointer)batteries[i].name);
  }

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "batt_browser_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Battery_items);
  g_list_free (Battery_items);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "man_entry");
  sprintf(buf, "%s", current_battery->manufacturer);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "type_entry");
  sprintf(buf, "no type info yet");
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "rate20_entry");
  sprintf(buf, "%d", current_battery->rate20);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "rate100_entry");
  sprintf(buf, "%d", current_battery->rate100);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "volts_entry");
  sprintf(buf, "%d", current_battery->voltage);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "price_entry");
  sprintf(buf, "$ %g", current_battery->price);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}


void
on_batt_browser_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  char buf[100];
  gchar *ptr;
  int i;

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "batt_browser_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  for (i=0; batteries[i].name != 0 ; i++) {
    if (strcmp(batteries[i].name, ptr) == 0){
      current_battery = &batteries[i];
      break;
    }    
  }

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "man_entry");
  sprintf(buf, "%s", current_battery->manufacturer);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "type_entry");
  sprintf(buf, "no type info yet");
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "rate20_entry");
  sprintf(buf, "%d", current_battery->rate20);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "rate100_entry");
  sprintf(buf, "%d", current_battery->rate100);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "volts_entry");
  sprintf(buf, "%d", current_battery->voltage);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(BatteryWindow), "price_entry");
  sprintf(buf, "$ %g", current_battery->price);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}


void
Popup_Warning (char *msg)
{
  GtkWidget *WarningBox;
  GtkWidget *dialog_vbox1;
  GtkWidget *button2;
  GtkWidget *dialog_action_area1;

  /* We create it with an OK button, and then remove the button, to work
     around a bug in gnome-libs. */
  WarningBox = gnome_message_box_new (msg,
                              GNOME_MESSAGE_BOX_WARNING,
                              GNOME_STOCK_BUTTON_OK, NULL);
  gtk_container_remove (GTK_CONTAINER (GNOME_DIALOG (WarningBox)->action_area),
                        GNOME_DIALOG (WarningBox)->buttons->data);
  GNOME_DIALOG (WarningBox)->buttons = NULL;
  gtk_object_set_data (GTK_OBJECT (WarningBox), "WarningBox", WarningBox);
  gtk_window_set_title (GTK_WINDOW (WarningBox), "Warning!");
  gtk_window_set_policy (GTK_WINDOW (WarningBox), FALSE, FALSE, FALSE);

  dialog_vbox1 = GNOME_DIALOG (WarningBox)->vbox;
  gtk_object_set_data (GTK_OBJECT (WarningBox), "dialog_vbox1", dialog_vbox1);
  gtk_widget_show (dialog_vbox1);

  gnome_dialog_append_button (GNOME_DIALOG (WarningBox), GNOME_STOCK_BUTTON_OK);
  button2 = GTK_WIDGET (g_list_last (GNOME_DIALOG (WarningBox)->buttons)->data);
  gtk_widget_ref (button2);
  gtk_object_set_data_full (GTK_OBJECT (WarningBox), "button2", button2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button2);
  GTK_WIDGET_SET_FLAGS (button2, GTK_CAN_DEFAULT);

  dialog_action_area1 = GNOME_DIALOG (WarningBox)->action_area;
  gtk_widget_ref (dialog_action_area1);
  gtk_object_set_data_full (GTK_OBJECT (WarningBox), "dialog_action_area1", dialog_action_area1,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_signal_connect (GTK_OBJECT (button2), "clicked",
                      GTK_SIGNAL_FUNC (gtk_widget_hide),
                      NULL);
  gtk_widget_show(WarningBox);
}

void
on_Wiring_map                          (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  gchar buf[100];
  gchar *ptr;

  set_wiresize_items (widget, "wiring_combo1");
  set_wiresize_items (widget, "wiring_combo2");
  set_wiresize_items (widget, "wiring_combo3");
  set_wiresize_items (widget, "wiring_combo4");
  set_wiresize_items (widget, "wiring_combo5");
  set_wiresize_items (widget, "wiring_combo6");
  set_wiresize_items (widget, "wiring_combo7");
  set_wiresize_items (widget, "wiring_combo8");
  set_wiresize_items (widget, "wiring_combo9");

  /* Module to Module  */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin1"));
  gtk_spin_button_set_value(spinb, wiredata.pv2pv.distance);
  entry = lookup_widget(widget, "wiring_entry1");
  if (wiredata.pv2pv.awg == 0)
    sprintf(buf, "none");
  else
    sprintf(buf, "%s", awg2str(wiredata.pv2pv.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
  /* PV Combiner to Charger  */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin2"));
  gtk_spin_button_set_value(spinb, wiredata.combiner2charger.distance);
  entry = lookup_widget(widget, "wiring_entry2");
  if (wiredata.combiner2charger.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.combiner2charger.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);  

  /* Wind Generator to Charger  */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin3"));
  gtk_spin_button_set_value(spinb, wiredata.wind2charger.distance);
  entry = lookup_widget(widget, "wiring_entry3");
  if (wiredata.wind2charger.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.wind2charger.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Charge Controller to Battery Bank */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin4"));
  gtk_spin_button_set_value(spinb, wiredata.charger2battery.distance);
  entry = lookup_widget(widget, "wiring_entry4");
  if (wiredata.charger2battery.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.charger2battery.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Battery to Inverter */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin5"));
  gtk_spin_button_set_value(spinb, wiredata.battery2invert.distance);
  entry = lookup_widget(widget, "wiring_entry5");
  if (wiredata.battery2invert.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.battery2invert.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Invert to Building 120VAC */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin6"));
  gtk_spin_button_set_value(spinb, wiredata.invert2bld120.distance);
  entry = lookup_widget(widget, "wiring_entry6");
  if (wiredata.invert2bld120.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.invert2bld120.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

#if 0
  for (i=0; panel_data[i] != 0 ; i++) {
    if (strcmp(panel_data[i]->Model, ptr) == 0){
      currentgpv = panel_data[i];
      g_print("Current Pv Panel is %s\n", currentpv->Model);
      break;
    }    
  }

  /* Invert to Building 12VDC */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin7"));
  gtk_spin_button_set_value(spinb, wiredata.invert2bld24.distance);
  entry = lookup_widget(widget, "wiring_entry7");
  if (wiredata.invert2bld24.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.invert2bld24.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Invert to Building 120VAC */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin8"));
  gtk_spin_button_set_value(spinb, wiredata.invert2bld12.distance);
  entry = lookup_widget(widget, "wiring_entry8");
  if (wiredata.invert2bld12.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.invert2bld12.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  /* Ground wire */
  spinb = GTK_SPIN_BUTTON(lookup_widget(widget, "wiring_spin9"));
  gtk_spin_button_set_value(spinb, wiredata.ground.distance);
  entry = lookup_widget(widget, "wiring_entry9");
  if (wiredata.ground.awg == 0)
    sprintf(buf, "none");
  else    
    sprintf(buf, "%s", awg2str(wiredata.ground.awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
#endif
}

void
update_wiring(void)
{
#if 0
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar buf[100];
  int distance, awg;
  gdouble nominal_volts, pv_volts, amps, lowtemp, hightemp, breaker;
  gdouble drop, loss;
  gchar *ptr;

  /* Turn on debugging messages for the NEC calculations */
  nec_toggle_debug(TRUE);
  
  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  nominal_volts = gtk_spin_button_get_value_as_int(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "pv_volts"));
  pv_volts = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "current_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  amps = atof(ptr);

  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin1"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  awg = nec_find_gauge(distance, pv_volts, amps, hightemp);
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry1");
  gtk_entry_set_text(GTK_ENTRY(entry), awg2str(awg));

  wiredata.pv2pv.distance = distance;
  wiredata.pv2pv.awg = awg;

  /* Do the PV Combiner to Charger calculation */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin2"));
  distance = gtk_spin_button_get_value_as_int(spinb);

  awg = nec_find_gauge(distance, nominal_volts, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry2");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.combiner2charger.distance = distance;
  wiredata.combiner2charger.awg = awg;

  /* PV Array to Charge Controller calculation */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin3"));
  distance = gtk_spin_button_get_value_as_int(spinb);

  awg = nec_find_gauge(distance, nominal_volts, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry3");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.wind2charger.distance = distance;
  wiredata.wind2charger.awg = awg;

  /* Do the charge controller to batteries calculation */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin4"));
  distance = gtk_spin_button_get_value_as_int(spinb);

  awg = nec_find_gauge(distance, nominal_volts, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry4");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.charger2battery.distance = distance;
  wiredata.charger2battery.awg = awg;

  /* Batteries to Inverter */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin5"));
  distance = gtk_spin_button_get_value_as_int(spinb);

  awg = nec_find_gauge(distance, 12.0, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry5");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.battery2invert.distance = distance;
  wiredata.battery2invert.awg = awg;

  /* Inverter & Battery bank to building */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin6"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  awg = nec_find_gauge(distance, 24, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry6");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.invert2bld120.distance = distance;
  wiredata.invert2bld120.awg = awg;
  
  awg = nec_find_gauge(distance, 120, amps, hightemp);  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry7");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.invert2bld24.distance = distance;
  wiredata.invert2bld24.awg = awg;

  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry8");
  awg = nec_find_gauge(distance, 12, amps, hightemp);  
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  wiredata.invert2bld12.distance = distance;
  wiredata.invert2bld12.awg = awg;

  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry9");
  awg = nec_find_ground();
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  nec_toggle_debug(FALSE);      /* FIXME: */
#endif
  
}

void
on_wiring_spin4_changed                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar *ptr, buf[100];
  gdouble volts, amps, lowtemp, hightemp;
  int awg, parallel, distance, series;

  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  volts = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_series_e");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  series = atoi(ptr);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_par_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  parallel = atoi(ptr);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  /* Turn on debugging messages for the NEC calculations */
  nec_toggle_debug(TRUE);
  
  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin2"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  amps = currentgpv->Imp;
  awg =  nec_awg_combiner2charger(distance, volts * series, amps * parallel, hightemp, 1);
  
  wiredata.combiner2charger.distance = distance;
  wiredata.combiner2charger.awg = awg;

  /* Turn off debugging messages for the NEC calculations */
  nec_toggle_debug(FALSE);

  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry2");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}

void
on_load_active_toggled                 (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  thisload = find_load(ptr); 
  thisload->active = (thisload->active) ? 0 : 1;
}


gboolean
on_load_hour_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "hours_spin"));
  thisload->hours = gtk_spin_button_get_value_as_float(spinb);

  g_print("Hours now %f\n", thisload->hours);
  update_watts_used(calc_watts(thisload));

  return FALSE;
}


gboolean
on_load_mins_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "mins_spin"));
  thisload->minutes = gtk_spin_button_get_value_as_float(spinb);

  g_print("Minutes now %f\n", thisload->minutes);
  update_watts_used(calc_watts(thisload));

  return FALSE;
}



gboolean
on_load_volts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "volts_spin"));
  thisload->voltage = gtk_spin_button_get_value_as_float(spinb);

  thisload->amperage = nec_amps(thisload->wattage, thisload->voltage);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "amps_spin"));
  gtk_spin_button_set_value(spinb, thisload->amperage);

  update_watts_used(calc_watts(thisload));

  return FALSE;
}



gboolean
on_load_amps_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "amps_spin"));
  thisload->amperage = gtk_spin_button_get_value_as_float(spinb);
  
  thisload->wattage = nec_watts(thisload->voltage, thisload->amperage);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "watts_spin"));
  gtk_spin_button_set_value(spinb, thisload->wattage);

  update_watts_used(calc_watts(thisload));

  return FALSE;
}


gboolean
on_load_watts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "watts_spin"));
  thisload->wattage = gtk_spin_button_get_value_as_float(spinb);

  thisload->amperage = nec_amps(thisload->wattage, thisload->voltage);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "amps_spin"));
  gtk_spin_button_set_value(spinb,  thisload->amperage);

  update_watts_used(calc_watts(thisload));

  return FALSE;
}



gboolean
on_load_days_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "days_spin"));
  thisload->days = gtk_spin_button_get_value_as_float(spinb);
  g_print("Days now %g\n", thisload->days);
  update_watts_used(calc_watts(thisload));

  return FALSE;
}


void
on_load_edit_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  EditLoad =  create_LoadWin();

  UpdateStatusMsg(1, "New Edit Load Window");

  gtk_widget_show (EditLoad);
}

void
on_LoadWin_map                         (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  int i, count;
  const char *namelist[300];
  load_t *thisload;

  read_loads_CSV("");

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  thisload = find_load("12' Refridgerator");
  
  gtk_entry_set_text(GTK_ENTRY(entry), thisload->name);

  if (Load_items == NULL) {
    count = load_names(namelist);
    
#if 0
    for (i=0; loads[i].name != 0; i++){
      Load_items = g_list_append (Load_items, (gpointer)loads[i].name);
    }
#else
    for (i=0;  i<count-1; i++){
      Load_items = g_list_append (Load_items, (gpointer)namelist[i]);
    }
#endif
  }

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Load_items);
  //  g_list_free (Load_items);

  update_watts_used(calc_watts(thisload));
}


void
on_load_device_entry_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkToggleButton *toggle;
  GtkRadioButton *radio; 
  GtkSpinButton *spinb;
  GSList *group = NULL;
  load_t *thisload;
  gchar *ptr;
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr);

  entry = lookup_widget(GTK_WIDGET(EditLoad), "load_group_entry");
  gtk_entry_set_text (GTK_ENTRY (entry), loadgroup_strs[thisload->group]);
  
  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "volts_spin"));
  gtk_spin_button_set_value(spinb, thisload->voltage);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "amps_spin"));
  if (thisload->amperage <= 0.0)
    thisload->amperage = nec_amps(thisload->wattage, thisload->voltage);
  gtk_spin_button_set_value(spinb, thisload->amperage);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "watts_spin"));
  if (thisload->wattage <= 0.0)
    thisload->wattage = nec_watts(thisload->voltage, thisload->amperage);  
  gtk_spin_button_set_value(spinb, thisload->wattage);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "hours_spin"));
  gtk_spin_button_set_value(spinb, thisload->hours);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "mins_spin"));
  gtk_spin_button_set_value(spinb, thisload->minutes);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "days_spin"));
  gtk_spin_button_set_value(spinb, thisload->days);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "quantity_spin"));
  gtk_spin_button_set_value(spinb, thisload->quantity);

  entry = lookup_widget(GTK_WIDGET(EditLoad), "text1");
  gtk_text_set_word_wrap(GTK_TEXT (entry), TRUE);
  gtk_text_backward_delete(GTK_TEXT (entry),
                           gtk_text_get_length(GTK_TEXT (entry)));  
  if (thisload->description != NULL) {
    gtk_text_insert (GTK_TEXT (entry),
                     NULL,  NULL, NULL,
                     thisload->description, strlen(thisload->description));
  }

  /* Set the "is device active" toggle */
  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "active"));
  if (thisload->active == YES)
    gtk_toggle_button_set_active(toggle, TRUE);
  else
    gtk_toggle_button_set_active(toggle, FALSE);

  /* Set the AC/DC radio button */
  radio = GTK_RADIO_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "dc_radiobutton"));
  group = gtk_radio_button_group (radio);

  /* See which element of the group is active */
  //  for (i=0; i<g_slist_length(group); i++) {
  
  if (thisload->type == DC) {
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (g_slist_nth(group, 0)->data), TRUE);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (g_slist_nth(group, 1)->data), FALSE);
  } else {
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (g_slist_nth(group, 0)->data), FALSE);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (g_slist_nth(group, 1)->data), TRUE);
  }

  update_watts_used(calc_watts(thisload));
  //  dump_load(thisload);
}

void
on_new_load_released                   (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
#if 0
  gchar *ptr;
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  g_print("Device is %s\n", ptr);
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "load_group_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  g_print("Load Group is %s\n", ptr);
#endif
  
  DialogBox = create_text_dialog();

  entry = lookup_widget(GTK_WIDGET(DialogBox), "input_label");
  gtk_label_set_text(GTK_LABEL(entry), "Load Name");

  gtk_widget_show (DialogBox);
    
  //  on_load_device_entry_changed((GtkEditable *)0, (gpointer)0);
}


void
on_text_ok_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *ptr;
  load_t *item;
  GtkWidget *entry;

  entry = lookup_widget(GTK_WIDGET(DialogBox), "input_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  item = g_malloc(sizeof(load_t));
  
  item->name = ptr;
  item->description = NULL;
  item->type = DC;
  item->group = NOGROUP;
  item->voltage = 12.0;
  item->wattage = 1.0;
  item->amperage = 0.0;
  item->hours = 0.0;
  item->minutes = 0.0;
  item->days = 1;
  item->quantity = 1;
  item->active = FALSE;

  add_load(item);
  
  Load_items = g_list_append (Load_items, (gpointer)item->name);

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_combo");
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), Load_items);
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  gtk_entry_set_text(GTK_ENTRY(entry), item->name);

  /* get rid of the dialog box */
  entry = lookup_widget(GTK_WIDGET(DialogBox), "text_dialog");
  gtk_widget_hide(entry);
}

void
on_text_cancel_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  
  entry = lookup_widget(GTK_WIDGET(DialogBox), "text_dialog");

  gtk_widget_destroy(entry);
}


void
on_text1_changed                       (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  gchar *ptr;
  load_t *thisload;
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  thisload = find_load(ptr);
  entry = lookup_widget(GTK_WIDGET(EditLoad), "text1");
  ptr = (gchar *)gtk_editable_get_chars(editable, 0, -1);
  
  if (thisload->description != NULL) {
    free(thisload->description);
  }
  
  thisload->description = g_malloc(256);
  strcpy(thisload->description, ptr);
}


gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  load_t *thisload = 0;
  static char buf[256];
  static char *bufptr = buf;
  gchar *ptr;

  //  g_print("Pressed key in text box\n");

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  if (bufptr == buf) {
    thisload = find_load(ptr);
    if (thisload->description != NULL) {
      strcpy(buf, thisload->description);
      bufptr += strlen(thisload->description);
    } else {
      thisload->description = g_malloc(256);
    }
  }
  
  ptr = gdk_keyval_name(event->keyval);
  entry = lookup_widget(GTK_WIDGET(EditLoad), "text1");

  if (strcmp(ptr, "BackSpace") == 0) {
    *bufptr-- = 0;
    gtk_text_backward_delete(GTK_TEXT (entry), 1);
  
    return FALSE;
  }
  
  /* User hit [Enter] */
  if (strcmp(ptr, "Return") == 0) {
    *bufptr = 0;
    g_print("Done: %s\n", gtk_editable_get_chars(GTK_EDITABLE(widget), 0, -1));
    //    g_print("Done...%s\n", buf);
    strcpy(thisload->description, gtk_editable_get_chars(GTK_EDITABLE(widget), 0, -1));
    
    bufptr = buf;
    memset(buf, 0, 256);
    
    return FALSE;
  }
    
  *bufptr++ = *ptr;
  gtk_text_insert (GTK_TEXT (entry), NULL,  NULL, NULL, ptr, 1);
  
  return FALSE;
}



void
on_text1_activate                      (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  load_t *thisload;
  static char buf[256];
  static char *bufptr = buf;
  gchar *ptr;
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  
  thisload = find_load(ptr);
  if (thisload->description != NULL) {
    strcpy(buf, thisload->description);
    bufptr += strlen(thisload->description);
  } else {
    thisload->description = g_malloc(256);
  }

  //  ptr = gdk_keyval_name(event->keyval);

  g_print("text 1 got an activate event, key was %s\n", ptr);
  
  //  entry = lookup_widget(GTK_WIDGET(EditLoad), "text1");
  
  // length = gtk_text_get_length(GTK_TEXT (entry));

  //  g_print("%s\n", gtk_editable_get_chars(entry, 0, -1));
  
  //  gtk_text_insert (GTK_TEXT (entry), NULL,  NULL, NULL, ptr, 1);
  
}


void
on_device_entry_activate               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  g_print("device activate!\n");
}


void
on_input_entry_activate                (GtkEditable     *editable,
                                        gpointer         user_data)
{
  g_print("input activate!\n");
  on_text_ok_clicked((GtkButton *)0, (gpointer)0);  
}


gboolean
on_load_quantity_spin_event            (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "quantity_spin"));
  thisload->quantity = gtk_spin_button_get_value_as_float(spinb);

  return FALSE;
}


void
on_file_ok_released                    (GtkButton       *button,
                                        gpointer         user_data)
{
  gchar *ptr;
  ptr = gtk_file_selection_get_filename(GTK_FILE_SELECTION(FileDialog));

  switch (filestate) {
  case LOADOPEN:
    read_loads_CSV(ptr);
    break;
  case LOADWRITE:
    write_loads(ptr);
    break;
  case SYSTEMOPEN:
    read_system(ptr);
    break;
  case SYSTEMWRITE:
    write_system(ptr);
    break;
  case PVOPEN:
  case PVWRITE:
  case BATTOPEN:
  case BATTWRITE:
  case CHARGERSOPEN:
  case CHARGERSWRITE:
  case COMBINOPEN:
  case COMBINWRITE:
  case INVERTOPEN:
  case INVERTWRITE:
    break;
  default:
    break;
  };

  filestate = NOSTATE;
  gtk_widget_hide(FileDialog);
}


void
on_file_cancel_released                (GtkButton       *button,
                                        gpointer         user_data)
{
  filestate = NOSTATE;
  gtk_widget_hide(FileDialog);
}


gboolean
on_watts_entry_changed                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  return FALSE;
}


gboolean
on_amps_entry_changed                  (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkSpinButton *spinb;
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "amps_entry"));
#if 0
  GPVData.amperage = gtk_spin_button_get_value_as_int(spinb);
  val = (gdouble)GPVData.nominal_voltage/GPVData.amperage;
  if (val > 0.0){
    gtk_spin_button_set_value(spinb, val);
  }
#endif
  
  return FALSE;
}

void
update_watts_used(double watts)
{
  GtkWidget *entry;
  char buf[100];
  load_t *thisload;
  gchar *ptr;
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr);
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "used_entry");
  sprintf(buf, "%g", calc_watts(thisload));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
}  


void
on_display_active_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int i, count;
  gdouble watts, time;
  const char *namelist[300];
  load_t *thisload;
  GtkWidget *table, *clist;
  GtkWidget *label1;
  gchar *items[6], *buf;
  int rows = 0;

  count = load_names(namelist);
  
  table = create_col_list6();
  clist = lookup_widget(GTK_WIDGET(table), "clist3");

  gtk_clist_set_column_justification (GTK_CLIST(clist), 0, GTK_JUSTIFY_LEFT);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 4, GTK_JUSTIFY_CENTER);
  gtk_clist_set_column_justification (GTK_CLIST(clist), 5, GTK_JUSTIFY_CENTER);


  for (i=0;  i<count-1; i++) {
    thisload = find_load(namelist[i]);
    if(thisload->active == YES) {
      buf = g_malloc(strlen(thisload->name) + 1);
      sprintf(buf, "%s", thisload->name);
      items[0] = buf;
    
      buf = g_malloc(7);
      sprintf(buf, "%d", thisload->quantity);
      items[1] = buf;
    
      buf = g_malloc(7);
      sprintf(buf, "%g", thisload->voltage);
      items[2] = buf;
      
      buf = g_malloc(7);
      sprintf(buf, "%g", thisload->wattage);
      items[3] = buf;
      
      buf = g_malloc(7);
      //     time =  ((thisload->hours + (thisload->minutes/60)) * 7) / thisload->days;
      time = calc_hours_daily(thisload);
      sprintf(buf, "%6.2f", time);
      items[4] = buf;
      
      buf = g_malloc(7);
      watts = calc_watts(thisload);
      sprintf(buf, "%6.3f", watts);
      if (time < 1)
        sprintf(buf, "%6.3f", watts);
      else
        sprintf(buf, "%6.2f", watts);
      items[5] = buf;
      
      rows++;
      gtk_clist_append(GTK_CLIST (clist), items);
    }
  }
    
  gtk_window_set_title (GTK_WINDOW (table), "Active Loads");
  gtk_window_set_default_size (GTK_WINDOW (table), pixels_per_col*6,
                               pixels_per_row*rows);

  // Label the first column
  label1 = lookup_widget(GTK_WIDGET(table), "label53");
  gtk_label_set_text(GTK_LABEL(label1), "Device");

  // Label the second column
  label1 = lookup_widget(GTK_WIDGET(table), "label54");
  gtk_label_set_text(GTK_LABEL(label1), "Quantity");

  // Label the third column
  label1 = lookup_widget(GTK_WIDGET(table), "label55");
  gtk_label_set_text(GTK_LABEL(label1), "Voltage");

  // Label the fourth column
  label1 = lookup_widget(GTK_WIDGET(table), "label56");
  gtk_label_set_text(GTK_LABEL(label1), "Wattage");

  // Label the fifth column
  label1 = lookup_widget(GTK_WIDGET(table), "label57");
  gtk_label_set_text(GTK_LABEL(label1), "Hours/Day");

  // Label the sixth column
  label1 = lookup_widget(GTK_WIDGET(table), "label58");
  gtk_label_set_text(GTK_LABEL(label1), "Watts/Day");

  gtk_widget_show (table);
  
}

/* Save a file with the default name via the File->Save menu item */
void
on_save2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  filestate = SYSTEMWRITE;
  write_system("");
}


/* Save a file with the choosen name via the File->Save menu item */
void
on_save_as2_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  FileDialog = create_fileselection();

  filestate = SYSTEMWRITE;
  
  gtk_widget_show(FileDialog);
}



gboolean
on_wiring_spin1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar *ptr, buf[100];
  gdouble volts, amps;
  int awg, parallel, distance;

  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  volts = gtk_spin_button_get_value_as_float(spinb);

#if 0
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);
#endif
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_par_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  parallel = atoi(ptr);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  /* Turn on debugging messages for the NEC calculations */
  //  nec_toggle_debug(TRUE);
  
  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin1"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  amps = currentgpv->Imp;
  awg =  nec_awg_pv2pv(distance, currentgpv->Vmp, amps, 167, 1);
  
  wiredata.pv2pv.distance = distance;
  wiredata.pv2pv.awg = awg;

  /* Turn off debugging messages for the NEC calculations */
  //  nec_toggle_debug(FALSE);

  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry1");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  return FALSE;
}


gboolean
on_wiring_spin2_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar *ptr, buf[100];
  gdouble volts, amps, lowtemp, hightemp;
  int awg, parallel, distance, series;

  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  volts = gtk_spin_button_get_value_as_float(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);
  
  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_series_e");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  series = atoi(ptr);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_par_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  parallel = atoi(ptr);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "combo_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  /* Turn on debugging messages for the NEC calculations */
  nec_toggle_debug(TRUE);
  
  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin2"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  amps = currentgpv->Imp;
  awg =  nec_awg_combiner2charger(distance, volts * series, amps * parallel, hightemp, 1);
  
  wiredata.combiner2charger.distance = distance;
  wiredata.combiner2charger.awg = awg;

  /* Turn off debugging messages for the NEC calculations */
  nec_toggle_debug(FALSE);

  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry2");
  sprintf(buf, "%s", awg2str(awg));
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  return FALSE;
}


gboolean
on_wiring_combo1_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo3_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo2_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo4_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo5_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo6_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo7_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo8_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


gboolean
on_wiring_combo9_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  //  update_wiring();

  return FALSE;
}


void
on_nec_spin3_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();
}


void
on_nec_spin3_activate                  (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();
}

gboolean
on_nec_spin3_button_press_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  update_nec_wire_ampacity();
  
  return FALSE;
}


gboolean
on_nec_combo1_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  g_print("NEC Comb1 Press Event");

  return FALSE;
}


gboolean
on_nec_combo2_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}

gboolean
on_wiring_spin01_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_nec_spin4_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  update_nec_wire_ampacity();

  update_nec_conduit_size();

  return FALSE;
}


gboolean
on_nec_spin5_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();

  return FALSE;
}


gboolean
on_nec_spin6_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();

  return FALSE;
}


gboolean
on_nec_spin1_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();

  return FALSE;
}

void
update_nec_conduit_size(void)
{
  GtkWidget *entry;
  GtkSpinButton *spinv;
  GtkToggleButton *toggle;
  gchar *ptr, buf[100];
  //  struct nec_table4 *table;
  conduit_type_t condtype = EMT;
  wiretype_t wiretype;
  int awg, conductors;
  float dia;

  // If the Conduit toggle isn't checked, don't bother to do anything
  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_check"));
  if (gtk_toggle_button_get_active(toggle) == 0) {
    return;
  }
  

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry5");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  
  if (strcmp(ptr, "EMT") == 0)
    condtype = EMT;
  
  if (strcmp(ptr, "ENT") == 0)
    condtype = ENT;
  
  if (strcmp(ptr, "FMC") == 0)
    condtype = FMC;
  
  if (strcmp(ptr, "IMC") == 0)
    condtype = IMC;

  if (strcmp(ptr, "LFNC_B") == 0)
    condtype = LFNC_B;
  
  if (strcmp(ptr, "LFNC_A") == 0)
    condtype = LFNC_A;
  
  if (strcmp(ptr, "LFMC") == 0)
    condtype = LFMC;
  
  if (strcmp(ptr, "RMC") == 0)
    condtype = RMC;
  
  if (strcmp(ptr, "RNC") == 0)
    condtype = RNC;
  
  if (strcmp(ptr, "PVC_80") == 0)
    condtype = PVC_80;
  
  if (strcmp(ptr, "PVC_40") == 0)
    condtype = PVC_40;
  
  if (strcmp(ptr, "PVC_A") == 0)
    condtype = PVC_A;
  
  if (strcmp(ptr, "PVC_EB") == 0)
    condtype = PVC_EB;  

  //  table[condtype] = _nec_table4s[condtype];
  
  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  awg = str2awg(ptr);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry2");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  wiretype = str2wiretype(ptr);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin4"));
  conductors = gtk_spin_button_get_value_as_int(spinv);

  //  nec_toggle_debug(TRUE);
  dia = nec_find_conduit(awg, conductors, wiretype, condtype);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry3");
  sprintf(buf, "%4.3g", dia);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);
  
}

void
update_nec_wire_ampacity(void)
{
  GtkToggleButton *toggle;
  GtkSpinButton *spinv;
  GtkRadioButton *radio;
  GtkWidget *entry;
  GSList *group = NULL;
  gchar *ptr, buf[10];
  int awg, conductors, temp;
  gdouble amps;
  int copper, aluminum;

  int conduit;
  wiretype_t wiretype;
  
  toggle = GTK_TOGGLE_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_check"));
  conduit = gtk_toggle_button_get_active(toggle);
  
  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin4"));
  conductors = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin7"));
  temp = gtk_spin_button_get_value_as_int(spinv);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  awg = str2awg(ptr);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry2");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  wiretype = str2wiretype(ptr);

  radio = GTK_RADIO_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_radio1"));
  group = gtk_radio_button_group (radio);
  copper  = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON
                                          (g_slist_nth(group, 0)->data));
  aluminum = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON
                                           (g_slist_nth(group, 1)->data));

  amps = nec_wire_ampacity(awg, temp, conductors, conduit, wiretype);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry4");
  sprintf(buf, "%g", amps);
  gtk_entry_set_text(GTK_ENTRY(entry), buf);

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_radio1");
}

void
update_nec_loss_drop(void)
{      
  GtkWidget *entry;
  gchar *ptr;
  GtkSpinButton *spinv;
  int awg, distance, conductors;
  gdouble volts, amps, temp, drop, loss;  

  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  /* Get the numeric AWG value for the string value */
  awg = str2awg(ptr);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin1"));  
  volts = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin2"));
  amps = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin3"));
  distance = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin4"));
  conductors = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin7"));
  temp = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin5"));
  loss = nec_volt_loss(distance, awg, amps, temp, conductors);
  gtk_spin_button_set_value(spinv, loss);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin6"));

  drop = nec_volt_drop(awg, distance, volts, amps, temp, conductors);
  gtk_spin_button_set_value(spinv, drop);


  
}

void
nec_update_awg(GtkWidget *widget)
{
  GtkWidget *entry;
  GtkRadioButton *radio;
  GtkSpinButton *spinv;
  GSList *group = NULL;
  int awg, distance, conductors;
  gdouble volts, amps, temp, drop, loss;
  int copper, aluminum;
  
  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin1"));  
  volts = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin2"));
  amps = gtk_spin_button_get_value_as_float(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin3"));
  distance = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin4"));
  conductors = gtk_spin_button_get_value_as_int(spinv);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin7"));
  temp = gtk_spin_button_get_value_as_float(spinv);

  radio = GTK_RADIO_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_radio1"));
  group = gtk_radio_button_group (radio);
  copper  = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON
                                          (g_slist_nth(group, 0)->data));
  aluminum = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON
                                           (g_slist_nth(group, 1)->data));
  
  /* Find the gauge we need */
  awg = nec_find_gauge(distance, volts, amps, temp, conductors);
  entry = lookup_widget(GTK_WIDGET(widget), "nec_entry1");
  gtk_entry_set_text(GTK_ENTRY(entry),awg2str(awg));
  
  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin5"));
  loss = nec_volt_loss(distance, awg, amps, temp, conductors);
  gtk_spin_button_set_value(spinv, loss);

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin6"));
  drop = nec_volt_drop(awg, distance, volts, amps, temp, conductors);
  //  drop = (loss/volts) * 100;
  gtk_spin_button_set_value(spinv, drop);

  
}


gboolean
on_nec_spin2_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  //  update_nec_wire_ampacity();

  return FALSE;
}


gboolean
on_nec_spin7_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  update_nec_loss_drop();

  update_nec_wire_ampacity();
  
  return FALSE;
}

void
on_neccalc_realize                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkSpinButton *spinv;
  GtkWidget *entry;

  set_wiresize_items (widget, "nec_combo1");
  set_wiretype_items (widget, "nec_combo2");

  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin2"));
  gtk_spin_button_set_value(spinv, 4.33);
  
  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin3"));
  gtk_spin_button_set_value(spinv, 20);
  
  spinv = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(NECWin), "nec_spin7"));
  gtk_spin_button_set_value(spinv, 86);

  /* Default to single strand THWN2 wire */
  entry = lookup_widget(GTK_WIDGET(NECWin), "nec_entry2");
  gtk_entry_set_text(GTK_ENTRY(entry), "THWN2");

  update_nec_wire_ampacity();
  
  //  nec_update_awg(widget);
}


void
on_nec_entry1_changed                  (GtkEditable     *editable,
                                        gpointer         user_data)
{
    update_nec_loss_drop();

    update_nec_wire_ampacity();

    update_nec_conduit_size();
}


void
on_nec_entry2_changed                  (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_nec_wire_ampacity();

  update_nec_conduit_size();
}

/* Set the list of items for a Wire Size (AWG Gauge) combo box */
void
set_wiresize_items (GtkWidget *widget, gchar *item)
{
  int i;
  GtkWidget *entry;
  GList *size_items = NULL;

  // Battery combo box from database
  for (i=0; awglabels[i] != 0; i++){
    size_items = g_list_append (size_items, (gpointer)awglabels[i]);
  }
  
  entry = lookup_widget(GTK_WIDGET(widget), item);
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), size_items);
  g_list_free (size_items);
}

/* Set the list of items for a Wire Type combo box */
void
set_wiretype_items (GtkWidget *widget, gchar *item)
{
  int i;
  GtkWidget *entry;
  GList *type_items = NULL;

  // Battery combo box from database
  for (i=0; wiretypes[i] != 0; i++){
    type_items = g_list_append (type_items, (gpointer)wiretypes[i]);
  }
  
  entry = lookup_widget(GTK_WIDGET(widget), item);
  gtk_combo_set_popdown_strings (GTK_COMBO(entry), type_items);
  g_list_free (type_items);
}

void
on_wiring_entry4_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
}


void
on_wiring_entry3_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
}


void
on_wiring_entry2_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar *ptr;
  gdouble volts, pv_volts, amps, lowtemp, hightemp;
  int awg, calcawg, distance, parallel;

  /* Turn on debugging messages for the NEC calculations */
  //  nec_toggle_debug(TRUE);
  
  // These are the data inputs for the PV Array calculations
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  volts = gtk_spin_button_get_value_as_int(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "pv_volts"));
  pv_volts = gtk_spin_button_get_value_as_float(spinb);
  
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);

  entry = lookup_widget(GTK_WIDGET(MainWindow), "pv_par_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  parallel = atoi(ptr);

  amps = currentgpv->Imp;

  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin2"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  awg = atoi(ptr);
  
  wiredata.combiner2charger.distance = distance;
  wiredata.combiner2charger.awg = awg;

  //  nec_toggle_debug(TRUE);
  
  calcawg =  nec_awg_combiner2charger(distance, currentgpv->Vmp, amps* parallel, hightemp, 1);

  //  nec_toggle_debug(FALSE);

  if (awg  > calcawg) {
    Popup_Warning("Voltage Drop is too high!!!!!\n");
  }
}


void
on_wiring_entry5_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_wiring_entry8_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_wiring_entry7_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_wiring_entry6_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_wiring_entry9_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{

}


void
on_wiring_entry1_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  gchar *ptr;
  gdouble volts, amps;
  int awg, calcawg, distance;

  /* Turn on debugging messages for the NEC calculations */
  //  nec_toggle_debug(TRUE);
  
  // These are the data inputs for the PV Array calculations
  //  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "nominal_volts"));
  //  volts = gtk_spin_button_get_value_as_int(spinb);
#if 0
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_start_entry"));
  lowtemp = gtk_spin_button_get_value_as_int(spinb);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(MainWindow), "temp_end_entry"));
  hightemp = gtk_spin_button_get_value_as_int(spinb);
#else
  volts = currentgpv->Vmp;
  amps = currentgpv->Imp;
#endif
  
  /* Do the Module To Module */
  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(WiringWindow), "wiring_spin1"));
  distance = gtk_spin_button_get_value_as_int(spinb);
  
  entry = lookup_widget(GTK_WIDGET(WiringWindow), "wiring_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  awg = atoi(ptr);
  
  wiredata.pv2pv.distance = distance;
  wiredata.pv2pv.awg = awg;
  
  calcawg =  nec_awg_pv2pv(distance, volts, amps, 167, 1);

  if (awg  > calcawg) {
    Popup_Warning("Voltage Drop is too high!!!!!\n");
  }
}


gboolean
on_nec_spin_key_press_event            (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
  gchar *ptr;
  
  ptr = gdk_keyval_name(event->keyval);

  /* Don't do anything for a backspace, it's handled for us by GTK */
  if (strcmp(ptr, "BackSpace") == 0) {
    return FALSE;
  }

  /* For now, only update the awg when the user hits a return key */
  if (strcmp(ptr, "Return") == 0) {
    nec_update_awg(widget);
  }
  
  return FALSE;
}


gboolean
on_nec_calculate_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  nec_update_awg(widget);
  
  return FALSE;
}


gboolean
on_wiring_spin5_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_wiring_spin4_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_wiring_spin3_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_wiring_spin6_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}


gboolean
on_wiring_spin02_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{

  return FALSE;
}
// This supports the newer "Yelp" based GNOME 2 help system. If won't work
// till we are all running Gnome2.
#if 0
void
on_help_button_clicked (GtkWidget *widget, gpointer user_data)
{
  GError *error = NULL;
  
  gnome_help_display ("tracegui", "intro", &error);
  if (error) {
    GtkWidget *dialog;
    
    dialog = gtk_message_dialog_new (GTK_WINDOW (toplevel), GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE,
                                     _("Could not display help for "
                                       "TraceGUI.\n"
                                       "%s"),
                                     error->message);
    
    g_signal_connect (dialog, "response",                       
                      gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
                      gtk_widget_show (dialog);
                      
                      g_error_free (error);
                      }
  }
}
#else
// This handles the default GNOME 1.4 help system, which just basically
// pops up an html page in a web browser.
void
on_help                                (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  gchar* helpfile;
  
  helpfile = gnome_help_file_find_file("gnuae",
                                       "gnuae.html");
  
  g_print("Helpfile path is %s\n", helpfile);
  
  if (helpfile != NULL) {
    gchar* url;
    
    url = g_strconcat("file:/usr/share/gnome/help/gnuae", helpfile, NULL);
    
    g_print(url);
    
    gnome_help_goto(NULL, url);
    
    g_free(url);
    g_free(helpfile);
  } else {
    gnome_error_dialog(_("Couldn't find the GNUae manual!"));

    gnome_help_goto(NULL, "file:/usr/local/share/gnome/help/gnuae/C/html/index.html");
    
  }
}                                                                              

#endif
                                                                               

void
on_manual_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  on_help(menuitem, user_data);
  
}


void
on_nec_check_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  update_nec_conduit_size();
  
  update_nec_wire_ampacity();
}


/* The conduit type changed */
void
on_nec_entry5_changed                  (GtkEditable     *editable,
                                        gpointer         user_data)
{
  update_nec_conduit_size();
}


void
on_pvwin_add_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
  AddPVWin = create_AddPVWin();

  gtk_widget_show(AddPVWin);
}

void
on_pvwin_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_hide(PVBrowser);
}


void
on_pvwin_cancel_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_hide(PVBrowser);
}


void
on_pvwin_calc_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_addpv_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
  on_addpv_apply_clicked(button, user_data);
  
  on_addpv_cancel_clicked(button, user_data);
}


void
on_addpv_cancel_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_widget_hide(AddPVWin);
}

void
on_addpv_apply_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spin;
  gchar *ptr;
  gfloat width, height;
  pvpanel_t *pv;

  pv = malloc(sizeof(pvpanel_t));
  
  memset(pv, 0, sizeof(pvpanel_t));
  entry = lookup_widget(GTK_WIDGET(button), "addpv_entry1");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  if (*ptr)
    pv->Manufacturer = strdup(ptr);    

  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(button), "addpv_spin1"));
  pv->Vmpo = gtk_spin_button_get_value_as_float(spin);
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin2"));
  pv->Voco = gtk_spin_button_get_value_as_float(spin);

  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin3"));
  pv->Series_Cells = gtk_spin_button_get_value_as_int(spin);
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin4"));
  height = gtk_spin_button_get_value_as_float(spin);
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin5"));
  pv->Price = gtk_spin_button_get_value_as_float(spin);

  /* These are the entries in the right column */
  entry = lookup_widget(GTK_WIDGET(AddPVWin), "addpv_entry2");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  if (*ptr)
    pv->Model = strdup(ptr);
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin6"));
  pv->Impo = gtk_spin_button_get_value_as_float(spin);  
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin7"));
  pv->Isco = gtk_spin_button_get_value_as_float(spin);  
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin8"));
  pv->Parallel_C_S = gtk_spin_button_get_value_as_int(spin);  
  
  spin = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(AddPVWin), "addpv_spin9"));
  width = gtk_spin_button_get_value_as_float(spin);  
  
  pv->Area = width * height;

  pv_add(pv);

  pv_write("");
  //  pv_dump(&pv);
}


void
on_pvwin_add_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{  
  AddPVWin = create_AddPVWin();
  
  gtk_widget_show(AddPVWin);
}

void
on_LoadWin_destroy                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  write_loads("");
}


void
on_apply_load_released                 (GtkButton       *button,
                                        gpointer         user_data)
{
  update_data();
  
  write_loads("");
  
  update_data();
}


void
on_ok_load_released                    (GtkButton       *button,
                                        gpointer         user_data)
{

  write_loads("");
  update_data();

  gtk_widget_hide(EditLoad);
}


void
on_ac_radiobutton_released             (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  GtkSpinButton *spinb;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  thisload = find_load(ptr); 
  thisload->type = AC;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "volts_spin"));
  thisload->voltage = 120;
  gtk_spin_button_set_value(spinb, thisload->voltage);

  thisload->amperage = nec_amps(thisload->wattage, thisload->voltage);

  spinb = GTK_SPIN_BUTTON(lookup_widget(GTK_WIDGET(EditLoad), "amps_spin"));
  gtk_spin_button_set_value(spinb, thisload->amperage);

  update_watts_used(calc_watts(thisload));
}


void
on_dc_radiobutton_released             (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *entry;
  load_t *thisload;
  gchar *ptr;

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  thisload = find_load(ptr); 
  thisload->type = DC;  
}


void
on_load_group_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
  load_t *thisload;
  GtkWidget *entry;
  gchar *ptr;  

  entry = lookup_widget(GTK_WIDGET(EditLoad), "device_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));
  thisload = find_load(ptr); 
  
  entry = lookup_widget(GTK_WIDGET(EditLoad), "load_group_entry");
  ptr = gtk_entry_get_text(GTK_ENTRY(entry));

  if (strcmp(ptr, "NOGROUP") == 0) {
    thisload->group = NOGROUP;
  }
  if (strcmp(ptr, "HOUSEHOLD") == 0) {
    thisload->group = HOUSEHOLD;    
  }
  if (strcmp(ptr, "KITCHEN") == 0) {
    thisload->group = KITCHEN;
  }
  if (strcmp(ptr, "DIGITAL") == 0) {
    thisload->group = DIGITAL;
  }
  if (strcmp(ptr, "TOOLS") == 0) {    
    thisload->group = TOOLS;
  }
  
}
