//*CID://+vbj0R~:                             update#=  693;       //~vbj0R~
//***********************************************************************//~v51gI~
//vbj0:180223 (GTK3)use enumprinter as alternative of cupsGetDest  //~vbj0I~
//vbi8:180221 (GTK3:bug) selected printer is not recovered(index differ by 1 by "Default" entry)//~vbi8I~
//vb7s:170128 (gxe:bug)avoid "Gtk-Message:GtkDialog mapped without a transient parent."//~vb7sI~
//vat0:140221 (gxe:gtk3:bug)gtk_enumerate_printers hungs when cups is not running//~vat0I~
//var8:140127 gtk3 suppott                                         //~var8I~
//var6:140123 (BUG)pagedialog:did not cleared pixmap at cancel button//~var6I~
//var5:140121 (BUG)chk no printer status;it cause loop at wxe_prtgetmaxpage by formsz value=0//~var5I~
//var4:140118 set transient for msgbox from dialog to protect to hide msgbox behind dialog//~var8R~
//vap1:131220 (LNX)configure supports NOPRINT for RedHat5.8        //~var8R~
//vamt:131015 (GtkPrint)accept minus value of margin to adjust origin for each printer's paper folder shift attachment.(case of that b5 origin is relativ to a4 origin)//~vamtI~
//vamp:131007 del vamk by vamm                                     //~vampI~
//vamk:131006 margin not by int but by gdouble for acuracy         //~vam7I~
//vam8:130929 (BUG)preview current page setting was ignore and always page=1//~vam8I~
//vam7:130929 add print with ligature                              //~vam7I~
//vam1:130915 sometime miss to initial screen drawing by the reason of cupsenumprinter lose control//~vam1I~
//            and signal:onsize by resizehint intercept xxemain_init process;//~vam1I~
//            so call enumprinter after xxemaini init end          //~vam1I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//vagG:121219 (Lnx)chk result of cupsGetDests(report from .at; folowing free() was crashed on RHEL5.73)//~vagGI~
//vafe:120612 BUG found by chk uninitialized variable warning by gcc 4.1.1 on FC5//~vafeI~
//vaa7:111117 (gcc4.6)Warning:unused-but-set                       //~vaa7I~
//va8c:101003 (XXE)set default button for "Print" on print dialog  //~va8cI~
//va8a:100926 (WXE)end wxp work at end print                       //~va8aI~
//va6y:000706 CUPs default printer is not same as gnome default    //~va49I~
//va49:100406 (WXE:BUG)wxe print abend when VHEX and HHEX.         //~va49I~
//v75V:070526 (XXE)cupsGetPrinters deprecated,use cupsDests        //~v75VI~
//v667:050823 (XXE)add printer selection dropdown list(effective only for CUPS)//~v667I~
//v664:050817 (XXE:BUG)pagecount unmatch between preview and print because cellh/w parm is different.//~v664I~
//vX02:050729 set defaut printer font same as screen               //~vXXEI~
//vXXE:050611 new for XXE                                          //~vXXEI~
//v62W:050422 (WXE)maximum cell height definition for small doc    //~v62WI~
//v627:050309 (WXE)vhex print support                              //~v627I~
//v56v:040411 (WXE)shorten page/line msg                           //~v56vI~
//v55F:040314 (WXE)english help                                    //~v55FI~
//v55D:040309 (WXE)popup help for dialog control                   //~v55DI~
//v51h:030525 (WXE)col/row by font size specification              //~v51hI~
//v51g:030525 (WXE)allow wrap around by NextPage/PrevPage button   //~v51gI~
//***********************************************************************//~v51gI~
//

#ifdef HAVE_CONFIG_H                                               //~v62WI~
#  include <config.h>                                              //~v62WI~
#endif                                                             //~v62WI~
                                                                   //~v62WI~
#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>                                                 //~v62WI~
#else                                                              //~var8R~
//#include <libgnomecanvas/libgnomecanvas.h>                       //~var8R~
#include <gtk/gtk.h>                                               //~var8R~
#include <gdk/gdkx.h>                                              //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0I~
	  #ifndef OPTGTK3                                              //~var8R~
		#include <gtk/gtkprinter.h>                                //~vam0I~
      #else                                                        //~var8R~
		#include <gtk/gtkunixprint.h>                              //~var8R~
      #endif                                                       //~var8R~
	#else    //!GTKPRINT                                           //~vam0I~
#include <libgnomeprint/gnome-print-paper.h>                       //~vXXER~
#include <libgnomeprint/gnome-print-unit.h>                        //~vXXER~
#include <libgnomeprint/gnome-print.h>                             //~vXXEI~
#include <libgnomeprint/gnome-print-job.h>                         //~vXXEI~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif                                                             //~vam0I~
#include <cups/cups.h>                                             //~v667I~
                                                                   //~v62WI~
#include "gxe.h"                                                   //~var8R~
#include "callbacks.h"                                             //~v62WI~
#include "interface.h"                                             //~v62WI~
#include "support.h"                                               //~v62WI~
                                                                   //~v62WI~
#include "ulib.h"                                                  //~v62WI~
#include "uedit.h"                                                 //~vXXEI~
#include "ualloc.h"                                                //~va6yI~
#include "utrace.h"                                                //~vam0I~
//#include "gxe.h"                                                 //~var8R~
#include "xxedef.h"                                                //~v62WI~
#include "xxemain.h"                                               //~v62WI~
#include "xxeres.h"                                                //~v62WI~
#include "gxedlg.h"                                                //~v62WI~
#include "gxeview.h"                                               //~vXXER~
#include "gxepage.h"                                               //~vXXEI~
#include "xxexei.h"                                                //~vXXEI~
#include "xxecsub.h"                                               //~vXXEI~
                                                                   //~v62WI~

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//************************************************************     //~v62WI~
#ifndef NOPRINT                                                    //~vam0I~
static int Sinitdlg=0;                                             //~va6yI~
#endif                                                             //~vam0I~
static    GtkWidget *Sprintdlg;                                    //~v62WI~
static    GtkWidget *Spwdpreview;                                  //~vXXER~
static 	  FONTDATA  Ssvfontdata1;   //save for canceled case       //~vXXEI~
#ifndef NOPRINT                                                    //~vam0I~
	#ifdef GTKPRINT                                                //~vam0I~
	#else    //!GTKPRINT                                           //~vam0I~
static    GList  *Spaperlist=NULL;                                 //~vXXEI~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif                                                             //~vam0I~
static    char   *Scupspaperlist=NULL;                             //~va6yI~
#ifndef NOPRINT                                                    //~vam0I~
static    RECT  Mpreview_rect;                                     //~vXXER~
#endif                                                             //~vam0I~
    int Mprttype,Mtotlineno,Mcmaxcol,Mcmaxrow,Mlinenodigit,Mmaxpage;
	int Mprtdatamaxcol,Mprtdatamaxrow;                             //~vXXEM~
	int Morgprttype;                                               //~vXXEM~
    int Mmaxlrecl,Mlinenosz,Mtotrow,Mcmaxlrecl;                    //~vXXEM~
    char Mprtfnm[_MAX_PATH];                                       //~vXXEM~
//  char Msvformtype[32];                                          //~vam0R~
    char Msvformtype[PPDMAXNAME];                                  //~vam0R~
//  char Msvprinter[32];                                           //~vam0R~
    char Msvprinter[PPDMAXNAME];                                   //~vam0R~
    char Msvprtfontstyle[128];                                     //~vXXEM~
	BOOL	Msv2p;                                                 //~vXXEM~
	BOOL	Msvfiletime;                                           //~vXXEM~
	BOOL	Msvheader;                                             //~vXXEM~
	BOOL	Msvfooter;                                             //~vXXEM~
	BOOL	Msvlinenumber;                                         //~vXXEM~
	BOOL	Msvsystime;                                            //~vXXEM~
	BOOL	Msvwwscrprt;                                           //~vXXEM~
	BOOL	Msvchkpfontsz;                                         //~vXXEM~
	int		Msvprtcol;                                             //~vXXEM~
	int		Msvprtrow;                                             //~vXXEM~
	int		Msvpcellszh;                                           //~vXXEM~
	int		Msvpcellszhmax;                                        //~vXXEM~
	int		Msvpcellszw;                                           //~vXXEM~
	int		Msvprt2pcol;                                           //~vXXER~
	int		Msvmarginl;                                            //~vXXEM~
	int		Msvmarginr;                                            //~vXXEM~
	int		Msvmargint;                                            //~vXXEM~
	int		Msvmarginb;                                            //~vXXEM~
	BOOL	Msvlandscape;                                          //~vXXEM~
	BOOL	Msvfullpage;                                           //~vXXEM~
	BOOL	MsvprintLigature;                                      //~vam7R~
#ifdef GTKPRINT                                                    //~vamtI~
	int		MsvmarginshiftT,MsvmarginshiftB,MsvmarginshiftL,MsvmarginshiftR;//~vamtI~
    #define MARGIN_SHIFT_UNIT   100       //xxyy:xx=shift,yy=margin//~vamtI~
    #define MARGIN_SHIFT_SET(margin,shift) ((shift)*MARGIN_SHIFT_UNIT+(margin))//~vamtR~
    #define MARGIN_SHIFT_PARSE(value,margin,shift) shift=(value)/MARGIN_SHIFT_UNIT,margin=(value)%MARGIN_SHIFT_UNIT,shift!=0//~vamtI~
#endif                                                             //~vamtI~
    int Snoprinter;                                                //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
	static GList *Sglcomboprinter;                                 //~vbj0I~
#else   //OPTGTK3                                                  //~var8R~
	static GList *Sglcombopaper;                                   //~var8R~
	static GList *Sglcomboprinter;                                 //~var8R~
//  double Sscalex,Sscaley;                                        //~var8R~
    GdkGC *SpgcpreviewWidget;  //drawingarea widget                //~var8R~
    GdkPixmap *SppixmappreviewWidget;  //pixmap for drawingarea widget//~var8R~
#endif                                                             //~var8R~
	static char *Senmuprinterlist;                                 //~vbj0M~
//************************************************************     //~vXXEI~
void saverestparm(int Psavesw);                                    //~vXXER~
BOOL OnInitDialog(void);                                           //~vXXEI~
int  getparm(void);                                                //~vXXEI~
void putparm(void);                                                //~vXXEI~
//BOOL Initcombo(void);                                            //~va6yR~
BOOL Initcombo(char *Pform);                                       //~va6yI~
BOOL Initcomboprinter(void);                                       //~v667I~
void displayform(int Phcopysw);                                    //~vXXEI~
void displaypageno(void);                                          //~vXXEI~
int chkpagerange(char *Pptext);                                    //~vXXEI~
void previewrectdraw(GdkColor *Ppcolor,RECT *Pprect);              //~vXXEI~
void gxepage_destroy(void);                                        //~vXXEI~
void drawpreviewcanvas(GdkPixmap *Pppixmap,gdouble Pscalex,gdouble Pscaley,RECT *Pprect);//~vXXER~
void  previewforminit(int Phcopysw,int Pformw,int Pformh);         //~vXXER~
void  previewformunref(void);                                      //~vXXEI~
void displayHWMargin(char *Pform);                                 //~vam8I~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
	int gxepage_combo_get_active(GtkWidget *Spdlg,GList *Ppglist,char *Pplokupid,char *Ppactivetext);//~var8R~
#endif                                                             //~var8R~
void freemems(void);                                               //~vbj0I~
//************************************************************     //~v62WI~
                                                                   //~vXXEI~
//***************************************************************************//~vXXEI~
// static init<--xxemain_init<--gxeview_init<--gxeview_realize     //~vXXEI~
//***************************************************************************//~vXXEI~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0I~
//=========================================================================//~vam0I~
void gxepage_init(void)                                            //~vam0I~
{                                                                  //~vam0I~
	gchar *gstr;                                                   //~vam0I~
//*****************                                                //~vam0I~
	if (!*Mprtfontstyle)                 //after delete ini file   //~vam0I~
    	strcpy(Mprtfontstyle,Mfontstyle);                          //~vam0I~
    gstr=g_new(gchar,strlen(Mprtfontstyle)+1);                     //~vam0I~
	strcpy(gstr,Mprtfontstyle);                                    //~vam0I~
	Gfontdata[1].FDfontname=gstr;	//scr fontname from default or ini file//~vam0I~
	Gfontdata[1].FDfontdesc=pango_font_description_from_string(gstr);//~vam0I~
//  Spaperlist=gnome_print_paper_get_list();                       //~vam0I~
//  Spaperlist=csubgetpaperlistGtk();   //using gtk                //~vam0I~//~vam1R~
	return;                                                        //~vam0I~
}//gxepage_init                                                    //~vam0I~
//=========================================================================//~vam1I~
//= from xxemain_init after Mxxemaininitend is set                 //~vam1I~
//=========================================================================//~vam1I~
void gxepage_init2(void)                                           //~vam1I~
{                                                                  //~vam1I~
//	gchar *gstr;                                                   //~vam1I~//~vam0R~
	GtkPrinter *pprinter;                                          //~vam0I~
//*****************                                                //~vam1I~
    UTRACEP("gxepage_init2 before getpaperlistGtk\n");                   //~vam1I~//~vam0R~
//  Spaperlist=csubgetpaperlistGtk();   //using gtk;create cups paperlist at                //~vam1I~//~vam0R~
	pprinter=csubgetdefaultprinterGtk();         //set SdefaultprinterGtk by enum printer//~vam0R~
    if (!pprinter)                             //no default printerdefined//~vam0I~
    {                                                              //~vat0I~
    	csubsrchprinterGtk(Mprinter,Mprinter_cupsdefault);	//set top printer//~vam0I~
        if (!*Mprinter_cupsdefault)                                //~vat0I~
    	    printf("\nWarning(gxe):No default printer, is cupsd runnung?\n");//~vat0R~
    }                                                              //~vat0I~
    UTRACEP("gxepage_init2 exit\n");                               //~vam0I~
	return;                                                        //~vam1I~
}//gxepage_init2                                                   //~vam1I~
	#else    //!GTKPRINT                                           //~vam0I~
//=========================================================================//~vam0I~
void gxepage_init(void)                                            //~vXXEI~
{                                                                  //~vXXEI~
	gchar *gstr;                                                   //~vXXEI~
//*****************                                                //~vXXEI~
	if (!*Mprtfontstyle)                 //after delete ini file   //~vXXEI~
    	strcpy(Mprtfontstyle,Mfontstyle);                          //~vXXEI~
    gstr=g_new(gchar,strlen(Mprtfontstyle)+1);                     //~vXXEI~
	strcpy(gstr,Mprtfontstyle);                                    //~vXXEI~
	Gfontdata[1].FDfontname=gstr;	//scr fontname from default or ini file//~vXXEI~
	Gfontdata[1].FDfontdesc=pango_font_description_from_string(gstr);//~vXXEI~
	Spaperlist=gnome_print_paper_get_list();                       //~vXXEI~
	return;                                                        //~vXXEI~
}//gxepage_init                                                     //~vXXEI~//~vam0R~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//************************************************************     //~vXXEI~
//*save value before dialog init *****************************     //~vXXEI~
//************************************************************     //~vXXEI~
void construct(void)                                               //~vXXER~
{                                                                  //~2B09M~
	void *pfh;                                                     //~2B10I~
    int lnotype;                                                   //~2C07I~
//********************************                                 //~2B09I~
	saverestparm(1);	//save value for the case canceled         //~vXXEI~
//  Mpwxemain=Ppwxemain;                                           //~vXXER~
	//{{AFX_DATA_INIT(CWxepage)                                    //~2B09M~
	Mcurpage = 0;                                                  //~3104R~
	//}}AFX_DATA_INIT
                                                                   //~vXXEI~
//save for cancel                                                  //~vXXEI~
//  Mformsize  =Mformtype;                                         //~v51hR~
//  Mpfontszh  =Mpwxemain->Mpfontszh;                              //~vXXER~
//  Mpfontszw  =Mpwxemain->Mpfontszw;                              //~vXXER~
                                                                   //~vXXEI~
    Mmaxlrecl=0;                                                   //~2B09I~
    Mtotlineno=0;                                                  //~2B09I~
    Mmaxpage=0;                                                    //~2B09I~
    Mcmaxcol=0;                                                    //~2B09I~
    Mcmaxrow=0;                                                    //~2B09I~
    Mprttype=0;                                                    //~2B30R~
    Mtotrow=0;                                                     //~2B09I~
                                                                   //~vXXEI~
	*Mprtfnm=0;                                                    //~2B10I~
	MlandscapeR=-1;	//ink clockwise rotate Land-top=Port-left,Land-right:Port-top//~vam7M~
//  Morgprttype=wxe_prtgetfnm(Mprtfnm,&pfh,&lnotype);	//file/dir/screen//~v627R~
    Morgprttype=wxe_prtgetfnm(Mprtfnm,0,&pfh,&lnotype);	//file/dir/screen//~v627I~
    if (Morgprttype==PRTTYPE_HCOPY)                                //~2C14R~
    	strcpy(Mprtfnm,PRTSCRID);                                  //~2C14I~
}                                                                  //~2B09M~
//************************************************************     //~vam0I~
void gxepage_destroy(void)                                         //~vXXER~
{                                                                  //~2B09R~
    if (Gpgcpreview)                                               //~vXXER~
    {                                                              //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
   		gdk_gc_unref(Gpgcpreview);                                 //~vXXER~
#else   //OPTGTK3                                                  //~var8R~
    	csub_gc_destroy_pixmap(SpgcpreviewWidget,SppixmappreviewWidget);  //destroy gc and pixmap//~var8R~
    	SppixmappreviewWidget=0;                                   //~var8R~
    	csub_gc_destroy_pixmap(Gpgcpreview,Gppixmappreview);  //destroy gc and pixmap//~var8R~
    	Gppixmappreview=0;                                         //~var8R~
#endif                                                             //~var8R~
    	Gpgcpreview=0;                                             //~vXXER~
    }                                                              //~vXXEI~
    gtk_widget_destroy(Sprintdlg);                                 //~vXXEM~
    freemems();                                                    //~vbj0I~
}                                                                  //~vbj0I~
//***************************************************************************//~vbj0I~
void freemems(void)                                                //~vbj0I~
{                                                                  //~vbj0I~
    if (Scupspaperlist)                                            //~va6yI~
    	ufree(Scupspaperlist);                                     //~va6yI~
    Scupspaperlist=0;                                              //~va6yI~
    if (Senmuprinterlist)                                          //~vbj0I~
    	free(Senmuprinterlist);                                    //~vbj0R~
    Senmuprinterlist=0;                                            //~vbj0I~
	return;                                                        //~vXXER~
}//gxepage_destroy                                                 //~vam0R~
//***************************************************************************//~vbj0I~
gboolean on_page_delete_event(GtkWidget *Ppwidget,GdkEvent *Ppevent,gpointer  user_data)//~vbj0I~
{                                                                  //~vbj0I~
	UTRACEP("%s:entry\n",UTT);                                     //~vbj0I~
    freemems();                                                    //~vbj0I~
    return FALSE;	//emit destroy signal,if true means you do not want destroy//~vbj0R~
}//on_page_delete_event                                            //~vbj0I~
//***************************************************************************//~v62WM~
// create dlg                                                      //~v62WI~
//***************************************************************************//~v62WM~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_create 				(GtkMenuItem     *Pmenuitem,   //~vXXER~
                                        gpointer         Puser_data)//~v62WM~
{                                                                  //~v62WM~
//****************************                                     //~v62WM~
	 dprintf("on_preview_activate  \n");                            //~v667R~
    Sprintdlg= create_printdlg();                                  //~v62WM~
    /* Make sure the dialog doesn't disappear behind the main window. *///~v62WM~
//#ifndef OPTGTK3                                                  //~vb7sR~
    gtk_window_set_transient_for (GTK_WINDOW (Sprintdlg),          //~v62WM~
				    GTK_WINDOW (Gpframe));                         //~v62WM~
//#else   //OPTGTK3                                                //~vb7sR~
//#endif                                                           //~vb7sR~
  	gtk_widget_show (Sprintdlg);                                   //~v62WM~
                                                                   //~v62WM~
  	/* We make sure the dialog is visible. */                      //~v62WM~
  	gtk_window_present (GTK_WINDOW (Sprintdlg));                   //~v62WM~
    construct();                                                   //~vXXEI~
    OnInitDialog();                                                //~vXXEI~
    g_signal_connect(GTK_WINDOW(Sprintdlg),"delete_event",G_CALLBACK (on_page_delete_event),NULL);//~vbj0I~
    return;                                                        //~v62WM~
}                                                                  //~v62WM~
#endif                                                             //~vam0I~
//***************************************************************************//~vXXEI~
// setup dialog data to display                                    //~vXXEI~
//***************************************************************************//~vXXEI~
#ifndef NOPRINT                                                    //~vam0I~
BOOL OnInitDialog(void)                                            //~vXXER~
{                                                                  //~2B09M~
	GtkWidget *pwidget;                                            //~vXXEI~
    RECT  rect;                                                    //~vXXEI~
    char defmarginwk[64];                                          //~vXXEI~
//************************                                         //~2B09M~
	UTRACEP("gxepage OnInitDialog\n");                             //~vam7I~
    Sinitdlg=0;                                                    //~va6yI~
//  CDialog::OnInitDialog();                                       //~vXXER~
//  Mspinpfontszw.SetRange(PRINTFONTSZW_MIN,PRINTFONTSZW_MAX);     //~vXXER~
//  Mspinpfontszh.SetRange(PRINTFONTSZH_MIN,PRINTFONTSZH_MAX);     //~vXXER~
	gxedlg_settext_fontname(1,Sprintdlg);                          //~vXXER~
//	SET_SENSITIVE(Sprintdlg,STRIDC_ENTRY_PFONTNAME,FALSE);         //~vXXER~
    SET_SENSITIVE(Sprintdlg,STRIDC_EDIT_PFONTSZH,FALSE);           //~vXXER~
    SET_SENSITIVE(Sprintdlg,STRIDC_EDIT_PFONTSZW,FALSE);           //~vXXER~
//  Mspinpcellszw.SetRange(PRINTCELLSZW_MIN,PRINTCELLSZW_MAX);     //~vXXER~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_PCOLW,Mpcellszw);         //~vXXER~
//  Mspinpcellszh.SetRange(PRINTCELLSZH_MIN,PRINTCELLSZH_MAX);     //~vXXER~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_PROWH,Mpcellszh);         //~vXXER~
//  Mspinpcellszhmax.SetRange(PRINTCELLSZHMAX_MIN,PRINTCELLSZHMAX_MAX);//~vXXER~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_MAXCOLROW,Mpcellszhmax);  //~vXXER~
//  Mspincol.SetRange(PRINTCOL_MIN,PRINTCOL_MAX);                  //~vXXER~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_COL,Mprtcol);             //~vXXER~
//  Mspinrow.SetRange(PRINTROW_MIN,PRINTROW_MAX);                  //~vXXER~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_ROW,Mprtrow);             //~vXXER~
                                                                   //~2B09I~
//  Mstaticpreview.GetClientRect(&Mpreview_rect);                  //~vXXER~
#ifdef XXX                                                         //~vXXEI~
    pwidget=lookup_widget(GTK_WIDGET(Sprintdlg),"scrolledwindow1");  \
    Mpreview_rect.top=0;                                           //~vXXEI~
    Mpreview_rect.left=0;                                          //~vXXEI~
    Mpreview_rect.right=pwidget->allocation.width;                 //~vXXEI~
    Mpreview_rect.bottom=pwidget->allocation.height;               //~vXXEI~
    dprintf("scroll window rect ww=%d,hh=%d\n",Mpreview_rect.right,Mpreview_rect.bottom);//~v667R~
#endif                                                             //~vXXEI~
    pwidget=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_PREVIEW_AREA);  \
    Spwdpreview=pwidget;	//preview area widget                  //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
    Gpgcpreview=gdk_gc_new(pwidget->window);	//preview area widget//~vXXER~
#else                                                              //~var8R~
//  Gpgcpreview=csub_gc_new(pwidget);	//preview area widget      //~var8R~
#endif                                                             //~var8R~
    Mpreview_rect.top=0;                                           //~vXXEI~
    Mpreview_rect.left=0;                                          //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
    Mpreview_rect.right=pwidget->allocation.width;                 //~vXXER~
    Mpreview_rect.bottom=pwidget->allocation.height;               //~vXXER~
#else                                                              //~var8R~
    csub_get_widget_allocation_wh(pwidget,&Mpreview_rect.right,&Mpreview_rect.bottom);//~var8R~
#endif                                                             //~var8R~
    dprintf("preview window rect ww=%d,hh=%d\n",Mpreview_rect.right,Mpreview_rect.bottom);//~v667R~
	                                                               //~2B09M~
//  Mchecklandscape.SetCheck(Mlandscape);                          //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_LANDSCAPE,Mlandscape);       //~vXXEI~
//  Mcheckfullpage.SetCheck(Mfullpage);                            //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_FULLPAGE,Mfullpage);         //~vXXEI~
//  Mcheckheader.SetCheck(Mheader);                                //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_HEADER,Mheader);             //~vXXEI~
//  Mcheckfooter.SetCheck(Mfooter);                                //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_FOOTER,Mfooter);             //~vXXEI~
//  Mchecklinenumber.SetCheck(Mlinenumber);                        //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_LINENUMBER,Mlinenumber);     //~vXXEI~
//  Mcheckfiletime.SetCheck(Mfiletime);                            //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_FILETIME,Mfiletime);         //~vXXEI~
//  Mchecksystime.SetCheck(Msystime);                              //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_SYSTIME,Msystime);           //~vXXEI~
//  Mcheckwwscrprt.SetCheck(Mwwscrprt);                            //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_WWSCRPRT,Mwwscrprt);         //~vXXEI~
//  Mcheck2p.SetCheck(M2p);                                        //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_2P,M2p);                     //~vXXEI~
//  Mcheckpfontsz.SetCheck(Mchkpfontsz);                           //~vXXER~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_PFONTSZ,Mchkpfontsz);        //~vXXEI~
                                                                   //~vam7I~
	SET_CHKBOX(Sprintdlg,STRIDC_CHECK_PRINTLIGATURE,MprintLigature);//~vam7R~
                                                                   //~vXXEI~
#ifdef GTKPRINT                                                    //~vamtI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_BOTTOM,MARGIN_SHIFT_SET(Mmarginb,MmarginshiftB));//~vamtR~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_LEFT,MARGIN_SHIFT_SET(Mmarginl,MmarginshiftL));//~vamtR~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_RIGHT,MARGIN_SHIFT_SET(Mmarginr,MmarginshiftR));//~vamtR~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_TOP,MARGIN_SHIFT_SET(Mmargint,MmarginshiftT));//~vamtR~
#else                                                              //~vamtI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_BOTTOM,Mmarginb);         //~vXXEI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_LEFT,Mmarginl);           //~vXXEI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_RIGHT,Mmarginr);          //~vXXEI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_TOP,Mmargint);            //~vXXEI~
#endif                                                             //~vamtI~
	SET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_2P,Mprt2pcol);            //~vXXER~
	SET_ENTRYINT(Sprintdlg,STRIDC_SPIN_CURPAGE,Mcurpage);          //~vXXER~
                                                                   //~vXXEI~
	gxepage_OnCheckpfontsz();		//enable/disable pfontsz,col,row//~vXXER~
    if (!M2p)                                                      //~2B09M~
//	    Medit2p.EnableWindow(FALSE);                               //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_2P,FALSE);             //~vXXEI~
    if (!Mheader)                                                  //~2B09I~
//	    Mcheckfiletime.EnableWindow(FALSE);                        //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_CHECK_FILETIME,FALSE);      //~vXXEI~
    if (!Mfooter)                                                  //~2B09I~
//	    Mchecksystime.EnableWindow(FALSE);                         //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_CHECK_SYSTIME,FALSE);       //~vXXEI~
    if (Morgprttype<0)	//current is not file scr                  //~2B30R~
    {                                                              //~2B10I~
//	    Mbuttonprint.EnableWindow(FALSE);                          //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_PRINT,FALSE);               //~vXXEI~
		SET_SENSITIVE(Sprintdlg,STRIDC_PRINTRANGE,FALSE);          //~vXXER~
//	    Mbuttonpreview.EnableWindow(FALSE);                        //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW,FALSE); //print in preview frame//~vXXEI~
//	    Mbuttonpreviewnextpage.EnableWindow(FALSE);                //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW_NEXTPAGE,FALSE);    //~vXXEI~
//	    Mbuttonpreviewprevpage.EnableWindow(FALSE);                //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW_PREVPAGE,FALSE);    //~vXXEI~
    }                                                              //~2B10I~
//  Meditfilename.SetWindowText(Mprtfnm);	//filename             //~vXXER~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_FILENAME,Mprtfnm);        //~vXXER~
//  Meditmaxlrecl.SetWindowText("page");       //max lrecl         //~vXXER~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_MAXPAGE,"page");          //~vXXER~
//	xxemain_prtdefaultmarginrect(&rect);                           //~vam7R~
// 	xxemain_prtdefaultmarginrect(&rect,NULL);                      //~vam7I~//~vampR~
	xxemain_prtdefaultmarginrect(&rect);                           //~vampI~
//  sprintf(defmarginwk,"default:L=%d,R=%d,T=%d,B=%d",rect.left,rect.right,rect.top,rect.bottom);//~va6yR~
    sprintf(defmarginwk,"HWMargins:L=%d,R=%d,T=%d,B=%d",rect.left,rect.right,rect.top,rect.bottom);//~va6yI~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_DEFMARGIN,defmarginwk);   //~vXXEI~
//  Initcombo();                                                   //~va6yR~
    Initcombo(0);                                                  //~va6yI~
    Initcomboprinter();                                            //~v667I~
    if (Snoprinter)                                                //~var5I~
    {                                                              //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PRINT,FALSE);               //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PRINTRANGE,FALSE);          //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW,FALSE); //print in preview frame//~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW_NEXTPAGE,FALSE);    //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEW_PREVPAGE,FALSE);    //~var5I~
                                                                   //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PREVIEWPRTSCR,FALSE);       //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_PRTSCR,FALSE);              //~var5I~
        SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_CURPAGE,FALSE);        //~var5R~
    }                                                              //~var5I~
    gtk_widget_grab_focus(lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_PRINT));//~va8cR~
    Sinitdlg=1;                                                    //~va6yI~
//  Invalidate(FALSE);                                             //~vXXER~
	return TRUE;                                                   //~va6yR~
}//OnInitDialog                                                    //~2B09M~
#endif   //!NOPRINT                                                //~vam0R~
void gxepage_OnCancel(void)                                        //~vXXEI~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg page cancel\n");                               //~v667R~
	afterprint(2);	//cancel print work                            //~va8aI~
	saverestparm(0);	//restore save at entery                   //~vXXEI~
//  gtk_widget_destroy(Sprintdlg);                                 //~var6R~
	gxepage_destroy();                                             //~var6I~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
void gxepage_OnOk(void)                                            //~vXXEI~
{
//**********************                                           //~2B03I~
	 dprintf("page onok,Snoprinter=%d\n",Snoprinter);              //~vat0R~
  if (!Snoprinter) //ignore rc of gxepage_combo_get_active         //~vat0I~
  {                                                                //~vat0I~
	if (getparm())                                                 //~v51hR~
    	return;                                                    //~v51hI~
	putparm();                                                     //~2B07I~
  }                                                                //~vat0I~
//  CDialog::OnOK();                                               //~vXXER~
	gxepage_destroy();                                             //~vXXEI~
	return;                                                        //~vXXEI~
}

void gxepage_OnPrint(void)                                         //~vXXER~
{
	if (getparm())                                                 //~v51hR~
    	return;                                                    //~v51hI~
	putparm();                                                     //~2B07I~
//	((CMainFrame*)(Mpwxemain->Mpmainframe))->PostMessage(WM_COMMAND,ID_FILE_PRINT,0);//~vXXER~
	gxeview_OnFilePrint();                                         //~vXXEI~
//	CDialog::OnOK();                                               //~vXXER~
	gxepage_destroy();                                             //~vXXEI~
	return;                                                        //~vXXEI~
}
//******************************************************************//~vam0I~
void gxepage_OnPrtscr(void)                                        //~vXXER~
{                                                                  //~2B10M~
	if (getparm())                                                 //~v51hR~
    	return;                                                    //~v51hI~
	putparm();                                                     //~2B10I~
//  ((CMainFrame*)(Mpwxemain->Mpmainframe))->PostMessage(WM_COMMAND,ID_FILE_SCRPRT,0);//~vXXER~
	gxeview_OnFileScrprt();                                        //~vXXER~
//  CDialog::OnOK();                                               //~vXXER~
	gxepage_destroy();                                             //~vXXEI~
	return;                                                        //~vXXEI~
}                                                                  //~2B10M~
//******************************************************************//~vam0I~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_OnPreview(void)                                       //~vXXER~
{                                                                  //~2B04M~
	if (getparm())                                                 //~v51hR~
    	return;                                                    //~v51hI~
//  Mcurpage=1;     if 0 set 1                                   //~3104R~//~vam8R~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_CURPAGE,Mcurpage);        //~vam8I~
    UTRACEP("gxepage_OnPreview Mcurpage=%d\n",Mcurpage);           //~vam8I~
	displayform(0);     //prtfile                                  //~2B10R~
	return;                                                        //~vXXEI~
}                                                                  //~2B04M~
#else                                                              //~vam0I~
void gxepage_OnPreview(void)                                       //~vam0I~
{                                                                  //~vam0I~
//from callback,signal never occurs                                //~vam0I~
}                                                                  //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//******************************************************************//~vam0I~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_OnPreviewprevpage(void)                               //~vXXER~
{                                                                  //~2C14I~
	if (getparm())                                                 //~v51hI~
    	return;                                                    //~v51hI~
    Mcurpage--;                                                    //~3104M~
    if (Mcurpage<=0)                                               //~v51gR~
        Mcurpage=-1;    //around to max req                        //~v51gR~
	displayform(0);     //prtfile                                  //~2C14I~
	return;                                                        //~vXXEI~
}                                                                  //~2C14I~
#else                                                              //~vam0I~
void gxepage_OnPreviewprevpage(void)                               //~vam0I~
{                                                                  //~vam0I~
//from callback,signal never occurs                                //~vam0I~
}                                                                  //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//******************************************************************//~vam0I~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_OnPreviewNextpage(void)                               //~vXXER~
{                                                                  //~3104M~
	if (getparm())                                                 //~v51hI~
    	return;                                                    //~v51hI~
    Mcurpage++;                                                    //~3104M~
	displayform(0);     //prtfile                                  //~3104I~
	return;                                                        //~vXXEI~
}                                                                  //~3104M~
#else                                                              //~vam0I~
void gxepage_OnPreviewNextpage(void)                               //~vam0I~
{                                                                  //~vam0I~
//from callback,signal never occurs                                //~vam0I~
}                                                                  //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//******************************************************************//~vam0I~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_OnPreviewprtscr(void)                                 //~vXXER~
{                                                                  //~2B10M~
	if (getparm())                                                 //~v51hI~
    	return;                                                    //~v51hI~
    Mcurpage=1;                                                    //~2C14R~
	displayform(1);   	//prtscr                                   //~2B10I~
	return;                                                        //~vXXEI~
}                                                                  //~2B10M~
#else                                                              //~vam0I~
void gxepage_OnPreviewprtscr(void)                                 //~vam0I~
{                                                                  //~vam0I~
}                                                                  //~vam0I~
//from callback,signal never occurs                                //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//******************************************************************//~vam0I~
void gxepage_OnCheckHeader(void)                                   //~vXXER~
{                                                                  //~2B10M~
    dprintf("OncheckHeader\n");                                    //~v667R~
//  Mheader=Mcheckheader.GetCheck();                               //~vXXER~
    GET_CHKBOX(Sprintdlg,STRIDC_CHECK_HEADER,Mheader);             //~vXXEI~
//  Mcheckfiletime.EnableWindow(Mheader);                          //~vXXER~
	SET_SENSITIVE(Sprintdlg,STRIDC_CHECK_FILETIME,Mheader);        //~vXXER~
	return;	                                                       //~vXXER~
}                                                                  //~2B10M~
                                                                   //~2B10M~
void gxepage_OnCheckFooter(void)                                   //~vXXER~
{                                                                  //~2B10M~
    dprintf("OncheckFooter\n");                                    //~v667R~
//  Mfooter=Mcheckfooter.GetCheck();                               //~vXXER~
    GET_CHKBOX(Sprintdlg,STRIDC_CHECK_FOOTER,Mfooter);             //~vXXER~
//	Mchecksystime.EnableWindow(Mfooter);                           //~vXXER~
	SET_SENSITIVE(Sprintdlg,STRIDC_CHECK_SYSTIME,Mfooter);         //~vXXER~
	return;                                                        //~vXXEI~
}                                                                  //~2B10M~
#ifdef GTKPRINT                                                    //~2B10M~//~vamtR~
//**************************************************************** //~vamtI~
//*margin shift for,ex, B5 paper on A4 printer folder              //~vamtI~
//**************************************************************** //~vamtI~
void                                                               //~vamtR~
chkmarginshift()                                                   //~vamtI~
{                                                                  //~vamtI~
	Mmarginshift=0;                                                //~vamtI~
    if (MARGIN_SHIFT_PARSE(Mmargint/*in*/,Mmargint/*out*/,MmarginshiftT/*out*/))//~vamtR~
		Mmarginshift=1;                                            //~vamtI~
    if (MARGIN_SHIFT_PARSE(Mmarginb,Mmarginb,MmarginshiftB))       //~vamtR~
		Mmarginshift=1;                                            //~vamtI~
    if (MARGIN_SHIFT_PARSE(Mmarginl,Mmarginl,MmarginshiftL))       //~vamtR~
		Mmarginshift=1;                                            //~vamtI~
    if (MARGIN_SHIFT_PARSE(Mmarginr,Mmarginr,MmarginshiftR))       //~vamtR~
		Mmarginshift=1;                                            //~vamtI~
    UTRACEP("gxepage chkmarginshift Mmarginshift=%d\n",Mmarginshift);//~vamtI~
    UTRACEP("gxepage chkmarginshift Mmargin t=%d,b=%d,l=%d,r=%d\n",Mmargint,Mmarginb,Mmarginl,Mmarginr);//~vamtI~
    UTRACEP("gxepage chkmarginshift Mmarginshift t=%d,b=%d,l=%d,r=%d\n",MmarginshiftT,MmarginshiftB,MmarginshiftL,MmarginshiftR);//~vamtI~
}//chkmarginshift                                                  //~vamtI~
//**************************************************************** //~vamtI~
//*put marigin to ini                                              //~vamtI~
//**************************************************************** //~vamtI~
void                                                               //~vamtI~
gxepage_savemarginshift(WXEINIDATA *Pwxei)                         //~vamtI~
{                                                                  //~vamtI~
    Pwxei->WXEINIleft     =MARGIN_SHIFT_SET(Mmarginl,MmarginshiftL);//~vamtR~
    Pwxei->WXEINIright    =MARGIN_SHIFT_SET(Mmarginr,MmarginshiftR);//~vamtR~
    Pwxei->WXEINItop      =MARGIN_SHIFT_SET(Mmargint,MmarginshiftT);//~vamtR~
    Pwxei->WXEINIbottom   =MARGIN_SHIFT_SET(Mmarginb,MmarginshiftB);//~vamtR~
}//gxepage_savemarginshift                                         //~vamtI~
//**************************************************************** //~vamtI~
//*margin shift for,ex, B5 paper on A4 printer folder              //~vamtI~
//**************************************************************** //~vamtI~
void                                                               //~vamtR~
gxepage_papershift(int *Pporgx,int *Pporgy)                        //~vamtI~
{                                                                  //~vamtI~
	int xx,yy;                                                     //~vamtR~
//****************************                                     //~vamtI~
	UTRACEP("gaxepage_papaerhift input(point) orgx=%d,orgy=%d,shft T=%d,B=%d,L=%d,R=%d\n",*Pporgx,*Pporgy,MmarginshiftT,MmarginshiftB,MmarginshiftL,MmarginshiftR);//~vamtR~
    xx=*Pporgx;                                                    //~vamtR~
    yy=*Pporgy;                                                    //~vamtR~
    if (Mlandscape)                                                //~vamtI~
    {                                                              //~vamtI~
    	xx+=MM2POINT(MmarginshiftB);                               //~vamtI~
	    yy+=MM2POINT(MmarginshiftL);                               //~vamtI~
    }                                                              //~vamtI~
    else                                                           //~vamtI~
    {                                                              //~vamtI~
    	xx+=MM2POINT(MmarginshiftR);                               //~vamtR~
	    yy+=MM2POINT(MmarginshiftB);                               //~vamtI~
    }                                                              //~vamtI~
    *Pporgx=xx;                                                    //~vamtI~
    *Pporgy=yy;                                                    //~vamtI~
	UTRACEP("gxepage_papershift output(point) orgx=%d,orgy=%d\n",xx,yy);//~vamtR~
}//gxepage_papershift                                              //~vamtI~
#endif                                                             //~vamtI~
//**************************************************************** //~2B04I~
//*get value and set to wxemain variable                           //~2B06R~
//**************************************************************** //~2B04I~
int  getparm(void)                                                 //~vXXER~
{                                                                  //~2B04I~
    char entrytext[128];                                           //~vXXER~
//**********************                                           //~2B04I~
//  Meditrow.GetWindowText(txt,sizeof(txt));                       //~vXXER~
//  Mpagerow   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_ROW,Mprtrow);             //~vXXER~
//  Meditcolumn.GetWindowText(txt,sizeof(txt));                    //~vXXER~
//  Mpagecol   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_COL,Mprtcol);             //~vXXER~
//  Meditpfontszh.GetWindowText(txt,sizeof(txt));                  //~vXXER~
//  Mpfontszh  =atoi(txt);                                         //~vXXER~
//  Meditpfontszw.GetWindowText(txt,sizeof(txt));                  //~vXXER~
//  Mpfontszw  =atoi(txt);                                         //~vXXER~
//  Meditpcellszh.GetWindowText(txt,sizeof(txt));                  //~vXXER~
//  Mpcellszh  =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_PROWH,Mpcellszh);         //~vXXER~
//  Meditpcellszhmax.GetWindowText(txt,sizeof(txt));               //~vXXER~
//  Mpcellszhmax  =atoi(txt);                                      //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_MAXCOLROW,Mpcellszhmax);  //~vXXER~
//  Meditpcellszw.GetWindowText(txt,sizeof(txt));                  //~vXXER~
//  Mpcellszw  =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_PCOLW,Mpcellszw);         //~vXXER~
//  Medit2p.GetWindowText(txt,sizeof(txt));                        //~vXXER~
//  M2pcol     =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_2P,Mprt2pcol);            //~vXXER~
//  Meditleft.GetWindowText(txt,sizeof(txt));                      //~vXXER~
//  Mmarginl   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_LEFT,Mmarginl);           //~vXXEI~
//  Meditright.GetWindowText(txt,sizeof(txt));                     //~vXXER~
//  Mmarginr   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_RIGHT,Mmarginr);          //~vXXEI~
//  Medittop.GetWindowText(txt,sizeof(txt));                       //~vXXER~
//  Mmargint   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_TOP,Mmargint);            //~vXXEI~
//  Meditbottom.GetWindowText(txt,sizeof(txt));                    //~vXXER~
//  Mmarginb   =atoi(txt);                                         //~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_BOTTOM,Mmarginb);         //~vXXEI~
//  Mheader    =Mcheckheader.GetCheck();                           //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_HEADER,Mheader);             //~vXXEI~
//  Mfooter    =Mcheckfooter.GetCheck();                           //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_FOOTER,Mfooter);             //~vXXEI~
//  Mlinenumber=Mchecklinenumber.GetCheck();                       //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_LINENUMBER,Mlinenumber);     //~vXXER~
//  Mfiletime  =Mcheckfiletime.GetCheck();                         //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_FILETIME,Mfiletime);         //~vXXEI~
//  Msystime   =Mchecksystime.GetCheck();                          //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_SYSTIME,Msystime);           //~vXXEI~
//  Mwwscrprt  =Mcheckwwscrprt.GetCheck();                         //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_WWSCRPRT,Mwwscrprt);         //~vXXEI~
//  M2p        =Mcheck2p.GetCheck();                               //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_2P,M2p);                     //~vXXEI~
//  Mlandscape =Mchecklandscape.GetCheck();                        //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_LANDSCAPE,Mlandscape);       //~vXXEI~
//	Mfullpage  =Mcheckfullpage.GetCheck();                         //~vXXER~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_FULLPAGE,Mfullpage);         //~vXXEI~
                                                                   //~vam7I~
	GET_CHKBOX(Sprintdlg,STRIDC_CHECK_PRINTLIGATURE,MprintLigature);//~vam7R~
    UTRACEP("gxepage getparm MprintLigature=%d\n",MprintLigature); //~vam7R~
    UTRACEP("gxepage getparm margin l=%d,r=%d,t=%d,b=%d\n",Mmarginl,Mmarginr,Mmargint,Mmarginb);//~vamtR~
#ifdef GTKPRINT                                                    //~vamtI~
    chkmarginshift();                                              //~vamtI~
    UTRACEP("getparm after chkmarginshift l=%d,r=%d,t=%d,b=%d\n",Mmarginl,Mmarginr,Mmargint,Mmarginb);//~vamtR~
    UTRACEP("getparm after chkmarginshift marginshift l=%d,r=%d,t=%d,b=%d\n",MmarginshiftL,MmarginshiftR,MmarginshiftT,MmarginshiftB);//~vamtR~
#endif                                                             //~vamtI~
                                                                   //~2B04I~
//  Mcombo_form.GetLBText(Mcombo_form.GetCurSel(),txt);            //~vXXER~
//	strncpy(Mformtype,txt,sizeof(Mformtype));                      //~vXXER~
#ifndef OPTGTK3                                                    //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,Mformtype);     //~vXXER~
#else   //OPTGTK3                                                  //~var8R~
	if (gxepage_combo_get_active(Sprintdlg,Sglcombopaper,STRIDC_COMBO_FORM,Mformtype)<0)//~var8R~
        return 4;                                                  //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_PRINTER,Mprinter);   //~v667I~
#else   //OPTGTK3                                                  //~var8R~
	if (gxepage_combo_get_active(Sprintdlg,Sglcomboprinter,STRIDC_COMBO_PRINTER,Mprinter)<0)//~var8R~
        return 4;                                                  //~var8R~
#endif                                                             //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_PRINTRANGE,entrytext);          //~vXXER~
    if (chkpagerange(entrytext))                                   //~vXXEI~
        return 4;                                                  //~vXXEI~
                                                                   //~vXXEI~
//  Mcombofontstyle.GetLBText(Mcombofontstyle.GetCurSel(),txt);    //~vXXER~
//	strncpy(Mprtfontstyle,txt,sizeof(Mprtfontstyle));              //~vXXER~
    if (  Mchkpfontsz                                              //~v51hI~
    	  &&  (/*  (Mpfontszh<PRINTFONTSZH_MIN||Mpfontszh>PRINTFONTSZH_MAX)//~vXXER~
    	       ||(Mpfontszw<PRINTFONTSZW_MIN||Mpfontszw>PRINTFONTSZW_MAX)//~v51hR~
    	       ||*/(Mpcellszh<PRINTCELLSZH_MIN||Mpcellszh>PRINTCELLSZH_MAX)//~vXXER~
    	       ||(Mpcellszw<PRINTCELLSZW_MIN||Mpcellszw>PRINTCELLSZW_MAX)//~v51hR~
              )                                                    //~v51hI~
       )                                                           //~v51hI~
    {                                                              //~v51hI~
//  	uerrmsgbox("invalid Col,Row,FontH FontW parm",0);          //~v627R~
    	uerrmsgbox("\"Col/Row by Cell-H/W\" is checked and Cell size parameter range err",0);//~vXXER~
        return 4;                                                  //~v51hI~
    }                                                              //~v51hI~
    UTRACEP("getparm Mwwscrprt=%d\n",Mwwscrprt);                   //~var8R~
    return 0;                                                      //~v51hR~
}//getparm                                                         //~2B09R~
//**************************************************************** //~vXXEI~
//*get paper width/height(unit:POINT)                              //~vam0R~
//**************************************************************** //~vXXEI~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT
//=========================================================================
int gxepage_prtgetformsz(int Plandscape,char *Pformtype,int *Ppwidth,int *Ppheight)//~vXXER~
{                                                                  //~vXXEI~
//  GList *pgl;                                                    //~vXXEI~//~vam0R~
//  GnomePrintPaper *ppp;                                          //~vXXER~//~vam0R~
    int ww,hh,rc;                                                  //~vXXER~
    int height,width;                                              //~vam0I~
//  int jj;                                                        //~va6yI~//~vam0R~
    char *pform;                                                   //~va6yI~
    RECT  formsz;                                                  //~va6yI~
//  GnomePrintPaper wkpp;                                          //~va6yI~//~vam0R~
    int pppok=0;                                                   //~vafeI~
//**********************                                           //~vXXEI~
    pform=Pformtype;                                               //~va6yR~
//for (jj=0;jj<2;jj++)                                             //~va6yI~//~vam0R~
//{                                                                //~va6yI~//~vam0R~
// if (!csubgetcupspagesz(CGCPOHW,&formsz,pform))	//get ww and hh//~vam7R~
// if (!csubgetcupspagesz(CGCPOHW,&formsz,pform,NULL))	//get ww and hh//~vam7I~//~vampR~
   if (!csubgetcupspagesz(CGCPOHW,&formsz,pform))	//get ww and hh//~vampI~
   {                                                               //~va6yI~
//  ppp=&wkpp;                                                     //~va6yI~//~vam0R~
//  ppp->height=MM2POINT(formsz.bottom);                           //~va6yR~//~vam0R~
    height=MM2POINT(formsz.bottom);                                //~vam0I~
//  ppp->width=MM2POINT(formsz.right);                             //~va6yR~//~vam0R~
    width=MM2POINT(formsz.right);                                  //~vam0I~
	pppok=1;                                                       //~vafeI~//~vam0R~
	UTRACEP("gxepage_prtgetforms ww=%dpoint,hh=%d,bottom=%d,right=%d\n",width,height,formsz.bottom,formsz.right);//~vam0R~
//   	break;	//cups form found                                      //~va6yI~//~vam0R~
   }                                                               //~va6yI~
//   else                                                            //~va6yI~//~vam0R~
//   {                                                               //~va6yI~//~vam0R~
//    pgl=Spaperlist;                                                //~vXXEI~//~vam0R~
//    while(pgl!=NULL)                                               //~vXXEI~//~vam0R~
//    {                                                              //~vXXEI~//~vam0R~
//        ppp=(GnomePrintPaper*)(pgl->data);                         //~vXXER~//~vam0R~
////      if (!strcmp(Pformtype,ppp->name))                          //~va6yR~//~vam0R~
//        if (!strcmp(pform,ppp->name))                              //~va6yI~//~vam0R~
//        {                                                          //~vafeI~//~vam0R~
//            pppok=1;                                               //~vafeI~//~vam0R~
//            break;                                                 //~vXXEI~//~vam0R~
//        }                                                          //~vafeI~//~vam0R~
//        pgl=pgl->next;                                             //~vXXEI~//~vam0R~
//    }                                                              //~vXXEI~//~vam0R~
//    if (pgl!=NULL)                                                 //~va6yI~//~vam0R~
//        break;                                                     //~va6yI~//~vam0R~
//   }                                                               //~va6yI~//~vam0R~
//    pform=DEF_FORMSIZE;                                            //~va6yR~//~vam0R~
//  }                                                                //~va6yI~//~vam0R~
//	if (pgl!=NULL)                                                 //~vXXEI~//~vafeR~
  	if (pppok)                                                     //~vafeI~
    {                                                              //~vXXEI~
        if (Plandscape)                                            //~vXXEI~
        {                                                          //~vXXEI~
//          ww=ppp->height;                                        //~vXXEI~//~vam0R~
            ww=height;                                             //~vam0I~
//          hh=ppp->width;                                         //~vXXEI~//~vam0R~
            hh=width;                                              //~vam0I~
        }                                                          //~vXXEI~
        else                                                       //~vXXEI~
        {                                                          //~vXXEI~
//          hh=ppp->height;                                        //~vXXEI~//~vam0R~
            hh=height;                                             //~vam0I~
//          ww=ppp->width;                                         //~vXXEI~//~vam0R~
            ww=width;                                              //~vam0I~
        }                                                          //~vXXEI~
        *Ppwidth=ww;                                               //~vXXEI~
        *Ppheight=hh;                                              //~vXXEI~
        UTRACEP("gxepage_prtgetformsz %s ww=%d,hh=%d\n",Pformtype,ww,hh);      //~v667R~//~vam0R~
	    rc=0;                                                      //~vXXEI~
    }                                                              //~vXXEI~
    else                                                           //~vXXEI~
    	rc=4;                                                      //~vXXEI~
    return rc;                                                     //~vXXEI~
}//gxepage_prtgetformsz                                            //~vXXER~
	#else    //!GTKPRINT
//==========================================================================
int gxepage_prtgetformsz(int Plandscape,char *Pformtype,int *Ppwidth,int *Ppheight)//~vXXER~
{                                                                  //~vXXEI~
	GList *pgl;                                                    //~vXXEI~
    GnomePrintPaper *ppp;                                          //~vXXER~
    int ww,hh,rc;                                                  //~vXXER~
    int jj;                                                        //~va6yI~
    char *pform;                                                   //~va6yI~
    RECT  formsz;                                                  //~va6yI~
    GnomePrintPaper wkpp;                                          //~va6yI~
    int pppok=0;                                                   //~vafeI~
//**********************                                           //~vXXEI~
    pform=Pformtype;                                               //~va6yR~
  for (jj=0;jj<2;jj++)                                             //~va6yI~
  {                                                                //~va6yI~
// if (!csubgetcupspagesz(CGCPOHW,&formsz,pform))	//get ww and hh//~vam7R~
// if (!csubgetcupspagesz(CGCPOHW,&formsz,pform,NULL))	//get ww and hh//~vam7I~//~vampR~
   if (!csubgetcupspagesz(CGCPOHW,&formsz,pform))	//get ww and hh//~vampI~
   {                                                               //~va6yI~
    ppp=&wkpp;                                                     //~va6yI~
    ppp->height=MM2POINT(formsz.bottom);                           //~va6yR~
    ppp->width=MM2POINT(formsz.right);                             //~va6yR~
    pppok=1;                                                       //~vafeI~
   	break;	//cups form found                                      //~va6yI~
   }                                                               //~va6yI~
   else                                                            //~va6yI~
   {                                                               //~va6yI~
    pgl=Spaperlist;                                                //~vXXEI~
  	while(pgl!=NULL)                                               //~vXXEI~
  	{                                                              //~vXXEI~
		ppp=(GnomePrintPaper*)(pgl->data);                         //~vXXER~
//      if (!strcmp(Pformtype,ppp->name))                          //~va6yR~
        if (!strcmp(pform,ppp->name))                              //~va6yI~
        {                                                          //~vafeI~
            pppok=1;                                               //~vafeI~
        	break;                                                 //~vXXEI~
        }                                                          //~vafeI~
		pgl=pgl->next;                                             //~vXXEI~
    }                                                              //~vXXEI~
    if (pgl!=NULL)                                                 //~va6yI~
        break;                                                     //~va6yI~
   }                                                               //~va6yI~
    pform=DEF_FORMSIZE;                                            //~va6yR~
  }                                                                //~va6yI~
//	if (pgl!=NULL)                                                 //~vXXEI~//~vafeR~
  	if (pppok)                                                     //~vafeI~
    {                                                              //~vXXEI~
        if (Plandscape)                                            //~vXXEI~
        {                                                          //~vXXEI~
            ww=ppp->height;                                        //~vXXEI~
            hh=ppp->width;                                         //~vXXEI~
        }                                                          //~vXXEI~
        else                                                       //~vXXEI~
        {                                                          //~vXXEI~
            hh=ppp->height;                                        //~vXXEI~
            ww=ppp->width;                                         //~vXXEI~
        }                                                          //~vXXEI~
        *Ppwidth=ww;                                               //~vXXEI~
        *Ppheight=hh;                                              //~vXXEI~
        dprintf("formsize %s ww=%d,hh=%d\n",Pformtype,ww,hh);      //~v667R~
	    rc=0;                                                      //~vXXEI~
    }                                                              //~vXXEI~
    else                                                           //~vXXEI~
    	rc=4;                                                      //~vXXEI~
    return rc;                                                     //~vXXEI~
}//gxepage_prtgetformsz                                            //~vXXER~
	#endif   //!GTKPRINT                                           //~vam0M~
#endif //!NOGOMEPRINT                                              //~vam0I~
//**************************************************************** //~2B07I~
//*set parm to wxemain variable                                    //~2B07I~
//**************************************************************** //~2B07I~
void putparm(void)                                                 //~vXXEI~
{                                                                  //~2B07I~
//**********************                                           //~2B07I~
//  strncpy(Mpwxemain->Mformtype,Mformtype,sizeof(Mpwxemain->Mformtype));//~vXXER~
//	strncpy(Mpwxemain->Mprtfontstyle,Mprtfontstyle,sizeof(Mpwxemain->Mprtfontstyle));//~vXXER~
  	strncpy(Mprtfontstyle,Gfontdata[1].FDfontname,sizeof(Mprtfontstyle));//~vXXEI~
//#ifndef XXE                                                        //~vXXEI~//~vamtR~
//    Mpwxemain->M2p        =M2p;                                    //~2B04I~//~vamtR~
//    Mpwxemain->Mfiletime  =Mfiletime;                              //~2B04I~//~vamtR~
//    Mpwxemain->Mheader    =Mheader;                                //~2B04I~//~vamtR~
//    Mpwxemain->Mfooter    =Mfooter;                                //~2B04I~//~vamtR~
//    Mpwxemain->Mlinenumber=Mlinenumber;                            //~2B04I~//~vamtR~
//    Mpwxemain->Msystime   =Msystime;                               //~2B04I~//~vamtR~
//    Mpwxemain->Mwwscrprt  =Mwwscrprt;                              //~2B10I~//~vamtR~
//    Mpwxemain->Mprtcol    =Mpagecol;                               //~2B09R~//~vamtR~
//    Mpwxemain->Mprtrow    =Mpagerow;                               //~2B09R~//~vamtR~
//    Mpwxemain->Mpfontszh  =Mpfontszh;                              //~v51hR~//~vamtR~
//    Mpwxemain->Mpfontszw  =Mpfontszw;                              //~v51hI~//~vamtR~
//    Mpwxemain->Mpcellszh  =Mpcellszh;                              //~v51hI~//~vamtR~
//    Mpwxemain->Mpcellszhmax  =Mpcellszhmax;                        //~v62WI~//~vamtR~
//    Mpwxemain->Mpcellszw  =Mpcellszw;                              //~v51hI~//~vamtR~
//    Mpwxemain->Mprt2pcol  =M2pcol;                                 //~2B04I~//~vamtR~
//    Mpwxemain->Mmarginl   =Mmarginl;                               //~2B04I~//~vamtR~
//    Mpwxemain->Mmarginr   =Mmarginr;                               //~2B04I~//~vamtR~
//    Mpwxemain->Mmargint   =Mmargint;                               //~2B04I~//~vamtR~
//    Mpwxemain->Mmarginb   =Mmarginb;                               //~2B04I~//~vamtR~
//    Mpwxemain->Mlandscape =Mlandscape;                             //~2B04I~//~vamtR~
//    Mpwxemain->Mfullpage  =Mfullpage ;                             //~2B30I~//~vamtR~
//    Mpwxemain->Mchkpfontsz=Mchkpfontsz;                            //~v51hI~//~vamtR~
//    Mpwxemain->MprintLigature=MprintLigature;                      //~vam7R~//~vamtR~
//#endif                                                             //~vXXEI~//~vamtR~
    UTRACEP("putparm margin l=%d,r=%d,t=%d,b=%d\n",Mmarginl,Mmarginr,Mmargint,Mmarginb);//~vamtI~
#ifdef GTKPRINT                                                    //~var8R~
    UTRACEP("putparm marginshift l=%d,r=%d,t=%d,b=%d\n",MmarginshiftL,MmarginshiftR,MmarginshiftT,MmarginshiftB);//~vamtI~
#endif                                                             //~var8R~
    return;                                                        //~2B04I~
}//putparm                                                         //~2B09R~
//**************************************************************** //~2B23I~
//*save and restore wxemain parm at preview call                   //~2B23I~
//**************************************************************** //~2B23I~
void saverestparm(int Psavesw)                                     //~vXXER~
{                                                                  //~2B23I~
//**********************                                           //~2B23I~
	if (Psavesw)                                                   //~2B23I~
    {                                                              //~2B23I~
    	 dprintf("entry value\n");                                  //~v667R~
//pagesetup parm                                                   //~2B23I~
        strncpy(Msvformtype,Mformtype,sizeof(Msvformtype));        //~vXXER~
        strncpy(Msvprinter,Mprinter,sizeof(Msvprinter));           //~v667I~
		strncpy(Msvprtfontstyle,Mprtfontstyle,sizeof(Mprtfontstyle));//~vXXEI~
		memcpy(&Ssvfontdata1,&Gfontdata[1],FONTDATASZ);            //~vXXEI~
        Msv2p           =M2p        ;                              //~vXXER~
        Msvfiletime     =Mfiletime  ;                              //~vXXER~
        Msvheader       =Mheader    ;                              //~vXXER~
        Msvfooter       =Mfooter    ;                              //~vXXER~
        Msvlinenumber   =Mlinenumber;                              //~vXXER~
        Msvsystime      =Msystime   ;                              //~vXXER~
        Msvwwscrprt     =Mwwscrprt  ;                              //~vXXER~
        Msvprtcol       =Mprtcol    ;                              //~vXXER~
        Msvprtrow       =Mprtrow    ;                              //~vXXER~
        Msvprt2pcol     =Mprt2pcol  ;                              //~vXXER~
        Msvmarginl      =Mmarginl   ;                              //~vXXER~
        Msvmarginr      =Mmarginr   ;                              //~vXXER~
        Msvmargint      =Mmargint   ;                              //~vXXER~
        Msvmarginb      =Mmarginb   ;                              //~vXXER~
#ifdef GTKPRINT                                                    //~vamtI~
        MsvmarginshiftT=MmarginshiftT;                             //~vamtI~
        MsvmarginshiftB=MmarginshiftB;                             //~vamtI~
        MsvmarginshiftL=MmarginshiftL;                             //~vamtI~
        MsvmarginshiftR=MmarginshiftR;                             //~vamtI~
#endif                                                             //~vamtI~
        Msvlandscape    =Mlandscape ;                              //~vXXER~
        Msvfullpage     =Mfullpage  ;                              //~vXXER~
		Msvpcellszh     =Mpcellszh;                                //~vXXEI~
		Msvpcellszhmax  =Mpcellszhmax;                             //~vXXEI~
		Msvpcellszw     =Mpcellszw;                                //~vXXER~
		Msvchkpfontsz   =Mchkpfontsz;                              //~vXXEI~
		MsvprintLigature=MprintLigature;                           //~vam7R~
    }                                                              //~2B23I~
    else                                                           //~2B23I~
    {                                                              //~2B23I~
    	 dprintf("exit value\n");                                   //~v667R~
        strncpy(Mformtype,Msvformtype,sizeof(Mformtype));          //~vXXER~
        strncpy(Mprinter,Msvprinter,sizeof(Mprinter));             //~v667I~
		strncpy(Mprtfontstyle,Msvprtfontstyle,sizeof(Mprtfontstyle));//~vXXEI~
		memcpy(&Gfontdata[1],&Ssvfontdata1,FONTDATASZ);            //~vXXEI~
        M2p         =Msv2p;                                        //~vXXER~
        Mfiletime   =Msvfiletime;                                  //~vXXER~
        Mheader     =Msvheader;                                    //~vXXER~
        Mfooter     =Msvfooter;                                    //~vXXER~
        Mlinenumber =Msvlinenumber;                                //~vXXER~
        Msystime    =Msvsystime;                                   //~vXXER~
        Mwwscrprt   =Msvwwscrprt;                                  //~vXXER~
        Mprtcol     =Msvprtcol;                                    //~vXXER~
        Mprtrow     =Msvprtrow;                                    //~vXXER~
        Mprt2pcol   =Msvprt2pcol;                                  //~vXXER~
        Mmarginl    =Msvmarginl;                                   //~vXXER~
        Mmarginr    =Msvmarginr;                                   //~vXXER~
        Mmargint    =Msvmargint;                                   //~vXXER~
        Mmarginb    =Msvmarginb;                                   //~vXXER~
#ifdef GTKPRINT                                                    //~vamtI~
        MmarginshiftT=MsvmarginshiftT;                             //~vamtI~
        MmarginshiftB=MsvmarginshiftB;                             //~vamtI~
        MmarginshiftL=MsvmarginshiftL;                             //~vamtI~
        MmarginshiftR=MsvmarginshiftR;                             //~vamtI~
#endif                                                             //~vamtI~
        Mlandscape  =Msvlandscape;                                 //~vXXER~
        Mfullpage   =Msvfullpage ;                                 //~vXXER~
		Mpcellszh   =Msvpcellszh;                                  //~vXXEI~
		Mpcellszhmax=Msvpcellszhmax;                               //~vXXEI~
		Mpcellszw   =Msvpcellszw;                                  //~vXXER~
		Mchkpfontsz =Msvchkpfontsz;                                //~vXXEI~
		MprintLigature=MsvprintLigature;                           //~vam7R~
    }                                                              //~2B23I~
    dprintf("form=%s,font=%s,printer=%s\n",Mformtype,Mprtfontstyle,Mprinter);//~v667R~
    dprintf("landspace=%d\n",Mlandscape);                          //~v667R~
    UTRACEP("saverestparm margin l=%d,r=%d,t=%d,b=%d\n",Mmarginl,Mmarginr,Mmargint,Mmarginb);//~v667R~//~vamtR~
#ifdef GTKPRINT                                                    //~var8R~
    UTRACEP("saverestparm marginshift l=%d,r=%d,t=%d,b=%d\n",MmarginshiftL,MmarginshiftR,MmarginshiftT,MmarginshiftB);//~vamtI~
#endif                                                             //~var8R~
    dprintf("cell h=%d,w=%d,max=%d\n",Mpcellszh,Mpcellszw,Mpcellszhmax);//~v667R~
    dprintf("col=%d,row=%dcolrow by cellsz=%d\n",Mprtcol,Mprtrow,Mchkpfontsz);//~v667R~
    dprintf("lineno=%d.hdr=%d,footer=%d,wwscrprt=%d\n",Mlinenumber,Mheader,Mfooter,Mwwscrprt);//~v667R~
    dprintf("2p=%d-%d\n",M2p,Mprt2pcol);                           //~v667R~
    dprintf("filetime=%d,systime=%d,fullpage=%d,printligature=%d\n",Mfiletime,Msystime,Mfullpage,MprintLigature);//~v667R~//~vam7R~
    return;                                                        //~2B23I~
}//saverestparm                                                    //~vXXER~
//**************************************************************** //~2B09I~
//*                                                                //~2B09I~
//**************************************************************** //~2B09I~
#ifndef NOPRINT                                                    //~vam0I~
int  pagecount(int Phcopysw)                                       //~vXXER~
{                                                                  //~2B09I~
	int formw,formh,cellh,cellw,linenofw,col2p,lnotype;            //~2C07R~
//  int pfontsz;                                                   //~v51hR~
    void *pfh;                                                     //~2B09I~
    void *pcw;                                                     //~v627I~
    int rc2;                                                       //~var5I~
//*******************************                                  //~2B09I~
//  Mprttype=Mpwxemain->prtgetscrdata(Phcopysw,Mwwscrprt,&pfh,Mprtfnm,//~v627R~
    Mprttype=xxemain_prtgetscrdata(Phcopysw,Mwwscrprt,&pcw,&pfh,Mprtfnm,//~vXXER~
									&Mtotlineno,&Mmaxlrecl,&Mlinenosz,&Mcmaxlrecl,&lnotype);//~2C07R~
//  cellh=Mcellh;                                                  //~v664R~
//  cellw=Mcellw;                                                  //~v664R~
    cellh=Mpfontszh;                                               //~v664I~
    cellw=Mpfontszw;                                               //~v664I~
	if (Mchkpfontsz)	//fontsize specified                       //~v51hI~
    {                                                              //~v51hI~
    	cellh=Mpcellszh,cellw=Mpcellszw;                           //~v51hR~
        if (!cellh)                                                //~v51hI~
        	cellh=Mpfontszh;                                       //~v51hR~
        if (!cellw)                                                //~v664I~
        	cellw=Mpfontszw;                                       //~v664I~
    }                                                              //~v51hI~
    Mprtdatamaxcol=                                                //~v51hR~
    Mcmaxcol=Mprtcol;                                              //~vXXER~
    Mprtdatamaxrow=                                                //~v51hR~
    Mcmaxrow=Mprtrow;                                              //~vXXER~
    if (Mprttype==PRTTYPE_VHEXTEXT                                 //~v627R~
    ||  Mprttype==PRTTYPE_VHEXHHEX                                 //~va49I~
    ||  Mprttype==PRTTYPE_VHEXBIN)                                 //~v627R~
    {                                                              //~v627I~
        if (Mprtdatamaxrow>=3)                                     //~v627I~
            Mprtdatamaxrow=(Mprtdatamaxrow/3)*3;    //multiple of 3 line//~v627R~
    }                                                              //~v627I~
//  if (!Mcmaxcol || !Mcmaxrow)                                    //~v51hR~
    if (Mprttype>0)                                                //~v51hI~
    {                                                              //~2B09I~
      if (!Mcmaxcol || !Mcmaxrow || Mchkpfontsz)//fixed font or col/ro is 0//~v51hI~
      {                                                            //~v51hI~
       rc2=                                                        //~var5I~
		gxepage_prtgetformsz(Mlandscape,Mformtype,&formw,&formh);  //~vXXER~
       if (rc2)                                                    //~var5I~
       	return 4;                                                  //~var5I~
        formw-=max(Mmarginl,MARGIN_FORM_CLIP)+max(Mmarginr,MARGIN_FORM_CLIP);//~2B24I~//~vamtR~
        formh-=max(Mmargint,MARGIN_FORM_CLIP)+max(Mmarginb,MARGIN_FORM_CLIP);//~2B24I~//~vamtR~
        if (Mlinenumber)                                           //~2B09I~
        	linenofw=Mlinenosz+1;                                  //~2B09I~
        else                                                       //~2B09I~
        	linenofw=0;                                            //~2B09I~
        if (M2p)                                                   //~2B09I~
            col2p=Mprt2pcol;                                       //~vXXER~
        else                                                       //~2B09I~
            col2p=0;                                               //~2B09I~
//        if (Mchkpfontsz)//fixed font                             //~v51hR~
//            pfontsz=(Mpfontszw<<16)|Mpfontszh;  //id of fixed font//~v51hR~
//        else                                                     //~v51hR~
//            pfontsz=0;                                           //~v51hR~
    	if (xxemain_prtajustcolrow(Mprttype,formw,formh,Mheader+Mfooter,cellw,cellh,//~vXXER~
//  							Mcmaxlrecl,Mtotlineno,linenofw,col2p,&Mcmaxcol,&Mcmaxrow);//~v51hR~
    							Mcmaxlrecl,Mtotlineno,linenofw,col2p,&Mcmaxcol,&Mcmaxrow,//~v51hR~
//  							Mchkpfontsz,&Mprtdatamaxcol,&Mprtdatamaxrow))//~v62WR~
    							Mchkpfontsz,Mpcellszhmax,&Mprtdatamaxcol,&Mprtdatamaxrow))//~v62WI~
      		return 4;                    	                       //~v51hR~
      }//fixed font or col/ro is 0                                 //~v51hI~
      else                                                         //~v51hI~
      {                                                            //~v51hI~
      	Mprtdatamaxcol=Mcmaxcol;                                   //~v51hR~
      	Mprtdatamaxrow=Mcmaxrow;                                   //~v51hR~
      }                                                            //~v51hI~
//  }                                                              //~v51hR~
//  if (Mprttype>0)                                                //~v51hR~
//  {                                                              //~v51hR~
//      Mmaxpage=wxe_prtgetmaxpage(pfh,&Mcmaxlrecl,&Mcmaxcol,Mcmaxrow,&Mtotrow);//~v51hR~
//      Mmaxpage=wxe_prtgetmaxpage(pfh,&Mcmaxlrecl,&Mcmaxcol,&Mprtdatamaxcol,Mprtdatamaxrow,&Mtotrow);//~v627R~
        Mmaxpage=wxe_prtgetmaxpage(pcw,pfh,&Mcmaxlrecl,&Mcmaxcol,&Mprtdatamaxcol,Mprtdatamaxrow,&Mtotrow);//~v627I~
        if (M2p)                                                   //~2B24I~
        	Mmaxpage=(Mmaxpage+1)>>1;                              //~2B24I~
    }                                                              //~2B24I~
    else                                                           //~2B10I~
    {                                                              //~2B10I~
  	 	Mtotrow=Mtotlineno;                                        //~2B10I~
    	Mmaxpage=1;                                                //~2B10I~
    }                                                              //~2B10I~
    return 0;                                                      //~v51hR~
}//pagecount                                                       //~2B09I~
#endif //!NOGOMEPRINT                                              //~vam0I~
//**************************************************************** //~va6yI~
//*update form at printer combo box changed                        //~va6yI~
//**************************************************************** //~va6yI~
#ifndef NOPRINT                                                    //~vam0I~
void gxepage_updateformlist(void)                                  //~va6yI~
{                                                                  //~va6yI~
	char printer[sizeof(Mprinter)];                                //~va6yI~
	char form[sizeof(Mformtype)];                                  //~va6yI~
//************************                                         //~va6yI~
#ifndef OPTGTK3                                                    //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_PRINTER,printer);    //~va6yR~
#else   //OPTGTK3                                                  //~var8R~
	gxepage_combo_get_active(Sprintdlg,Sglcomboprinter,STRIDC_COMBO_PRINTER,printer);//~var8R~
#endif                                                             //~var8R~
    if (!strcmp(printer,Mprinter))                                 //~va6yI~
    	return;	//same or dup event                                //~va6yI~
    strcpy(Mprinter,printer);                                      //~va6yI~
#ifndef OPTGTK3                                                    //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,form);          //~va6yI~
#else   //OPTGTK3                                                  //~var8R~
	gxepage_combo_get_active(Sprintdlg,Sglcombopaper,STRIDC_COMBO_FORM,form);//~var8R~
#endif                                                             //~var8R~
	Initcombo(form);//update formlist                              //~va6yR~
}//gxepage_updateformlist                                          //~va6yI~
#endif //!NOGOMEPRINT                                              //~vam0I~
//**************************************************************** //~2B03I~
//*                                                                //~2B03I~
//**************************************************************** //~2B03I~
//BOOL Initcombo(void)                                             //~va6yR~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT
BOOL Initcombo(char *Pformtype)                                    //~va6yR~
{                                                                  //~2B03aI~//~vXXER~
//	GnomePrintPaper *ppp/*,*pppdef*/;                                  //~vXXER~//~vaa7R~//~vam0R~
//	GList *gl;                                                     //~vXXER~//~vam0R~
	GList *glcombo;                                                //~vXXEI~
    GtkWidget *pwdcombo;                                           //~vXXEI~
    char *pformlist,*pform,*pformtype;                             //~va6yR~
    int formno,entsz,ii;                                           //~va6yR~
    char realname[PPDMAXNAME];                                     //~vam0I~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
	int activeidx=0,idx=0;                                         //~var8R~
#endif                                                             //~var8R~
//********************************                                 //~2B03I~
	dprintf("InitcomboGtk Mform=%s,parm=%s\n",Mformtype,Pformtype);   //~va6yR~//~vam0R~
    if (!(pformtype=Pformtype))                                    //~va6yR~
    	pformtype=Mformtype;                                       //~va6yR~
//    ppp=(GnomePrintPaper*)gnome_print_paper_get_default();         //~vXXEI~//~vam0R~
//    if (ppp)                                                       //~vXXEI~//~vam0R~
//         dprintf("default paper %s,w=%lf,h=%lf\n",ppp->name,ppp->width,ppp->height);//~v667R~//~vam0R~
//  if (!Pformtype)                                                  //~va6yR~//~vam0R~
//    if (!*Mformtype)                                               //~vXXEI~//~vam0R~
//    {                                                              //~vXXEI~//~vam0R~
//        if (ppp)                                                   //~vXXEI~//~vam0R~
//            strcpy(Mformtype,ppp->name);                           //~vXXEI~//~vam0R~
//    }                                                              //~vXXEI~//~vam0R~
//	gl=Spaperlist;                                                 //~vXXER~//~vam0R~
    glcombo=NULL;                                                  //~vXXEI~
//if (!csubgetcupsform(0,0/*dest*/,&pformlist,&formno,&entsz))     //~vam0R~
    csubsrchprinterGtk(Mprinter,realname);                         //~vam0I~
  if (!csubgetcupsform(0,realname/*dest*/,&pformlist,&formno,&entsz))//~vam0I~
  {                                                                //~va6yI~
  	for (pform=pformlist,ii=formno;ii>0;ii--,pform+=entsz)         //~va6yI~
  	{                                                              //~va6yI~
  		dprintf("paper list=%s,Pformtype=%s\n",pform,Pformtype);   //~var8R~
        glcombo=g_list_append(glcombo,pform);                      //~va6yI~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
        if (!strcmp(pform,Mformtype))                              //~var8R~
        	activeidx=idx;                                         //~var8R~
        idx++;                                                     //~var8R~
#endif                                                             //~var8R~
    }                                                              //~va6yI~
    if (Scupspaperlist)                                            //~va6yI~
    	ufree(Scupspaperlist);                                     //~va6yI~
    Scupspaperlist=pformlist;                                      //~va6yI~
  }                                                                //~va6yI~
  else                                                             //~va6yI~
  {                                                                //~va6yI~
//    while(gl!=NULL)                                                //~vXXEI~//~vam0R~
//    {                                                              //~vXXEI~//~vam0R~
//        ppp=(GnomePrintPaper*)gl->data;                            //~vXXEI~//~vam0R~
//         dprintf("default paper list =%s,w=%lf,h=%lf\n",ppp->name,ppp->width,ppp->height);//~v667R~//~vam0R~
//        glcombo=g_list_append(glcombo,ppp->name);                  //~vXXER~//~vam0R~
//        gl=gl->next;                                               //~vXXEI~//~vam0R~
//    }                                                              //~vXXEI~//~vam0R~
        glcombo=g_list_append(glcombo,"Not defined");              //~vam0I~
  }                                                                //~va6yI~
    pwdcombo=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_COMBO_FORM);//~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_combo_set_popdown_strings(GTK_COMBO(pwdcombo),glcombo);    //~vXXER~
    g_list_free(glcombo);                                          //~vXXEI~
#else                                                              //~var8R~
	if (Sglcombopaper)                                             //~var8R~
	    g_list_free(Sglcombopaper);                                //~var8R~
    csub_gtk_combo_set_popdown_strings(GTK_COMBO_BOX_TEXT(pwdcombo),glcombo);//~var8R~
    Sglcombopaper=glcombo;                                         //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    SET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,pformtype);     //~va6yR~
#else   //OPTGTK3                                                  //~var8R~
	dprintf("initcombo setactive=%d\n",activeidx);                 //~var8R~
    gtk_combo_box_set_active(GTK_COMBO_BOX(pwdcombo),activeidx);   //~var8R~
#endif                                                             //~var8R~
	displayHWMargin(pformtype);//update formlist                   //~vam8I~
//#ifndef XXE                                                        //~vXXEI~//~vam0R~
//    Mpwxemain->createfontlist(&Mcombofontstyle,Mprtfontstyle);     //~v51hR~//~vam0R~
//#endif                                                             //~vXXEI~//~vam0R~
    return 0;                                                      //~2B03I~
}//Initcombo                                                       //~vXXER~
//==========================================================================
	#else    //!GTKPRINT
//==========================================================================
BOOL Initcombo(char *Pformtype)                                    //~va6yR~
{                                                                  //~2B03aI~//~vXXER~
  	GnomePrintPaper *ppp/*,*pppdef*/;                                  //~vXXER~//~vaa7R~
	GList *gl;                                                     //~vXXER~
	GList *glcombo;                                                //~vXXEI~
    GtkWidget *pwdcombo;                                           //~vXXEI~
    char *pformlist,*pform,*pformtype;                             //~va6yR~
    int formno,entsz,ii;                                           //~va6yR~
//********************************                                 //~2B03I~
	dprintf("Initcombo Mform=%s,parm=%s\n",Mformtype,Pformtype);   //~va6yR~
    if (!(pformtype=Pformtype))                                    //~va6yR~
    	pformtype=Mformtype;                                       //~va6yR~
    ppp=(GnomePrintPaper*)gnome_print_paper_get_default();         //~vXXEI~
    if (ppp)                                                       //~vXXEI~
		 dprintf("default paper %s,w=%lf,h=%lf\n",ppp->name,ppp->width,ppp->height);//~v667R~
//  pppdef=ppp;                                                    //~vXXEI~//~vaa7R~
  if (!Pformtype)                                                  //~va6yR~
	if (!*Mformtype)                                               //~vXXEI~
    {                                                              //~vXXEI~
	    if (ppp)                                                   //~vXXEI~
	        strcpy(Mformtype,ppp->name);                           //~vXXEI~
    }                                                              //~vXXEI~
	gl=Spaperlist;                                                 //~vXXER~
    glcombo=NULL;                                                  //~vXXEI~
  if (!csubgetcupsform(0,0/*dest*/,&pformlist,&formno,&entsz))     //~va6yI~
  {                                                                //~va6yI~
  	for (pform=pformlist,ii=formno;ii>0;ii--,pform+=entsz)         //~va6yI~
  	{                                                              //~va6yI~
  		dprintf("paper list=%s\n",pform);                          //~va6yI~
        glcombo=g_list_append(glcombo,pform);                      //~va6yI~
    }                                                              //~va6yI~
    if (Scupspaperlist)                                            //~va6yI~
    	ufree(Scupspaperlist);                                     //~va6yI~
    Scupspaperlist=pformlist;                                      //~va6yI~
  }                                                                //~va6yI~
  else                                                             //~va6yI~
  {                                                                //~va6yI~
  	while(gl!=NULL)                                                //~vXXEI~
  	{                                                              //~vXXEI~
		ppp=(GnomePrintPaper*)gl->data;                            //~vXXEI~
  		 dprintf("default paper list =%s,w=%lf,h=%lf\n",ppp->name,ppp->width,ppp->height);//~v667R~
//      glcombo=g_list_append(glcombo,"test size");                //~vXXER~
        glcombo=g_list_append(glcombo,ppp->name);                  //~vXXER~
		gl=gl->next;                                               //~vXXEI~
    }                                                              //~vXXEI~
  }                                                                //~va6yI~
    pwdcombo=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_COMBO_FORM);  \
    gtk_combo_set_popdown_strings(GTK_COMBO(pwdcombo),glcombo);    //~vXXER~
    g_list_free(glcombo);                                          //~vXXEI~
//  gnome_print_paper_free_list(gl);                               //~vXXER~
//  SET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,Mformtype);     //~va6yR~
    SET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,pformtype);     //~va6yR~
                                                                   //~vXXEI~
#ifndef XXE                                                        //~vXXEI~
	Mpwxemain->createfontlist(&Mcombofontstyle,Mprtfontstyle);     //~v51hR~
#endif                                                             //~vXXEI~
    return 0;                                                      //~2B03I~
}//Initcombo                                                       //~vXXER~
	#endif   //!GTKPRINT
#endif //!NOGOMEPRINT                                              //~vam0I~
//**************************************************************** //~v667I~
//*                                                                //~v667I~
//**************************************************************** //~v667I~
#ifdef GTKPRINT
//=========================================================================//~vbj0I~
//fill combobox by enum printer on GTK3                            //~vbj0I~
//=========================================================================//~vbj0I~
int Initcomboenumprinter(GList **Ppplist,int *Ppactiveidx)         //~vbj0R~
{                                                                  //~2B03aI~//~vbj0I~
	GList *glcombo;                                                //~vbj0I~
    int pn0;                                                       //~vbj0R~
	int activeidx=0,idx=0;                                         //~vbj0R~
    char *plist,*pc;                                               //~vbj0I~
    int ctr,defidx;                                                //~vbj0R~
//********************************                                 //~vbj0I~
    UTRACEP("%s: entry Mprinter=%s\n",UTT,Mprinter);               //~vbj0I~
    glcombo=*Ppplist;                                              //~vbj0R~
    pn0=0;                                                         //~vbj0I~
    if (ctr=csublistprinter(&plist,&defidx),ctr)                   //~vbj0I~
    {                                                              //~vbj0I~
        pn0=ctr;                                                   //~vbj0I~
        activeidx=defidx;                                          //~vbj0I~
        glcombo=g_list_append(glcombo,DEF_PRINTER);                //~vbj0I~
        for (pc=plist;ctr>0;pc+=strlen(pc)+1,ctr--)                //~vbj0I~
        {                                                          //~vbj0I~
            UTRACEP("%s:cups printer list=%s\n",UTT,pc);           //~vbj0I~
            glcombo=g_list_append(glcombo,pc);                     //~vbj0R~
            if (!strcmp(pc,Mprinter))                              //~vbj0R~
                activeidx=idx+1;                                   //~vbj0R~
            idx++;                                                 //~vbj0I~
        }                                                          //~vbj0I~
		Senmuprinterlist=plist;                                    //~vbj0I~
    }//ctr!=0                                                      //~vbj0I~
    *Ppactiveidx=activeidx;                                        //~vbj0R~
    *Ppplist=glcombo;                                              //~vbj0I~
    UTRACEP("%s:return listctr=%d,Mprinter=%s\n",UTT,pn0,Mprinter);//~vbj0R~
    return pn0;                                                    //~vbj0R~
}//Initcomboenumprinter                                            //~vbj0R~
//=========================================================================
BOOL Initcomboprinter(void)                                        //~v667I~
{                                                                  //~2B03aI~//~v667I~
	GList *glcombo;                                                //~v667I~
    GtkWidget *pwdcombo;                                           //~v667I~
    int pn,pn0;                                                    //~v667R~
    cups_dest_t  *pl,*pl0;                                         //~v75VI~
#ifndef OPTGTK3                                                    //~var8R~
	int activeidx=0;                                               //~vbj0I~
#else                                                              //~var8R~
	int activeidx=0,idx=0;                                         //~var8R~
#endif                                                             //~var8R~
	int swenumprinter=0;                                           //~vbj0I~
//********************************                                 //~v667I~
    UTRACEP("%s: entry Mprinter=%s\n",UTT,Mprinter);               //~vb7sI~
    glcombo=NULL;                                                  //~v667I~
    Snoprinter=0;                                                  //~var8R~
 if (pn0=Initcomboenumprinter(&glcombo,&activeidx),pn0)    //by enumprinter//~vbj0I~
    swenumprinter=1;                                               //~vbj0I~
 else                                                              //~vbj0I~
 {                                                                 //~vbj0I~
    UTRACEP("%s:call cupsGetDest\n",UTT);                          //~vbj0R~
    pn0=pn=cupsGetDests(&pl0);                                     //~v75VI~
    UTRACEP("%s:return cupsGetDest\n",UTT);                        //~vbj0R~
 }                                                                 //~vbj0I~
  if (pn0)                                                         //~vagGI~
  {                                                                //~vagGI~
   if (!swenumprinter)                                             //~vbj0I~
   {                                                               //~vbj0I~
    glcombo=g_list_append(glcombo,DEF_PRINTER);                    //~v667R~//~vam0R~
    for (pl=pl0;pn>0;pn--,pl++)                                    //~v667I~
    {                                                              //~v667I~
    	dprintf("cups printer list=%s,isdefault=%d\n",pl->name,pl->is_default);//~va49R~
    	UTRACEP("%s:cups printer list=%s,isdefault=%d\n",UTT,pl->name,pl->is_default);//~vb7sR~
#ifndef OPTGTK3                                                    //~var8R~
        glcombo=g_list_append(glcombo,pl->name);                   //~v75VR~
#else   //pl-name may be freeed  by cupsFreeDest,need alloc to save as static//~var8R~
        glcombo=g_list_append(glcombo,strdup(pl->name));           //~var8R~
        if (!strcmp(pl->name,Mprinter))                            //~var8R~
        {                                                          //~vb7sI~
		    UTRACEP("%s:activeindex=%d\n",UTT,idx);                //~vb7sI~
//      	activeidx=idx;                                         //~var8R~//~vbi8R~
        	activeidx=idx+1; //index 0 is "Default"                //~vbi8I~
        }                                                          //~vb7sI~
        idx++;                                                     //~var8R~
#endif                                                             //~var8R~
    }                                                              //~v667I~
   }//!swenumprinter                                               //~vbj0I~
    pwdcombo=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_COMBO_PRINTER);//~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_combo_set_popdown_strings(GTK_COMBO(pwdcombo),glcombo);    //~v667I~
#else                                                              //~var8R~
    csub_gtk_combo_set_popdown_strings(GTK_COMBO_BOX_TEXT(pwdcombo),glcombo);//~var8R~
#endif                                                             //~var8R~
//#ifndef OPTGTK3                                                    //~var8R~//~vbj0R~
//    g_list_free(glcombo);                                          //~v667I~//~vbj0R~
//#else                                                              //~var8R~//~vbj0R~
	if (Sglcomboprinter)                                           //~var8R~
	    g_list_free(Sglcomboprinter);                              //~var8R~
    Sglcomboprinter=glcombo;                                       //~var8R~
//#endif                                                             //~var8R~//~vbj0R~
   if (!swenumprinter)                                             //~vbj0I~
    cupsFreeDests(pn0,pl0);  //free printer list                   //~vagGI~
  }                                                                //~vagGI~
    if (!pn0)	//not CUPS but LPRing                              //~v667I~
    {                                                              //~vam0I~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
    	pwdcombo=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_COMBO_PRINTER);//~var8R~
        glcombo=g_list_append(glcombo,NO_CUPS_PRINTER);            //~var8R~
	    csub_gtk_combo_set_popdown_strings(GTK_COMBO_BOX_TEXT(pwdcombo),glcombo);//~var8R~
		if (Sglcomboprinter)                                       //~var8R~
	    	g_list_free(Sglcomboprinter);                          //~var8R~
    	Sglcomboprinter=glcombo;                                   //~var8R~
#endif                                                             //~var8R~
        Snoprinter=1;                                              //~var8R~
    	strcpy(Mprinter,NO_CUPS_PRINTER);                              //~v667I~//~vam0R~
		gxepage_err_nocupsprinter();                               //~vam0I~
    }                                                              //~vam0I~
#ifndef OPTGTK3                                                    //~var8R~
    SET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_PRINTER,Mprinter);   //~v667I~
#else   //OPTGTK3                                                  //~var8R~
    gtk_combo_box_set_active(GTK_COMBO_BOX(pwdcombo),activeidx);   //~var8R~
#endif                                                             //~var8R~
    UTRACEP("%s:return Mprinter=%s\n",UTT,Mprinter);            //~vam0I~//~vb7sR~
    return 0;                                                      //~v667I~
}//Initcomboprinter                                                //~v667I~
#else    //!GTKPRINT
//=========================================================================
BOOL Initcomboprinter(void)                                        //~v667I~
{                                                                  //~2B03aI~//~v667I~
	GList *glcombo;                                                //~v667I~
    GtkWidget *pwdcombo;                                           //~v667I~
    int pn,pn0;                                                    //~v667R~
//  char **pl,**pl0;                                               //~v75VR~
    cups_dest_t  *pl,*pl0;                                         //~v75VI~
//********************************                                 //~v667I~
    glcombo=NULL;                                                  //~v667I~
//  pn0=pn=cupsGetPrinters(&pl0);                                  //~v75VR~
    pn0=pn=cupsGetDests(&pl0);                                     //~v75VI~
  if (pn0)                                                         //~vagGI~
  {                                                                //~vagGI~
    glcombo=g_list_append(glcombo,DEF_PRINTER);                    //~v667R~
    for (pl=pl0;pn>0;pn--,pl++)                                    //~v667I~
    {                                                              //~v667I~
    	dprintf("cups printer list=%s\n",*pl);                     //~var8R~
//      glcombo=g_list_append(glcombo,*pl);                        //~v75VI~
    	dprintf("cups printer list=%s,isdefault=%d\n",pl->name,pl->is_default);//~va49R~
        glcombo=g_list_append(glcombo,pl->name);                   //~v75VR~
    }                                                              //~v667I~
    pwdcombo=lookup_widget(GTK_WIDGET(Sprintdlg),STRIDC_COMBO_PRINTER);  \
    gtk_combo_set_popdown_strings(GTK_COMBO(pwdcombo),glcombo);    //~v667I~
    g_list_free(glcombo);                                          //~v667I~
//  free(pl0);  //free printer list                                //~vagGR~
    cupsFreeDests(pn0,pl0);  //free printer list                   //~vagGI~
  }                                                                //~vagGI~
    if (!pn0)	//not CUPS but LPRing                              //~v667I~
    	strcpy(Mprinter,DEF_PRINTER);                              //~v667I~
    SET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_PRINTER,Mprinter);   //~v667I~
    return 0;                                                      //~v667I~
}//Initcomboprinter                                                //~v667I~
#endif   //!GTKPRINT
//**************************************************************** //~v51hI~
void gxepage_OnCheck2p(void)                                       //~vXXER~
{                                                                  //~2B04I~
//  M2p=Mcheck2p.GetCheck();                                       //~vXXER~
    GET_CHKBOX(Sprintdlg,STRIDC_CHECK_2P,M2p);                     //~vXXEI~
	 dprintf("OmCheck2p M2p=%d\n",M2p);                             //~v667R~
    if (M2p)                                                       //~vXXER~
    {                                                              //~vXXEI~
//	    Medit2p.EnableWindow(TRUE);                                //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_2P,TRUE);              //~vXXEI~
    }                                                              //~vXXEI~
    else                                                           //~2B04I~
    {                                                              //~vXXEI~
//	    Medit2p.EnableWindow(FALSE);                               //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_2P,FALSE);             //~vXXEI~
    }                                                              //~vXXEI~
}                                                                  //~2B04I~
//**************************************************************** //~v51hI~
void gxepage_OnCheckpfontsz(void)                                  //~vXXER~
{                                                                  //~v51hI~
//  Mchkpfontsz=Mcheckpfontsz.GetCheck();                          //~vXXER~
    GET_CHKBOX(Sprintdlg,STRIDC_CHECK_PFONTSZ,Mchkpfontsz);        //~vXXEI~
	 dprintf("OnCheckpfontsz Mchkpfontsz%d\n",Mchkpfontsz);         //~v667R~
    if (Mchkpfontsz)                                               //~v51hI~
    {                                                              //~v51hI~
//      Meditpfontszh.EnableWindow(TRUE);                          //~vXXER~
//      Meditpfontszw.EnableWindow(TRUE);                          //~vXXER~
//      Meditpcellszh.EnableWindow(TRUE);                          //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_PROWH,TRUE);           //~vXXER~
//      Meditpcellszw.EnableWindow(TRUE);                          //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_PCOLW,TRUE);           //~vXXER~
//      Meditpcellszhmax.EnableWindow(FALSE);                      //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_MAXCOLROW,FALSE);      //~vXXER~
    }                                                              //~v51hI~
    else                                                           //~v51hI~
    {                                                              //~v51hI~
//	    Meditpfontszh.EnableWindow(FALSE);                         //~vXXER~
//	    Meditpfontszw.EnableWindow(FALSE);                         //~vXXER~
//	    Meditpcellszh.EnableWindow(FALSE);                         //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_PROWH,FALSE);          //~vXXER~
//	    Meditpcellszw.EnableWindow(FALSE);                         //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_PCOLW,FALSE);          //~vXXER~
//	    Meditpcellszhmax.EnableWindow(TRUE);                       //~vXXER~
		SET_SENSITIVE(Sprintdlg,STRIDC_SPIN_MAXCOLROW,TRUE);       //~vXXER~
    }                                                              //~v51hI~
}//OnCheckpfontsz                                                  //~v51hI~
//**************************************************************** //~2B09I~
//*                                                                //~2B09I~
//**************************************************************** //~2B09I~
void displaypageno(void)                                           //~vXXER~
{                                                                  //~2B09I~
    char txt[128];                                                 //~v51hR~
    int pos;                                                       //~v51hR~
//*************************                                        //~2B09I~
//  Meditfilename.SetWindowText(Mprtfnm);	//filename             //~vXXER~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_FILENAME,Mprtfnm);        //~vXXER~
    sprintf(txt,"%d",Mcurpage);                                    //~2C14R~
//  Meditcurpage.SetWindowText(txt);       //max lrecl             //~vXXER~
	SET_ENTRYTEXT(Sprintdlg,STRIDC_SPIN_CURPAGE,txt);              //~vXXEI~
//  sprintf(txt,"/%d page. %d line. maxlen=%d",                    //~v56vR~
    sprintf(txt,"/%d pg. %d ln. maxln=%d",                         //~v56vI~
    		Mmaxpage,Mtotlineno,Mmaxlrecl);                        //~2C14I~
//  Meditmaxlrecl.SetWindowText(txt);       //max lrecl            //~vXXER~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_MAXPAGE,txt);             //~vXXER~
//    if (Mpagecol)                       //non 0 parm specified   //~v51hR~
////      *txt=0;                                                  //~v51hR~
//        col=Mpagecol;                                            //~v51hR~
//    else                                                         //~v51hR~
////      sprintf(txt,"%d",Mcmaxcol);                              //~v51hR~
//        col=Mcmaxcol;                                            //~v51hR~
////  Meditmaxcol0.SetWindowText(txt);        //calculated  maxcol when col=0//~v51hR~
//    if (Mpagerow)                                                //~v51hR~
////      *txt=0;                                                  //~v51hR~
//        row=Mpagerow;                                            //~v51hR~
//    else                                                         //~v51hR~
////      sprintf(txt,"%d",Mcmaxrow);                              //~v51hR~
//        row=Mcmaxrow;                                            //~v51hR~
////  Meditmaxrow0.SetWindowText(txt);        //calculated max row when row=0//~v51hR~
//    sprintf(txt,"( col: %d , row: %d )",col,row);                //~v51hR~
	if (Mprtdatamaxcol==Mcmaxcol)                                  //~v51hI~
    	pos=sprintf(txt,"(col: %d , ",Mcmaxcol);                   //~v51hI~
    else                                                           //~v51hI~
    	pos=sprintf(txt,"(col: %d/%d , ",Mprtdatamaxcol,Mcmaxcol); //~v51hI~
	if (Mprtdatamaxrow==Mcmaxrow)                                  //~v51hI~
    	sprintf(txt+pos,"row: %d )",Mcmaxrow);                     //~v51hI~
    else                                                           //~v51hI~
    	sprintf(txt+pos,"row: %d/%d )",Mprtdatamaxrow,Mcmaxrow);   //~v51hI~
//  Meditmaxcolrow.SetWindowText(txt);        //calculated max row when row=0//~vXXER~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_COLS,txt);                //~vXXER~
}//displaypageno                                                   //~2B09I~
	                                                               //~2B09M~
//**************************************************************** //~2B04I~
//*                                                                //~2B04I~
//**************************************************************** //~2B04I~
#ifndef NOPRINT                                                    //~vam0I~
void displayform(int Phcopysw)                                     //~vXXER~
{                                                                  //~2B04I~
#define MINPIXEL 1                                                 //~2B09R~
//	COLORREF bg=RGB(180,180,180);     //gra                       //~vXXER~
//	COLORREF bgf=RGB(255,255,255);     //form                      //~vXXER~
//	COLORREF txtfg=RGB(160,160,160);     //gray                    //~vXXER~
#ifdef XXX                                                         //~vXXER~
  	GdkColor bg=COLOR_GRAY;                                        //~vXXER~
  	GdkColor bgf=COLOR_WHITE;                                      //~vXXER~
    GdkColor txtfg=COLOR_BLACK;                                    //~vXXER~
#endif                                                             //~vXXEI~
	int ww,hh,formw,formh,marginx=0,marginy=0;                     //~2B23R~
//	int  marginl,marginr,margint,marginb;                          //~vXXER~
    RECT formrect/*,drawrect*/;                                    //~vXXER~
    float fh,frhws,frhwf,fscalex,fscaley;                          //~vXXER~
    int rc2;                                                       //~var5I~
//************************                                         //~2B04I~
//#ifndef OPTGTK3                                                  //~var8R~
//#else   //OPTGTK3                                                //~var8R~
//    csub_get_widget_allocation_wh(Gpview,&Mwinextw,&Mwinexth);//referred at prtviewportgcopy//~var8R~
//    UTRACEP("displayform Gpview w=%d,h=%d\n",Mwinextw,Mwinexth); //~var8R~
//#endif                                                           //~var8R~
    if (pagecount(Phcopysw))	//parm err                         //~v51hR~
    	return;                                                    //~v51hI~
    if (Mcurpage>Mmaxpage)                                         //~2C14R~
//      Mcurpage=Mmaxpage;                                         //~v51gR~
        Mcurpage=1;                                                //~v51gI~
    else                                                           //~v51gI~
    	if (Mcurpage<0)                                            //~v51gR~
        	Mcurpage=Mmaxpage;                                     //~v51gR~
        else                                                       //~v51gI~
    		if (!Mcurpage)                                         //~v51gI~
	        	Mcurpage=1;                                        //~v51gR~
    displaypageno();                                               //~2B09R~
//  previewrectdraw(pdc,&br,&Mpreview_rect);                       //~vXXER~
#ifndef OPTGTK3                                                    //~var8R~
    previewrectdraw(&Gpreviewbg,&Mpreview_rect);                   //~vXXER~
#else   //OPTGTK3                                                  //~var8R~
#endif                                                             //~var8R~
//**form rectangle                                                 //~2B09M~
  rc2=                                                             //~var5I~
	gxepage_prtgetformsz(Mlandscape,Mformtype,&formw,&formh);      //~vXXER~
  if (rc2)                                                         //~var5I~
    return;                                                        //~var5I~
    formrect=Mpreview_rect;                                        //~2B06I~
    marginx=MARGIN_PREVIEWBOX;                                     //~2B06I~
    marginy=MARGIN_PREVIEWBOX;                                     //~2B06I~
    formrect.top+=marginy;                                         //~2B06I~
    formrect.bottom-=marginy;                                      //~2B06I~
    formrect.left+=marginx;                                        //~2B06I~
    formrect.right-=marginx;                                       //~2B06I~
    ww=formrect.right-formrect.left;                               //~2B09R~
    hh=formrect.bottom-formrect.top;                               //~2B09R~
    UTRACEP("displayform w=%d,h=%d,top=%d,bot=%d,l=%d,r=%d\n",ww,hh,formrect.top,formrect.bottom,formrect.left,formrect.right);//~vam0I~
    frhwf=(fh=(float)formh)/formw;		//forma rate h/w           //~2B06R~
    frhws=(fh=(float)hh)/ww;		//box rate h/w                 //~2B09R~
    if (frhwf<frhws)			//screen is taller,landscape       //~2B06I~
    {                                                              //~2B06I~
        marginx=0;                                                 //~2B06I~
      	marginy=(hh-(int)(ww*frhwf))/2;                            //~2B09R~
    }                                                              //~2B06I~
    else						//sceen is portlate                //~2B06R~
    {                                                              //~2B06I~
        marginx=(ww-(int)(hh/frhwf))/2;                            //~2B09R~
        marginy=0;                                                 //~2B06I~
    }                                                              //~2B06I~
    formrect.top   +=marginy;                                      //~2B06R~
    formrect.bottom-=marginy;                                      //~2B06R~
    formrect.left  +=marginx;                                      //~2B06R~
    formrect.right -=marginx;                                      //~2B06R~
    UTRACEP("displayform w=%d,h=%d,top=%d,bot=%d,l=%d,r=%d\n",ww,hh,formrect.top,formrect.bottom,formrect.left,formrect.right);//~v667R~//~vam0R~
//  previewrectdraw(&Gprintbg,&formrect);	//pixmap bg is white   //~vXXER~
	fscalex=(gdouble)(formrect.right-formrect.left)/formw;         //~vXXER~
	fscaley=(gdouble)(formrect.bottom-formrect.top)/formh;         //~vXXEI~
    UTRACEP("displayform scale=(%f,%f),formw=%d,h=%d\n",fscalex,fscaley,formw,formh);//~vam8R~
//**draw text by rectangle                                         //~2B09I~
//#define PREVIEWTEXT                                              //~v51hR~
//#ifdef PREVIEWTEXT                                               //~v51hR~
	saverestparm(1);    //save wxemain parm                        //~2B23I~
	putparm();          //update wxemain parm                      //~2B23I~
#ifdef XXX                                                         //~vXXER~
	gdk_gc_set_rgb_bg_color(Gpgcpreview,&bgf);  //white            //~vXXEI~
	gdk_gc_set_rgb_fg_color(Gpgcpreview,&txtfg);//black            //~vXXEI~
#endif                                                             //~vXXEI~
    previewforminit(Phcopysw,formw,formh);                         //~vXXER~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
    previewrectdraw(&Gpreviewbg,&Mpreview_rect);                   //~var8R~
#endif                                                             //~var8R~
    xxemain_prtpreview(Phcopysw,Mcurpage);                         //~vXXER~
    drawpreviewcanvas(Gppixmappreview,fscalex,fscaley,&formrect);  //~vXXER~
	previewformunref();                                            //~vXXEI~
	saverestparm(0);    //restore wxemain parm                     //~2B23I~
//#else                                                            //~v51hR~
//    displaybyrect(pdc,int Phcopysw,&drawrect);                   //~v51hR~
//#endif                                                           //~v51hR~
    return;                                                        //~2B04I~
}//displayform                                                     //~2B04R~
#endif //!NOGOMEPRINT                                              //~vam0I~
////****************************************************************//~v51hR~
////*                                                              //~v51hR~
////****************************************************************//~v51hR~
//void CWxepage::displaybyrect(CDC *Ppdc,int Phcopysw,RECT &Pdrawrect)//~v51hR~
//{                                                                //~v51hR~
//#define MINPIXEL 1                                               //~v51hR~
//    COLORREF bg=RGB(180,180,180);     //gray                     //~v51hR~
//    COLORREF bgf=RGB(255,255,255);     //form                    //~v51hR~
//    COLORREF txtfg=RGB(160,160,160);     //gray                  //~v51hR~
//    int ww,ww2,ww3,ww4,hh,hh2,hh3,marginx=0,marginy=0;           //~v51hR~
//    int  linenofw;                                               //~v51hR~
//    RECT textrect,textrect2,linenorect,hdrrect,ftrrect;          //~v51hR~
//    float fh,fw,frhwf,frhwt;                                     //~v51hR~
//    int   cmaxrow,txtw,txth,swlineno,swww,sw2p,swheader,swfooter;//~v51hR~
////************************                                       //~v51hR~
//    if (Mprttype<0) //prtscr                                     //~v51hR~
//    {                                                            //~v51hR~
//        swheader=0;                                              //~v51hR~
//        swfooter=0;                                              //~v51hR~
//        swlineno=0;                                              //~v51hR~
//        sw2p=0;                                                  //~v51hR~
//        swww=Mwwscrprt;                                          //~v51hR~
//    }                                                            //~v51hR~
//    else                                                         //~v51hR~
//    {                                                            //~v51hR~
//        swheader=Mheader;                                        //~v51hR~
//        swfooter=Mfooter;                                        //~v51hR~
//        swlineno=Mlinenumber;                                    //~v51hR~
//        sw2p=M2p;                                                //~v51hR~
//        swww=0;                                                  //~v51hR~
//    }                                                            //~v51hR~
//    textrect=Pdrawrect;                                          //~v51hR~
//    cmaxrow=Mcmaxrow+(swheader+swfooter)*2;                      //~v51hR~
//    if (swlineno)                                                //~v51hR~
//        linenofw=Mlinenosz+1;                                    //~v51hR~
//    else                                                         //~v51hR~
//        linenofw=0;                                              //~v51hR~
//    txtw=Mcmaxcol+linenofw;                                      //~v51hR~
//    if (sw2p)                                                    //~v51hR~
//        txtw+=txtw+M2pcol;      //width of 2p                    //~v51hR~
//    fw=(float)(Mpwxemain->Mcellw*txtw);                          //~v51hR~
//    fh=(float)(Mpwxemain->Mcellh*cmaxrow);                       //~v51hR~
//    frhwt=fh/fw;                                                 //~v51hR~
//    ww=textrect.right-textrect.left;                             //~v51hR~
//    hh=textrect.bottom-textrect.top;                             //~v51hR~
//    frhwf=(float)hh/ww;     //form  rate h/w in margin           //~v51hR~
//    if (frhwt>frhwf)        //text is tall                       //~v51hR~
//        textrect.right-=ww-(int)(hh/frhwt); //ajust width by form orientation//~v51hR~
//    else                                                         //~v51hR~
//        textrect.bottom-=hh-(int)(ww*frhwt);//ajust height by form orientation//~v51hR~
//    CBrush  brt(txtfg);                                          //~v51hR~
//    hh2=hh/cmaxrow; // 1line height                              //~v51hR~
//    hh3=hh*2/cmaxrow;//2line height                              //~v51hR~
//    if (hh2<MINPIXEL)                                            //~v51hR~
//        hh2=MINPIXEL;                                            //~v51hR~
//    if (hh3<=hh2+MINPIXEL)                                       //~v51hR~
//        hh3=hh2+MINPIXEL;                                        //~v51hR~
//    if (swheader)                                                //~v51hR~
//    {                                                            //~v51hR~
//        hdrrect=textrect;                                        //~v51hR~
//        hdrrect.bottom=hdrrect.top+hh2;                          //~v51hR~
//        previewrectdraw(Ppdc,&brt,&hdrrect);                     //~v51hR~
//        textrect.top+=hh3;                                       //~v51hR~
//    }                                                            //~v51hR~
//    if (swfooter)                                                //~v51hR~
//    {                                                            //~v51hR~
//        ftrrect=textrect;                                        //~v51hR~
//        ftrrect.top=ftrrect.bottom-hh2;                          //~v51hR~
//        textrect.bottom-=hh3;                                    //~v51hR~
//    }                                                            //~v51hR~
////text area                                                      //~v51hR~
//    ww=textrect.right-textrect.left;                             //~v51hR~
//    hh=textrect.bottom-textrect.top;                             //~v51hR~
//    if (sw2p)                                                    //~v51hR~
//    {                                                            //~v51hR~
//        ww4=ww*M2pcol/txtw;                                      //~v51hR~
//        if (ww4<MINPIXEL)                                        //~v51hR~
//            ww4=MINPIXEL;                                        //~v51hR~
//    }                                                            //~v51hR~
//    ww2=ww*(linenofw-1)/txtw;   //pixel for lineno fld           //~v51hR~
//    ww3=ww*linenofw/txtw;       //pixel for lineno fld+1 byte delm//~v51hR~
//    if (ww2<MINPIXEL)                                            //~v51hR~
//        ww2=MINPIXEL;                                            //~v51hR~
//    if (ww3<=ww2+MINPIXEL)                                       //~v51hR~
//        ww3=ww2+MINPIXEL;                                        //~v51hR~
//    if (swww)       //wysiwig scr prt                            //~v51hR~
//    {                                                            //~v51hR~
//        textrect.right=textrect.left+ww*Mpwxemain->Mscrcmaxcol/Mcmaxcol;//net range//~v51hR~
//        textrect.bottom=textrect.top+hh*Mpwxemain->Mscrcmaxrow/cmaxrow;//net range//~v51hR~
//    }                                                            //~v51hR~
//    else                                                         //~v51hR~
//        if (Mtotrow<Mcmaxrow)    //draw net row range for 1page  //~v51hR~
//        {                                                        //~v51hR~
//            txth=Mtotrow+(swheader+swfooter)*2;                  //~v51hR~
//            textrect.bottom=hh*txth/cmaxrow;                     //~v51hR~
//        }                                                        //~v51hR~
//    if (sw2p)                                                    //~v51hR~
//    {                                                            //~v51hR~
//        textrect2=textrect;                                      //~v51hR~
//        textrect.right=textrect.left+(ww-ww4)/2;                 //~v51hR~
//        textrect2.left=textrect.right+ww4;                       //~v51hR~
//    }                                                            //~v51hR~
//    if (swlineno)                                                //~v51hR~
//    {                                                            //~v51hR~
//        linenorect=textrect;                                     //~v51hR~
//        linenorect.right=linenorect.left+ww2;                    //~v51hR~
//        previewrectdraw(Ppdc,&brt,&linenorect);                  //~v51hR~
//        textrect.left+=ww3;                                      //~v51hR~
//    }                                                            //~v51hR~
//    previewrectdraw(Ppdc,&brt,&textrect);                        //~v51hR~
//    if (sw2p)                                                    //~v51hR~
//    {                                                            //~v51hR~
//        if (swlineno)                                            //~v51hR~
//        {                                                        //~v51hR~
//            linenorect=textrect2;                                //~v51hR~
//            linenorect.right=linenorect.left+ww2;                //~v51hR~
//            previewrectdraw(Ppdc,&brt,&linenorect);              //~v51hR~
//            textrect2.left+=ww3;                                 //~v51hR~
//        }                                                        //~v51hR~
//        previewrectdraw(Ppdc,&brt,&textrect2);                   //~v51hR~
//    }                                                            //~v51hR~
//                                                                 //~v51hR~
//    if (swfooter)                                                //~v51hR~
//        previewrectdraw(Ppdc,&brt,&ftrrect);                     //~v51hR~
//    return;                                                      //~v51hR~
//}//displaybyrect                                                 //~v51hR~
//void previewrectdraw(CDC *Ppdc,CBrush *Ppbrush,GdkColor Ppcolor,RECT *Pprect)//~vXXER~
void previewrectdraw(GdkColor *Ppcolor,RECT *Pprect)               //~vXXEI~
{                                                                  //~2B09I~
//  GnomeCanvasItem *item;                                         //~vXXEI~//~vaa7R~
    gdouble x1,x2,y1,y2;                                           //~vXXEI~
//  gdouble affine[6];                                             //~vXXER~
//*******************************                                  //~vXXEI~
#ifdef XXX                                                         //~vXXEI~
	if (!Pprect)	//clear req                                    //~vXXEI~
    {                                                              //~vXXEI~
    	gdk_window_clear(Spwdpreview->window);                     //~vXXEI~
		return;                                                    //~vXXEI~
	}                                                              //~vXXEI~
#endif                                                             //~vXXEI~
#ifdef XXX                                                         //~vXXEI~
	gdk_gc_set_rgb_fg_color(Gpgcpreview,Ppcolor);                  //~vXXER~
    gdk_draw_rectangle(Spwdpreview->window,Gpgcpreview,TRUE,	//fill//~vXXER~
    					Pprect->left,Pprect->top,Pprect->right-Pprect->left,Pprect->bottom-Pprect->top);//~vXXER~
#endif                                                             //~vXXEI~
    x1=(gdouble)Pprect->left;                                      //~vXXEI~
    y1=(gdouble)Pprect->top;                                       //~vXXEI~
    x2=(gdouble)Pprect->right-1;                                   //~vXXEI~
    y2=(gdouble)Pprect->bottom-1;                                  //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
    /*item=*/gnome_canvas_item_new(gnome_canvas_root(GNOME_CANVAS(Spwdpreview)),//~vXXER~//~vaa7R~
    					GNOME_TYPE_CANVAS_RECT,                    //~vXXEI~
                        "x1",x1,"y1",y1,"x2",x2,"y2",y2,           //~vXXER~
                        "fill_color_gdk",Ppcolor,                  //~vXXEI~
                        NULL);                                     //~vXXEI~
#else   //OPTGTK3                                                  //~var8R~
//  csub_gdk_draw_rectangle_direct(Spwdpreview,Ppcolor,TRUE,x1,y1,x2-x1,y2-y1);//~var8R~
    gdk_gc_set_foreground(SpgcpreviewWidget,Ppcolor);      //white //~var8R~
    csub_gdk_draw_rectangle(SppixmappreviewWidget,SpgcpreviewWidget,TRUE,x1,y1,x2-x1,y2-y1);//~var8R~
#endif                                                             //~var8R~
//    gnome_canvas_item_show(item);                                //~vXXER~
//    gnome_canvas_item_i2c_affine(item,affine);                   //~vXXER~
//    dprintf("i2c after  0=%lf,1=%lf,2=%lf,3=%lf,4=%lf,5=%lf\n",affine[0],affine[1],affine[2],affine[3],affine[4],affine[5]);//~v667R~
 dprintf("canvas rect x1=%lf,y1=%lf,x2=%lf,y2=%lf\n",x1,y1,x2,y2); //~v667R~
    return;                                                        //~2B09I~
}//previewrectdraw                                                 //~vXXER~
//**************************************************************** //~vXXEI~
//*intialize paper pixmap                                          //~vXXEI~
//**************************************************************** //~vXXEI~
void  previewforminit(int Phcopysw,int Pformw,int Pformh)          //~vXXER~
{                                                                  //~vXXEI~
	int fontidx;                                                   //~vXXEI~
//************************************                             //~vXXEI~
	dprintf("previewforminit\n");                                  //~var8R~
//  fontidx=(Phcopysw==0);                                         //~vXXER~
    fontidx=1;			//preview by print font                    //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
    Gppixmappreview=gdk_pixmap_new(Spwdpreview->window,Pformw,Pformh,-1);//-1:same depth as drawable//~vXXEI~
#else                                                              //~var8R~
    if (Gppixmappreview)                                           //~var8R~
    	csub_gc_destroy_pixmap(Gpgcpreview,Gppixmappreview);  //destroy gc and pixmap//~var8R~
    Gppixmappreview=csub_pixmap_new(Spwdpreview,Pformw,Pformh,-1);//-1:same depth as drawable//~var8R~
    Gpgcpreview=csub_gc_new_pixmap(Spwdpreview,Gppixmappreview);	//cr for background surface//~var8R~
    if (SppixmappreviewWidget)                                     //~var8R~
    	csub_gc_destroy_pixmap(SpgcpreviewWidget,SppixmappreviewWidget);  //destroy gc and pixmap//~var8R~
    SppixmappreviewWidget=csub_pixmap_new(Spwdpreview,Mpreview_rect.right,Mpreview_rect.bottom,-1);//~var8R~
    SpgcpreviewWidget=csub_gc_new_pixmap(Spwdpreview,SppixmappreviewWidget);	//cr for background surface//~var8R~
#endif                                                             //~var8R~
    dprintf("preview pixmap w=%d,h=%d\n",Pformw,Pformh);           //~v667R~
//pango                                                            //~vXXEI~
	Gplayoutpreview=gtk_widget_create_pango_layout(Gpview,NULL);//colormap,fontdesc,base direction from Gpview//~vXXER~
    pango_layout_set_font_description(Gplayoutpreview,Gfontdata[fontidx].FDfontdesc);//~vXXER~
    UTRACEP("previewforminit pango_layout_et_font_description Gplayoutpreview=%p,fontdesc[%d]=%p\n",Gplayoutpreview,fontidx,Gfontdata[fontidx].FDfontdesc);//~vam7R~
//color                                                            //~vXXEI~
    gdk_gc_set_foreground(Gpgcpreview,&Gprintbg);      //white     //~vXXEI~
    gdk_draw_rectangle(Gppixmappreview,Gpgcpreview,TRUE,0,0,Pformw,Pformh);//~vXXEI~
    gdk_gc_set_background(Gpgcpreview,&Gprintbg);                  //~vXXEI~
    gdk_gc_set_foreground(Gpgcpreview,&Gprintfg);                  //~vXXEI~
    gdk_gc_set_line_attributes(Gpgcpreview,3,GDK_LINE_SOLID,GDK_CAP_NOT_LAST,GDK_JOIN_MITER);//~vXXER~
	return;                                                        //~vXXEI~
}//previewforminit                                                 //~vXXER~
//**************************************************************** //~vXXEI~
//*intialize paper pixmap                                          //~vXXEI~
//**************************************************************** //~vXXEI~
void  previewformunref(void)                                       //~vXXEI~
{                                                                  //~vXXEI~
//************************************                             //~vXXEI~
    if (Gppangoattrlist)                                           //~vXXEI~
    {                                                              //~vXXEI~
    	pango_attr_list_unref(Gppangoattrlist);                    //~vXXEI~
    	Gppangoattrlist=0;                                         //~vXXEI~
        UTRACEP("gxepage free Gppangoattrlist\n");                 //~var8R~
    }                                                              //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
    g_object_unref(G_OBJECT(Gppixmappreview));                     //~vXXEM~
#else   //unref at destroy                                         //~var8R~
#endif                                                             //~var8R~
	return;                                                        //~vXXEI~
}//xxemain_scrbgrect                                               //~vXXEI~
//**************************************************************** //~vXXER~
//*draw preview window                                             //~vXXEI~
//**************************************************************** //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
void drawpreviewcanvas(GdkPixmap *Pppixmap,gdouble Pscalex,gdouble Pscaley,RECT *Pprect)//~vXXER~
{                                                                  //~vXXEI~
	GdkPixbuf *pixbuf;                                             //~vXXEI~
    GnomeCanvasItem *item;                                         //~vXXEI~
    GnomeCanvasGroup *group;                                       //~vXXEI~
    gdouble affine[6];                                             //~vXXEI~
    gdouble xx,yy,hh,ww;                                           //~vXXEI~
//*************************                                        //~vXXEI~
dprintf("reducerate=x=%lf,y=%lf\n",Pscalex,Pscaley);               //~v667R~
    group=gnome_canvas_root(GNOME_CANVAS(Spwdpreview));            //~vXXER~
//  gnome_canvas_set_pixels_per_unit(GNOME_CANVAS(Spwdpreview),Pfreducerate);//~vXXER~
 	pixbuf=gdk_pixbuf_get_from_drawable(NULL,Pppixmap,NULL,0,0,0,0,-1,-1);//~vXXEI~
 	xx=(gdouble)(Pprect->left)/Pscalex;                            //~vXXEI~
 	yy=(gdouble)(Pprect->top)/Pscaley;                             //~vXXEI~
 	ww=(gdouble)(Pprect->right-Pprect->left);                      //~vXXEI~
 	hh=(gdouble)(Pprect->bottom-Pprect->top);                      //~vXXEI~
    dprintf("preview item new x=%lf,y=%lf,w=%lf,h=%lf\n",xx,yy,ww,hh);//~v667R~
    item=gnome_canvas_item_new(group,gnome_canvas_pixbuf_get_type(),"pixbuf",pixbuf,//~vXXER~
 			"x",xx,"y",yy,"width",ww,"height",hh,                  //~vXXER~
// 			"x_in_pixels",1,                                       //~vXXER~
// 			"y_in_pixels",1,                                       //~vXXER~
// 			"width_in_pixels",1,                                   //~vXXER~
// 			"height_in_pixels",1,                                  //~vXXER~
 			"anchor",GTK_ANCHOR_NW,                                //~vXXER~
            NULL);                                                 //~vXXEI~
//    gnome_canvas_item_i2w_affine(item,affine);                   //~vXXER~
//    dprintf("i2w before 0=%lf,1=%lf,2=%lf,3=%lf,4=%lf,5=%lf\n",affine[0],affine[1],affine[2],affine[3],affine[4],affine[5]);//~v667R~
    gnome_canvas_item_i2c_affine(item,affine);                     //~vXXER~
    dprintf("i2c before 0=%lf,1=%lf,2=%lf,3=%lf,4=%lf,5=%lf\n",affine[0],affine[1],affine[2],affine[3],affine[4],affine[5]);//~v667R~
//  gnome_canvas_set_pixels_per_unit(GNOME_CANVAS(Spwdpreview),Pfreducerate);//~vXXER~
                                                                   //~vXXEI~
    affine[0]=Pscalex; affine[3]=Pscaley;                          //~vXXER~
    gnome_canvas_item_affine_absolute(item,affine);                //~vXXEI~
//  gnome_canvas_item_set(item,"anchor",GTK_ANCHOR_NW,NULL);       //~vXXER~
//    gnome_canvas_item_i2w_affine(item,affine);                   //~vXXER~
//    dprintf("i2w after  0=%lf,1=%lf,2=%lf,3=%lf,4=%lf,5=%lf\n",affine[0],affine[1],affine[2],affine[3],affine[4],affine[5]);//~v667R~
    gnome_canvas_item_i2c_affine(item,affine);                     //~vXXER~
    dprintf("i2c after  0=%lf,1=%lf,2=%lf,3=%lf,4=%lf,5=%lf\n",affine[0],affine[1],affine[2],affine[3],affine[4],affine[5]);//~v667R~
//  gnome_canvas_item_show(item);                                  //~vXXER~
}//drawpreviewcanvas                                               //~vXXEI~
#else   //OPTGTK3                                                  //~var8R~
//**************************************************************** //~var8R~
//*set pixmap of paper into form on preview box                    //~var8R~
//**************************************************************** //~var8R~
void drawpreviewcanvas(GdkPixmap *Pppixmap,gdouble Pscalex,gdouble Pscaley,RECT *Pprect)//~var8R~
{                                                                  //~var8R~
	int ww,hh;                                                     //~var8R~
    GtkWidget *pwd;                                                //~var8R~
    GdkPixmap *ppmrect;                                            //~var8R~
    GdkGC *pgcrect;                                                //~var8R~
    double fscalex,fscaley;                                        //~var8R~
//*************************                                        //~var8R~
	pwd=Spwdpreview;                                               //~var8R~
 	ww=(Pprect->right-Pprect->left);	//form width in preview area//~var8R~
 	hh=(Pprect->bottom-Pprect->top);                               //~var8R~
	dprintf("drawpreviewcanvas form in box ww=%d,hh=%d\n",ww,hh);  //~var8R~
	UTRACEP("drawpreviewcanvas form in box x=%d,y=%d,ww=%d,hh=%d\n",Pprect->left,Pprect->top,ww,hh);//~var8R~
    ppmrect=cairo_surface_create_for_rectangle(SppixmappreviewWidget,(double)Pprect->left,(double)Pprect->top,(double)ww,(double)hh);//~var8R~
    pgcrect=cairo_create(ppmrect);                                 //~var8R~
    fscalex=Pscalex;                                               //~var8R~
    fscaley=Pscaley;                                               //~var8R~
//    if (Mwwscrprt)                                               //~var8R~
//    {                                                            //~var8R~
//        int viewww,viewhh;                                       //~var8R~
//        UTRACEP("drawpreviewcanvas default window w=%d,h=%d\n",Mwinextw,Mwinexth);//~var8R~
//        csub_get_widget_allocation_wh(Gpview,&viewww,&viewhh);   //~var8R~
//        UTRACEP("drawpreviewcanvas old scalex=%f,scaley=%f\n",fscalex,fscaley);//~var8R~
//        fscalex*=(double)viewww/Mwinextw;                        //~var8R~
//        fscaley*=(double)viewww/Mwinexth;                        //~var8R~
//        UTRACEP("drawpreviewcanvas Gpview w=%d,h=%d, new scalex=%f,scaley=%f\n",viewww,viewhh,fscalex,fscaley);//~var8R~
//    }                                                            //~var8R~
    cairo_scale(pgcrect,fscalex,fscaley);                          //~var8R~
    cairo_set_source_surface(pgcrect,Pppixmap,0.0/*Pxxsrc*/,0.0/*Pyysrc*/);//~var8R~
    cairo_paint(pgcrect);                                          //~var8R~
    csub_gc_destroy_pixmap(pgcrect,ppmrect);  //destroy gc and pixmap//~var8R~
    ww=Mpreview_rect.right;                                        //~var8R~
    hh=Mpreview_rect.bottom;                                       //~var8R~
	dprintf("drawpreviewcanvas box ww=%d,hh=%d\n",ww,hh);          //~var8R~
    gtk_widget_queue_draw_area(pwd,0,0,ww,hh);                     //~var8R~
}//drawpreviewcanvas                                               //~var8R~
//**************************************************************** //~var8R~
//*by "draw" signal                                                //~var8R~
//**************************************************************** //~var8R~
void gxepage_previewarea_draw(GtkWidget *Ppwidget,cairo_t *Pcr)    //~var8R~
{                                                                  //~var8R~
//*************************                                        //~var8R~
	if (!SppixmappreviewWidget)                                    //~var8R~
    	return;                                                    //~var8R~
//	dprintf("gxepage_previewarea_draw, scalex=%f,scaley=%f\n",Sscalex,Sscaley);//~var8R~
//  cairo_scale(Pcr,Sscalex,Sscaley);                              //~var8R~
	csub_draw_pixmap_to_screen(Pcr,SppixmappreviewWidget);         //~var8R~
}//drawpreviewcanvas                                               //~var8R~
#endif      //OPTGTK3                                              //~var8R~
//**************************************************************** //~vXXEI~
//*!!!not used,CALLBACK is not defined on interface.c              //~vam8I~
//**************************************************************** //~vam8I~
void gxepage_OnChangeEditCurpage(void)                             //~vXXER~
{
//****************************                                     //~2C14I~
//	Mcurpage=atoi((Meditcurpage.GetWindowText(txt,sizeof(txt)-1),txt));//~vXXER~
	GET_SPINBUTTON(Sprintdlg,STRIDC_SPIN_CURPAGE,Mcurpage);        //~vXXER~
    UTRACEP("gxepage_OnChangeEditCurpage Mcurpage=%d\n",Mcurpage); //~vam8I~
    return;                                                        //~vXXEI~
}
void gxepage_fontstyle(void)                                       //~vXXER~
{                                                                  //~v62WM~
//****************************                                     //~v62WM~
	 dprintf("gxedlg print fontstyle\n");                           //~v667R~
	gxedlg_font_create_sub(1,Sprintdlg);                           //~v62WR~
	return;                                                        //~v62WM~
}                                                                  //~v62WM~
int chkpagerange(char *Pptext)                                     //~vXXEI~
{                                                                  //~vXXEI~
    char *pc;                                                      //~vXXEI~
    int spage,epage=0,reslen,len,endch=0,num;                      //~v667R~
//****************************                                     //~vXXEI~
	 dprintf("pagerange text=%s\n",Pptext);                         //~v667R~
    Mpagerangeno=0;                                                //~vXXEI~
    pc=Pptext+strspn(Pptext," ");                                  //~vXXER~
    reslen=strlen(pc);                                             //~vXXEM~
    if (!reslen)                                                   //~v667I~
    	return 0;                                                  //~v667I~
    if (reslen>=3 && !memicmp(pc,"ALL",3))                         //~vXXER~
    	return 0;				//print all page                   //~vXXEI~
    for (;reslen>0;)                                               //~vXXEI~
    {                                                              //~vXXEI~
    	num=atoi(pc);                                              //~vXXEI~
        if (num<=0)                                                //~vXXEI~
            break;  //not num                                      //~vXXEI~
        spage=num;                                                 //~vXXEI~
        len=unumlen(pc,0,reslen);                                  //~vXXEI~
        pc+=len;                                                   //~vXXEI~
        reslen-=len;                                               //~vXXEI~
        endch=*pc;                                                 //~vXXEI~
        if (endch==','||endch==' '||!endch)	//1 page               //~vXXEI~
			epage=num;                                             //~vXXEI~
        else                                                       //~vXXEI~
        if (*pc=='-')                                              //~vXXEI~
        {	                                                       //~vXXEI~
            pc++;                                                  //~vXXEI~
            reslen--;                                              //~vXXEI~
            endch=*pc;                                             //~vXXEI~
        	if (endch==','||endch==' '||!endch)	//TEXT END         //~vXXEI~
            	epage=0;		//to end of page                   //~vXXEI~
            else                                                   //~vXXEI~
            {                                                      //~vXXEI~
                num=atoi(pc);                                      //~vXXEI~
                if (num<=0)                                        //~vXXEI~
                    break;  //not num                              //~vXXEI~
                epage=num;                                         //~vXXEI~
                len=unumlen(pc,0,reslen);                          //~vXXEI~
                pc+=len;                                           //~vXXEI~
                reslen-=len;                                       //~vXXEI~
	            endch=*pc;                                         //~vXXEI~
			}                                                      //~vXXEI~
		}//range                                                   //~vXXEI~
        if (Mpagerangeno+2>MAXPAGERANGE)                           //~vXXEI~
        	break;                                                 //~vXXEI~
		Mpagerange[Mpagerangeno++]=spage;                          //~vXXER~
		Mpagerange[Mpagerangeno++]=epage;                          //~vXXER~
        dprintf("range %d %d-->%d endch=(%c)\n",Mpagerangeno/2,spage,epage,endch);//~v667R~
        if (endch!=',')                                            //~vXXEI~
        	break;                                                 //~vXXEI~
        pc++;                                                      //~vXXEI~
        reslen--;                                                  //~vXXEI~
    }                                                              //~vXXEI~
    if (endch && endch!=' ')                                       //~vXXER~
    {                                                              //~vXXEI~
    	uerrmsgbox("page range format err.(%s)",0,                 //~vXXER~
                    Pptext);                                       //~vXXEI~
        return 4;                                                  //~vXXEI~
    }                                                              //~vXXEI~
	return 0;                                                      //~vXXEI~
}                                                                  //~vXXEI~
//**********************************************                   //~va6yI~
//*EventHandler Printer combbox-entry changed                      //~va6yI~
//**********************************************                   //~va6yI~
#ifndef NOPRINT                                                    //~vam0I~
#ifndef OPTGTK3                                                    //~var8R~
void gxepage_OnChanged_ComboPrinter(GtkEditable *editable,gpointer user_data)//~va6yI~
#else   //OPTGTK3                                                  //~var8R~
void gxepage_OnChanged_ComboPrinter(GtkComboBox *Ppcombo,gpointer user_data)//~var8R~
#endif                                                             //~var8R~
{                                                                  //~va6yI~
//***********************                                          //~va6yI~
	dprintf("changed event combo printer\n");                      //~va6yI~
    if (!Sinitdlg)	//ignore initial setting                       //~va6yI~
    	return;                                                    //~va6yI~
	gxepage_updateformlist();                                      //~va6yI~
	dprintf("changed event combo printer updated\n");              //~va6yI~
    return;                                                        //~va6yI~
}//gxepage_OnChanged_ComboPrinter                                  //~va6yI~
#else                                                              //~vam0I~
#ifndef OPTGTK3                                                    //~var8R~
void gxepage_OnChanged_ComboPrinter(GtkEditable *editable,gpointer user_data)//~vam0I~
#else   //OPTGTK3                                                  //~var8R~
void gxepage_OnChanged_ComboPrinter(GtkComboBox *Ppcombo,gpointer user_data)//~var8R~
#endif                                                             //~var8R~
{                                                                  //~vam0I~
//from callback,signal never occurs                                //~vam0I~
}                                                                  //~vam0I~
#endif //!NOGOMEPRINT                                              //~vam0I~
                                                                   //~vam0I~
#ifdef GTKPRINT                                                    //~vam0I~
//*****************************************************************//~vam0I~
int gxepage_err_nocupsprinter(void)                                //~vam0I~
{                                                                  //~vam0I~
//  uerrmsgbox("No CUPS printer defined",0);                       //~var4R~
    umsgbox_modalinparent(Sprintdlg,"No CUPS printer defined",GTK_BUTTONS_CLOSE);//~var4R~
    return 4;                                                      //~vam0I~
}                                                                  //~vam0I~
#endif                                                             //~vam0I~
//*****************************************************************//~vam8I~
void displayHWMargin(char *Pform)                                  //~vam8R~
{                                                                  //~vam8I~
    char defmarginwk[64];                                          //~vam8I~
    RECT rect;                                                     //~vam8I~
//**************************************                           //~vam8I~
//  csubgetcupspagesz(0,&rect,Pform);                              //~vam7R~
//  csubgetcupspagesz(0,&rect,Pform,NULL);;                        //~vam7I~//~vampR~
    csubgetcupspagesz(0,&rect,Pform);                              //~vampI~
    sprintf(defmarginwk,"HWMargins:L=%d,R=%d,T=%d,B=%d",rect.left,rect.right,rect.top,rect.bottom);//~vam8I~
	SET_LABELTEXT(Sprintdlg,STRIDC_LABEL_DEFMARGIN,defmarginwk);   //~vam8I~
}                                                                  //~vam8I~
#ifndef NOPRINT                                                    //~vap1I~
//*****************************************************************//~vam8I~
#ifndef OPTGTK3                                                    //~var8R~
void gxepage_OnChanged_ComboForm(GtkEditable *editable,gpointer user_data)//~vam8I~
#else   //OPTGTK3                                                  //~var8R~
void gxepage_OnChanged_ComboForm(GtkComboBox *Ppcombo,gpointer user_data)//~var8R~
#endif //!NOPRINT                                                  //~var8R~
{                                                                  //~vam8I~
	char form[sizeof(Mformtype)];                                  //~vam8I~
//***********************                                          //~vam8I~
	UTRACEP("changed event combo form\n");                         //~vam8R~
    if (!Sinitdlg)	//ignore initial setting                       //~vam8I~
    	return;                                                    //~vam8I~
#ifndef OPTGTK3                                                    //~var8R~
    GET_ENTRYTEXT(Sprintdlg,STRIDC_COMBOENTRY_FORM,form);          //~vam8I~
#else   //OPTGTK3                                                  //~var8R~
	gxepage_combo_get_active(Sprintdlg,Sglcombopaper,STRIDC_COMBO_FORM,form);//~var8R~
#endif                                                             //~var8R~
	UTRACEP("changed event combo selected form=%s\n",form);        //~vam8R~
    strcpy(Mformtype,form);                                        //~vam8R~
	displayHWMargin(form);//update formlist                        //~vam8R~
    return;                                                        //~vam8I~
}//gxepage_OnChanged_ComboPrinter                                  //~vam8I~
#endif //!NOPRINT                                                  //~vap1I~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
//*****************************************************************//~var8R~
int gxepage_combo_get_active(GtkWidget *Ppdlg,GList *Ppglist,char *Pplookupid,char *Ppactivetext)//~var8R~
{                                                                  //~var8R~
   	int active,ii;                                                 //~var8R~
    GtkWidget *pcombo;                                             //~var8R~
    GList *gl;                                                     //~var8R~
    char *pentry;                                                  //~var8R~
//*********************                                            //~var8R~
	if (Snoprinter)                                                //~var8R~
    	return -2;                                                 //~var8R~
    pcombo=lookup_widget(GTK_WIDGET(Ppdlg),Pplookupid);            //~var8R~
	active=gtk_combo_box_get_active(GTK_COMBO_BOX(pcombo));        //~var8R~
    UTRACEP("%s:active index=%d,lookupid=%s\n",UTT,active,Pplookupid);                    //~vb7sR~//~vbi8R~
    if (active==-1)                                                //~var8R~
    	return -1;                                                 //~var8R~
  	for (ii=0,gl=Ppglist;gl;ii++,gl=gl->next)                      //~var8R~
  	{                                                              //~var8R~
        pentry=(char*)gl->data;                                    //~var8R~
        dprintf("getactive ii=%d=%s\n",ii,pentry);                 //~var8R~
        UTRACEP("%s:getactive ii=%d=%s\n",UTT,ii,pentry);          //~vb7sI~
    	if (ii==active)                                            //~var8R~
        {                                                          //~var8R~
		    strcpy(Ppactivetext,pentry);                           //~var8R~
	        UTRACEP("%s:active entry=%s\n",UTT,pentry);            //~vb7sI~
        	break;                                                 //~var8R~
        }                                                          //~var8R~
    }                                                              //~var8R~
    if (!gl)                                                       //~var8R~
    	return -1;                                                 //~var8R~
    return 0;                                                      //~var8R~
}//gxepage_combo_get_active                                        //~var8R~
#endif                                                             //~var8R~
