//*CID://+vbdjR~:                            update#=  330;        //~vbdjR~
//******************************************************************************//~vaf6I~
//vbdm:171125 (gxe)append "NewFile" for menu:File/New when directory is selected//~vbdmI~
//vbdk:171125 GTK2 GtkFileSelection was dprecated,GtkFileChooser is available from v2.4//~vbdkI~
//vbdj:171125 (GTK2) menu label Ctrl+x dose not change by SetupDialog:Accel On/Off//~vbdjI~
//vbdi:171125 (gxe) set accelerator(A+F,N it is not shortcut:Ctrl+N)//~vbdiI~
//vbdh:171123 (GTK3.10 BUG) gtk_widget_add_accelerator() dose not allow runtime change of accelerator//~vbdhI~
//            use not gtk_menu_item_set_accel_path() but gtk_widget_set_accel_path() to set accel path withgtk_accel_map_add_entry()//~vbdhI~
//vbdc:171122 (gxe:BUG)Mainmenu nemonic have to set menubar item   //~vbdcI~
//vbdb:171121*(gxe)try setup/preview menu as menuitem to open dialog by one touch//~vbdbI~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //~vbd2I~
//vv7B:170201 (gxe:BUG)scroll event was not catched                //~vb7BI~
//vb7t:170128 (gxe)Gtk3 deprecated
//vawF:140621 (BUG)On Ubuntu13.4;when global menu,menuitem on menubar show "activate" menuitem and no effect.//~vawFI~
//var8:140127 gtk3 suppott                                         //~var8I~
//var7:140126 delete label of toolbox to widen screen              //~var7I
//var0:140114 (Bug:gxe)toolbar icon for open was same as save      //~var0I
//vap1:131220 (LNX)configure aupports NOPRINT for RedHat5.8        //~vap1I
//vamt:131015 (GtkPrint)accept minus value of margin to adjust origin for each printer's paper folder shift attachment.(case of that b5 origin is relativ to a4 origin)//~vamtI
//vamb:131002 re-draw HWmargin when form changed                   //~vak3I
//vam7:130929 add print with ligature                              //~vambI//~vam7M
//vak3:130904 deplicated function;gdk:gdk_pixxbuf_unref(frrom gtk2)-->g_object_unref//~vak3R
//vaf6:120604 (XXE) fildialog(gtkfileselection) display previous selection directory//~vaf6I~
//******************************************************************************//~vaf6I~

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifndef OPTGTK3                                                    //~var8R~
#include <bonobo.h>
#include <gnome.h>
	#include "gxe.h"                                               //~vawFI~
	#include "xxeres.h"                                            //~vawFM~
#else                                                              //~var8R~
	#include <libgnome/libgnome.h>                                 //~var8R~
	#include <gtk/gtk.h>                                           //~var8R~
	#include <gdk/gdkx.h>                                          //~var8R~
	#include <gdk/gdkkeysyms-compat.h>                             //~var8R~
//	#include <libgnomecanvas/libgnomecanvas.h>  use GtkDrawingArea //~var8R~
                                                                   //~var8R~
	#include "gxe.h"                                               //~var8R~
	#include "gxedlg.h"                                            //~var8R~
	#include "gxeview.h"                                           //~var8R~
	#include "xxeres.h"                                            //~vawFI~
#endif                                                             //~var8R~
                                                                   //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
    #ifdef GTK_WIDGET_SET_FLAGS                                    //~var8R~
    	#undef GTK_WIDGET_SET_FLAGS                                //~var8R~
    #endif                                                         //~var8R~
    #define GTK_WIDGET_SET_FLAGS(Ppwidget,Pflag) interface_gtk_widget_set_flags(Ppwidget,Pflag,TRUE)//~var8R~
    	void interface_gtk_widget_set_flags(GtkWidget *Ppwidget,int Pflag,gboolean Pbool);//~var8R~
        #define GTK_CAN_FOCUS        (1<<11)                       //~var8R~
        #define GTK_CAN_DEFAULT      (1<<13)                       //~var8R~
                                                                   //~var8R~
	#define GtkTooltips gchar                                      //~var8R~
	#define gtk_tooltips_new() NULL                                //~var8R~
    #define gtk_tool_item_set_tooltip(pGtkToolItem,pGtkTooltips,ptip_text,ptip_private)\
    		gtk_tool_item_set_tooltip_text(pGtkToolItem,(pGtkTooltips=ptip_text)) //~var8I~//~var8R~
    #define gtk_tooltips_set_tip(pGtkTooltip,Ppwidget,Ptipstr,Ppvtstr)\
            gtk_widget_set_tooltip_text(Ppwidget,(pGtkTooltip=Ptipstr))//~var8R~
    #define gtk_vbox_new(homogeneous,spacing)  gtk_box_new(GTK_ORIENTATION_VERTICAL,spacing)//~var8R~
    #define gtk_hbox_new(homogeneous,spacing)  gtk_box_new(GTK_ORIENTATION_HORIZONTAL,spacing)//~var8R~
    #ifdef GTK_TABLE	                                           //~var8R~
    	#undef GTK_TABLE                                           //~var8R~
    #endif                                                         //~var8R~
    #define GTK_TABLE  GTK_GRID                                    //~var8R~
    #define gtk_table_new(rows,cols,homogeneous)  gtk_grid_new()   //~var8R~
    #define gtk_table_new(rows,cols,homogeneous)  gtk_grid_new()   //~var8R~
    #define gtk_table_attach(grid,child,leftcol,rightcol,toprow,bottomrow,xoption,yoption,xpad,ypad)\
    	interface_gtk_table_attach(grid,child,leftcol,rightcol,toprow,bottomrow,xoption,yoption,xpad,ypad)//~var8R~
    void interface_gtk_table_attach(GtkGrid *,GtkWidget *,guint,guint,guint,guint,GtkAttachOptions,GtkAttachOptions,guint,guint);//~var8R~
    #define gtk_hseparator_new() gtk_separator_new(GTK_ORIENTATION_HORIZONTAL)//~var8R~
    //******************************************************       //~var8R~
#endif                                                             //~var8R~

#include "callbacks.h"
#include "interface.h"
#include "support.h"
                                                                   //~var8R~
//************************                                         //~var8R~
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else                                                              //~var8R~
	void interface_add_filter(GtkWidget *Pwidget);                 //~var8R~
#ifndef CCC                                                        //~var8R~
#if GTK_CHECK_VERSION(3,10,0)	//gtk_ui_manager was deprecated    //~vb7tI~
#else                                                              //~vb7tI~
    static GtkUIManager *SpUIManager;                              //~var8R~
#endif                                                             //~vb7tI~
//    GtkWidget *Gpframwidget;                                     //~var8R~
#endif	//!CCC                                                     //~var8R~
#endif                                                             //~var8R~
#ifndef GGG                                                        //~vawFI~
  #if GTK_CHECK_VERSION(3,10,0)                                    //~vb7tI~
    void set_menubar_dialog_open_signal(GtkWidget *framewindow);   //~vb7tI~
  #else                                                            //~vb7tI~
    void set_menubar_dialog_open_signal(void);                     //~vawFI~
  #endif                                                           //~vb7tI~
#endif                                                             //~vawFI~
//************************                                         //~var8R~
                                                                   //~var8R~
#define TOOLTIPS_PAGE_LABEL_MARGIN "HWMarginis applied when 0.\n" \
                                   "If the printer/paper-folder dose not support the PaperSize,\n" \
                                   "try xxyy format(xx:shift,yy:margin).\n"  \
                                   "ex) Top=3500:shift print y-origin 35mm toward top edge.\n" \
                                   "    Right=4000:shift print x-origin 40mm toward right edge."//~vamtI
#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else                                                              //+var8~//~var8R~
#ifndef CCC                                                        //~var8R~
  #if GTK_CHECK_VERSION(3,10,0)                                    //~vb7tI~
	void hookup_menu(GtkWidget *framewindow,char *Pmenuid,char *Phookupkey);//~vb7tI~
	#define GLADE_HOOKUP_OBJECT_MENU(framewindow,path,menuid,lookupstrid)\
		hookup_menu(framewindow,menuid,lookupstrid)                //~vb7tI~
  #else                                                            //~vb7tI~
#define GLADE_HOOKUP_OBJECT_MENU(component,path,menuid,lookupstrid)\
	GLADE_HOOKUP_OBJECT(framewindow,gtk_ui_manager_get_widget(SpUIManager,path "/" menuid),lookupstrid)//~var8R~
  #endif                                                           //~vb7tI~
#endif  //!CCC                                                     //~var8R~
#ifdef BBB                                                         //~var8R~
#define GLADE_HOOKUP_OBJECT_MENU(component,strid)\
	GLADE_HOOKUP_OBJECT(framewindow,gtk_builder_get_object(Smenubuilder,strid),strid);//~var8R~
#endif //BBB                                                       //~var8R~
#endif                                                             //+var8~//~var8R~
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else                                                              //+var8~//~var8R~
#ifndef CCC                                                        //~var8R~
#ifdef EEE                                                         //~var8R~
    #define DEFINE_ACTION_SELECT(name) {#name,on_##name_select,NULL/*parmtype*/,NULL/*state*/,NULL/*change state func*/}//~var8R~
    #define DEFINE_ACTION_SELECT_FUNC(name,lookupid)\
        void select_##name(GSimpleAction *Paction,GVariant *Pparm,gpointer Puserdata)\
        {\
        	GtkWidget *pmenu;\
        	dprintf("select menu=%s\n",#name);\
            pmenu=lookup_widget(Gpframe,lookupid);\
            on_##name##_activate(GTK_MENU_ITEM(pmenu),Puserdata);\
        }                                                          //~var8R~
#endif                                                             //~var8R~
#endif                                                             //~var8R~
#ifdef BBB                                                         //~var8R~
    #define DEFINE_ACTION(name) {#name,activate_##name,NULL/*parmtype*/,NULL/*state*/,NULL/*change state func*/}//~var8R~
    #define DEFINE_ACTION_ACTIVATE_FUNC(name)\
        void activate_##name(GSimpleAction *Paction,GVariant *Pparm,gpointer Puserdata)\
        {\
            on_##name##_activate(NULL/*menuitem*/,Puserdata);\
        }                                                          //~var8R~
    GtkBuilder *Smenubuilder;                                      //~var8R~
#endif                                                             //~var8R~
#endif                                                             //+var8~//~var8R~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
//*See gtk/gtstock.h                                               //~var8R~
  #if GTK_CHECK_VERSION(3,10,0)                                    //~vb7tI~
	#define TB_STOCK_OPEN          GTK3_STOCK_OPEN                 //~vb7tR~
	#define TB_STOCK_SAVE          GTK3_STOCK_SAVE                 //~vb7tR~
	#define TB_STOCK_END           "media-floppy"                  //~vb7tR~
	#define TB_STOCK_CANCEL        "document-revert"               //~vb7tI~
	#define TB_STOCK_PRINT         "document-print"                //~vb7tI~
	#define TB_STOCK_HOME          "go-home"                       //~vb7tI~
	#define TB_STOCK_TERMINAL      "system-run"                    //~vb7tI~
	#define TB_STOCK_CUT           GTK3_STOCK_CUT                  //~vb7tR~
	#define TB_STOCK_COPY          GTK3_STOCK_COPY                 //~vb7tR~
	#define TB_STOCK_CLEAR         GTK3_STOCK_CLEAR                //~vb7tR~
	#define TB_STOCK_PASTE         GTK3_STOCK_PASTE                //~vb7tR~
  #else                                                            //~vb7tI~
	#define TB_STOCK_OPEN          GTK_STOCK_OPEN                  //~var8R~
	#define TB_STOCK_SAVE          GTK_STOCK_SAVE                  //~var8R~
	#define TB_STOCK_END           GTK_STOCK_FLOPPY                //~var8R~
	#define TB_STOCK_CANCEL        GTK_STOCK_REVERT_TO_SAVED //GTK_STOCK_MISSING_IMAGE//~var8R~
	#define TB_STOCK_PRINT         GTK_STOCK_PRINT                 //~var8R~
	#define TB_STOCK_HOME          GTK_STOCK_HOME                  //~var8R~
	#define TB_STOCK_TERMINAL      GTK_STOCK_EXECUTE               //~var8R~
	#define TB_STOCK_CUT           GTK_STOCK_CUT                   //~var8R~
	#define TB_STOCK_COPY          GTK_STOCK_COPY                  //~var8R~
	#define TB_STOCK_CLEAR         GTK_STOCK_CLEAR                 //~var8R~
	#define TB_STOCK_PASTE         GTK_STOCK_PASTE                 //~var8R~
  #endif                                                           //~vb7tI~
#endif                                                             //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tR~
	#define TB_STOCK_PASTE_INS     "format-indent-more"            //~vb7tR~
	#define TB_STOCK_PASTE_REP     "format-justify-fill"           //~vb7tR~
#else                                                              //~vb7tR~
#define TB_STOCK_PASTE_INS     GTK_STOCK_INDENT                    //~var8R~
#define TB_STOCK_PASTE_REP     GTK_STOCK_INDEX                     //~var8R~
#endif                                                             //~vb7tR~
//************************                                         //~var8R~
#ifndef OPTGTK3                                                    //+var8~//~var8R~
static GnomeUIInfo file_menu_uiinfo[] =
{
#define UIINFO_NEW 0                                               //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("New"),                                  //~vbdiR~
    GNOME_APP_UI_ITEM, N_("New(_N)") ,                             //~vbdiI~
    NULL,
    (gpointer) on_new_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-new",
    GDK_N, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_OPEN 1                                              //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Open"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Open(_O)"),                             //~vbdiI~
    NULL,
    (gpointer) on_open_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-open",
    GDK_O, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_SAVE 2                                              //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Save"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Save(_S)"),                             //~vbdiI~
    NULL,
    (gpointer) on_save_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-save",
    GDK_S, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_SAVEAS 3                                            //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("SaveAs"),                               //~vbdiR~
    GNOME_APP_UI_ITEM, N_("SaveAs(_A)"),                           //~vbdiI~
    NULL,
    (gpointer) on_saveas_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-save-as",
    GDK_A, (GdkModifierType) GDK_CONTROL_MASK, NULL   //reset by gxemfrm.c:actinit
  },
  GNOMEUIINFO_SEPARATOR,
#define UIINFO_PRINT 5                                             //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Print"),                                //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Print(_P)"),                            //~vbdiI~
    NULL,
    (gpointer) on_print_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-print",
    GDK_P, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_PRTSCR 6                                            //~vbdjR~
  {
//  GNOME_APP_UI_ITEM, N_("PrtScr"),                               //~vbdiR~
    GNOME_APP_UI_ITEM, N_("PrtScr(_H)"),                           //~vbdiI~
    NULL,
    (gpointer) on_prtscr_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-print",
    GDK_H, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
  GNOMEUIINFO_SEPARATOR,
#define UIINFO_HOME 8                                              //+vbdjR~
  {
//  GNOME_APP_UI_ITEM, N_("Home"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Home(_E)"),                             //~vbdiI~
    NULL,
    (gpointer) on_home_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-home",
    GDK_E, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_TERM 9                                              //+vbdjR~
  {
//  GNOME_APP_UI_ITEM, N_("Term"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Term(_M)"),                             //~vbdiI~
    NULL,
    (gpointer) on_terminal_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-execute",
    GDK_M, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_EXIT 10                                             //+vbdjR~
  {
//  GNOME_APP_UI_ITEM, N_("Exit"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Exit(_X)"),                             //~vbdiI~
    NULL,
    (gpointer) on_exit_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-quit",
    GDK_X, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo edit_menu_uiinfo[] =
{
#define UIINFO_CUT 0                                               //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Cut"),                                  //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Cut(_T)"),                              //~vbdiI~
    NULL,
    (gpointer) on_cut_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-cut",
    GDK_T, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_COPY 1                                              //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Copy"),                                 //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Copy(_C)"),                             //~vbdiI~
    NULL,
    (gpointer) on_copy_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-copy",
    GDK_C, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_CLEAR 2                                             //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Clear"),                                //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Clear(_L)"),                            //~vbdiI~
    NULL,
    (gpointer) on_clear_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-clear",
    GDK_L, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_PASTE_V 3                                           //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Paste"),                                //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Paste(_V)"),                            //~vbdiI~
    N_("Standard Paste"),
    (gpointer) on_PasteV_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-paste",
    GDK_V, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_PASTE 4                                             //~vbdjI~
  {
//  GNOME_APP_UI_ITEM, N_("Paste-Insert"),                         //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Paste-Insert(_I)"),                     //~vbdiI~
    N_("BlockInsert"),
    (gpointer) on_paste_insert_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-paste",
    GDK_I, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_PASTE_REP 5                                         //~vbdjR~
  {
//  GNOME_APP_UI_ITEM, N_("Paste-Replace"),                        //~vbdiR~
    GNOME_APP_UI_ITEM, N_("Paste-Replace(_R)"),                    //~vbdiI~
    N_("BlockReplace"),
    (gpointer) on_paste_replace_activate, NULL, NULL,
    GNOME_APP_PIXMAP_STOCK, "gtk-paste",
    GDK_R, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
#define UIINFO_SELECTALL 6                                         //~vbdjR~
  {                                                                //~vbd2M~
//  GNOME_APP_UI_ITEM, N_("SelectAll"),                            //~vbd2M~//~vbdiR~
    GNOME_APP_UI_ITEM, N_("SelectAll(_A)"),                        //~vbdiI~
    NULL,                                                          //~vbd2M~
    (gpointer) on_selectall_activate, NULL, NULL,                  //~vbd2M~
    GNOME_APP_PIXMAP_STOCK, "gtk-select-all",                      //~vbd2M~
    GDK_A, (GdkModifierType) GDK_CONTROL_MASK, NULL                //~vbd2M~
  },                                                               //~vbd2M~
  GNOMEUIINFO_END
};

static GnomeUIInfo help2_menu_uiinfo[] =
{
  {
    GNOME_APP_UI_ITEM, N_("HelpDoc"),
    NULL,
    (gpointer) on_helpdoc_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_ITEM, N_("Version"),
    NULL,
    (gpointer) on_version_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};

#ifndef GGG                                                        //~vawFI~
static GnomeUIInfo setup_menu_uiinfo[] =                           //~vawFI~
{                                                                  //~vawFI~
  {                                                                //~vawFI~
    GNOME_APP_UI_ITEM, N_("Open Dialog"),                          //~vawFI~
    NULL,                                                          //~vawFI~
    (gpointer) on_setup_activate, NULL, NULL,                      //~vawFI~
    GNOME_APP_PIXMAP_NONE, NULL,                                   //~vawFI~
    0, (GdkModifierType) 0, NULL                                   //~vawFI~
  },                                                               //~vawFI~
  GNOMEUIINFO_END                                                  //~vawFI~
};                                                                 //~vawFI~
static GnomeUIInfo preview_menu_uiinfo[] =                         //~vawFI~
{                                                                  //~vawFI~
  {                                                                //~vawFI~
    GNOME_APP_UI_ITEM, N_("Open Dialog"),                          //~vawFI~
    NULL,                                                          //~vawFI~
    (gpointer) on_preview_activate, NULL, NULL,                    //~vawFI~
    GNOME_APP_PIXMAP_NONE, NULL,                                   //~vawFI~
    0, (GdkModifierType) 0, NULL                                   //~vawFI~
  },                                                               //~vawFI~
  GNOMEUIINFO_END                                                  //~vawFI~
};                                                                 //~vawFI~
#endif                                                             //~vawFI~
static GnomeUIInfo menubar1_uiinfo[] =
{
  {
    GNOME_APP_UI_SUBTREE, N_("_File "),
    NULL,
    file_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  {
    GNOME_APP_UI_SUBTREE, N_("_Edit "),
    NULL,
    edit_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
//#ifdef GGG                                                         //~vawFI~//~vbdbR~
#ifdef GGG                                                         //~vbdbR~
#ifdef GGG                                                         //~vbdbR~
  {
    GNOME_APP_UI_ITEM, N_("_Setup"),
    NULL,
    (gpointer) on_setup_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
#else                                                              //~vbdbI~
////  GNOMEUIINFO_ITEM_NONE(N_("_Setup"),NULL,on_setup_activate),    //~vbdbR~
//  {                                                                //~vbdbI~
//    GNOME_APP_UI_TOGGLEITEM, N_("_SetupB"),                        //~vbdbR~
//    NULL,                                                          //~vbdbI~
//    (gpointer) on_setup_activate, NULL, NULL,                      //~vbdbI~
////  GNOME_APP_PIXMAP_STOCK, GTK_STOCK_NEW,                         //~vbdbR~
//    GNOME_APP_PIXMAP_NONE, NULL,                                   //~vbdbI~
//    GDK_KEY_B, GDK_CONTROL_MASK, NULL                              //~vbdbR~
//  },                                                               //~vbdbI~
#endif                                                             //~vbdbI~
	GNOMEUIINFO_MENU_PREFERENCES_ITEM(on_setup_activate,NULL),
#else                                                              //~vawFI~
  {                                                                //~vawFI~
    GNOME_APP_UI_SUBTREE, N_("_Setup"),                            //~vawFI~
    NULL,                                                          //~vawFI~
    setup_menu_uiinfo, NULL, NULL,                                 //~vawFI~
    GNOME_APP_PIXMAP_NONE, NULL,                                   //~vawFI~
    0, (GdkModifierType) 0, NULL                                   //~vawFI~
  },                                                               //~vawFI~
#endif                                                             //~vawFI~
#ifdef GGG                                                         //~vawFI~
  {
    GNOME_APP_UI_ITEM, N_("_Preview"),
    NULL,
    (gpointer) on_preview2_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
#else                                                              //~vawFI~
  {                                                                //~vawFI~
    GNOME_APP_UI_SUBTREE, N_("_Preview"),                          //~vawFI~
    NULL,                                                          //~vawFI~
    preview_menu_uiinfo, NULL, NULL,                               //~vawFI~
    GNOME_APP_PIXMAP_NONE, NULL,                                   //~vawFI~
    0, (GdkModifierType) 0, NULL                                   //~vawFI~
  },                                                               //~vawFI~
#endif                                                             //~vawFI~
  {
    GNOME_APP_UI_SUBTREE, N_("_Help "),
    NULL,
    help2_menu_uiinfo, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};
#else 	//OPTGTK3                                                  //~var8R~
#ifndef CCC                                                        //~var8R~
#if GTK_CHECK_VERSION(3,10,0)
#else                                                              //~vb7tI~
static const gchar *main_menu_uiinfo=                              //~var8R~
	"<ui>"                                                         //~var8R~
    	"<menubar name='MainMenu'>"                                //~var8R~
			"<menu name='File' action='File'>"                     //~var8R~
				"<menuitem name='New' action='New'/>"              //~var8R~
				"<menuitem name='Open' action='Open'/>"            //~var8R~
				"<menuitem name='Save' action='Save'/>"            //~var8R~
				"<menuitem name='SaveAs' action='SaveAs'/>"        //~var8R~
				"<separator/>"                                     //~var8R~
				"<menuitem name='Print' action='Print'/>"          //~var8R~
				"<menuitem name='PrtScr' action='PrtScr'/>"        //~var8R~
				"<separator/>"                                     //~var8R~
				"<menuitem name='Home' action='Home'/>"            //~var8R~
				"<menuitem name='Term' action='Term'/>"            //~var8R~
				"<menuitem name='Exit' action='Exit'/>"            //~var8R~
			"</menu>"                                              //~var8R~
			"<menu name='Edit' action='Edit'>"                     //~var8R~
				"<menuitem name='Cut' action='Cut'/>"              //~var8R~
				"<menuitem name='Copy' action='Copy'/>"            //~var8R~
				"<menuitem name='Clear' action='Clear'/>"          //~var8R~
				"<menuitem name='Paste' action='Paste'/>"          //~var8R~
				"<menuitem name='Paste-Insert' action='Paste-Insert'/>"//~var8R~
				"<menuitem name='Paste-Replace' action='Paste-Replace'/>"//~var8R~
				"<menuitem name='SelectAll' action='SelectAll'/>"  //~vbd2M~
			"</menu>"                                              //~var8R~
//	  		"<menu name='Setup' action='Setup'>"                   //~var8R~
//				"<menuitem name='SetupDialog' action='SetupDialog'/>"//~var8R~
//			"</menu>"                                              //~var8R~
#ifdef GGG                                                         //~vawFI~
	  		"<menuitem name='Setup' action='Setup'/>"              //~var8R~
#else                                                              //~vawFI~
			"<menu name='Setup' action='SetupMenu'>"               //~vawFI~
				"<menuitem name='SetupDialog' action='Setup'/>"    //~vawFI~
			"</menu>"                                              //~vawFI~
#endif                                                             //~vawFI~
//  		"<menu name='Preview' action='Preview'>"               //~var8R~
//  		"</menu>"                                              //~var8R~
#ifdef GGG                                                         //~vawFI~
    		"<menuitem name='Preview' action='Preview'/>"          //~var8R~
#else                                                              //~vawFI~
			"<menu name='Preview' action='PreviewMenu'>"           //~vawFI~
	    		"<menuitem name='PreviewDialog' action='Preview'/>"//~vawFI~
			"</menu>"                                              //~vawFI~
#endif                                                             //~vawFI~
			"<menu name='help2' action='help2'>"                   //~var8R~
				"<menuitem name='HelpDoc' action='HelpDoc'/>"      //~var8R~
				"<menuitem name='Version' action='Version'/>"      //~var8R~
			"</menu>"                                              //~var8R~
    	"</menubar>"                                               //~var8R~
                                                                   //~var8R~
//        "<menubar name='menubar1'>"                              //~var8R~
//            "<menu name='_File' action='_File'/>"                //~var8R~
//            "<menu name='_Edit' action='_Edit'/>"                //~var8R~
//            "<menu name='_Setup' action='_Setup'/>"              //~var8R~
//            "<menu name='_Preview' action='_Preview'/>"          //~var8R~
//            "<menu name='_Help' action='_Help'/>"                //~var8R~
//        "</menubar>"                                             //~var8R~
    "</ui>";                                                       //~var8R~
#endif //GTK_CHECK_VERSION(3,10,0)                                 //~vb7tI~
#endif	//!CCC                                                     //~var8R~
#ifdef BBB                                                         //~var8R~
static const gchar *main_menu_uiinfo=                              //~var8R~
	"<?xml version='1.0'?>"                                        //~var8R~
	"<interface>"                                                  //~var8R~
    "<menu id='MainMenu'>"                                         //~var8R~
    	"<submenu id='file'>"                                      //~var8R~
			"<attribute name='label' translatable='yes'>_File</attribute>"//~var8R~
            "<section>"                                            //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>new</attribute>"         //~var8R~
					"<attribute name='label' translatable='yes'>_New</attribute>"//~var8R~
					"<attribute name='action'>win.new</attribute>" //~var8R~
					"<attribute name='accel'>&lt;Primary&gt;n</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>open</attribute>"        //~var8R~
					"<attribute name='label' translatable='yes'>_Open</attribute>"//~var8R~
					"<attribute name='action'>win.open</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;o</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>save</attribute>"        //~var8R~
					"<attribute name='label' translatable='yes'>_Save</attribute>"//~var8R~
					"<attribute name='action'>win.save</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;s</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>saveas</attribute>"      //~var8R~
					"<attribute name='label' translatable='yes'>_SaveAs</attribute>"//~var8R~
					"<attribute name='action'>win.saveas</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;a</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            "</section>"                                           //~var8R~
            "<section>"                                            //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>print</attribute>"       //~var8R~
					"<attribute name='label' translatable='yes'>_Print</attribute>"//~var8R~
					"<attribute name='action'>win.print</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;p</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>prtscr</attribute>"      //~var8R~
					"<attribute name='label' translatable='yes'>_PrtScr</attribute>"//~var8R~
					"<attribute name='action'>win.prtscr</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;h</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            "</section>"                                           //~var8R~
            "<section>"                                            //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>home</attribute>"        //~var8R~
					"<attribute name='label' translatable='yes'>_Home</attribute>"//~var8R~
					"<attribute name='action'>win.home</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;e</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>terminal</attribute>"    //~var8R~
					"<attribute name='label' translatable='yes'>_Term</attribute>"//~var8R~
					"<attribute name='action'>win.term</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;m</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>exit</attribute>"        //~var8R~
					"<attribute name='label' translatable='yes'>_Exit</attribute>"//~var8R~
					"<attribute name='action'>win.exit</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;x</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            "</section>"                                           //~var8R~
    	"</submenu>"                                               //~var8R~
    	"<submenu id='edit'>"                                      //~var8R~
			"<attribute name='label' translatable='yes'>_Edit</attribute>"//~var8R~
            "<section>"                                            //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>cut</attribute>"         //~var8R~
					"<attribute name='label' translatable='yes'>_Cut</attribute>"//~var8R~
					"<attribute name='action'>win.cut</attribute>" //~var8R~
					"<attribute name='accel'>&lt;Primary&gt;t</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>copy</attribute>"        //~var8R~
					"<attribute name='label' translatable='yes'>_Copy</attribute>"//~var8R~
					"<attribute name='action'>win.copy</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;c</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>clear</attribute>"       //~var8R~
					"<attribute name='label' translatable='yes'>_Clear</attribute>"//~var8R~
					"<attribute name='action'>win.clear</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;c</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>paste_V</attribute>"     //~var8R~
					"<attribute name='label' translatable='yes'>_Paste</attribute>"//~var8R~
					"<attribute name='action'>win.PasteV</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;v</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>paste_insert</attribute>"//~var8R~
					"<attribute name='label' translatable='yes'>_Paste-Insert</attribute>"//~var8R~
					"<attribute name='action'>win.paste_insert</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;i</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>paste_replace</attribute>"//~var8R~
					"<attribute name='label' translatable='yes'>_Paste-Replace</attribute>"//~var8R~
					"<attribute name='action'>win.paste_replace</attribute>"//~var8R~
					"<attribute name='accel'>&lt;Primary&gt;r</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~vbd2M~
					"<attribute name='id'>SelectAll</attribute>"   //~vbd2M~
					"<attribute name='label' translatable='yes'>_SelectAll</attribute>"//~vbd2M~
					"<attribute name='action'>win.selectall</attribute>"//~vbd2M~
					"<attribute name='accel'>&lt;Primary&gt;t</attribute>"//~vbd2M~
            	"</item>"                                          //~vbd2M~
            "</section>"                                           //~var8R~
    	"</submenu>"                                               //~var8R~
    	"<submenu id='setup'>"                                     //~var8R~
            "<section>"                                            //~var8R~
				"<attribute name='label' translatable='yes'>_Setup</attribute>"//~var8R~
				"<attribute name='action'>win.setup</attribute>"   //~var8R~
            "</section>"                                           //~var8R~
    	"</submenu>"                                               //~var8R~
    	"<submenu id='preview2'>"                                  //~var8R~
			"<attribute name='label' translatable='yes'>_Preview</attribute>"//~var8R~
			"<attribute name='action'>win.preview</attribute>"     //~var8R~
    	"</submenu>"                                               //~var8R~
    	"<submenu id='help2'>"                                     //~var8R~
			"<attribute name='label' translatable='yes'>_Help</attribute>"//~var8R~
            "<section>"                                            //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>helpdoc</attribute>"     //~var8R~
					"<attribute name='label' translatable='yes'>_HelpDoc</attribute>"//~var8R~
					"<attribute name='action'>win.helpdoc</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            	"<item>"                                           //~var8R~
					"<attribute name='id'>version</attribute>"     //~var8R~
					"<attribute name='label' translatable='yes'>_Version</attribute>"//~var8R~
					"<attribute name='action'>win.version</attribute>"//~var8R~
            	"</item>"                                          //~var8R~
            "</section>"                                           //~var8R~
    	"</submenu>"                                               //~var8R~
	"</menu>"                                                      //~var8R~
	"</interface>";                                                //~var8R~
#endif	//BBB                                                      //~var8R~

#ifndef CCC                                                        //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tM~
    #define GTK3_MNEMONIC_OPEN      _("_Open")                     //~vb7tI~
    #define GTK3_MNEMONIC_CANCEL    _("_Cancel")                   //~vb7tI~
    #define GTK3_MNEMONIC_CLOSE     _("_Close")                    //~vb7tI~
    #define GTK3_MNEMONIC_OK        _("_OK")                       //~vb7tI~
    #define GTK3_MNEMONIC_YES       _("_Yes")                      //~vb7tI~
    #define GTK3_MNEMONIC_NEW       _("_New")                       //~vb7tI~//~vbdmI~
                                                                   //~vb7tI~
    typedef struct  _UActionEntry{                                 //~vb7tI~
                const gchar *name;                                 //~vb7tI~
                const gchar *stock_id;                             //~vb7tI~
                const gchar *label;                                //~vb7tI~
                const gchar *accelerator;                          //~vb7tI~
                const gchar *tooltip;                              //~vb7tI~
                GCallback    callback;                             //~vb7tI~
                GtkWidget   *menuitem;                             //~vb7tI~
        } UActionEntry;                                            //~vb7tI~
                                                                   //~vb7tI~
static UActionEntry actions[]={                                    //~vb7tI~
#else                                                              //~vb7tI~
static GtkActionEntry actions[]={	                               //~var8R~
#endif                                                             //~vb7tI~
//*   name     stock id         	label       	accelerator		tooltip	callback							is_active//~var8R~
  	{"File",	NULL,				"_File"},                      //~var8R~
//	{"New",		GTK_STOCK_NEW,		"_New",			"<control>N",	NULL,	G_CALLBACK(on_new_activate)			},//~var8R~//~vbdiR~
	{"New",		GTK_STOCK_NEW,		N_("New(_N)"),	"<control>N",	NULL,	G_CALLBACK(on_new_activate)			},//~vbdiI~
//	{"Open",	GTK_STOCK_OPEN, 	"_Open",		"<control>O",	NULL,	G_CALLBACK(on_open_activate) 		},//~var8R~//~vbdiR~
  	{"Open",	GTK_STOCK_OPEN, 	N_("Open(_O)"),		"<control>O",	NULL,	G_CALLBACK(on_open_activate) 		},//~vbdiI~
//  {"Save",	GTK_STOCK_SAVE, 	"_Save",		"<control>S",	NULL,	G_CALLBACK(on_save_activate) 		},//~var8R~//~vbdiR~
    {"Save",	GTK_STOCK_SAVE, 	N_("Save(_S)"),		"<control>S",	NULL,	G_CALLBACK(on_save_activate) 		},//~vbdiI~
//    {"SaveAs",  GTK_STOCK_SAVE_AS,  "Save_As",      "<control>A",   NULL,   G_CALLBACK(on_saveas_activate)      },//~var8R~//~vbd2R~
//  {"SaveAs",  GTK_STOCK_SAVE_AS,  "Save_As",      "<control><shift>A",   NULL,   G_CALLBACK(on_saveas_activate)      },//~vbd2I~//~vbdiR~
    {"SaveAs",  GTK_STOCK_SAVE_AS,  N_("SaveAs(_A)"),      "<control><shift>A",   NULL,   G_CALLBACK(on_saveas_activate)      },//~vbdiI~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
	{""},	//separator                                            //~vb7tI~
#endif                                                             //~vb7tI~
//  {"Print",  	GTK_STOCK_PRINT,	"_Print",  		"<control>P",	NULL,	G_CALLBACK(on_print_activate) 		},//~var8R~//~vbdiR~
    {"Print",  	GTK_STOCK_PRINT,	N_("Print(_P)"),  		"<control>P",	NULL,	G_CALLBACK(on_print_activate) 		},//~vbdiI~
//  {"PrtScr", 	GTK_STOCK_PRINT,	"_PrtScr",  	"<control>H",	NULL,	G_CALLBACK(on_prtscr_activate) 		},//~var8R~//~vbdiR~
    {"PrtScr", 	GTK_STOCK_PRINT,	N_("PrtScr(_H)"),  	"<control>H",	NULL,	G_CALLBACK(on_prtscr_activate) 		},//~vbdiI~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
	{""},	//separator                                            //~vb7tI~
#endif                                                             //~vb7tI~
//  {"Home",   	GTK_STOCK_HOME,		"Home",  		"<control>E",	NULL,	G_CALLBACK(on_home_activate) 		},//~var8R~//~vbdiR~
    {"Home",   	GTK_STOCK_HOME,		N_("Home(_E)"),  		"<control>E",	NULL,	G_CALLBACK(on_home_activate) 		},//~vbdiI~
//  {"Term",   	GTK_STOCK_HOME,		"Term",   		"<control>M",	NULL,	G_CALLBACK(on_terminal_activate) 	},//~var8R~//~vbdiR~
    {"Term",   	GTK_STOCK_HOME,		N_("Term(_M)"),   		"<control>M",	NULL,	G_CALLBACK(on_terminal_activate) 	},//~vbdiI~
//  {"Exit",   	GTK_STOCK_QUIT,		"Exit",   		"<control>X",	NULL,	G_CALLBACK(on_exit_activate) 		},//~var8R~//~vbdiR~
    {"Exit",   	GTK_STOCK_QUIT,		N_("Exit(_X)"),   		"<control>X",	NULL,	G_CALLBACK(on_exit_activate) 		},//~vbdiI~
                                                                   //~var8R~
  	{"Edit",	NULL,				"Edit"},                       //~var8R~
//  {"Cut",		GTK_STOCK_CUT,		"Cut",			"<control>T",	NULL,	G_CALLBACK(on_cut_activate) 		},//~var8R~//~vbdiR~
    {"Cut",		GTK_STOCK_CUT,		N_("Cut(_T)"),			"<control>T",	NULL,	G_CALLBACK(on_cut_activate) 		},//~vbdiI~
//  {"Copy",	GTK_STOCK_COPY, 	"Copy",			"<control>C",	NULL,	G_CALLBACK(on_copy_activate) 		},//~var8R~//~vbdiR~
    {"Copy",	GTK_STOCK_COPY, 	N_("Copy(_C)"),			"<control>C",	NULL,	G_CALLBACK(on_copy_activate) 		},//~vbdiI~
//  {"Clear",   GTK_STOCK_CLEAR,	"Clear",   		"<control>L",	NULL,	G_CALLBACK(on_clear_activate) 		},//~var8R~//~vbdiR~
    {"Clear",   GTK_STOCK_CLEAR,	N_("Clear(_L)"),   		"<control>L",	NULL,	G_CALLBACK(on_clear_activate) 		},//~vbdiI~
//  {"Paste",   GTK_STOCK_PASTE,	"Paste",   		"<control>V",	NULL,	G_CALLBACK(on_PasteV_activate) 		},//~var8R~//~vbdiR~
    {"Paste",   GTK_STOCK_PASTE,	N_("Paste(_V)"),   		"<control>V",	NULL,	G_CALLBACK(on_PasteV_activate) 		},//~vbdiI~
//  {"Paste-Insert",NULL,			"Paste-Insert","<control>I",	NULL,	G_CALLBACK(on_paste_insert_activate)},//~var8R~//~vbdiR~
    {"Paste-Insert",NULL,			N_("Paste-Insert(_I)"),"<control>I",	NULL,	G_CALLBACK(on_paste_insert_activate)},//~vbdiI~
//  {"Paste-Replace",NULL,			"Paste-Replace","<control>R",	NULL,	G_CALLBACK(on_paste_replace_activate)},//~var8R~//~vbdiR~
    {"Paste-Replace",NULL,			N_("Paste-Replace(_R)"),"<control>R",	NULL,	G_CALLBACK(on_paste_replace_activate)},//~vbdiI~
//  {"SelectAll",GTK_STOCK_SELECT_ALL,	"SelectAll","<control>A",	NULL,	G_CALLBACK(on_selectall_activate) 		},//~vbd2M~//~vbdiR~
    {"SelectAll",GTK_STOCK_SELECT_ALL,	N_("SelectAll(_A)"),"<control>A",	NULL,	G_CALLBACK(on_selectall_activate) 		},//~vbdiI~
                                                                   //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
	{"Setup",   NULL,		        "Setup",		NULL, 			NULL,	G_CALLBACK(on_setup_activate)},//~vb7tI~
	{"Preview", NULL,				"Preview",		NULL,           NULL,   G_CALLBACK(on_preview_activate)},//~vb7tI~
	{"help2",   NULL,			    "Help"},                       //~vb7tI~
	{"HelpDoc",	GTK_STOCK_HELP,		"HelpDoc","",NULL,	G_CALLBACK(on_helpdoc_activate) 	},//~vb7tI~
	{"Version",	NULL,               "Version","",NULL,	G_CALLBACK(on_version_activate) 	},//~vb7tI~
#else                                                              //~vb7tI~
#ifdef GGG                                                         //~vawFI~
//  {"Setup",   NULL,			    "Setup"},                      //~var8R~
	{"Setup",   NULL,			    "Setup",        NULL,			NULL,	G_CALLBACK(on_setup_activate)},//~var8R~
//    {"SetupDialog",NULL,            "SetupDialog",  NULL,           NULL,   G_CALLBACK(on_setupdialog_activate)},//~var8R~
#else                                                              //~vawFI~
	{"SetupMenu",   NULL,		    "Setup"},                      //~vawFI~
	{"Setup",   NULL,			    "Open Dialog",        NULL,			NULL,	G_CALLBACK(on_setup_activate)},//~vawFI~
#endif                                                             //~vawFI~
#ifdef GGG                                                         //~vawFI~
	{"Preview", NULL,			    "Preview",		NULL,           NULL,   G_CALLBACK(on_preview_activate)},//~var8R~
//    {"PreviewDialog",NULL,          "PreviewDialog",  NULL,         NULL,   G_CALLBACK(on_previewdialog_activate)},//~var8R~
	{"PreviewDialog",   NULL,		"Open Dialog"},                //~vawFI~
#else                                                              //~vawFI~
	{"PreviewMenu",   NULL,		"Preview"},                        //~vawFI~
	{"Preview", NULL,			"Open Dialog",		NULL,           NULL,   G_CALLBACK(on_preview_activate)},//~vawFI~
#endif                                                             //~vawFI~
                                                                   //~var8R~
	{"help2",   NULL,			    "Help"},                       //~var8R~
	{"HelpDoc",	GTK_STOCK_HELP,		"HelpDoc","",NULL,	G_CALLBACK(on_helpdoc_activate) 	},//~var8R~
	{"Version",	NULL,               "Version", 	NULL,			NULL,	G_CALLBACK(on_version_activate) 	},//~var8R~
#endif  //GTK3.10                                                  //~vb7tM~
};                                                                 //~var8R~
#ifdef AAA                                                         //~var8R~
	DEFINE_ACTION_SELECT_FUNC(setup,STRID_SETUP)                   //~var8R~
	DEFINE_ACTION_SELECT_FUNC(preview,STRID_PAGE_SETUP)            //~var8R~
#endif                                                             //~var8R~
#endif	//!CCC                                                     //~var8R~
#ifdef BBB                                                         //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(new)                               //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(open)                              //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(save)                              //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(saveas)                            //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(print)                             //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(prtscr)                            //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(home)                              //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(terminal)                          //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(exit)                              //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(cut)                               //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(copy)                              //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(clear)                             //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(PasteV)                            //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(paste_insert)                      //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(paste_replace)                     //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(setup)                             //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(preview)                           //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(helpdoc)                           //~var8R~
	DEFINE_ACTION_ACTIVATE_FUNC(version)                           //~var8R~
static  GActionEntry actions[]={                                   //~var8R~
//  DEFINE_ACTION(File),                                           //~var8R~
	DEFINE_ACTION(new),                                            //~var8R~
	DEFINE_ACTION(open),                                           //~var8R~
	DEFINE_ACTION(save),                                           //~var8R~
	DEFINE_ACTION(saveas),                                         //~var8R~
	DEFINE_ACTION(print),                                          //~var8R~
	DEFINE_ACTION(prtscr),                                         //~var8R~
	DEFINE_ACTION(home),                                           //~var8R~
	DEFINE_ACTION(terminal),                                       //~var8R~
	DEFINE_ACTION(exit),                                           //~var8R~
                                                                   //~var8R~
//  DEFINE_ACTION(Edit),                                           //~var8R~
	DEFINE_ACTION(cut),                                            //~var8R~
	DEFINE_ACTION(copy),                                           //~var8R~
	DEFINE_ACTION(clear),                                          //~var8R~
	DEFINE_ACTION(PasteV),                                         //~var8R~
	DEFINE_ACTION(paste_insert),                                   //~var8R~
	DEFINE_ACTION(paste_replace),                                  //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION(setup),                                          //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION(preview),                                        //~var8R~
                                                                   //~var8R~
	DEFINE_ACTION(helpdoc),                                        //~var8R~
	DEFINE_ACTION(version)                                         //~var8R~
};                                                                 //~var8R~
#endif                                                             //~var8R~
#endif                                                             //~var8R~
//void listmenu()                                                  //~var8R~
//{                                                                //~var8R~
//    GSList *plist;                                               //~var8R~
//    int ii=0;                                                    //~var8R~
//    printf("menu type=%x,menuitem=%x\n",GTK_TYPE_MENU,GTK_TYPE_MENU_ITEM);//~var8R~
//    plist=gtk_builder_get_objects(Smenubuilder);                 //~var8R~
//    for (;plist;plist=plist->next)                               //~var8R~
//    {                                                            //~var8R~
//        printf("gtkmenu #=%d\n",++ii);                           //~var8R~
//        if (GTK_IS_MENU_ITEM(plist->data))                       //~var8R~
//        {                                                        //~var8R~
//            GtkMenuItem *item=(GtkMenuItem*)plist->data;         //~var8R~
//            printf("gtkmenuitem label=%s\n",gtk_menu_item_get_label(item));//~var8R~
//        }                                                        //~var8R~
//        if (GTK_IS_MENU(plist->data))                            //~var8R~
//        {                                                        //~var8R~
//            printf("gtkmenu\n");                                 //~var8R~
//        }                                                        //~var8R~
//        if (G_IS_MENU(plist->data))                              //~var8R~
//        {                                                        //~var8R~
//            printf("g_menu\n");                                  //~var8R~
//        }                                                        //~var8R~
//        if (G_IS_MENU_ITEM(plist->data))                         //~var8R~
//        {                                                        //~var8R~
//            printf("g_menuitem\n");                              //~var8R~
//        }                                                        //~var8R~
//        if (GTK_IS_CONTAINER(GTK_WIDGET(plist->data)))           //~var8R~
//        {                                                        //~var8R~
//            GList *children=gtk_container_get_children(GTK_CONTAINER(plist->data));//~var8R~
//            printf("gtkcontainer child=%d\n",g_list_length(children));//~var8R~
//        }                                                        //~var8R~
//    }                                                            //~var8R~
//}                                                                //~var8R~
GtkWidget*
create_framewindow (void)
{
  GtkWidget *framewindow;
  GdkPixbuf *framewindow_icon_pixbuf;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkWidget *bonobodock1;
#endif                                                             //+var8~//~var8R~
  GtkWidget *toolbar1;
  GtkIconSize tmp_toolbar_icon_size;
  GtkWidget *tmp_image;
  GtkWidget *button_open;
  GtkWidget *button_save;
  GtkWidget *button_end;
  GtkWidget *button_cancel;
  GtkWidget *button_print;
  GtkWidget *button_home;
  GtkWidget *button_terminal;
  GtkWidget *button_cut;
  GtkWidget *button_copy;
  GtkWidget *button_clear;
  GtkWidget *button_pasteV;
  GtkWidget *button_pasteins;
  GtkWidget *button_pasterep;
  GtkWidget *maindraw;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkWidget *appbar1;
#endif                                                             //+var8~//~var8R~
  GtkTooltips *tooltips;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else                                                              //~var8R~
  GtkWidget *vbox;                                                 //~var8R~
#endif                                                             //+var8~//~var8R~
//***************************                                      //~var8R~
  tooltips = gtk_tooltips_new ();

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  framewindow = gnome_app_new ("gxe", _("gxe"));
#else                                                              //+var8~//~var8R~
//#ifndef GTK3GTK3                                                    //+var8I~//~var8R~
//  framewindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);             //~var8R~
//#else                                                              //+var8I~//~var8R~
  framewindow = gtk_application_window_new(GTK_APPLICATION(Ggtkappgxe));//~var8R~
  vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,3/*menubar,toolbar,canvas*/);//~var8R~
  gtk_container_add(GTK_CONTAINER(framewindow),vbox);              //~var8R~
  dprintf("create_framewindow framewindow=%p,vbox=%p\n",framewindow,vbox);//~var8R~
//#endif                                                             //+var8I~//~var8R~
#endif                                                             //+var8~//~var8R~
  gtk_window_set_position (GTK_WINDOW (framewindow), GTK_WIN_POS_MOUSE);
  framewindow_icon_pixbuf = create_pixbuf ("gxe/wxe.png");
  if (framewindow_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (framewindow), framewindow_icon_pixbuf);
#if GTK_MAJOR_VERSION>=2                                           //~vak3R
      g_object_unref(framewindow_icon_pixbuf);                     //~vak3I
#else                                                              //~vak3R
      gdk_pixbuf_unref (framewindow_icon_pixbuf);
#endif                                                             //~vak3I
    }

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  bonobodock1 = GNOME_APP (framewindow)->dock;
  gtk_widget_show (bonobodock1);

  gnome_app_create_menus (GNOME_APP (framewindow), menubar1_uiinfo);
#else                                                              //+var8~//~var8R~
#ifndef CCC                                                        //~var8R~
	interface_create_menu(framewindow,vbox);                       //~var8R~
#endif                                                             //~var8R~
#endif                                                             //+var8~//~var8R~

  toolbar1 = gtk_toolbar_new ();
  gtk_widget_show (toolbar1);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gnome_app_add_toolbar (GNOME_APP (framewindow), GTK_TOOLBAR (toolbar1), "toolbar1",
                                BONOBO_DOCK_ITEM_BEH_EXCLUSIVE,
                                BONOBO_DOCK_TOP, 1, 0, 0);
#else                                                              //~var8R~
  gtk_container_add(GTK_CONTAINER(vbox),toolbar1);                 //~var8R~
#endif                                                             //+var8~//~var8R~
  gtk_container_set_border_width (GTK_CONTAINER (toolbar1), 1);
//gtk_toolbar_set_style (GTK_TOOLBAR (toolbar1), GTK_TOOLBAR_BOTH);//~var7R
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar1), GTK_TOOLBAR_ICONS);//icon only//~var8R~
  tmp_toolbar_icon_size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (toolbar1));

//tmp_image = gtk_image_new_from_stock ("gtk-save", tmp_toolbar_icon_size);//~var0R
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock (GTK_STOCK_OPEN, tmp_toolbar_icon_size);//~var8R~
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tR~
  tmp_image = gtk_image_new_from_icon_name(TB_STOCK_OPEN, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tR~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_OPEN, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tR~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_open = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Open"));
#else                                                              //~var8R~
  button_open = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL); //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_open);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_open);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_open), tooltips, _("Open File"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-save", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_SAVE, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_SAVE, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_save = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Save"));
#else                                                              //~var8R~
  button_save = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL); //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_save);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_save);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_save), tooltips, _("Save File"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-floppy", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_END, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_END, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_end = (GtkWidget*) gtk_tool_button_new (tmp_image, _("End"));
#else                                                              //~var8R~
  button_end = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);  //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_end);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_end);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_end), tooltips, _("Save then Close"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-missing-image", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_CANCEL, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_CANCEL, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_cancel = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Can"));
#else                                                              //~var8R~
  button_cancel = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_cancel);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_cancel);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_cancel), tooltips, _("Discard"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-print", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_PRINT, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_PRINT, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_print = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Prt"));
#else   //OPTGTK3                                                  //~var8R~
  button_print = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_print);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_print);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_print), tooltips, _("Print"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-home", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_HOME, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_HOME, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_home = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Home"));
#else                                                              //~var8R~
  button_home = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL); //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_home);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_home);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_home), tooltips, _("Home"), NULL);
#else   //OPTGTK3                                                  //~var8R~
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_home), tooltips, _("nautilus Home"), NULL);//~var8R~
#endif                                                             //~var8R~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-execute", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_TERMINAL, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_TERMINAL, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_terminal = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Term"));
#else                                                              //~var8R~
  button_terminal = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_terminal);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_terminal);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_terminal), tooltips, _("Open Terminal Window"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-cut", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_CUT, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_CUT, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_cut = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Cut"));
#else                                                              //~var8R~
  button_cut = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);  //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_cut);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_cut);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_cut), tooltips, _("Cut"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-copy", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_COPY, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_COPY, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_copy = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Copy"));
#else                                                              //~var8R~
  button_copy = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL); //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_copy);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_copy);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_copy), tooltips, _("Copy"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-clear", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_CLEAR, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_CLEAR, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_clear = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Clr"));
#else                                                              //~var8R~
  button_clear = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_clear);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_clear);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_clear), tooltips, _("Clear"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-paste", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_PASTE, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_PASTE, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_pasteV = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Paste"));
#else   //OPTGTK3                                                  //~var8R~
  button_pasteV = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_pasteV);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_pasteV);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_pasteV), tooltips, _("Paste(Like Windows Ctrl+v)"), NULL);

#ifdef DDD                                                         //~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-paste", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_PASTE_INS, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_PASTE_INS, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_pasteins = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Ins"));
#else                                                              //~var8R~
  button_pasteins = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_pasteins);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_pasteins);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_pasteins), tooltips, _("Paste(BlockInsert)"), NULL);

#ifdef DDD                                                         //~var8R~
  tmp_image = gtk_image_new_from_stock ("gtk-paste", tmp_toolbar_icon_size);
#else   //OPTGTK3                                                  //~var8R~
 #if GTK_CHECK_VERSION(3,10,0)                                     //~vb7tI~
  tmp_image = gtk_image_new_from_icon_name (TB_STOCK_PASTE_REP, tmp_toolbar_icon_size);//~vb7tI~
 #else                                                             //~vb7tI~
  tmp_image = gtk_image_new_from_stock (TB_STOCK_PASTE_REP, tmp_toolbar_icon_size);//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //~var8R~
  gtk_widget_show (tmp_image);
#ifndef OPTGTK3                                                    //~var8R~
  button_pasterep = (GtkWidget*) gtk_tool_button_new (tmp_image, _("Rep"));
#else                                                              //~var8R~
  button_pasterep = (GtkWidget*) gtk_tool_button_new (tmp_image,NULL);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (button_pasterep);
  gtk_container_add (GTK_CONTAINER (toolbar1), button_pasterep);
  gtk_tool_item_set_tooltip (GTK_TOOL_ITEM (button_pasterep), tooltips, _("Paste(BlockReplace)"), NULL);

  maindraw = gtk_drawing_area_new ();
  gtk_widget_show (maindraw);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gnome_app_set_contents (GNOME_APP (framewindow), maindraw);
#else                                                              //+var8~//~var8R~
//gtk_container_add(GTK_CONTAINER(vbox),maindraw);                 //~var8R~
  gtk_box_pack_start(GTK_BOX(vbox),maindraw,TRUE/*expand*/,TRUE/*fill*/,0/*padding*/);//~var8R~
#endif                                                             //+var8~//~var8R~
  GTK_WIDGET_SET_FLAGS (maindraw, GTK_CAN_FOCUS);
#ifdef AAA                                                         //~vb7BR~
  gtk_widget_set_events (maindraw, GDK_EXPOSURE_MASK | GDK_BUTTON1_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK | GDK_FOCUS_CHANGE_MASK);
#else                                                              //~vb7BR~
  gtk_widget_set_events (maindraw, GDK_EXPOSURE_MASK | GDK_BUTTON1_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK | GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK | GDK_FOCUS_CHANGE_MASK | GDK_SCROLL_MASK);//~vb7BR~
#endif                                                             //~vb7BR~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  appbar1 = gnome_appbar_new (FALSE, FALSE, GNOME_PREFERENCES_NEVER);
  gtk_widget_show (appbar1);
  gnome_app_set_statusbar (GNOME_APP (framewindow), appbar1);
#endif                                                             //+var8~//~var8R~

  g_signal_connect ((gpointer) framewindow, "realize",
                    G_CALLBACK (on_framewindow_realize),
                    NULL);
  g_signal_connect ((gpointer) framewindow, "unrealize",
                    G_CALLBACK (on_framewindow_unrealize),
                    NULL);
  g_signal_connect ((gpointer) framewindow, "configure_event",
                    G_CALLBACK (on_framewindow_configure_event),
                    NULL);
  g_signal_connect ((gpointer) framewindow, "delete_event",
                    G_CALLBACK (on_framewindow_delete_event),
                    NULL);
  g_signal_connect ((gpointer) framewindow, "destroy_event",
                    G_CALLBACK (on_framewindow_destroy_event),
                    NULL);
  g_signal_connect ((gpointer) framewindow, "drag_data_received",
                    G_CALLBACK (on_framewindow_drag_data_received),
                    NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gnome_app_install_menu_hints (GNOME_APP (framewindow), menubar1_uiinfo);
#endif                                                             //+var8~//~var8R~
  g_signal_connect ((gpointer) button_open, "clicked",
                    G_CALLBACK (on_button_open_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_save, "clicked",
                    G_CALLBACK (on_button_save_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_end, "clicked",
                    G_CALLBACK (on_button_end_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_cancel, "clicked",
                    G_CALLBACK (on_button_cancel_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_print, "clicked",
                    G_CALLBACK (on_button_print_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_home, "clicked",
                    G_CALLBACK (on_button_home_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_terminal, "clicked",
                    G_CALLBACK (on_button_terminal_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_cut, "clicked",
                    G_CALLBACK (on_button_cut_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_copy, "clicked",
                    G_CALLBACK (on_button_copy_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_clear, "clicked",
                    G_CALLBACK (on_button_pasteV_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_pasteV, "clicked",
                    G_CALLBACK (on_button_pasteV_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_pasteins, "clicked",
                    G_CALLBACK (on_button_pasteins_clicked),
                    NULL);
  g_signal_connect ((gpointer) button_pasterep, "clicked",
                    G_CALLBACK (on_button_pasterep_clicked),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "configure_event",
                    G_CALLBACK (on_maindraw_configure_event),
                    NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_signal_connect ((gpointer) maindraw, "expose_event",
                    G_CALLBACK (on_maindraw_expose_event),
                    NULL);
#else   //OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) maindraw, "draw",                   //~var8R~
                    G_CALLBACK (on_maindraw_draw),                 //~var8R~
                    NULL);                                         //~var8R~
#endif                                                             //~var8R~
  g_signal_connect ((gpointer) maindraw, "button_press_event",
                    G_CALLBACK (on_maindraw_button_press_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "button_release_event",
                    G_CALLBACK (on_maindraw_button_release_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "key_press_event",
                    G_CALLBACK (on_maindraw_key_press_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "key_release_event",
                    G_CALLBACK (on_maindraw_key_release_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "leave_notify_event",
                    G_CALLBACK (on_maindraw_leave_notify_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "enter_notify_event",
                    G_CALLBACK (on_maindraw_enter_notify_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "motion_notify_event",
                    G_CALLBACK (on_maindraw_motion_notify_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "realize",
                    G_CALLBACK (on_maindraw_realize),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "unrealize",
                    G_CALLBACK (on_maindraw_unrealize),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "focus_in_event",
                    G_CALLBACK (on_maindraw_focus_in_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "focus_out_event",
                    G_CALLBACK (on_maindraw_focus_out_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "scroll_event",
                    G_CALLBACK (on_maindraw_scroll_event),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "drag_data_get",
                    G_CALLBACK (on_maindraw_drag_data_get),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "drag_end",
                    G_CALLBACK (on_maindraw_drag_end),
                    NULL);
  g_signal_connect ((gpointer) maindraw, "drag_begin",
                    G_CALLBACK (on_maindraw_drag_begin),
                    NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_signal_connect ((gpointer) maindraw, "client_event",
                    G_CALLBACK (on_maindraw_client_event),
                    NULL);
#else   //OPTGTK3                                                  //~var8R~
    interface_add_filter(maindraw/*GPview*/);                      //~var8R~
#endif                                                             //~var8R~

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (framewindow, framewindow, "framewindow");
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GLADE_HOOKUP_OBJECT (framewindow, bonobodock1, "bonobodock1");
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[0].widget, "file");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[0].widget, "new");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[1].widget, "open");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[2].widget, "save");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[3].widget, "saveas");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[4].widget, "separator1");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[5].widget, "print");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[6].widget, "prtscr");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[7].widget, "seperator2");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[8].widget, "home");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[9].widget, "terminal");
  GLADE_HOOKUP_OBJECT (framewindow, file_menu_uiinfo[10].widget, "exit");
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[1].widget, "edit");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[0].widget, "cut");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[1].widget, "copy");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[2].widget, "clear");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[3].widget, "paste_V");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[4].widget, "paste_insert");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[5].widget, "paste_replace");
  GLADE_HOOKUP_OBJECT (framewindow, edit_menu_uiinfo[6].widget, STRID_EDIT_SELECTALL/*"selectall"*/);//~vbd2R~
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[2].widget, "setup");
#ifdef GGG                                                         //~vawFI~
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[3].widget, "preview2");//~vawFR~
#else                                                              //~vawFI~
//  GLADE_HOOKUP_OBJECT (framewindow, preview_menu_uiinfo[0].widget, STRID_PAGE_SETUP);//~vawFI~//~vbdcR~
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[3].widget, STRID_PAGE_SETUP);//~vbdcI~
#endif                                                             //~vawFI~
  GLADE_HOOKUP_OBJECT (framewindow, menubar1_uiinfo[4].widget, "help2");
  GLADE_HOOKUP_OBJECT (framewindow, help2_menu_uiinfo[0].widget, "helpdoc");
  GLADE_HOOKUP_OBJECT (framewindow, help2_menu_uiinfo[1].widget, "version");
#else                                                              //+var8~//~var8R~
//    listmenu();                                                  //~var8R~
#ifndef CCC                                                        //~var8R~
//*                                     path        menuid strid   //~vawFI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","File",STRID_FILE/*lookup key*/);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","New",STRID_FILE_NEW);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Open",STRID_FILE_OPEN);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Save",STRID_FILE_SAVE);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","SaveAs",STRID_FILE_SAVEAS);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Print",STRID_FILE_PRINT);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","PrtScr",STRID_FILE_PRTSCR);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Home",STRID_FILE_HOME);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Term",STRID_FILE_TERMINAL);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/File","Exit",STRID_FILE_EXIT);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","Edit",STRID_EDIT);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Cut",STRID_EDIT_CUT);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Copy",STRID_EDIT_COPY);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Clear",STRID_EDIT_CLEAR);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Paste",STRID_EDIT_PASTE_V);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Paste-Insert",STRID_EDIT_PASTE);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","Paste-Replace",STRID_EDIT_PASTE_REP);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Edit","SelectAll",STRID_EDIT_SELECTALL);//~vbd2M~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","Setup",STRID_SETUP);//~vb7tI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","Preview",STRID_PAGE_SETUP);//~vb7tI~
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","Setup",STRID_SETUP);//~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Setup","SetupDialog",STRID_SETUP_DIALOG);//~var8R~
#ifdef GGG                                                         //~vawFI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","Preview",STRID_PAGE_SETUP);//~var8R~
#else                                                              //~vawFI~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Preview","PreviewDialog",STRID_PAGE_SETUP);//~vawFI~
#endif                                                             //~vawFI~
#endif	//GTK3.10                                                  //~vb7tI~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/Preview","PreviewDialog",STRID_PAGE_SETUP_DIALOG);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu","help2",STRID_HELP);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/help2","HelpDoc",STRID_HELPDOC);//~var8R~
  GLADE_HOOKUP_OBJECT_MENU (framewindow,"/MainMenu/help2","Version",STRID_VERSION);//~var8R~
                                                                   //~vb7tI~
//    {                                                            //~var8R~
//                                                                 //~var8R~
//        GtkWidget *wd;                                           //~var8R~
//#ifdef AAA   //selected also when hover                          //~var8R~
//        wd=lookup_widget(GTK_WIDGET(framewindow),STRID_SETUP); //edit menuitem//~var8R~
//        g_signal_connect ((gpointer)wd,"select",                 //~var8R~
//                    G_CALLBACK (on_setup_select),                //~var8R~
//                    NULL);                                       //~var8R~
//#endif                                                           //~var8R~
//        wd=lookup_widget(GTK_WIDGET(framewindow),STRID_PAGE_SETUP); //edit menuitem//~var8R~
//        g_signal_connect ((gpointer)wd,"select",                 //~var8R~
//                    G_CALLBACK (on_preview_select),              //~var8R~
//                    NULL);                                       //~var8R~
//    }                                                            //~var8R~
#endif                                                             //~var8R~
//#ifdef BBB                                                       //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"new");                  //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"open");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"save");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"saveas");               //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"print");                //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"prtscr");               //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"home");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"terminal");             //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"exit");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"edit");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"cut");                  //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"copy");                 //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"clear");                //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"paste_V");              //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"paste_insert");         //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"paste_replace");        //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"setup");                //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"preview2");             //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"help2");                //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"helpdoc");              //~var8R~
//  GLADE_HOOKUP_OBJECT_MENU (framewindow,"version");              //~var8R~
//#endif                                                           //~var8R~
#endif                                                             //+var8~//~var8R~
  GLADE_HOOKUP_OBJECT (framewindow, toolbar1, "toolbar1");
  GLADE_HOOKUP_OBJECT (framewindow, button_open, "button_open");
  GLADE_HOOKUP_OBJECT (framewindow, button_save, "button_save");
  GLADE_HOOKUP_OBJECT (framewindow, button_end, "button_end");
  GLADE_HOOKUP_OBJECT (framewindow, button_cancel, "button_cancel");
  GLADE_HOOKUP_OBJECT (framewindow, button_print, "button_print");
  GLADE_HOOKUP_OBJECT (framewindow, button_home, "button_home");
  GLADE_HOOKUP_OBJECT (framewindow, button_terminal, "button_terminal");
  GLADE_HOOKUP_OBJECT (framewindow, button_cut, "button_cut");
  GLADE_HOOKUP_OBJECT (framewindow, button_copy, "button_copy");
  GLADE_HOOKUP_OBJECT (framewindow, button_clear, "button_clear");
  GLADE_HOOKUP_OBJECT (framewindow, button_pasteV, "button_pasteV");
  GLADE_HOOKUP_OBJECT (framewindow, button_pasteins, "button_pasteins");
  GLADE_HOOKUP_OBJECT (framewindow, button_pasterep, "button_pasterep");
  GLADE_HOOKUP_OBJECT (framewindow, maindraw, "maindraw");
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GLADE_HOOKUP_OBJECT (framewindow, appbar1, "appbar1");
#endif                                                             //~var8R~
  GLADE_HOOKUP_OBJECT_NO_REF (framewindow, tooltips, "tooltips");

  gtk_widget_grab_focus (maindraw);
//#ifndef OPTGTK3                                                    //+var8~//~vawFR~
//#else                                                              //+var8~//~vawFR~
//#endif                                                             //+var8~//~vawFR~
#ifndef GGG                                                        //~vawFI~
  #if GTK_CHECK_VERSION(3,10,0)                                    //~vb7tI~
  #else                                                            //~vb7tI~
    set_menubar_dialog_open_signal();                              //~vawFI~
  #endif                                                           //~vb7tI~
#endif                                                             //+var8~//~vawFI~
  return framewindow;
}//create_framewindow                                              //~var8R~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  #if GTK_CHECK_VERSION(2,4,0)	//GtkFileChooser is available      //~vbdkI~
//*******************************************************************//~vbdkI~
//action 1:open/2:new/3:saveas                                     //~vbdkI~
//rc:4:cancel,1:new                                                //~vbdmI~
//*******************************************************************//~vbdkI~
GtkWidget *                                                        //~vbdkI~
create_fileselection (GtkWidget *Pparent,int Pactionid,int *Pprc)  //~vbdkI~
{                                                                  //~vbdkI~
  GtkWidget *fileselection;                                        //~vbdkI~
	GtkFileChooserAction action;                                   //~vbdkI~
	gchar *buttonid;                                               //~vbdkI~
	int rc;                                                        //~vbdkI~
    char *ptitle;                                                  //~vbdkI~
//***************************************                          //~vbdkI~
    if (Pactionid==1||Pactionid==2)//open/new                      //~vbdkI~
    {                                                              //~vbdkI~
 	  if (Pactionid==2) //New                                      //~vbdmI~
	   	action=GTK_FILE_CHOOSER_ACTION_SAVE;  //show textbox:name  //~vbdmR~
      else                                                         //~vbdmI~
    	action=GTK_FILE_CHOOSER_ACTION_OPEN;                       //~vbdkI~
        buttonid=GTK_STOCK_OPEN;                                   //~vbdkI~
    	if (Pactionid==1)                                          //~vbdkI~
	        ptitle="File Selection(OpenFile)";                     //~vbdkI~
        else                                                       //~vbdkI~
	        ptitle="File Selection(NewFile)";                      //~vbdkI~
    }                                                              //~vbdkI~
    else	//saveas                                               //~vbdkI~
    {                                                              //~vbdkI~
    	action=GTK_FILE_CHOOSER_ACTION_SAVE;                       //~vbdkI~
        buttonid=GTK_STOCK_SAVE_AS;                                //~vbdkI~
	    ptitle="File Selection(SaveAs)";                           //~vbdkI~
    }                                                              //~vbdkI~
//fileselection = gtk_file_chooser_dialog_new(_("File Selection"), //~vbdkI~
  fileselection = gtk_file_chooser_dialog_new(ptitle,              //~vbdkI~
  					GTK_WINDOW(Pparent),                           //~vbdkI~
                    action,                                        //~vbdkI~
                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,//button1 //~vbdkI~
                    buttonid,GTK_RESPONSE_ACCEPT,	//button2      //~vbdkI~
                    NULL);	//last                                 //~vbdkI~
 	if (Pactionid==2) //New                                        //~vbdmI~
    	gtk_file_chooser_set_current_name((GtkFileChooser*)fileselection,"NewFile"); //fill default name//~vbdmI~
  gtk_window_set_modal (GTK_WINDOW (fileselection), TRUE);         //~vbdkI~
  gtk_window_set_destroy_with_parent (GTK_WINDOW (fileselection), TRUE);//~vbdkI~
  gtk_window_set_type_hint (GTK_WINDOW (fileselection), GDK_WINDOW_TYPE_HINT_DIALOG);//~vbdkI~
  if (Gfileselectiondir && *Gfileselectiondir)                     //~vbdkI~
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(fileselection),Gfileselectiondir);//~vbdkI~
	rc=gtk_dialog_run(GTK_DIALOG(fileselection));                  //~vbdkI~
    if (rc==GTK_RESPONSE_ACCEPT)                                   //~vbdkI~
        rc=0;                                                      //~vbdkI~
    else	//cancel                                               //~vbdmI~
//    if (rc==GTK_RESPONSE_CLOSE)                                  //~vbdmR~
//        rc=1;                                                    //~vbdmR~
//    else    //cancel                                               //~vbdkI~//~vbdmR~
    	rc=4;                                                      //~vbdkI~
    *Pprc=rc;                                                      //~vbdkI~
    return fileselection;                                          //~vbdkI~
}                                                                  //~vbdkI~
  #else                                                            //~vbdkI~
GtkWidget*
create_fileselection (void)
{
  GtkWidget *fileselection;
  GtkWidget *file_button_ok;
  GtkWidget *file_button_cancel;

  fileselection = gtk_file_selection_new (_("File Selection"));
  gtk_container_set_border_width (GTK_CONTAINER (fileselection), 10);
  gtk_window_set_modal (GTK_WINDOW (fileselection), TRUE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (fileselection), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (fileselection), GDK_WINDOW_TYPE_HINT_DIALOG);

  file_button_ok = GTK_FILE_SELECTION (fileselection)->ok_button;
  if (Gfileselectiondir && *Gfileselectiondir)                     //~vaf6I~
	  gtk_file_selection_set_filename(GTK_FILE_SELECTION(fileselection),Gfileselectiondir);//~vaf6R~
  gtk_widget_show (file_button_ok);
  GTK_WIDGET_SET_FLAGS (file_button_ok, GTK_CAN_DEFAULT);

  file_button_cancel = GTK_FILE_SELECTION (fileselection)->cancel_button;
  gtk_widget_show (file_button_cancel);
  GTK_WIDGET_SET_FLAGS (file_button_cancel, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) file_button_ok, "clicked",
                    G_CALLBACK (on_file_button_ok_clicked),
                    NULL);
  g_signal_connect ((gpointer) file_button_cancel, "clicked",
                    G_CALLBACK (on_file_button_cancel_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection, fileselection, "fileselection");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection, file_button_ok, "file_button_ok");
  GLADE_HOOKUP_OBJECT_NO_REF (fileselection, file_button_cancel, "file_button_cancel");

  return fileselection;
}
  #endif  //GTK_CHECK_VERSION(2,4,0)	//GtkFileChooser is available//~vbdkI~
#else	//OPTGTK3                                                  //~var8R~
//*******************************************************************//~var8R~
//action 1:open/2:new/3:saveas                                     //~var8R~
//rc:4:cancel,1:new                                                //~vbdmI~
//*******************************************************************//~var8R~
GtkWidget *                                                        //~var8R~
create_fileselection (GtkWidget *Pparent,int Pactionid,int *Pprc)  //~var8R~
{                                                                  //~var8R~
  GtkWidget *fileselection;                                        //~var8R~
//  GtkWidget *file_button_ok;                                     //~var8R~
//  GtkWidget *file_button_cancel;                                 //~var8R~
	GtkFileChooserAction action;	                               //~var8R~
	gchar *buttonid;                                               //~var8R~
	int rc;                                                        //~var8R~
    char *ptitle;                                                  //~vbdmI~
//***************************************                          //~var8R~
    if (Pactionid==1||Pactionid==2)//open/new                      //~var8R~
    {                                                              //~var8R~
 	  if (Pactionid==2) //New                                      //~vbdmI~
	   	action=GTK_FILE_CHOOSER_ACTION_SAVE;  //show textbox:name  //~vbdmI~
      else                                                         //~vbdmI~
    	action=GTK_FILE_CHOOSER_ACTION_OPEN;                       //~var8R~
        buttonid=GTK_STOCK_OPEN;                                   //~var8R~
    	if (Pactionid==1)                                          //~vbdmI~
	        ptitle="File Selection(OpenFile)";                     //~vbdmI~
        else                                                       //~vbdmI~
	        ptitle="File Selection(NewFile)";                      //~vbdmI~
    }                                                              //~var8R~
    else	//saveas                                               //~var8R~
    {                                                              //~var8R~
    	action=GTK_FILE_CHOOSER_ACTION_SAVE;                       //~var8R~
        buttonid=GTK_STOCK_SAVE_AS;                                //~var8R~
	    ptitle="File Selection(SaveAs)";                           //~vbdmI~
    }                                                              //~var8R~
//  fileselection = gtk_file_selection_new (_("File Selection"));  //~var8R~
//  gtk_container_set_border_width (GTK_CONTAINER (fileselection), 10);//~var8R~
// if (Pactionid==2) //New                                         //~vbdmR~
//  fileselection = gtk_file_chooser_dialog_new(ptitle,            //~vbdmR~
//                    GTK_WINDOW(Pparent),                         //~vbdmR~
//                    action,                                      //~vbdmR~
//#if GTK_CHECK_VERSION(3,10,0)                                    //~vbdmR~
//                    GTK3_MNEMONIC_CANCEL,GTK_RESPONSE_CANCEL,//button1//~vbdmR~
//#else                                                            //~vbdmR~
//                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,//button1//~vbdmR~
//#endif                                                           //~vbdmR~
//                    buttonid,GTK_RESPONSE_ACCEPT,   //button2    //~vbdmR~
//#if GTK_CHECK_VERSION(3,10,0)                                    //~vbdmR~
//                    GTK3_MNEMONIC_NEW,GTK_RESPONSE_CLOSE,//button3//~vbdmR~
//#else                                                            //~vbdmR~
//                    GTK_STOCK_NEW,GTK_RESPONSE_CLOSE,            //~vbdmR~
//#endif                                                           //~vbdmR~
//                    NULL);  //last                               //~vbdmR~
// else                                                            //~vbdmR~
//fileselection = gtk_file_chooser_dialog_new(_("File Selection"), //~var8R~//~vbdmR~
  fileselection = gtk_file_chooser_dialog_new(ptitle,              //~vbdmI~
  					GTK_WINDOW(Pparent),                           //~var8R~
                    action,                                        //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
                    GTK3_MNEMONIC_CANCEL,GTK_RESPONSE_CANCEL,//button1//~vb7tR~
#else                                                              //~vb7tI~
                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,//button1 //~var8R~
#endif                                                             //~vb7tI~
                    buttonid,GTK_RESPONSE_ACCEPT,	//button2      //~var8R~
                    NULL);	//last                                 //~var8R~
 	if (Pactionid==2) //New                                        //~vbdmI~
    	gtk_file_chooser_set_current_name((GtkFileChooser*)fileselection,"NewFile"); //fill default name//~vbdmI~
  gtk_window_set_modal (GTK_WINDOW (fileselection), TRUE);         //~var8R~
  gtk_window_set_destroy_with_parent (GTK_WINDOW (fileselection), TRUE);//~var8R~
  gtk_window_set_type_hint (GTK_WINDOW (fileselection), GDK_WINDOW_TYPE_HINT_DIALOG);//~var8R~
//  file_button_ok = GTK_FILE_SELECTION (fileselection)->ok_button;//~var8R~
  if (Gfileselectiondir && *Gfileselectiondir)                     //+vaf6I~//~var8R~
//      gtk_file_selection_set_filename(GTK_FILE_SELECTION(fileselection),Gfileselectiondir);//+vaf6R~//~var8R~
      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(fileselection),Gfileselectiondir);//+vaf6R~//~var8R~
//  gtk_widget_show (file_button_ok);                              //~var8R~
//  GTK_WIDGET_SET_FLAGS (file_button_ok, GTK_CAN_DEFAULT);        //~var8R~
//  return fileselection;                                          //~var8R~
	rc=gtk_dialog_run(GTK_DIALOG(fileselection));                  //~var8R~
    if (rc==GTK_RESPONSE_ACCEPT)                                   //~var8R~
        rc=0;                                                      //~var8R~
    else	//cancel                                               //~var8R~
//    if (rc==GTK_RESPONSE_CLOSE)                                  //~vbdmR~
//        rc=1;                                                    //~vbdmR~
//    else    //cancel                                             //~vbdmR~
    	rc=4;                                                      //~var8R~
    *Pprc=rc;    	                                               //~var8R~
    return fileselection;                                          //~var8R~
}                                                                  //~var8R~
#endif //OPTGTK3                                                   //~var8R~

//*****************************************************************//~var8R~
//*color selection dialog                                          //~var8R~
//*****************************************************************//~var8R~
#ifndef OPTGTK3                                                    //+var8~//~var8R~
GtkWidget*
create_colorselectiondialog (void)
{
  GtkWidget *colorselectiondialog;
  GtkWidget *color_button_ok;
  GtkWidget *color_button_cancel;
  GtkWidget *help_button1;
  GtkWidget *color_selection1;

  colorselectiondialog = gtk_color_selection_dialog_new (_("Color Selection"));
  gtk_window_set_modal (GTK_WINDOW (colorselectiondialog), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (colorselectiondialog), FALSE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (colorselectiondialog), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (colorselectiondialog), GDK_WINDOW_TYPE_HINT_DIALOG);

//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  color_button_ok = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog)->ok_button;
//#else                                                            //~var8R~
//  g_object_get(GTK_COLOR_SELECTION_DIALOG (colorselectiondialog),"ok_button",&color_button_ok);//~var8R~
//#endif                                                             //+var8I~//~var8R~
  gtk_widget_show (color_button_ok);
  GTK_WIDGET_SET_FLAGS (color_button_ok, GTK_CAN_DEFAULT);

//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  color_button_cancel = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog)->cancel_button;
//#else                                                            //~var8R~
//  g_object_get(GTK_COLOR_SELECTION_DIALOG (colorselectiondialog),"cancel_button",&color_button_cancel);//~var8R~
//#endif                                                             //+var8I~//~var8R~
  gtk_widget_show (color_button_cancel);
  GTK_WIDGET_SET_FLAGS (color_button_cancel, GTK_CAN_DEFAULT);

//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  help_button1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog)->help_button;
//#else                                                            //~var8R~
//  g_object_get(GTK_COLOR_SELECTION_DIALOG (colorselectiondialog),"help_button",&help_button1);//~var8R~
//#endif                                                             //+var8I~//~var8R~
  gtk_widget_show (help_button1);
  GTK_WIDGET_SET_FLAGS (help_button1, GTK_CAN_DEFAULT);

//#ifndef OPTGTK3                                                    //~var8I~//~var8R~
  color_selection1 = GTK_COLOR_SELECTION_DIALOG (colorselectiondialog)->colorsel;
//#else                                                            //~var8R~
//  color_selection1 = gtk_color_selection_dialog_get_color_selection(GTK_COLOR_SELECTION_DIALOG (colorselectiondialog));//~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (color_selection1);
  gtk_color_selection_set_has_opacity_control (GTK_COLOR_SELECTION (color_selection1), FALSE);

  g_signal_connect ((gpointer) color_button_ok, "clicked",
                    G_CALLBACK (on_color_button_ok_clicked),
                    NULL);
  g_signal_connect ((gpointer) color_button_cancel, "clicked",
                    G_CALLBACK (on_color_button_cancel_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog, colorselectiondialog, "colorselectiondialog");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog, color_button_ok, "color_button_ok");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog, color_button_cancel, "color_button_cancel");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog, help_button1, "help_button1");
  GLADE_HOOKUP_OBJECT_NO_REF (colorselectiondialog, color_selection1, "color_selection1");

  return colorselectiondialog;
}
#else   //OPTGTK3                                                  //~var8R~
////************************************************************************//~var8R~
//void response_colorselectiondialog(GtkDialog Pdialog,gint Prespid,gpointer Ppdata)//~var8R~
//{                                                                //~var8R~
////******************************                                 //~var8R~
//    if (Prespid==GTK_RESPONSE_OK)                                //~var8R~
//    {                                                            //~var8R~
//        gxedlg_Color_OnOK(NULL/*button*/,NULL/*user_data*/);     //~var8R~
//    }                                                            //~var8R~
//    else                                                         //~var8R~
//    {                                                            //~var8R~
//        gxedlg_Color_OnCancel(NULL/*button*/,NULL/*user_data*/); //~var8R~
//    }                                                            //~var8R~
//}//response_colorselectiondialog                                 //~var8R~
//************************************************************************//~var8R~
GtkWidget*                                                         //~var8R~
create_colorselectiondialog (GtkWidget *Pparent)                   //~var8R~
{                                                                  //~var8R~
  	GtkWidget *colorselectiondialog;                               //~var8R~
//*******************************                                  //~var8R~
	colorselectiondialog = gtk_color_chooser_dialog_new (_("Color Selection"),GTK_WINDOW(Pparent));//~var8R~
//    g_signal_connect(colorselectiondialog,"response",G_CALLBACK(response_colorselectiondialog),NULL);//~var8R~
//    gtk_widget_show_all(colorselectiondialog);                   //~var8R~
	return colorselectiondialog;                                   //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
//************************************************************************//~var8R~
GtkWidget*
create_fontselectiondialog (void)
{
  GtkWidget *fontselectiondialog;
  GtkWidget *font_button_ok;
  GtkWidget *font_button_cancel;
//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  GtkWidget *font_button_apply;
//#else                                                            //~var8R~
//#endif                                                           //~var8R~
  GtkWidget *font_selection1;

  fontselectiondialog = gtk_font_selection_dialog_new (_("Font Selection"));
  gtk_container_set_border_width (GTK_CONTAINER (fontselectiondialog), 4);
  gtk_window_set_modal (GTK_WINDOW (fontselectiondialog), TRUE);
  gtk_window_set_destroy_with_parent (GTK_WINDOW (fontselectiondialog), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (fontselectiondialog), GDK_WINDOW_TYPE_HINT_DIALOG);

//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  font_button_ok = GTK_FONT_SELECTION_DIALOG (fontselectiondialog)->ok_button;
//#else                                                            //~var8R~
//  font_button_ok = gtk_font_selection_dialog_get_ok_button(GTK_FONT_SELECTION_DIALOG (fontselectiondialog));//~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (font_button_ok);
  GTK_WIDGET_SET_FLAGS (font_button_ok, GTK_CAN_DEFAULT);

//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  font_button_cancel = GTK_FONT_SELECTION_DIALOG (fontselectiondialog)->cancel_button;
//#else                                                            //~var8R~
//  font_button_cancel = gtk_font_selection_dialog_get_cancel_button(GTK_FONT_SELECTION_DIALOG (fontselectiondialog));//~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (font_button_cancel);
  GTK_WIDGET_SET_FLAGS (font_button_cancel, GTK_CAN_DEFAULT);

//#ifndef OPTGTK3                                                  //~var8R~
  font_button_apply = GTK_FONT_SELECTION_DIALOG (fontselectiondialog)->apply_button;
  gtk_widget_show (font_button_apply);
  GTK_WIDGET_SET_FLAGS (font_button_apply, GTK_CAN_DEFAULT);
//#else                                                            //~var8R~
//font_button_apply = gtk_font_selection_dialog_get_apply_button(GTK_FONT_SELECTION_DIALOG (fontselectiondialog));//~var8R~
//#endif                                                             //+var8I~//~var8R~

//#ifndef OPTGTK3                                                  //~var8R~
  font_selection1 = GTK_FONT_SELECTION_DIALOG (fontselectiondialog)->fontsel;
//#else                                                            //~var8R~
//  font_selection1 = gtk_font_selection_dialog_get_font_selection(GTK_FONT_SELECTION_DIALOG (fontselectiondialog));//~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (font_selection1);
  gtk_container_set_border_width (GTK_CONTAINER (font_selection1), 4);

  g_signal_connect ((gpointer) font_button_ok, "clicked",
                    G_CALLBACK (on_font_button_ok_clicked),
                    NULL);
  g_signal_connect ((gpointer) font_button_cancel, "clicked",
                    G_CALLBACK (on_font_button_cancel_clicked),
                    NULL);
//#ifndef OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) font_button_apply, "clicked",
                    G_CALLBACK (on_font_button_apply_clicked),
                    NULL);
//#else   //deplicated gtk_font_selection_get_apply_button         //~var8R~
//#endif                                                           //~var8R~

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (fontselectiondialog, fontselectiondialog, "fontselectiondialog");
  GLADE_HOOKUP_OBJECT_NO_REF (fontselectiondialog, font_button_ok, "font_button_ok");
  GLADE_HOOKUP_OBJECT_NO_REF (fontselectiondialog, font_button_cancel, "font_button_cancel");
//#ifndef OPTGTK3                                                  //~var8R~
  GLADE_HOOKUP_OBJECT_NO_REF (fontselectiondialog, font_button_apply, "font_button_apply");
//#else   //deplicated gtk_font_selection_get_apply_button         //~var8R~
//#endif                                                           //~var8R~
  GLADE_HOOKUP_OBJECT_NO_REF (fontselectiondialog, font_selection1, "font_selection1");

  return fontselectiondialog;
}
#else   //OPTGTK3                                                  //~var8R~
////************************************************************************//~var8R~
//void response_fontselectiondialog(GtkDialog Pdialog,gint Prespid,gpointer Ppdata)//~var8R~
//{                                                                //~var8R~
////******************************                                 //~var8R~
//    dprintf("response_fontselectiondialog responseid=%d\n",Prespid);//~var8R~
//    if (Prespid==GTK_RESPONSE_OK)                                //~var8R~
//    {                                                            //~var8R~
//        gxedlg_Font_OnOK(NULL/*button*/,NULL/*user_data*/);      //~var8R~
//    }                                                            //~var8R~
//    else                                                         //~var8R~
//    {                                                            //~var8R~
//        gxedlg_Font_OnCancel(NULL/*button*/,NULL/*user_data*/);  //~var8R~
//    }                                                            //~var8R~
//}//response_fontselectiondialog                                  //~var8R~
//************************************************************************//~var8R~
GtkWidget* create_fontselectiondialog (GtkWidget *Ppparent)        //~var8R~
{                                                                  //~var8R~
  	GtkWidget *fontselectiondialog;                                //~var8R~
//********************************                                 //~var8R~
  	fontselectiondialog = gtk_font_chooser_dialog_new (_("Font Selection"),GTK_WINDOW(Ppparent));//~var8R~
//  g_signal_connect(fontselectiondialog,"response",G_CALLBACK(response_fontselectiondialog)*/,NULL);//~var8R~
//  gtk_widget_show_all(fontselectiondialog); //do run             //~var8R~
	return fontselectiondialog;                                    //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~

GtkWidget*
create_aboutdlg (void)
{
  GtkWidget *aboutdlg;
  GtkWidget *dialog_vbox1;
  GtkWidget *vbox1;
  GtkWidget *image743;
  GtkWidget *about_label;
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GtkWidget *dialog_action_area1;
#endif                                                             //+var8~//~vb7tI~
  GtkWidget *about_button_close;

  aboutdlg = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (aboutdlg), _("About gxe"));
  gtk_window_set_modal (GTK_WINDOW (aboutdlg), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (aboutdlg), GDK_WINDOW_TYPE_HINT_DIALOG);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_vbox1 = GTK_DIALOG (aboutdlg)->vbox;
#else                                                              //+var8~//~var8R~
  dialog_vbox1 = gtk_dialog_get_content_area(GTK_DIALOG (aboutdlg));//~var8R~
#endif                                                             //+var8~//~var8R~
  gtk_widget_show (dialog_vbox1);

  vbox1 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox1);
  gtk_box_pack_start (GTK_BOX (dialog_vbox1), vbox1, TRUE, TRUE, 0);

  image743 = create_pixmap (aboutdlg, "gxe/wxe.png");
  gtk_widget_show (image743);
  gtk_box_pack_start (GTK_BOX (vbox1), image743, TRUE, TRUE, 0);

  about_label = gtk_label_new (_("label2"));
  gtk_widget_show (about_label);
  gtk_box_pack_start (GTK_BOX (vbox1), about_label, FALSE, FALSE, 0);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_action_area1 = GTK_DIALOG (aboutdlg)->action_area;
#else                                                              //+var8~//~var8R~
 #if GTK_CHECK_VERSION(3,12,0)                                     //~vb7tI~
 #else                                                             //~vb7tI~
  dialog_action_area1 = gtk_dialog_get_action_area(GTK_DIALOG (aboutdlg));//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //+var8~//~var8R~
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  gtk_widget_show (dialog_action_area1);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area1), GTK_BUTTONBOX_END);
#endif                                                             //~vb7tI~

#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
  about_button_close = gtk_button_new_with_mnemonic (GTK3_MNEMONIC_CLOSE);//~vb7tR~
#else                                                              //~vb7tI~
  about_button_close = gtk_button_new_from_stock ("gtk-close");
#endif                                                             //~vb7tI~
  gtk_widget_show (about_button_close);
  gtk_dialog_add_action_widget (GTK_DIALOG (aboutdlg), about_button_close, GTK_RESPONSE_CLOSE);
  GTK_WIDGET_SET_FLAGS (about_button_close, GTK_CAN_DEFAULT);

  g_signal_connect ((gpointer) about_button_close, "clicked",
                    G_CALLBACK (on_about_button_close_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (aboutdlg, aboutdlg, "aboutdlg");
  GLADE_HOOKUP_OBJECT_NO_REF (aboutdlg, dialog_vbox1, "dialog_vbox1");
  GLADE_HOOKUP_OBJECT (aboutdlg, vbox1, "vbox1");
  GLADE_HOOKUP_OBJECT (aboutdlg, image743, "image743");
  GLADE_HOOKUP_OBJECT (aboutdlg, about_label, "about_label");
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT_NO_REF (aboutdlg, dialog_action_area1, "dialog_action_area1");
#endif                                                             //~vb7tI~
  GLADE_HOOKUP_OBJECT (aboutdlg, about_button_close, "about_button_close");

  return aboutdlg;
}
#ifdef OPTGTK3TEST                                                 //~var8R~
void geomhint(GtkWidget *main,GtkWidget *comp,int w,int h)         //~var8R~
{                                                                  //~var8R~
	GdkGeometry geom={0};                                          //~var8R~
    geom.max_width=w; geom.max_height=h;                           //~var8R~
	GdkWindowHints hintsmask=GDK_HINT_MAX_SIZE;                    //~var8R~
    gtk_window_set_geometry_hints(GTK_WINDOW(main),comp,&geom,hintsmask);//~var8R~
    dprintf("geomhit w=%d,h=%d\n",w,h);                            //~var8R~
}                                                                  //~var8R~
void geomhint2(GtkWidget *main,GtkWidget *comp,int w,int h)        //~var8R~
{                                                                  //~var8R~
	GdkGeometry geom={0};                                          //~var8R~
    double aspect=0.5;                                             //~var8R~
    geom.max_width=w; geom.max_height=h;                           //~var8R~
    geom.min_aspect=aspect; geom.max_aspect=aspect;                //~var8R~
	GdkWindowHints hintsmask=GDK_HINT_MAX_SIZE|GDK_HINT_ASPECT;    //~var8R~
    gtk_window_set_geometry_hints(GTK_WINDOW(main),comp,&geom,hintsmask);//~var8R~
    dprintf("geomhit2 main=%p,comp=%p,w=%d,h=%d,aspet=%f\n",main,comp,w,h,aspect);//~var8R~
}                                                                  //~var8R~
void on_optiondlg_realize                 (GtkWidget       *widget,//~var8R~
                                        gpointer         user_data)//~var8R~
{                                                                  //~var8R~
void csub_get_widget_allocation_wh(GtkWidget *Ppwidget,int *Ppww,int *Pphh);//~var8R~
	int ww,hh;                                                     //~var8R~
	csub_get_widget_allocation_wh(widget,&ww,&hh);                 //~var8R~
	dprintf("on_optiondlg_realize widget=%p,ww=%d,hh=%d\n",widget,ww,hh);//~var8R~
  	gtk_window_set_default_size(GTK_WINDOW(widget),100,200);  //shrink avail//~var8R~
//  geomhint2(widget,widget,100,200);                              //~var8R~
    return;                                                        //~var8R~
}                                                                  //~var8R~
gboolean on_optiondlg_configure_event     (GtkWidget       *widget,//~var8R~
                                        gpointer         user_data)//~var8R~
{                                                                  //~var8R~
void csub_get_widget_allocation_wh(GtkWidget *Ppwidget,int *Ppww,int *Pphh);//~var8R~
	int ww,hh;                                                     //~var8R~
	csub_get_widget_allocation_wh(widget,&ww,&hh);                 //~var8R~
	dprintf("on_optiondlg_configure_event ww=%d,hh=%d\n",ww,hh);   //~var8R~
    return FALSE;                                                  //~var8R~
}                                                                  //~var8R~
void on_option_drawingarea_colorsample_realize (GtkWidget       *widget,//~var8R~
                                        gpointer         user_data)//~var8R~
{                                                                  //~var8R~
	int ww,hh;                                                     //~var8R~
void csub_get_widget_allocation_wh(GtkWidget *Ppwidget,int *Ppww,int *Pphh);//~var8R~
	csub_get_widget_allocation_wh(widget,&ww,&hh);                 //~var8R~
	dprintf("on_color_sample_realize ww=%d,hh=%d\n",ww,hh);        //~var8R~
    return;                                                        //~var8R~
}                                                                  //~var8R~
#endif  //PPP                                                      //~var8R~

GtkWidget*
create_optiondlg (void)
{
  GtkWidget *optiondlg;
  GtkWidget *dialog_vbox2;
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GtkWidget *alignment2;
#endif                                                             //~vb7tI~
  GtkWidget *vbox2;
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GtkWidget *alignment1;
#endif                                                             //~vb7tI~
  GtkWidget *eventbox1;
  GtkWidget *option_frame_label;
  GtkWidget *vbox19;
  GtkWidget *option_entry_current_font;
  GtkWidget *hbox46;
  GtkWidget *button1;
  GtkWidget *hbox47;
  GtkWidget *option_label_fonth;
  GtkWidget *option_entry_fonth;
  GtkWidget *option_label_fontw;
  GtkWidget *option_entry_fontw;
  GtkWidget *vbox20;
  GtkWidget *hseparator4;
  GtkWidget *hbox43;
  GtkWidget *option_label_cellh;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *option_spinbutton_rowh_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *option_spinbutton_rowh_adj;                       //~var8R~
#endif                                                             //~var8R~
  GtkWidget *option_spinbutton_rowh;
  GtkWidget *label56;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *option_spinbutton_colw_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *option_spinbutton_colw_adj;                       //~var8R~
#endif                                                             //~var8R~
  GtkWidget *option_spinbutton_colw;
  GtkWidget *option_chkbutton_ligature;
  GtkWidget *option_label_font;
  GtkWidget *option_frame_color;
  GtkWidget *hbox45;
  GtkWidget *option_drawingarea_colorsample;
  GtkWidget *hbox52;
  GtkWidget *option_button_color_change;
  GtkWidget *on_button_ruler_color_change;
  GtkWidget *option_label_color;
  GtkWidget *hbox44;
  GtkWidget *option_label_scrollctr;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *option_spinbutton_scrollctr_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *option_spinbutton_scrollctr_adj;                  //~var8R~
#endif                                                             //~var8R~
  GtkWidget *option_spinbutton_scrollctr;
  GtkWidget *option_label_interval;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *option_spinbutton_interval_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *option_spinbutton_interval_adj;                   //~var8R~
#endif                                                             //~var8R~
  GtkWidget *option_spinbutton_interval;
  GtkWidget *option_label_hsec;
  GtkWidget *hbox53;
  GtkWidget *label67;
  GtkWidget *label69;
  GtkWidget *option_entry_rulerkey;
  GtkWidget *label68;
  GtkWidget *table1;
  GtkWidget *option_chkbutton_acc;
  GtkWidget *option_chkbutton_menu;
  GtkWidget *option_chkbutton_Rctl;
  GtkWidget *option_chkbutton_freecsr;
  GtkWidget *option_chkbox_beep;
  GtkWidget *label66;
  GtkWidget *option_chkbox_qexit;
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GtkWidget *dialog_action_area2;
#endif                                                             //~vb7tI~
  GtkWidget *option_button_cancel;
  GtkWidget *option_button_ok;
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  optiondlg = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (optiondlg), _("Setup Options"));
  gtk_window_set_modal (GTK_WINDOW (optiondlg), TRUE);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_window_set_resizable (GTK_WINDOW (optiondlg), FALSE);
#else   //OPTGTK3                                                  //~var8R~
  gtk_window_set_resizable (GTK_WINDOW (optiondlg), TRUE);         //~var8R~
#endif                                                             //~var8R~
  gtk_window_set_destroy_with_parent (GTK_WINDOW (optiondlg), TRUE);
  gtk_window_set_type_hint (GTK_WINDOW (optiondlg), GDK_WINDOW_TYPE_HINT_DIALOG);
                                                                   //~var8R~
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
	{                                                              //~var8R~
//  gtk_window_set_default_size(GTK_WINDOW(optiondlg),100,100);    //~var8R~
	GdkGeometry geom={0/*minw*/,0/*minh*/,50/*maxw*/,100/*maxh*/}; //~var8R~
	GdkWindowHints hintsmask=GDK_HINT_MAX_SIZE;                    //~var8R~
    gtk_window_set_geometry_hints(GTK_WINDOW(optiondlg),optiondlg,&geom,hintsmask);//~var8R~
    }                                                              //~var8R~
#endif                                                             //~var8R~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_vbox2 = GTK_DIALOG (optiondlg)->vbox;
#else                                                              //+var8~//~var8R~
  dialog_vbox2 = gtk_dialog_get_content_area(GTK_DIALOG (optiondlg));//~var8R~
#endif                                                             //+var8~//~var8R~
  gtk_widget_show (dialog_vbox2);

#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
//alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);                 //~vb7tI~
//gtk_widget_show (alignment2);                                    //~vb7tI~
//gtk_box_pack_start (GTK_BOX (dialog_vbox2), alignment2, TRUE, TRUE, 0);//~vb7tI~
                                                                   //~vb7tI~
  vbox2 = gtk_vbox_new (FALSE, 0);                                 //~vb7tI~
  gtk_widget_show (vbox2);                                         //~vb7tI~
//gtk_container_add (GTK_CONTAINER (alignment2), vbox2);           //~vb7tI~
  gtk_widget_set_valign(vbox2,GTK_ALIGN_CENTER);                   //~vb7tI~
  gtk_widget_set_halign(vbox2,GTK_ALIGN_CENTER);                   //~vb7tI~
  gtk_box_pack_start (GTK_BOX (dialog_vbox2), vbox2, TRUE/*expand*/, TRUE/*fill space*/, 0);//~vb7tI~
#else                                                              //~vb7tI~
//#ifndef OPTGTK3                                                    //+var8~//~var8R~
  alignment2 = gtk_alignment_new (0.5, 0.5, 1, 1);
//#else   //OPTGTK3                                                //~var8R~
//  alignment2 = gtk_alignment_new (0.5, 0.5, 0, 0);               //~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (alignment2);
  gtk_box_pack_start (GTK_BOX (dialog_vbox2), alignment2, TRUE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox2);
  gtk_container_add (GTK_CONTAINER (alignment2), vbox2);
#endif                                                             //~vb7tR~
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
//alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);                 //~vb7tI~
//gtk_widget_show (alignment1);                                    //~vb7tI~
//gtk_box_pack_start (GTK_BOX (vbox2), alignment1, TRUE, TRUE, 0); //~vb7tI~
                                                                   //~vb7tI~
  eventbox1 = gtk_event_box_new ();                                //~vb7tI~
  gtk_widget_show (eventbox1);                                     //~vb7tI~
//gtk_container_add (GTK_CONTAINER (alignment1), eventbox1);       //~vb7tI~
  gtk_widget_set_valign(eventbox1,GTK_ALIGN_CENTER);               //~vb7tI~
  gtk_widget_set_halign(eventbox1,GTK_ALIGN_CENTER);               //~vb7tI~
  gtk_box_pack_start (GTK_BOX (vbox2), eventbox1, TRUE/*expand*/, TRUE/*fill space*/, 0);//~vb7tI~
#else                                                              //~vb7tI~
//#ifndef OPTGTK3                                                    //+var8~//~var8R~
  alignment1 = gtk_alignment_new (0.5, 0.5, 1, 1);
//#else   //OPTGTK3                                                //~var8R~
//  alignment1 = gtk_alignment_new (0.5, 0.5, 0, 0);               //~var8R~
//#endif                                                           //~var8R~
  gtk_widget_show (alignment1);
  gtk_box_pack_start (GTK_BOX (vbox2), alignment1, TRUE, TRUE, 0);

  eventbox1 = gtk_event_box_new ();
  gtk_widget_show (eventbox1);
  gtk_container_add (GTK_CONTAINER (alignment1), eventbox1);
#endif                                                             //~vb7tI~

  option_frame_label = gtk_frame_new (NULL);
  gtk_widget_show (option_frame_label);
  gtk_container_add (GTK_CONTAINER (eventbox1), option_frame_label);
  gtk_container_set_border_width (GTK_CONTAINER (option_frame_label), 2);

  vbox19 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox19);
  gtk_container_add (GTK_CONTAINER (option_frame_label), vbox19);

  option_entry_current_font = gtk_entry_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
//    gtk_entry_set_width_chars(GTK_ENTRY(option_entry_current_font),2);//~var8R~
//  geomhint(optiondlg,option_entry_current_font,10,5);            //~var8R~
//  gtk_entry_set_max_length(GTK_ENTRY(option_entry_current_font),5);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (option_entry_current_font);
  gtk_box_pack_start (GTK_BOX (vbox19), option_entry_current_font, FALSE, FALSE, 0);
  gtk_tooltips_set_tip (tooltips, option_entry_current_font, _("Current Font Style"), NULL);
  gtk_editable_set_editable (GTK_EDITABLE (option_entry_current_font), FALSE);

  hbox46 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox46);
//#ifdef AAA                                                       //~var8R~
  gtk_box_pack_start (GTK_BOX (vbox19), hbox46, TRUE, TRUE, 0);
//#endif                                                           //~var8R~

  button1 = gtk_button_new_with_mnemonic (_("Font Change"));
  gtk_widget_show (button1);
  gtk_box_pack_start (GTK_BOX (hbox46), button1, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (button1), 2);
  gtk_tooltips_set_tip (tooltips, button1, _("push to change Font Style"), NULL);

  hbox47 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox47);
  gtk_box_pack_start (GTK_BOX (hbox46), hbox47, TRUE, TRUE, 0);

  option_label_fonth = gtk_label_new (_(" Font-H "));
  gtk_widget_show (option_label_fonth);
  gtk_box_pack_start (GTK_BOX (hbox47), option_label_fonth, FALSE, FALSE, 0);

  option_entry_fonth = gtk_entry_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
    gtk_entry_set_width_chars(GTK_ENTRY(option_entry_fonth),3);    //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (option_entry_fonth);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_box_pack_start (GTK_BOX (hbox47), option_entry_fonth, TRUE, TRUE, 0);
#else   //OPTGTK3                                                  //~var8R~
  gtk_box_pack_start (GTK_BOX (hbox47), option_entry_fonth,FALSE,FALSE, 0);//~var8R~
#endif                                                             //~var8R~
//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  gtk_widget_set_size_request (option_entry_fonth, 20, -1);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,option_entry_fonth,10,5);                   //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, option_entry_fonth, _("Average Height of the current Font "), NULL);
  gtk_entry_set_max_length (GTK_ENTRY (option_entry_fonth), 2);
  gtk_editable_set_editable (GTK_EDITABLE (option_entry_fonth), FALSE);
  gtk_entry_set_has_frame (GTK_ENTRY (option_entry_fonth), FALSE);

  option_label_fontw = gtk_label_new (_(" Font-W "));
  gtk_widget_show (option_label_fontw);
  gtk_box_pack_start (GTK_BOX (hbox47), option_label_fontw, FALSE, FALSE, 0);

  option_entry_fontw = gtk_entry_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
    gtk_entry_set_width_chars(GTK_ENTRY(option_entry_fontw),3);    //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (option_entry_fontw);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_box_pack_start (GTK_BOX (hbox47), option_entry_fontw, TRUE, TRUE, 0);
#else   //OPTGTK3                                                  //~var8R~
  gtk_box_pack_start (GTK_BOX (hbox47), option_entry_fontw, FALSE,FALSE, 0);//~var8R~
#endif                                                             //~var8R~
//#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  gtk_widget_set_size_request (option_entry_fontw, 20, -1);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,option_entry_fontw,10,5);                   //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, option_entry_fontw, _("Average Width of the current Font"), NULL);
  gtk_entry_set_max_length (GTK_ENTRY (option_entry_fontw), 2);
  gtk_editable_set_editable (GTK_EDITABLE (option_entry_fontw), FALSE);
  gtk_entry_set_has_frame (GTK_ENTRY (option_entry_fontw), FALSE);

  vbox20 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox20);
  gtk_box_pack_start (GTK_BOX (vbox19), vbox20, TRUE, TRUE, 0);

  hseparator4 = gtk_hseparator_new ();
  gtk_widget_show (hseparator4);
  gtk_box_pack_start (GTK_BOX (vbox20), hseparator4, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (hseparator4, -1, 3);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,hseparator4,50,1);                          //~var8R~
//#endif                                                           //~var8R~

  hbox43 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox43);
//#ifdef AAA                                                       //~var8R~
  gtk_box_pack_start (GTK_BOX (vbox20), hbox43, TRUE, TRUE, 0);
//#endif                                                           //~var8R~

  option_label_cellh = gtk_label_new (_("Row-H"));
  gtk_widget_show (option_label_cellh);
  gtk_box_pack_start (GTK_BOX (hbox43), option_label_cellh, FALSE, FALSE, 0);
//#fndef OPTGTK3                                                   //~var8R~
  gtk_widget_set_size_request (option_label_cellh, 50, -1);
//#else   //OPTGTK3                                                //~var8R~
//  geomhint(optiondlg,option_label_cellh,25,5);                   //~var8R~
//#endif                                                           //~var8R~

  option_spinbutton_rowh_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  option_spinbutton_rowh = gtk_spin_button_new (GTK_ADJUSTMENT (option_spinbutton_rowh_adj), 1, 0);
  gtk_widget_show (option_spinbutton_rowh);
  gtk_box_pack_start (GTK_BOX (hbox43), option_spinbutton_rowh, TRUE, TRUE, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (option_spinbutton_rowh, 50, -1);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(option_spinbutton_rowh),3);  //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, option_spinbutton_rowh, _("Row Height"), NULL);

  label56 = gtk_label_new (_(" Col-W"));
  gtk_widget_show (label56);
  gtk_box_pack_start (GTK_BOX (hbox43), label56, FALSE, FALSE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (label56, 50, -1);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,label56,25,5);                              //~var8R~
//#endif                                                           //~var8R~

  option_spinbutton_colw_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  option_spinbutton_colw = gtk_spin_button_new (GTK_ADJUSTMENT (option_spinbutton_colw_adj), 1, 0);
  gtk_widget_show (option_spinbutton_colw);
  gtk_box_pack_start (GTK_BOX (hbox43), option_spinbutton_colw, TRUE, TRUE, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (option_spinbutton_colw, 50, -1);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(option_spinbutton_colw),3);  //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, option_spinbutton_colw, _("Column Width"), NULL);

  option_chkbutton_ligature = gtk_check_button_new_with_mnemonic (_("Ligature"));
  gtk_widget_show (option_chkbutton_ligature);
  gtk_box_pack_start (GTK_BOX (hbox43), option_chkbutton_ligature, TRUE, TRUE, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbutton_ligature, _("accept Ligature if the font supports(combine to a glyph such as 'fi'), keep mono-spacing if chk-Off"), NULL);

  option_label_font = gtk_label_new (_("Font"));
  gtk_widget_show (option_label_font);
  gtk_frame_set_label_widget (GTK_FRAME (option_frame_label), option_label_font);

  option_frame_color = gtk_frame_new (NULL);
  gtk_widget_show (option_frame_color);
  gtk_box_pack_start (GTK_BOX (vbox2), option_frame_color, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (option_frame_color), 2);

  hbox45 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox45);
  gtk_container_add (GTK_CONTAINER (option_frame_color), hbox45);

  option_drawingarea_colorsample = gtk_drawing_area_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
//	dprintf("create_optiondlg sample widget=%p\n",option_drawingarea_colorsample);//~var8R~
//    gtk_widget_set_size_request (option_drawingarea_colorsample, 40, 10);//~var8R~
//	geomhint(optiondlg,option_drawingarea_colorsample,10,2);       //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (option_drawingarea_colorsample);
//#ifdef AAA                                                       //~var8R~
  gtk_box_pack_start (GTK_BOX (hbox45), option_drawingarea_colorsample, TRUE, TRUE, 0);
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, option_drawingarea_colorsample, _("Sample Display Window"), NULL);

  hbox52 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox52);
  gtk_box_pack_start (GTK_BOX (hbox45), hbox52, FALSE, FALSE, 0);

  option_button_color_change = gtk_button_new_with_mnemonic (_("BGC"));
  gtk_widget_show (option_button_color_change);
  gtk_box_pack_start (GTK_BOX (hbox52), option_button_color_change, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (option_button_color_change), 2);
  gtk_tooltips_set_tip (tooltips, option_button_color_change, _("Change Background Color"), NULL);

  on_button_ruler_color_change = gtk_button_new_with_mnemonic (_("Ruler"));
  gtk_widget_show (on_button_ruler_color_change);
  gtk_box_pack_start (GTK_BOX (hbox52), on_button_ruler_color_change, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (on_button_ruler_color_change), 2);
  gtk_tooltips_set_tip (tooltips, on_button_ruler_color_change, _("Change Crosshair Cursor Color(toggle key:S+C+F1,F2,F3)"), NULL);

  option_label_color = gtk_label_new (_("BackGroundColor"));
  gtk_widget_show (option_label_color);
  gtk_frame_set_label_widget (GTK_FRAME (option_frame_color), option_label_color);

  hbox44 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox44);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_box_pack_start (GTK_BOX (vbox2), hbox44, TRUE, TRUE, 0);
#else   //OPTGTK3                                                  //~var8R~
#endif                                                             //~var8R~

  option_label_scrollctr = gtk_label_new (_(" Scroll ctr"));
  gtk_widget_show (option_label_scrollctr);
  gtk_box_pack_start (GTK_BOX (hbox44), option_label_scrollctr, FALSE, FALSE, 0);

  option_spinbutton_scrollctr_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  option_spinbutton_scrollctr = gtk_spin_button_new (GTK_ADJUSTMENT (option_spinbutton_scrollctr_adj), 1, 0);
  gtk_widget_show (option_spinbutton_scrollctr);
  gtk_box_pack_start (GTK_BOX (hbox44), option_spinbutton_scrollctr, TRUE, TRUE, 0);
  gtk_tooltips_set_tip (tooltips, option_spinbutton_scrollctr, _("Scroll Line Count for each MouseWheel "), NULL);

  option_label_interval = gtk_label_new (_("  Interval"));
  gtk_widget_show (option_label_interval);
  gtk_box_pack_start (GTK_BOX (hbox44), option_label_interval, FALSE, FALSE, 0);

  option_spinbutton_interval_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  option_spinbutton_interval = gtk_spin_button_new (GTK_ADJUSTMENT (option_spinbutton_interval_adj), 1, 0);
  gtk_widget_show (option_spinbutton_interval);
  gtk_box_pack_start (GTK_BOX (hbox44), option_spinbutton_interval, TRUE, TRUE, 0);
  gtk_tooltips_set_tip (tooltips, option_spinbutton_interval, _("Scroll in each Intervaltime when continue to push L-Button at the edge of screen"), NULL);

  option_label_hsec = gtk_label_new (_("0.1sec"));
  gtk_widget_show (option_label_hsec);
  gtk_box_pack_start (GTK_BOX (hbox44), option_label_hsec, FALSE, FALSE, 0);

  hbox53 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox53);
//#ifdef AAA                                                       //~var8R~
  gtk_box_pack_start (GTK_BOX (vbox2), hbox53, TRUE, TRUE, 0);
//#endif                                                           //~var8R~

  label67 = gtk_label_new ("");
  gtk_widget_show (label67);
  gtk_box_pack_start (GTK_BOX (hbox53), label67, FALSE, FALSE, 0);

  label69 = gtk_label_new (_("Ruler:S+C+"));
  gtk_widget_show (label69);
  gtk_box_pack_start (GTK_BOX (hbox53), label69, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (label69, 30, -1);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,label69,10,2);                              //~var8R~
//#endif                                                           //~var8R~

  option_entry_rulerkey = gtk_entry_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
//    gtk_entry_set_width_chars(GTK_ENTRY(option_entry_rulerkey),8);//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (option_entry_rulerkey);
  gtk_box_pack_start (GTK_BOX (hbox53), option_entry_rulerkey, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (option_entry_rulerkey, 40, -1);
//#else   //OPTGTK3                                                //~var8R~
//	geomhint(optiondlg,option_entry_rulerkey,10,2);                //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, option_entry_rulerkey, _("Upper letter for 3 ruler trigger keys with Shift-Control-. ex).\"!\" for key-1,\"Q\" for key-q,\"F1\" for key-F1. \"F10,\" for key-F10"), NULL);
  gtk_entry_set_max_length (GTK_ENTRY (option_entry_rulerkey), 12);

  label68 = gtk_label_new (_("                 "));
  gtk_widget_show (label68);
  gtk_box_pack_start (GTK_BOX (hbox53), label68, FALSE, FALSE, 0);

  table1 = gtk_table_new (4, 2, FALSE);
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
  gtk_grid_set_row_homogeneous(GTK_GRID(table1),TRUE);	//all rows are same height//~var8R~
//  gtk_grid_set_column_homogeneous(GTK_GRID(table1),TRUE);   //all rows are same height//~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (table1);
  gtk_box_pack_start (GTK_BOX (vbox2), table1, TRUE, TRUE, 0);

  option_chkbutton_acc = gtk_check_button_new_with_mnemonic (_("Accelerator"));
  gtk_widget_show (option_chkbutton_acc);
  gtk_table_attach (GTK_TABLE (table1), option_chkbutton_acc, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbutton_acc, _("Use Shortcut key(Ctl+x) for Menuitem activation"), NULL);

  option_chkbutton_menu = gtk_check_button_new_with_mnemonic (_("Menu key"));
  gtk_widget_show (option_chkbutton_menu);
  gtk_table_attach (GTK_TABLE (table1), option_chkbutton_menu, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbutton_menu, _("Use Alt+x key to pulldown MenuItem"), NULL);

  option_chkbutton_Rctl = gtk_check_button_new_with_mnemonic (_("R-Ctrl"));
  gtk_widget_show (option_chkbutton_Rctl);
  gtk_table_attach (GTK_TABLE (table1), option_chkbutton_Rctl, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbutton_Rctl, _("Use Right-Control Key for \"Execute\" function"), NULL);

  option_chkbutton_freecsr = gtk_check_button_new_with_mnemonic (_("FreeCursor"));
  gtk_widget_show (option_chkbutton_freecsr);
  gtk_table_attach (GTK_TABLE (table1), option_chkbutton_freecsr, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbutton_freecsr, _("Wrap Cursor at the edge of screen"), NULL);

  option_chkbox_beep = gtk_check_button_new_with_mnemonic (_("Beep"));
  gtk_widget_show (option_chkbox_beep);
  gtk_table_attach (GTK_TABLE (table1), option_chkbox_beep, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbox_beep, _("sound Beep when error"), NULL);
//#ifndef OPTGTK3                                                    //+var8~//~var8R~
//#else   //OPTGTK3                                                //~var8R~
//  {                                                              //~var8R~
//  GtkWidget *label1223;                                          //~var8R~
//  label1223 = gtk_label_new (" ");                               //~var8R~
//  gtk_widget_show (label1223);                                   //~var8R~
//  gtk_table_attach (GTK_TABLE (table1), label1223, 1, 2, 2, 3,   //~var8R~
//                    (GtkAttachOptions) (GTK_FILL),               //~var8R~
//                    (GtkAttachOptions) (0), 0, 0);               //~var8R~
//  }                                                              //~var8R~
//#endif                                                           //~var8R~

  label66 = gtk_label_new (_("Use \"OPT\" cmd\nfor other options"));
  gtk_widget_show (label66);
  gtk_table_attach (GTK_TABLE (table1), label66, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(label66,GTK_ALIGN_CENTER);                 //~vb7tR~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (label66), 0, 0.5);
#endif                                                             //~vb7tI~

  option_chkbox_qexit = gtk_check_button_new_with_mnemonic (_("Q-exit"));
  gtk_widget_show (option_chkbox_qexit);
  gtk_table_attach (GTK_TABLE (table1), option_chkbox_qexit, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, option_chkbox_qexit, _("Quiet(without confirmation dialog) Exit"), NULL);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_action_area2 = GTK_DIALOG (optiondlg)->action_area;
#else                                                              //+var8~//~var8R~
 #if GTK_CHECK_VERSION(3,12,0)                                     //~vb7tI~
 #else                                                             //~vb7tI~
  dialog_action_area2 = gtk_dialog_get_action_area(GTK_DIALOG (optiondlg));//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //+var8~//~var8R~
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  gtk_widget_show (dialog_action_area2);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area2), GTK_BUTTONBOX_END);
#endif                                                             //+var8~//~vb7tI~

#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
  option_button_cancel = gtk_button_new_with_mnemonic (GTK3_MNEMONIC_CANCEL);//~vb7tR~
#else                                                              //~vb7tI~
  option_button_cancel = gtk_button_new_from_stock ("gtk-cancel");
#endif                                                             //~vb7tI~
  gtk_widget_show (option_button_cancel);
  gtk_dialog_add_action_widget (GTK_DIALOG (optiondlg), option_button_cancel, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (option_button_cancel, GTK_CAN_DEFAULT);

#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
  option_button_ok = gtk_button_new_with_mnemonic (GTK3_MNEMONIC_OK);//~vb7tR~
#else                                                              //~vb7tI~
  option_button_ok = gtk_button_new_from_stock ("gtk-ok");
#endif                                                             //~vb7tI~
  gtk_widget_show (option_button_ok);
  gtk_dialog_add_action_widget (GTK_DIALOG (optiondlg), option_button_ok, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (option_button_ok, GTK_CAN_DEFAULT);
#ifdef OPTGTK3TEST                                                 //~var8R~
  g_signal_connect ((gpointer) optiondlg, "realize",               //~var8R~
                    G_CALLBACK (on_optiondlg_realize),             //~var8R~
                    NULL);                                         //~var8R~
  g_signal_connect ((gpointer) optiondlg, "configure-event",       //~var8R~
                    G_CALLBACK (on_optiondlg_configure_event),     //~var8R~
                    NULL);                                         //~var8R~
  g_signal_connect ((gpointer) option_drawingarea_colorsample, "realize",//~var8R~
                    G_CALLBACK (on_option_drawingarea_colorsample_realize),//~var8R~
                    NULL);                                         //~var8R~
#endif //OPTGTK3TEST                                               //~var8R~
  g_signal_connect ((gpointer) button1, "clicked",
                    G_CALLBACK (on_option_button_change_font_clicked),
                    NULL);
  g_signal_connect ((gpointer) option_drawingarea_colorsample, "configure_event",
                    G_CALLBACK (on_option_drawingarea_colorsample_configure_event),
                    NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_signal_connect ((gpointer) option_drawingarea_colorsample, "expose_event",
                    G_CALLBACK (on_option_drawingarea_colorsample_expose_event),
                    NULL);
#else   //OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) option_drawingarea_colorsample, "draw",//~var8R~
                    G_CALLBACK (on_option_drawingarea_colorsample_draw),//~var8R~
                    NULL);                                         //~var8R~
#endif                                                             //~var8R~
  g_signal_connect ((gpointer) option_button_color_change, "clicked",
                    G_CALLBACK (on_option_button_color_change_clicked),
                    NULL);
  g_signal_connect ((gpointer) on_button_ruler_color_change, "clicked",
                    G_CALLBACK (on_option_button_rulercolor_change_clicked),
                    NULL);
  g_signal_connect ((gpointer) option_button_cancel, "clicked",
                    G_CALLBACK (on_option_button_cancel_clicked),
                    NULL);
  g_signal_connect ((gpointer) option_button_ok, "clicked",
                    G_CALLBACK (on_option_button_ok_clicked),
                    NULL);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (optiondlg, optiondlg, "optiondlg");
  GLADE_HOOKUP_OBJECT_NO_REF (optiondlg, dialog_vbox2, "dialog_vbox2");
#if GTK_CHECK_VERSION(3,10,0)
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT (optiondlg, alignment2, "alignment2");
#endif                                                             //~vb7tI~
  GLADE_HOOKUP_OBJECT (optiondlg, vbox2, "vbox2");
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT (optiondlg, alignment1, "alignment1");
#endif                                                             //~vb7tI~
  GLADE_HOOKUP_OBJECT (optiondlg, eventbox1, "eventbox1");
  GLADE_HOOKUP_OBJECT (optiondlg, option_frame_label, "option_frame_label");
  GLADE_HOOKUP_OBJECT (optiondlg, vbox19, "vbox19");
  GLADE_HOOKUP_OBJECT (optiondlg, option_entry_current_font, "option_entry_current_font");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox46, "hbox46");
  GLADE_HOOKUP_OBJECT (optiondlg, button1, "button1");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox47, "hbox47");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_fonth, "option_label_fonth");
  GLADE_HOOKUP_OBJECT (optiondlg, option_entry_fonth, "option_entry_fonth");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_fontw, "option_label_fontw");
  GLADE_HOOKUP_OBJECT (optiondlg, option_entry_fontw, "option_entry_fontw");
  GLADE_HOOKUP_OBJECT (optiondlg, vbox20, "vbox20");
  GLADE_HOOKUP_OBJECT (optiondlg, hseparator4, "hseparator4");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox43, "hbox43");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_cellh, "option_label_cellh");
  GLADE_HOOKUP_OBJECT (optiondlg, option_spinbutton_rowh, "option_spinbutton_rowh");
  GLADE_HOOKUP_OBJECT (optiondlg, label56, "label56");
  GLADE_HOOKUP_OBJECT (optiondlg, option_spinbutton_colw, "option_spinbutton_colw");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbutton_ligature, "option_chkbutton_ligature");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_font, "option_label_font");
  GLADE_HOOKUP_OBJECT (optiondlg, option_frame_color, "option_frame_color");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox45, "hbox45");
  GLADE_HOOKUP_OBJECT (optiondlg, option_drawingarea_colorsample, "option_drawingarea_colorsample");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox52, "hbox52");
  GLADE_HOOKUP_OBJECT (optiondlg, option_button_color_change, "option_button_color_change");
  GLADE_HOOKUP_OBJECT (optiondlg, on_button_ruler_color_change, "on_button_ruler_color_change");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_color, "option_label_color");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox44, "hbox44");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_scrollctr, "option_label_scrollctr");
  GLADE_HOOKUP_OBJECT (optiondlg, option_spinbutton_scrollctr, "option_spinbutton_scrollctr");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_interval, "option_label_interval");
  GLADE_HOOKUP_OBJECT (optiondlg, option_spinbutton_interval, "option_spinbutton_interval");
  GLADE_HOOKUP_OBJECT (optiondlg, option_label_hsec, "option_label_hsec");
  GLADE_HOOKUP_OBJECT (optiondlg, hbox53, "hbox53");
  GLADE_HOOKUP_OBJECT (optiondlg, label67, "label67");
  GLADE_HOOKUP_OBJECT (optiondlg, label69, "label69");
  GLADE_HOOKUP_OBJECT (optiondlg, option_entry_rulerkey, "option_entry_rulerkey");
  GLADE_HOOKUP_OBJECT (optiondlg, label68, "label68");
  GLADE_HOOKUP_OBJECT (optiondlg, table1, "table1");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbutton_acc, "option_chkbutton_acc");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbutton_menu, "option_chkbutton_menu");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbutton_Rctl, "option_chkbutton_Rctl");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbutton_freecsr, "option_chkbutton_freecsr");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbox_beep, "option_chkbox_beep");
  GLADE_HOOKUP_OBJECT (optiondlg, label66, "label66");
  GLADE_HOOKUP_OBJECT (optiondlg, option_chkbox_qexit, "option_chkbox_qexit");
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT_NO_REF (optiondlg, dialog_action_area2, "dialog_action_area2");
#endif                                                             //~vb7tI~
  GLADE_HOOKUP_OBJECT (optiondlg, option_button_cancel, "option_button_cancel");
  GLADE_HOOKUP_OBJECT (optiondlg, option_button_ok, "option_button_ok");
  GLADE_HOOKUP_OBJECT_NO_REF (optiondlg, tooltips, "tooltips");
//#ifndef OPTGTK3                                                  //~var8R~
//#else   //OPTGTK3                                                //~var8R~
//  gtk_dialog_set_default_response(GTK_DIALOG(optiondlg),GTK_RESPONSE_CANCEL);//~var8R~
//#endif                                                           //~var8R~

  return optiondlg;
}

GtkWidget*
create_printdlg (void)
{
  GtkWidget *printdlg;
  GtkWidget *dialog_vbox3;
  GtkWidget *hbox17;
  GtkWidget *vbox12;
  GtkWidget *frame12;
  GtkWidget *vbox16;
  GtkWidget *hbox51;
  GtkWidget *page_label_printer;
  GtkWidget *combo2;
  GtkWidget *page_combo_printer;
  GtkWidget *label65;
  GtkWidget *hbox34;
  GtkWidget *page_label_size;
  GtkWidget *combo1;
  GtkWidget *page_combo_form;
  GtkWidget *page_chkbutton_landscape;
  GtkWidget *frame13;
  GtkWidget *table8;
  GtkWidget *page_label_left;
  GtkWidget *page_label_top;
  GtkWidget *page_label_right;
  GtkWidget *page_label_bottom;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_top_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_top_adj;                                //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_top;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_right_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_right_adj;                              //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_right;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_bottom_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_bottom_adj;                             //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_bottom;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_left_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_left_adj;                               //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_left;
  GtkWidget *page_label_margin;
  GtkWidget *page_label_default_margin;
  GtkWidget *page_label_form;
  GtkWidget *frame14;
  GtkWidget *vbox17;
  GtkWidget *page_entry_current_font;
  GtkWidget *hbox48;
  GtkWidget *page_font_change;
  GtkWidget *page_label_fonth;
  GtkWidget *page_entry_fonth;
  GtkWidget *label59;
  GtkWidget *page_entry_fontw;
  GtkWidget *vbox18;
  GtkWidget *hbox36;
  GtkWidget *hseparator3;
  GtkWidget *page_chkbutton_bycellhw;
  GtkWidget *hbox37;
  GtkWidget *hbox41;
  GtkWidget *page_label_cellh;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spinbutton_cellh_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spinbutton_cellh_adj;                        //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spinbutton_cellh;
  GtkWidget *page_label_cellw;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spinbutton_cellw_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spinbutton_cellw_adj;                        //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spinbutton_cellw;
  GtkWidget *page_label_font;
  GtkWidget *vbox15;
  GtkWidget *hbox33;
  GtkWidget *page_label_col;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_col_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_col_adj;                                //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_col;
  GtkWidget *page_label_row;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spin_row_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spin_row_adj;                                //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spin_row;
  GtkWidget *hbox50;
  GtkWidget *label63;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spinbutton_cellhmax_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spinbutton_cellhmax_adj;                     //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spinbutton_cellhmax;
  GtkWidget *hseparator5;
  GtkWidget *table7;
  GtkWidget *page_chkbutton_lineno;
  GtkWidget *page_chkbutton_2p;
  GtkWidget *page_chkbutton_header;
  GtkWidget *page_chkbutton_filetime;
  GtkWidget *page_chkbutton_footer;
  GtkWidget *page_chkbutton_wwscrprt;
  GtkWidget *page_chkbutton_systime;
  GtkWidget *page_chkbutton_fullpage;
  GtkWidget *page_chkbutton_ligature;                              //~vam7I
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spinbutton_2pinterval_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spinbutton_2pinterval_adj;                   //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spinbutton_2pinterval;
  GtkWidget *vbox10;
  GtkWidget *frame9;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkWidget *scrolledwindow1;
#endif                                                             //~var8R~
  GtkWidget *page_preview_area;
  GtkWidget *page_label_preview_area;
  GtkWidget *vbox11;
  GtkWidget *page_label_filename;
  GtkWidget *hbox18;
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GtkObject *page_spinbutton_curpage_adj;
#else   //OPTGTK3                                                  //~var8R~
  GtkAdjustment *page_spinbutton_curpage_adj;                      //~var8R~
#endif                                                             //~var8R~
  GtkWidget *page_spinbutton_curpage;
  GtkWidget *page_label_pageno;
  GtkWidget *page_label_cols;
  GtkWidget *page_frame_preview;
  GtkWidget *hbox19;
  GtkWidget *page_button_preview_print;
  GtkWidget *hbox20;
  GtkWidget *page_button_np;
  GtkWidget *hbox21;
  GtkWidget *page_button_pp;
  GtkWidget *page_button_preview_prtscr;
  GtkWidget *page_label_preview;
  GtkWidget *hseparator1;
  GtkWidget *hbox35;
  GtkWidget *hbox40;
  GtkWidget *page_entry_pagerange;
  GtkWidget *page_button_print;
  GtkWidget *hbox49;
  GtkWidget *label60;
  GtkWidget *page_button_prtscr;
  GtkWidget *hbox22;
  GtkWidget *hseparator2;
  GtkWidget *hbox23;
  GtkWidget *label62;
  GtkWidget *page_button_cancel;
  GtkWidget *page_button_save;
  GtkWidget *label61;
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GtkWidget *dialog_action_area3;
#endif                                                             //~vb7tI~
  GtkTooltips *tooltips;

  tooltips = gtk_tooltips_new ();

  printdlg = gtk_dialog_new ();
  gtk_window_set_title (GTK_WINDOW (printdlg), _("PageSetup"));
  gtk_window_set_modal (GTK_WINDOW (printdlg), TRUE);
  gtk_window_set_default_size (GTK_WINDOW (printdlg), 150, -1);
  gtk_window_set_resizable (GTK_WINDOW (printdlg), FALSE);
  gtk_window_set_type_hint (GTK_WINDOW (printdlg), GDK_WINDOW_TYPE_HINT_DIALOG);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_vbox3 = GTK_DIALOG (printdlg)->vbox;
#else                                                              //+var8~//~var8R~
  dialog_vbox3 = gtk_dialog_get_content_area(GTK_DIALOG (printdlg));//~var8R~
#endif                                                             //+var8~//~var8R~
  gtk_widget_show (dialog_vbox3);

  hbox17 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox17);
  gtk_box_pack_start (GTK_BOX (dialog_vbox3), hbox17, TRUE, TRUE, 0);

  vbox12 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox12);
  gtk_box_pack_start (GTK_BOX (hbox17), vbox12, TRUE, TRUE, 0);

  frame12 = gtk_frame_new (NULL);
  gtk_widget_show (frame12);
  gtk_box_pack_start (GTK_BOX (vbox12), frame12, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame12), 3);

  vbox16 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox16);
  gtk_container_add (GTK_CONTAINER (frame12), vbox16);

  hbox51 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox51);
  gtk_box_pack_start (GTK_BOX (vbox16), hbox51, TRUE, TRUE, 0);

  page_label_printer = gtk_label_new (_("Printer  "));
  gtk_widget_show (page_label_printer);
  gtk_box_pack_start (GTK_BOX (hbox51), page_label_printer, FALSE, FALSE, 0);

  combo2 = gtk_combo_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_object_set_data (G_OBJECT (GTK_COMBO (combo2)->popwin),
                     "GladeParentKey", combo2);
#endif    //no popwin corresponding is found?                      //~var8R~
  gtk_widget_show (combo2);
  gtk_box_pack_start (GTK_BOX (hbox51), combo2, TRUE, TRUE, 0);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  page_combo_printer = GTK_COMBO (combo2)->entry;
#else                                                              //~var8R~
  page_combo_printer = gtk_bin_get_child(GTK_BIN(combo2));         //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (page_combo_printer);
  gtk_widget_set_size_request (page_combo_printer, 30, -1);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_editable_set_editable (GTK_EDITABLE (page_combo_printer), FALSE);
#else                                                              //~var8R~
#endif                                                             //~var8R~

  label65 = gtk_label_new (_("            "));
  gtk_widget_show (label65);
  gtk_box_pack_start (GTK_BOX (hbox51), label65, FALSE, FALSE, 0);

  hbox34 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox34);
//#ifdef AAA                                                       //~var8R~
  gtk_box_pack_start (GTK_BOX (vbox16), hbox34, TRUE, TRUE, 0);
//#endif                                                           //~var8R~

//page_label_size = gtk_label_new (_("FormSize "));                //~vamtR
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  page_label_size = gtk_label_new (_("PaperSize "));               //~vamtI
#else        //shrink dialog width                                 //~var8R~
  page_label_size = gtk_label_new (_("Paper   "));                 //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (page_label_size);
  gtk_box_pack_start (GTK_BOX (hbox34), page_label_size, FALSE, FALSE, 0);

  combo1 = gtk_combo_new ();
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_object_set_data (G_OBJECT (GTK_COMBO (combo1)->popwin),
                     "GladeParentKey", combo1);
#endif    //no popwin corresponding is found?                      //~var8R~
  gtk_widget_show (combo1);
  gtk_box_pack_start (GTK_BOX (hbox34), combo1, TRUE, TRUE, 0);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  page_combo_form = GTK_COMBO (combo1)->entry;
#else                                                              //~var8R~
  page_combo_form = gtk_bin_get_child(GTK_BIN(combo1));            //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (page_combo_form);
  gtk_widget_set_size_request (page_combo_form, 30, -1);
  gtk_tooltips_set_tip (tooltips, page_combo_form, _("Form name"), NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_editable_set_editable (GTK_EDITABLE (page_combo_form), FALSE);
#else                                                              //~var8R~
#endif                                                             //~var8R~
  page_chkbutton_landscape = gtk_check_button_new_with_mnemonic (_("Landscape"));
  gtk_widget_show (page_chkbutton_landscape);
  gtk_box_pack_start (GTK_BOX (hbox34), page_chkbutton_landscape, FALSE, FALSE, 0);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_landscape, _("Portrait's right margin is Landscape's top."), NULL);//~vam7R

  frame13 = gtk_frame_new (NULL);
  gtk_widget_show (frame13);
  gtk_box_pack_start (GTK_BOX (vbox16), frame13, TRUE, TRUE, 0);
  gtk_widget_set_size_request (frame13, -1, 70);
  gtk_container_set_border_width (GTK_CONTAINER (frame13), 3);

  table8 = gtk_table_new (2, 6, FALSE);
  gtk_widget_show (table8);
  gtk_container_add (GTK_CONTAINER (frame13), table8);
  gtk_widget_set_size_request (table8, -1, 23);

  page_label_left = gtk_label_new (_("  Left"));
  gtk_widget_show (page_label_left);
  gtk_table_attach (GTK_TABLE (table8), page_label_left, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_left,GTK_ALIGN_CENTER);         //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_left), 0, 0.5);
#endif                                                             //~vb7tI~

  page_label_top = gtk_label_new (_("  Top"));
  gtk_widget_show (page_label_top);
  gtk_table_attach (GTK_TABLE (table8), page_label_top, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_top,GTK_ALIGN_CENTER);          //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_top), 0, 0.5);
#endif                                                             //~vb7tI~

  page_label_right = gtk_label_new (_("  Right"));
  gtk_widget_show (page_label_right);
  gtk_table_attach (GTK_TABLE (table8), page_label_right, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_right,GTK_ALIGN_CENTER);        //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_right), 0, 0.5);
#endif                                                             //~vb7tI~

  page_label_bottom = gtk_label_new (_("  Bottom"));
  gtk_widget_show (page_label_bottom);
  gtk_table_attach (GTK_TABLE (table8), page_label_bottom, 2, 3, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_bottom,GTK_ALIGN_CENTER);       //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_bottom), 0, 0.5);
#endif                                                             //~vb7tI~

#ifdef GTKPRINT                                                    //~vamtI
  page_spin_top_adj = gtk_adjustment_new (0/*init*/, 0/*min*/,9999/*max,xxyy:xx=shift,yy=margin*/, 1/*step increment*/, 10/*page increment*/, 0/*page size*/);//~vamtR
#else                                                              //~vamtI
  page_spin_top_adj = gtk_adjustment_new (9, 0, 1000, 1, 10, 0);   //~vamtR
#endif                                                             //~vamtI
  page_spin_top = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_top_adj), 1, 0);
  gtk_widget_show (page_spin_top);
  gtk_table_attach (GTK_TABLE (table8), page_spin_top, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (page_spin_top, -1, 22);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_top),2);           //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_top, _("Top margin"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_top), TRUE);

#ifdef GTKPRINT                                                    //~vamtI
  page_spin_right_adj = gtk_adjustment_new (0, 0, 9999, 1, 10, 0); //~vamtR
#else                                                              //~vamtI
  page_spin_right_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0); //~vamtR
#endif                                                             //~vamtI
  page_spin_right = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_right_adj), 1, 0);
  gtk_widget_show (page_spin_right);
  gtk_table_attach (GTK_TABLE (table8), page_spin_right, 3, 4, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (page_spin_right, -1, 22);
#else                                                              //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_right),2);         //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_right, _("Right margin"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_right), TRUE);

#ifdef GTKPRINT                                                    //~vamtI
  page_spin_bottom_adj = gtk_adjustment_new (0, 0, 9999, 1, 10, 0);//~vamtR
#else                                                              //~vamtI
  page_spin_bottom_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0);//~vamtR
#endif                                                             //~vamtI
  page_spin_bottom = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_bottom_adj), 1, 0);
  gtk_widget_show (page_spin_bottom);
  gtk_table_attach (GTK_TABLE (table8), page_spin_bottom, 3, 4, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (page_spin_bottom, -1, 22);
#else                                                              //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_bottom),2);        //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_bottom, _("Bottom margin"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_bottom), TRUE);

#ifdef GTKPRINT                                                    //~vamtI
  page_spin_left_adj = gtk_adjustment_new (0, 0, 9999, 1, 10, 0);  //~vamtR
#else                                                              //~vamtI
  page_spin_left_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0);  //~vamtR
#endif                                                             //~vamtI
  page_spin_left = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_left_adj), 1, 0);
  gtk_widget_show (page_spin_left);
  gtk_table_attach (GTK_TABLE (table8), page_spin_left, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
//#ifdef GTKPRINT                                                  //~var8R~
  gtk_widget_set_size_request (page_spin_left, -1, 22);
//#else                                                            //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_left),2);        //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_left, _("Left Margin"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_left), TRUE);

//page_label_margin = gtk_label_new (_("Margin(mm)"));             //~vam7R//~vamtR
  page_label_margin = gtk_label_new (_("Margin(mm) as portrait")); //~vam7I//~vamtM
  gtk_widget_show (page_label_margin);
  gtk_frame_set_label_widget (GTK_FRAME (frame13), page_label_margin);
  gtk_tooltips_set_tip (tooltips, page_label_margin, _(TOOLTIPS_PAGE_LABEL_MARGIN), NULL);//~vamtI

  page_label_default_margin = gtk_label_new (_("by milimeter"));
  gtk_widget_show (page_label_default_margin);
  gtk_box_pack_start (GTK_BOX (vbox16), page_label_default_margin, FALSE, FALSE, 0);

  page_label_form = gtk_label_new (_("Form"));
  gtk_widget_show (page_label_form);
  gtk_frame_set_label_widget (GTK_FRAME (frame12), page_label_form);
  gtk_widget_set_size_request (page_label_form, -1, 18);

  frame14 = gtk_frame_new (NULL);
  gtk_widget_show (frame14);
  gtk_box_pack_start (GTK_BOX (vbox12), frame14, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame14), 3);

  vbox17 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox17);
  gtk_container_add (GTK_CONTAINER (frame14), vbox17);

  page_entry_current_font = gtk_entry_new ();
  gtk_widget_show (page_entry_current_font);
  gtk_box_pack_start (GTK_BOX (vbox17), page_entry_current_font, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_entry_current_font, 50, -1);
  gtk_tooltips_set_tip (tooltips, page_entry_current_font, _("Current Font for print"), NULL);
  gtk_editable_set_editable (GTK_EDITABLE (page_entry_current_font), FALSE);

  hbox48 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox48);
  gtk_box_pack_start (GTK_BOX (vbox17), hbox48, FALSE, FALSE, 0);

  page_font_change = gtk_button_new_with_mnemonic (_("FontChange"));
  gtk_widget_show (page_font_change);
  gtk_box_pack_start (GTK_BOX (hbox48), page_font_change, FALSE, FALSE, 0);
  gtk_tooltips_set_tip (tooltips, page_font_change, _("Push when change print Font"), NULL);

  page_label_fonth = gtk_label_new (_(" Font-H"));
  gtk_widget_show (page_label_fonth);
  gtk_box_pack_start (GTK_BOX (hbox48), page_label_fonth, FALSE, FALSE, 0);

  page_entry_fonth = gtk_entry_new ();
  gtk_widget_show (page_entry_fonth);
  gtk_box_pack_start (GTK_BOX (hbox48), page_entry_fonth, TRUE, TRUE, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (page_entry_fonth, 30, -1);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_entry_fonth),2);        //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_entry_fonth, _("Average charcter Height of the Font"), NULL);

  label59 = gtk_label_new (_(" Font-W"));
  gtk_widget_show (label59);
  gtk_box_pack_start (GTK_BOX (hbox48), label59, FALSE, FALSE, 0);

  page_entry_fontw = gtk_entry_new ();
  gtk_widget_show (page_entry_fontw);
  gtk_box_pack_start (GTK_BOX (hbox48), page_entry_fontw, TRUE, TRUE, 0);
#ifndef OPTGTK3                                                    //~var8R~
  gtk_widget_set_size_request (page_entry_fontw, 30, -1);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_entry_fontw),2);        //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_entry_fontw, _("Average char Width of the Font"), NULL);

  vbox18 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox18);
  gtk_box_pack_start (GTK_BOX (vbox17), vbox18, TRUE, TRUE, 0);

  hbox36 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox36);
  gtk_box_pack_start (GTK_BOX (vbox18), hbox36, TRUE, TRUE, 0);

  hseparator3 = gtk_hseparator_new ();
  gtk_widget_show (hseparator3);
  gtk_box_pack_start (GTK_BOX (hbox36), hseparator3, TRUE, TRUE, 0);

  page_chkbutton_bycellhw = gtk_check_button_new_with_mnemonic (_("Col/Row by Cell-H/W"));
  gtk_widget_show (page_chkbutton_bycellhw);
  gtk_box_pack_start (GTK_BOX (vbox18), page_chkbutton_bycellhw, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_chkbutton_bycellhw, 100, -1);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_bycellhw, _("Determin Row/Column of page from CellH/Cell-W parameter"), NULL);

  hbox37 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox37);
  gtk_box_pack_start (GTK_BOX (vbox18), hbox37, TRUE, TRUE, 0);

  hbox41 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox41);
  gtk_box_pack_start (GTK_BOX (hbox37), hbox41, TRUE, TRUE, 0);

  page_label_cellh = gtk_label_new (_(" Cell-H"));
  gtk_widget_show (page_label_cellh);
  gtk_box_pack_start (GTK_BOX (hbox41), page_label_cellh, FALSE, FALSE, 0);

  page_spinbutton_cellh_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  page_spinbutton_cellh = gtk_spin_button_new (GTK_ADJUSTMENT (page_spinbutton_cellh_adj), 1, 0);
  gtk_widget_show (page_spinbutton_cellh);
  gtk_box_pack_start (GTK_BOX (hbox41), page_spinbutton_cellh, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (page_spinbutton_cellh, 30, -1);
//#else   //OPTGTK3                                                //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spinbutton_cellh),2); //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spinbutton_cellh, _("height of Row"), NULL);

  page_label_cellw = gtk_label_new (_(" Cell-W"));
  gtk_widget_show (page_label_cellw);
  gtk_box_pack_start (GTK_BOX (hbox41), page_label_cellw, FALSE, FALSE, 0);

  page_spinbutton_cellw_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  page_spinbutton_cellw = gtk_spin_button_new (GTK_ADJUSTMENT (page_spinbutton_cellw_adj), 1, 0);
  gtk_widget_show (page_spinbutton_cellw);
  gtk_box_pack_start (GTK_BOX (hbox41), page_spinbutton_cellw, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (page_spinbutton_cellw, 30, -1);
//#else   //OPTGTK3                                                //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spinbutton_cellw),2); //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spinbutton_cellw, _("Width of Column"), NULL);

  page_label_font = gtk_label_new (_("Font"));
  gtk_widget_show (page_label_font);
  gtk_frame_set_label_widget (GTK_FRAME (frame14), page_label_font);

  vbox15 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox15);
  gtk_box_pack_start (GTK_BOX (vbox12), vbox15, TRUE, TRUE, 0);

  hbox33 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox33);
  gtk_box_pack_start (GTK_BOX (vbox15), hbox33, TRUE, TRUE, 0);

  page_label_col = gtk_label_new (_("Col"));
  gtk_widget_show (page_label_col);
  gtk_box_pack_start (GTK_BOX (hbox33), page_label_col, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_label_col, 50, -1);

  page_spin_col_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0);
  page_spin_col = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_col_adj), 1, 0);
  gtk_widget_show (page_spin_col);
  gtk_box_pack_start (GTK_BOX (hbox33), page_spin_col, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (page_spin_col, 30, -1);
//#else   //OPTGTK3                                                //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_col),2);         //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_col, _("Columns per Line;if 0 Col is determined by longest line of the file"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_col), TRUE);

  page_label_row = gtk_label_new (_("Row"));
  gtk_widget_show (page_label_row);
  gtk_box_pack_start (GTK_BOX (hbox33), page_label_row, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_label_row, 50, -1);
  gtk_label_set_justify (GTK_LABEL (page_label_row), GTK_JUSTIFY_RIGHT);

  page_spin_row_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0);
  page_spin_row = gtk_spin_button_new (GTK_ADJUSTMENT (page_spin_row_adj), 1, 0);
  gtk_widget_show (page_spin_row);
  gtk_box_pack_start (GTK_BOX (hbox33), page_spin_row, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (page_spin_row, 30, -1);
//#else   //OPTGTK3                                                //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spin_row),2);         //~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spin_row, _("Rows per page;if 0 determined by Col & Font Height/Width rate"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spin_row), TRUE);

  hbox50 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox50);
  gtk_box_pack_start (GTK_BOX (vbox15), hbox50, TRUE, TRUE, 0);

  label63 = gtk_label_new (_("         maximum Cell-H  "));
  gtk_widget_show (label63);
  gtk_box_pack_start (GTK_BOX (hbox50), label63, FALSE, FALSE, 0);

  page_spinbutton_cellhmax_adj = gtk_adjustment_new (1, 0, 1000, 1, 10, 0);
  page_spinbutton_cellhmax = gtk_spin_button_new (GTK_ADJUSTMENT (page_spinbutton_cellhmax_adj), 1, 0);
  gtk_widget_show (page_spinbutton_cellhmax);
  gtk_box_pack_start (GTK_BOX (hbox50), page_spinbutton_cellhmax, TRUE, TRUE, 0);
//#ifndef OPTGTK3                                                  //~var8R~
  gtk_widget_set_size_request (page_spinbutton_cellhmax, 20, -1);
//#else   //OPTGTK3                                                //~var8R~
//  gtk_entry_set_width_chars(GTK_ENTRY(page_spinbutton_cellhmax),2);//~var8R~
//#endif                                                           //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spinbutton_cellhmax, _("maixmum Row Height applied when both Col & Row is 0"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spinbutton_cellhmax), TRUE);

  hseparator5 = gtk_hseparator_new ();
  gtk_widget_show (hseparator5);
  gtk_box_pack_start (GTK_BOX (vbox15), hseparator5, TRUE, TRUE, 0);

  table7 = gtk_table_new (5, 3, FALSE);
  gtk_widget_show (table7);
  gtk_box_pack_start (GTK_BOX (vbox15), table7, TRUE, TRUE, 0);

  page_chkbutton_lineno = gtk_check_button_new_with_mnemonic (_("LineNumber"));
  gtk_widget_show (page_chkbutton_lineno);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_lineno, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_lineno, _("Print LineNumber"), NULL);

  page_chkbutton_2p = gtk_check_button_new_with_mnemonic (_("2p"));
  gtk_widget_show (page_chkbutton_2p);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_2p, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (page_chkbutton_2p, 30, -1);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_2p, _("Print 2 pages per sheet"), NULL);

  page_chkbutton_header = gtk_check_button_new_with_mnemonic (_("Header"));
  gtk_widget_show (page_chkbutton_header);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_header, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (page_chkbutton_header, 30, -1);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_header, _("Print Header Line(FileName)"), NULL);

  page_chkbutton_filetime = gtk_check_button_new_with_mnemonic (_("FileTime"));
  gtk_widget_show (page_chkbutton_filetime);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_filetime, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_filetime, _("Print File Timestamp on Header line"), NULL);

  page_chkbutton_footer = gtk_check_button_new_with_mnemonic (_("Footer"));
  gtk_widget_show (page_chkbutton_footer);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_footer, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (page_chkbutton_footer, 30, -1);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_footer, _("Print Footer Line(PageNumber)"), NULL);

  page_chkbutton_wwscrprt = gtk_check_button_new_with_mnemonic (_("WW ScrPrt"));
  gtk_widget_show (page_chkbutton_wwscrprt);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_wwscrprt, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_widget_set_size_request (page_chkbutton_wwscrprt, 30, -1);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_wwscrprt, _("WysiWig ScreenPrint(print as you see in the whole of screen,else expand up to page width or height)"), NULL);

  page_chkbutton_systime = gtk_check_button_new_with_mnemonic (_("SysTime"));
  gtk_widget_show (page_chkbutton_systime);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_systime, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_systime, _("Print Current Time on the Footer line"), NULL);

  page_chkbutton_fullpage = gtk_check_button_new_with_mnemonic (_("FillPage"));
  gtk_widget_show (page_chkbutton_fullpage);
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_fullpage, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_tooltips_set_tip (tooltips, page_chkbutton_fullpage, _("print expanded to whole of page(height and width)"), NULL);
                                                                   //~vam7I
//  page_chkbutton_ligature = gtk_check_button_new_with_mnemonic (_("Ligature"));//~vam7R
//  gtk_widget_show (page_chkbutton_ligature);                     //~vam7R
//  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_ligature, 0, 1, 4, 5,//~vam7R
//                    (GtkAttachOptions) (GTK_FILL),               //~vam7R
//                    (GtkAttachOptions) (0), 0, 0);               //~vam7R
//  gtk_tooltips_set_tip (tooltips, page_chkbutton_ligature, _("Print lines with ligature"), NULL);//~vam7R

  page_spinbutton_2pinterval_adj = gtk_adjustment_new (1, 0, 100, 1, 10, 0);
  page_spinbutton_2pinterval = gtk_spin_button_new (GTK_ADJUSTMENT (page_spinbutton_2pinterval_adj), 1, 0);
  gtk_widget_show (page_spinbutton_2pinterval);
  gtk_table_attach (GTK_TABLE (table7), page_spinbutton_2pinterval, 2, 3, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_widget_set_size_request (page_spinbutton_2pinterval, 30, -1);
#else   //OPTGTK3                                                  //~var8R~
  gtk_entry_set_width_chars(GTK_ENTRY(page_spinbutton_2pinterval),2);//~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_spinbutton_2pinterval, _("Columns between page when 2p option"), NULL);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (page_spinbutton_2pinterval), TRUE);
                                                                   //~vam7I
  page_chkbutton_ligature = gtk_check_button_new_with_mnemonic (_("Ligature"));//~vam7R
  gtk_widget_show (page_chkbutton_ligature);                       //~vam7R
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_ligature, 2, 3, 1, 2,//~vam7R
                    (GtkAttachOptions) (GTK_FILL),                 //~vam7R
                    (GtkAttachOptions) (0), 0, 0);                 //~vam7R
#else   //OPTGTK3                                                  //~var8R~
  gtk_table_attach (GTK_TABLE (table7), page_chkbutton_ligature, 0, 1, 4, 5,//~var8R~
                    (GtkAttachOptions) (GTK_FILL),                 //~var8R~
                    (GtkAttachOptions) (0), 0, 0);                 //~var8R~
#endif                                                             //~var8R~
  gtk_tooltips_set_tip (tooltips, page_chkbutton_ligature, _("Print allows ligature.\n(for PrtScr,applied \"Ligature\" of \"Setup Options\" dialog)"), NULL);//~vam7R
                                                                   //~vam7I

  vbox10 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox10);
  gtk_box_pack_start (GTK_BOX (hbox17), vbox10, TRUE, TRUE, 0);

  frame9 = gtk_frame_new (NULL);
  gtk_widget_show (frame9);
  gtk_box_pack_start (GTK_BOX (vbox10), frame9, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame9), 3);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  scrolledwindow1 = gtk_scrolled_window_new (NULL, NULL);
  gtk_widget_show (scrolledwindow1);
  gtk_container_add (GTK_CONTAINER (frame9), scrolledwindow1);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolledwindow1), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
#endif                                                             //~var8R~

#ifndef OPTGTK3                                                    //~var8R~
  page_preview_area = gnome_canvas_new ();
#else   //OPTGTK3                                                  //~var8R~
  page_preview_area = gtk_drawing_area_new ();                     //~var8R~
#endif                                                             //~var8R~
  gtk_widget_show (page_preview_area);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gtk_container_add (GTK_CONTAINER (scrolledwindow1), page_preview_area);
#else   //OPTGTK3                                                  //~var8R~
  gtk_container_add (GTK_CONTAINER (frame9), page_preview_area);   //~var8R~
#endif                                                             //~var8R~
  gtk_widget_set_size_request (page_preview_area, 250, 250);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  gnome_canvas_set_scroll_region (GNOME_CANVAS (page_preview_area), 0, 0, 250, 250);
#else   //OPTGTK3                                                  //~var8R~
#endif                                                             //~var8R~

  page_label_preview_area = gtk_label_new (_("Preview window"));
  gtk_widget_show (page_label_preview_area);
  gtk_frame_set_label_widget (GTK_FRAME (frame9), page_label_preview_area);

  vbox11 = gtk_vbox_new (FALSE, 0);
  gtk_widget_show (vbox11);
  gtk_box_pack_start (GTK_BOX (vbox10), vbox11, TRUE, TRUE, 0);

  page_label_filename = gtk_label_new (_("FileName"));
  gtk_widget_show (page_label_filename);
  gtk_box_pack_start (GTK_BOX (vbox11), page_label_filename, FALSE, FALSE, 0);

  hbox18 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox18);
  gtk_box_pack_start (GTK_BOX (vbox11), hbox18, TRUE, TRUE, 0);

  page_spinbutton_curpage_adj = gtk_adjustment_new (1, 0, 10000, 1, 10, 0);
  page_spinbutton_curpage = gtk_spin_button_new (GTK_ADJUSTMENT (page_spinbutton_curpage_adj), 1, 0);
  gtk_widget_show (page_spinbutton_curpage);
  gtk_box_pack_start (GTK_BOX (hbox18), page_spinbutton_curpage, TRUE, TRUE, 0);
  gtk_tooltips_set_tip (tooltips, page_spinbutton_curpage, _("Curent preview PageNumber"), NULL);

  page_label_pageno = gtk_label_new (_("page"));
  gtk_widget_show (page_label_pageno);
  gtk_box_pack_start (GTK_BOX (hbox18), page_label_pageno, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_label_pageno, 200, -1);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_pageno,GTK_ALIGN_CENTER);       //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_pageno), 0, 0.5);
#endif                                                             //~vb7tI~

  page_label_cols = gtk_label_new ("");
  gtk_widget_show (page_label_cols);
  gtk_box_pack_start (GTK_BOX (vbox11), page_label_cols, FALSE, FALSE, 0);
#if GTK_CHECK_VERSION(3,14,0)                                      //~vb7tI~
  gtk_widget_set_valign(page_label_cols,GTK_ALIGN_CENTER);         //~vb7tI~
#else                                                              //~vb7tI~
  gtk_misc_set_alignment (GTK_MISC (page_label_cols), 0, 0.5);
#endif                                                             //~vb7tI~

  page_frame_preview = gtk_frame_new (NULL);
  gtk_widget_show (page_frame_preview);
  gtk_box_pack_start (GTK_BOX (vbox11), page_frame_preview, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (page_frame_preview), 3);

  hbox19 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox19);
  gtk_container_add (GTK_CONTAINER (page_frame_preview), hbox19);

  page_button_preview_print = gtk_button_new_with_mnemonic (_("Print"));
  gtk_widget_show (page_button_preview_print);
  gtk_box_pack_start (GTK_BOX (hbox19), page_button_preview_print, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_preview_print, 66, -1);
  gtk_tooltips_set_tip (tooltips, page_button_preview_print, _("Preview FilePrint"), NULL);

  hbox20 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox20);
  gtk_box_pack_start (GTK_BOX (hbox19), hbox20, TRUE, TRUE, 0);

  page_button_np = gtk_button_new_with_mnemonic (_("NP"));
  gtk_widget_show (page_button_np);
  gtk_box_pack_end (GTK_BOX (hbox20), page_button_np, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_np, 33, -1);
  gtk_tooltips_set_tip (tooltips, page_button_np, _("Preview NextPage"), NULL);

  hbox21 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox21);
  gtk_box_pack_start (GTK_BOX (hbox19), hbox21, TRUE, TRUE, 0);

  page_button_pp = gtk_button_new_with_mnemonic (_("PP"));
  gtk_widget_show (page_button_pp);
  gtk_box_pack_start (GTK_BOX (hbox21), page_button_pp, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_pp, 33, -1);
  gtk_tooltips_set_tip (tooltips, page_button_pp, _("Preview PreviousPage"), NULL);

  page_button_preview_prtscr = gtk_button_new_with_mnemonic (_("PrtScr"));
  gtk_widget_show (page_button_preview_prtscr);
  gtk_box_pack_end (GTK_BOX (hbox19), page_button_preview_prtscr, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_preview_prtscr, 66, -1);
  gtk_tooltips_set_tip (tooltips, page_button_preview_prtscr, _("Preview ScreenPrint"), NULL);

  page_label_preview = gtk_label_new (_("Preview"));
  gtk_widget_show (page_label_preview);
  gtk_frame_set_label_widget (GTK_FRAME (page_frame_preview), page_label_preview);

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vbox11), hseparator1, TRUE, TRUE, 0);
  gtk_widget_set_size_request (hseparator1, -1, 4);

  hbox35 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox35);
  gtk_box_pack_start (GTK_BOX (vbox11), hbox35, TRUE, TRUE, 0);

  hbox40 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox40);
  gtk_box_pack_start (GTK_BOX (hbox35), hbox40, FALSE, FALSE, 0);

  page_entry_pagerange = gtk_entry_new ();
  gtk_widget_show (page_entry_pagerange);
  gtk_box_pack_start (GTK_BOX (hbox40), page_entry_pagerange, TRUE, TRUE, 0);
  gtk_widget_set_size_request (page_entry_pagerange, 100, -1);
  gtk_tooltips_set_tip (tooltips, page_entry_pagerange, _("PrintpageRange. ex) 2-3,5,7,9-"), NULL);
  gtk_entry_set_max_length (GTK_ENTRY (page_entry_pagerange), 100);
  gtk_entry_set_text (GTK_ENTRY (page_entry_pagerange), _("all pages"));

  page_button_print = gtk_button_new_with_mnemonic (_("Print"));
  gtk_widget_show (page_button_print);
  gtk_box_pack_start (GTK_BOX (hbox40), page_button_print, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_print, 66, -1);
  gtk_tooltips_set_tip (tooltips, page_button_print, _("Execute FilePrint"), NULL);

  hbox49 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox49);
  gtk_box_pack_start (GTK_BOX (hbox35), hbox49, TRUE, TRUE, 0);

  label60 = gtk_label_new (_("    "));
  gtk_widget_show (label60);
  gtk_box_pack_start (GTK_BOX (hbox49), label60, FALSE, FALSE, 0);

  page_button_prtscr = gtk_button_new_with_mnemonic (_("PrtScr"));
  gtk_widget_show (page_button_prtscr);
  gtk_box_pack_end (GTK_BOX (hbox35), page_button_prtscr, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_prtscr, 66, -1);
//  gtk_tooltips_set_tip (tooltips, page_button_prtscr, _("Execute ScreenPrint"), NULL);//~vam7R
  gtk_tooltips_set_tip (tooltips, page_button_prtscr, _("Execute ScreenPrint using Font of \"Setup Options\" dialog"), NULL);//~vam7I

  hbox22 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox22);
  gtk_box_pack_start (GTK_BOX (vbox11), hbox22, TRUE, TRUE, 0);

  hseparator2 = gtk_hseparator_new ();
  gtk_widget_show (hseparator2);
  gtk_box_pack_start (GTK_BOX (hbox22), hseparator2, TRUE, TRUE, 0);
  gtk_widget_set_size_request (hseparator2, -1, 10);

  hbox23 = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (hbox23);
  gtk_box_pack_start (GTK_BOX (vbox11), hbox23, TRUE, TRUE, 0);

  label62 = gtk_label_new (_("  "));
  gtk_widget_show (label62);
  gtk_box_pack_start (GTK_BOX (hbox23), label62, FALSE, FALSE, 0);
  gtk_widget_set_size_request (label62, 100, -1);

  page_button_cancel = gtk_button_new_with_mnemonic (_("Cancel"));
  gtk_widget_show (page_button_cancel);
  gtk_box_pack_end (GTK_BOX (hbox23), page_button_cancel, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_cancel, 66, -1);
  gtk_tooltips_set_tip (tooltips, page_button_cancel, _("Discard Changes and exit"), NULL);

  page_button_save = gtk_button_new_with_mnemonic (_("OK"));
  gtk_widget_show (page_button_save);
  gtk_box_pack_start (GTK_BOX (hbox23), page_button_save, FALSE, FALSE, 0);
  gtk_widget_set_size_request (page_button_save, 66, -1);
  gtk_tooltips_set_tip (tooltips, page_button_save, _("Save Changes and exit"), NULL);

  label61 = gtk_label_new (_("    "));
  gtk_widget_show (label61);
  gtk_box_pack_start (GTK_BOX (hbox23), label61, FALSE, FALSE, 0);

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  dialog_action_area3 = GTK_DIALOG (printdlg)->action_area;
#else                                                              //+var8~//~var8R~
 #if GTK_CHECK_VERSION(3,12,0)                                     //~vb7tI~
 #else                                                             //~vb7tI~
  dialog_action_area3 = gtk_dialog_get_action_area(GTK_DIALOG (printdlg));//~var8R~
 #endif                                                            //~vb7tI~
#endif                                                             //+var8~//~var8R~
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  gtk_widget_show (dialog_action_area3);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_action_area3), GTK_BUTTONBOX_END);
#endif                                                             //+var8~//~vb7tI~

#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_signal_connect ((gpointer) page_combo_printer, "changed",
                    G_CALLBACK (on_page_combo_printer_changed),
                    NULL);
#else   //OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) combo2, "changed",                  //~var8R~
                    G_CALLBACK (on_page_combo_printer_changed),    //~var8R~
                    NULL);                                         //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vap1I
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  g_signal_connect ((gpointer) page_combo_form, "changed",         //~vambR
                    G_CALLBACK (on_page_combo_form_changed),       //~vambR
                    NULL);                                         //~vambR
#else   //OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) combo1, "changed",                  //~var8R~
                    G_CALLBACK (on_page_combo_form_changed),       //~var8R~
                    NULL);                                         //~var8R~
#endif                                                             //~var8R~
#endif //!NOPRINT                                                  //~vap1I
  g_signal_connect ((gpointer) page_font_change, "clicked",
                    G_CALLBACK (on_page_font_change_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_chkbutton_bycellhw, "toggled",
                    G_CALLBACK (on_page_chkbutton_bycellhw_toggled),
                    NULL);
  g_signal_connect ((gpointer) page_chkbutton_2p, "toggled",
                    G_CALLBACK (on_page_chkbutton_2p_toggled),
                    NULL);
  g_signal_connect ((gpointer) page_chkbutton_header, "toggled",
                    G_CALLBACK (on_page_chkbutton_header_toggled),
                    NULL);
  g_signal_connect ((gpointer) page_chkbutton_footer, "toggled",
                    G_CALLBACK (on_page_chkbutton_footer_toggled),
                    NULL);
  g_signal_connect ((gpointer) page_button_preview_print, "clicked",
                    G_CALLBACK (on_page_button_preview_print_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_np, "clicked",
                    G_CALLBACK (on_page_button_np_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_pp, "clicked",
                    G_CALLBACK (on_page_button_pp_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_preview_prtscr, "clicked",
                    G_CALLBACK (on_page_button_preview_prtscr_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_print, "clicked",
                    G_CALLBACK (on_page_button_print_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_prtscr, "clicked",
                    G_CALLBACK (on_page_button_prtscr_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_cancel, "clicked",
                    G_CALLBACK (on_page_button_cancel_clicked),
                    NULL);
  g_signal_connect ((gpointer) page_button_save, "clicked",
                    G_CALLBACK (on_page_button_save_clicked),
                    NULL);
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else   //OPTGTK3                                                  //~var8R~
  g_signal_connect ((gpointer) page_preview_area, "draw",          //~var8R~
                    G_CALLBACK (on_page_previewarea_draw),         //~var8R~
                    NULL);                                         //~var8R~
#endif                                                             //~var8R~

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (printdlg, printdlg, "printdlg");
  GLADE_HOOKUP_OBJECT_NO_REF (printdlg, dialog_vbox3, "dialog_vbox3");
  GLADE_HOOKUP_OBJECT (printdlg, hbox17, "hbox17");
  GLADE_HOOKUP_OBJECT (printdlg, vbox12, "vbox12");
  GLADE_HOOKUP_OBJECT (printdlg, frame12, "frame12");
  GLADE_HOOKUP_OBJECT (printdlg, vbox16, "vbox16");
  GLADE_HOOKUP_OBJECT (printdlg, hbox51, "hbox51");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_printer, "page_label_printer");
  GLADE_HOOKUP_OBJECT (printdlg, combo2, "combo2");
  GLADE_HOOKUP_OBJECT (printdlg, page_combo_printer, "page_combo_printer");
  GLADE_HOOKUP_OBJECT (printdlg, label65, "label65");
  GLADE_HOOKUP_OBJECT (printdlg, hbox34, "hbox34");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_size, "page_label_size");
  GLADE_HOOKUP_OBJECT (printdlg, combo1, "combo1");
  GLADE_HOOKUP_OBJECT (printdlg, page_combo_form, "page_combo_form");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_landscape, "page_chkbutton_landscape");
  GLADE_HOOKUP_OBJECT (printdlg, frame13, "frame13");
  GLADE_HOOKUP_OBJECT (printdlg, table8, "table8");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_left, "page_label_left");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_top, "page_label_top");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_right, "page_label_right");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_bottom, "page_label_bottom");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_top, "page_spin_top");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_right, "page_spin_right");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_bottom, "page_spin_bottom");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_left, "page_spin_left");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_margin, "page_label_margin");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_default_margin, "page_label_default_margin");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_form, "page_label_form");
  GLADE_HOOKUP_OBJECT (printdlg, frame14, "frame14");
  GLADE_HOOKUP_OBJECT (printdlg, vbox17, "vbox17");
  GLADE_HOOKUP_OBJECT (printdlg, page_entry_current_font, "page_entry_current_font");
  GLADE_HOOKUP_OBJECT (printdlg, hbox48, "hbox48");
  GLADE_HOOKUP_OBJECT (printdlg, page_font_change, "page_font_change");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_fonth, "page_label_fonth");
  GLADE_HOOKUP_OBJECT (printdlg, page_entry_fonth, "page_entry_fonth");
  GLADE_HOOKUP_OBJECT (printdlg, label59, "label59");
  GLADE_HOOKUP_OBJECT (printdlg, page_entry_fontw, "page_entry_fontw");
  GLADE_HOOKUP_OBJECT (printdlg, vbox18, "vbox18");
  GLADE_HOOKUP_OBJECT (printdlg, hbox36, "hbox36");
  GLADE_HOOKUP_OBJECT (printdlg, hseparator3, "hseparator3");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_bycellhw, "page_chkbutton_bycellhw");
  GLADE_HOOKUP_OBJECT (printdlg, hbox37, "hbox37");
  GLADE_HOOKUP_OBJECT (printdlg, hbox41, "hbox41");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_cellh, "page_label_cellh");
  GLADE_HOOKUP_OBJECT (printdlg, page_spinbutton_cellh, "page_spinbutton_cellh");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_cellw, "page_label_cellw");
  GLADE_HOOKUP_OBJECT (printdlg, page_spinbutton_cellw, "page_spinbutton_cellw");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_font, "page_label_font");
  GLADE_HOOKUP_OBJECT (printdlg, vbox15, "vbox15");
  GLADE_HOOKUP_OBJECT (printdlg, hbox33, "hbox33");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_col, "page_label_col");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_col, "page_spin_col");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_row, "page_label_row");
  GLADE_HOOKUP_OBJECT (printdlg, page_spin_row, "page_spin_row");
  GLADE_HOOKUP_OBJECT (printdlg, hbox50, "hbox50");
  GLADE_HOOKUP_OBJECT (printdlg, label63, "label63");
  GLADE_HOOKUP_OBJECT (printdlg, page_spinbutton_cellhmax, "page_spinbutton_cellhmax");
  GLADE_HOOKUP_OBJECT (printdlg, hseparator5, "hseparator5");
  GLADE_HOOKUP_OBJECT (printdlg, table7, "table7");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_lineno, "page_chkbutton_lineno");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_2p, "page_chkbutton_2p");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_header, "page_chkbutton_header");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_filetime, "page_chkbutton_filetime");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_footer, "page_chkbutton_footer");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_wwscrprt, "page_chkbutton_wwscrprt");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_systime, "page_chkbutton_systime");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_fullpage, "page_chkbutton_fullpage");
  GLADE_HOOKUP_OBJECT (printdlg, page_chkbutton_ligature, "page_chkbutton_ligature");//~vam7I
  GLADE_HOOKUP_OBJECT (printdlg, page_spinbutton_2pinterval, "page_spinbutton_2pinterval");
  GLADE_HOOKUP_OBJECT (printdlg, vbox10, "vbox10");
  GLADE_HOOKUP_OBJECT (printdlg, frame9, "frame9");
#ifndef OPTGTK3                                                    //+var8~//~var8R~
  GLADE_HOOKUP_OBJECT (printdlg, scrolledwindow1, "scrolledwindow1");
#endif                                                             //~var8R~
  GLADE_HOOKUP_OBJECT (printdlg, page_preview_area, "page_preview_area");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_preview_area, "page_label_preview_area");
  GLADE_HOOKUP_OBJECT (printdlg, vbox11, "vbox11");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_filename, "page_label_filename");
  GLADE_HOOKUP_OBJECT (printdlg, hbox18, "hbox18");
  GLADE_HOOKUP_OBJECT (printdlg, page_spinbutton_curpage, "page_spinbutton_curpage");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_pageno, "page_label_pageno");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_cols, "page_label_cols");
  GLADE_HOOKUP_OBJECT (printdlg, page_frame_preview, "page_frame_preview");
  GLADE_HOOKUP_OBJECT (printdlg, hbox19, "hbox19");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_preview_print, "page_button_preview_print");
  GLADE_HOOKUP_OBJECT (printdlg, hbox20, "hbox20");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_np, "page_button_np");
  GLADE_HOOKUP_OBJECT (printdlg, hbox21, "hbox21");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_pp, "page_button_pp");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_preview_prtscr, "page_button_preview_prtscr");
  GLADE_HOOKUP_OBJECT (printdlg, page_label_preview, "page_label_preview");
  GLADE_HOOKUP_OBJECT (printdlg, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (printdlg, hbox35, "hbox35");
  GLADE_HOOKUP_OBJECT (printdlg, hbox40, "hbox40");
  GLADE_HOOKUP_OBJECT (printdlg, page_entry_pagerange, "page_entry_pagerange");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_print, "page_button_print");
  GLADE_HOOKUP_OBJECT (printdlg, hbox49, "hbox49");
  GLADE_HOOKUP_OBJECT (printdlg, label60, "label60");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_prtscr, "page_button_prtscr");
  GLADE_HOOKUP_OBJECT (printdlg, hbox22, "hbox22");
  GLADE_HOOKUP_OBJECT (printdlg, hseparator2, "hseparator2");
  GLADE_HOOKUP_OBJECT (printdlg, hbox23, "hbox23");
  GLADE_HOOKUP_OBJECT (printdlg, label62, "label62");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_cancel, "page_button_cancel");
  GLADE_HOOKUP_OBJECT (printdlg, page_button_save, "page_button_save");
  GLADE_HOOKUP_OBJECT (printdlg, label61, "label61");
#if GTK_CHECK_VERSION(3,12,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
  GLADE_HOOKUP_OBJECT_NO_REF (printdlg, dialog_action_area3, "dialog_action_area3");
#endif                                                             //~vb7tI~
  GLADE_HOOKUP_OBJECT_NO_REF (printdlg, tooltips, "tooltips");

  return printdlg;
}
#ifndef OPTGTK3                                                    //+var8~//~var8R~
#else                                                              //~var8R~
//*****************************************************************//~var8R~
void interface_gtk_widget_set_flags(GtkWidget *Ppwidget,int Pflag,gboolean Pbool)//~var8R~
{                                                                  //~var8R~
dprintf("interface_gtk_widget_setflags flag=%d, canfocus=%d,can_default=%d\n",Pflag,GTK_CAN_FOCUS,GTK_CAN_DEFAULT);//~var8R~
	if (Pflag==GTK_CAN_FOCUS)                                      //~var8R~
    	gtk_widget_set_can_focus(Ppwidget,Pbool);                  //~var8R~
    else                                                           //~var8R~
	if (Pflag==GTK_CAN_DEFAULT)                                    //~var8R~
    	gtk_widget_set_can_default(Ppwidget,Pbool);                //~var8R~
    else                                                           //~var8R~
    	printf("??? interface_gtk_widget_flags parm err flag=%x\n",Pflag);//~var8R~
}//interface_gtk_widget_set_flags                                  //~var8R~
//*****************************************************************//~var8R~
void interface_gtk_table_attach(GtkGrid *Ppgrid,GtkWidget *Ppchild,//~var8R~
					guint Pleft,guint Pright,guint Ptop,guint Pbottom,GtkAttachOptions Pxopt,GtkAttachOptions pyopt,guint Pxpad,guint Pypad)//~var8R~
{                                                                  //~var8R~
	int width,height;                                              //~var8R~
//********************************                                 //~var8R~
	width=Pright-Pleft;                                            //~var8R~
	height=Pbottom-Ptop;                                           //~var8R~
    dprintf("interface_gtk_table_attache x=%d,y=%d,w=%d,h=%d\n",Pleft,Ptop,width,height);//~var8R~
	gtk_grid_attach(Ppgrid,Ppchild,Pleft,Ptop,width,height);       //~var8R~
//FIXME                                                            //~var8R~
//    if (Pxopt & GTK_EXPAND)                                      //~var8R~
//    if (Pxopt & GTK_FILL)                                        //~var8R~
}//interface_gtk_table_attach                                      //~var8R~
//*****************************************************************//~var8R~
GdkFilterReturn interface_msg_filter(GdkXEvent *Pxevent,GdkEvent *Pevent,gpointer Pdata)//~var8R~
{                                                                  //~var8R~
	XClientMessageEvent *clientevent;                              //~var8R~
    Atom msgtype;                                                  //~var8R~
//********************************                                 //~var8R~
	if (((XEvent *)Pxevent)->type!=ClientMessage)                  //~var8R~
    	return GDK_FILTER_CONTINUE;                                //~var8R~
    clientevent=(XClientMessageEvent*)Pxevent;                     //~var8R~
    msgtype=XInternAtom(clientevent->display,XEVENT_CLIENT_MSG_TYPE,FALSE/*only if exist*/);//by csub:upostmsg//~var8R~
    if (clientevent->message_type!=msgtype)                        //~var8R~
    	return GDK_FILTER_CONTINUE;                                //~var8R~
    gxeview_clientevent(Gpview,clientevent,NULL);                  //~var8R~
    return GDK_FILTER_REMOVE;                                      //~var8R~
}//interface_msg_filter                                            //~var8R~
//*****************************************************************//~var8R~
void interface_add_filter(GtkWidget *Pwidget)                      //~var8R~
{                                                                  //~var8R~
    GdkWindow *window;                                             //~var8R~
//********************************                                 //~var8R~
    window=gtk_widget_get_window(Pwidget);                         //~var8R~
    gdk_window_add_filter(window,interface_msg_filter,Pwidget/*user data for callback*/);//~var8R~
}//interface_add_filter                                            //~var8R~
#ifndef CCC                                                        //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
#else                                                              //~vb7tI~
//*****************************************************************//~var8R~
//*from startup signal                                             //~var8R~
//*menu by uimanager                                               //~var8R~
//*****************************************************************//~var8R~
void interface_create_menu(GtkWidget *Ppframe,GtkWidget *Ppvbox)   //~var8R~
{                                                                  //~var8R~
    GtkWidget *menubar;                                            //~var8R~
    GtkUIManager *uim;                                             //~var8R~
    GtkActionGroup *ag;                                            //~var8R~
    GError *gerr=NULL;                                             //~var8R~
//*************************                                        //~var8R~
    ag=gtk_action_group_new("MenuActions");                        //~var8R~
    gtk_action_group_add_actions(ag,actions,G_N_ELEMENTS(actions),Ppframe/*userdata*/);//~var8R~
    uim=gtk_ui_manager_new();                                      //~var8R~
    gtk_ui_manager_insert_action_group(uim,ag,0/*pos*/);           //~var8R~
    g_object_unref(ag);                                            //~var8R~
    gtk_window_add_accel_group(GTK_WINDOW(Ppframe),gtk_ui_manager_get_accel_group(uim));//~var8R~
    gtk_ui_manager_add_ui_from_string(uim,main_menu_uiinfo,-1/*strlen*/,&gerr);//~var8R~
    if (gerr)                                                      //~var8R~
    {                                                              //~var8R~
        fprintf(stderr,"interface_create_menu uimanager err=%s\n",gerr->message);//~var8R~
        g_error_free(gerr);                                        //~var8R~
        return;                                                    //~var8R~
    }                                                              //~var8R~
    menubar=gtk_ui_manager_get_widget(uim,"/MainMenu");            //~var8R~
	dprintf("create_menu menubar=%p\n",menubar);                   //~var8R~
	gtk_container_add(GTK_CONTAINER(Ppvbox),menubar);              //~var8R~
    SpUIManager=uim;                                               //~var8R~
}//interface_create_menu                                           //~var8R~
#endif //!GTK_CHECK_VERSION(3,10,0)                                //~vb7tI~
#endif //!CCC                                                      //~var8R~
//void interface_create_appmenu(GtkApplication *Ppapp)             //~var8R~
//{                                                                //~var8R~
//    GtkBuilder *builder;                                         //~var8R~
//    GtkActionGroup *ag;                                          //~var8R~
//    GError *gerr=NULL;                                           //~var8R~
////*************************                                      //~var8R~
//    builder=gtk_builder_new();                                   //~var8R~
//    gtk_builder_add_from_string(builder,main_menu_uiinfo,-1/*strlen*/,&gerr);//~var8R~
//    if (gerr)                                                    //~var8R~
//    {                                                            //~var8R~
//        fprintf(stderr,"interface_create_appmenu err=%s\n",gerr->message);//~var8R~
//        g_error_free(gerr);                                      //~var8R~
//        return;                                                  //~var8R~
//    }                                                            //~var8R~
//    ag=GTK_ACTION_GROUP(gtk_builder_get_object(builder,"actions"));//~var8R~
//    gtk_application_set_menubar(Ppapp,G_MENU_MODEL(gtk_builder_get_object(builder,"MainMenu")));//~var8R~
//    g_object_unref(builder);                                     //~var8R~
//}//interface_create_appmenu                                      //~var8R~
//*****************************************************************//~var8R~
//#ifndef GTK3GTK3                                                 //~var8R~
//void interface_add_toolbar(GtkWidget *Pframe,GtkWidget *Ptoolbar)//~var8R~
//{                                                                //~var8R~
//    gtk_container_add(GTK_CONTAINER(Pframe),Ptoolbar);           //~var8R~
//}//interface_add_toolbar                                         //~var8R~
//#else                                                            //~var8R~
//#endif  //GTK3GTK3                                               //~var8R~
#ifdef BBB                                                         //~var8R~
//*****************************************************************//~var8R~
//*from startup signal                                             //~var8R~
//*GMenu has no method to access menuitem(use UIManager)           //~var8R~
//*****************************************************************//~var8R~
void interface_create_menu(GApplication *Ppapp)	                   //~var8R~
{                                                                  //~var8R~
    GtkBuilder *builder;                                           //~var8R~
    GMenuModel *menubar;                                           //~var8R~
    GError *gerr=NULL;                                             //~var8R~
//*************************                                        //~var8R~
	g_action_map_add_action_entries(G_ACTION_MAP(framewindow),actions,G_N_ELEMENTS(actions),framewindow/*userdata*/);//~var8R~
    builder=gtk_builder_new();                                     //~var8R~
    gtk_builder_add_from_string(builder,main_menu_uiinfo,-1/*strlen*/,&gerr);//~var8R~
    if (gerr)                                                      //~var8R~
    {                                                              //~var8R~
        fprintf(stderr,"interface_create_appmenu err=%s\n",gerr->message);//~var8R~
        g_error_free(gerr);                                        //~var8R~
        return;                                                    //~var8R~
    }                                                              //~var8R~
    menubar=(GMenuModel*)gtk_builder_get_object(builder,"MainMenu");//~var8R~
    gtk_application_set_menubar(GTK_APPLICATION(Ppapp),menubar);   //~var8R~
    Smenubuilder=builder;                                          //~var8R~
//  g_object_unref(builder);                                       //~var8R~
}//interface_create_menu                                           //~var8R~
#endif	//BBB                                                      //~var8R~
//*****************************************************************//~var8R~
//*from startup signal                                             //~var8R~
//*****************************************************************//~var8R~
void interface_create_window(GApplication *Ppapp)                  //~var8R~
{                                                                  //~var8R~
    GtkWidget *framewindow;                                        //~var8R~
//*************************                                        //~var8R~
	Ggtkappgxe=Ppapp;                                              //~var8R~
	framewindow=create_framewindow();                              //~var8R~
    gtk_widget_show_all(framewindow);                              //~var8R~
}//interface_create_window                                         //~var8R~//~vbdhR~
//*****************************************************************//~var8R~
//*from startup signal                                             //~var8R~
//*****************************************************************//~var8R~
void interface_quit()                                              //~var8R~
{                                                                  //~var8R~
	GtkApplication *papp;                                          //~var8R~
  	GtkWidget *win;                                                //~var8R~
  	GList *list, *next;                                            //~var8R~
//*************************                                        //~var8R~
	papp=GTK_APPLICATION(Ggtkappgxe);                              //~var8R~
  	list=gtk_application_get_windows(papp);                        //~var8R~
    dprintf("interface_quit destroy list=%p\n",list);              //~var8R~
  	while (list)                                                   //~var8R~
    {                                                              //~var8R~
      	win=list->data;                                            //~var8R~
      	next=list->next;                                           //~var8R~
    	dprintf("interface_quit destroy win=%p\n",win);            //~var8R~
      	gtk_widget_destroy(GTK_WIDGET(win));                       //~var8R~
      	list = next;                                               //~var8R~
    }                                                              //~var8R~
}//interface_quit                                                  //~var8R~
#endif  //OPTGTK3                                                  //~var8R~
#ifndef GGG                                                        //~vawFI~
//*****************************************************************//~vawFI~
//*set button-press signal handler to setup/preview menuitem on menubar//~vb7tR~
//*to open dialog by 1 click                                       //~vawFI~
//*****************************************************************//~vawFI~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
#else	//GTK3.10                                                  //~vb7tI~
void set_menubar_dialog_open_signal(void)                          //~vawFI~
{                                                                  //~vawFI~
#ifndef OPTGTK3                                                    //+var8~//~vawFI~
   	dprintf("preview widget=%p\n",menubar1_uiinfo[3].widget);      //~vawFI~
    dprintf("preview opendialog widget=%p\n",preview_menu_uiinfo[0].widget);//~vawFI~
   	dprintf("setup widget=%p\n",menubar1_uiinfo[2].widget);        //~vawFI~
// 	dprintf("setup opendialog widget=%p\n",setup_menu_uiinfo[0].widget);//~vawFI~//~vbdbR~
  	g_signal_connect ((gpointer)menubar1_uiinfo[3].widget,         //~vawFI~
                    "button-press-event",//by 1 click for menuitem on menubar//~vawFI~
                    G_CALLBACK (on_preview_button_press),          //~vawFI~
  					(gpointer)preview_menu_uiinfo[0].widget);  //openDialog menuitem//~vawFI~
#ifndef GGG                                                        //~vbdbR~
  	g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,         //~vawFI~
                    "button-press-event",//by 1 click for menuitem on menubar//~vawFI~
                    G_CALLBACK (on_setup_button_press),            //~vawFI~
  					(gpointer)setup_menu_uiinfo[0].widget);        //~vawFI~
#else                                                              //~vbdbI~
//    g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,       //~vbdbR~
//                    "button-press-event",//by 1 click for menuitem on menubar//~vbdbR~
//                    G_CALLBACK (on_setup_activate),              //~vbdbR~
//                    NULL/*func_data*/);                          //~vbdbR~
//      g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,     //~vbdbI~
//                    "button-press-event",//by 1 click for menuitem on menubar//~vbdbI~
//                    G_CALLBACK (on_setup_activate),              //~vbdbI~
//                    NULL/*func_data*/);                          //~vbdbI~
//      g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,     //~vbdbR~
//                    "click",//by 1 click for menuitem on menubar //~vbdbR~
//                    G_CALLBACK (on_setup_activate),              //~vbdbR~
//                    NULL/*func_data*/);                          //~vbdbR~
//      g_signal_connect ((gpointer)menubar1_uiinfo[3].widget,
//                    "click",//by 1 click for menuitem on menubar
//                    G_CALLBACK (on_setup_activate),
//                    NULL/*func_data*/);
//      g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,     //~vbdbR~
//                    "activate",//by 1 click for menuitem on menubar//~vbdbR~
//                    G_CALLBACK (on_setup_activate),              //~vbdbR~
//                    NULL/*func_data*/);                          //~vbdbR~
//      g_signal_connect ((gpointer)menubar1_uiinfo[2].widget,       //~vbdbR~
//                    "event",//by 1 click for menuitem on menubar   //~vbdbR~
//                    G_CALLBACK (on_setup_activate),                //~vbdbR~
//                    NULL/*func_data*/);                            //~vbdbR~
#endif                                                             //~vbdbI~
#else  //OPTGTK3                                                   //~vawFI~
	GtkWidget *pwidgetm,*pwidgetmi;                                //~vawFI~
//*************************                                        //~vawFI~
   	dprintf("setup widget uimgr=%p\n",SpUIManager);                //~vb7tR~
    pwidgetm=gtk_ui_manager_get_widget(SpUIManager,"/MainMenu/Setup");//~vawFI~
    pwidgetmi=gtk_ui_manager_get_widget(SpUIManager,"/MainMenu/Setup/SetupDialog");//~vawFI~
   	dprintf("setup widget menu=%p,menuitem=%p\n",pwidgetm,pwidgetmi);//~vawFI~
  	g_signal_connect ((gpointer)pwidgetm,                          //~vawFI~
                    "button-press-event",//by 1 click for menuitem on menubar//~vawFI~
                    G_CALLBACK (on_setup_button_press),            //~vawFI~
  					(gpointer)pwidgetmi);  //openDialog menuitem   //~vawFI~
    pwidgetm=gtk_ui_manager_get_widget(SpUIManager,"/MainMenu/Preview");//~vawFI~
    pwidgetmi=gtk_ui_manager_get_widget(SpUIManager,"/MainMenu/Preview/PreviewDialog");//~vawFI~
   	dprintf("preview widget menu=%p,menuitem=%p\n",pwidgetm,pwidgetmi);//~vawFI~
  	g_signal_connect ((gpointer)pwidgetm,                          //~vawFI~
                    "button-press-event",//by 1 click for menuitem on menubar//~vawFI~
                    G_CALLBACK (on_preview_button_press),          //~vawFI~
  					NULL);  //openDialog menuitem   //~vawFI~      //~vbdbR~
#endif //OPTGTK3                                                   //~vawFI~
}//set_menubar_dialog_open_signal                                  //~vb7tR~
#endif //GTK3.10                                                   //~vb7tI~
#endif  //GGG                                                      //~vawFI~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vb7tI~
#ifdef QQQ   //done at actinit by gtk_accel_map_add_entry()+gtkwidget_set_accel_path()//~vbdhI~
//*****************************************************************//~vb7tI~
//*from startup signal                                             //~vb7tI~
//*menu by uimanager                                               //~vb7tI~
//*****************************************************************//~vb7tI~
void interface_addaccel(GtkAccelGroup *Ppag,char *Paccel,GtkWidget *Pmenuitem,char *Pname)//~vb7tI~
{                                                                  //~vb7tI~
	char *pc;                                                      //~vb7tI~
	char *pc2;                                                     //~vbd2I~
    int mask=0,key;                                                //~vb7tI~
//*************************                                        //~vb7tI~
    if (!Paccel||!*Paccel)                                         //~vb7tR~
    	return;                                                    //~vb7tI~
	if (pc=strstr(Paccel,UACC_CONTROL_MASK),pc)                    //~vb7tI~
    {                                                              //~vb7tI~
	  if (pc2=strstr(Paccel,UACC_SHIFT_MASK),pc2)                  //~vbd2R~
      {                                                            //~vbd2I~
    	mask=GDK_CONTROL_MASK|GDK_SHIFT_MASK;                      //~vbd2I~
        key=*(pc+strlen(pc)-1);                                    //~vbd2I~
      }                                                            //~vbd2I~
      else                                                         //~vbd2I~
      {                                                            //~vbd2I~
    	mask=GDK_CONTROL_MASK;                                     //~vb7tI~
        key=*(pc+sizeof(UACC_CONTROL_MASK)-1);                     //~vb7tI~
      }                                                            //~vbd2I~
    }                                                              //~vb7tI~
    else                                                           //~vb7tI~
        key=*pc;                                                   //~vb7tI~
#ifdef QQQ   //done at actinit by gtk_accel_map_add_entry          //~vbdhI~
    gtk_widget_add_accelerator(Pmenuitem,"activate",Ppag,key,mask,GTK_ACCEL_VISIBLE);//~vb7tR~
#else                                                              //~vbdhI~
    gxemfrm_actinit_menuitem(Ppag,Pmenuitem,key,mask);             //~vbdhR~
#endif                                                             //~vbdhM~
	dprintf("interface_addaccell name=%s,accell=%s,mask=%x,key=%c,menu=%p\n",Pname,Paccel,mask,key,Pmenuitem);//~vb7tI~//~vbdhR~
}//interface_addaccel                                              //~vb7tI~
#endif   //QQQ                                                     //~vbdhI~
//*****************************************************************
//*from startup signal
//*menu by uimanager
//*****************************************************************
GtkWidget* interface_create_menubar(GtkWidget *framewindow)        //~vb7tI~
{
    GtkWidget *menubar;
    GtkWidget *mitem,*submenu=0;                                   //~vb7tR~
    int entno,ii;                                                  //~vb7tI~
    UActionEntry *puae;                                            //~vb7tI~
    GtkAccelGroup *pag;                                            //~vb7tI~
//*************************
	pag=gtk_accel_group_new();                                     //~vb7tI~
    Gpag=pag;	//use at gxemfrm:actinit                           //~vbdhI~
    gtk_window_add_accel_group(GTK_WINDOW(framewindow),pag);       //~vb7tI~
	menubar=gtk_menu_bar_new();                                    //~vb7tI~
	entno=(int)(sizeof(actions)/sizeof(UActionEntry));             //~vb7tI~
    for (ii=0,puae=actions;ii<entno;ii++,puae++)                   //~vb7tI~
    {                                                              //~vb7tI~
      if (puae->label && strchr(puae->label,'_'))                  //~vbdhI~
#ifdef QQQ                                                        //~vbdhI~//~vbdiR~
      {                                                            //~vbdhI~
        mitem=gtk_menu_item_new_with_mnemonic(puae->label);        //~vb7tR~
		dprintf("with_mnemonic label=%s\n",puae->label);           //~vbdhI~
      }                                                            //~vbdhI~
#else                                                              //~vbdhI~
      {                                                            //~vbdhI~
        mitem=gtk_menu_item_new_with_label(puae->label);           //~vbdhI~
        gtk_menu_item_set_use_underline((GtkMenuItem*)mitem,TRUE);               //~vbdhI~//~vbdjR~
		dprintf("with_label label=%s\n",puae->label);              //~vbdhI~
      }                                                            //~vbdhI~
#endif                                                             //~vbdhI~
      else                                                         //~vbdhI~
        mitem=gtk_menu_item_new_with_label(puae->label);           //~vbdhI~
    	if (!*puae->name)	//separator                            //~vb7tM~
        {                                                          //~vb7tM~
    		mitem=gtk_separator_menu_item_new();                   //~vb7tM~
    		gtk_menu_shell_append(GTK_MENU_SHELL(submenu),mitem);  //~vb7tM~
			dprintf("create_menu separator widget=%p\n",mitem);    //~vb7tM~
        }                                                          //~vb7tM~
        else                                                       //~vb7tI~
    	if (!puae->callback)	//has submenu                      //~vb7tR~
        {                                                          //~vb7tI~
		    submenu=gtk_menu_new();                                //~vb7tI~
		    gtk_menu_item_set_submenu(GTK_MENU_ITEM(mitem),submenu);//~vb7tI~
		    gtk_menu_shell_append(GTK_MENU_SHELL(menubar),mitem);  //~vb7tI~
			dprintf("create_menu top=%s,widget=%p\n",puae->name,mitem);//~vb7tI~
        }                                                          //~vb7tI~
        else                                                       //~vb7tI~
        {                                                          //~vb7tI~
	    	if (!puae->accelerator)	//top menu                     //~vb7tR~
            {                                                      //~vb7tI~
	    		gtk_menu_shell_append(GTK_MENU_SHELL(menubar),mitem);//~vb7tI~
				dprintf("interface_create_menubar:topmenu item=%s,widget=%p\n",puae->name,mitem);//~vb7tR~
  				g_signal_connect ((gpointer)mitem,                 //~vb7tI~
                    "button-press-event",//by 1 click for menuitem on menubar//~vb7tI~
                    G_CALLBACK (puae->callback),                   //~vb7tI~
  					NULL);                                         //~vb7tI~
				dprintf("interface_create_menubar:signal connect to button-press-event ,cb=%p\n",puae->callback);//~vb7tI~
            }                                                      //~vb7tI~
            else                                                   //~vb7tI~
            {                                                      //~vb7tI~
    			gtk_menu_shell_append(GTK_MENU_SHELL(submenu),mitem);//~vb7tR~
				dprintf("interface_create_menubar:submenu item=%s,widget=%p\n",puae->name,mitem);//~vb7tR~
#ifdef QQQ                                                         //~vbdhI~
                interface_addaccel(pag,(char *)(puae->accelerator),mitem,(char*)(puae->name));//~vb7tI~
#endif                                                             //~vbdhI~
            }                                                      //~vb7tI~
		  	g_signal_connect ((gpointer)mitem,                     //~vb7tI~
                    "activate",                                    //~vb7tR~
                    G_CALLBACK (puae->callback),                   //~vb7tI~
  					NULL);  //openDialog menuitem                  //~vb7tI~
            dprintf("interface_create_menubar:signal connect to activate ,cb=%p\n",puae->callback);//~vb7tI~
        }                                                          //~vb7tI~
		puae->menuitem=mitem;                                      //~vb7tI~
    }                                                              //~vb7tI~
    return menubar;                                                //~vb7tI~
}//interface_create_menubar                                        //~vb7tI~
//*****************************************************************//~vb7tI~
//*signal connect for menu item from GRADE_HOOKUP_OBJECT_MENU      //~vb7tI~
//*****************************************************************//~vb7tI~
UActionEntry *srch_menu(char *Pmenuid)                             //~vb7tR~
{                                                                  //~vb7tI~
    int entno,ii;                                                  //~vb7tI~
    UActionEntry *puae;                                            //~vb7tI~
//*************************                                        //~vb7tI~
	entno=(int)(sizeof(actions)/sizeof(UActionEntry));             //~vb7tI~
    for (ii=0,puae=actions;ii<entno;ii++,puae++)                   //~vb7tI~
    {                                                              //~vb7tI~
        if (!strcmp(Pmenuid,puae->name))                           //~vb7tR~
        	return puae;                                           //~vb7tI~
    }                                                              //~vb7tI~
    return 0;                                                      //~vb7tI~
}//srch_menu                                                       //~vb7tR~
//*****************************************************************//~vb7tI~
//*signal connect for menu item from GRADE_HOOKUP_OBJECT_MENU      //~vb7tI~
//*****************************************************************//~vb7tI~
void hookup_menu(GtkWidget *framewindow,char *Pmenuid,char *Phookupkey)//~vb7tI~
{                                                                  //~vb7tI~
    UActionEntry *puae;                                            //~vb7tI~
//*************************                                        //~vb7tI~
	puae=srch_menu(Pmenuid);                                       //~vb7tI~
	dprintf("menu hookup Pmenuid=%s,key=%s,puae=%p\n",Pmenuid,Phookupkey,puae);//~vb7tI~
    if (!puae)                                                     //~vb7tR~
    	return;                                                    //~vb7tR~
	GLADE_HOOKUP_OBJECT(framewindow,puae->menuitem,Phookupkey);    //~vb7tR~
	dprintf("menu hookup name=%s,label=%s,hookup=%s,widget=%p\n",puae->name,puae->label,Phookupkey,puae->menuitem);//~vb7tR~
}//hookup_menu                                                     //~vb7tI~
//*****************************************************************
//*from startup signal
//*menu by uimanager
//*****************************************************************
void interface_create_menu(GtkWidget *Ppframe,GtkWidget *Ppvbox)   //~vb7tI~
{
    GtkWidget *menubar;
//*************************
	menubar=interface_create_menubar(Ppframe);                     //~vb7tI~
//  ag=gtk_action_group_new("MenuActions");                        //~vb7tR~
//  gtk_action_group_add_actions(ag,actions,G_N_ELEMENTS(actions),Ppframe/*userdata*/);//~vb7tR~
//  uim=gtk_ui_manager_new();                                      //~vb7tR~
//  gtk_ui_manager_insert_action_group(uim,ag,0/*pos*/);           //~vb7tR~
//  g_object_unref(ag);                                            //~vb7tR~
//  gtk_window_add_accel_group(GTK_WINDOW(Ppframe),gtk_ui_manager_get_accel_group(uim));//~vb7tR~
//  gtk_ui_manager_add_ui_from_string(uim,main_menu_uiinfo,-1/*strlen*/,&gerr);//~vb7tR~
//  if (gerr)                                                      //~vb7tR~
//  {                                                              //~vb7tR~
//      fprintf(stderr,"interface_create_menu uimanager err=%s\n",gerr->message);//~vb7tR~
//      g_error_free(gerr);                                        //~vb7tR~
//      return;                                                    //~vb7tR~
//  }                                                              //~vb7tR~
	dprintf("create_menu menubar=%p\n",menubar);
	gtk_container_add(GTK_CONTAINER(Ppvbox),menubar);
}//interface_create_menu
#endif  //GTK3.10                                                  //~vb7tI~
#ifndef SSS                                                        //~vbdjI~
#ifndef OPTGTK3                                                    //+var8~//~vbdjI~
//******************************************************           //~vbdjI~
char *interface_getmenuitemlabel(int Pmenuid) //by ID_FILE_NEW etc //~vbdjR~
{                                                                  //~vbdjI~
    const char *plabel=0;                                          //~vbdjR~
//***************                                                  //~vbdjI~
    switch(Pmenuid)                                                //~vbdjI~
    {                                                              //~vbdjI~
	case ID_FILE_NEW:                                              //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_NEW].label;                 //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_OPEN:                                             //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_OPEN].label;                //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_SAVE:                                             //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_SAVE].label;                //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_FILE_SAVEAS:                                           //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_SAVEAS].label;              //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_PRINT:                                            //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_PRINT].label;               //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_PRTSCR:                                           //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_PRTSCR].label;              //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_HOME:                                             //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_HOME].label;                //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_TERMINAL:                                         //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_TERM].label;                //~vbdjR~
        break;                                                     //~vbdjI~
	case ID_FILE_EXIT:                                             //~vbdjI~
		plabel=file_menu_uiinfo[UIINFO_EXIT].label;                //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_CUT:                                              //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_CUT].label;                 //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_CLEAR:                                            //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_CLEAR].label;               //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_COPY:                                             //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_COPY].label;                //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_PASTE:                                            //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_PASTE].label;               //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_PASTE_REP:                                        //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_PASTE_REP].label;           //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_PASTE_V:                                          //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_PASTE_V].label;             //~vbdjR~
        break;                                                     //~vbdjI~
    case ID_EDIT_SELECTALL:                                        //~vbdjI~
		plabel=edit_menu_uiinfo[UIINFO_SELECTALL].label;           //~vbdjR~
        break;                                                     //~vbdjI~
    }                                                              //~vbdjI~
    return (char*)plabel;                                          //~vbdjR~
}//interface_getmenuitemlabel                                      //~vbdjI~
#endif // OPTGTK3                                                    //+var8~//~vbdjI~
#endif //SSS                                                       //~vbdjI~
