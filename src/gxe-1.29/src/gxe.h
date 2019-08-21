//*CID://+vbj2R~:                             update#=  278;       //+vbj2R~
//***************************************************************************//~v59zI~
//vbj2:180424 popup menu on cmd history list                       //+vbj2I~
//vbdh:171123 (GTK3.10 BUG) gtk_widget_add_accelerator() dose not allow runtime change of accelerator//~vbdhI~
//vb7v:170128 (gxe:GTK3 BUG)DragDrop hung                          //~vb7vI~
//vb2b:160119 (gxe)new --xxekbchku8 option to print utf8 char      //~vb2bI~
//var8:140127 gtk3 suppott                                         //~var8I~
//vam7:130929 add print with ligature(also for gnomeprint)         //~vam7I~
//vam0:130911 for distro removed gnome-print,use GTKprint          //~vam0I~
//v780:080212 syntaxhighlight support (SYN cmd,C+s func key)       //~v780I~
//v76c:070617 (XXE)paste from PRIMARY clipboard by middle button down//~v76cI~
//v73t:070125 cross-hair ruler support by Shift+Ctl+lbuton         //~v73tI~
//v71A:061030 Use HtmlHelp;Winhelp is deprecated at Vista;XP english ersion cannot read .hlp by the readson of codepage unsupported//~v71AI~
//v66a:050827 (XXE)printf used,so change to dprintf which change to nop by DUMMYPRINTF//~v66aI~
//v669:050826 (XXE)help support                                    //~v66aI~
//vX03:050729 force monospacefor the case sbcs is monospace but dbcs is not//~vX03I~
//***************************************************************************//~v59zI~
// gxe.h                                                           //~v59zI~
//***************************************************************************//~v59zI~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
	#define GdkGC cairo_t                                          //~var8R~
	#define GdkPixmap cairo_surface_t                              //~var8R~
	#define GdkColormap GdkVisual                                  //~var8R~
	#define GtkObject   GObject                                    //~var8R~
	#define GdkEventClient XClientMessageEvent                     //~var8R~
	#define GtkFontSelectionDialog GtkFontChooserDialog            //~var8R~
	#define GtkFontSelection      GtkFontChooser                   //~var8R~
	#define GdkColormap GdkVisual                                  //~var8R~
	#define gdk_colormap_get_system  gdk_visual_get_system         //~var8R~
	#define GTK_OBJECT G_OBJECT                                    //~var8R~
    #define gnome_canvas_new gtk_drawing_area_new                  //~var8R~
    #define gtk_widget_ref    g_object_ref                         //~var8R~
    #define gtk_widget_unref  g_object_unref                       //~var8R~
    #define gtk_combo_new  gtk_combo_box_text_new                  //~var8R~
	#define GTK_COMBO  GTK_COMBO_BOX_TEXT                          //~var8R~
                                                                   //~var8R~
    typedef enum                                                   //~var8R~
    {                                                              //~var8R~
      GDK_LINE_SOLID,                                              //~var8R~
      GDK_LINE_ON_OFF_DASH,                                        //~var8R~
      GDK_LINE_DOUBLE_DASH                                         //~var8R~
    } GdkLineStyle;                                                //~var8R~
                                                                   //~var8R~
    typedef enum                                                   //~var8R~
    {                                                              //~var8R~
      GDK_CAP_NOT_LAST,                                            //~var8R~
      GDK_CAP_BUTT,                                                //~var8R~
      GDK_CAP_ROUND,                                               //~var8R~
      GDK_CAP_PROJECTING                                           //~var8R~
    } GdkCapStyle;                                                 //~var8R~
                                                                   //~var8R~
    typedef enum                                                   //~var8R~
    {                                                              //~var8R~
      GDK_JOIN_MITER,                                              //~var8R~
      GDK_JOIN_ROUND,                                              //~var8R~
      GDK_JOIN_BEVEL                                               //~var8R~
    } GdkJoinStyle;                                                //~var8R~
                                                                   //~var8R~
    typedef enum                                                   //~var8R~
    {                                                              //~var8R~
      GDK_GC_FOREGROUND    = 1 << 0,                               //~var8R~
      GDK_GC_BACKGROUND    = 1 << 1,                               //~var8R~
      GDK_GC_FONT          = 1 << 2,                               //~var8R~
      GDK_GC_FUNCTION      = 1 << 3,                               //~var8R~
      GDK_GC_FILL          = 1 << 4,                               //~var8R~
      GDK_GC_TILE          = 1 << 5,                               //~var8R~
      GDK_GC_STIPPLE       = 1 << 6,                               //~var8R~
      GDK_GC_CLIP_MASK     = 1 << 7,                               //~var8R~
      GDK_GC_SUBWINDOW     = 1 << 8,                               //~var8R~
      GDK_GC_TS_X_ORIGIN   = 1 << 9,                               //~var8R~
      GDK_GC_TS_Y_ORIGIN   = 1 << 10,                              //~var8R~
      GDK_GC_CLIP_X_ORIGIN = 1 << 11,                              //~var8R~
      GDK_GC_CLIP_Y_ORIGIN = 1 << 12,                              //~var8R~
      GDK_GC_EXPOSURES     = 1 << 13,                              //~var8R~
      GDK_GC_LINE_WIDTH    = 1 << 14,                              //~var8R~
      GDK_GC_LINE_STYLE    = 1 << 15,                              //~var8R~
      GDK_GC_CAP_STYLE     = 1 << 16,                              //~var8R~
      GDK_GC_JOIN_STYLE    = 1 << 17                               //~var8R~
    } GdkGCValuesMask;                                             //~var8R~
                                                                   //~var8R~
    typedef enum                                                   //~var8R~
    {                                                              //~var8R~
      GDK_COPY,                                                    //~var8R~
      GDK_INVERT,                                                  //~var8R~
      GDK_XOR,                                                     //~var8R~
      GDK_CLEAR,                                                   //~var8R~
      GDK_AND,                                                     //~var8R~
      GDK_AND_REVERSE,                                             //~var8R~
      GDK_AND_INVERT,                                              //~var8R~
      GDK_NOOP,                                                    //~var8R~
      GDK_OR,                                                      //~var8R~
      GDK_EQUIV,                                                   //~var8R~
      GDK_OR_REVERSE,                                              //~var8R~
      GDK_COPY_INVERT,                                             //~var8R~
      GDK_OR_INVERT,                                               //~var8R~
      GDK_NAND,                                                    //~var8R~
      GDK_NOR,                                                     //~var8R~
      GDK_SET                                                      //~var8R~
    } GdkFunction;                                                 //~var8R~
                                                                   //~var8R~
    typedef struct _GdkGCValues {                                  //~var8R~
        GdkColor foreground;                                       //~var8R~
    	int line_width;                                            //~var8R~
        GdkLineStyle line_style;                                   //~var8R~
    } GdkGCValues;                                                 //~var8R~
                                                                   //~var8R~
//  #define GDK_DISPLAY() GDK_DISPLAY_XDISPLAY(gdk_display_get_default())//~var8R~
    #define XEVENT_CLIENT_MSG_TYPE  "gxeAtom"                      //~var8R~
#endif                                                             //~var8R~
#ifdef DUMMYPRINTF                                                 //~vX03R~
	#define dprintf dummyprintf                                    //~v66aR~
#else                                                              //~v66aI~
	#define dprintf printf                                         //~v66aI~
#endif                                                             //~vX03M~
#define XXEPGMID     "gxe"                                         //~v59zR~
#ifdef GBL_GXE                                                     //~v59zI~
	#define GXE_EXTERN                                             //~v59zI~
    #define INITVAL(val) =val                                      //~v59zR~
#else                                                              //~v59zI~
	#define GXE_EXTERN extern                                      //~v59zI~
    #define INITVAL(val)                                           //~v59zI~
#endif                                                             //~v59zI~
//************************************************************     //~v59zI~
typedef struct _FONTDATA {                                         //~v59zM~
					gchar                 *FDfontname;             //~v59zM~
					PangoFontDescription  *FDfontdesc;             //~v59zM~
                  } FONTDATA , *PFONTDATA;                         //~v59zM~
#define FONTDATASZ sizeof(FONTDATA)                                //~v59zM~
#define XXE_MAXFONTFACE 4                                          //~v780I~
		PangoFontDescription  *Gsynfontdesc[XXE_MAXFONTFACE];      //~v780I~
typedef struct _COLORDATA {                                        //~v59zM~
					int                   CDstatus;                //~v59zR~
#define CDST_RGB       1  //RGB is valid                           //~v59zI~
#define CDST_PIXEL     2  //collor alloced                         //~v59zI~
					GdkColor              CDcolor;                 //~v59zM~
                  } COLORDATA , *PCOLORDATA;                       //~v59zM~
#define COLORDATASZ sizeof(COLORDATA)                              //~v59zM~
#define MAX_PALETTE 256                                            //~v59zI~
//************************************************************     //~v59zI~
GXE_EXTERN  GtkWidget *Gpframe;                                    //~v59zR~
GXE_EXTERN  GtkWidget *Gpview;                                     //~v59zR~
GXE_EXTERN  GdkPixmap *Gppixmap,*Gppixmapprtscr,*Gppixmappreview;  //~v59zR~
#ifdef GTKPRINT                                                    //~vam0I~
GXE_EXTERN  GdkPixmap *GppixmapGtkPrint;                           //~vam0I~
#endif   //!GTKPRINT                                               //~vam0I~
GXE_EXTERN  GdkGC     *Gpgc,*Gpprtgc,*Gpgcpreview;                 //~v59zR~
#ifdef GTKPRINT                                                    //~vam0I~
GXE_EXTERN  GdkGC     *GpgcGtkPrint;                               //~vam0I~
#endif   //!GTKPRINT                                               //~vam0I~
GXE_EXTERN  GdkGC     *Gpgccsr;     //caret display                //~v59zR~
GXE_EXTERN  GdkGC     *Gpgcim;      //im preedit                   //~v59zI~
GXE_EXTERN  GdkGC     *Gpgcruler;   //ruler                        //~v73tI~
GXE_EXTERN  GdkColormap *Gpcolormap;                               //~v59zI~
GXE_EXTERN  GdkColor   Gxxepalette[MAX_PALETTE];                   //~v59zR~
#define COLOR_GRAY    {0,0x8888,0x8888,0x8888}                     //~v59zR~
#define COLOR_WHITE   {0,0xffff,0xffff,0xffff}                     //~v59zI~
#define COLOR_BLACK   {0,0x0000,0x0000,0x0000}                     //~v59zR~
GXE_EXTERN  GdkColor   Gxxesynpalette[16];                         //~v780R~
GXE_EXTERN  GdkColor   Gprintbg  INITVAL(COLOR_WHITE);             //~v59zI~
GXE_EXTERN  GdkColor   Gprintfg  INITVAL(COLOR_BLACK);             //~v59zI~
GXE_EXTERN  GdkColor   Gpreviewbg  INITVAL(COLOR_GRAY);            //~v59zI~
GXE_EXTERN  GdkColor   Gcsrcolor INITVAL(COLOR_GRAY);              //~v59zR~
GXE_EXTERN  GdkColor   Gimbgcolor INITVAL(COLOR_WHITE);            //~v59zR~
GXE_EXTERN  GdkColor   Gimfgcolor INITVAL(COLOR_BLACK);            //~v59zR~
GXE_EXTERN  GdkColor   Grulerfg;                                   //~v73tI~
GXE_EXTERN  PangoLayout *Gplayout,*Gplayoutpreview;                //~v59zR~
#ifdef GTKPRINT                                                    //~vam0I~
GXE_EXTERN  PangoLayout *GplayoutGtkPrint;                         //~vam0I~
GXE_EXTERN  PangoLayout *GplayoutGtkPrintScr;                      //~vam0I~
#else                                                              //~vam7I~
GXE_EXTERN  PangoLayout *GplayoutGnomePrint;                       //~vam7I~
#endif   //!GTKPRINT                                               //~vam0I~
GXE_EXTERN  PangoContext *Gppangocontext;                          //~v59zR~
GXE_EXTERN  PangoLanguage *Gppangolang;                            //~v59zR~
GXE_EXTERN  FONTDATA  Gfontdata[2];                                //~v59zR~
GXE_EXTERN  COLORDATA Gcolordata;                                  //~v59zR~
                                                                   //~v59zI~
GXE_EXTERN  GtkClipboard *Gpclipboard;                             //~v59zR~
GXE_EXTERN  GtkClipboard *Gpclipboardp;    //PRIMARY clipboard     //~v76cI~
GXE_EXTERN  GtkIMContext *Gpimcontext;                             //~v59zI~
GXE_EXTERN  int           Gxxeopt;                                 //~v59zI~
#define     GXXEOPT_KBCHK  0x01                                    //~v59zI~
#define     GXXEOPT_KBCHKU8 0x02  /*with GXXEOPT_KBCHK*/           //~vb2bR~
GXE_EXTERN  GdkDragContext  *Gpsourcedragcontext;                  //~v59zI~
GXE_EXTERN  GtkWidget *Gppopupmenu;                                //~v59zI~
GXE_EXTERN  GtkWidget *GppopupmenuCHL;                             //+vbj2I~
#ifndef NOPRINT                                                    //~vam0R~
	#ifdef GTKPRINT                                                //~vam0R~
GXE_EXTERN  GtkPrintContext   *Gpgtkprtctxt;                       //~vam0R~
GXE_EXTERN  GtkPrintOperation *Gpgtkpo;                            //~vam0I~
GXE_EXTERN  GtkPrintSettings  *Gpgtkps;                            //~vam0I~
#define DEFAULT_PRINTER_UNIT  GTK_UNIT_POINTS                      //~vam0R~
	#else                                                          //~vam0R~
GXE_EXTERN  GnomePrintConfig *Gpprtconf;                           //~v59zI~
GXE_EXTERN  GnomePrintContext *Gpprtctxt;                          //~v59zI~
	#endif                                                         //~vam0R~
#endif                                                             //~vam0I~
GXE_EXTERN  PangoAttrList  *Gppangoattrlist;                       //~v59zI~
#ifdef GTKPRINT                                                    //~vam0I~
GXE_EXTERN  PangoAttrList  *GppangoattrlistGtkPrint;               //~vam0I~
#endif   //!GTKPRINT                                               //~vam0I~
GXE_EXTERN  PangoAttrList  *Gppangoattrlistscreen;                 //~vX03I~
//GXE_EXTERN  char *Ghelpdir;                                      //~v71AR~
#define DEF_HELPDIR "/usr/local/share/gnome/help/xxe"              //~v669R~
                                                                   //~v59zI~
#ifndef XXE                                                        //~v59zI~
GXE_EXTERN  void *Mppdevmode;                                      //~v59zM~
GXE_EXTERN  int Mappinitsw;                                        //~v59zM~
GXE_EXTERN  int Mshowmaxsw; //at init CMainfrm set from ini file   //~v59zM~
#endif                                                             //~v59zI~
#ifndef OPTGTK3                                                    //~var8R~
#else   //OPTGTK3                                                  //~var8R~
GXE_EXTERN  GdkGC *GpgcOnDraw; //cairo_t at callback "draw"        //~var8R~
GXE_EXTERN  GdkRGBA *GphoverRGBA;                                  //~var8R~
#if GTK_CHECK_VERSION(3,10,0)                                      //~vbdhI~
	GXE_EXTERN  GtkAccelGroup *Gpag;                               //~vbdhI~
#endif                                                             //~vbdhR~
#ifndef YYY                                                        //~vb7vR~
//*request_contennts callback data                                 //~vb7vR~
#define  GCB_MAXUD  8                                              //~vb7vR~
GXE_EXTERN  int          Gcb_status;            //clibpoard filename//~vb7vR~
GXE_EXTERN  char         Gcb_userdataReq[GCB_MAXUD+1];        //uclipboard_getfileselection() caller set//~vb7vR~
#endif	//!YYY                                                     //~vb7vR~
#endif                                                             //~var8R~
//***************************************************************************//~v59zI~
void gxe_init(int argc,char *arg[]);                               //~v59zR~
void dummyprintf(char *Pfmt,...);	//sto set printf nop           //~v59zI~
                                                                   //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
#else                                                              //~var8R~
#ifdef AAA                                                         //~var8R~
//#ifdef GTK3GTK3                                                  //~var8R~
//***************************************************************************//~var8R~
#ifndef _GTK3GXE                                                   //~var8R~
#define _GTK3GXE                                                   //~var8R~
                                                                   //~var8R~
G_BEGIN_DECLS                                                      //~var8R~
                                                                   //~var8R~
#define GXE_TYPE_APPLICATION             (gxe_get_type ())         //~var8R~
#define GXE_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GXE_TYPE_APPLICATION, Gxe))//~var8R~
#define GXE_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GXE_TYPE_APPLICATION, GxeClass))//~var8R~
#define GXE_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GXE_TYPE_APPLICATION))//~var8R~
#define GXE_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GXE_TYPE_APPLICATION))//~var8R~
#define GXE_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GXE_TYPE_APPLICATION, GxeClass))//~var8R~
                                                                   //~var8R~
typedef struct _GxeClass GxeClass;                                 //~var8R~
typedef struct _Gxe Gxe;                                           //~var8R~
typedef struct _GxePrivate GxePrivate;                             //~var8R~
                                                                   //~var8R~
struct _GxeClass                                                   //~var8R~
{                                                                  //~var8R~
	GtkApplicationClass parent_class;                              //~var8R~
};                                                                 //~var8R~
                                                                   //~var8R~
struct _Gxe                                                        //~var8R~
{                                                                  //~var8R~
	GtkApplication parent_instance;                                //~var8R~
                                                                   //~var8R~
	GxePrivate *priv;                                              //~var8R~
                                                                   //~var8R~
};                                                                 //~var8R~
                                                                   //~var8R~
GType gxe_get_type (void) G_GNUC_CONST;                            //~var8R~
Gxe *gxe_new (void);                                               //~var8R~
                                                                   //~var8R~
Gxe *Ggtkappgxe;                                                   //~var8R~
G_END_DECLS                                                        //~var8R~
                                                                   //~var8R~
#endif /* _APPLICATION_H_ */                                       //~var8R~
//#endif //GTK3GTK3                                                //~var8R~
#else    //AAA                                                     //~var8R~
GApplication *Ggtkappgxe;                                          //~var8R~
void gxe_startup(GApplication *app);                               //~var8R~
void gxe_activate(GApplication *app);                              //~var8R~
//void gxeregister_stock_icons (void);                             //~var8R~
#endif   //AAA                                                     //~var8R~
#endif	//OPTGTK3                                                  //~var8R~
