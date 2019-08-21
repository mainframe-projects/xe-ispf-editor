//*CID://+var8R~:                             update#=   10;       //~var8R~
//***************************************************************************//~var8I~
//var8:140127 gtk3 suppott                                         //~var8I~
//***************************************************************************//~var8I~

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#ifndef OPTGTK3                                                    //~var8R~
#include <gnome.h>
#else                                                              //~var8R~
	#include <libgnome/libgnome.h>                                 //~var8R~
	#include <gtk/gtk.h>                                           //~var8R~
#endif                                                             //~var8R~
#include "gxe.h"                                                   //~var8R~
#include "support.h"

GtkWidget*
lookup_widget                          (GtkWidget       *widget,
                                        const gchar     *widget_name)
{
  GtkWidget *parent, *found_widget;

  for (;;)
    {
      if (GTK_IS_MENU (widget))
      {                                                            //~var8R~
        parent = gtk_menu_get_attach_widget (GTK_MENU (widget));
        dprintf("lookup_widget menu parent of =%p is %p\n",widget,parent);//~var8R~
      }                                                            //~var8R~
      else
      {                                                            //~var8R~
#ifndef OPTGTK3                                                    //~var8R~
        parent = widget->parent;
#else                                                              //~var8R~
        parent = gtk_widget_get_parent(widget);                    //~var8R~
#endif                                                             //~var8R~
        dprintf("lookup_widget not menu parent of =%p is %p\n",widget,parent);//+var8R~
      }                                                            //~var8R~
      if (!parent)
      {                                                            //~var8R~
        parent = (GtkWidget*) g_object_get_data (G_OBJECT (widget), "GladeParentKey");
//      dprintf("lookup_widget object data parent of =%p is %p\n",widget,parent);//~var8R~
      }                                                            //~var8R~
      if (parent == NULL)
        break;
      widget = parent;
    }

  found_widget = (GtkWidget*) g_object_get_data (G_OBJECT (widget),
                                                 widget_name);
//dprintf("lookup_widget object data of %p is %p by %s\n",widget,found_widget,widget_name);//~var8R~
  if (!found_widget)
    g_warning ("Widget not found: %s", widget_name);
  return found_widget;
}

/* This is an internally used function to create pixmaps. */
GtkWidget*
create_pixmap                          (GtkWidget       *widget,
                                        const gchar     *filename)
{
  GtkWidget *pixmap;
  gchar *pathname;

  if (!filename || !filename[0])
      return gtk_image_new ();

  pathname = gnome_program_locate_file (NULL, GNOME_FILE_DOMAIN_APP_PIXMAP,
                                        filename, TRUE, NULL);
  if (!pathname)
    {
      g_warning (_("Couldn't find pixmap file: %s"), filename);
      return gtk_image_new ();
    }

  pixmap = gtk_image_new_from_file (pathname);
  g_free (pathname);
  return pixmap;
}

/* This is an internally used function to create pixmaps. */
GdkPixbuf*
create_pixbuf                          (const gchar     *filename)
{
  gchar *pathname = NULL;
  GdkPixbuf *pixbuf;
  GError *error = NULL;

  if (!filename || !filename[0])
      return NULL;

  pathname = gnome_program_locate_file (NULL, GNOME_FILE_DOMAIN_APP_PIXMAP,
                                        filename, TRUE, NULL);

  if (!pathname)
    {
      g_warning (_("Couldn't find pixmap file: %s"), filename);
      return NULL;
    }

  pixbuf = gdk_pixbuf_new_from_file (pathname, &error);
  if (!pixbuf)
    {
      fprintf (stderr, "Failed to load pixbuf file: %s: %s\n",
               pathname, error->message);
      g_error_free (error);
    }
  g_free (pathname);
  return pixbuf;
}

/* This is used to set ATK action descriptions. */
void
glade_set_atk_action_description       (AtkAction       *action,
                                        const gchar     *action_name,
                                        const gchar     *description)
{
  gint n_actions, i;

  n_actions = atk_action_get_n_actions (action);
  for (i = 0; i < n_actions; i++)
    {
      if (!strcmp (atk_action_get_name (action, i), action_name))
        atk_action_set_description (action, i, description);
    }
}

