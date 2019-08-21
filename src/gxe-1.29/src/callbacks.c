//*CID://+vbd2R~:                             update#=  256;       //+vbd2R~
//***************************************************************************//~v66aI~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //+vbd2I~
//vb7t:170128 (gxe)Gtk3 deprecated                                 //~vb7tI~
//vawF:140621 (BUG)On Ubuntu13.4;when global menu,menuitem on menubar show "activate" menuitem and no effect.//~vawFI~
//var8:140127 gtk3 suppott                                         //~var8I~
//vap1:131220 (LNX)configure aupports NOPRINT for RedHat5.8        //~vap1I~
//vamb:131002 re-draw HWmargin when form changed                   //~vambI~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//vak6:130905 compiler warning;never executes                      //~vak6I~
//va6y:000706 CUPs default printer is not same as gnome default    //~va6yI~
//v73t:070125 cross-hair ruler support by Shift+Ctl+lbuton         //~v73tI~
//v71s:061022 (WXE/XXE)err msg when drag canceled by mouse lb release//~v71sI~
//v686:060323 dnd support by paste(edit:pastev,ins=paste-ins,rep=paste-rep)//~v686I~
//v685:060322 dnd support "file copy into the dir slected" and even in inter-split-screen.//~v685I~
//v66p:051026 (XXE)std paste support                               //~v66pI~
//v66a:050827 (XXE)printf used,so change to dprintf which change to nop by DUMMYPRINTF//~v66aI~
//***************************************************************************//~v66aI~
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>
#else                                                              //~var8R~
#include <gtk/gtk.h>                                               //~var8R~
#include <gdk/gdkx.h>                                              //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0I~
	#else    //!GTKPRINT                                           //~vam0I~
#include <libgnomeprint/gnome-print.h>                             //~5803I~
#include <libgnomeprint/gnome-print-job.h>                         //~5803I~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif                                                             //~vam0I~

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "ulib.h"                                                  //~5613I~
#include "gxe.h"                                                   //~5803I~
#include "xxedef.h"                                                //~5613I~
#include "xxeres.h"                                                //~var8R~
#include "gxeview.h"                                               //~5728I~
#include "gxemfrm.h"                                               //~5613I~
#include "gxedlg.h"                                                //~5604I~
#include "gxepage.h"                                               //~5703I~
#include "xxefile.h"                                               //~5625I~
#include "xxecsub.h"                                               //~var8R~

#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
    #define EXPORT_CALLBACK G_MODULE_EXPORT                        //~var8R~
#endif                                                             //~var8R~
//*********************************                                //~5604I~
//*file                                                            //~5604I~
//*********************************                                //~5604I~
void
on_new_activate                       (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_FILE_NEW));//~var8R~
#endif                                                             //~var8R~
	dprintf("on_new_activate menuitem=%p\n",GTK_MENU_ITEM(menuitem));//~var8R~
	gxedoc_OnNewDocument(menuitem,user_data);                      //~5604R~
    return;                                                        //~5603R~
}
void
on_open_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_FILE_OPEN));//~var8R~
#endif                                                             //~var8R~
	gxedoc_OnOpenDocument(menuitem,user_data);                     //~5728R~
    return;                                                        //~5603I~
}
void
on_save_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
	gxedoc_OnSaveDocument();                                       //~5603I~
    return;                                                        //~5603I~
}
void
on_saveas_activate                   (GtkMenuItem     *menuitem,   //~5603R~
                                        gpointer         user_data)
{
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_FILE_SAVEAS));//~var8R~
#endif                                                             //~var8R~
	gxedoc_OnSaveAsDocument(menuitem,user_data);                   //~5604R~
    return;                                                        //~5603R~
}
void
on_print_activate                      (GtkMenuItem     *menuitem, //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnFilePrint();                                         //~5717R~
    return;                                                        //~5603R~
}
void
on_prtscr_activate                   (GtkMenuItem     *menuitem,   //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnFileScrprt();                                        //~5717R~
    return;                                                        //~5603I~

}
void
//***********************************************************      //~var8R~
//*Preview                                                         //~var8R~
//***********************************************************      //~var8R~
on_preview_activate                    (GtkMenuItem     *menuitem, //~5603R~
                                        gpointer         user_data)
{
#ifdef GGG                                                         //~vawFI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_PAGE_SETUP));//~var8R~
#endif                                                             //~var8R~
#endif                                                             //~vawFI~
	dprintf("on_preview_activate\n");                              //~var8R~
	gxeview_OnPageSetup(menuitem,user_data);                       //~5609R~
	return;                                                        //~5603R~
}
#ifndef OPTGTK3                                                    //~var8R~
void                                                               //~5603I~
on_preview2_activate                    (GtkMenuItem     *menuitem,//~5603I~
                                        gpointer         user_data)//~5603I~
{                                                                  //~5603I~
	dprintf("on_preview2_activate\n");                             //~vb7tR~
	gxeview_OnPageSetup(menuitem,user_data);                       //~5609I~
	return;                                                        //~5603I~
}                                                                  //~5603I~
#else                                                              //~var8R~
#endif                                                             //~var8R~
//void                                                             //~var8R~
//on_preview_select(GtkMenuItem     *menuitem,                     //~var8R~
//                                        gpointer         user_data)//~var8R~
//{                                                                //~var8R~
//    dprintf("on_preview_select\n");                              //~var8R~
//    uactivate_menuitem(STRID_PAGE_SETUP_DIALOG);                 //~var8R~
//    return;                                                      //~var8R~
//}                                                                //~var8R~
//void                                                             //~var8R~
//on_previewdialog_activate                      (GtkMenuItem     *menuitem,//~var8R~
//                                        gpointer         user_data)//~var8R~
//{                                                                //~var8R~
//    dprintf("on_previewdialog_activate\n");                      //~var8R~
//    gxeview_OnPageSetup(menuitem,user_data);                     //~var8R~
//    return;                                                      //~var8R~
//}                                                                //~var8R~
void                                                               //~5604M~
on_home_activate                       (GtkMenuItem     *menuitem, //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxeview_OnEditExplorer();                                      //~5604M~
	return;                                                        //~5604M~
}                                                                  //~5604M~
void                                                               //~5604M~
on_terminal_activate                   (GtkMenuItem     *menuitem, //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxeview_OnFileDos();                                           //~5604M~
	return;                                                        //~5604M~
}                                                                  //~5604M~
void
on_exit_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnExit();                                              //~5603I~
}
//*********************************                                //~5604I~
//*edit                                                            //~5604I~
//*********************************                                //~5604I~
void                                                               //+vbd2I~
on_selectall_activate                       (GtkMenuItem     *menuitem,//+vbd2I~
                                        gpointer         user_data)//+vbd2I~
{                                                                  //+vbd2I~
	gxeview_OnEditSelectAll();                                     //+vbd2I~
	return;                                                        //+vbd2I~
}                                                                  //+vbd2I~
void
on_cut_activate                       (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnEditCut();                                           //~5603I~
	return;                                                        //~5603R~
}
void
on_copy_activate                      (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnEditCopy();                                          //~5603I~

}
void
on_clear_activate                     (GtkMenuItem     *menuitem,  //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnEditClear();                                         //~5603I~
	return;                                                        //~5603R~
}
void
on_paste_insert_activate                     (GtkMenuItem     *menuitem,//~5603R~
                                        gpointer         user_data)
{
	gxeview_OnEditPasteIns();                                      //~5603I~
    return;                                                        //~5603I~
}
void
on_paste_replace_activate           (GtkMenuItem     *menuitem,    //~5603R~
                                        gpointer         user_data)
{
	gxeview_OnEditPasteRep();                                      //~5603I~
}
void                                                               //~v66pM~
on_PasteV_activate                     (GtkMenuItem     *menuitem, //~v66pM~
                                        gpointer         user_data)//~v66pM~
{                                                                  //~v66pM~
	gxeview_OnEditPasteV();                                        //~v66pI~
}                                                                  //~v66pM~
//*********************************                                //~5604I~
//*setup                                                           //~5604I~
//*********************************                                //~5604I~
void                                                               //~5610M~
on_setup_activate                      (GtkMenuItem     *menuitem, //~5610M~
                                        gpointer         user_data)//~5610M~
{                                                                  //~5610M~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_SETUP));//~var8R~
#endif                                                             //~var8R~
	dprintf("on_setup_activate menuitem=%p\n",GTK_MENU_ITEM(menuitem));//~var8R~
//#ifdef AAA                                                       //~var8R~
	gxeview_OnOptions(menuitem,user_data);                         //~5610M~
//#else                                                            //~var8R~
//    uactivate_menuitem(STRID_SETUP_DIALOG);                      //~var8R~
//#endif                                                           //~var8R~
	return;                                                        //~5610M~
}                                                                  //~5610M~
//#ifdef AAA                                                       //~var8R~
//void                                                             //~var8R~
//on_setup_select(GtkMenuItem     *menuitem,                       //~var8R~
//                                        gpointer         user_data)//~var8R~
//{                                                                //~var8R~
//    GtkWidget *pmenu;                                            //~var8R~
//    dprintf("on_setup_select menu=%p\n",menuitem);               //~var8R~
//    pmenu=lookup_widget(GTK_WIDGET(Gpframe),STRID_SETUP);        //~var8R~
//    dprintf("on_setup_select lookup menu=%p\n",pmenu);           //~var8R~
//    dprintf("on_setup_select imagemenuitem menu=%p\n",GTK_IMAGE_MENU_ITEM(pmenu));//~var8R~
//    gtk_menu_popdown(GTK_MENU(pmenu));                           //~var8R~
//    uactivate_menuitem(STRID_SETUP_DIALOG);                      //~var8R~
//    return;                                                      //~var8R~
//}                                                                //~var8R~
//#endif                                                           //~var8R~
//void                                                             //~var8R~
//on_setupdialog_activate                      (GtkMenuItem     *menuitem,//~var8R~
//                                        gpointer         user_data)//~var8R~
//{                                                                //~var8R~
//    dprintf("on_setupdialog_activate\n");                        //~var8R~
//    gxeview_OnOptions(menuitem,user_data);                       //~var8R~
//    gtk_menu_item_deselect(menuitem);                            //~var8R~
//    return;                                                      //~var8R~
//}                                                                //~var8R~
//*********************************                                //~5604I~
//*help                                                            //~5604I~
//*********************************                                //~5604I~
void                                                               //~5826M~
on_helpdoc_activate                    (GtkMenuItem     *menuitem, //~5826M~
                                        gpointer         user_data)//~5826M~
{                                                                  //~5826M~
	gxemfrm_OnHelp();                                              //~5826I~
	return;                                                        //~5826I~
}                                                                  //~5826M~
void
on_version_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3 parm:menuitem==GtkAction                         //~var8R~
	menuitem=GTK_MENU_ITEM(lookup_widget(GTK_WIDGET(Gpframe),STRID_VERSION));//~var8R~
#endif                                                             //~var8R~
	gxedlg_about_create(menuitem,user_data);                       //~5604R~
	return;                                                        //~5603R~
}
//*********************************                                //~5604I~
//*toolbar                                                         //~5604I~
//*********************************                                //~5604I~
void                                                               //~5728M~
on_button_open_clicked                 (GtkButton       *button,   //~5728M~
                                        gpointer         user_data)//~5728M~
{                                                                  //~5728M~
	gxedoc_OnOpenDocument(0,user_data);	//0 button id              //~5728I~
    return;                                                        //~5728I~
}                                                                  //~5728M~
void
on_button_save_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	gxedoc_OnSaveDocument();                                       //~5604R~
    return;                                                        //~5603R~
}
void
on_button_end_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditEnd();                                           //~5603I~
}
void
on_button_cancel_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditCancel();                                        //~5603I~

}
void
on_button_print_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnFilePrint();                                         //~5717R~
	return;                                                        //~5603R~
}
void
on_button_home_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditExplorer();                                      //~5603I~
	return;                                                        //~5603R~
}
void
on_button_terminal_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnFileDos();                                           //~5603I~
	return;                                                        //~5603R~
}
void
on_button_cut_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditCut();                                           //~5603I~
	return;                                                        //~5603R~
}
void
on_button_copy_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditCopy();                                          //~5603I~
	return;                                                        //~5603R~
}
void
on_button_clear_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditClear();                                         //~5603I~
	return;                                                        //~5603R~
}
void
on_button_pasteins_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditPasteIns();                                      //~5603I~
	return;                                                        //~5603R~
}
void
on_button_pasterep_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	gxeview_OnEditPasteRep();                                      //~5603I~
	return;                                                        //~5603R~
}
void                                                               //~v66pM~
on_button_pasteV_clicked               (GtkButton       *button,   //~v66pM~
                                        gpointer         user_data)//~v66pM~
{                                                                  //~v66pM~
	gxeview_OnEditPasteV();                                        //~v66pI~
	return;                                                        //~v66pI~
}                                                                  //~v66pM~
//*******************************************************************//~5604I~
//*file dialog                                                     //~5604I~
//*******************************************************************//~5604I~
#ifndef OPTGTK3	//gtk3 is by filechooserdialog                     //~var8R~
void                                                               //~5604M~
on_file_button_ok_clicked              (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	xxefile_dlgOnOK();                                             //~5703R~
    return;                                                        //~5604I~
}                                                                  //~5604M~
void
on_file_button_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	xxefile_dlgOnCancel();                                         //~5703R~
    return;                                                        //~5604R~
}
#endif                                                             //~var8R~
//*******************************************************************//~5604M~
//*font dialog                                                     //~5604M~
//*******************************************************************//~5604M~
#ifndef OPTGTK3	//gtk3 is by filechooserdialog                     //~var8R~
void                                                               //~5604M~
on_font_button_ok_clicked              (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxedlg_Font_OnOK(button,user_data);                            //~5604M~
	return;                                                        //~5604M~
}                                                                  //~5604M~
void                                                               //~5604M~
on_font_button_cancel_clicked          (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxedlg_Font_OnCancel(button,user_data);                        //~5604M~
    return;                                                        //~5604M~
}                                                                  //~5604M~
void                                                               //~5604M~
on_font_button_apply_clicked           (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxedlg_Font_OnApply(button,user_data);                         //~5604M~
    return;                                                        //~5604M~
}                                                                  //~5604M~
#endif                                                             //~var8R~
//*******************************************************************//~5604I~
//*color dialog                                                    //~5604I~
//*******************************************************************//~5604I~
#ifndef OPTGTK3                                                    //~var8R~
void
on_color_button_ok_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
	gxedlg_Color_OnOK(button,user_data);                           //~5604I~
    return;                                                        //~5604I~
}
void
on_color_button_cancel_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	gxedlg_Color_OnCancel(button,user_data);                       //~5604I~
    return;                                                        //~5604I~
}
#else   //OPTGTK3                                                  //~var8R~
#endif                                                             //~var8R~
//*******************************************************************//~5604I~
//*option dialog                                                   //~5604R~
//*******************************************************************//~5604I~
                                                                   //~5604M~
void                                                               //~5604M~
on_option_button_cancel_clicked        (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxedlg_option_OnCancel(button,user_data);                      //~5610R~
    return;                                                        //~5604I~
}                                                                  //~5604M~
void                                                               //~5604M~
on_option_button_ok_clicked            (GtkButton       *button,   //~5604M~
                                        gpointer         user_data)//~5604M~
{                                                                  //~5604M~
	gxedlg_option_OnOK(button,user_data);                          //~5610R~
    return;                                                        //~5610I~
}                                                                  //~5604M~
void                                                               //~5610M~
on_option_button_change_font_clicked   (GtkButton       *button,   //~5610M~
                                        gpointer         user_data)//~5610M~
{                                                                  //~5610M~
	gxedlg_option_fontstyle(button,user_data);                     //~5610I~
    return;                                                        //~5610I~
}                                                                  //~5610M~
void                                                               //~5610M~
on_option_button_color_change_clicked  (GtkButton       *button,   //~5610M~
                                        gpointer         user_data)//~5610M~
{                                                                  //~5610M~
	gxedlg_option_color_create(button,user_data);                  //~5610R~
    return;                                                        //~5610I~
}                                                                  //~5610M~
gboolean                                                           //~5610M~
on_option_drawingarea_colorsample_configure_event                  //~5610M~
                                        (GtkWidget       *widget,  //~5610M~
                                        GdkEventConfigure *event,  //~5610M~
                                        gpointer         user_data)//~5610M~
{                                                                  //~5610M~
    dprintf("callbacks on_drawingarea_colorsample_configure_event event w=%d,h=%d\n",event->width,event->height);//~var8R~
	gxedlg_option_drawingarea_configure(widget);                   //~5610I~
  	return FALSE;                                                  //~5610I~
}                                                                  //~5610M~
#ifndef OPTGTK3                                                    //~var8R~
gboolean                                                           //~5610M~
on_option_drawingarea_colorsample_expose_event                     //~5610M~
                                        (GtkWidget       *widget,  //~5610M~
                                        GdkEventExpose  *event,    //~5610M~
                                        gpointer         user_data)//~5610M~
{                                                                  //~5610M~
	gxedlg_option_drawingarea_expose(widget,event);                //~5610R~
	return FALSE;                                                  //~5610I~
}                                                                  //~5610M~
#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_option_drawingarea_colorsample_draw(GtkWidget *widget,cairo_t *Pcr,gpointer user_data)//~var8R~
{                                                                  //~var8R~
	gxedlg_option_drawingarea_draw(widget,Pcr);                    //~var8R~
	return FALSE;                                                  //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
//*******************************************************************//~5604I~
//*about dialog                                                    //~5604I~
//*******************************************************************//~5604I~
void
on_about_button_close_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	gxedlg_About_OnClose(button,user_data);                        //~5604I~
    return;                                                        //~5604I~
}

//*******************************************************************//~5609I~
//*print dialog                                                    //~5609I~
//*******************************************************************//~5609I~
void
on_page_font_change_clicked            (GtkButton       *button,   //~5716M~
                                        gpointer         user_data)
{
	gxepage_fontstyle();                                           //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_preview_print_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPreview();                                           //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_np_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPreviewNextpage();                                   //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_pp_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPreviewprevpage();                                   //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_preview_prtscr_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPreviewprtscr();                                     //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_print_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPrint();                                             //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_prtscr_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnPrtscr();                                            //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_save_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnOk();                                                //~5716R~
    return;                                                        //~5609I~
}
void
on_page_button_cancel_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
	gxepage_OnCancel();                                            //~5716R~
    return;                                                        //~5609I~
}
void                                                               //~5716M~
on_page_chkbutton_bycellhw_toggled     (GtkToggleButton *togglebutton,//~5716M~
                                        gpointer         user_data)//~5716M~
{                                                                  //~5716M~
	gxepage_OnCheckpfontsz();                                      //~5716I~
    return;                                                        //~5716I~
}                                                                  //~5716M~
                                                                   //~5716M~
                                                                   //~5716M~
void                                                               //~5716M~
on_page_chkbutton_2p_toggled           (GtkToggleButton *togglebutton,//~5716M~
                                        gpointer         user_data)//~5716M~
{                                                                  //~5716M~
	gxepage_OnCheck2p();                                           //~5716I~
    return;                                                        //~5716I~
}                                                                  //~5716M~
void                                                               //~5716M~
on_page_chkbutton_header_toggled       (GtkToggleButton *togglebutton,//~5716M~
                                        gpointer         user_data)//~5716M~
{                                                                  //~5716M~
	gxepage_OnCheckHeader();                                       //~5716I~
    return;                                                        //~5716I~
}                                                                  //~5716M~
void                                                               //~5716M~
on_page_chkbutton_footer_toggled       (GtkToggleButton *togglebutton,//~5716M~
                                        gpointer         user_data)//~5716M~
{                                                                  //~5716M~
	gxepage_OnCheckFooter();                                       //~5716I~
    return;                                                        //~5716I~
}                                                                  //~5716M~
void                                                               //~5716M~
on_page_entry_pageno_editing_done      (GtkCellEditable *celleditable,//~5716M~
                                        gpointer         user_data)//~5716M~
{                                                                  //~5716M~
	gxepage_OnChangeEditCurpage();                                 //~5716I~
    return;                                                        //~5716I~
}                                                                  //~5716M~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_page_previewarea_draw(GtkWidget *widget,cairo_t *Pcr,gpointer user_data)//~var8R~
{                                                                  //~var8R~
	gxepage_previewarea_draw(widget,Pcr);                          //~var8R~
	return FALSE;                                                  //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
                                                                   //~5716M~
//*******************************************************************//~5610I~
//*main draw area                                                  //~5610I~
//*******************************************************************//~5610I~
gboolean
on_maindraw_configure_event            (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{
	gxeview_configure(widget,event);                               //~5610I~
  	return FALSE;                                                  //~5610R~
}
#ifndef OPTGTK3                                                    //~var8R~
gboolean
on_maindraw_expose_event               (GtkWidget       *widget,
                                        GdkEventExpose  *event,
                                        gpointer         user_data)
{
	gxeview_expose(widget,event);                                  //~5610I~
  	return FALSE;                                                  //~5610R~
}
#else   //OPTGTK3                                                  //~var8R~
gboolean                                                           //~var8R~
on_maindraw_draw(GtkWidget *widget,cairo_t *Pcr,gpointer user_data)//~var8R~
{                                                                  //~var8R~
	gxeview_draw(widget,Pcr);                                      //~var8R~
  	return FALSE;                                                  //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
gboolean
on_maindraw_button_press_event         (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	return gxeview_buttondown(widget,event);                       //~5610I~
}
gboolean
on_maindraw_button_release_event       (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
	return gxeview_buttonup(widget,event);                         //~5610I~
}
gboolean                                                           //~5623M~
on_maindraw_scroll_event               (GtkWidget       *widget,   //~5623M~
                                        GdkEvent        *event,    //~5623R~
                                        gpointer         user_data)//~5623M~
{                                                                  //~5623M~
	return gxeview_mousewheel(widget,(GdkEventScroll*)event);      //~5623R~
//	return FALSE;                                                  //~vak6R~
}                                                                  //~5623M~
gboolean
on_maindraw_key_press_event            (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	return gxeview_OnKeyDown(widget,event);                        //~5718R~
}
gboolean
on_maindraw_key_release_event          (GtkWidget       *widget,
                                        GdkEventKey     *event,
                                        gpointer         user_data)
{
	return gxeview_OnKeyUp(widget,event);                          //~5718R~
}
gboolean
on_maindraw_leave_notify_event         (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data)
{
	return gxeview_leave(widget,event);                            //~5610I~
}
gboolean
on_maindraw_enter_notify_event         (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data)
{
	return gxeview_enter(widget,event);                            //~5610I~
}
gboolean
on_maindraw_motion_notify_event        (GtkWidget       *widget,
                                        GdkEventMotion  *event,
                                        gpointer         user_data)
{
	return gxeview_motion(widget,event);                           //~5610I~
}
void
on_maindraw_realize                    (GtkWidget       *widget,
                                        gpointer         user_data)
{
	gxeview_realize				    (widget);                      //~5611R~
    return;                                                        //~5611I~
}
void
on_maindraw_unrealize                  (GtkWidget       *widget,
                                        gpointer         user_data)
{
	gxeview_unrealize				    (widget);                  //~5611R~
    return;                                                        //~5611I~
}
gboolean
on_maindraw_focus_in_event             (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	return gxeview_focus_in				    (widget,event);        //~5611R~
}
gboolean
on_maindraw_focus_out_event            (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
	return gxeview_focus_out   			    (widget,event);        //~5611R~
}
void
on_framewindow_realize                 (GtkWidget       *widget,
                                        gpointer         user_data)
{
  	gxemfrm_realize				    (widget);                      //~5706R~
    return;                                                        //~5613I~
}
void
on_framewindow_unrealize               (GtkWidget       *widget,
                                        gpointer         user_data)
{
	gxemfrm_unrealize				    (widget);                  //~5613I~
    return;                                                        //~5613I~
}
gboolean
on_framewindow_configure_event         (GtkWidget       *widget,
                                        GdkEventConfigure *event,
                                        gpointer         user_data)
{
	gxemfrm_configure				    (widget,event);            //~5613I~
  	return FALSE;                                                  //~5613R~
}
gboolean
on_framewindow_delete_event            (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gxemfrm_delete				    (widget,event);                //~5614I~
  	return FALSE;                                                  //~5614R~
}


gboolean
on_framewindow_destroy_event           (GtkWidget       *widget,
                                        GdkEvent        *event,
                                        gpointer         user_data)
{
	gxemfrm_destroy 			    (widget,event);                //~5614I~
	return FALSE;                                                  //~5614R~
}
//**************************************************************** //~5625I~
//*drag & drop                                                     //~5625I~
//**************************************************************** //~5625I~
//**target app                                                     //~5627I~
void
on_framewindow_drag_data_received      (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        gint             x,
                                        gint             y,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data)
{
    dprintf("callbacks:framewindow:drag data receive context=%p,seldata=%p\n",drag_context,data);//~v685I~//~vb7tR~
//	xxefile_ondropfiles(drag_context,data,time);                   //~v686R~
  	xxefile_ondropfiles(drag_context,data,x,y,time);               //~v686R~
    return;                                                        //~5625I~
}
//void                                                             //~vb7tR~
//on_maindraw_drag_data_received      (GtkWidget       *widget,    //~vb7tR~
//                                        GdkDragContext  *drag_context,//~vb7tR~
//                                        gint             x,      //~vb7tR~
//                                        gint             y,      //~vb7tR~
//                                        GtkSelectionData *data,  //~vb7tR~
//                                        guint            info,   //~vb7tR~
//                                        guint            time,   //~vb7tR~
//                                        gpointer         user_data)//~vb7tR~
//{                                                                //~vb7tR~
//    dprintf("callbacks:maindraw:drag data receive context=%p,seldata=%p\n",drag_context,data);//~vb7tR~
//    xxefile_ondropfiles(drag_context,data,x,y,time);             //~vb7tR~
//    return;                                                      //~vb7tR~
//}                                                                //~vb7tR~
//**source app                                                     //~5627I~
void
on_maindraw_drag_data_get              (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        GtkSelectionData *data,
                                        guint            info,
                                        guint            time,
                                        gpointer         user_data)
{
    dprintf("callbacks:drag data get context=%p,seldata=%p\n",drag_context,data);//~v685I~
    gxeview_dragdataget(drag_context,data);                        //~5625R~
    return;                                                        //~5625I~
}
void                                                               //~5627M~
on_maindraw_drag_begin                 (GtkWidget       *widget,   //~5627M~
                                        GdkDragContext  *drag_context,//~5627M~
                                        gpointer         user_data)//~5627M~
{                                                                  //~5627M~
    dprintf("callbacks:drag data begin context=%p user_data=%p\n",drag_context,user_data);//~v685I~
    gxeview_dragbegin(drag_context);                               //~v71sI~
}                                                                  //~5627M~
void
on_maindraw_drag_end                   (GtkWidget       *widget,
                                        GdkDragContext  *drag_context,
                                        gpointer         user_data)
{
    dprintf("callbacks:drag data end context=%p user_data=%p\n",drag_context,user_data);//~v685I~
    gxeview_dragend(drag_context);                                 //~5627R~
}


void
on_button_save_enter                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar save enter\n");                               //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_save_leave                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar save leave\n");                               //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_end_enter                    (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar end  enter\n");                               //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_end_leave                    (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar end  leave\n");                               //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_cancel_enter                 (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar cancel enter\n");                             //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_cancel_leave                 (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar cancel leave\n");                             //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_print_enter                  (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar print enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_print_leave                  (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar print leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_home_enter                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar home  enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_home_leave                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar home  leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_terminal_enter               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar term  enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_terminal_leave               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar term  leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_cut_enter                    (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar cut   enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_cut_leave                    (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar cut   leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_copy_enter                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar copy  enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_copy_leave                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar copy  leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_clear_enter                  (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar clear enter\n");                              //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_clear_leave                  (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar clear leave\n");                              //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_pasteins_enter               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasteins enter\n");                           //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_pasteins_leave               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasteins leave\n");                           //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void
on_button_pasterep_enter               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasterep enter\n");                           //~v66aR~
	gxemfrm_enabletoolbar(1);                                      //~5702I~
}
void
on_button_pasterep_leave               (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasterep leave\n");                           //~v66aR~
	gxemfrm_enabletoolbar(0);                                      //~5702I~
}
void                                                               //~v66pM~
on_button_pasteV_enter                 (GtkButton       *button,   //~v66pM~
                                        gpointer         user_data)//~v66pM~
{                                                                  //~v66pM~
    dprintf("toolbar pasteV enter\n");                             //~v66pI~
	gxemfrm_enabletoolbar(1);                                      //~v66pI~
}                                                                  //~v66pM~
void                                                               //~v66pM~
on_button_pasteV_leave                 (GtkButton       *button,   //~v66pM~
                                        gpointer         user_data)//~v66pM~
{                                                                  //~v66pM~
    dprintf("toolbar pasteV leave\n");                             //~v66pI~
	gxemfrm_enabletoolbar(0);                                      //~v66pI~
                                                                   //~v66pM~
}                                                                  //~v66pM~
void
on_button_open_enter                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasteopen enter\n");                          //~v66pR~
	gxemfrm_enabletoolbar(1);                                      //~5728I~
}
void
on_button_open_leave                   (GtkButton       *button,
                                        gpointer         user_data)
{
    dprintf("toolbar pasteopen leave\n");                          //~v66pR~
	gxemfrm_enabletoolbar(0);                                      //~5728I~
}


#ifndef OPTGTK3                                                    //~var8R~
gboolean
on_maindraw_client_event               (GtkWidget       *widget,
                                        GdkEventClient  *event,
                                        gpointer         user_data)
{
    return gxeview_clientevent(widget,event,user_data);            //~v685I~
}
#else   //OPTGTK3                                                  //~var8R~
//*call gxeview_clientevent from interface_msg_filter              //~var8R~
#endif                                                             //~var8R~


void
on_option_button_rulercolor_change_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	gxedlg_option_rulercolor_create(button,user_data);             //~v73tI~
    return;                                                        //~v73tI~
}
//********************************************************         //~var8R~
//*combo printer selection changed                                 //~var8R~
//********************************************************         //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
void
on_page_combo_printer_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
	gxepage_OnChanged_ComboPrinter(editable,user_data);            //~va6yI~
}
#else   //OPTGTK3                                                  //~var8R~
void                                                               //~var8R~
on_page_combo_printer_changed(GtkComboBox *Ppcombo,gpointer user_data)//~var8R~
{                                                                  //~var8R~
	gxepage_OnChanged_ComboPrinter(Ppcombo,user_data);             //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vap1M~
//********************************************************         //~var8R~
//*combo form selection changed                                    //~var8R~
//********************************************************         //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
void                                                               //~vambI~
on_page_combo_form_changed          (GtkEditable     *editable,    //~vambI~
                                        gpointer         user_data)//~vambI~
{                                                                  //~vambI~
	gxepage_OnChanged_ComboForm(editable,user_data);               //~vambI~
}                                                                  //~vambI~
#else   //OPTGTK3                                                  //~var8R~
void on_page_combo_form_changed(GtkComboBox *Ppcombo,gpointer  user_data)//~var8R~
{                                                                  //~var8R~
	gxepage_OnChanged_ComboForm(Ppcombo,user_data);                //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
#endif //!NOPRINT                                                  //~vap1R~
//***********************************************************************//~vawFI~
#ifndef GGG                                                        //~vawFM~
gboolean                                                           //~vawFM~
on_setup_button_press(GtkWidget       *widget,                     //~vawFM~
                                        GdkEventButton  *event,    //~vawFM~
                                        gpointer         user_data)//~vawFM~
{                                                                  //~vawFM~
    dprintf("on_setup_button_press widget=%p,ud=%p\n",widget,user_data);//~vawFM~
	gtk_menu_item_deselect(GTK_MENU_ITEM(user_data));              //~vawFI~
	on_setup_activate(GTK_MENU_ITEM(user_data),NULL); //user_data:menuitem on submenu//~vawFM~
    return TRUE;                                                   //~vawFM~
}                                                                  //~vawFM~
gboolean                                                           //~vawFM~
on_preview_button_press(GtkWidget       *widget,                   //~vawFM~
                                        GdkEventButton  *event,    //~vawFM~
                                        gpointer         user_data)//~vawFM~
{                                                                  //~vawFM~
    dprintf("on_preview_button_press widget=%p,ud=%p\n",widget,user_data);//~vawFM~
	gtk_menu_item_deselect(GTK_MENU_ITEM(user_data));              //~vawFI~
	on_preview_activate(GTK_MENU_ITEM(user_data),NULL); //user_data:menuitem on submenu//~vawFR~
    return TRUE;                                                   //~vawFM~
}                                                                  //~vawFM~
#endif //!GGG                                                      //~vawFR~
