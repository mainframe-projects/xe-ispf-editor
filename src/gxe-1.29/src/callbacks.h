//*CID://+vbd2R~:                             update#=   23;       //+vbd2R~
//********************************************************************//~var8I~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //+vbd2I~
//vawF:140621 (BUG)On Ubuntu13.4;when global menu,menuitem on menubar show "activate" menuitem and no effect.//~vawfI~
//var8:140127 gtk3 suppott                                         //~var8I~
//********************************************************************//~var8I~
#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>
#else                                                              //~var8R~
#include <gtk/gtk.h>                                               //~var8R~
#endif                                                             //~var8R~


void
on_new_activate                       (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_open_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_save_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_saveas_activate                   (GtkMenuItem     *menuitem,   //~5603R~
                                        gpointer         user_data);

void
on_print_activate                      (GtkMenuItem     *menuitem, //~5603R~
                                        gpointer         user_data);

void
on_prtscr_activate                   (GtkMenuItem     *menuitem,   //~5603R~
                                        gpointer         user_data);

void
on_preview_activate                    (GtkMenuItem     *menuitem, //~5603R~
                                        gpointer         user_data);

//void                                                             //~var8R~
//on_preview_select                    (GtkMenuItem     *menuitem, //~var8R~
//                                        gpointer         user_data);//~var8R~
//                                                                 //~var8R~
//void                                                             //~var8R~
//on_previewdialog_activate                    (GtkMenuItem     *menuitem,//~var8R~
//                                        gpointer         user_data);//~var8R~
//                                                                 //~var8R~
void                                                               //~5603I~
on_preview2_activate                    (GtkMenuItem     *menuitem,//~5603I~
                                        gpointer         user_data);//~5603I~
                                                                   //~5603I~
void
on_exit_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void                                                               //+vbd2I~
on_selectall_activate                       (GtkMenuItem     *menuitem,//+vbd2I~
                                        gpointer         user_data);//+vbd2I~
                                                                   //+vbd2I~
void
on_cut_activate                       (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_copy_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_clear_activate                     (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data);

void
on_paste_insert_activate                     (GtkMenuItem     *menuitem,//~5603R~
                                        gpointer         user_data);

void
on_paste_replace_activate           (GtkMenuItem     *menuitem,    //~5603R~
                                        gpointer         user_data);

void
on_setup_activate                (GtkMenuItem     *menuitem,       //~5603R~
                                        gpointer         user_data);

//void                                                             //~var8R~
//on_setup_select                (GtkMenuItem     *menuitem,       //~var8R~
//                                        gpointer         user_data);//~var8R~
//                                                                 //~var8R~
//void                                                             //~var8R~
//on_setupdialog_activate                (GtkMenuItem     *menuitem,//~var8R~
//                                        gpointer         user_data);//~var8R~
//                                                                 //~var8R~
void
on_version_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_home_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_terminal_activate                   (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button_save_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_end_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_print_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_home_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_terminal_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cut_clicked                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_copy_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_clear_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasteins_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasterep_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_font_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_color_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_options_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_font_button_ok_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_font_button_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_font_button_apply_clicked           (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_fontselectiondialog_configure_event (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_fileselection_configure_event       (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

void
on_file_button_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_colorselectiondialog_configure_event
                                        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

void
on_color_button_ok_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_file_button_ok_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_color_button_cancel_clicked         (GtkButton       *button,
                                        gpointer         user_data);

void
on_about_button_close_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_option_button_cancel_clicked        (GtkButton       *button,
                                        gpointer         user_data);

void
on_option_button_ok_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_fontstyle_clicked       (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_preview_print_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_np_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_pp_clicked              (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_preview_prtscr_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_print_clicked           (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_prtscr_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_save_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_button_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_option_button_change_font_clicked   (GtkButton       *button,
                                        gpointer         user_data);

void
on_option_button_color_change_clicked  (GtkButton       *button,
                                        gpointer         user_data);

void
on_setup_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_page_previewarea_draw(GtkWidget *widget,cairo_t *Pcr,gpointer user_data);//~var8R~
#endif                                                             //~var8R~
gboolean
on_option_drawingarea_colorsample_configure_event
                                        (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

#ifndef OPTGTK3                                                    //~var8R~
gboolean
on_option_drawingarea_colorsample_expose_event
                                        (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);
#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_option_drawingarea_colorsample_draw(GtkWidget *widget,cairo_t *Pcr,gpointer user_data);//~var8R~
#endif                                                             //~var8R~

gboolean
on_maindraw_configure_event            (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

#ifndef OPTGTK3                                                    //~var8R~
gboolean
on_maindraw_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data);

#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_maindraw_draw(GtkWidget *widget,cairo_t *Pcr,gpointer Puser_data);//~var8R~
#endif                                                             //~var8R~
gboolean
on_maindraw_button_press_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_maindraw_button_release_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data);

gboolean
on_maindraw_key_press_event            (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_maindraw_key_release_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data);

gboolean
on_maindraw_leave_notify_event         (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data);

gboolean
on_maindraw_enter_notify_event         (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data);

gboolean
on_maindraw_motion_notify_event        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data);

void
on_maindraw_realize                    (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_maindraw_unrealize                  (GtkWidget       *widget,
                                        gpointer         user_data);

gboolean
on_maindraw_focus_in_event             (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

gboolean
on_maindraw_focus_out_event            (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data);

void
on_framewindow_realize                 (GtkWidget       *widget,
                                        gpointer         user_data);

void
on_framewindow_unrealize               (GtkWidget       *widget,
                                        gpointer         user_data);

gboolean
on_framewindow_configure_event         (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data);

gboolean
on_framewindow_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_framewindow_destroy_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

gboolean
on_maindraw_scroll_event               (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data);

void
on_framewindow_drag_data_received      (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        gint             x,
                                        gint             y,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data);

void
on_maindraw_drag_data_get              (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data);

void
on_maindraw_drag_end                   (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        gpointer         user_data);

void
on_maindraw_drag_begin                 (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        gpointer         user_data);

void
on_button_save_enter                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_save_leave                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_end_enter                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_end_leave                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cancel_enter                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cancel_leave                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_print_enter                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_print_leave                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_home_enter                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_home_leave                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_terminal_enter               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_terminal_leave               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cut_enter                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_cut_leave                    (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_copy_enter                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_copy_leave                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_clear_enter                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_clear_leave                  (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasteins_enter               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasteins_leave               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasterep_enter               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasterep_leave               (GtkButton       *button,
                                        gpointer         user_data);

void
on_page_chkbutton_bycellhw_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_page_chkbutton_2p_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_page_chkbutton_header_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_page_chkbutton_footer_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_page_entry_pageno_editing_done      (GtkCellEditable *celleditable,
                                        gpointer         user_data);

void
on_page_font_change_clicked            (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_open_clicked                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_open_enter                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_open_leave                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_helpdoc_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_PasteV_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_button_pasteV_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasteV_enter                 (GtkButton       *button,
                                        gpointer         user_data);

void
on_button_pasteV_leave                 (GtkButton       *button,
                                        gpointer         user_data);

#ifndef OPTGTK3                                                    //~var8R~
gboolean
on_maindraw_client_event               (GtkWidget       *widget,
                                        GdkEventClient  *event,
                                        gpointer         user_data);

#endif                                                             //~var8R~
void
on_option_button_rulercolor_change_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data);

gboolean
on_combo2_selection_notify_event       (GtkWidget       *widget,
                                        GdkEventSelection *event,
                                        gpointer         user_data);

void
on_combo2_selection_received           (GtkWidget       *widget,
                                        GtkSelectionData *data,
                                        guint            time,
                                        gpointer         user_data);

gboolean
on_page_combo_printer_selection_notify_event
                                        (GtkWidget       *widget,
                                        GdkEventSelection *event,
                                        gpointer         user_data);

void
on_page_combo_printer_selection_received
                                        (GtkWidget       *widget,
                                        GtkSelectionData *data,
                                        guint            time,
                                        gpointer         user_data);

gboolean
on_page_combo_printer_selection_request_event
                                        (GtkWidget       *widget,
                                        GdkEventSelection *event,
                                        gpointer         user_data);

void
on_combo2_selection_get                (GtkWidget       *widget,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data);

gboolean
on_combo2_selection_request_event      (GtkWidget       *widget,
                                        GdkEventSelection *event,
                                        gpointer         user_data);

void
on_page_combo_printer_selection_get    (GtkWidget       *widget,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data);

void
on_combo2_state_changed                (GtkWidget       *widget,
                                        GtkStateType     state,
                                        gpointer         user_data);

#ifndef OPTGTK3                                                    //~var8R~
void
on_page_combo_printer_changed          (GtkEditable     *editable,
                                        gpointer         user_data);
#else   //OPTGTK3                                                  //~var8R~
	void on_page_combo_printer_changed(GtkComboBox *Ppcombo,gpointer user_data);//~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
void                                                               //~3A02I~
on_page_combo_form_changed          (GtkEditable     *editable,    //~3A02I~
                                        gpointer         user_data);//~3A02I~
#else   //OPTGTK3                                                  //~var8R~
	void on_page_combo_form_changed(GtkComboBox *Ppcombo,gpointer  user_data);//~var8R~
#endif                                                             //~var8R~
#ifndef GGG                                                        //~vawfM~
gboolean                                                           //~vawfM~
on_setup_button_press(GtkWidget       *widget,                     //~vawfM~
                                        GdkEventButton  *event,    //~vawfM~
                                        gpointer         user_data);//~vawfM~
gboolean                                                           //~vawfM~
on_preview_button_press(GtkWidget       *widget,                   //~vawfM~
                                        GdkEventButton  *event,    //~vawfM~
                                        gpointer         user_data);//~vawfM~
#endif	//!GGG                                                     //~vawfI~
