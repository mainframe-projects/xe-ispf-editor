//*CID://+var8R~:                             update#=  187;       //+var8R~
//***************************************************************************//~v516I~
//***************************************************************************//~v516I~
// gxedlg.h                                                        //~v59zR~
//***************************************************************************//~v59zI~
//var8:140127 gtk3 suppott                                         //+var8I~
//v73t:070125 cross-hair ruler support by Shift+Ctl+lbuton         //~v73tI~
//vXXE:050611 new for XXE                                          //~vXXEI~
//***************************************************************************//~v59zI~
//***************************************************************************//~vXXEI~
#define GET_COMBOENTRYTEXT(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget; gchar *ptext;	                	\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
    	    pwidget=GTK_WIDGET(GTK_COMBO(pwidget)->entry);       \
	        ptext=(char*)gtk_entry_get_text(GTK_ENTRY(pwidget));        \
            if (ptext)   	/*const gchar, dont free  or update*/         \
            	strcpy(varname,(char*)ptext);   					 \
            else                                                 \
            	*varname=0;                                       \
        }                                                          //~vXXEI~
#define SET_CHKBOX(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;									\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(pwidget),varname);\
        }    	                                                   //~vXXEI~
#define GET_CHKBOX(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;									\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        varname=gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(pwidget));        \
        }                                                          //~vXXEI~
#define SET_SPINBUTTON(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;									\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        gtk_spin_button_set_value(GTK_SPIN_BUTTON(pwidget),(gdouble)(varname));        \
        }                                                          //~vXXEI~
#define GET_SPINBUTTON(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;									\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        varname=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(pwidget));        \
        }                                                          //~vXXEI~
#define SET_ENTRYINT(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget; char numwk[16];					\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
            sprintf(numwk,"%d",varname);                         \
	        gtk_entry_set_text(GTK_ENTRY(pwidget),numwk);        \
        }                                                          //~vXXEI~
#define SET_ENTRYTEXT(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;                					\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        gtk_entry_set_text(GTK_ENTRY(pwidget),varname);        \
            dprintf("SET_ENTRYTEXT widget=%s,value=%s\n",widgetid,varname);\
        }                                                          //~vXXEI~
#define SET_LABELTEXT(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;                					\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        gtk_label_set_text(GTK_LABEL(pwidget),varname);        \
        }                                                          //~vXXEI~
#define GET_ENTRYTEXT(parent,widgetid,varname)                    \
		{ GtkWidget *pwidget;	gchar *ptext;                	\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
	        ptext=(gchar*)gtk_entry_get_text(GTK_ENTRY(pwidget));        \
            if (ptext)   	/*const gchar, dont free  or update*/         \
		        strcpy(varname,ptext);                               \
            else                                                 \
            	*varname=0;                                       \
        }                                                          //~vXXEI~
#define SET_SENSITIVE(parent,widgetid,enable)                    \
		{ GtkWidget *pwidget;                					\
    		pwidget=lookup_widget(GTK_WIDGET(parent),widgetid);  \
			gtk_widget_set_sensitive(GTK_WIDGET(pwidget),enable); \
        }                                                          //~vXXEI~
//***************************************************************************//~v59zI~
void gxedlg_init(void);                                            //~v59zR~
//Font*********                                                    //~v59zI~
void gxedlg_font_create 				(GtkMenuItem     *menuitem,//~v59zI~
                                        gpointer         user_data);//~v59zI~
void gxedlg_Font_OnConfigure			(GtkWidget       *Pwidget, //~v59zI~
                                        GdkEventConfigure *Pevent, //~v59zI~
                                        gpointer         Puser_data);//~v59zI~
void gxedlg_Font_OnApply   				(GtkButton       *button,  //~v59zI~
                                        gpointer         user_data);//~v59zI~
void gxedlg_Font_OnOK      				(GtkButton       *button,  //~v59zI~
                                        gpointer         user_data);//~v59zI~
void gxedlg_Font_OnCancel  				(GtkButton       *button,  //~v59zI~
                                        gpointer         user_data);//~v59zI~
//Color ********                                                   //~v59zI~
void gxedlg_option_color_create 		(GtkButton     *Pbutton,   //~v59zR~
                                        gpointer         user_data);//~v59zI~
void gxedlg_option_rulercolor_create 				(GtkButton    *Pbutton,//~v73tI~
                                        gpointer         Puser_data);//~v73tI~
void gxedlg_Color_OnConfigure			(GtkWidget       *Pwidget, //~v59zI~
                                        GdkEventConfigure *Pevent, //~v59zI~
                                        gpointer         Puser_data);//~v59zI~
void gxedlg_Color_OnOK      				(GtkButton       *button,//~v59zI~
                                        gpointer         user_data);//~v59zI~
void gxedlg_Color_OnCancel  				(GtkButton       *button,//~v59zI~
                                        gpointer         user_data);//~v59zI~
//Options ********                                                 //~v59zM~
void gxedlg_option_create 				(GtkMenuItem     *menuitem,//~v59zR~
                                        gpointer         user_data);//~v59zM~
void gxedlg_option_OnOK      				(GtkButton       *button,//~v59zR~
                                        gpointer         user_data);//~v59zI~
void gxedlg_option_OnCancel  				(GtkButton       *button,//~v59zR~
                                        gpointer         user_data);//~v59zI~
void gxedlg_option_fontstyle  				(GtkButton       *Pbutton,//~v59zI~
                                        gpointer         Puser_data);//~v59zI~
void gxedlg_option_drawingarea_configure	(GtkWidget       *Ppwidget);//~v59zR~
#ifndef OPTGTK3                                                    //+var8R~
void gxedlg_option_drawingarea_expose   	(GtkWidget       *widget,//~v59zR~
                                        GdkEventExpose  *event);   //~v59zI~
#else   //OPTGTK3                                                  //+var8R~
void gxedlg_option_drawingarea_draw(GtkWidget *widget,cairo_t *Pcr);//+var8R~
#endif                                                             //+var8R~
void	gxedlg_font_create_sub			(int Pprintid,GtkWidget *Ppparent);//~vXXER~
int gxedlg_settext_fontname(int Pprintid,GtkWidget *Pparent);      //~vXXER~
int gxedlg_getfontdata(GtkWidget *Ppfontdlg,int Pprintid);         //~vXXEM~
//About   ********                                                 //~v59zR~
void gxedlg_about_create 				(GtkMenuItem     *menuitem,//~v59zR~
                                        gpointer         user_data);//~v59zI~
void gxedlg_About_OnClose   				(GtkButton       *Pbutton,//~v59zI~
                                        gpointer         Puser_data);//~v59zI~
