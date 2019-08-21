//*CID://+vbdhR~:                             update#=   72;       //~vbdhR~
//************************************************************************//~v51dI~
//vbdh:171123 (GTK3.10 BUG) gtk_widget_add_accelerator() dose not allow runtime change of accelerator//~vbdhI~
//vbd2:171114 (Wxe)Add SelectAll menuitem                          //~vbd2I~
//v66r:051025 (XXE) for v66m for WXE                               //~v66rI~
//v669:050826 (XXE)help support                                    //~v669I~
//vXXE:050611 new for XXE                                          //~vXXEI~
//v55z:040304 (WXE)help support                                    //~v55zI~
//v51w:030615 (WXE)icon for MDOS and Explorer                      //~v51wI~
//v51d:030517 (WXE)bitmap menu                                     //~v51dI~
//************************************************************************//~v51dI~
#ifdef EXT                                                         //~vXXEI~
    #undef EXT                                                     //~vXXEI~
    #undef INIT                                                    //~vXXEI~
#endif                                                             //~vXXEI~
#ifdef GBL_GXEMFRM                                                 //~vXXEI~
	#define EXT                                                    //~vXXEI~
	#define INIT(value)  =value                                    //~vXXEI~
#else                                                              //~vXXEI~
	#define EXT extern                                             //~vXXEI~
	#define INIT(value)                                            //~vXXEI~
#endif                                                             //~vXXEI~

#ifdef __cplusplus                                                 //~vXXEI~
class CMainFrame : public CFrameWnd
{
public:                                                            //~vXXEM~
#endif                                                             //~vXXEI~
//* public func ***********************************                //~vXXEI~
	void gxemfrm_construct(void);                                  //~vXXER~
	void gxemfrm_realize                    (GtkWidget       *Ppwidget);//~vXXEI~
	void gxemfrm_unrealize                  (GtkWidget       *widget);//~vXXEI~
	void gxemfrm_configure            (GtkWidget       *Ppwidget,  //~vXXER~
                                        GdkEventConfigure *event); //~vXXEI~
	void gxemfrm_delete            (GtkWidget  *widget,GdkEvent *event);//~vXXER~
	void gxemfrm_destroy           (GtkWidget  *widget,GdkEvent *event);//~vXXEI~
	void gxemfrm_onclose(void);                                    //~vXXEI~
	GtkWidget *gxemfrm_popupmenu_getmenuitem(int Pitemid);         //~vXXER~
	int  gxemfrm_popupmenu_getmenuitemid(int Pindex);              //~vXXER~
	int  gxemfrm_enabletoolbar(int Penterid);                      //~vXXEI~
	int  gxemfrm_updatemainmenu(int Pusemk);                       //~vXXEI~
	int  gxemfrm_Loadact(int Puseact);                             //~vXXEI~
	void gxemfrm_OnHelp(void);                                     //~v669I~
	int gxemfrm_updateFileMenu(int Popt);                          //~vbdhI~
	int gxemfrm_chkDiabledMenuid(int Popt,int Pshift,int Pkeyval); //+vbdhI~
//* public data ************************************               //~vXXER~
EXT    int       Museact;                                          //~vXXER~
EXT    int       Musemk ;                                          //~vXXER~
EXT    WXEINIDATA Mwxeinidata;                                     //~vXXER~
EXT    int Mswgetinifail;   //ini get fail                         //~vXXEI~
EXT    int Menablecopy,Menablecut,Menablepaste,Menablepastev;      //~v66rR~
EXT    int Menableselectall;                                       //~vbd2I~
EXT    GtkWidget *Mtoolbar;                                        //~v66rR~
#ifndef XXE                                                        //~vXXEI~
	virtual ~CMainFrame();                                         //~vXXEM~
	void    frmsetxemain(CWxemain *Ppm);                           //~vXXEM~
	int     enablemainmenu(void);                                  //~vXXEM~
#ifdef _DEBUG                                                      //~vXXEM~
	virtual void AssertValid() const;                              //~vXXEM~
	virtual void Dump(CDumpContext& dc) const;                     //~vXXEM~
#endif                                                             //~vXXEM~
                                                                   //~vXXEM~
//  CStatusBar  m_wndStatusBar;                                    //~vXXEM~
//  CToolBar    m_wndToolBar;                                      //~vXXEM~
                                                                   //~vXXEM~
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);           //~vXXEM~
	afx_msg void OnClose();                                        //~vXXEM~
	afx_msg void OnInitMenu(CMenu* pMenu);                         //~vXXEM~
	afx_msg void OnHelp();                                         //~vXXEM~
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
#endif	                                                           //~vXXER~
#ifdef __cplusplus                                                 //~vXXEI~
private:                                                           //~2A14I~
#endif                                                             //~vXXEI~
#ifdef GBL_GXEMFRM                                                 //~vXXEI~
//* private func ************************************              //~vXXEI~
	void gxemfrm_setwindowsize(void);                              //~vXXEI~
#ifndef XXE                                                        //~vXXEI~
	int       updatemenutext(char *Ptext,ACCEL *Ppact);            //~vXXEM~
	int       updatemainmenu(CMenu *Ppmenu);                       //~vXXEM~
	int  	  updatemainmenutext(int Pmenupos,char *Ptext,int Pusesw);//~vXXEM~
	int  appendmenu(CMenu* Ppmenu);                                //~vXXEM~
#endif                                                             //~vXXEI~
//* private data ************************************              //~vXXEI~
#ifndef XXE                                                        //~v66rM~
	void  /*ACCEL*/    *Mpact;                                     //~vXXER~
	int Mactno;                                                    //~vXXEI~
//  CWxeApp  *Mpapp;                                               //~vXXER~
//  CWxemain *Mpxemain;                                            //~vXXER~
	CBitmap Mbmsave,Mbmend,Mbmcancel,Mbmprint,Mbmcopy,Mbmcut,Mbmclear,Mbmpastei,Mbmpaster;//~v51dI~
	CBitmap Mbmexplorer,Mbmdos;                                    //~v51wR~
#endif  //XXE                                                      //~vXXEI~
#endif  //GBL                                                      //~vXXEI~
int  gxemfrm_actinit_menuitem(GtkAccelGroup *Ppag,GtkWidget *Pmenuitem,int Pkey,int Pmask);//~vbd2I~
#ifdef __cplusplus                                                 //~vXXEI~
};                                                                 //~vXXER~
#endif                                                             //~vXXEI~
