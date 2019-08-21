//*CID://+vbd2R~:                             update#=  152;       //+vbd2R~
//***************************************************************************//~v516I~
// gxeview.h                                                       //~v59zR~
//***************************************************************************//~v59zI~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //+vbd2I~
//var8:140127 gtk3 suppott                                         //~var8I~
//v71s:061022 (WXE/XXE)err msg when drag canceled by mouse lb release//~v71sI~
//v685:060322 dnd support "file copy into the dir slected" and even in inter-split-screen.//~v685I~
//v66p:051026 (XXE)std paste support                               //~v66pI~
//vXXE:050611 new for XXE                                          //~vXXEI~
//*wxeview ******************************************************************//~v59zI~
void gxeview_realize                    (GtkWidget       *widget); //~v59zI~
void gxeview_unrealize                  (GtkWidget       *widget); //~v59zI~
int gxeview_focus_in             (GtkWidget       *widget,         //~v59zI~
                                        GdkEventFocus   *event);   //~v59zI~
int gxeview_focus_out            (GtkWidget       *widget,         //~v59zI~
                                        GdkEventFocus   *event);   //~v59zI~
void gxeview_configure            (GtkWidget       *widget,        //~v59zI~
                                        GdkEventConfigure *event); //~v59zI~
#ifndef OPTGTK3                                                    //~var8R~
void gxeview_expose               (GtkWidget       *widget,        //~v59zI~
                                        GdkEventExpose  *event);   //~v59zI~
#else   //OPTGTK3                                                  //~var8R~
	void gxeview_draw(GtkWidget *Ppwidget,cairo_t *Pcr);           //~var8R~
#endif                                                             //~var8R~
int gxeview_buttondown           (GtkWidget       *widget,         //~v59zI~
                                        GdkEventButton  *event);   //~v59zI~
int gxeview_buttonup             (GtkWidget       *widget,         //~v59zR~
                                        GdkEventButton  *event);   //~v59zI~
int gxeview_mousewheel             (GtkWidget       *Pwidget,      //~v59zI~
                                        GdkEventScroll  *Pevent);  //~v59zI~
int gxeview_OnKeyDown            (GtkWidget       *widget,         //~vXXER~
                                        GdkEventKey     *event);   //~v59zI~
int gxeview_OnKeyUp              (GtkWidget       *widget,         //~vXXER~
                                        GdkEventKey     *event);   //~v59zI~
int gxeview_leave                (GtkWidget       *widget,         //~v59zI~
                                        GdkEventCrossing *event);  //~v59zI~
int gxeview_enter                (GtkWidget       *widget,         //~v59zI~
                                        GdkEventCrossing *event);  //~v59zI~
int gxeview_motion               (GtkWidget       *widget,         //~v59zI~
                                        GdkEventMotion  *event);   //~v59zI~
void gxeview_dragbegin              (GdkDragContext  *Ppcontext);  //~v71sI~
void gxeview_dragdataget              (GdkDragContext  *Ppcontext, //~v59zI~
                                        GtkSelectionData *Ppseldata);//~v59zR~
void gxeview_dragend              (GdkDragContext  *Ppcontext);    //~v59zR~
void gxeview_OnUpdateEditPaste(GtkMenuItem *Ppmenuid);             //~vXXER~
void gxeview_OnUpdateEditPasteRep(GtkMenuItem *Ppmenuid);          //~vXXER~
void gxeview_OnUpdateEditPasteV(GtkMenuItem *Ppmenuid);            //~v66pI~
void gxeview_OnUpdateEditCopy(GtkMenuItem *Ppmenuid);              //~vXXER~
void gxeview_OnUpdateEditCut(GtkMenuItem *Ppmenuid);               //~vXXER~
void gxeview_OnUpdateEditClear(GtkMenuItem *Ppmenuid);             //~vXXER~
//**********                                                       //~v59zI~
int  gxeview_OnFilePrint(void);                                    //~vXXER~
void gxeview_OnFileScrprt(void);                                   //~vXXEI~
void gxeview_OnOk(void);                                           //~v59zR~
void gxeview_OnEditSelectAll(void);                                //+vbd2I~
void gxeview_OnEditPasteIns(void);                                 //~v59zR~
void gxeview_OnEditPasteRep(void);                                 //~v59zR~
void gxeview_OnEditPasteV(void);                                   //~v66pI~
void gxeview_OnEditCopy(void);                                     //~v59zR~
void gxeview_OnEditCut(void);                                      //~v59zR~
void gxeview_OnEditClear(void);                                    //~v59zR~
void gxeview_OnFileScrprt(void);                                   //~v59zR~
void gxeview_OnEditEnd(void);                                      //~v59zR~
void gxeview_OnEditCancel(void);                                   //~v59zR~
void gxeview_OnFileDos(void);                                      //~v59zR~
void gxeview_OnEditExplorer(void);                                 //~v59zR~
void gxeview_OnFileOpenwith(void);                                 //~v59zR~
void gxeview_OnExit(void);                                         //~v59zI~
//***** wxedlg *************************************************   //~v59zI~
void gxeview_OnOptions						(GtkMenuItem     *menuitem,//~v59zM~
                                        gpointer         user_data);//~v59zM~
void gxeview_OnPageSetup               (GtkMenuItem     *menuitem, //~v59zR~
                                        gpointer         user_data);//~v59zI~
gboolean gxeview_clientevent(GtkWidget       *widget,              //~v685I~
                             GdkEventClient  *event,               //~v685I~
                             gpointer         user_data);          //~v685I~
//******************************************************           //~v59zI~
void gxeview_fillmainwindow(void);                                 //~v59zM~
