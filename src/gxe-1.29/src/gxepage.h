//*CID://+var8R~:                             update#=  133;       //+var8R~
//********************************************************************//~2B09I~
//var8:140127 gtk3 suppott                                         //+var8I~
//vamt:131015 (GtkPrint)accept minus value of margin to adjust origin for each printer's paper folder shift attachment.(case of that b5 origin is relativ to a4 origin)//~vamtI~
//vamb:131002 re-draw HWmargin when form changed                   //~vambI~
//vam1:130915 sometime miss to initial screen drawing by the reason of cupsenumprinter lose control//~vam1I~
//            and signal:onsize by resizehint intercept xxemain_init process;//~vam1I~
//            so call enumprinter after xxemaini init end          //~vam1I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//va6y:000706 CUPs default printer is not same as gnome default    //~va20I~
//va20:091125 (UTF8)UTF8 full support(display utf8 also unprintable as locale code)//~va20I~
//vXXE:050611 new for XXE                                          //~vXXEI~
//v62W:050422 (WXE)maximum cell height definition for small doc    //~v62WI~
//v55D:040309 (WXE)popup help for dialog control                   //~v55DI~
//v51h:030525 (WXE)col/row by font size specification              //~3525I~
//********************************************************************//~3525I~
#define MARGIN_PREVIEWBOX    4  //8    //preview box border margin //~vXXER~
#define MARGIN_FORM_CLIP     0    //10mm form minimum margin       //~vXXER~
#define PRINTCOL_MIN         0    //print page column minimum      //~3525I~
//#define PRINTCOL_MAX         500  //print page column maximum      //~3525R~//~va20R~
#define PRINTROW_MIN         0    //print page row    minimum      //~3525I~
#define PRINTROW_MAX         500  //print page row    maximum      //~3525R~
#define PRINTFONTSZH_MIN      2    //print page fontsz minimum     //~3608R~
#define PRINTFONTSZH_MAX     999   //print page fontsz maximum     //~3601R~
#define PRINTFONTSZW_MIN      0    //print page fontsz minimum     //~3525I~
#define PRINTFONTSZW_MAX     999   //print page fontsz maximum     //~3601R~
#define PRINTCELLSZH_MIN      0    //print page fontsz minimum     //~v51hI~
#define PRINTCELLSZH_MAX     999   //print page fontsz maximum     //~v51hI~
#define PRINTCELLSZW_MIN      0    //print page fontsz minimum     //~v51hI~
#define PRINTCELLSZW_MAX     999   //print page fontsz maximum     //~v51hI~
#define PRINTCELLSZHMAX_MIN      0    //print page cell height max //~v62WI~
#define PRINTCELLSZHMAX_MAX     999   //print page cell height max //~v62WI~
//********************************************************************//~2B09I~
void gxepage_init(void);                                           //~vXXEI~
#ifdef GTKPRINT                                                    //~vam1I~
	void gxepage_init2(void);                                      //~vam1I~
#endif   //!GTKPRINT                                               //~vam1I~
void gxepage_fontstyle(void);                                      //~vXXEI~
void gxepage_OnPreview(void);                                      //~vXXEI~
void gxepage_OnPreviewNextpage(void);                              //~vXXEI~
void gxepage_OnPreviewprevpage(void);                              //~vXXER~
void gxepage_OnPreviewprtscr(void);                                //~vXXEI~
void gxepage_OnPrint(void);                                        //~vXXEI~
void gxepage_OnPrtscr(void);                                       //~vXXEI~
void gxepage_OnOk(void);                                           //~vXXEI~
void gxepage_OnCancel(void);                                       //~vXXEI~
void gxepage_create	(GtkMenuItem     *Pmenuitem,                   //~vXXER~
                                        gpointer         Puser_data);//~vXXEI~
void gxepage_OnCheckHeader(void);                                  //~vXXEI~
void gxepage_OnCheckFooter(void);                                  //~vXXEI~
void gxepage_OnCheckpfontsz(void);                                 //~vXXEI~
void gxepage_OnCheck2p(void);                                      //~vXXEI~
void gxepage_OnChangeEditCurpage(void);                            //~vXXEI~
void gxepage_fontstyle(void);                                      //~vXXEI~
void gxepage_Font_OnOK(void);                                      //~vXXER~
void gxepage_Font_OnApply(void);                                   //~vXXEI~
int  gxepage_prtgetformsz(int Plandscape,char *Pformtype,int *Ppwidth,int *Ppheight);//~vXXER~
#ifndef OPTGTK3                                                    //+var8R~
void gxepage_OnChanged_ComboPrinter(GtkEditable *editable,gpointer user_data);//~va20I~
#else   //OPTGTK3                                                  //+var8R~
void gxepage_OnChanged_ComboPrinter(GtkComboBox *Ppcombo,gpointer user_data);//+var8R~
#endif                                                             //+var8R~
#ifdef GTKPRINT                                                    //~vam0I~
int gxepage_err_nocupsprinter(void);                               //~vam0I~
void gxepage_papershift(int *Pporgx,int *Pporgy);                  //~vamtR~
void gxepage_savemarginshift(WXEINIDATA *Pwxei);                   //~vamtI~
#endif                                                             //~vam0I~
#ifndef OPTGTK3                                                    //+var8R~
void gxepage_OnChanged_ComboForm(GtkEditable *editable,gpointer user_data);//~vambI~
#else   //OPTGTK3                                                  //+var8R~
	void gxepage_OnChanged_ComboForm(GtkComboBox *Ppcombo,gpointer user_data);//+var8R~
	void gxepage_previewarea_draw(GtkWidget *Ppwidget,cairo_t *Pcr);//+var8R~
#endif                                                             //+var8R~
//********************************************************************//~vXXEI~
	int		Mcurpage;                                              //~vXXEM~
#ifndef XXE                                                        //~vXXEI~
};
#endif                                                             //~vXXEI~
