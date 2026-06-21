#ifndef SENTINX_NOTIFICATION_CENTER_H
#define SENTINX_NOTIFICATION_CENTER_H

#include <gtk/gtk.h>
#include <common/xfce-notify-log-types.h>
#include "notification-plugin.h"

GtkWidget *
create_notification_card_from_entry(
    XfceNotifyLogEntry *entry
);

GtkWidget *
sentinx_notification_center_widget(
    NotificationPlugin *notification_plugin
);
GtkWidget *sentinx_notification_center_create(void);
void sentinx_notification_center_show(void);
gboolean sentinx_toggle_dnd(
    GtkSwitch *widget,
    gboolean state,
    gpointer data
);
#endif
