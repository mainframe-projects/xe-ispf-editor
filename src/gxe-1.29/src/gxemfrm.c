//*CID://+vbj2R~:                             update#=  515;       //~vbj2R~
//************************************************************************//~v51dI~
//vbj2:180424 popup menu on cmd history list                       //~vbj2I~
//vbi9:180221 (GTK3:bug)window size recovery err                   //~vbi9R~
//vbdn:171125 disable filemenu depending curent pcw type           //~vbdnI~
//vbdj:171125 (GTK2) menu label Ctrl+x dose not change by SetupDialog:Accel On/Off//~vbdjI~
//vbdh:171123 (GTK3.10 BUG) gtk_widget_add_accelerator() dose not allow runtime change of accelerator//~vbdhI~
//            use not gtk_menu_item_set_accel_path() but gtk_widget_set_accel_path() to set accel path withgtk_accel_map_add_entry()//~vbdhI~
//vbdb:171121*(gxe)try setup/preview menu as menuitem to open dialog by one touch//~vbdbI~
//vbd3:171117 (Wxe)MainMenu enable/disable also on Edit submenu    //~vbd3I~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //~vbd2I~
//vb74:161220 Gtk3 warning                                         //~vb74I~
//var8:140127 gtk3 suppott                                         //~var8I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//va72:100801 LP64 wchar_t is 4byte on LP64                        //~va72I~
//v71A:061030 Use HtmlHelp;Winhelp is deprecated at Vista;XP english ersion cannot read .hlp by the readson of codepage unsupported//~v71AI~
//v69r:060531 (XXE)print debug message by GError                   //~v69rI~
//v66D:051220 (BUG:XXE)gxe need Ctrl+C after System-Close button pushed//~v66DI~
//v66B:051220 (XXE)html help top index split to japanese and english//~v66BI~
//v66r:051025 (XXE) for v66m for WXE                               //~v66rI~
//v66p:051026 (XXE)std paste support                               //~v66pI~
//v669:050826 (XXE)help support                                    //~v669I~
//vXXE:050611 new for XXE                                          //~vXXEI~
//v55F:040314 (WXE)english help                                    //~v55FI~
//v55z:040304 (WXE)help support                                    //~v55zI~
//v53t:031004 (WXE:BUG)not freed area exist                        //~v51wI~
//v51w:030615 (WXE)icon for MDOS and Explorer                      //~v51wI~
//v51d:030517 (WXE)bitmap menu                                     //~v51dI~
//************************************************************************//~v51dI~
#include <stdlib.h>                                                //~var8R~
#include <string.h>                                                //~var8R~
#include <ctype.h>                                                 //~var8R~

#ifdef HAVE_CONFIG_H                                               //~vXXEI~
#  include <config.h>                                              //~vXXEI~
#endif                                                             //~vXXEI~
                                                                   //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>                                                 //~vXXEI~
#else                                                              //~var8R~
#include <gtk/gtk.h>                                               //~var8R~
#include <gdk/gdkx.h>                                              //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0I~
	#else    //!GTKPRINT                                           //~vam0I~
#include <libgnomeprint/gnome-print.h>                             //~vXXEI~
#include <libgnomeprint/gnome-print-job.h>                         //~vXXEI~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif                                                             //~vam0I~
//#include <libgnome/gnome-help.h>                                 //~v71AR~
                                                                   //~vXXEI~
#include "callbacks.h"                                             //~vXXEI~
#include "interface.h"                                             //~vXXEI~
#include "support.h"                                               //~vXXEI~
                                                                   //~vXXEI~
#include <ulib.h>                                                  //~vXXEI~
#include <ufile.h>                                                 //~v669I~
#include <uerr.h>                                                  //~v669I~
#include <utrace.h>                                                //~vam0I~
                                                                   //~vXXEI~
#include <xxedef.h>                                                //~vXXER~
#include <xxeres.h>                                                //~vXXEI~
#define GBL_GXEMFRM                                                //~vXXEI~
#include <gxe.h>                                                   //~vXXEI~
#include <xxemain.h>                                               //~vXXEI~
#include <xxecsub.h>                                               //~vXXEI~
#include <xxexei.h>                                                //~vXXEI~
                                                                   //~vXXEI~
#include "gxemfrm.h"                                               //~vXXEI~
#include "gxeview.h"                                               //~vXXEI~

//#include "wxefile.h"                                             //~vXXER~
//#include "wxedoc.h"                                              //~vXXER~
//#include "wxehelp.h"                                             //~vXXER~
//                                                                 //~vXXER~
//#include "utrace.h"                                              //~vXXER~

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//**************************************************************************//~vXXEI~
//for menu key enable/disable                                      //~vXXEI~
typedef struct _MAINMENUTBL {                                      //~vXXER~
								int          MMTid;                //~vXXEM~
                                UCHAR       *MMTstrid;             //~vXXEM~
                                GtkMenuItem *MMTpmenuitem;         //~vXXEM~
                                GtkLabel    *MMTplabel;            //~vXXEM~
                                UCHAR        MMTlabelon[16];       //~vXXER~
                                UCHAR        MMTlabeloff[16];      //~vXXER~
                            } MAINMENUTBL,*PMAINMENUTBL;           //~vXXEM~
#define MAINMENUTBL_ENTRYDEF(menuid,labon)  {menuid,STR##menuid,0,0,labon,""}//~vXXER~
                                                                   //~vXXEI~
//for accelerator enable/disable                                   //~vXXEI~
typedef struct _ACCMENUTBL {                                       //~vXXER~
								int          AMTid;                //~vXXEI~
                                UCHAR       *AMTstrid;             //~vXXEI~
                                GtkMenuItem *AMTpmenuitem;         //~vXXEI~
                                int          AMTkey;               //~vXXEI~
                                int          AMTmodifier;          //~vXXER~
                                UCHAR        AMTpath[32];         //~vXXEI~//~vbdjR~
#ifndef SSS                                                        //~vbdjI~
#ifndef OPTGTK3                                                    //~vbdjI~
                                UCHAR        AMTlabelon[32];       //~vbdjI~
                                UCHAR        AMTlabeloff[32];      //~vbdjI~
#endif                                                             //~vbdjI~
#endif                                                             //~vbdjI~
                            } ACCMENUTBL,*PACCMENUTBL;             //~vXXEI~
#define ACCPATH_PREFIX   "<"XXEPGMID"-"XXEPGMID">"                 //~vXXER~
#define ACCMENUTBL_ENTRYDEF(menuid,path)  \
	{menuid,STR##menuid,0,ACCKEY##menuid,(GDK_CONTROL_MASK),ACCPATH_PREFIX "/" path "/" STR##menuid}//~vXXEI~
#define ACCMENUTBL_ENTRYDEF2(menuid,path)  \
	{menuid,STR##menuid,0,ACCKEY##menuid,(GDK_CONTROL_MASK|GDK_SHIFT_MASK),ACCPATH_PREFIX "/" path "/" STR##menuid}//~vbd2I~
                                                                   //~vXXEI~
//for context menuitem enable/disable                              //~vXXEI~
typedef void (CONTEXTMENU_ENABLE_FUNC)(GtkMenuItem  *Pmenuitem);   //~vXXEI~
typedef struct _CONTEXTMENUTBL {                                   //~vXXEI~
								int          CMTid;                //~vXXEI~
                                UCHAR       *CMTstrid;             //~vXXEI~
                                GtkMenuItem *CMTpmenuitem;         //~vXXEI~
        						CONTEXTMENU_ENABLE_FUNC *CMTfunc;  //~vXXEI~
                                UCHAR       *CMTtbstrid;           //~vXXEI~
                                GtkWidget   *CMTptoolbarbutton;    //~vXXEI~
                            } CONTEXTMENUTBL,*PCONTEXTMENUTBL;     //~vXXER~
#define CONTEXTMENUTBL_ENTRYDEF(menuid,func)  {menuid,STR##menuid,0,func,STRTB##menuid,0}//~vXXER~
                                                                   //~vXXEI~
//for popup context menuitem enable/disable                        //~vXXEI~
typedef struct _POPUPMENUTBL {                                     //~vXXEI~
								int          PMTid;                //~vXXEI~
                                UCHAR       *PMTstrid;             //~vXXEI~
                                GtkMenuItem *PMTpmenuitem;         //~vXXER~
                            } POPUPMENUTBL,*PPOPUPMENUTBL;         //~vXXEI~
#define POPUPMENUTBL_ENTRYDEF(menuid,strid)  {menuid,strid,0}      //~vXXER~
//**************************************************************************//~vXXEI~
static int Sadjustww,Sadjusthh;                                    //~vbi9R~
//**************************************************************************//~vbi9R~
//void popupmenu_activate_callback(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vXXER~//~vbj2R~
void popupmenu_activate_callbackCHL(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vbj2I~
void popupmenu_activate_callbackCHLCMD(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vbj2I~
void popupmenu_activate_callback2(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vXXEI~
void popupmenu_activate_callback2CHL(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vbj2I~
void popupmenu_activate_openwith(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vXXEI~
int popupmenu_srchid(int Pitemid);                                 //~vXXEM~
void popupmenu_init(void);                                         //~vXXEM~
int append_menuitem_by_stockid(int Pitemid,char *Pstockid);        //~vXXEM~
void popupmenu_activate_callback(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vXXEM~
void popupmenu_deactivate_callback(GtkWidget  *Ppmenuitem,gpointer Puparm);//~vXXEM~
int  updatemainmenutext(PMAINMENUTBL Ppmt,int Pusemk);             //~vXXEI~
int  updatemenu(int Puseact);                                      //~vXXEI~
int  actinit(void);                                                //~vXXEI~
void changemenuaccelkey(void);                                     //~vXXER~
//**************************************************************************//~vXXEI~
//mainmenu menuitem name and widget ptr for change menukey use     //~vXXEI~
static MAINMENUTBL Smainmenutbl[]={                                //~vXXEI~
					MAINMENUTBL_ENTRYDEF(ID_FILE,"_File"),         //~vXXER~
					MAINMENUTBL_ENTRYDEF(ID_EDIT,"_Edit"),         //~vXXER~
					MAINMENUTBL_ENTRYDEF(ID_SETUP,"_Setup"),       //~vXXER~
					MAINMENUTBL_ENTRYDEF(ID_PAGE_SETUP,"_Preview"),//~vXXER~
					MAINMENUTBL_ENTRYDEF(ID_HELP,"_Help")          //~vXXER~
								  };                               //~vXXEI~
#define MAINMENUTBLENTNO  (sizeof(Smainmenutbl)/sizeof(MAINMENUTBL))//~vXXER~
                                                                   //~vXXEI~
//accelerator set menuitem tbl                                     //~vXXEI~
static ACCMENUTBL Saccmenutbl[]={                                  //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_NEW,"file"),       //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_OPEN,"file"),      //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_SAVE,"file"),      //~vXXEI~
//  				ACCMENUTBL_ENTRYDEF(ID_FILE_SAVEAS,"file"),    //~vXXEI~//~vbd2R~
    				ACCMENUTBL_ENTRYDEF2(ID_FILE_SAVEAS,"file"),   //ctrl+shift//~vbd2I~
					ACCMENUTBL_ENTRYDEF(ID_FILE_PRINT,"file"),     //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_PRTSCR,"file"),    //~vXXEI~
//  				ACCMENUTBL_ENTRYDEF(ID_FILE_PREVIEW,"file"),   //~v66pR~
					ACCMENUTBL_ENTRYDEF(ID_FILE_HOME,"file"),      //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_TERMINAL,"file"),  //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_FILE_EXIT,"file"),      //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_CUT,"edit"),       //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_COPY,"edit"),      //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_CLEAR,"edit"),     //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_PASTE_V,"edit"),   //~v66pR~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_PASTE,"edit"),     //~vXXEI~
					ACCMENUTBL_ENTRYDEF(ID_EDIT_PASTE_REP,"edit")  //~vXXEI~
			        ,ACCMENUTBL_ENTRYDEF(ID_EDIT_SELECTALL,"edit") //~vbd2R~
								  };                               //~vXXEI~
#define ACCMENUTBLENTNO  (sizeof(Saccmenutbl)/sizeof(ACCMENUTBL))  //~vXXEI~
                                                                   //~vXXEI~
//context menuitem/toolbar-button widget ptr for disable/enable (edit context menu)****************//~vXXER~
#define TOOLBARINDEX_SAVE 6  //index of Scontextmenutbl            //~vbdnI~
static  CONTEXTMENUTBL Scontextmenutbl[]={                         //~vXXER~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_CUT,gxeview_OnUpdateEditCut),//~vXXEI~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_COPY,gxeview_OnUpdateEditCopy),//~vXXEI~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_CLEAR,gxeview_OnUpdateEditClear),//~vXXEI~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_PASTE_V,gxeview_OnUpdateEditPasteV),//~v66pR~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_PASTE,gxeview_OnUpdateEditPaste),//~vXXEI~
				CONTEXTMENUTBL_ENTRYDEF(ID_EDIT_PASTE_REP,gxeview_OnUpdateEditPasteRep)//~vXXEI~
			,	CONTEXTMENUTBL_ENTRYDEF(ID_FILE_SAVE,NULL)   //enable/disable by updateMenuIcon()//~vbdnI~
                						};                         //~vXXEI~
#define CONTEXTMENU_ITEMCTR (sizeof(Scontextmenutbl)/sizeof(CONTEXTMENUTBL))//~vXXER~
                                                                   //~vXXEI~
//popupmenu menuitem id,name and widget ptr ******************     //~vXXER~
static POPUPMENUTBL  Spopupmenutbl[]={                             //~vXXEI~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CUT,STRID_EDIT_CUT), //~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_COPY,STRID_EDIT_COPY),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CLEAR,STRID_EDIT_CLEAR),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE_V,STRID_EDIT_PASTE_V),//~v66pI~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE,STRID_EDIT_PASTE),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE_REP,STRID_EDIT_PASTE_REP),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_SELECTALL,STRID_EDIT_SELECTALL),//~vbd2M~
				POPUPMENUTBL_ENTRYDEF(ID_FILE_SAVE,STRID_FILE_SAVE),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_END,STRTBID_EDIT_END),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CANCEL,STRTBID_EDIT_CANCEL),//~vXXER~
				POPUPMENUTBL_ENTRYDEF(ID_FILE_OPENWITH,"")         //~vXXER~
                				};                                 //~vXXEI~
#define POPUPMENU_ITEMCTR (sizeof(Spopupmenutbl)/sizeof(POPUPMENUTBL))//~vXXER~
static POPUPMENUTBL  SpopupmenutblCHL[]={                          //~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_EXE_CLOSED,STRID_CHL_EXE_CLOSED),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_EXE_CURRENT,STRID_CHL_EXE_CURRENT),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_EXE_SPLIT,STRID_CHL_EXE_SPLIT),//~vbj2I~
                                                                   //~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_SET_CLOSED,STRID_CHL_SET_CLOSED),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_SET_CURRENT,STRID_CHL_SET_CURRENT),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_CHL_SET_SPLIT,STRID_CHL_SET_SPLIT),//~vbj2I~
                                                                   //~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CUT,STRID_EDIT_CUT), //~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_COPY,STRID_EDIT_COPY),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CLEAR,STRID_EDIT_CLEAR),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE_V,STRID_EDIT_PASTE_V),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE,STRID_EDIT_PASTE),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_PASTE_REP,STRID_EDIT_PASTE_REP),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_SELECTALL,STRID_EDIT_SELECTALL),//~vbj2I~
				POPUPMENUTBL_ENTRYDEF(ID_EDIT_CANCEL,STRTBID_EDIT_CANCEL),//~vbj2I~
                				};                                 //~vbj2I~
#define POPUPMENU_ITEMCTR_CHL (sizeof(SpopupmenutblCHL)/sizeof(POPUPMENUTBL))//~vbj2I~
                                                                   //~vXXEI~
//* popup menu table                                               //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
#define PIX_STOCK(stockid)  GNOME_APP_PIXMAP_STOCK,stockid         //~vXXER~
static GnomeUIInfo Spopupmenuuiinfo[] = {                          //~vXXEI~
                                                                   //~vXXEI~
	GNOMEUIINFO_SEPARATOR,                                         //~vXXEI~
                                                                   //~vXXEI~
	{GNOME_APP_UI_ITEM, N_("Cut(_T)"),                        //type,label//~vXXER~
	 NULL,                                                 //hint  //~vXXEI~
	 popupmenu_activate_callback,(gpointer)1, NULL, //callback,callback parm(table index),reseved//~vXXER~
	 PIX_STOCK(GTK_STOCK_CUT),								//pixmap type and id//~vXXEI~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vXXER~
	{GNOME_APP_UI_ITEM, N_("Copy(_C)"),                            //~vXXER~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_callback,(gpointer)2, NULL,                //~vXXER~
	 PIX_STOCK(GTK_STOCK_COPY),                                    //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("Clear(_L)"),                           //~vXXER~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_callback,(gpointer)3, NULL,                //~vXXER~
	 PIX_STOCK(GTK_STOCK_COPY),                                    //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("Paste(_V)"),                           //~v66pI~
	 NULL,                                                         //~v66pI~
	 popupmenu_activate_callback,(gpointer)4, NULL,                //~v66pI~
	 PIX_STOCK(GTK_STOCK_PASTE),                                   //~v66pI~
	 0, 0, NULL},                                                  //~v66pI~
	{GNOME_APP_UI_ITEM, N_("PasteIns(_I)"),                        //~vXXER~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_callback,(gpointer)5, NULL,                //~v66pR~
	 PIX_STOCK(GTK_STOCK_PASTE),                                   //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("PasteRep(_R)"),                        //~vXXER~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_callback,(gpointer)6, NULL,                //~v66pR~
	 PIX_STOCK(GTK_STOCK_PASTE),                                   //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("SelectAll(_A)"),                        //type,label//~vbd2M~
	 NULL,                                                 //hint  //~vbd2M~
	 popupmenu_activate_callback,(gpointer)7, NULL, //callback,callback parm(table index),reseved//~vbd2M~
	 PIX_STOCK(GTK_STOCK_SELECT_ALL),								//pixmap type and id//~vbd2M~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbd2M~
                                                                   //~vXXEI~
	GNOMEUIINFO_SEPARATOR,                                         //~vXXER~
                                                                   //~vXXEI~
	{GNOME_APP_UI_ITEM, N_("Save(_S)"),                            //~vXXER~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_callback,(gpointer)8, NULL,                //~v66pR~//~vbd2R~
	 PIX_STOCK(GTK_STOCK_SAVE),                                    //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("End(_E)"),                             //~vXXER~
	 N_("Save,then Close"),                                        //~vXXEI~
	 popupmenu_activate_callback2,(gpointer)9,NULL,                //~v66pR~//~vbd2R~
	 PIX_STOCK(GTK_STOCK_CLOSE),                                   //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	{GNOME_APP_UI_ITEM, N_("Discard(_D)"),                         //~vXXER~
	 N_("Cancel,then Close"),                                      //~vXXEI~
	 popupmenu_activate_callback2,(gpointer)10, NULL,               //~v66pR~//~vbd2R~
	 PIX_STOCK(GTK_STOCK_CANCEL),                                  //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
//	{GNOME_APP_UI_ITEM, N_("OpenWidthA(_A)"),                      //~vXXER~//~vbd2R~
  	{GNOME_APP_UI_ITEM, N_("OpenWidth(_W)"),                       //~vbd2I~
	 NULL,                                                         //~vXXEI~
	 popupmenu_activate_openwith,(gpointer)11, NULL,               //~v66pR~//~vbd2R~
	 PIX_STOCK(GTK_STOCK_OPEN),                                    //~vXXEI~
	 0, 0, NULL},                                                  //~vXXER~
	                                                               //~vXXER~
	GNOMEUIINFO_END                                                //~vXXEI~
};                                                                 //~vXXEI~
//*CHL ***                                                         //~vbj2I~
static GnomeUIInfo SpopupmenuuiinfoCHL[] = {                       //~vbj2I~
                                                                   //~vbj2I~
	GNOMEUIINFO_SEPARATOR,                                         //~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_EXE_CLOSED),          //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)1, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_EXE_CLOSED),								//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_EXE_CURRENT),          //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)2, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_EXE_CURRENT),								//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_EXE_SPLIT),          //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)3, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_EXE_SPLIT),								//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_SET_CLOSED),         //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)4, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_SET_CLOSED),  							//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_SET_CURRENT),        //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)5, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_SET_CURRENT), 							//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_(STRID_CHL_SET_SPLIT),         //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHLCMD,(gpointer)6, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK(STRID_CHL_SET_SPLIT),   							//stock//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
                                                                   //~vbj2I~
	GNOMEUIINFO_SEPARATOR,                                         //~vbj2I~
                                                                   //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("Cut(_T)"),                        //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)7, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK("CHL_Cut"),								//pixmap type and id//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
	{GNOME_APP_UI_ITEM, N_("Copy(_C)"),                            //~vbj2I~
	 NULL,                                                         //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)8, NULL,             //~vbj2R~
	 PIX_STOCK("CHL_Copy"),                                        //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("Clear(_L)"),                           //~vbj2I~
	 NULL,                                                         //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)9, NULL,             //~vbj2R~
	 PIX_STOCK("CHL_Clear"),                                       //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("Paste(_V)"),                           //~vbj2I~
	 NULL,                                                         //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)10, NULL,            //~vbj2R~
	 PIX_STOCK("CHL_PasteV"),                                      //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("PasteIns(_I)"),                        //~vbj2I~
	 NULL,                                                         //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)11, NULL,            //~vbj2R~
	 PIX_STOCK("CHL_PasteI"),                                      //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("PasteRep(_R)"),                        //~vbj2I~
	 NULL,                                                         //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)12, NULL,            //~vbj2R~
	 PIX_STOCK("CHL_PasteR"),                                      //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("SelectAll(_A)"),                        //type,label//~vbj2I~
	 NULL,                                                 //hint  //~vbj2I~
	 popupmenu_activate_callbackCHL,(gpointer)13, NULL, //callback,callback parm(table index),reseved//~vbj2R~
	 PIX_STOCK("CHL_SelectAll"),								//pixmap type and id//~vbj2R~
	 0, 0, NULL},   										//acc key,acc key modifier,output menuitem widget//~vbj2I~
                                                                   //~vbj2I~
	GNOMEUIINFO_SEPARATOR,                                         //~vbj2I~
                                                                   //~vbj2I~
	{GNOME_APP_UI_ITEM, N_("Discard(_D)"),                         //~vbj2I~
	 N_("Cancel,then Close"),                                      //~vbj2I~
	 popupmenu_activate_callback2CHL,(gpointer)14, NULL,           //~vbj2R~
	 PIX_STOCK("CHL_Cancel"),                                      //~vbj2R~
	 0, 0, NULL},                                                  //~vbj2I~
                                                                   //~vbj2I~
	GNOMEUIINFO_END                                                //~vbj2I~
};                                                                 //~vbj2I~
#else   //OPTGTK3                                                  //~var8R~
//*****************************************************************//~var8R~
void gxemfrm_create_popupmenu()                                    //~var8R~
{                                                                  //~var8R~
    GtkMenu *pmenu;                                                //~var8R~
    GtkWidget *pmisep;                                             //~var8R~
    GtkWidget *pmicut,*pmicopy,*pmiclear,*pmipastev,*pmipastei,*pmipaster,*pmisave,*pmiend,*pmidiscard,*pmiopenwith;//~var8R~
    GtkWidget *pmiselectall;                                       //~vbd2I~
//*****************************                                    //~var8R~
	pmenu=(GtkMenu*)Gppopupmenu;                                   //~var8R~
    pmicut=gtk_menu_item_new_with_mnemonic("Cut(_T)");             //~var8R~
    pmicopy=gtk_menu_item_new_with_mnemonic("Copy(_C)");           //~var8R~
    pmiclear=gtk_menu_item_new_with_mnemonic("Clear(_L)");         //~var8R~
    pmipastev=gtk_menu_item_new_with_mnemonic("Paste(_V)");        //~var8R~
    pmipastei=gtk_menu_item_new_with_mnemonic("PasteIns(_I)");     //~var8R~
    pmipaster=gtk_menu_item_new_with_mnemonic("PasteRep(_R)");     //~var8R~
    pmiselectall=gtk_menu_item_new_with_mnemonic("SelectAll(_A)"); //~vbd2M~
    pmisave=gtk_menu_item_new_with_mnemonic("Save(_S)");           //~var8R~
    pmiend=gtk_menu_item_new_with_mnemonic("End(_E)");             //~var8R~
    pmidiscard=gtk_menu_item_new_with_mnemonic("Discard(_D)");     //~var8R~
//  pmiopenwith=gtk_menu_item_new_with_mnemonic("OpenWidthA(_A)"); //~var8R~//~vbd2R~
    pmiopenwith=gtk_menu_item_new_with_mnemonic("OpenWidthA(_W)"); //~vbd2I~
                                                                   //~var8R~
	pmisep=gtk_separator_menu_item_new();                          //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmicut);           //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmicopy);          //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiclear);         //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipastev);        //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipastei);        //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipaster);        //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiselectall);     //~vbd2M~
	pmisep=gtk_separator_menu_item_new();                          //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisave);          //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiend);           //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmidiscard);       //~var8R~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiopenwith);      //~var8R~
                                                                   //~var8R~
  	g_signal_connect(pmicut,     "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)1);//~var8R~
  	g_signal_connect(pmicopy,    "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)2);//~var8R~
  	g_signal_connect(pmiclear,   "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)3);//~var8R~
  	g_signal_connect(pmipastev,  "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)4);//~var8R~
  	g_signal_connect(pmipastei,  "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)5);//~var8R~
  	g_signal_connect(pmipaster,  "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)6);//~var8R~
  	g_signal_connect(pmiselectall,"activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)7);//~vbd2M~
  	g_signal_connect(pmisave,    "activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)8);//~var8R~
  	g_signal_connect(pmiend,     "activate",G_CALLBACK(popupmenu_activate_callback2),(gpointer)9);//~var8R~
  	g_signal_connect(pmidiscard, "activate",G_CALLBACK(popupmenu_activate_callback2),(gpointer)10);//~var8R~
  	g_signal_connect(pmiopenwith,"activate",G_CALLBACK(popupmenu_activate_openwith),(gpointer)11);//~var8R~
                                                                   //~var8R~
    Spopupmenutbl[0].PMTpmenuitem=(GtkMenuItem*)pmicut;            //~var8R~
    Spopupmenutbl[1].PMTpmenuitem=(GtkMenuItem*)pmicopy;           //~var8R~
    Spopupmenutbl[2].PMTpmenuitem=(GtkMenuItem*)pmiclear;          //~var8R~
    Spopupmenutbl[3].PMTpmenuitem=(GtkMenuItem*)pmipastev;         //~var8R~
    Spopupmenutbl[4].PMTpmenuitem=(GtkMenuItem*)pmipastei;         //~var8R~
    Spopupmenutbl[5].PMTpmenuitem=(GtkMenuItem*)pmipaster;         //~var8R~
    Spopupmenutbl[6].PMTpmenuitem=(GtkMenuItem*)pmiselectall;      //~vbd2I~
    Spopupmenutbl[7].PMTpmenuitem=(GtkMenuItem*)pmisave;           //~var8R~//~vbd2R~
    Spopupmenutbl[8].PMTpmenuitem=(GtkMenuItem*)pmiend;            //~var8R~//~vbd2R~
    Spopupmenutbl[9].PMTpmenuitem=(GtkMenuItem*)pmidiscard;        //~var8R~//~vbd2R~
    Spopupmenutbl[10].PMTpmenuitem=(GtkMenuItem*)pmiopenwith;       //~var8R~//~vbd2R~
}//gxemfrm_create_popupmenu                                        //~var8R~
//*****************************************************************//~vbj2I~
void gxemfrm_create_popupmenuCHL()                                 //~vbj2I~
{                                                                  //~vbj2I~
    GtkMenu *pmenu;                                                //~vbj2I~
    GtkWidget *pmisep;                                             //~vbj2I~
    GtkWidget *pmicut,*pmicopy,*pmiclear,*pmipastev,*pmipastei,*pmipaster,*pmidiscard;//~vbj2I~
    GtkWidget *pmiselectall;                                       //~vbj2I~
    GtkWidget *pmiexeclosed,*pmiexecurrent,*pmiexesplit,*pmisetclosed,*pmisetcurrent,*pmisetsplit;//+vbj2R~
//*****************************                                    //~vbj2I~
	pmenu=(GtkMenu*)GppopupmenuCHL;                                //~vbj2I~
    pmiexeclosed=gtk_menu_item_new_with_mnemonic(STRID_CHL_EXE_CLOSED);//~vbj2R~
    pmiexecurrent=gtk_menu_item_new_with_mnemonic(STRID_CHL_EXE_CURRENT);//~vbj2R~
    pmiexesplit=gtk_menu_item_new_with_mnemonic(STRID_CHL_EXE_SPLIT);//~vbj2R~
    pmisetclosed=gtk_menu_item_new_with_mnemonic(STRID_CHL_SET_CLOSED);//~vbj2R~
    pmisetcurrent=gtk_menu_item_new_with_mnemonic(STRID_CHL_SET_CURRENT);//~vbj2R~
    pmisetsplit=gtk_menu_item_new_with_mnemonic(STRID_CHL_SET_SPLIT);//~vbj2R~
                                                                   //~vbj2I~
    pmicut=gtk_menu_item_new_with_mnemonic("Cut(_T)");             //~vbj2I~
    pmicopy=gtk_menu_item_new_with_mnemonic("Copy(_C)");           //~vbj2I~
    pmiclear=gtk_menu_item_new_with_mnemonic("Clear(_L)");         //~vbj2I~
    pmipastev=gtk_menu_item_new_with_mnemonic("Paste(_V)");        //~vbj2I~
    pmipastei=gtk_menu_item_new_with_mnemonic("PasteIns(_I)");     //~vbj2I~
    pmipaster=gtk_menu_item_new_with_mnemonic("PasteRep(_R)");     //~vbj2I~
    pmiselectall=gtk_menu_item_new_with_mnemonic("SelectAll(_A)"); //~vbj2I~
    pmidiscard=gtk_menu_item_new_with_mnemonic("Discard(_D)");     //~vbj2I~
                                                                   //~vbj2I~
	pmisep=gtk_separator_menu_item_new();                          //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiexeclosed);     //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiexecurrent);    //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiexesplit);      //~vbj2I~
	pmisep=gtk_separator_menu_item_new();                          //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisetclosed);     //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisetcurrent);    //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisetsplit);      //~vbj2I~
                                                                   //~vbj2I~
	pmisep=gtk_separator_menu_item_new();                          //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmicut);           //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmicopy);          //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiclear);         //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipastev);        //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipastei);        //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmipaster);        //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmiselectall);     //~vbj2I~
	pmisep=gtk_separator_menu_item_new();                          //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmisep);           //~vbj2I~
	gtk_menu_shell_append(GTK_MENU_SHELL(pmenu),pmidiscard);       //~vbj2I~
                                                                   //~vbj2I~
  	g_signal_connect(pmiexeclosed,     "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)1);//~vbj2R~
  	g_signal_connect(pmiexecurrent,    "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)2);//~vbj2R~
  	g_signal_connect(pmiexesplit,      "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)3);//~vbj2R~
  	g_signal_connect(pmisetclosed,     "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)4);//~vbj2R~
  	g_signal_connect(pmisetcurrent,    "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)5);//~vbj2R~
  	g_signal_connect(pmisetsplit,      "activate",G_CALLBACK(popupmenu_activate_callbackCHLCMD),(gpointer)6);//~vbj2R~
                                                                   //~vbj2I~
  	g_signal_connect(pmicut,     "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)7);//~vbj2I~
  	g_signal_connect(pmicopy,    "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)8);//~vbj2I~
  	g_signal_connect(pmiclear,   "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)9);//~vbj2I~
  	g_signal_connect(pmipastev,  "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)10);//~vbj2I~
  	g_signal_connect(pmipastei,  "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)11);//~vbj2I~
  	g_signal_connect(pmipaster,  "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)12);//~vbj2I~
  	g_signal_connect(pmiselectall,"activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)13);//~vbj2I~
  	g_signal_connect(pmidiscard, "activate",G_CALLBACK(popupmenu_activate_callbackCHL),(gpointer)14);//~vbj2I~
                                                                   //~vbj2I~
    SpopupmenutblCHL[0].PMTpmenuitem=(GtkMenuItem*)pmiexeclosed;   //~vbj2I~
    SpopupmenutblCHL[1].PMTpmenuitem=(GtkMenuItem*)pmiexecurrent;  //~vbj2I~
    SpopupmenutblCHL[2].PMTpmenuitem=(GtkMenuItem*)pmiexesplit;    //~vbj2I~
    SpopupmenutblCHL[3].PMTpmenuitem=(GtkMenuItem*)pmisetclosed;   //~vbj2I~
    SpopupmenutblCHL[4].PMTpmenuitem=(GtkMenuItem*)pmisetcurrent;  //~vbj2I~
    SpopupmenutblCHL[5].PMTpmenuitem=(GtkMenuItem*)pmisetsplit;    //~vbj2I~
    SpopupmenutblCHL[6].PMTpmenuitem=(GtkMenuItem*)pmicut;         //~vbj2I~
    SpopupmenutblCHL[7].PMTpmenuitem=(GtkMenuItem*)pmicopy;        //~vbj2I~
    SpopupmenutblCHL[8].PMTpmenuitem=(GtkMenuItem*)pmiclear;       //~vbj2I~
    SpopupmenutblCHL[9].PMTpmenuitem=(GtkMenuItem*)pmipastev;      //~vbj2I~
    SpopupmenutblCHL[10].PMTpmenuitem=(GtkMenuItem*)pmipastei;     //~vbj2I~
    SpopupmenutblCHL[11].PMTpmenuitem=(GtkMenuItem*)pmipaster;     //~vbj2I~
    SpopupmenutblCHL[12].PMTpmenuitem=(GtkMenuItem*)pmiselectall;  //~vbj2I~
    SpopupmenutblCHL[13].PMTpmenuitem=(GtkMenuItem*)pmidiscard;    //~vbj2I~
}//gxemfrm_create_popupmenu                                        //~vbj2I~
#endif                                                             //~var8R~
//	 GNOME_APP_PIXMAP_NONE, NULL,		for no icon                //~vXXEI~
///////////////////////////////////////////////////////////////////////////////~vXXEI~
//#define APPENDPOS   9                                            //~v51wR~
#define APPENDPOS   11                                             //~v51wI~
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

/////////////////////////////////////////////////////////////////////////////

void gxemfrm_construct(void)                                       //~vXXER~
{
//******************************                                   //~vXXEI~
//  Mpxemain=0;	//for OnSize                                       //~vXXER~
	Mswgetinifail=                                                 //~vXXEI~
	ugetinidata(&Mwxeinidata);		//read ini data                //~2A19I~
    UTRACED("gxemfrm_construct WXEINI",&Mwxeinidata,(int)WXEINIDATASZ);//~vbdnI~
#ifndef XXE                                                        //~vXXEI~
    Mshowmaxsw=Mwxeinidata.WXEINIshowmaxsw;	//show max at init instance of wxe.cpp//~vXXER~
//  Museact=Mwxeinidata.WXEINIuseact;	//accelerator use          //~vXXER~
//  Musemk =Mwxeinidata.WXEINIusemk ;	//accelerator use          //~vXXER~
    Mpact=0;        //accelerator table copy                       //~3104I~
#endif                                                             //~v66rM~
    Menableselectall=-1;                                           //~vbd2I~
    Menablecut=-1;    //initialy dispaly menu bitmap               //~v66rR~
    Menablecopy=-1;                                                //~v66rR~
    Menablepaste=-1;                                               //~v66rR~
    Menablepastev=-1;                                              //~v66rI~
	popupmenu_init();		//read ini data                        //~vXXEI~
    changemenuaccelkey();                                          //~vXXER~
}

//***********************************************                  //~vXXEI~
//*accelerator key update                                          //~vXXEI~
//***********************************************                  //~vXXEI~
int  gxemfrm_Loadact(int Puseact)                                  //~vXXER~
{                                                                  //~3103I~
#ifndef XXE                                                        //~vXXEM~
	int delsw=0;                                                   //~3105R~
    CMenu *pmenu;                                                  //~3103I~
#endif                                                             //~vXXEI~
    static int Suseact=1;	//add entry by actinit                 //~vXXEI~
//*******************************                                  //~3103I~
	dprintf("%s:Puseact=%d\n",UTT,Puseact);                        //~vbdhI~
//	if (Puseact!=-1)        //init req from wxe.cpp                //~vXXER~
    	if (Suseact==Puseact)   //not changed                      //~vXXER~
            return 0;                                              //~3103R~
        else                                                       //~3103I~
            Suseact=Puseact;                                       //~vXXER~
#ifndef XXE                                                        //~vXXEI~
	if (Museact)	//accelerator use                              //~3103I~
    {                                                              //~3103I~
    	if (m_hAccelTable)	//already loaded,mfc asset fail        //~3103R~
        	delsw=1;                                               //~3103I~
    }                                                              //~3103I~
    else                                                           //~3103I~
    	if (m_hAccelTable)	//already loaded,mfc asset fail        //~3103I~
        	delsw=1;                                               //~3103I~
    if (delsw)                                                     //~3103I~
    {                                                              //~3103I~
        DestroyAcceleratorTable(m_hAccelTable);                    //~3103R~
    	m_hAccelTable=0;                                           //~3103R~
    }                                                              //~3103I~
    pmenu=GetMenu();                                               //~3103M~
	updatemenu(0,pmenu);                                           //~3103R~
	if (Puseact==-1)        //init req from wxe.cpp                //~v51dI~
		appendmenu(pmenu);                                         //~v51dI~
    Invalidate(FALSE);                                             //~v51dI~
#endif                                                             //~vXXEI~
	updatemenu(Puseact);                                           //~vXXEI~
	return 1;                                                      //~3103R~
}                                                                  //~3103I~
#ifndef SSS                                                        //~vbdjI~
#ifndef OPTGTK3                                                    //~vbdjI~
//***********************************************                  //~vbdjI~
//*acc table init for menuitem with accelerator                    //~vbdjI~
//***********************************************                  //~vbdjI~
int  getmenulabel(PACCMENUTBL Ppamt)                               //~vbdjI~
{                                                                  //~vbdjI~
	char *plabel,*pc;                                              //~vbdjI~
//***************                                                  //~vbdjI~
    dprintf("%s:menulabel=%s\n",UTT,gtk_menu_item_get_label(Ppamt->AMTpmenuitem));//~vbdjI~
	plabel=interface_getmenuitemlabel(Ppamt->AMTid); //by ID_FILE_NEW etc//~vbdjI~
    dprintf("%s:interface_getmenuitemlabel=%s\n",UTT,plabel);      //~vbdjI~
    if (plabel)                                                    //~vbdjI~
    {                                                              //~vbdjI~
    	strncpy(Ppamt->AMTlabelon,plabel,sizeof(Ppamt->AMTlabelon)-1);//~vbdjR~
    	strncpy(Ppamt->AMTlabeloff,plabel,sizeof(Ppamt->AMTlabeloff)-1);//~vbdjR~
        pc=strchr(Ppamt->AMTlabeloff,' ');                         //~vbdjR~
        if (pc)                                                    //~vbdjI~
	    	*pc=0;                                                 //~vbdjI~
    }                                                              //~vbdjI~
    return plabel!=0;                                              //~vbdjI~
}//getmenulabel                                                    //~vbdjI~
#endif // OPTGTK3                                                  //~vbdjI~
#endif                                                             //~vbdjI~
//***********************************************                  //~vXXEI~
//*acc table init for menuitem with accelerator                    //~vXXEI~
//***********************************************                  //~vXXEI~
int  actinit(void)                                                 //~vXXEI~
{                                                                  //~vXXEI~
    GtkMenuItem *pmenuitem;                                        //~vXXEI~
	PACCMENUTBL pamt;                                              //~vXXEI~
    int ii;                                                        //~vXXEI~
//***************************                                      //~vXXEI~
    for (ii=0,pamt=Saccmenutbl;ii<ACCMENUTBLENTNO;ii++,pamt++)     //~vXXEI~
    {                                                              //~vXXEI~
	    pmenuitem=(GtkMenuItem*)lookup_widget(GTK_WIDGET(Gpframe),pamt->AMTstrid); //edit menuitem//~vXXEI~
        pamt->AMTpmenuitem=pmenuitem;                              //~vXXEI~
#if GTK_CHECK_VERSION(3,10,0)	//gtk_ui_manager was deprecated    //~vbdhI~
		gtk_accel_map_add_entry(pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier);//~vbdhM~
	    dprintf("%s:gtk_accel_map_add_entry %s,key=%x,mod=%x\n",UTT,pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier);//~vbdhM~
    	gtk_widget_set_accel_path((GtkWidget*)pmenuitem,pamt->AMTpath,Gpag);//~vbdhM~
	    dprintf("%s:gtk_widget_set_accel_path %s\n",UTT,pamt->AMTpath);//~vbdhM~
#else                                                              //~vbdhM~
		gtk_menu_item_set_accel_path(pmenuitem,pamt->AMTpath);     //~vXXEI~
		gtk_accel_map_add_entry(pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier);//~vXXER~
#endif                                                             //~vbdhI~
        dprintf("%s:gtk_accel_map_add_entry menu=%p,path=%s,key=%x,mod=%x,resut=%s\n",UTT,pmenuitem,pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier,gtk_menu_item_get_accel_path(pmenuitem));//~vbd2R~//~vbdhR~
#ifdef QQQ                                                         //~vbdhI~
        {                                                          //~vbdhI~
        	gchar *gc,*gc2; gchar *pc;                             //~vbdhI~
            pc=pamt->AMTpath;//@@@@test                            //~vbdhI~
            gc=g_intern_static_string(pamt->AMTpath);//@@@@test    //~vbdhI~
            gc2=g_intern_static_string(gc);//@@@@test              //~vbdhI~
     	    dprintf("%s:path=%p=%s,canonical str by g_intern_static_string=%p=%s->%p=%s\n",UTT,pc,pc,gc,gc,gc2,gc2);//~vbdhI~
        }                                                          //~vbdhI~
#endif                                                             //~vbdhI~
        dprintf("%s:accel map lookup=%d\n",UTT,gtk_accel_map_lookup_entry(pamt->AMTpath,NULL));//~vbd2I~//~vbdhR~
#ifndef SSS                                                        //~vbdjI~
#ifndef OPTGTK3                                                    //~vbdjI~
		getmenulabel(pamt);                                        //~vbdjI~
#endif                                                             //~vbdjI~
#endif                                                             //~vbdjI~
	}                                                              //~vXXEI~
	updatemenu(1);	//initialy useact=on                           //~vbdhI~
	return 0;                                                      //~vXXEI~
}//actinit                                                         //~vXXEI~
#ifdef QQQ                                                         //~vbdhI~
//***********************************************                  //~vbdhI~
//*acc table init for menuitem with accelerator                    //~vbdhI~
//***********************************************                  //~vbdhI~
int  gxemfrm_actinit_menuitem(GtkAccelGroup *Ppag,GtkWidget *Pmenuitem,int Pkey,int Pmask)//~vbdhI~
{                                                                  //~vbdhI~
	PACCMENUTBL pamt;                                              //~vbdhI~
    int ii,rc=0;                                                   //~vbdhI~
//***************************                                      //~vbdhI~
	dprintf("%s:Pkey=%x,Pmod=%x\n",UTT,Pkey,Pmask);                //~vbdhI~
    for (ii=0,pamt=Saccmenutbl;ii<ACCMENUTBLENTNO;ii++,pamt++)     //~vbdhI~
    {                                                              //~vbdhI~
	    dprintf("%s:menuid=%s,key=%x,mod=%x\n",UTT,pamt->AMTstrid,pamt->AMTkey,pamt->AMTmodifier);//~vbdhI~
    	if (toupper(pamt->AMTkey)==toupper(Pkey) && pamt->AMTmodifier==Pmask)//~vbdhR~
        {                                                          //~vbdhI~
			gtk_accel_map_add_entry(pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier);//~vbdhI~
	        dprintf("%s:gtk_accel_map_add_entry %s,key=%x,mod=%x\n",UTT,pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier);//~vbdhI~
#ifdef QQQ                                                         //~vbdhR~
  	 		gtk_menu_item_set_accel_path(Pmenuitem,pamt->AMTpath); //~vbdhI~
	        dprintf("%s:gtk_menu_item_set_accel_path %s\n",UTT,pamt->AMTpath);//~vbdhI~
#else                                                              //~vbdhI~
    		gtk_widget_set_accel_path(Pmenuitem,pamt->AMTpath,Ppag);//~vbdhR~
	        dprintf("%s:gtk_widget_set_accel_path %s\n",UTT,pamt->AMTpath);//~vbdhI~
#endif                                                             //~vbdhI~
            rc=1;                                                  //~vbdhI~
            break;	                                               //~vbdhI~
        }                                                          //~vbdhI~
	}                                                              //~vbdhI~
	return rc;                                                     //~vbdhI~
}//gxemfrm_actinit_menuitem                                        //~vbdhI~
#endif //QQQ                                                       //~vbdhI~
//***********************************************                  //~vbd2I~
int gxemfrm_enablesubmenuitem(int Pitemid,int Penable)             //~vbd3R~
{                                                                  //~vbd3R~
    GtkMenuItem *pmenuitem;                                        //~vbd3R~
    char *pstrid=STRID_EDIT_SELECTALL;                             //~vbd3R~
//***************************                                      //~vbd3R~
    switch(Pitemid)                                                //~vbd3R~
    {                                                              //~vbd3R~
    case ID_EDIT_CUT:                                              //~vbd3R~
	    pstrid=STRID_EDIT_CUT;                                     //~vbd3R~
        break;                                                     //~vbd3R~
    case ID_EDIT_CLEAR:                                            //~vbd3R~
	    pstrid=STRID_EDIT_CLEAR;                                   //~vbd3R~
        break;                                                     //~vbd3R~
    case ID_EDIT_COPY:                                             //~vbd3R~
	    pstrid=STRID_EDIT_COPY;                                    //~vbd3R~
        break;                                                     //~vbd3R~
    case ID_EDIT_PASTE:                                            //~vbd3R~
	    pstrid=STRID_EDIT_PASTE;                                   //~vbd3R~
        break;                                                     //~vbd3R~
    case ID_EDIT_PASTE_REP:                                        //~vbd3R~
	    pstrid=STRID_EDIT_PASTE_REP;                               //~vbd3R~
        break;                                                     //~vbd3R~
    case ID_EDIT_PASTE_V:                                          //~vbd3R~
	    pstrid=STRID_EDIT_PASTE_V;                                 //~vbd3R~
        break;                                                     //~vbd3R~
    }                                                              //~vbd3R~
    pmenuitem=GTK_MENU_ITEM(lookup_widget(Gpframe,pstrid));        //~vbd3R~
#ifndef OPTGTK3                                                    //~vbd3R~
//	gtk_action_set_sensitive(GTK_WIDGET(pmenuitem),Penable);       //~vbd3R~
	gtk_widget_set_sensitive(GTK_WIDGET(pmenuitem),Penable);       //~vbd3R~
#else                                                              //~vbd3R~
	gtk_widget_set_sensitive(GTK_WIDGET(pmenuitem),Penable);       //~vbd3R~
#endif                                                             //~vbd3R~
    dprintf("%s:menuid=%d,enable=%d,menuitem=%p\n",UTT,Pitemid,Penable,pmenuitem);//~vbd3R~
    return 0;                                                      //~vbd3R~
}//gxemfrm_enablesubmenuitem                                       //~vbd3R~
//***********************************************                  //~v51dI~
//* set enable/disable toolbar button                              //~vXXEI~
//***********************************************                  //~vXXEI~
int  gxemfrm_enabletoolbar(int Penterid)                           //~vXXER~
{                                                                  //~v51dI~
    GtkWidget *pwd;                                                //~vXXEI~
    PCONTEXTMENUTBL pcmt;                                          //~vXXEI~
    int enablecopy,enablepaste,enablecut,ii,buttonid,flag;         //~vXXER~
    int enablepastev;                                              //~v66pI~
    int enableselectall;                                           //~vbd2I~
    int chngsw=0;                                                  //~v51dI~
    int flago=0;                                                   //~v66rR~
//***************************                                      //~v51dI~
    enablecopy =xxemain_cpupdatecopy();                            //~vXXER~
    enablecut  =xxemain_cpupdatecut();                             //~vXXER~
    enablepaste=xxemain_cpupdatepaste();                           //~vXXER~
    enablepastev=xxemain_cpupdatepastev();                         //~v66pI~
    enableselectall =xxemain_cpupdateselectall();                  //~vbd2I~
    for (ii=0,pcmt=Scontextmenutbl;ii<CONTEXTMENU_ITEMCTR;ii++,pcmt++)//~vXXER~
    {                                                              //~vXXEI~
		buttonid=pcmt->CMTid;                                      //~vXXER~
        pwd=pcmt->CMTptoolbarbutton;                               //~vXXER~
//      flag=1;    //enable if leave notify                        //~v66rR~
        flag=-1;   //enable if leave notify                        //~v66rI~
//      if (Penterid)   //enter notify                             //~v66rR~
            switch(buttonid)                                       //~vXXER~
            {                                                      //~vXXER~
            case ID_EDIT_CUT:                                      //~vXXER~
            case ID_EDIT_CLEAR:                                    //~vXXER~
                flago=Menablecut;                                  //~v66rI~
                flag=enablecut;                                    //~vXXER~
//printf("cut old=%d,new=%d\n",flago,flag);                        //~v66rR~
                break;                                             //~vXXER~
            case ID_EDIT_COPY:                                     //~vXXER~
                flago=Menablecopy;                                 //~v66rI~
                flag=enablecopy;                                   //~vXXER~
//printf("cpy old=%d,new=%d\n",flago,flag);                        //~v66rR~
                break;                                             //~vXXER~
            case ID_EDIT_PASTE:                                    //~vXXER~
            case ID_EDIT_PASTE_REP:                                //~vXXER~
                flago=Menablepaste;                                //~v66rI~
                flag=enablepaste;                                  //~vXXER~
//printf("paste old=%d,new=%d\n",flago,flag);                      //~v66rR~
                break;                                             //~vXXER~
            case ID_EDIT_PASTE_V:                                  //~v66pI~
                flago=Menablepastev;                               //~v66rI~
                flag=enablepastev;                                 //~v66pI~
//printf("pasteV old=%d,new=%d\n",flago,flag);                     //~v66rR~
                break;                                             //~v66pI~
            }                                                      //~vXXER~
      if (flag>=0 && flag!=flago)                                  //~v66rI~
      {                                                            //~v66rI~
        chngsw=1;                                                  //~v66rI~
		gtk_widget_set_sensitive(GTK_WIDGET(pwd),flag);            //~vXXEI~
		gxemfrm_enablesubmenuitem(buttonid,flag);                  //~vbd2I~
                                                                   //~vbd2I~
//      dprintf("edit toolbar button=%s,enable=%d\n",pcmt->CMTtbstrid,flag);//~v669R~
      }                                                            //~v66rI~
    }                                                              //~vXXEI~
    if (enableselectall!=Menableselectall)                         //~vbd2R~
		gxemfrm_enablesubmenuitem(ID_EDIT_SELECTALL,enableselectall);//~vbd2I~
//printf("chngsw=%d\n",chngsw);                                    //~v66rR~
    if (chngsw)                                                    //~v66rR~
        gtk_widget_show(Mtoolbar);                                 //~v66rI~
    Menableselectall=enableselectall;                              //~vbd2R~
    Menablecut=enablecut;                                          //~v66rI~
    Menablecopy=enablecopy;                                        //~v66rI~
    Menablepaste=enablepaste;                                      //~v66rI~
    Menablepastev=enablepastev;                                    //~v66rI~
    return 0;                                                      //~v51dI~
}//gxemfrm_enabletoolbar                                           //~v66rR~
//***********************************************                  //~3103I~
int  updatemenu(int Puseact)                                       //~vXXER~
{                                                                  //~3103I~
	int ii;                                                        //~vXXEI~
    PACCMENUTBL pamt;                                              //~vXXEI~
    gboolean rc2;                                                  //~vbd2I~
    int rc=0;                                                      //~vbd2R~
//**************************************                           //~vXXEI~
    for (ii=0,pamt=Saccmenutbl;ii<ACCMENUTBLENTNO;ii++,pamt++)     //~vXXEI~
    {                                                              //~vXXEI~
#ifndef QQQ                                                        //~vbdhR~
        if (Puseact)                                               //~vXXEI~
          rc2=                                                     //~vbd2I~
			gtk_accel_map_change_entry(pamt->AMTpath,pamt->AMTkey,pamt->AMTmodifier,0);//~vXXER~
        else                                                       //~vXXEI~
        {                                                          //~vbdjI~
          rc2=                                                     //~vbd2I~
			gtk_accel_map_change_entry(pamt->AMTpath,0,0,0);       //~vXXEI~
	    	dprintf("%s:gtk_accel_map_change_entry clear rc=%d\n",UTT,rc2);//~vbdjI~
        }                                                          //~vbdjI~
#ifndef SSS                                                        //~vbdjI~
#ifndef OPTGTK3                                                    //~vbdjI~
        dprintf("%s:label=%s\n",UTT,gtk_menu_item_get_label(pamt->AMTpmenuitem));//~vbdjR~
        if (Puseact)                                               //~vbdjI~
        	gtk_menu_item_set_label(pamt->AMTpmenuitem,pamt->AMTlabelon);//~vbdjR~
        else                                                       //~vbdjI~
        	gtk_menu_item_set_label(pamt->AMTpmenuitem,pamt->AMTlabeloff);//~vbdjR~
        dprintf("%s:label=%s\n",UTT,gtk_menu_item_get_label(pamt->AMTpmenuitem));//~vbdjI~
#endif                                                             //~vbdjI~
#endif                                                             //~vbdjI~
#else                                                              //~vbdhI~
    	gchar *gc3;                                                //~vbdhI~
            gc3=g_intern_static_string(pamt->AMTpath);//@@@@test   //~vbdhI~
            dprintf("%s:gc3=%p=%s\n",UTT,gc3,gc3);                 //~vbdhI~
        if (Puseact)                                               //~vbdhI~
          rc2=                                                     //~vbdhI~
			gtk_accel_map_change_entry(gc3,toupper(pamt->AMTkey),pamt->AMTmodifier,0);//~vbdhI~
        else                                                       //~vbdhI~
          rc2=                                                     //~vbdhI~
			gtk_accel_map_change_entry(gc3,0,0,0);                 //~vbdhI~
#endif                                                             //~vbdhI~
        if (!rc2)                                                  //~vbd2I~
        	rc++;                                                  //~vbd2I~
    	dprintf("%s:gtk_accel_map_change_entry rc=%d,useact=%d,key=%x,mod=%d,amtpath=%s\n",UTT,rc2,Puseact,pamt->AMTkey,pamt->AMTmodifier,pamt->AMTpath);//~vbd2I~//~vbdhR~
    	dprintf("%s:menuitem=%p,path=%s\n",UTT,pamt->AMTpmenuitem,gtk_menu_item_get_accel_path(pamt->AMTpmenuitem));//~vbd2I~
#ifndef SSS                                                        //~vbdjI~
		{                                                          //~vbdjI~
        	dprintf("%s:label=%s\n",UTT,gtk_menu_item_get_label(pamt->AMTpmenuitem));//~vbdjI~
        }                                                          //~vbdjI~
#endif                                                             //~vbdjI~
                                                                   //~vbdjI~
	}                                                              //~vXXEI~
//  return 0;                                                      //~3103I~//~vbd2R~
    return rc;  //fail count                                       //~vbd2I~
}//updatemenu                                                      //~3103I~
//***********************************************                  //~3104I~
//*update mein manue text                                          //~3104I~
//*return:1:updated                                                //~3104I~
//***********************************************                  //~3104I~
int  gxemfrm_updatemainmenu(int Pusemk)                            //~vXXER~
{                                                                  //~3104I~
#ifndef XXE                                                        //~vXXEI~
    CMenu *pmenu;                                                  //~3105I~
	int ii,cmdid,updatesw=0;                                       //~3104R~
    char menutext[64];                                             //~3104I~
#endif                                                             //~vXXEI~
static int Susemk=-1;                                              //~vXXER~
    int ii;                                                        //~vXXEI~
    PMAINMENUTBL pmt;                                              //~vXXER~
//***************************                                      //~3104I~
//	if (Pusemk!=-1)        //init req from wxe.cpp                 //~vXXER~
//  {                                                              //~vXXER~
    	if (Susemk==Pusemk)   //not changed                        //~vXXER~
            return 0;                                              //~3105I~
        else                                                       //~3105I~
            Susemk=Pusemk;                                         //~vXXER~
//  }                                                              //~vXXER~
    for (ii=0,pmt=Smainmenutbl;ii<MAINMENUTBLENTNO;ii++,pmt++)     //~vXXER~
		updatemainmenutext(pmt,Pusemk);                            //~vXXER~
    return 1;                                                      //~vXXEI~
}//gxemfrm_updatemainmenu                                          //~vXXER~
//***********************************************                  //~3104I~
//*ret 0:no update required                                        //~3104I~
//***********************************************                  //~3104I~
//nt  CMainFrame::updatemainmenutext(int Pmenupos,char *Ptext,int Pusemk)//~vXXER~
int  updatemainmenutext(PMAINMENUTBL Ppmt,int Pusemk)              //~vXXEI~
{                                                                  //~3104I~
    if (Pusemk) //set on                                           //~vXXEI~
    {                                                              //~vXXEI~
        gtk_label_set_text_with_mnemonic(Ppmt->MMTplabel,Ppmt->MMTlabelon);//~vXXER~
        dprintf("menu on %s\n",Ppmt->MMTlabelon);                  //~v669R~
    }                                                              //~vXXEI~
    else                                                           //~vXXEI~
    {                                                              //~vXXEI~
        gtk_label_set_text(Ppmt->MMTplabel,Ppmt->MMTlabeloff);     //~vXXEI~
        dprintf("menu off %s\n",Ppmt->MMTlabeloff);                //~v669R~
    }                                                              //~vXXEI~
    return 1;                                                      //~vXXEI~
}//updatemainmenutext                                              //~3104I~
//***********************************************                  //~vbdnI~
int  updateMenuIcon(int Popt,int Pchkidx,int Piconidx)             //~vbdnR~
{                                                                  //~vbdnI~
    GtkWidget *pwd;                                                //~vbdnI~
    PCONTEXTMENUTBL pcmt;                                          //~vbdnI~
    int enable,rc=0,stat;                                          //~vbdnR~
//********************************                                 //~vbdnI~
    enable=wxe_chkEnableFileSubmenu(0,Pchkidx); //xxexei3.c        //~vbdnI~
	pcmt=Scontextmenutbl+Piconidx;                                 //~vbdnR~
    pwd=pcmt->CMTptoolbarbutton;                                   //~vbdnI~
	stat=gtk_widget_get_sensitive(GTK_WIDGET(pwd));                //~vbdnI~
    if (stat!=enable)                                              //~vbdnI~
    {                                                              //~vbdnI~
		gtk_widget_set_sensitive(GTK_WIDGET(pwd),enable);          //~vbdnR~
        rc=1;                                                      //~vbdnI~
    }                                                              //~vbdnI~
	dprintf("%s:chkidx=%d,iconidx=%d,enable=%x,stat=%d,rc=%d\n",UTT,Pchkidx,Piconidx,enable,stat,rc);//~vbdnR~
    return  rc;                                                    //~vbdnI~
}//updateMenuIcon                                                  //~vbdnI~
//***********************************************                  //~vbdnI~
//*update mein manue text                                          //~vbdnI~
//*return:1:updated                                                //~vbdnI~
//***********************************************                  //~vbdnI~
int updatemainmenuFile(void)                                       //~vbdnR~
{                                                                  //~vbdnI~
	int ii,menuid,chkidx,updatectr=0,stat,enable;                  //~vbdnR~
    GtkMenuItem *pmenuitem;                                        //~vbdnI~
    PACCMENUTBL pamt;                                              //~vbdnI~
//**************************************                           //~vbdnI~
    for (ii=0,pamt=Saccmenutbl;ii<ACCMENUTBLENTNO;ii++,pamt++)     //~vbdnI~
    {                                                              //~vbdnI~
        menuid=pamt->AMTid;                                        //~vbdnI~
        pmenuitem=pamt->AMTpmenuitem;                              //~vbdnI~
	    dprintf("%s:ii=%d,menuid=%d=%s,pmenuitem=%p\n",UTT,ii,menuid,pamt->AMTstrid,pmenuitem);//~vbdnI~
        switch (menuid)                                            //~vbdnI~
        {                                                          //~vbdnI~
        case ID_FILE_SAVE:                                         //~vbdnI~
        	chkidx=CHKSTF_SAVE;                                    //~vbdnI~
            break;                                                 //~vbdnI~
        case ID_FILE_SAVEAS:                                       //~vbdnI~
        	chkidx=CHKSTF_SAVEAS;                                  //~vbdnI~
            break;                                                 //~vbdnI~
        case ID_FILE_PRINT:                                        //~vbdnI~
        	chkidx=CHKSTF_PRINT;                                   //~vbdnI~
            break;                                                 //~vbdnI~
        default:                                                   //~vbdnI~
        	chkidx=-1;                                             //~vbdnI~
        }                                                          //~vbdnI~
        if (chkidx>=0)                                             //~vbdnI~
        {                                                          //~vbdnI~
			stat=gtk_widget_get_sensitive(GTK_WIDGET(pmenuitem));  //~vbdnR~
        	enable=wxe_chkEnableFileSubmenu(0,chkidx); //wxexei3   //~vbdnI~
        	dprintf("%s:set_sensitive chkidx=%d,enable=%d,stat=%d\n",UTT,chkidx,enable,stat);//~vbdnI~
            if (enable!=stat)                                      //~vbdnI~
            {                                                      //~vbdnI~
				gtk_widget_set_sensitive(GTK_WIDGET(pmenuitem),enable);//~vbdnI~
            	updatectr++;                                       //~vbdnR~
            }                                                      //~vbdnI~
        }                                                          //~vbdnI~
	}                                                              //~vbdnI~
    return updatectr;                                              //~vbdnI~
}//updatemainmenuFile                                              //~vbdnI~
//***********************************************                  //~vbdnI~
int gxemfrm_updateFileMenu(int Popt)                               //~vbdnI~
{                                                                  //~vbdnI~
    int rc;                                                        //~vbdnI~
//********************************                                 //~vbdnI~
	rc=updatemainmenuFile();                                       //~vbdnR~
//*toolbar save icon                                               //~vbdnI~
	rc+=updateMenuIcon(0,CHKSTF_SAVE,TOOLBARINDEX_SAVE);           //~vbdnR~
    return  rc;                                                    //~vbdnI~
}//updateFileManu                                                  //~vbdnI~
//***************************************************************************//~vXXEM~
//* mainmenu enter notify callback                                 //~vXXEM~
//***************************************************************************//~vXXEM~
void on_mainmenu_enter_notify_edit(GtkMenuItem     *Pmenuitem,     //~vXXEM~
                              GdkEventCrossing *Pevent,            //~vXXEM~
                              gpointer         Puser_data)         //~vXXEM~
{                                                                  //~vXXEM~
	int ii;                                                        //~vXXEM~
    PCONTEXTMENUTBL pcmt;                                          //~vXXEI~
//*********************                                            //~vXXEM~
    dprintf("mainmenu enter notify=%p\n",Pmenuitem);               //~v669R~
    for (ii=0,pcmt=Scontextmenutbl;ii<CONTEXTMENU_ITEMCTR;ii++,pcmt++)//~vXXER~
	  if (pcmt->CMTfunc)                                           //~vbdnR~
		(pcmt->CMTfunc)(pcmt->CMTpmenuitem);	//enable func call //~vbdnI~
    return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//***************************************************************************//~vXXEM~
//* mainmenu init <--gxemfrm_realize                               //~vXXEM~
//***************************************************************************//~vXXEM~
void mainmenu_init(void)                                           //~vXXEM~
{                                                                  //~vXXEM~
    GtkMenuItem *pmenuitem;                                        //~vXXEM~
    char *pci,*pco;                                                //~vXXER~
    int ii,jj;                                                     //~vXXEM~
    PMAINMENUTBL pmt;                                              //~vXXEM~
    PCONTEXTMENUTBL pcmt;                                          //~vXXEI~
//******************************                                   //~vXXEM~
//for mainmenu to usemk(menu key usage) change                     //~vXXEM~
    for (ii=0,pmt=Smainmenutbl;ii<MAINMENUTBLENTNO;ii++,pmt++)     //~vXXER~
    {                                                              //~vXXEM~
	    pmenuitem=(GtkMenuItem*)lookup_widget(GTK_WIDGET(Gpframe),pmt->MMTstrid); //edit menuitem//~vXXEM~
    	pmt->MMTpmenuitem=pmenuitem;                               //~vXXEM~
        pmt->MMTplabel=(GtkLabel*)gtk_bin_get_child(GTK_BIN(pmenuitem));	//label//~vXXEM~
//      ptext=(char*)gtk_label_get_label(pmt->MMTplabel);          //~vXXER~
//      strncpy(pmt->MMTlabelon,ptext,sizeof(pmt->MMTlabelon)-1);  //~vXXER~
        pci=pmt->MMTlabelon;                                       //~vXXEM~
        pco=pmt->MMTlabeloff;                                      //~vXXEM~
        for (jj=0;jj<strlen(pmt->MMTlabelon);jj++,pci++)           //~vXXEM~
            if (*pci!='_')                                         //~vXXEM~
                *pco++=*pci;                                       //~vXXEM~
        *pco=0;                                                    //~vXXEM~
        dprintf("menu label wiget=%p,ii=%d,on=%s,off=%s\n",pmenuitem,ii,pmt->MMTlabelon,pmt->MMTlabeloff);//~v669R~//~vbdbR~
    }                                                              //~vXXEM~
    gxemfrm_updatemainmenu(Mwxeinidata.WXEINIusemk) ;	//set menukey enable/disable//~vXXER~
	actinit();	//accelerater tbl init                             //~vXXER~
	gxemfrm_Loadact(Mwxeinidata.WXEINIuseact);                     //~vXXEI~
//for edit submenu to enable/disable                               //~vXXEM~
    pmenuitem=(GtkMenuItem*)lookup_widget(GTK_WIDGET (Gpframe),STRID_EDIT); //edit menuitem//~vXXEM~
	g_signal_connect ((gpointer)pmenuitem,"enter_notify_event",    //~vXXEM~
                    G_CALLBACK (on_mainmenu_enter_notify_edit),    //~vXXEM~
                    NULL);                                         //~vXXEM~
//get context menuitem widget addr                                 //~vXXER~
    for (ii=0,pcmt=Scontextmenutbl;ii<CONTEXTMENU_ITEMCTR;ii++,pcmt++)//~vXXER~
    {                                                              //~vXXEM~
		pcmt->CMTpmenuitem=(GtkMenuItem*)lookup_widget (GTK_WIDGET (Gpframe),pcmt->CMTstrid); //edit menuitem//~vXXER~
        dprintf("edit menu widget=%p,str=%s\n",pcmt->CMTpmenuitem,pcmt->CMTstrid);//~v669R~
    }                                                              //~vXXEM~
    return;                                                        //~vXXEM~
}//mainmenu_init                                                   //~vXXEM~
//***************************************************************************//~vXXEM~
//* toolbar init                                                   //~vXXEI~
//***************************************************************************//~vXXEM~
void toolbar_init(void)                                            //~vXXEM~
{                                                                  //~vXXEM~
	PCONTEXTMENUTBL pcmt;                                          //~vXXER~
    int ii;                                                        //~vXXEM~
//******************************                                   //~vXXEM~
//get button widget addr                                           //~vXXEM~
    for (ii=0,pcmt=Scontextmenutbl;ii<CONTEXTMENU_ITEMCTR;ii++,pcmt++)//~vXXER~
    {                                                              //~vXXEM~
		pcmt->CMTptoolbarbutton=(GtkWidget*)lookup_widget(GTK_WIDGET(Gpframe),pcmt->CMTtbstrid); //edit menuitem//~vXXER~
        dprintf("edit toolbar widget=%p,str=%s\n",pcmt->CMTptoolbarbutton,pcmt->CMTtbstrid);//~v669R~
    }                                                              //~vXXEM~
    return;                                                        //~vXXEM~
}//toolbar_init                                                    //~vXXEM~
void gxemfrm_OnHelp(void)                                          //~v669R~
{
//    char fnm[_MAX_PATH],uri[_MAX_PATH+8],*phd,**pphd;              //~v669R~,//~v71AR~
//    GError *perr=0;                                                //~v669I~,//~v71AR~
//    int rc;                                                        //~v669I~,//~v71AR~
//    char *helpdir[]={"~/xehelp",DEF_HELPDIR,0};                    //~v669I~,//~v71AR~
//    FILEFINDBUF3 ffb3;                                             //~v669I~,//~v71AR~
//    char *html;                                                    //~v66BI~,//~v71AR~
//#ifndef XXE                                                      //~v71AR~
//    int ctxid;                                                   //~v71AR~
////******************                                             //~v71AR~
////  Mpapp->WinHelp(0,HELP_CONTENTS);                             //~v71AR~
////  Mpapp->WinHelp(0,HELP_FINDER);                               //~v71AR~
//    if (wxegetdbcsmode())                                        //~v71AR~
//        ctxid=IDH_JAPANESE;                                      //~v71AR~
//    else                                                         //~v71AR~
//        ctxid=IDH_ENGLISH;                                       //~v71AR~
//    WinHelp(ctxid,HELP_CONTEXT);                                 //~v71AR~
//#endif                                                           //~v71AR~
//	fnm="file:///d/mydoc/hpb/xehelp/index.htm";                    //~v669R~
//    if (wxegetdbcsmode())                                          //~v66BI~,//~v71AR~
//        html="/indexj.htm";                                        //~v66BI~,//~v71AR~
//    else                                                           //~v66BI~,//~v71AR~
//        html="/indexe.htm";                                        //~v66BI~,//~v71AR~
//    phd=Ghelpdir;                                                  //~v669I~ ,//~v71AR~
//    if (phd)                                                       //~v669I~,//~v71AR~
//    {                                                              //~v669I~,//~v71AR~
////      sprintf(fnm,"%s/index.htm",phd);                           //~v66BR~,//~v71AR~
//        sprintf(fnm,"%s%s",phd,html);                              //~v66BI~,//~v71AR~
//        if (ufstat(fnm,&ffb3))                                     //~v669I~,//~v71AR~
//        {                                                          //~v669I~,//~v71AR~
//            uerrmsg("%s is not found",0,                           //~v669R~,//~v71AR~
//                    fnm);                                          //~v669I~,//~v71AR~
//            phd=0;//errid                                          //~v669I~,//~v71AR~
//        }                                                          //~v669I~,//~v71AR~
//    }                                                              //~v669I~,//~v71AR~
//    else                                                           //~v669I~,//~v71AR~
//    {                                                              //~v669I~,//~v71AR~
//        for (pphd=helpdir;;pphd++)                                 //~v669I~,//~v71AR~
//        {                                                          //~v669I~,//~v71AR~
//            phd=*pphd;                                             //~v669I~,//~v71AR~
//            if (!phd)                                              //~v669I~,//~v71AR~
//                break;  //eol                                      //~v669I~,//~v71AR~
//            ufullpath(fnm,phd,_MAX_PATH);                          //~v669R~,//~v71AR~
////          strcat(fnm,"/index.htm");                              //~v66BR~,//~v71AR~
//            strcat(fnm,html);                                      //~v66BI~,//~v71AR~
//            if (!ufstat(fnm,&ffb3))                                //~v669I~,//~v71AR~
//                break;                                             //~v669I~,//~v71AR~
//        }                                                          //~v669I~,//~v71AR~
//        if (!phd)                                                  //~v669I~,//~v71AR~
////          uerrmsg("helpdir/index.htm not found on %s nor %s",0,  //~v66BR~,//~v71AR~
////                  helpdir[0],helpdir[1]);                        //~v66BI~,//~v71AR~
//            uerrmsg("helpdir%s not found on %s nor %s",0,          //~v66BI~,//~v71AR~
//                    html,helpdir[0],helpdir[1]);                   //~v66BI~,//~v71AR~
//    }                                                              //~v669I~,//~v71AR~
//    if (phd)                                                       //~v669R~,//~v71AR~
//    {                                                              //~v669I~,//~v71AR~
//        sprintf(uri,"file://%s",fnm);                              //~v669I~,//~v71AR~
//        rc=gnome_help_display_uri(uri,&perr);                      //~v669R~,//~v71AR~
//        PRINTGERR("gxemfrm_OnHelp-gnome_help_display_uri",perr);   //+v69rR~,//~v71AR~
//        if (!rc)    //false                                        //~v669R~,//~v71AR~
//            uerrmsg("%s exist?\n",uri);                            //~v669R~,//~v71AR~
//    }                                                              //~v669I~,//~v71AR~
//    xxe_scrdisp();//display errmsg                                 //~v669I~,//~v71AR~
	wxe_helpcall();                                                //~v71AI~
	xxemain_scrinvalidate(0);                                      //~v669I~
    return;                                                        //~v669I~
}//gxemain_OnHelp                                                  //~v669R~
//***************************************************************************//~vXXEI~
//* search mainmenu menuitem tbl to get widget name                //~vXXEI~
//***************************************************************************//~vXXEI~
int mainmenu_srchmenuitem(GtkWidget *Ppmenuitem)                   //~vXXER~
{                                                                  //~vXXEI~
	int ii;                                                        //~vXXEI~
    PCONTEXTMENUTBL pcmt;                                          //~vXXEI~
//********************************                                 //~vXXEI~
	for (ii=0,pcmt=Scontextmenutbl;ii<CONTEXTMENU_ITEMCTR;ii++,pcmt++)//~vXXER~
		if (GTK_WIDGET(pcmt->CMTpmenuitem)==Ppmenuitem)            //~vXXER~
        	return ii;                                             //~vXXEI~
    return -1;                                                     //~vXXEI~
}//mainmenu_srchmenuitem                                           //~vXXEI~
                                                                   //~vXXEI~
//***************************************************************************//~vXXEI~
//* popupmenu init                                                 //~vXXEI~
//***************************************************************************//~vXXEI~
void popupmenu_initCHL(void)                                       //~vbj2I~
{                                                                  //~vbj2I~
#ifndef OPTGTK3                                                    //~vbj2I~
	GnomeUIInfo *puiinfo;                                          //~vbj2I~
    int itemcount,ii,itemidx;                                      //~vbj2I~
#else                                                              //~vbj2I~
#endif                                                             //~vbj2I~
//******************************                                   //~vbj2I~
	GppopupmenuCHL=gtk_menu_new();                                 //~vbj2I~
    g_signal_connect(GppopupmenuCHL,"deactivate",G_CALLBACK(popupmenu_deactivate_callback),NULL);//~vbj2I~
#ifndef OPTGTK3                                                    //~vbj2I~
	gnome_app_fill_menu (GTK_MENU_SHELL(GppopupmenuCHL),SpopupmenuuiinfoCHL,//~vbj2I~
			     NULL,TRUE,0);	//acc group,underline accelerator efective,menuitem insert pos//~vbj2I~
	itemcount=sizeof(SpopupmenuuiinfoCHL)/sizeof(SpopupmenuuiinfoCHL[0]);//~vbj2R~
	for (ii=0,puiinfo=SpopupmenuuiinfoCHL;ii<itemcount;ii++,puiinfo++)//~vbj2I~
    {                                                              //~vbj2I~
    	itemidx=(int)(ULONG)(puiinfo->user_data)-1;	//gpointer     //~vbj2I~
        if (itemidx>=0)    //not seperator                         //~vbj2I~
        {                                                          //~vbj2I~
        	 dprintf("idx=%d,menuitem=%p\n",itemidx,puiinfo->widget);//~vbj2I~
			SpopupmenutblCHL[itemidx].PMTpmenuitem=(GtkMenuItem*)(puiinfo->widget);		//save menuitem widget ptr//~vbj2I~
        }                                                          //~vbj2I~
    }                                                              //~vbj2I~
#else                                                              //~vbj2I~
	gxemfrm_create_popupmenuCHL();                                 //~vbj2I~
#endif                                                             //~vbj2I~
    return;                                                        //~vbj2I~
}//popupmenu_initCHL                                               //~vbj2I~
//***************************************************************************//~vbj2I~
void popupmenu_init(void)                                          //~vXXER~
{                                                                  //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
	GnomeUIInfo *puiinfo;                                          //~vXXER~
    int itemcount,ii,itemidx;                                      //~vXXEI~
#else                                                              //~var8R~
#endif                                                             //~var8R~
//******************************                                   //~vXXEI~
	Gppopupmenu=gtk_menu_new();                                    //~vXXEI~
    g_signal_connect(Gppopupmenu,"deactivate",G_CALLBACK(popupmenu_deactivate_callback),NULL);//~vXXER~
#ifdef AAA                                                         //~vXXEI~
	append_menuitem_by_stockid(ID_EDIT_CUT,      GTK_STOCK_CUT);   //~vXXER~
	append_menuitem_by_stockid(ID_EDIT_CLEAR,    GTK_STOCK_CLEAR); //~vXXER~
	append_menuitem_by_stockid(ID_EDIT_COPY,     GTK_STOCK_COPY);  //~vXXER~
	append_menuitem_by_stockid(ID_EDIT_PASTE,    GTK_STOCK_PASTE); //~vXXER~
	append_menuitem_by_stockid(ID_EDIT_PASTE_REP,GTK_STOCK_PASTE); //~vXXEI~
	append_menuitem_by_stockid(ID_EDIT_CANCEL,   GTK_STOCK_CANCEL);//~vXXER~
	append_menuitem_by_stockid(ID_EDIT_END,      GTK_STOCK_PASTE); //~vXXER~
	append_menuitem_by_stockid(ID_FILE_SAVE,     GTK_STOCK_SAVE);  //~vXXER~
	append_menuitem_by_stockid(ID_FILE_OPENWITH, GTK_STOCK_OPEN);  //~vXXER~
#else                                                              //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
	gnome_app_fill_menu (GTK_MENU_SHELL(Gppopupmenu),Spopupmenuuiinfo,//~vXXEI~
			     NULL,TRUE,0);	//acc group,underline accelerator efective,menuitem insert pos//~vXXEI~
	itemcount=sizeof(Spopupmenuuiinfo)/sizeof(Spopupmenuuiinfo[0]);//~vXXEI~
	for (ii=0,puiinfo=Spopupmenuuiinfo;ii<itemcount;ii++,puiinfo++)//~vXXER~
    {                                                              //~vXXEI~
//  	itemidx=(int)(puiinfo->user_data)-1;                       //~vXXER~//~va72R~
    	itemidx=(int)(ULONG)(puiinfo->user_data)-1;	//gpointer     //~va72I~
        if (itemidx>=0)    //not seperator                         //~vXXEI~
        {                                                          //~vXXEI~
        	 dprintf("idx=%d,menuitem=%p\n",itemidx,puiinfo->widget);//~v669R~
			Spopupmenutbl[itemidx].PMTpmenuitem=(GtkMenuItem*)(puiinfo->widget);		//save menuitem widget ptr//~vXXER~
        }                                                          //~vXXEI~
    }                                                              //~vXXEI~
#else                                                              //~var8R~
	gxemfrm_create_popupmenu();                                    //~var8R~
#endif                                                             //~var8R~
#endif                                                             //~vXXEI~
	popupmenu_initCHL();                                           //~vbj2I~
    return;                                                        //~vXXEI~
}//popupmenu_init                                                  //~vXXER~
#ifdef AAA                                                         //~vXXEI~
//***************************************************************************//~vXXEI~
//* popupmenu menuitem append by stock id                          //~vXXEI~
//***************************************************************************//~vXXEI~
int append_menuitem_by_stockid(int Pitemid,char *Pstockid)         //~vXXEI~
{                                                                  //~vXXEI~
	GtkWidget *menuitem;                                           //~vXXEI~
    int itemtbidx;                                                 //~vXXEI~
//******************************                                   //~vXXEI~
	itemtbidx=popupmenu_srchid(Pitemid);                           //~vXXEI~
    if (itemtbidx<0)                                               //~vXXER~
    	return -1;                                                 //~vXXEI~
	 dprintf("apend stoc menuitemid=%d,stockid=%s\n",Pitemid,Pstockid);//~v669R~
//	menuitem=gtk_image_menu_item_new_from_stock(Pstockid,NULL);//NULL:GtkAccelGroup//~vXXER~
  	menuitem=gtk_image_menu_item_new_with_mnemonic("_File");       //~vXXER~
  	g_signal_connect(menuitem,"activate",G_CALLBACK(popupmenu_activate_callback),(gpointer)Pitemid);//~vXXER~
	 dprintf("activate signal connect\n");                          //~v669R~
	gtk_widget_show (menuitem);                                    //~vXXEI~
  	gtk_menu_shell_append (GTK_MENU_SHELL(Gppopupmenu), menuitem); //~vXXER~
    Spopupmenuitemtbl[itemtbidx]=menuitem;                         //~vXXER~
    return itemtbidx;                                              //~vXXER~
}                                                                  //~vXXEI~
#endif                                                             //~vXXEI~
//***************************************************************************//~vXXEI~
//* popupmenu activate callback                                    //~vXXEI~
//***************************************************************************//~vXXEI~
void popupmenu_deactivate_callback(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vXXEI~
{                                                                  //~vXXEI~
//******************************                                   //~vXXEI~
	Mfloatmenusw=0;                                                //~vXXEI~
	 dprintf("popupmenu deactivate cb\n"); 	//file print           //~v669R~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* popupmenu activate callback,emit by menu                       //~vXXER~
//***************************************************************************//~vXXEI~
void popupmenu_activate_callback(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vXXER~
{                                                                  //~vXXEI~
    int itemtbidx;                                                 //~vXXEI~
    char *strid;                                                   //~vXXEI~
//******************************                                   //~vXXEI~
//	 dprintf("popupmenu activate cb menuitemid=%d\n",(int)Puparm);  //~v669R~//~va72R~
  	 dprintf("popupmenu activate cb menuitemid=%p\n",Puparm);      //~va72I~
//  itemtbidx=popupmenu_srchid((int)Puparm);                       //~vXXER~
//  if (itemtbidx<0)                                               //~vXXER~
//  	return;                                                    //~vXXER~
//  itemtbidx=(int)Puparm-1;                                       //~vXXER~//~va72R~
    itemtbidx=(int)(ULONG)Puparm-1;                                //~va72I~
    if (itemtbidx>=0)                                              //~vXXER~
    {                                                              //~vXXEI~
		strid=Spopupmenutbl[itemtbidx].PMTstrid;                   //~vXXER~
		uactivate_menuitem(strid); 	//file print                   //~vXXER~
		 dprintf("popupmenu activate cb menuitem=%s\n",strid); 	//file print//~v669R~
    }                                                              //~vXXEI~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vbj2I~
//* CHL popupmenu activate callback for CHL cmd                    //~vbj2I~
//***************************************************************************//~vbj2I~
void popupmenu_activate_callbackCHLCMD(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vbj2I~
{                                                                  //~vbj2I~
    int itemtbidx,menuid;                                          //~vbj2I~
    int cmd=0;                                                     //~vbj2I~
//******************************                                   //~vbj2I~
  	dprintf("%s:parm=%p\n",UTT,Puparm);                            //~vbj2I~
    itemtbidx=(int)(ULONG)Puparm-1;                                //~vbj2I~
    if (itemtbidx>=0)                                              //~vbj2I~
    {                                                              //~vbj2I~
    	menuid=SpopupmenutblCHL[itemtbidx].PMTid;                  //~vbj2I~
        switch(menuid)                                             //~vbj2I~
        {                                                          //~vbj2I~
        case ID_CHL_EXE_CLOSED:                                    //~vbj2I~
            cmd='x';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        case ID_CHL_EXE_CURRENT:                                   //~vbj2I~
            cmd='X';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        case ID_CHL_EXE_SPLIT:                                     //~vbj2I~
            cmd='y';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        case ID_CHL_SET_CLOSED:                                    //~vbj2I~
            cmd='s';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        case ID_CHL_SET_CURRENT:                                   //~vbj2I~
            cmd='S';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        case ID_CHL_SET_SPLIT:                                     //~vbj2I~
            cmd='t';                                               //~vbj2I~
        	break;                                                 //~vbj2I~
        default:                                                   //~vbj2I~
        	return;                                                //~vbj2I~
        }                                                          //~vbj2I~
		dprintf("%s: strid=%s,cmd=%c\n",UTT,SpopupmenutblCHL[itemtbidx].PMTstrid,cmd);//~vbj2R~
        onfileCHL(cmd);	                                           //~vbj2I~
    }                                                              //~vbj2I~
    return;                                                        //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vbj2I~
//* CHL popupmenu activate callback,emit by main menu              //~vbj2R~
//***************************************************************************//~vbj2I~
void popupmenu_activate_callbackCHL(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vbj2I~
{                                                                  //~vbj2I~
    int itemtbidx;                                                 //~vbj2I~
    char *strid;                                                   //~vbj2R~
//******************************                                   //~vbj2I~
  	dprintf("%s:parm=%p\n",UTT,Puparm);                            //~vbj2R~
    itemtbidx=(int)(ULONG)Puparm-1;                                //~vbj2I~
    if (itemtbidx>=0)                                              //~vbj2I~
    {                                                              //~vbj2I~
    	strid=SpopupmenutblCHL[itemtbidx].PMTstrid;                //~vbj2R~
    	uactivate_menuitem(strid);                                 //~vbj2R~
		dprintf("%s: strid=%s\n",UTT,SpopupmenutblCHL[itemtbidx].PMTstrid);//~vbj2M~
    }                                                              //~vbj2I~
    return;                                                        //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vXXEI~
//* popupmenu activate callback,emit by toolbar button             //~vXXER~
//***************************************************************************//~vXXEI~
void popupmenu_activate_callback2(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vXXEI~
{                                                                  //~vXXEI~
    int itemtbidx;                                                 //~vXXEI~
    char *strid;                                                   //~vXXEI~
//******************************                                   //~vXXEI~
//	 dprintf("popupmenu activate cb2 menuitemid=%d\n",(int)Puparm); //~v669R~//~va72R~
	 dprintf("popupmenu activate cb2 menuitemid=%p\n",Puparm);     //~va72I~
//  itemtbidx=(int)Puparm-1;                                       //~vXXER~//~va72R~
    itemtbidx=(int)(ULONG)Puparm-1;                                //~va72I~//~vbd2R~
    if (itemtbidx>=0)                                              //~vXXER~
    {                                                              //~vXXEI~
		strid=Spopupmenutbl[itemtbidx].PMTstrid;                   //~vXXEI~
		uclick_toolbarbutton(strid); 	//file print               //~vXXER~
		 dprintf("popupmenu activate cb2 menuitem=%s\n",strid); 	//file print//~v669R~
    }                                                              //~vXXEI~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vbj2I~
//* CHL popupmenu activate callback,emit by toolbar button         //~vbj2I~
//***************************************************************************//~vbj2I~
void popupmenu_activate_callback2CHL(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vbj2I~
{                                                                  //~vbj2I~
    int itemtbidx;                                                 //~vbj2I~
    char *strid;                                                   //~vbj2I~
//******************************                                   //~vbj2I~
	dprintf("%s:menuitemid=%p\n",UTT,Puparm);                      //~vbj2I~
    itemtbidx=(int)(ULONG)Puparm-1;                                //~vbj2I~
    if (itemtbidx>=0)                                              //~vbj2I~
    {                                                              //~vbj2I~
		strid=SpopupmenutblCHL[itemtbidx].PMTstrid;                //~vbj2I~
		uclick_toolbarbutton(strid); 	//file print               //~vbj2I~
		dprintf("%s:menuitem=%s\n",UTT,strid); 	//file print       //~vbj2I~
    }                                                              //~vbj2I~
    return;                                                        //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vXXEI~
//* popupmenu activate callback                                    //~vXXEI~
//***************************************************************************//~vXXEI~
void popupmenu_activate_openwith(GtkWidget  *Ppmenuitem,gpointer Puparm)//~vXXEI~
{                                                                  //~vXXEI~
//******************************                                   //~vXXEI~
//	 dprintf("popupmenu activate openwith itemid=%d\n",(int)Puparm);//~v669R~//~va72R~
	 dprintf("popupmenu activate openwith itemid=%p\n",Puparm);    //~va72I~
    gxeview_OnFileOpenwith();                                      //~vXXER~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vbj2I~
int popupmenu_srchidCHL(int Pitemid)                               //~vbj2I~
{                                                                  //~vbj2I~
	int ii;                                                        //~vbj2I~
//********************************                                 //~vbj2I~
	for (ii=0;ii<POPUPMENU_ITEMCTR_CHL;ii++)                       //~vbj2I~
		if (SpopupmenutblCHL[ii].PMTid==Pitemid)                   //~vbj2I~
        	return ii;                                             //~vbj2I~
    return -1;                                                     //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vXXEI~
//* search popupmenu item id tbl                                   //~vXXEI~
//***************************************************************************//~vXXEI~
//int popupmenu_srchid(Pitemid)                                    //~vb74R~
int popupmenu_srchid(int Pitemid)                                  //~vb74I~
{                                                                  //~vXXEI~
	int ii;                                                        //~vXXEI~
//********************************                                 //~vXXEI~
	for (ii=0;ii<POPUPMENU_ITEMCTR;ii++)                           //~vXXEI~
		if (Spopupmenutbl[ii].PMTid==Pitemid)                      //~vXXER~
        	return ii;                                             //~vXXEI~
    return -1;                                                     //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vbj2I~
//* get itemid from CHL tbl index                                  //~vbj2I~
//***************************************************************************//~vbj2I~
GtkWidget *gxemfrm_popupmenu_getmenuitemCHL(int Pitemid)           //~vbj2I~
{                                                                  //~vbj2I~
	int itemtbidx;                                                 //~vbj2I~
//**************************                                       //~vbj2I~
	itemtbidx=popupmenu_srchidCHL(Pitemid);                        //~vbj2R~
    if (itemtbidx<0)                                               //~vbj2I~
    	return 0;                                                  //~vbj2I~
	return (GtkWidget*)(SpopupmenutblCHL[itemtbidx].PMTpmenuitem); //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vXXEI~
//* get itemid from tbl index                                     //~vXXER~//~vbj2R~
//***************************************************************************//~vXXEI~
GtkWidget *gxemfrm_popupmenu_getmenuitem(int Pitemid)              //~vXXER~
{                                                                  //~vXXEI~
	int itemtbidx;                                                 //~vXXER~
//**************************                                       //~vXXEI~
	if (Gxxestat & GXXES_POPUPMENU_CHL)                            //~vbj2I~
		return gxemfrm_popupmenu_getmenuitemCHL(Pitemid);          //~vbj2I~
	itemtbidx=popupmenu_srchid(Pitemid);                           //~vXXER~
    if (itemtbidx<0)                                               //~vXXER~
    	return 0;                                                  //~vXXEI~
	return (GtkWidget*)(Spopupmenutbl[itemtbidx].PMTpmenuitem);    //~vXXER~
}                                                                  //~vXXEI~
//***************************************************************************//~vbj2I~
//* search CHL popupmenu item                                      //~vbj2I~
//***************************************************************************//~vbj2I~
    int gxemfrm_popupmenu_getmenuitemidCHL(int Pindex)             //~vbj2R~
{                                                                  //~vbj2I~
	if (Pindex>=0 && Pindex<POPUPMENU_ITEMCTR_CHL)                 //~vbj2I~
    	return SpopupmenutblCHL[Pindex].PMTid;                     //~vbj2I~
    return 0;                                                      //~vbj2I~
}                                                                  //~vbj2I~
//***************************************************************************//~vXXEI~
//* search popupmenu item                                          //~vXXEI~
//***************************************************************************//~vXXEI~
int gxemfrm_popupmenu_getmenuitemid(int Pindex)                    //~vXXER~
{                                                                  //~vXXEI~
	if (Gxxestat & GXXES_POPUPMENU_CHL)                            //~vbj2R~
		return gxemfrm_popupmenu_getmenuitemidCHL(Pindex);         //~vbj2I~
	if (Pindex>=0 && Pindex<POPUPMENU_ITEMCTR)                     //~vXXER~
    	return Spopupmenutbl[Pindex].PMTid;                        //~vXXER~
    return 0;                                                      //~vXXER~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
//* realize *****************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_realize                    (GtkWidget       *Ppwidget)//~vXXER~
{                                                                  //~vXXEI~
	 dprintf("main frame realize\n");                               //~v669R~
//    { //@@@@test                                                 //~vbdnR~
//        int  www,hhh;                                            //~vbdnR~
//        csub_get_widget_allocation_wh(Ppwidget,&www,&hhh);       //~vbdnR~
//        dprintf("%s: w=%d,h=%d\n",UTT,www,hhh);                  //~vbdnR~
//    }                                                            //~vbdnR~
	Gpframe=Ppwidget;                                              //~vXXER~
    Gpview=lookup_widget (GTK_WIDGET (Ppwidget), "maindraw"); //   //~vXXER~
    Mtoolbar=lookup_widget (GTK_WIDGET (Ppwidget),STRTBID_TOOLBAR); ////~v66rI~
    gxemfrm_setwindowsize();                                       //~vXXEI~
    udragdestset();                                                //~vXXER~
    mainmenu_init();                                               //~vXXEI~
	toolbar_init();		//read ini data                            //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
    if (Gppopupmenu)                                               //~var8R~
    	gtk_menu_attach_to_widget(GTK_MENU(Gppopupmenu),Gpview,NULL/*detach callback*/);//~var8R~
#endif                                                             //~var8R~
//    { //@@@@test                                                 //~vbdnR~
//        int  www,hhh;                                            //~vbdnR~
//        csub_get_widget_allocation_wh(Ppwidget,&www,&hhh);       //~vbdnR~
//        dprintf("%s: w=%d,h=%d\n",UTT,www,hhh);                  //~vbdnR~
//    }                                                            //~vbdnR~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* unrealize ***************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_unrealize                  (GtkWidget       *widget)  //~vXXEI~
{                                                                  //~vXXEI~
	 dprintf("mainframe  unrealize\n");                             //~v669R~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* configure ***************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_configure            (GtkWidget       *Ppwidget,      //~vXXER~
                                        GdkEventConfigure *event)  //~vXXEI~
{                                                                  //~vXXEI~
    int ww,hh;                                                     //~vbi9R~
//*********************************                                //~vXXEI~
//    csub_get_widget_allocation_wh(Ppwidget,&ww,&hh); //@@@@test  //~vbi9R~
    UTRACEP("%s:type=%d,event w=%d,h=%d\n",UTT,event->type,event->width,event->height);//~vam0R~//~vbi9R~
    dprintf("%s:type=%d,event w=%d,h=%d\n",UTT,event->type,event->width,event->height);//~vbi9R~
                                                                   //~vbi9R~
    ww=Mwxeinidata.WXEINIframewidth;    //restore size             //~vbi9R~
    hh=Mwxeinidata.WXEINIframeheight;   //restore size             //~vbi9R~
    if (!Sadjustww)                                                //~vbi9R~
    {                                                              //~vbi9R~
    	if (event->width>=ww && event->height>=hh)                 //~vbi9R~
        {                                                          //~vbi9R~
        	Sadjustww=event->width-ww;                             //~vbi9R~
        	Sadjusthh=event->height-hh;                            //~vbi9R~
		    UTRACEP("%s:ini=%d,%d,adjust=%d,%d\n",UTT,ww,hh,Sadjustww,Sadjusthh);//~vbi9R~
//          csub_get_widget_allocation_wh(Ppwidget,&ww,&hh);//test //~vbi9R~
        }                                                          //~vbi9R~
    }                                                              //~vbi9R~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* delete    ***************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_delete               (GtkWidget       *Ppwidget,      //~vXXEI~
                                        GdkEvent        *event)    //~vXXEI~
{                                                                  //~vXXEI~
//*********************************                                //~vXXEI~
//  dprintf("mainframe delete   \n");                              //~v66DR~
	printf("Update discarded.\n");                                 //~v66DR~
    exit(12);                                                      //~v66DI~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* destroy   ***************************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_destroy              (GtkWidget       *Ppwidget,      //~vXXEI~
                                        GdkEvent        *event)    //~vXXEI~
{                                                                  //~vXXEI~
//*********************************                                //~vXXEI~
	 dprintf("mainframe destroy  \n"); //destroy unreachable?       //~v669R~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vXXEI~
//* set initial window size *************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_setwindowsize(void)                                   //~vXXEI~
{                                                                  //~vXXEM~
	int ww,hh;                                                     //~vXXEI~
//**********************************                               //~vXXEM~
	if (Mswgetinifail)                                             //~vXXEI~
    {                                                              //~vXXEI~
        ww=DEF_FRAMEWIDTH;                                         //~vXXEI~
        hh=DEF_FRAMEHEIGHT;                                        //~vXXEI~
    }                                                              //~vXXEI~
    else                                                           //~vXXEI~
    {                                                              //~vXXEI~
        ww=Mwxeinidata.WXEINIframewidth;    //restore size         //~vXXER~
        hh=Mwxeinidata.WXEINIframeheight;   //restore size         //~vXXER~
    }                                                              //~vXXEI~
//	gtk_widget_set_size_request(Gpframe,ww,hh);      //cannot shrink//~vXXER~
	dprintf("gxemfrm_setwindowsize w=%d,h=%d\n",ww,hh);            //~var8R~
//#ifdef TEST                                                        //~vbdnR~//~vbi9R~
//    gtk_window_set_default_size(GTK_WINDOW(Gpview),ww,hh);  //shrink avail//~vbdnI~//~vbi9R~
//    UTRACEP("%s:Gpview=%p gtk_window_set_default_size w=%d,h=%d,Mswgetinifail=%d\n",UTT,Gpview,ww,hh,Mswgetinifail);//~vbdnI~//~vbi9R~
//#else                                                              //~vbdnI~//~vbi9R~
  	gtk_window_set_default_size(GTK_WINDOW(Gpframe),ww,hh);  //shrink avail//~vXXER~
	UTRACEP("%s:Gpframe=%p gtk_window_set_default_size w=%d,h=%d,Mswgetinifail=%d\n",UTT,Gpframe,ww,hh,Mswgetinifail);           //~v669R~//~vam0R~//~vbdnR~
//#endif                                                             //~vbdnI~//~vbi9R~
//#ifndef TEST                                                       //~vbdnI~//~vbi9R~
//    {   //@@@@test                                                 //~vbdnR~//~vbi9R~
//        int  www,hhh;                                              //~vbdnI~//~vbi9R~
//        csub_get_widget_allocation_wh(Gpframe,&www,&hhh);          //~vbdnI~//~vbi9R~
//        UTRACEP("%s:gtk_window_get_allocation w=%d,h=%d\n",UTT,www,hhh);//~vbdnI~//~vbi9R~
//    }                                                              //~vbdnI~//~vbi9R~
//#endif                                                             //~vbdnI~//~vbi9R~
	return;                                                        //~vXXEI~
}                                                                  //~vXXEM~
//***************************************************************************//~vXXEI~
//* on close write ini      *************************************************//~vXXEI~
//***************************************************************************//~vXXEI~
void gxemfrm_onclose(void)                                         //~vXXEI~
{                                                                  //~vXXEM~
//  WINDOWPLACEMENT wp;                                            //~vXXEI~
//*******************************                                  //~vXXEM~
//  if (Mpxemain)                                                  //~vXXEI~
//  {                                                              //~vXXEI~
        xxemain_iniput(&Mwxeinidata);//write scr size              //~vXXER~
//      GetWindowPlacement(&wp);                                   //~vXXER~
#ifndef OPTGTK3                                                    //~var8R~
        Mwxeinidata.WXEINIframewidth=Gpframe->allocation.width;    //~vXXER~
        Mwxeinidata.WXEINIframeheight=Gpframe->allocation.height;  //~vXXER~
		UTRACEP("%s:GTK2:by Gframe allocation w=%d,h=%d\n",UTT,Mwxeinidata.WXEINIframewidth,Mwxeinidata.WXEINIframeheight);//~vbdnI~
#else                                                              //~var8R~
		csub_get_widget_allocation_wh(Gpframe,&Mwxeinidata.WXEINIframewidth,&Mwxeinidata.WXEINIframeheight);//~var8R~
		Mwxeinidata.WXEINIframewidth-=Sadjustww;                   //~vbi9R~
		Mwxeinidata.WXEINIframeheight-=Sadjusthh;                  //~vbi9R~
                                                                   //~vbi9R~
		UTRACEP("%s:GTK3:by csub_get_widget_allocation_wh w=%d,h=%d,adjust=%d,%d\n",UTT,Mwxeinidata.WXEINIframewidth,Mwxeinidata.WXEINIframeheight,Sadjustww,Sadjusthh);//~vbdnI~//~vbi9R~
#endif                                                             //~var8R~
//        {//@@@@test                                                //~vbdnM~//~vbi9R~
//            int www,hhh;                                           //~vbdnM~//~vbi9R~
//            csub_get_widget_allocation_wh(Gpframe,&www,&hhh);      //~vbdnI~//~vbi9R~
//            csub_get_widget_allocation_wh(Gpview,&www,&hhh);       //~vbdnI~//~vbi9R~
//        }                                                          //~vbdnM~//~vbi9R~
//      Mwxeinidata.WXEINIshowmaxsw=IsZoomed();                    //~vXXER~
UTRACEP("%s:window w=%d,h=%d\n",UTT,Mwxeinidata.WXEINIframewidth,Mwxeinidata.WXEINIframeheight);//~v669R~//~vam0R~//~vbdnR~
        uputinidata(&Mwxeinidata);                                 //~vXXEM~
        wxe_xecall(WXE_REQ_TERM,0);	//write xe.ini                 //~vXXER~
//  }                                                              //~vXXEI~
//  Mpapp->WinHelp(0,HELP_QUIT);                                   //~vXXEI~
    UTRACEP("gxemfrm onclose return\n");                              //~v669R~//~vam0R~
    utrace_term(0);  //close utrace file and stop utrace,moved from xe.c//~vbdnI~
    return;                                                        //~vXXEI~
}	                                                               //~vXXEI~
//***************************************************************************//~vXXEI~
//* release f10 for xe;and use Shift+Control+F10 as menu acceskey  //~vXXEI~
//***************************************************************************//~vXXEI~
void changemenuaccelkey(void)                                      //~vXXER~
{                                                                  //~vXXEI~
	char *orgvalue;;                                               //~vXXEI~
//*******************************                                  //~vXXEI~
	orgvalue=NULL;                                                 //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    g_object_get(G_OBJECT(gtk_settings_get_default()),             //~var8R~
                        "gtk-menu-bar-accel",                      //~var8R~
                        &orgvalue,                                 //~var8R~
                        NULL);                                     //~var8R~
#else   //OPTGTK3                                                  //~var8R~
#endif                                                             //~var8R~
#if GTK_CHECK_VERSION(3,16,0)                                      //~vb74I~
    g_object_set(G_OBJECT(gtk_settings_get_default()),             //~vb74I~
                        "gtk-menu-bar-accel",                      //~vb74I~
                        "<Shift><Control>F10",NULL);               //~vb74I~
#else                                                              //~vb74I~
    gtk_settings_set_string_property(                              //~vXXEI~
                          gtk_settings_get_default(),              //~vXXEI~
                        "gtk-menu-bar-accel",                      //~vXXEI~
                        "<Shift><Control>F10","gxe-gxe");          //~vXXEI~
#endif                                                             //~vb74I~
    g_object_get(G_OBJECT(gtk_settings_get_default()),             //~vXXEI~
                        "gtk-menu-bar-accel",                      //~vXXEI~
                        &orgvalue,                                 //~vXXEI~
                        NULL);                                     //~vXXEI~
    dprintf("get changed  menu_bar_accel=%s\n",orgvalue);          //~v669R~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
//***************************************************************************//~vbdnI~
// check SetupDialog:Museacc on but disabled menuitem by pcw type if Control+key//~vbdnI~
// rc:TRUE if diabled key                                          //~vbdnI~
//***************************************************************************//~vbdnI~
int gxemfrm_chkDiabledMenuid(int Popt,int Pshift,int Pkeyval)      //~vbdnI~
{                                                                  //~vbdnI~
	PACCMENUTBL pamt;                                              //~vbdnI~
    int ii,mod,key,rc=0,shift;                                     //~vbdnR~
//*******************************                                  //~vbdnI~
	shift=Pshift & (GDK_CONTROL_MASK|GDK_SHIFT_MASK);              //~vbdnI~
	dprintf("%s:Museact=%d,Pshift=%x,shift=%x,Pkey=%x\n",UTT,Museact,Pshift,shift,Pkeyval);//~vbdnR~
    for (ii=0,pamt=Saccmenutbl;ii<ACCMENUTBLENTNO;ii++,pamt++)     //~vbdnI~
    {                                                              //~vbdnI~
        mod=pamt->AMTmodifier;                                     //~vbdnI~
        key=pamt->AMTkey;                                          //~vbdnI~
	    dprintf("%s:key=%x,mod=%x\n",UTT,key,mod);                 //~vbdnI~
        if (toupper(key)==toupper(Pkeyval) && mod==shift)          //~vbdnR~
        {                                                          //~vbdnI~
			wxe_errmenuitemDisabled2(pamt->AMTstrid);              //~vbdnI~
            rc=1;                                                  //~vbdnI~
            break;                                                 //~vbdnI~
        }                                                          //~vbdnI~
	}                                                              //~vbdnI~
    return rc;                                                     //~vbdnI~
}//gxemfrm_chkDiabledMenuid                                        //~vbdnI~
