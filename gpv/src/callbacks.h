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

#include <gnome.h>

extern GtkWidget *MainWindow;
extern GtkWidget *PVWindow;


struct gpv_panel
{
  char *Model;
  char *Material;
  int Series_Cells;
  int Parallel_Cells;
  double Isc;                  /* Short Circuit Current */
  double Voc;                  /* Open Circuit Voltage */
  double Imp;                  /* Nominal Current */
  double Vmp;                  /* Nominal Voltage */
  double Price;
};

struct gpv_data 
{
  int nominal_voltage;
  int array_voltage;
  float hours_of_sun;
  int reserve_time;
  int usable_capacity;
  
  char *module;
  int current_needed;
  int mod_series;
  int mod_parallel;
  int mod_total;

  char *battery;
  int capacity_needed;
  int batt_series;
  int batt_parallel;
  int batt_total;
  int wattage;
  int amperage;  
};

void
on_file1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new2_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_file1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_guppi_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_gtkplot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_stripchart1_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_awg_vs_ohms1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_temp_vs_ohms1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_voltage_drop1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_voltage_loss1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_pv_temp_comp1_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as1_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_print1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_close1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_beam_irradiation_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_diffuse_irradiation_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_ambient_temperature_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_sun_elevation_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_aoi_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_wind_speed_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_X_altitude_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_isc_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_imp_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_vmp_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_voc_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_tc_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_power_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_efficiency_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_fill_factor_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_beam_irradiation_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Y_diffuse_irradiation_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_ambient_temperature_activate      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_sun_elevation_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_aoi_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_wind_speed_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_Z_altitude_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new3_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_radio1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_manual_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about2_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
quit                                   (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_file2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_x_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_y_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_z_axis1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_new_2d_plot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

GtkWidget*
make_gtk_plot_custom (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2);

GtkWidget*
make_gtk_plot_custom_3d (gchar *widget_name, gchar *string1, gchar *string2,
                gint int1, gint int2);

void
on_new_3d_plot_activate                (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table8_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table690_7_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_conduit_size_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_nec_calculator_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_310_15b2_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_310_15b6_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_310_11_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_310_16_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_310_17_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_table_690_31c_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

gboolean
on_neccalc_expose_event                (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

void
on_spinbutton28_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton29_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_fnec_fixed_expose_event             (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

gboolean
on_fnec_fixed_configure_event          (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

void
on_fnec_fixed_map                      (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_pv_browser_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_pv_e_changed                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pv_e_changed                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wire_resistance_activate            (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_wire_ampacity_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_isc_x_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_aoi_y_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_isc_y_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_nominal_volts_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_sun_per_day_changed                 (GtkEditable     *editable,
                                        gpointer         user_data);
void
on_reserve_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_capacity_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_add_load_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_display_loads_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_loads_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as_loads_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_loads_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
init_data                              (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_choose_loads_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_combo_entry1_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_temp_changed                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pv_volts_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_battery_changed                     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pv_changed                          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_sizes_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_power_center_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_generate_parts_list_activate        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_center_entry_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_charger_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_inverter_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_combiner_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_inverters1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_batteries_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_charge_controllers_activate         (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_invert_apply_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_InverterBrowser_map                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_InverterBrowser_map                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_inverter_model_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_charger_list_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_Charger_map                         (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_fixed12_map                         (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_pv_combiner_boxes_activate          (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_combiner_entry_changed              (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_combiner_browser__entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_battery_browser_map                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_batt_browser_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_Wiring_map                          (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_load_edit_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_LoadWin_map                         (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_load_device_entry_changed           (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_load_active_toggled                 (GtkButton       *button,
                                        gpointer         user_data);


void
on_new_load_released                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_new_load_released                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_text_ok_clicked                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_text_cancel_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_text1_changed                       (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_text1_insert_text                   (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_text1_changed                       (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_text1_key_press_event               (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

void
on_text1_activate                      (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_device_entry_activate               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_input_entry_activate                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_apply1_released                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_LoadWin_map                         (GtkWidget       *widget,
                                        gpointer         user_data);

gboolean
on_load_watts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_volts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_amps_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_quantity_spin_event            (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_file_ok_released                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_file_cancel_released                (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_watts_entry_changed                 (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_amps_entry_changed                  (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_hour_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_mins_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_days_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_display_active_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save2_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as2_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
void
UpdateStatusMsg(int bar, char *msg);

void
on_wiring_spin1_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin2_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin3_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin4_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin5_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin6_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin7_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_spin8_changed                (GtkEditable     *editable,
                                        gpointer         user_data);


gboolean
on_wiring_spin1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin2_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo1_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo3_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo2_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo4_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo5_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo6_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo7_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo8_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_combo9_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);
void
on_spinbutton23_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton24_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton25_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton26_changed                (GtkEditable     *editable,
                                        gpointer         user_data);
void
on_spinbutton27_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton28_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton29_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_spinbutton30_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_nec_combo1_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_combo2_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_wiring_spin9_changed                (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_wiring_spin01_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin4_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin5_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin6_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin1_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin2_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin7_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin1_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin2_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin4_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin5_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin6_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin7_changed                   (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_combo1_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_combo2_button_press_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_neccalc_realize                     (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_nec_entry2_changed                  (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_nec_entry1_changed                  (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry4_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry3_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry2_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry5_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry8_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry7_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry6_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry9_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_wiring_entry1_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_wiring_spin1_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_nec_spin3_activate                  (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_nec_spin3_button_press_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);


void
on_nec_spin3_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

void
on_nec_spin5_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

void
on_nec_spin6_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

void
on_nec_spin1_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

void
on_nec_spin2_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

void
on_nec_spin7_insert_text               (GtkEditable     *editable,
                                        gchar           *new_text,
                                        gint             new_text_length,
                                        gint            *position,
                                        gpointer         user_data);

gboolean
on_nec_spin1_button_press_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin1_client_event              (GtkWidget       *widget,
                                        GdkEventClient  *event,
                                        gpointer         user_data);

gboolean
on_nec_spin1_key_press_event           (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_nec_spin_key_press_event            (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_nec_calculate_release_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin5_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin4_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin3_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin6_button_press_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_wiring_spin02_button_press_event    (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_manual_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_nec_check_toggled                   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

gboolean
on_nec_combo3_button_release_event     (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_nec_entry5_changed                  (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_nec_radio2_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_nec_radio1_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button20_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_pvwin_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_pvwin_add_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
om_pvwin_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_pvwin_cancel_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_pvwin_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_pvwin_calc_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_addpv_ok_clicked                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_addpv_cancel_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_addpv_apply_clicked                 (GtkButton       *button,
                                        gpointer         user_data);


void
on_pvwin_add_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data);
void
on_LoadWin_destroy                     (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_apply_load_released                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_load_released                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_ac_radiobutton_released             (GtkButton       *button,
                                        gpointer         user_data);

void
on_dc_radiobutton_released             (GtkButton       *button,
                                        gpointer         user_data);

void
on_load_group_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data);

gboolean
on_load_hour_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_mins_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_days_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_volts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_amps_spin_changed              (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_load_watts_spin_changed             (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

void
on_nec_ok_released                     (GtkButton       *button,
                                        gpointer         user_data);

void
on_nec_cancel_released                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_wiring_ok_released                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_wiring_cancel_released              (GtkButton       *button,
                                        gpointer         user_data);
