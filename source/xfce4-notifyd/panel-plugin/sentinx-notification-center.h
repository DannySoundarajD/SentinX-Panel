#ifndef SENTINX_NOTIFICATION_CENTER_H
#define SENTINX_NOTIFICATION_CENTER_H

#include <gtk/gtk.h>

GtkWidget *sentinx_notification_center_widget(void);
GtkWidget *sentinx_notification_center_create(void);
void sentinx_notification_center_show(void);
gboolean sentinx_toggle_dnd(
    GtkSwitch *widget,
    gboolean state,
    gpointer data
);
#endif
