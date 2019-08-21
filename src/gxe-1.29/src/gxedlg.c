//*CID://+vbdaR~:                             update#=  376;       //+vbdaR~
//***************************************************************************//~vXXEI~
// gxedlg.c                                                        //~vXXEI~
//***************************************************************************//~vXXEI~
//vbda:171121*(gxe)display GTK3/GTK2 on titlemsg/about dialog      //+vbdaI~
//vb7s:170128 (gxe:bug)avoid "Gtk-Message:GtkDialog mapped without a transient parent."//~vb7sI~
//vb7t:170128 (gxe)Gtk3 deprecated
//var8:140127 gtk3 suppott                                         //~var8I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//vaa7:111117 (gcc4.6)Warning:unused-but-set                       //~vaa7I~
//va20:091125 (UTF8)UTF8 full support(display utf8 also unprintable as locale code)//~va20I~
//            add ff to sample string for ligature chk             //~va20I~
//va1M:091121 (LNX)ligature support;keep monospace for english lagature; Arabian ? I don't know.//~va1MI~
//v77t:080111*(XXE:BUG)font selection setting fail.                //~v77tI~
//            (gtk_fontselection_set_font_name serach by familyname by pango_font\description_get_family)//~v77tI~
//            (but pango returns family+style the search fail.pass fontname without style to gtk)//~v77tI~
//            ("," means end of familyname. Yet style positionning.)//~v77tI~
//v77r:080110*(XXE:BUG) restore freed area(fontname) when dialoc end by cancel//~v77rI~
//v75X:070526 (XXE:BUG)assertion fail face!=NULL, gnome_font_find  //~v75xI~
//v740:070201 (WXE/XXE)kde dose not report keypress event for S+C+F1;so use keyup event//~v740I~
//            so support specify trigger key on setupdialog        //~v740I~
//v73y:070128-(WXE/XXE)Quiet-exit support                          //~v73yI~
//v73t:070125 cross-hair ruler support by Shift+Ctl+lbuton         //~v73tI~
//v69q:060530 (XXE:fc5)font\description in pango_context is freed each time//~v69qI~
//            when pango_context_set_file_description is called. under fc5 it is called many times.//~v69qI~
//            Then abend when Setup menue selected.                //~v69qI~
//            If xeg.ini remained font_description is not from pango_context but newly created,//~v69qI~
//            So ,no abend occures.                                //~v69qI~
//v696:060427 (XXE) drop japanese from font sample text if english mode//~v696I~
//v664:050817 (XXE:BUG)pagecount unmatch between preview and print because cellh/w parm is different.//~v664I~
//vX01:050729 cellh/cellw=0 mean same as fonth/fontw               //~vX01I~
//vXXE:050611 new for XXE                                          //~vXXEI~
//v55G:040315 (WXE)Beep option on setup dialog                     //~vXXEM~
//v55F:040314 (WXE)english help                                    //~vXXEM~
//v55D:040309 (WXE)popup help for dialog control                   //~vXXEM~
//v55q:040228 option to scroll by csr move(CSRSCROLL option)       //~vXXEM~
//v55c:040208 (WXE)distingush L-CTL/R-CTL & report R-CTL           //~vXXEM~
//v510:030215 (WXE)parameterize interval for scroll by mouse       //~vXXEM~
//030102:other carset support                                      //~vXXEM~
//***************************************************************************//~vXXEI~
#include <stdlib.h>                                                //~v740I~
#include <string.h>                                                //~v740I~
#include <ctype.h>                                                 //~v740I~
                                                                   //~vXXEI~
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
                                                                   //~vXXEI~
#include "callbacks.h"                                             //~vXXEI~
#include "interface.h"                                             //~vXXEI~
#include "support.h"                                               //~vXXEI~
                                                                   //~vXXEI~
#include "ulib.h"                                                  //~vXXEI~
#include "utrace.h"                                                //~vam0I~
#include "gxe.h"                                                   //~vXXEI~
#include "gxedlg.h"                                                //~vXXEI~
#include "gxeview.h"                                               //~vXXEI~
#include "xxedef.h"                                                //~vXXEI~
#include "xxemain.h"                                               //~vXXEI~
#include "xxeres.h"                                                //~vXXEI~
#include "xxexei.h"                                                //~vXXEI~
#include "xxecsub.h"                                               //~vXXEI~
#include "gxepage.h"                                               //~vXXEI~
                                                                   //~vXXEI~
//***************************************************************************//~vXXEI~
//#deefine FONT_SAMPLE_TEXT "abcdefghijk ABCDEFGHIJK 色は匂へと" //utf8//~vXXEI~//~va20R~
#define FONT_SAMPLE_TEXT "abcdefffighijk ABCDEFGHIJK 色は匂へと" //utf8//~va20R~
//#define FONT_SAMPLE_TEXTE "abcdefghijk ABCDEFGHIJK 1234567890" //utf8//~v696R~//~va20R~
#define FONT_SAMPLE_TEXTE "abcdefffighijk ABCDEFGHIJK 1234567890" //utf8//~va20R~
//***************************************************************************//~vXXEI~
static    GtkWidget *Sfontdlg,*Scolordlg,*Saboutdlg,*Soptiondlg;   //~vXXER~
static    GtkWidget *Soptiondlg_colorsample;                       //~vXXEI~
static    int       Sfontsorp=0;                                   //~vXXEI~
static    gchar    *Sfontsampletext=FONT_SAMPLE_TEXT;              //~vXXEI~
static    gchar    *Sfontsampletexte=FONT_SAMPLE_TEXTE;            //~v696I~
static 	  GdkPixmap *Spmcolorsample=NULL;                          //~vXXEI~
static 	  FONTDATA  Ssvfontdata0;	//save for canceled case       //~vXXEI~
static 	  COLORDATA Ssvcolordata;                                  //~vXXEI~
static 	  GdkColor  Srulergdkcolor;                                //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
static 	  GdkGC *Spgccolorsample=NULL;	//gc for Spmcolorsample(caito_t * for cairo_surface_t*)//~var8R~
#endif                                                             //~var8R~
//***************************************************************************//~vXXEI~
int gxedlg_getcolordata(GtkWidget *Ppcolordlg);                    //~vXXEI~
void gxe_option_draw_sampletext(GdkPixmap *Pppixmap,GdkGC *Ppgc,PangoLayout *Pplayout,//~vXXEI~
								GdkColormap *Ppcm,GdkColor *Ppcolor,//~vXXEI~
								char *Pptext,int Pxx,int Pyy);     //~vXXEI~
void gxedlg_option_draw_samplebox(void);                           //~vXXEI~
int gxedlg_setcolor(int Popt,XXECOLOR *Ppcolor);                   //~vXXEI~
int gxedlg_setrulercolor(int Popt);                                //~v73tI~
int gxedlg_setrulerkey(int Popt);                                  //~v740I~
int gxedlg_getrulercolordata(GtkWidget *Ppcolordlg);               //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
	void gxedlg_color_chooser_set_rgba(GtkColorChooserDialog *Pdlg,GdkColor *Pcolor);//~var8R~
	void gxedlg_color_chooser_get_rgba(GtkColorChooserDialog *Pdlg,GdkColor *Ppcolor);//~var8R~
	void gxedlg_font_chooser_set_font_name(GtkFontChooserDialog *Ppdlg,char *Pfontname);//~var8R~
#endif                                                             //~var8R~
//==========================================================       //~vXXEI~
//int CALLBACK effp(LOGFONT *Pelf,TEXTMETRIC *Pntm,DWORD Pft,LPARAM Plp);//~2817R~
//int (CALLBACK *effp)(const LOGFONT *Pelf,const TEXTMETRIC *Pntm,DWORD Pft,LPARAM Plp);//~2817R~
//	FONTENUMPROC effp;                                             //~2817R~
/////////////////////////////////////////////////////////////////////////////

//CWxedlg::CWxedlg(CWnd* pParent,CWxemain *Ppwxemain)              //~vXXER~
//    : CDialog(CWxedlg::IDD, pParent)                             //~vXXER~
void gxedlg_construct(void)                                        //~vXXER~
{
	Mrctl   = wxe_getrctl();                                       //~v55cR~
	Mfreecsr= wxe_getfreecsr();                                    //~v55qR~
	Mbeep = wxe_getbeep();                                         //~v55GI~
	return;                                                        //~vXXEI~
}
//***************************************************************************//~vXXEM~
// static init<--xxemain_init<--gxeview_init<--gxeview_realize     //~vXXER~
//***************************************************************************//~vXXEM~
void gxedlg_init(void)                                             //~vXXEM~
{                                                                  //~vXXEM~
	gchar *gstr;                                                   //~vXXEM~
//*****************                                                //~vXXEM~
  if (!*Mfontstyle)	//after ini deleted                            //~vXXEI~
  {                                                                //~vXXEI~
		Gfontdata[0].FDfontdesc=pango_context_get_font_description(Gppangocontext);//~vXXEI~
    	gstr=pango_font_description_to_string((const PangoFontDescription*)(Gfontdata[0].FDfontdesc));//~vXXEI~
        strcpy(Mfontstyle,gstr);                                   //~vXXEI~
		Gfontdata[0].FDfontname=gstr;	//scr fontname from default or ini file//~vXXEI~
		Gfontdata[0].FDfontdesc=pango_font_description_from_string(gstr);//desc of context may freed,so allocate new//~v69qI~
  }                                                                //~vXXEI~
  else                                                             //~vXXEI~
  {                                                                //~vXXEI~
    gstr=g_new(gchar,strlen(Mfontstyle)+1);                        //~vXXEM~
	strcpy(gstr,Mfontstyle);                                       //~vXXEM~
	Gfontdata[0].FDfontname=gstr;	//scr fontname from default or ini file//~vXXEM~
	Gfontdata[0].FDfontdesc=pango_font_description_from_string(gstr);//~vXXEM~
    dprintf("gxedlg_init fontdesc=%p,name=%s\n",Gfontdata[0].FDfontdesc,gstr);//~v75XI~
  }                                                                //~vXXEI~
    xxemain_createfont();                                          //~vX01M~
    dprintf("after createfont h=%d-->%d,w=%d->%d\n",Mcellh0,Mcellh,Mcellw0,Mcellw);//~v664R~
    gxedlg_setcolor(1,&Mbgcolor);	//Mbgcolr->COLORDATA           //~vXXEM~
    gxedlg_setrulercolor(1);	//Grulerfg->Srulergdkcolor         //~v73tM~
	return;                                                        //~vXXEM~
}//gxedlg_init                                                     //~vXXEM~
//void CWxedlg::DoDataExchange(CDataExchange* pDX)                 //~vXXER~
//***************************************************************************//~vXXEI~
//* init chkbox,spinbutton                                         //~vXXEI~
//***************************************************************************//~vXXEI~
void gxedlg_setvalue(void)                                         //~vXXEI~
{
	int qexit;                                                     //~v73yI~
//******************************                                   //~vXXEI~
	SET_ENTRYINT(Soptiondlg,STRIDC_EDIT_HEIGHT,Mfontheight);	//set at createfont//~vXXER~
	SET_ENTRYINT(Soptiondlg,STRIDC_EDIT_WIDTH,Mfontwidth);         //~vXXER~
	SET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_COLW,Mcellw0);           //~vX01R~
	SET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_ROWH,Mcellh0);           //~vX01R~
	SET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_SCROLLCTR,Mscrollctr);   //~vXXER~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_USEACT,Museact);            //~vXXEI~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_USEMK,Musemk);              //~vXXEI~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_LIGATURE,Mligature);        //~va1MI~
	SET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_SCROLLTIMER,Mscrolltimer);//~vXXER~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_RCTL,Mrctl);                //~vXXEI~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_FREECSR,Mfreecsr);          //~vXXEI~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_BEEP,Mbeep);                //~vXXEI~
    qexit=(Gwxestat & GWXES_OPT_QEXIT)!=0;                         //~v73yI~
	SET_CHKBOX(Soptiondlg,STRIDC_CHECK_QEXIT,qexit);               //~v73yI~
	SET_ENTRYTEXT(Soptiondlg,STRIDC_ENTRY_FONTNAME,Mfontstyle);    //~vXXER~
                                                                   //~vXXEI~
//  SET_SENSITIVE(Soptiondlg,STRIDC_ENTRY_FONTNAME,FALSE);         //~vXXER~
    SET_SENSITIVE(Soptiondlg,STRIDC_EDIT_HEIGHT,FALSE);            //~vXXER~
    SET_SENSITIVE(Soptiondlg,STRIDC_EDIT_WIDTH,FALSE);             //~vXXER~
    dprintf("setvalue fw=%d,fh=%d,fname=%s\n",Mfontwidth,Mfontheight,Mfontstyle);//~v664R~
    gxedlg_setrulerkey(1);                                         //~v740M~
}
/////////////////////////////////////////////////////////////////////////////

//void CWxedlg::OnOK()                                             //~vXXER~
void gxedlg_option_OnOK      				(GtkButton       *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{
    int qexit;                                                     //~v73yI~
//**********************                                           //~2817M~
	UTRACEP("gxedlg option onok \n");                             //~v664R~//~vam0R~
    GET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_COLW,Mcellw0);           //~vX01R~
    GET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_ROWH,Mcellh0);           //~vX01R~
    gxedlg_setcolor(0,&Mbgcolor);	//save from gbl                //~vXXEM~
    gxedlg_setrulercolor(0);	//Mrulercolor->Srulergdkcolor      //~v73tI~
    if (gxedlg_setrulerkey(0))                                     //~v740I~
    	return ;                                                   //~v740R~
//    strncpy(Mpwxemain->Mfontstyle,Mfontstyle,sizeof(Mpwxemain->Mfontstyle));//~vXXER~
	strcpy(Mfontstyle,Gfontdata[0].FDfontname);	//for ini save     //~vXXEM~
//accelerator                                                      //~3103I~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_USEACT,Museact);            //~vXXER~
//menukey usage                                                    //~3105I~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_USEMK,Musemk);              //~vXXER~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_LIGATURE,Mligature);        //~va1MI~
//rctl key useage                                                  //~v55cI~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_RCTL,Mrctl);                //~vXXER~
//freecsr mode                                                     //~v55qR~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_FREECSR,Mfreecsr);          //~vXXER~
//beep  mode                                                       //~vXXER~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_BEEP,Mbeep);                //~vXXER~
    GET_CHKBOX(Soptiondlg,STRIDC_CHECK_QEXIT,qexit);               //~v73yI~
    if (qexit)                                                     //~v73yI~
    	Gwxestat|=GWXES_OPT_QEXIT;                                 //~v73yI~
    else                                                           //~v73yI~
    	Gwxestat&=~GWXES_OPT_QEXIT;                                //~v73yI~
                                                                   //~3103I~
    GET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_SCROLLCTR,Mscrollctr);   //~vXXER~
    GET_SPINBUTTON(Soptiondlg,STRIDC_SPIN_SCROLLTIMER,Mscrolltimer);//~vXXER~
                                                                   //~2915I~
                                                                   //~2915I~
    gtk_widget_destroy(Soptiondlg);                                //~vXXEM~
	xxemain_createfont();                                          //~vXXEM~
    xxemain_scrbgrect();                                           //~vXXEM~
	xxemain_scrinvalidate(1);                                      //~vXXEM~
    UTRACEP("optiondlg on ok:rowh=%d,colw=%d,scrollctr=%d,scroll-interval=%d\n",//~v664R~//~vam0R~
    	Mcellh,Mcellw,Mscrollctr,Mscrolltimer);                    //~vXXER~
    dprintf("   acc=%d,menukey=%d,rctl=%d,freecsr=%d,beep=%d\n",   //~v664R~
    	Museact,Musemk,Mrctl,Mfreecsr,Mbeep);                      //~vXXEI~
	xxemain_OnOk();                                                //~vX01M~
	return;                                                        //~vXXEM~
}//gxedlg_option_OnOK                                              //~v73tR~
                                                                   //~vXXEM~
///////////////////////////////////////////////////////////////////////////////~vXXEI~
void gxedlg_option_OnCancel  				(GtkButton       *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{
//****************************                                     //~vXXEM~
	 dprintf("gxedlg option cancel\n");                            //~var8R~
	memcpy(&Gfontdata[0],&Ssvfontdata0,FONTDATASZ);                //~vXXEM~
    if (memcmp(&Gcolordata,&Ssvcolordata,COLORDATASZ))             //~vXXEM~
		memcpy(&Gcolordata,&Ssvcolordata,COLORDATASZ);             //~vXXEM~
    gtk_widget_destroy(Soptiondlg);                                //~vXXEM~
	xxemain_createfont();                                          //~vXXEM~
    xxemain_scrbgrect();                                           //~vXXEM~
	xxemain_scrinvalidate(1);                                      //~vXXEM~
	return;                                                        //~vXXEM~
}//gxedlg_option_OnCancel                                          //~var8R~

//***************************************************************************//~vXXEM~
// Options  <--gxeview_OnOptions<--on_setup_activate               //~vXXER~
//***************************************************************************//~vXXEM~
void gxedlg_option_create 				(GtkMenuItem     *Pmenuitem,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//#ifndef OPTGTK3 //var8 test also on gtk2 FIXME                   //~vb7sR~
  	GtkWidget *framewindow;                                        //~vXXEM~
//#else   //OPTGTK3                                                //~vb7sR~
//#endif                                                           //~vb7sR~
//****************************                                     //~vXXEM~
	 dprintf("on_option_activate  \n");                             //~v664R~
//#ifndef OPTGTK3 //var8test also on gtk2 FIXME                    //~vb7sR~
  	framewindow = lookup_widget (GTK_WIDGET (Pmenuitem), "framewindow");//~vXXEM~
//#else   //OPTGTK3                                                //~vb7sR~
//#endif                                                           //~vb7sR~
    Soptiondlg= create_optiondlg();                                //~vXXEM~
    /* Make sure the dialog doesn't disappear behind the main window. *///~vXXEM~
//#ifndef OPTGTK3 //var8test also on gtk2 FIXME                    //~vb7sR~
    gtk_window_set_transient_for (GTK_WINDOW (Soptiondlg),         //~vXXEM~
				    GTK_WINDOW (framewindow));                     //~vXXEM~
//#else   //OPTGTK3                                                //~vb7sR~
//#endif                                                           //~vb7sR~
    Soptiondlg_colorsample=lookup_widget(GTK_WIDGET (Soptiondlg),STRIDC_STATIC_COLORBOX);//~vXXER~
//#ifndef OPTGTK3                                                  //~var8R~
  	gtk_widget_show (Soptiondlg);                                  //~vXXEM~
//#else   //OPTGTK3                                                //~var8R~
//#endif                                                           //~var8R~
                                                                   //~vXXEM~
                                                                   //~var8R~
  	/* We make sure the dialog is visible. */                      //~vXXEM~
  	gtk_window_present (GTK_WINDOW (Soptiondlg));                  //~vXXEM~
	memcpy(&Ssvfontdata0,&Gfontdata[0],FONTDATASZ);                //~vXXEM~
	memcpy(&Ssvcolordata,&Gcolordata,COLORDATASZ);                 //~vXXEM~
	gxedlg_construct();                                            //~vXXEI~
	gxedlg_setvalue();                                             //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
    gtk_dialog_run(GTK_DIALOG(Soptiondlg));                        //~var8R~
#endif                                                             //~var8R~
    return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//******************************************************           //~vXXEM~
//* display font data on parent dialog                             //~vXXEM~
//******************************************************           //~vXXEM~
int gxedlg_settext_fontname(int Pprintid,GtkWidget *Pparent)       //~vXXEM~
{                                                                  //~vXXEM~
    PFONTDATA pfd;                                                 //~vXXEM~
#ifndef NOPRINT                                                    //~vam0I~
	#ifdef GTKPRINT                                                //~vam0I~
    gchar     *pfontname;                                          //~vam0I~
    #else                                                          //~vam0I~
    gchar     *pfontname,*pfullname;                               //~vam0I~
    #endif                                                         //~vam0I~
#else                                                              //~vam0I~
    gchar     *pfontname;                               //~vXXER~  //~vam0R~
#endif                                                             //~vam0I~
    int rc=0,fszh,fszw;                                            //~vXXER~
//  GnomeFont *pgfont;                                             //~vXXEI~//~vaa7R~
#ifndef NOPRINT                                                    //~vam0I~
	#ifdef GTKPRINT                                                //~vam0I~
    #else                                                          //~vam0I~
    char outfontname[256];                                         //~v75XI~
    #endif                                                         //~vam0I~
#endif                                                             //~vam0I~
//************************************                             //~vXXEM~
    pfd=Gfontdata+Pprintid;                                        //~vXXEM~
	if (pfontname=pfd->FDfontname,pfontname)                       //~vXXEM~
    {                                                              //~vXXEM~
    	if (Pprintid)                                              //~vXXEM~
        {                                                          //~vXXEI~
#ifndef NOPRINT                                                    //~vam0I~
	#ifdef GTKPRINT                                                //~vam0I~
			ugetfontmetrics(pfd->FDfontdesc,&fszw,&fszh,0);//0:no mospace chk//~vam0I~
	#else    //!GTKPRINT                                           //~vam0I~
        	fszw=0;fszh=0;                                         //~vXXEI~
//  		pgfont=uprtcreatefont(pfontname,&fszw,&fszh);          //~v75XR~
    		/*pgfont=*/uprtcreatefont(pfontname,&fszw,&fszh,outfontname);//~v75XI~//~vaa7R~
//          pfullname=gnome_font_get_full_name(pgfont);            //~v75XR~
            if (*outfontname)                                      //~v75XI~
            {                                                      //~v75XI~
//              g_free(pfontname);  //free old                     //~v77rR~
            	pfullname=g_new(gchar,strlen(outfontname)+1);      //~v75XR~
                strcpy(pfullname,outfontname);                     //~v75XI~
            }                                                      //~v75XI~
            else                                                   //~v75XI~
            	pfullname=pfontname;                               //~v75XI~
dprintf("fontname %s-->%s fullname\n",pfontname,pfullname);        //~v664R~
            pfd->FDfontname=pfontname=pfullname;                   //~vXXEI~
	#endif   //!GTKPRINT                                           //~vam0M~
			SET_ENTRYTEXT(Pparent,STRIDC_ENTRY_PFONTNAME,pfontname);//~vXXER~
			SET_ENTRYINT(Pparent,STRIDC_EDIT_PFONTSZH,fszh);       //~vXXER~
			SET_ENTRYINT(Pparent,STRIDC_EDIT_PFONTSZW,fszw);       //~vXXER~
            Mpfontszh=fszh;	//for preview pagecount calc           //~v664I~
            Mpfontszw=fszw;                                        //~v664I~
#else       //NOPRINT                                              //~vam0I~
			;                                                      //~vam0I~
#endif                                                             //~vam0I~
        }                                                          //~vXXEI~
    	else                                                       //~vXXEM~
        {                                                          //~vXXEI~
			ugetfontmetrics(pfd->FDfontdesc,&fszw,&fszh,0);//0:no mospace chk//~vXXER~
			SET_ENTRYTEXT(Pparent,STRIDC_ENTRY_FONTNAME,pfontname);//~vXXER~
			SET_ENTRYINT(Pparent,STRIDC_EDIT_HEIGHT,fszh);         //~vXXER~
			SET_ENTRYINT(Pparent,STRIDC_EDIT_WIDTH,fszw);          //~vXXER~
        }                                                          //~vXXEI~
        rc=1;                                                      //~vXXER~
    dprintf("setvalue fw=%d,fh=%d,fname=%s\n",fszh,fszw,pfontname);//~v664R~
    }                                                              //~vXXEM~
    return rc;                                                     //~vXXEM~
}//gxedlg_settext_fontname                                         //~vXXEM~
//***************************************************************************//~vXXEM~
// Color                                                           //~vXXEM~
//***************************************************************************//~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
//***************************************************************************//~var8R~
int gxedlg_chk_colordlg_resonse()                                  //~var8R~
{                                                                  //~var8R~
	int rc;                                                        //~var8R~
//***********************                                          //~var8R~
    rc=gtk_dialog_run(GTK_DIALOG(Scolordlg));                      //~var8R~
    dprintf("response_colorselectiondialog responseid=%d\n",rc);   //~var8R~
	if (rc==GTK_RESPONSE_OK) //-5                                  //~var8R~
    {                                                              //~var8R~
		gxedlg_Color_OnOK(NULL/*button*/,NULL/*user_data*/);       //~var8R~
    }                                                              //~var8R~
	if (rc==GTK_RESPONSE_CANCEL)//-6                               //~var8R~
    {                                                              //~var8R~
		gxedlg_Color_OnCancel(NULL/*button*/,NULL/*user_data*/);   //~var8R~
    }                                                              //~var8R~
    return rc;                                                     //~var8R~
}//gxedlg_colordlg_resonse                                         //~var8R~
#endif                                                             //~var8R~
//***************************************************************************//~var8R~
void gxedlg_option_color_create 				(GtkButton    *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
  	GtkWidget *framewindow;                                        //~vXXEM~
  	GtkWidget *helpbutton;                                         //~vXXEM~
#else                                                              //~var8R~
#endif                                                             //~var8R~
//****************************                                     //~vXXEM~
	 dprintf("on_color_activate  \n");                              //~v664R~
#ifndef OPTGTK3                                                    //~var8R~
  	framewindow = Gpframe;                                         //~vXXEM~
    Scolordlg = create_colorselectiondialog ();                    //~vXXEM~
#else                                                              //~var8R~
    Scolordlg = create_colorselectiondialog(Soptiondlg);           //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_object_set_user_data (GTK_OBJECT (Scolordlg),0);	//0:id of BG color change//~v73tI~
#else                                                              //~var8R~
    g_object_set_data (G_OBJECT (Scolordlg),"user_data",0); //0:id of BG color change//~var8R~
#endif                                                             //~var8R~
//  gtk_object_set_data (GTK_OBJECT (Scolordlg), FRAME_WINDOW_KEY, framewindow);//~vXXER~
                                                                   //~vXXEM~
      /* Make sure the dialog doesn't disappear behind the main window. *///~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Scolordlg),          //~vXXEM~
				    GTK_WINDOW (framewindow));                     //~vXXEM~
#else   //OPTGTK3                                                  //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Scolordlg),          //~var8R~
				    GTK_WINDOW (Soptiondlg));                      //~var8R~
#endif                                                             //~var8R~
	if (Gcolordata.CDstatus)                                       //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
	  	gtk_color_selection_set_current_color(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG (Scolordlg)->colorsel),//~vXXEM~
                                   &(Gcolordata.CDcolor));         //~vXXEM~
#else                                                              //~var8R~
		gxedlg_color_chooser_set_rgba(GTK_COLOR_CHOOSER_DIALOG(Scolordlg),//~var8R~
                                   &(Gcolordata.CDcolor));         //~var8R~
#endif                                                             //~var8R~
  	gtk_widget_show (Scolordlg);                                   //~vXXEM~
                                                                   //~vXXEM~
  	/* We make sure the dialog is visible. */                      //~vXXEM~
  	gtk_window_present (GTK_WINDOW (Scolordlg));                   //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
    helpbutton=lookup_widget(Scolordlg,"help_button1");            //~vXXEM~
    gtk_widget_hide(helpbutton);                                   //~vXXEM~
#else                                                              //~var8R~
	gxedlg_chk_colordlg_resonse();                                 //~var8R~
#endif                                                             //~var8R~
    return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//***************************************************************************//~v73tI~
void gxedlg_option_rulercolor_create 				(GtkButton    *Pbutton,//~v73tI~
                                        gpointer         Puser_data)//~v73tI~
{                                                                  //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
  	GtkWidget *framewindow;                                        //~v73tI~
  	GtkWidget *helpbutton;                                         //~v73tI~
#else                                                              //~var8R~
#endif                                                             //~var8R~
//****************************                                     //~v73tI~
	 dprintf("on_rulercolor_activate  \n");                        //~v73tR~
#ifndef OPTGTK3                                                    //~var8R~
  	framewindow = Gpframe;                                         //~v73tI~
    Scolordlg = create_colorselectiondialog ();                    //~v73tI~
#else                                                              //~var8R~
    Scolordlg = create_colorselectiondialog(Soptiondlg);           //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_object_set_user_data (GTK_OBJECT (Scolordlg),(gpointer)1);	//0:id of BG color change//~v73tR~
#else                                                              //~var8R~
    g_object_set_data (G_OBJECT (Scolordlg),"user_data",(gpointer)1); //0:id of BG color change//~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Scolordlg),          //~v73tI~
				    GTK_WINDOW (framewindow));                     //~v73tI~
#else                                                              //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Scolordlg),          //~var8R~
				    GTK_WINDOW (Soptiondlg));                      //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
	gtk_color_selection_set_current_color(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG (Scolordlg)->colorsel),//~v73tI~
                                   &Srulergdkcolor);               //~v73tI~
#else                                                              //~var8R~
	gxedlg_color_chooser_set_rgba(GTK_COLOR_CHOOSER_DIALOG(Scolordlg),//~var8R~
                                   &Srulergdkcolor);               //~var8R~
#endif                                                             //~var8R~
  	gtk_widget_show (Scolordlg);                                   //~v73tI~
  	gtk_window_present (GTK_WINDOW (Scolordlg));                   //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
    helpbutton=lookup_widget(Scolordlg,"help_button1");            //~v73tI~
    gtk_widget_hide(helpbutton);                                   //~v73tI~
#else                                                              //~var8R~
	gxedlg_chk_colordlg_resonse();                                 //~var8R~
#endif                                                             //~var8R~
    return;                                                        //~v73tI~
}                                                                  //~v73tI~
//***************************************************************************//~v73tI~
void gxedlg_Color_OnOK      				(GtkButton       *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
	gpointer puserdata;                                            //~v73tI~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg Color onok mainlevel=%d\n",gtk_main_level());  //~v664R~
#ifndef OPTGTK3                                                    //~var8R~
    puserdata=gtk_object_get_user_data(GTK_OBJECT(Scolordlg));     //~v73tI~
#else                                                              //~var8R~
    puserdata=g_object_get_data(G_OBJECT(Scolordlg),"user_data");  //~var8R~
#endif                                                             //~var8R~
	 dprintf("gxedlg Color onok userdata=%p\n",puserdata);         //~v73tR~
  if (puserdata==NULL)	//bg color                                 //~v73tR~
    gxedlg_getcolordata(Scolordlg);                                //~vXXEM~
  else                                                             //~v73tI~
    gxedlg_getrulercolordata(Scolordlg);                           //~v73tI~
    gtk_widget_destroy(Scolordlg);                                 //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
                                                                   //~vXXEM~
void gxedlg_Color_OnCancel  				(GtkButton       *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg Color cancel\n");                              //~v664R~
    gtk_widget_destroy(Scolordlg);                                 //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//******************************************************           //~vXXEM~
//* get color data from dialog setting                             //~vXXEM~
//******************************************************           //~vXXEM~
int gxedlg_getcolordata(GtkWidget *Ppcolordlg)                     //~vXXEM~
{                                                                  //~vXXEM~
//***********************************:                             //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
  	gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG (Ppcolordlg)->colorsel),//~vXXEM~
                                   &(Gcolordata.CDcolor));         //~vXXEM~
#else                                                              //~var8R~
	gxedlg_color_chooser_get_rgba(GTK_COLOR_CHOOSER_DIALOG(Ppcolordlg),//~var8R~
                                   &(Gcolordata.CDcolor));         //~var8R~
#endif                                                             //~var8R~
    dprintf("color %x=(%x,%x,%x)\n",Gcolordata.CDcolor.pixel,      //~v664R~
                                      Gcolordata.CDcolor.red,      //~vXXEM~
                                      Gcolordata.CDcolor.green,    //~vXXEM~
                                      Gcolordata.CDcolor.blue);    //~vXXEM~
	Gcolordata.CDstatus=CDST_RGB;   //valid color data id          //~vXXEM~
	gxedlg_option_draw_samplebox();                                //~vXXEM~
    return Gcolordata.CDcolor.pixel;                               //~vXXEM~
}//gxedlg_getcolordata                                             //~vXXEM~
//******************************************************           //~v73tI~
//* get color data from dialog setting                             //~v73tI~
//******************************************************           //~v73tI~
int gxedlg_getrulercolordata(GtkWidget *Ppcolordlg)                //~v73tI~
{                                                                  //~v73tI~
//***********************************:                             //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
  	gtk_color_selection_get_current_color(GTK_COLOR_SELECTION(GTK_COLOR_SELECTION_DIALOG (Ppcolordlg)->colorsel),//~v73tI~
                                   &Srulergdkcolor);               //~v73tI~
#else                                                              //~var8R~
	gxedlg_color_chooser_get_rgba(GTK_COLOR_CHOOSER_DIALOG(Ppcolordlg),//~var8R~
                                   &Srulergdkcolor);
#endif                                                             //~var8R~
    dprintf("ruler color %x=(%x,%x,%x)\n",Srulergdkcolor.pixel,    //~v73tI~
                                      Srulergdkcolor.red,          //~v73tR~
                                      Srulergdkcolor.green,        //~v73tR~
                                      Srulergdkcolor.blue);        //~v73tR~
	gxedlg_option_draw_samplebox();                                //~v73tI~
    return Srulergdkcolor.pixel;                                   //~v73tI~
}//gxedlg_getrulercolordata                                        //~v73tI~
//***************************************************************************//~vXXEM~
//color data exchange                                              //~vXXEM~
//p1:operation: 1:XXECOLOR->COLORDATA, 0:COLORDATA->XXECOLOR       //~vXXEM~
//p2:XXECOLOR                                                      //~vXXEM~
//***************************************************************************//~vXXEM~
int gxedlg_setcolor(int Popt,XXECOLOR *Ppcolor)                    //~vXXEM~
{                                                                  //~vXXEM~
    if (Popt)		//gbl init                                     //~vXXER~
    {                                                              //~vXXEM~
    	Gcolordata.CDstatus=CDST_RGB;                              //~vXXEM~
    	Gcolordata.CDcolor.red=Ppcolor->red;                       //~vXXEM~
    	Gcolordata.CDcolor.green=Ppcolor->green;                   //~vXXEM~
    	Gcolordata.CDcolor.blue=Ppcolor->blue;                     //~vXXEM~
    }                                                              //~vXXEM~
    else             //set to Mbgcolor to save to inifile          //~vXXER~
    {                                                              //~vXXEM~
    	Ppcolor->red=Gcolordata.CDcolor.red;                       //~vXXEM~
    	Ppcolor->green=Gcolordata.CDcolor.green;                   //~vXXEM~
    	Ppcolor->blue=Gcolordata.CDcolor.blue;                     //~vXXEM~
    }                                                              //~vXXEM~
    return 0;                                                      //~vXXEM~
}                                                                  //~vXXEM~
//***************************************************************************//~v73tI~
//color data exchange  for ruler                                   //~v73tI~
//***************************************************************************//~v73tI~
int gxedlg_setrulercolor(int Popt)                                 //~v73tI~
{                                                                  //~v73tI~
    if (Popt)//gbl init,setup for dialog                           //~v73tI~
    {                                                              //~v73tI~
        Srulergdkcolor.red=Mrulercolor.red;                        //~v73tI~
        Srulergdkcolor.green=Mrulercolor.green;                    //~v73tI~
        Srulergdkcolor.blue=Mrulercolor.blue;                      //~v73tI~
    }                                                              //~v73tI~
    else    //exit setup dlg by OK button             //set to Mbgcolor to save to inifile//~v73tI~
    {                                                              //~v73tI~
        Mrulercolor.red=Srulergdkcolor.red;                        //~v73tR~
        Mrulercolor.green=Srulergdkcolor.green;                    //~v73tR~
        Mrulercolor.blue=Srulergdkcolor.blue;                      //~v73tR~
	    memcpy(&Grulerfg,&Srulergdkcolor,sizeof(Srulergdkcolor));  //~v73tR~
	    gdk_gc_set_foreground(Gpgcruler,&Grulerfg);                //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
		cairo_set_line_width(Gpgcruler,1.0);                       //~var8R~
#endif                                                             //~var8R~
    }                                                              //~v73tI~
    return 0;                                                      //~v73tI~
}                                                                  //~v73tI~
//***************************************************************************//~v740I~
//color data exchange  for ruler                                   //~v740I~
//***************************************************************************//~v740I~
int gxedlg_setrulerkey(int Popt)                                   //~v740I~
{                                                                  //~v740I~
    char entrytext[128];                                           //~v740I~
    char *pc,*pco;                                                 //~v740R~
    int ii,ch;                                                     //~v740I~
//****************************                                     //~v740I~
    if (Popt)//gbl init,setup for dialog                           //~v740I~
    {                                                              //~v740I~
    	for (pco=entrytext,pc=Mrulerkey,ii=0;ii<3;ii++,pc++)       //~v740R~
        	if (*pc>=1 && *pc<=12) 	//F1-->F12                     //~v740I~
            	if (ii<2)                                          //~v740I~
	            	pco+=sprintf(pco,"F%d,",*pc);                  //~v740R~
                else                                               //~v740I~
	            	pco+=sprintf(pco,"F%d",*pc);                   //~v740R~
            else                                                   //~v740I~
            	*pco++=toupper(*pc);                               //~v740R~
        *pco=0;                                                    //~v740I~
        SET_ENTRYTEXT(Soptiondlg,STRIDC_EDIT_RULERKEY,entrytext);  //~v740R~
    }                                                              //~v740I~
    else                                                           //~v740I~
    {                                                              //~v740I~
    	memset(entrytext,0,sizeof(entrytext));                     //~v740I~
        GET_ENTRYTEXT(Soptiondlg,STRIDC_EDIT_RULERKEY,entrytext);  //~v740R~
        dprintf("rulerkey text=%s\n",entrytext);                   //~v740I~
        pc=entrytext+strspn(entrytext," ");                        //~v740R~
        for (pco=Mrulerkey,ii=0;*pc && ii<3;ii++)                  //~v740I~
        {                                                          //~v740I~
            ch=toupper(*pc);                                       //~v740I~
        	if (ch=='F'		//Fn key                               //~v740I~
            &&  (*(pc+1)>='1' && *(pc+1)<='9'))                    //~v740I~
            {                                                      //~v740I~
            	pc++;                                              //~v740I~
            	ch=atoi(pc);                                       //~v740I~
                if (!(ch>=1 && ch<=12))                            //~v740I~
                	break;	//err                                  //~v740I~
                while(*pc>='0' && *pc<='9')                        //~v740I~
                	pc++;                                          //~v740I~
            }                                                      //~v740I~
            else                                                   //~v740I~
            {                                                      //~v740I~
                pc++;                                              //~v740I~
                if (ch==',')                                       //~v740I~
                {                                                  //~v740I~
                	ii--;                                          //~v740I~
                    continue;                                      //~v740I~
                }                                                  //~v740I~
            }                                                      //~v740I~
            *pco++=ch;                                             //~v740I~
        }                                                          //~v740I~
        if (ii)                                                    //~v740I~
        {                                                          //~v740I~
            if (ii!=3||*pc)                                        //~v740R~
            {                                                      //~v740R~
                uerrmsgbox("specify 3 upper letter by the sequence of Vertical/Horizontal/Cross ruler\n"//~v740R~
                           "ex) \"F1F2F12\":F1,F2,F12  \"!#$\":1,3,4  \"IOP\":iop",0);//~v740R~
                return 4;                                          //~v740R~
            }                                                      //~v740R~
            *pco=0;                                                //~v740R~
        }                                                          //~v740I~
        else                                                       //~v740I~
			strcpy(Mrulerkey,DEF_RULERKEY);	//default rulerkey     //~v740I~
dprintf("rulerkey=%x %x %x\n",(UINT)Mrulerkey[0],(UINT)Mrulerkey[1],(UINT)Mrulerkey[2]);//~v740R~
    }                                                              //~v740I~
    return 0;                                                      //~v740I~
}                                                                  //~v740I~
//***************************************************************************//~v77tI~
// set fontselection dialog style(face) column selection           //~v77tI~
// because gtk_font_selection_dialog_set_font_name faile if style contained in fontname//~v77tI~
//***************************************************************************//~v77tI~
void set_cursor_to_iter (GtkTreeView *view, GtkTreeIter *iter)     //~v77tI~
{                                                                  //~v77tI~
  GtkTreeModel *model = gtk_tree_view_get_model (view);            //~v77tI~
  GtkTreePath *path = gtk_tree_model_get_path (model, iter);       //~v77tI~
  gtk_tree_view_set_cursor (view, path, 0, FALSE);                 //~v77tI~
  gtk_tree_path_free (path);                                       //~v77tI~
}//set_cursor_to_iter                                              //~v77tI~
#ifndef OPTGTK3                                                    //~var8R~
//***************************************************************************//~v77tI~
// set fontselection dialog style(face) column selection           //~v77tI~
// because gtk_font_selection_dialog_set_font_name faile if style contained in fontname//~v77tI~
//***************************************************************************//~v77tI~
int gxedlg_setfaceselection(GtkFontSelectionDialog *Pfontdlg,char *Pfacename)//~v77tR~
{                                                                  //~v77tI~
	GtkFontSelection *pfontsel;                                    //~v77tI~
	GtkTreeModel *model;                                           //~v77tI~
	gboolean valid;                                                //~v77tI~
    const gchar *pfacename;                                        //~v77tR~
  	GtkTreeIter iter;                                              //~v77tI~
    PangoFontFace *pface=0;                                        //~v77tI~
  	PangoFontFace *new_face = NULL;                                //~v77tI~
  	GtkTreeIter match_iter;                                        //~v77tI~
enum {                                                             //~v77tI~
  FACE_COLUMN,                                                     //~v77tI~
  FACE_NAME_COLUMN                                                 //~v77tI~
};                                                                 //~v77tI~
//*************************************                            //~v77tI~
//#ifndef OPTGTK3                                                  //~var8R~
	pfontsel=GTK_FONT_SELECTION(Pfontdlg->fontsel);                //~v77tR~
//#else                                                            //~var8R~
//    pfontsel=GTK_FONT_CHOOSER(Pfontdlg);                         //~var8R~
//#endif                                                           //~var8R~
//#ifndef OPTGTK3                                                  //~var8R~
  	model = gtk_tree_view_get_model(GTK_TREE_VIEW (pfontsel->face_list));//~v77tR~
//#else                                                            //~var8R~
//    model = gtk_tree_view_get_model(GTK_TREE_VIEW (gtk_font_selection_get_face_list(pfontsel)));//~var8R~
//#endif                                                           //~var8R~
  	for (valid = gtk_tree_model_get_iter_first (model, &iter);     //~v77tI~
       valid;                                                      //~v77tI~
       valid = gtk_tree_model_iter_next (model, &iter))            //~v77tI~
    {                                                              //~v77tI~
      	gtk_tree_model_get (model, &iter, FACE_COLUMN, &pface, -1);//~v77tI~
      	pfacename=pango_font_face_get_face_name(pface);            //~v77tI~
dprintf("face of list=%s\n",pfacename);                            //~v77tI~
      	if (!strcmp(pfacename,Pfacename))                          //~v77tI~
	 	{                                                          //~v77tI~
        	new_face=pface;                                        //~v77tR~
	  		match_iter = iter;                                     //~v77tI~
	  		break;                                                 //~v77tI~
		}                                                          //~v77tI~
    }                                                              //~v77tI~
    if (!new_face)                                                 //~v77tI~
    	return 0;                                                  //~v77tI~
//#ifndef OPTGTK3                                                  //~var8R~
	if (pfontsel->face==new_face)                                  //~v77tI~
//#else                                                            //~var8R~
//    if (gtk_font_selection_get_face(pfontsel)==new_face)         //~var8R~
//#endif                                                           //~var8R~
    	return 0;                                                  //~v77tI~
//#ifndef OPTGTK3                                                  //~var8R~
  	set_cursor_to_iter(GTK_TREE_VIEW (pfontsel->face_list),&match_iter);//~v77tI~
//#else                                                            //~var8R~
//    set_cursor_to_iter(GTK_TREE_VIEW (gtk_font_selection_get_face_list(pfontsel)),&match_iter);//~var8R~
//#endif                                                           //~var8R~
  	return TRUE;                                                   //~v77tI~
}//gxedlg_setfaceselection                                         //~v77tI~
#endif                                                             //~var8R~
//***************************************************************************//~vXXEM~
// Font                                                            //~vXXEM~
//***************************************************************************//~vXXEM~
void gxedlg_option_fontstyle  				(GtkButton       *Pbutton,//~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg option fontstyle\n");                          //~v664R~
	gxedlg_font_create_sub(0,Soptiondlg);                          //~vXXER~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
void gxedlg_font_create_sub 				(int Pprintid,GtkWidget *Pparent)//~vXXER~
{                                                                  //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
  	GtkWidget *framewindow;                                        //~vXXEM~
#else                                                              //~var8R~
#endif                                                             //~var8R~
//*********************************************                    //~vXXEM~
	 dprintf("on_font_activate  \n");                               //~v664R~
#ifndef OPTGTK3                                                    //~var8R~
  	framewindow = Gpframe;                                         //~vXXEM~
    Sfontdlg= create_fontselectiondialog ();                       //~vXXEM~
#else                                                              //~var8R~
    Sfontdlg= create_fontselectiondialog(Pparent);                 //~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_object_set_user_data (GTK_OBJECT (Sfontdlg), Pparent);     //~vXXER~
#else                                                              //~var8R~
    g_object_set_data (G_OBJECT (Sfontdlg),"user_data", Pparent);  //~var8R~
#endif                                                             //~var8R~
                                                                   //~vXXEM~
    /* Make sure the dialog doesn't disappear behind the main window. *///~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Sfontdlg),           //~vXXEM~
				    GTK_WINDOW (framewindow));                     //~vXXEM~
#else                                                              //~var8R~
    gtk_window_set_transient_for (GTK_WINDOW (Sfontdlg),           //~var8R~
				    GTK_WINDOW (Pparent));                         //~var8R~
#endif                                                             //~var8R~
    dprintf("family from desc=%s\n",pango_font_description_get_family(Gfontdata[Pprintid].FDfontdesc));//~v77tI~
    dprintf("style  from desc=%d\n",pango_font_description_get_style(Gfontdata[Pprintid].FDfontdesc));//~v77tR~
	if (Gfontdata[Pprintid].FDfontname)                            //~vXXEM~
//    	gtk_font_selection_dialog_set_font_name (GTK_FONT_SELECTION_DIALOG (Sfontdlg),//~v77tR~
//											Gfontdata[Pprintid].FDfontname);//~v77tR~
	{                                                              //~v77tI~
#ifndef OPTGTK3                                                    //~var8R~
	  	gchar *fontname,*facename,*pc,*pc2;                        //~v77tR~
//      int rc;                                                    //~v77tI~//~vaa7R~
    	fontname=g_strdup(Gfontdata[Pprintid].FDfontname);         //~v77tI~
      	if (pc=strchr(fontname,','),pc)   //end of family          //~v77tR~
        	pc++;                                                  //~v77tR~
        else                                                       //~v77tI~
    		pc=strchr(fontname,' ');                               //~v77t~//~v77tR~
        if (pc)                                                    //~v77tR~
        {                                                          //~v77tI~
			pc2=pc+strspn(pc," ");                                 //~v77tR~
	    	facename=g_strdup(pc2);                                //~v77tI~
		    if (pc2=strrchr(facename,' '),pc2)                     //~v77tI~
            	*pc2=0;                                            //~v77tI~
    	}                                                          //~v77tI~
        else                                                       //~v77tI~
        	facename=0;                                            //~v77tI~
	    pc2=strrchr(fontname,' ');                                 //~v77tI~
        if (pc && pc2 && pc2>pc)    //style parmexist              //~v77tR~
    		memset(pc,' ',(UINT)((ULONG)pc2-(ULONG)pc));	//drop stle//~v77tI~
dprintf("setselection fontname=%s\n",fontname);                    //~v77tI~
	  	/*rc=*/gtk_font_selection_dialog_set_font_name(GTK_FONT_SELECTION_DIALOG (Sfontdlg),//~v77tR~//~vaa7R~
											fontname);//if face contained set_selection fail//~v77tR~
        if (facename)                                              //~v77tI~
        {                                                          //~v77tI~
dprintf("setselection facename=%s\n",facename);                    //~v77tI~
    		gxedlg_setfaceselection(GTK_FONT_SELECTION_DIALOG(Sfontdlg),facename);//~v77tR~
	        g_free(facename);                                      //~v77tI~
        }                                                          //~v77tI~
        g_free(fontname);                                          //~v77tI~
#else   //OPTGTK3                                                  //~var8R~
		gxedlg_font_chooser_set_font_name(GTK_FONT_CHOOSER_DIALOG(Sfontdlg),//~var8R~
    										Gfontdata[Pprintid].FDfontname);//~var8R~
#endif                                                             //~var8R~
    }                                                              //~v77tI~
#ifndef OPTGTK3                                                    //+var8I~//~var8R~
  if (wxegetdbcsmode())                                            //~v696I~
    gtk_font_selection_dialog_set_preview_text(GTK_FONT_SELECTION_DIALOG(Sfontdlg),Sfontsampletext);//~vXXEM~
  else                                                             //~v696I~
    gtk_font_selection_dialog_set_preview_text(GTK_FONT_SELECTION_DIALOG(Sfontdlg),Sfontsampletexte);//~v696I~
#else                                                              //~var8R~
  if (wxegetdbcsmode())                                            //~var8R~
    gtk_font_chooser_set_preview_text(GTK_FONT_CHOOSER(Sfontdlg),Sfontsampletext);//~var8R~
  else                                                             //~var8R~
    gtk_font_chooser_set_preview_text(GTK_FONT_CHOOSER(Sfontdlg),Sfontsampletexte);//~var8R~
#endif                                                             //~var8R~
  	gtk_widget_show (Sfontdlg);                                    //~vXXEM~
                                                                   //~vXXEM~
  	/* We make sure the dialog is visible. */                      //~vXXEM~
  	gtk_window_present (GTK_WINDOW (Sfontdlg));                    //~vXXEM~
	Sfontsorp=Pprintid;		//index of font data table             //~vXXEM~
    dprintf("gxedlg_option_fontface destroy dialog\n");            //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
    {                                                              //~var8R~
    	int rc;                                                    //~var8R~
    	rc=gtk_dialog_run(GTK_DIALOG(Sfontdlg));                   //~var8R~
    	dprintf("response_fontselectiondialog responseid=%d\n",rc);//~var8R~
		if (rc==GTK_RESPONSE_OK) //-5                              //~var8R~
    	{                                                          //~var8R~
			gxedlg_Font_OnOK(NULL/*button*/,NULL/*user_data*/);    //~var8R~
    	}                                                          //~var8R~
		if (rc==GTK_RESPONSE_CANCEL)//-6                           //~var8R~
    	{                                                          //~var8R~
			gxedlg_Font_OnCancel(NULL/*button*/,NULL/*user_data*/);//~var8R~
    	}                                                          //~var8R~
    }                                                              //~var8R~
#endif                                                             //~var8R~
    return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
void gxedlg_Font_OnOK      				(GtkButton       *Pbutton, //~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg font onok mainlevel=%d\n",gtk_main_level());   //~v664R~
    gxedlg_getfontdata(Sfontdlg,Sfontsorp);                        //~vXXEM~
    if (!Sfontsorp)		//print dlg                                //~vXXER~
		gxedlg_option_draw_samplebox();                            //~vXXEI~
    gtk_widget_destroy(Sfontdlg);                                  //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
void gxedlg_Font_OnCancel  				(GtkButton       *Pbutton, //~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg font cancel\n");                               //~v664R~
    gtk_widget_destroy(Sfontdlg);                                  //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
                                                                   //~vXXEM~
void gxedlg_Font_OnApply   				(GtkButton       *Pbutton, //~vXXEM~
                                        gpointer         Puser_data)//~vXXEM~
{                                                                  //~vXXEM~
//****************************                                     //~vXXEM~
	 dprintf("gxedlg font apply\n");                                //~v664R~
    gxedlg_getfontdata(Sfontdlg,Sfontsorp);                        //~vXXEM~
    if (!Sfontsorp)		//print dlg                                //~vXXER~
    {                                                              //~vXXER~
		gxedlg_option_draw_samplebox();                            //~vXXEI~
		xxemain_createfont();                                      //~vXXER~
		xxemain_scrinvalidate(1);                                  //~vXXER~
    }                                                              //~vXXER~
	return;                                                        //~vXXEM~
}//gxedlg_Font_OnApply                                             //~var8R~
//******************************************************           //~vXXEM~
//* get font data from dialog setting                              //~vXXEM~
//******************************************************           //~vXXEM~
int gxedlg_getfontdata(GtkWidget *Ppfontdlg,int Pprintid)          //~vXXEM~
{                                                                  //~vXXEM~
    PFONTDATA pfd;                                                 //~vXXEM~
    GtkWidget *parent;                                             //~vXXEI~
                                                                   //~v75XR~
  	GtkFontSelectionDialog *fsd;                                   //~v75XR~
	GtkFontSelection *fontsel;                                     //~v75XR~
#ifndef OPTGTK3                                                    //~var8R~
    G_CONST_RETURN char *pfamilyname,*pfacename;    //need not free//~v75XR~
    int len;                                                       //~v75XR~
    char fontname[256],*pc;                                        //~v75XR~
#endif                                                             //~var8R~
	gchar *pfontname;                                              //~v75XR~
//************************************                             //~vXXEM~
    pfd=Gfontdata+Pprintid;                                        //~vXXEM~
//  if (pfd->FDfontname)                                           //~v77rR~
//    	g_free(pfd->FDfontname);                                   //~v77rR~
#ifndef OPTGTK3                                                    //~var8R~
  	pfd->FDfontname=gtk_font_selection_dialog_get_font_name (GTK_FONT_SELECTION_DIALOG (Ppfontdlg));//~vXXEM~
#else   //OPTGTK3                                                  //~var8R~
  	pfd->FDfontname=gtk_font_chooser_get_font(GTK_FONT_CHOOSER(Ppfontdlg));//~var8R~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
//supply face=Reguler to avoid assertion face!=NULL err msg        //~v75xR~
//  if (Pprintid)	//print font                                   //~v75XR~
//  {                                                              //~v75XR~
        pfontname=pfd->FDfontname;                                 //~v75XR~
    	dprintf("getfontdata dialog fontname=%s\n",pfontname);     //~v75XR~
  		fsd=GTK_FONT_SELECTION_DIALOG (Ppfontdlg);                 //~v75XR~
//#ifndef OPTGTK3                                                  //~var8R~
  		fontsel=GTK_FONT_SELECTION (fsd->fontsel);                 //~v75XR~
    	dprintf("getfontdata family=%p\n",fontsel->family);        //~v75XR~
    	dprintf("getfontdata face=%p\n",fontsel->face);            //~v75XR~
//#else                                                            //~var8R~
//        fontsel=GTK_FONT_SELECTION (gtk_font_selection_dialog_get_font_selection(fsd));//~var8R~
//#endif                                                           //~var8R~
//#ifndef OPTGTK3                                                  //~var8R~
    	pfamilyname=pango_font_family_get_name(fontsel->family);   //~v75XR~
//#else                                                            //~var8R~
//        pfamilyname=pango_font_family_get_name(gtk_font_selection_get_family(fontsel));//~var8R~
//#endif                                                           //~var8R~
//#ifndef OPTGTK3                                                  //~var8R~
    	pfacename=pango_font_face_get_face_name(fontsel->face);    //~v75XR~
//#else                                                            //~var8R~
//        pfacename=pango_font_face_get_face_name(gtk_font_selection_get_face(fontsel));//~var8R~
//#endif                                                           //~var8R~
    	dprintf("getfontdata facename=%s,familyname=%s\n",pfacename,pfamilyname);//~v77tI~
    	dprintf("tostring=%s\n",pango_font_description_to_string((const PangoFontDescription*)(Gfontdata[0].FDfontdesc)));//~v77tI~
//      if (!strstr(pfontname,pfacename))	//face name missing    //~v77tR~
//      {                                                          //~v77tR~
//      	pc=strrchr(pfontname,' ');                             //~v77tR~
//          if (pc)                                                //~v77tR~
//          {                                                      //~v77tR~
//        		len=(ULONG)pc-(ULONG)pfontname;                    //~v77tR~
//        		memcpy(fontname,pfontname,(UINT)len);              //~v77tR~
//              sprintf(fontname+len," %s%s",pfacename,pc);        //~v77tR~
        		pc=strrchr(pfontname,' ');	//size pos             //~v77tI~
        		if (pc)                                            //~v77tI~
        			pc++;		//stype position                   //~v77tI~
        		else                                               //~v77tI~
        			pc="";                                         //~v77tI~
                if (strchr(pfamilyname,' '))                       //~v77tI~
        			sprintf(fontname,"%s, %s %s",pfamilyname,pfacename,pc);//family+style+size;//~v77tR~
                else                                               //~v77tI~
        			sprintf(fontname,"%s %s %s",pfamilyname,pfacename,pc);//family+style+size;//~v77tI~
                len=strlen(fontname);                              //~v75XR~
        		pfontname=g_new(gchar,len+1);                      //~v75XR~
        		strcpy(pfontname,fontname);                        //~v75XR~
//  			g_free(pfd->FDfontname);                           //~v77rR~
    			pfd->FDfontname=pfontname;                         //~v75XR~
		    	dprintf("getfontdata result=%s\n",pfontname);      //~v77tI~
//          }                                                      //~v77tR~
//      }                                                          //~v77tR~
//  }                                                              //~v75XR~
//                                                                 //~v75XR~
#else   //OPTGTK3                                                  //~var8R~
  	fsd=GTK_FONT_CHOOSER_DIALOG (Ppfontdlg);                       //~var8R~
  	fontsel=GTK_FONT_CHOOSER(fsd);                                 //~var8R~
    pfontname=gtk_font_chooser_get_font(fontsel);                  //~var8R~
	pfd->FDfontname=pfontname;                                     //~var8R~
#endif                                                             //~var8R~
  	pfd->FDfontdesc=pango_font_description_from_string(pfd->FDfontname);//~vXXEM~
    dprintf("new toring=%s\n",pango_font_description_to_string((const PangoFontDescription*)(pfd->FDfontdesc)));//~v77tI~
    dprintf("family from desc=%s\n",pango_font_description_get_family(pfd->FDfontdesc));//~v77tI~
    dprintf("style  from desc=%d\n",pango_font_description_get_style(pfd->FDfontdesc));//~v77tI~
#ifndef OPTGTK3                                                    //~var8R~
    parent=gtk_object_get_user_data (GTK_OBJECT (Ppfontdlg));      //~vXXEI~
#else                                                              //~var8R~
    parent=g_object_get_data (G_OBJECT (Ppfontdlg),"user_data");   //~var8R~
#endif                                                             //~var8R~
	gxedlg_settext_fontname(Pprintid,parent);                      //~vXXER~
    dprintf("desc=%p,fontname=%s,printfontsw=%d\n",pfd->FDfontdesc,pfd->FDfontname,Pprintid);//~v75XR~
    return pfd->FDfontdesc!=0;                                     //~vXXEM~
}//gxedlg_getfontdata                                              //~vXXEM~
                                                                   //~vXXEM~
//**************************************************************** //~vXXEM~
//*                                                                //~vXXEM~
//**************************************************************** //~vXXEM~
void gxedlg_displaycolor(void)                                     //~vXXEM~
{                                                                  //~vXXEM~
    return;                                                        //~vXXEM~
}//displaycolor                                                    //~vXXEM~
//****************************************************             //~vXXEM~
//* draw sample color box                                          //~vXXEM~
//****************************************************             //~vXXEM~
void gxedlg_option_draw_samplebox(void)                            //~vXXEM~
{                                                                  //~vXXEM~
	GtkWidget *pwdraw;                                             //~vXXEM~
	GdkPixmap *pixmap;                                             //~vXXEM~
    GdkGC   	*pgc;                                              //~vXXEM~
    GdkColormap *pcm;                                              //~vXXEM~
    GdkColor bgcolor;                                              //~vXXEM~
    GdkColor *pcol;                                                //~vXXEI~
    PangoLayout *playout;                                          //~vXXEM~
    int hh,ww,boundary=2;                                          //~vXXEM~
    UCHAR attrtbl[8];                                              //~vXXER~
    int xx1,yy1,xx2,yy2,fontwidth,fontheight;                      //~v73yR~
//***************************                                      //~vXXEM~
	pixmap=Spmcolorsample;                                         //~vXXEM~
    pwdraw=Soptiondlg_colorsample;                                 //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
    ww=pwdraw->allocation.width;                                   //~vXXEM~
    hh=pwdraw->allocation.height;                                  //~vXXEM~
#else                                                              //~var8R~
	csub_get_widget_allocation_wh(pwdraw,&ww,&hh);                 //~var8R~
#endif                                                             //~var8R~
    dprintf("color sample draw box w=%d,h=%d\n",ww,hh);            //~v664R~
#ifndef OPTGTK3                                                    //~var8R~
    pgc=gdk_gc_new(pwdraw->window);                                //~vXXEM~
#else                                                              //~var8R~
    pgc=Spgccolorsample;	//draw to pixmap through gc            //~var8R~
#endif                                                             //~var8R~
    dprintf("color sample draw gc=%p\n",pgc);                      //~var8R~
#if GTK_CHECK_VERSION(3,22,0)	//gtk_ui_manager was deprecated    //~vb7tI~
    pcm=gdk_screen_get_system_visual(gdk_screen_get_default());	//pcm:GdkVisual by gxe.h//~vb7tI~
#else                                                              //~vb7tI~
    pcm=gdk_colormap_get_system();                                 //~vXXEM~
#endif                                                             //~vb7tI~
    playout=gtk_widget_create_pango_layout(pwdraw,NULL);           //~vXXEM~
    pango_layout_set_font_description(playout,Gfontdata[0].FDfontdesc);//~vXXEM~
    UTRACEP("gxe_option_draw_sample pango_layout_et_font_description playout=%p,fontdesc[0]=%p\n",playout,Gfontdata[0].FDfontdesc);//~vam0R~
    memcpy(&bgcolor,&(Gcolordata.CDcolor),sizeof(GdkColor));       //~vXXEM~
//  gdk_color_alloc(pcm,&bgcolor);           //gdk_color_alloc depricated//~v73tR~
    gdk_colormap_alloc_color(pcm,&bgcolor,FALSE,TRUE);             //~v73tI~
    gdk_gc_set_foreground(pgc,&bgcolor);                           //~vXXEM~
    gdk_gc_set_background(pgc,&bgcolor);                           //~vXXEM~
    gdk_draw_rectangle(pixmap,pgc,TRUE,0,0,ww,hh);                 //~vXXEM~
//sample text with color                                           //~vXXEI~
	wxe_getsamplecolor(attrtbl);	//3 sample paletteno           //~vXXEI~
    dprintf("attr=%d,%d,%d\n",*attrtbl,*(attrtbl+1),*(attrtbl+2)); //~v664R~
    pcol=Gxxepalette+(int)(*attrtbl);                              //~vXXEM~
    gxe_option_draw_sampletext(pixmap,pgc,playout,pcm,pcol,"Browse",boundary,boundary);//~vXXEM~
    pcol=Gxxepalette+(int)(*(attrtbl+1));                          //~vXXEI~
    gxe_option_draw_sampletext(pixmap,pgc,playout,pcm,pcol,"Edit  ",boundary+(ww-boundary)/3,boundary);//~vXXEI~
    pcol=Gxxepalette+(int)(*(attrtbl+2));                          //~vXXEI~
    gxe_option_draw_sampletext(pixmap,pgc,playout,pcm,pcol,"Lineno",boundary+(ww-boundary)*2/3,boundary);//~vXXEI~
//draw ruler                                                       //~v73tI~
	ugetfontmetrics(Gfontdata[0].FDfontdesc,&fontwidth,&fontheight,0);//0:no monospace chjk//~v73tR~
    gdk_colormap_alloc_color(pcm,&Srulergdkcolor,FALSE,TRUE);      //~v73tI~
    gdk_gc_set_foreground(pgc,&Srulergdkcolor);                    //~v73tI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
	gdk_gc_set_line_attributes(pgc,1/*linewidth*/,0/*Plinetype*/,0/*GdkCapStyle*/,0/*GdkJoinStyle*/);//~var8R~
#endif                                                             //~var8R~
    xx1=0;xx2=ww;                                                  //~v73tI~
    yy1=yy2=min(fontheight+boundary,hh-2);                         //~v73tR~
    gdk_draw_line(Spmcolorsample,pgc,xx1,yy1,xx2,yy2); //hline     //~v73tR~
    xx1=xx2=min(fontwidth+boundary,ww-2);                          //~v73tR~
    yy1=0;yy2=hh;                                                  //~v73tI~
    gdk_draw_line(Spmcolorsample,pgc,xx1,yy1,xx2,yy2); //vhline    //~v73tR~
    gtk_widget_queue_draw_area(pwdraw,0,0,ww,hh);                  //~vXXEM~
	return;                                                        //~vXXEM~
}//gxedlg_option_draw_samplebox                                    //~vXXEM~
//****************************************************             //~vXXEM~
//* draw text by sample color                                      //~vXXEM~
//****************************************************             //~vXXEM~
void gxe_option_draw_sampletext(GdkPixmap *Pppixmap,GdkGC *Ppgc,PangoLayout *Pplayout,//~vXXEM~
								GdkColormap *Ppcm,GdkColor *Ppcolor,//~vXXEM~
								char *Pptext,int Pxx,int Pyy)      //~vXXEM~
{                                                                  //~vXXEM~
    GdkColor fgcolor;                                              //~vXXEM~
//******************************                                   //~vXXEM~
    pango_layout_set_text(Pplayout,Pptext,strlen(Pptext));         //~vXXEM~
    memcpy(&fgcolor,Ppcolor,sizeof(GdkColor));                     //~vXXEM~
//  gdk_color_alloc(Ppcm,&fgcolor);                                //~v73tR~
    gdk_colormap_alloc_color(Ppcm,&fgcolor,FALSE,TRUE);            //~v73tI~
    gdk_gc_set_foreground(Ppgc,&fgcolor);                          //~vXXEM~
    gdk_draw_layout(Pppixmap,Ppgc,Pxx,Pyy,Pplayout);               //~vXXEM~
    return;                                                        //~vXXEM~
}//gxe_option_draw_sampletext                                      //~vXXEM~
//***************************                                      //~vXXEM~
// Color sample configure   *                                      //~vXXEM~
//***************************                                      //~vXXEM~
void gxedlg_option_drawingarea_configure	(GtkWidget       *Ppwidget)//~vXXEM~
{                                                                  //~vXXEM~
	GdkPixmap *pixmap;                                             //~vXXEM~
    int ww,hh;                                                     //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
	static int Soldww,Soldhh;                                      //~var8R~
#endif                                                             //~var8R~
//***************************                                      //~vXXEM~
	pixmap=Spmcolorsample;                                         //~vXXEM~
#ifndef OPTGTK3                                                    //~var8R~
	if (pixmap)                                                    //~vXXEM~
    	g_object_unref(pixmap);                                    //~vXXEM~
#endif                                                             //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    ww=Ppwidget->allocation.width;                                 //~vXXEM~
    hh=Ppwidget->allocation.height;                                //~vXXEM~
#else                                                              //~var8R~
	csub_get_widget_allocation_wh(Ppwidget,&ww,&hh);               //~var8R~
#endif                                                             //~var8R~
    dprintf("color sample configure widget=%p,w=%d,h=%d\n",Ppwidget,ww,hh);//~var8R~
#ifndef OPTGTK3                                                    //~var8R~
    Spmcolorsample=gdk_pixmap_new(Ppwidget->window,ww,hh,-1);//-1:depth is same as window//~vXXEM~
#else                                                              //~var8R~
	if (!pixmap||ww!=Soldww||hh!=Soldhh)                           //~var8R~
    {                                                              //~var8R~
		if (pixmap)                                                //~var8R~
    		csub_gc_destroy_pixmap(Spgccolorsample,pixmap);  //destroy gc and pixmap//~var8R~
    	Spmcolorsample=csub_pixmap_new(Ppwidget,ww,hh,-1);//-1:depth is same as window//~var8R~
	    Spgccolorsample=csub_gc_new_pixmap(Ppwidget,Spmcolorsample);//set source_surface to gc//~var8R~
        Soldww=ww,Soldhh=hh;                                       //~var8R~
    }                                                              //~var8R~
    dprintf("color sample configure gc=%p,pixmap=%p\n",Spgccolorsample,Spmcolorsample);//~var8R~
#endif                                                             //~var8R~
	gxedlg_option_draw_samplebox();                                //~vXXEM~
	return;                                                        //~vXXEM~
}//gxedlg_option_drawingarea_configure                             //~vXXEM~
//***************************                                      //~vXXEM~
// Color sample expose      *                                      //~vXXEM~
//***************************                                      //~vXXEM~
#ifndef OPTGTK3                                                    //+var8I~//~var8R~
void gxedlg_option_drawingarea_expose		(GtkWidget       *Ppwidget,//~vXXEM~
                                        GdkEventExpose  *Ppevent)  //~vXXEM~
{                                                                  //~vXXEM~
    dprintf("color sample expose x=%d,y=%d,w=%d,h=%d\n",           //~v664R~
                      Ppevent->area.x,Ppevent->area.y,             //~vXXEM~
                      Ppevent->area.width,Ppevent->area.height);   //~vXXEM~
	gdk_draw_drawable(Ppwidget->window,                            //~vXXEM~
                      Ppwidget->style->fg_gc[GTK_WIDGET_STATE(Ppwidget)],//~vXXEM~
                      Spmcolorsample,                              //~vXXEM~
                      Ppevent->area.x,Ppevent->area.y,             //~vXXEM~
                      Ppevent->area.x,Ppevent->area.y,             //~vXXEM~
                      Ppevent->area.width,Ppevent->area.height);   //~vXXEM~
                                                                   //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
#else   //OPTGTK3                                                  //~var8R~
//***************************                                      //~var8R~
void gxedlg_option_drawingarea_draw(GtkWidget *Ppwidget,cairo_t *Pcr)//~var8R~
{                                                                  //~var8R~
    dprintf("color sample draw event\n");                          //~var8R~
	csub_draw_pixmap_to_screen(Pcr,Spmcolorsample);                //~var8R~
	return;                                                        //~var8R~
}                                                                  //~var8R~
#endif                                                             //~var8R~
//*********************                                            //~vXXEM~
//*font height                                                     //~vXXEM~
//*********************                                            //~vXXEM~
void gxedlg_OnChangeEditHeight(void)                               //~vXXEM~
{                                                                  //~vXXEM~
	return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//*********************                                            //~vXXEM~
//*font width                                                      //~vXXEM~
//*********************                                            //~vXXEM~
void gxedlg_OnChangeEditWidth(void)                                //~vXXEM~
{                                                                  //~vXXEM~
    return;                                                        //~vXXEM~
}                                                                  //~vXXEM~
//***************************************************************************//~vXXEI~
// About                                                           //~vXXER~
//***************************************************************************//~vXXEI~
void gxedlg_about_create 				(GtkMenuItem     *Pmenuitem,//~vXXEI~
                                        gpointer         Puser_data)//~vXXEI~
{                                                                  //~vXXEI~
  	GtkWidget *framewindow;                                        //~vXXEI~
  	GtkLabel  *labelwd;                                            //~vXXEI~
    char verinf[256];                                              //~vXXEI~
//****************************                                     //~vXXEI~
	 dprintf("on_about_activate  \n");                              //~v664R~
  	framewindow = lookup_widget (GTK_WIDGET (Pmenuitem), "framewindow");//~vXXEI~
    Saboutdlg= create_aboutdlg();                                  //~vXXEI~
  	labelwd = (GtkLabel*)lookup_widget (GTK_WIDGET (Saboutdlg), "about_label");//~vXXEI~
//setup about dialog                                               //~vXXEI~
//  sprintf(verinf,"gxe version %d.%02d by MIZUMAKI-machi",WXE_VER/100,WXE_VER%100);//~vXXER~//+vbdaR~
#ifndef OPTGTK3                                                    //+vbdaI~
    sprintf(verinf,"gxe(GTK2) version %d.%02d  by  MIZUMAKI-machi",WXE_VER/100,WXE_VER%100);//+vbdaI~
#else                                                              //+vbdaI~
    sprintf(verinf,"gxe(GTK3) version %d.%02d  by  MIZUMAKI-machi",WXE_VER/100,WXE_VER%100);//+vbdaI~
#endif                                                             //+vbdaI~
    gtk_label_set_label(labelwd,verinf);                           //~vXXEI~
    /* Make sure the dialog doesn't disappear behind the main window. *///~vXXEI~
    gtk_window_set_transient_for (GTK_WINDOW (Saboutdlg),          //~vXXEI~
				    GTK_WINDOW (framewindow));                     //~vXXEI~
  	gtk_widget_show (Saboutdlg);                                   //~vXXEI~
                                                                   //~vXXEI~
  	/* We make sure the dialog is visible. */                      //~vXXEI~
  	gtk_window_present (GTK_WINDOW (Saboutdlg));                   //~vXXEI~
    return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
void gxedlg_About_OnClose   				(GtkButton       *Pbutton,//~vXXEI~
                                        gpointer         Puser_data)//~vXXEI~
{                                                                  //~vXXEI~
//****************************                                     //~vXXEI~
	 dprintf("gxedlg about onclose\n");                             //~v664R~
    gtk_widget_destroy(Saboutdlg);                                 //~vXXEI~
	return;                                                        //~vXXEI~
}                                                                  //~vXXEI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
//******************************************************************//~var8R~
void gxedlg_color_chooser_set_rgba(GtkColorChooserDialog *Pdlg,GdkColor *Pcolor)//~var8R~
{                                                                  //~var8R~
	GdkRGBA *prgba=csub_gdkColor2RGBA(Pcolor,0xff);                //~var8R~
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(Pdlg),prgba);     //~var8R~
    gdk_rgba_free(prgba);                                          //~var8R~
}                                                                  //~var8R~
//******************************************************************//~var8R~
void gxedlg_color_chooser_get_rgba(GtkColorChooserDialog *Pdlg,GdkColor *Ppcolor)//~var8R~
{                                                                  //~var8R~
	GdkRGBA rgba;                                                  //~var8R~
//*****************************                                    //~var8R~
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(Pdlg),&rgba);     //~var8R~
	csub_gdkRGBA2Color(&rgba,Ppcolor);                             //~var8R~
}                                                                  //~var8R~
//******************************************************************//~var8R~
void gxedlg_font_chooser_set_font_name(GtkFontChooserDialog *Ppdlg,char *Pfontname)//~var8R~
{                                                                  //~var8R~
	GtkFontChooser *chooser;                                       //~var8R~
//*****************************                                    //~var8R~
	chooser=GTK_FONT_CHOOSER(Ppdlg);                               //~var8R~
    gtk_font_chooser_set_font(chooser,Pfontname);                  //~var8R~
}//gxedlg_font_chooser_set_font_name                               //~var8R~
#endif                                                             //~var8R~
