//*CID://+vb2bR~:                             update#=  234;       //+vb2bR~
//***************************************************************************//~v59zI~
//vb2b:160119 (gxe)new --xxekbchku8 option to print utf8 char      //+vb2bI~
//varc:140215 add resizehint option  --gh={Y|n}                    //~varcI~
//var8:140127 gtk3 suppott                                         //~var8I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//va70:000701 LP64 option support. at first chk PTR sz(ini file comaptibility)//~v770I~
//v76c:070617 (XXE)paste from PRIMARY clipboard by middle button down//~v76cI~
//v71A:061030 Use HtmlHelp;Winhelp is deprecated at Vista;XP english ersion cannot read .hlp by the readson of codepage unsupported//~v71AI~
//v69u:060602 (XXE)try im for english mode                         //~v69uI~
//v669:050826 (XXE)help support                                    //~v669I~
//***************************************************************************//~v59zI~
// gxe.c                                                           //~v59zI~
//***************************************************************************//~v59zI~
//                                                                 //~v59zI~
#include <stdlib.h>                                                //~var8R~
#include <string.h>                                                //~var8R~
#include <ctype.h>                                                 //~var8R~
                                                                   //~v59zI~
#ifdef HAVE_CONFIG_H                                               //~v59zI~
#  include <config.h>                                              //~v59zI~
#endif                                                             //~v59zI~
                                                                   //~v59zI~
#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>                                                 //~v59zI~
#else                                                              //~var8R~
#include <gtk/gtk.h>                                               //~var8R~
#include <gdk/gdkx.h>                                              //~var8R~
#endif                                                             //~var8R~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0I~
	#else    //!GTKPRINT                                           //~vam0I~
#include <libgnomeprint/gnome-print.h>                             //~v59zI~
#include <libgnomeprint/gnome-print-job.h>                         //~v59zI~
	#endif   //!GTKPRINT                                           //~vam0I~
#endif                                                             //~vam0I~
                                                                   //~v59zI~
#include "callbacks.h"                                             //~v59zI~
#include "interface.h"                                             //~v59zI~
#include "support.h"                                               //~v59zI~
                                                                   //~v59zI~
#include <ulib.h>                                                  //~v59zI~
#include <ufile.h>                                                 //~v669I~
#include <ustring.h>                                               //~varcI~
                                                                   //~v59zI~
#include <xxedef.h>                                                //~v59zM~
//#include <xxemain.h>                                             //~var8R~
#include <xxexei.h>                                                //~v59zM~
                                                                   //~v59zI~
#define  GBL_GXE                                                   //~v59zI~
#include "gxe.h"                                                   //~v59zI~
#include "gxemfrm.h"                                               //~v59zR~
#include "gxeview.h"                                               //~v59zI~
#include <xxemain.h>                                               //~var8R~
                                                                   //~v59zI~
//***************************************************************************//~v59zI~
#define OPT_GEOMETRY   "gh="	//option not to set geomitryhint   //~varcR~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
	#define HOVERRGBA {0.1/*r*/,0.4/*g*/,0.1/*b*/,0.1/*opaq*/}     //~var8R~
#endif                                                             //~var8R~
void gxe_im_init(void);                                            //~v59zI~
void gxe_parmchk(int *Ppargc,char ***Ppargv);                      //~v59zI~
void gxe_appinit(void);                                            //~v59zI~
void gxe_help(void);                                               //~v59zI~
//***************************************************************************//~v59zI~
// init1:before frame window create                                //~v59zR~
//***************************************************************************//~v59zI~
void gxe_init(int argc,char *arg[])                                //~v59zR~
{                                                                  //~v59zI~
	gxe_parmchk(&argc,&arg);                                       //~v59zI~
    wxe_preinit(argc,arg);  //xe preinit;get Gworkdir              //~v59zR~
    gxemfrm_construct();  		//read ini data                    //~v59zI~
    gxe_appinit();                                                 //~v59zI~
    xxemain_construct();		//xxemain global init              //~v59zR~
	gxe_im_init();                                                 //~v59zI~
}                                                                  //~v59zI~
//***************************************************************************//~v59zI~
// drop gnome parameter and chk xxe parameter                      //~v59zI~
//***************************************************************************//~v59zI~
void gxe_parmchk(int *Ppargc,char ***Ppargv)                       //~v59zI~
{                                                                  //~v59zI~
	int argc,nargc,ii;                                             //~v59zR~
	char **argv,**nargv,*pc;                                       //~v59zR~
//  FILEFINDBUF3 ffb3;                                             //~v71AR~
//static char Shelpdir[_MAX_PATH];                                 //~v71AR~
//*********************                                            //~v59zI~
    argc=*Ppargc;                                                  //~v59zI~
    argv=*Ppargv;                                                  //~v59zI~
//  *Ppargv=nargv=(char**)malloc((argc+1)*4);                      //~v59zR~//~v770R~
    *Ppargv=nargv=(char**)malloc((argc+1)*PTRSZ);                  //~v770I~
    nargc=0;                                                       //~v59zI~
    for (ii=0;ii<argc;ii++,argv++)                                 //~v59zI~
    {                                                              //~v59zI~
    	pc=*argv;                                                  //~v59zI~
    	if (*pc=='-'&&*(pc+1)=='-')                                //~v59zI~
        {                                                          //~v59zI~
        	pc+=2;                                                 //~v59zI~
//            if (!memicmp(pc,"hd:",3)) //helpdir                  //~v71AR~
//            {                                                    //~v71AR~
//                ufullpath(Shelpdir,pc+3,_MAX_PATH);              //~v71AR~
//                Ghelpdir=Shelpdir;                               //~v71AR~
//                if (ufstat(Ghelpdir,&ffb3)||!(ffb3.attrFile & FILE_DIRECTORY))//~v71AR~
//                {                                                //~v71AR~
//                    printf("helpdir %s is not found or not dir\n",Ghelpdir);//~v71AR~
//                    exit(8);                                     //~v71AR~
//                }                                                //~v71AR~
//            }                                                    //~v71AR~
//            else                                                 //~v71AR~
        	if (!stricmp(pc,"h"))                                  //~v59zR~
            	gxe_help();                                        //~v59zI~
            else                                                   //~v59zI~
        	if (!stricmp(pc,"?"))                                  //~v59zI~
            	gxe_help();                                        //~v59zI~
            else                                                   //~v59zI~
        	if (!stricmp(pc,"hh"))                                 //~varcI~
            {                                                      //~varcI~
	            Gxxestat|=GXXES_DEBUGHELP;	//no set geometry hint //~varcI~
            	gxe_help();                                        //~varcI~
            }                                                      //~varcI~
            else                                                   //~varcI~
        	if (!stricmp(pc,"??"))                                 //~varcI~
            {                                                      //~varcI~
	            Gxxestat|=GXXES_DEBUGHELP;	//no set geometry hint //~varcI~
            	gxe_help();                                        //~varcI~
            }                                                      //~varcI~
            else                                                   //~varcI~
        	if (USTRHEADIS_IC(pc,OPT_GEOMETRY))                    //~varcR~
            {                                                      //~varcI~
            	if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='N')    //~varcR~
	            	Gxxestat|=GXXES_NOGEOMETRYHINT;	//no set geometry hint//~varcR~
                else                                               //~varcI~
            	if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='Y')    //~varcR~
	            	Gxxestat&=~GXXES_NOGEOMETRYHINT;	//no set geometry hint//~varcI~
//                else                                             //~varcR~
//                if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='F')      //set to frame//~varcR~
//                    Gxxestat|=GXXES_FRAMEGH;                     //~varcR~
//                else                                             //~varcR~
//                if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='V')      //set to frame//~varcR~
//                    Gxxestat|=GXXES_VIEWGH;                      //~varcR~
                else                                               //~varcI~
            	if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='0')      //basex=basey=0;//~varcR~
	            	Gxxestat|=GXXES_BASE0;                         //~varcI~
                else                                               //~varcI~
            	if (toupper(*(pc+sizeof(OPT_GEOMETRY)-1))=='S')      //basex=basey=0;//~varcI~
	            	Gxxestat|=GXXES_GHATONSIZE;                    //~varcR~
                else                                               //~varcI~
                {                                                  //~varcI~
	            	Ggeometrybasex=atoi(pc+sizeof(OPT_GEOMETRY)-1);      //basex=basey=0;//~varcI~
                    printf("parm basex=%d\n",Ggeometrybasex);      //~varcR~
                }                                                  //~varcI~
            }                                                      //~varcI~
            else                                                   //~varcI~
        	if (!stricmp(pc,"xxekbchk"))                           //~v59zR~
            	Gxxeopt|=GXXEOPT_KBCHK;                            //~v59zI~
            else                                                   //+vb2bI~
        	if (!stricmp(pc,"xxekbchku8"))                         //+vb2bI~
            	Gxxeopt|=GXXEOPT_KBCHK|GXXEOPT_KBCHKU8;            //+vb2bI~
            continue;                                              //~v59zI~
        }                                                          //~v59zI~
        *nargv++=pc;                                               //~v59zI~
        nargc++;                                                   //~v59zI~
    }                                                              //~v59zI~
    *nargv=0;                                                      //~v59zI~
    *Ppargc=nargc;                                                 //~v59zI~
	return;                                                        //~v59zI~
}//gxe_parmchk                                                     //~v59zI~
//********************************************************         //~v59zI~
// help msg                                                        //~v59zR~
//********************************************************         //~v59zI~
void gxe_help(void)                                                //~v59zI~
{                                                                  //~v59zI~
//*********************************                                //~v59zI~
	fprintf(stdout,"gxe usage\n");                                 //~v59zR~
	fprintf(stdout,"gxe [--xxeoptions] [-xeoptions] [filename]\n");//~v59zR~
	fprintf(stdout,"  --xxe-options :\n");                         //~v59zR~
	fprintf(stdout,"    --h         : print this help.\n");        //~v59zR~
	fprintf(stdout,"   (--help      : gtk help)\n");               //~v59zI~
	fprintf(stdout,"    --?         : print this help.\n");        //~v59zR~
//  fprintf(stdout,"    --hd:dir    : help dir.\n");               //~v71AR~
//  fprintf(stdout,"                  default=$HOME/xehelp:%s\n",DEF_HELPDIR);//~v71AR~
	fprintf(stdout,"    --%s{Y|N}  : use geometry hint(specify \"n\" when window size shrinks).\n",OPT_GEOMETRY);//~varcR~
	if (Gxxestat & GXXES_DEBUGHELP)                                //~varcI~
    {                                                              //~varcI~
//    fprintf(stdout,"    --%sF      : use geometry hint for frame window.\n",OPT_GEOMETRY);//~varcR~
//    fprintf(stdout,"    --%sV      : use geometry hint for view widget.\n",OPT_GEOMETRY);//~varcR~
	fprintf(stdout,"    --%sn      : set geometry hint to baseX=n(n=0 measn no RESIZE_INC).\n",OPT_GEOMETRY);//~varcR~
	fprintf(stdout,"    --%sS      : set geometry hint at OnSize.\n",OPT_GEOMETRY);//~varcI~
    }                                                              //~varcI~
//  fprintf(stdout,"    --xxekbchk  : print key-code acceptance.\n");//~v59zR~//+vb2bR~
    fprintf(stdout,"    --xxekbchk  : print key-code acceptance(char by locale code).\n");//+vb2bI~
	fprintf(stdout,"    --xxekbchku8: print key-code acceptance(char by UTF-8).\n");//+vb2bI~
	fprintf(stdout,"  -xe-options   : option to xe (chk it by \"gxe -h\")\n");//~v59zR~
	fprintf(stdout,"  filename      : file or dir name to be opened.\n");//~v59zR~
    exit(1);                                                       //~v59zI~
}//gxe_im_init(void)                                               //~v59zI~
//********************************************************         //~v59zI~
// im init                                                         //~v59zI~
//********************************************************         //~v59zI~
void gxe_appinit(void)                                             //~v59zI~
{                                                                  //~v59zI~
//*********************************                                //~v59zI~
	Gpclipboard=gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);        //~v59zI~
	Gpclipboardp=gtk_clipboard_get(GDK_SELECTION_PRIMARY);         //~v76cI~
    return;                                                        //~v59zI~
}//gxe_appinit                                                     //~v59zR~
//********************************************************         //~v59zI~
// im init                                                         //~v59zI~
//********************************************************         //~v59zI~
void gxe_im_init(void)                                             //~v59zI~
{                                                                  //~v59zI~
//*********************************                                //~v59zI~
//  if (wxegetdbcsmode)      //no compile err?                     //~v669R~
//  if (wxegetdbcsmode())                                          //~v69uR~
		Gpimcontext=gtk_im_multicontext_new();                     //~v59zR~
    return;                                                        //~v59zI~
}//gxe_im_init(void)                                               //~v59zI~
//**************************************************************** //~v59zI~
//* printf format  nop mode                                        //~v59zI~
//**************************************************************** //~v59zI~
void dummyprintf(char *Pfmt,...)                                   //~v59zI~
{                                                                  //~v59zI~
    return;                                                        //~v59zI~
}//dummyprintf                                                     //~v59zI~
                                                                   //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
#ifdef AAA                                                         //~var8R~
//#ifndef GTK3GTK3                                                 //~var8R~
//#else                                                            //~var8R~
//**************************************************************** //~var8R~
G_DEFINE_TYPE (Gxe,gxe,GTK_TYPE_APPLICATION);//init,class_init,parent_class,..//~var8R~
//**************************************************************** //~var8R~
/* Create a new window loading a file */                           //~var8R~
void gxe_new_window (GApplication *app,                            //~var8R~
                           GFile        *file)                     //~var8R~
{                                                                  //~var8R~
	GtkWidget *window;                                             //~var8R~
//***************************                                      //~var8R~
	Ggtkappgxe=app;	//parm to create_window                        //~var8R~
	window=create_framewindow(app);                                //~var8R~
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));//~var8R~
	gtk_widget_show_all (GTK_WIDGET (window));                     //~var8R~
}                                                                  //~var8R~
                                                                   //~var8R~
                                                                   //~var8R~
//**************************************************************** //~var8R~
void gxe_activate (GApplication *application)                      //~var8R~
{                                                                  //~var8R~
	gxe_new_window (application, NULL);                            //~var8R~
}                                                                  //~var8R~
////****************************************************************//~var8R~
//void xe_open (GApplication  *application,                        //~var8R~
//                     GFile        **files,                       //~var8R~
//                     gint           n_files,                     //~var8R~
//                     const gchar   *hint)                        //~var8R~
//{                                                                //~var8R~
//    gint i;                                                      //~var8R~
                                                                   //~var8R~
//    for (i = 0; i < n_files; i++)                                //~var8R~
//        gxe_new_window (application, files[i]);                  //~var8R~
//}                                                                //~var8R~
//**************************************************************** //~var8R~
void gxe_startup(GApplication *Papp)                               //~var8R~
{                                                                  //~var8R~
//craete framewindow                                               //~var8R~
}                                                                  //~var8R~
//**************************************************************** //~var8R~
void gxe_shutdown(GApplication *Papp)                              //~var8R~
{                                                                  //~var8R~
    G_APPLICATION_CLASS(GxeParentClass)->shutdown(Papp);           //~var8R~
}                                                                  //~var8R~
//**************************************************************** //~var8R~
void gxe_init (Gxe *object)                                        //~var8R~
{                                                                  //~var8R~
                                                                   //~var8R~
}                                                                  //~var8R~
//**************************************************************** //~var8R~
void gxe_finalize (GObject *object)                                //~var8R~
{                                                                  //~var8R~
	G_OBJECT_CLASS (Gxe_parent_class)->finalize (object);          //~var8R~
}                                                                  //~var8R~
                                                                   //~var8R~
//**************************************************************** //~var8R~
void gxe_class_init (GxeClass *klass)                              //~var8R~
{                                                                  //~var8R~
	GApplicationClass *apc;                                        //~var8R~
//************************                                         //~var8R~
	apc=G_APPLICATION_CLASS(klass);                                //~var8R~
	apc->startup=gxe_startup;                                      //~var8R~
	apc->shutdown=gxe_shutdown;                                    //~var8R~
	apc->activate=gxe_activate;                                    //~var8R~
//	apc->open=gxe_open;                                            //~var8R~
	g_type_class_add_private (klass, sizeof (GxePrivate));         //~var8R~
                                                                   //~var8R~
	G_OBJECT_CLASS (klass)->finalize = gxe_finalize;               //~var8R~
}                                                                  //~var8R~
                                                                   //~var8R~
//**************************************************************** //~var8R~
Gxe *gxe_new(void)                                                 //~var8R~
{                                                                  //~var8R~
	Gxe *app;                                                      //~var8R~
	g_set_application_name("gxe");                                 //~var8R~
	app=g_object_new (gxe_get_type (),                             //~var8R~
	                     "application-id", "org.gnome.gxe",        //~var8R~
	                     "flags", G_APPLICATION_HANDLES_OPEN,      //~var8R~
	                     "register-session", TRUE,                 //~var8R~
	                     NULL);                                    //~var8R~
    return app;                                                    //~var8R~
}                                                                  //~var8R~
//#endif  //GTK3GTK3                                               //~var8R~
#else //AAA                                                        //~var8R~
//**************************************************************** //~var8R~
//*signal at register                                              //~var8R~
//**************************************************************** //~var8R~
void gxe_startup(GApplication *Papp)                               //~var8R~
{                                                                  //~var8R~
	GdkRGBA rgba=HOVERRGBA;                                        //~var8R~
//****************                                                 //~var8R~
#ifdef BBB                                                         //~var8R~
	interface_create_menu(Papp);                                   //~var8R~
#endif                                                             //~var8R~
	GphoverRGBA=gdk_rgba_copy(&rgba);                              //~var8R~
}                                                                  //~var8R~
//**************************************************************** //~var8R~
//*signal after startup                                            //~var8R~
//**************************************************************** //~var8R~
void gxe_activate (GApplication *Ppapp)                            //~var8R~
{                                                                  //~var8R~
	interface_create_window(Ppapp);                                //~var8R~
    dprintf("inhibit idle=%d\n",gtk_application_is_inhibited(GTK_APPLICATION(Ppapp),GTK_APPLICATION_INHIBIT_IDLE));//~var8R~
    dprintf("inhibit sw  =%d\n",gtk_application_is_inhibited(GTK_APPLICATION(Ppapp),GTK_APPLICATION_INHIBIT_SWITCH));//~var8R~
}                                                                  //~var8R~
#endif //AAA                                                       //~var8R~
#endif  //OPTGTK3                                                  //~var8R~
