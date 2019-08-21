//*CID://+var8R~:                             update#=    2;       //+var8R~
//**************************************************************** //+var8I~
//var8:140127 gtk3 suppott                                         //+var8I~
//**************************************************************** //+var8I~

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#ifndef OPTGTK3                                                    //+var8R~
#include <gnome.h>
#endif                                                             //+var8R~

#undef Q_
#ifdef ENABLE_NLS
#  define Q_(String) g_strip_context ((String), gettext (String))
#else
#  define Q_(String) g_strip_context ((String), (String))
#endif


/*
 * Public Functions.
 */

/*
 * This function returns a widget in a component created by Glade.
 * Call it with the toplevel widget in the component (i.e. a window/dialog),
 * or alternatively any widget in the component, and the name of the widget
 * you want returned.
 */
GtkWidget*  lookup_widget              (GtkWidget       *widget,
                                        const gchar     *widget_name);



/*
 * Private Functions.
 */

/* This is used to create the pixmaps used in the interface. */
GtkWidget*  create_pixmap              (GtkWidget       *widget,
                                        const gchar     *filename);

/* This is used to create the pixbufs used in the interface. */
GdkPixbuf*  create_pixbuf              (const gchar     *filename);

/* This is used to set ATK action descriptions. */
void        glade_set_atk_action_description (AtkAction       *action,
                                              const gchar     *action_name,
                                              const gchar     *description);

