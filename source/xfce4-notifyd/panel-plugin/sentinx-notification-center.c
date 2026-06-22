#include "sentinx-notification-center.h"
#include <xfconf/xfconf.h>
#include <common/xfce-notify-log-util.h>
#include <common/xfce-notify-log-types.h>
#include <common/xfce-notify-log-gbus.h>

typedef struct
{
    NotificationPlugin *plugin;
    gchar *id;
    GtkWidget *card;
}
SentinxNotificationDeleteData;

static GtkWidget *window = NULL;
gboolean
sentinx_toggle_dnd(
    GtkSwitch *widget,
    gboolean state,
    gpointer data

)
{
    XfconfChannel *channel;


    channel =
        xfconf_channel_get(
            "xfce4-notifyd"
        );

xfconf_channel_set_bool(
    channel,
    "/do-not-disturb",
    state
);
    g_print(
        "DND -> %s\n",
        !state ? "ON" : "OFF"
    );
return FALSE;
}
static gboolean
on_window_delete(GtkWidget *widget,
                 GdkEvent *event,
                 gpointer data)
{
    gtk_widget_hide(widget);
    return TRUE;
}

GtkWidget *
create_notification_card(
    const gchar *icon,
    const gchar *title_text,
    const gchar *message_text,
    const gchar *time_text)
{
    GtkWidget *frame;
    GtkWidget *box;
    GtkWidget *title;
    GtkWidget *message;
    GtkWidget *time;

    gchar markup[512];

    frame = gtk_frame_new(NULL);

    box = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        5
    );

    gtk_container_add(
        GTK_CONTAINER(frame),
        box
    );


    g_snprintf(
        markup,
        sizeof(markup),
        "<b>%s %s</b>",
        icon,
        title_text
    );

    title = gtk_label_new(NULL);

    gtk_label_set_markup(
        GTK_LABEL(title),
        markup
    );

    gtk_box_pack_start(
        GTK_BOX(box),
        title,
        FALSE,
        FALSE,
        5
    );

    message = gtk_label_new(message_text);

    gtk_box_pack_start(
        GTK_BOX(box),
        message,
        FALSE,
        FALSE,
        5
    );

    time = gtk_label_new(time_text);

    gtk_box_pack_start(
        GTK_BOX(box),
        time,
        FALSE,
        FALSE,
        5
    );

    return frame;
}

static void
sentinx_delete_notification(
    GtkButton *button,
    gpointer data
)
{
    SentinxNotificationDeleteData *delete_data =
        data;

    const gchar *ids[2];

    ids[0] = delete_data->id;
    ids[1] = NULL;

    xfce_notify_log_gbus_call_mark_read(
        delete_data->plugin->log,
        ids,
        NULL,
        NULL,
        NULL
    );

    gtk_widget_destroy(
        delete_data->card
    );

    g_free(delete_data->id);
    g_free(delete_data);
}


GtkWidget *
create_notification_card_from_entry(
    XfceNotifyLogEntry *entry
)
{
    gchar *body;
    gchar *summary;

    summary =
        notify_log_format_summary(
            entry->summary
        );

    body =
        notify_log_format_body(
            entry->body
        );

    GtkWidget *card =
        create_notification_card(
            "🔔",
            summary,
            body ? body : "",
            ""
        );

    g_free(summary);

    if (body)
        g_free(body);

    return card;
}
static void
sentinx_clear_all_notifications(
    GtkButton *button,
    gpointer data
)
{
    NotificationPlugin *notification_plugin =
        data;

    if (
        notification_plugin != NULL &&
        notification_plugin->log != NULL
    )
    {
        xfce_notify_log_gbus_call_clear(
            notification_plugin->log,
            NULL,
            NULL,
            NULL
        );
	if (
    notification_plugin->notif_box
)
{
    gtk_container_foreach(
        GTK_CONTAINER(
            notification_plugin->notif_box
        ),
        (GtkCallback)
        gtk_widget_destroy,
        NULL
    );
}

        g_print(
            "ALL NOTIFICATIONS CLEARED\n"
        );
    }
}

GtkWidget *
sentinx_notification_center_widget(
    NotificationPlugin *notification_plugin
)
{
    g_print("SENTINX WIDGET CREATED\n");
    GtkWidget *paned;

    GtkWidget *left_panel;
    GtkWidget *right_panel;

    GtkWidget *header;

    GtkWidget *scroll;
    GtkWidget *notif_box;

    GtkWidget *footer;
GtkWidget *dnd_row;
GtkWidget *dnd_label;
GtkWidget *dnd_switch;
    GtkWidget *btn_clear;

XfconfChannel *channel;

    GtkWidget *card;

    GtkWidget *date_label;
    GtkWidget *calendar;
    GtkWidget *events_frame;
    GtkWidget *events_label;



    paned = gtk_paned_new(
        GTK_ORIENTATION_HORIZONTAL
    );
    gtk_widget_set_size_request(
    paned,
    900,
    650
);

gtk_paned_set_position(
    GTK_PANED(paned),
    650
);

/* paned is now root widget */

    left_panel = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        10
    );

    right_panel = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        10
    );

    gtk_paned_pack1(
        GTK_PANED(paned),
        left_panel,
        TRUE,
        FALSE
    );

    gtk_paned_pack2(
        GTK_PANED(paned),
        right_panel,
        FALSE,
        FALSE
    );

    header = gtk_label_new(NULL);

    gtk_label_set_markup(
        GTK_LABEL(header),
        "<span size='x-large'><b>Notifications</b></span>"
    );

    gtk_box_pack_start(
        GTK_BOX(left_panel),
        header,
        FALSE,
        FALSE,
        10
    );

    scroll = gtk_scrolled_window_new(
        NULL,
        NULL
    );

    gtk_widget_set_vexpand(scroll, TRUE);

    gtk_box_pack_start(
        GTK_BOX(left_panel),
        scroll,
        TRUE,
        TRUE,
        0
    );

    notif_box = gtk_box_new(
        GTK_ORIENTATION_VERTICAL,
        10
    );
	if (notification_plugin != NULL)
{
    notification_plugin->notif_box =
        notif_box;
}
    gtk_container_add(
        GTK_CONTAINER(scroll),
        notif_box
    );
g_print(
    "PLUGIN=%p LOG=%p\n",
    notification_plugin,
    notification_plugin ?
        notification_plugin->log : NULL
);
    
if (
    notification_plugin != NULL &&
    notification_plugin->log != NULL
)
{
    GVariant *entriesv = NULL;
    GList *entries = NULL;
    GError *error = NULL;

    if (
        xfce_notify_log_gbus_call_list_sync(
            notification_plugin->log,
            "",
            20,
            FALSE,
            &entriesv,
            NULL,
            &error
        )
    )
    {
        entries =
            notify_log_variant_to_entries(
                entriesv
            );
	g_print(
    "ENTRIES=%d\n",
    g_list_length(entries)
);

        g_variant_unref(
            entriesv
        );

        for (
            GList *l = entries;
            l != NULL;
            l = l->next
        )
        {
XfceNotifyLogEntry *entry =
                l->data;
g_print(
    "ENTRY: %s\n",
    entry->summary
);

            card =
                create_notification_card_from_entry(
                    entry
                );
		GtkWidget *card_box;
GtkWidget *delete_button;

SentinxNotificationDeleteData *delete_data;

card_box =
    gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        5
    );

delete_button =
    gtk_button_new_with_label(
        "✕"
    );

delete_data =
    g_new0(
        SentinxNotificationDeleteData,
        1
    );

delete_data->plugin =
    notification_plugin;

delete_data->id =
    g_strdup(
        entry->id
    );

delete_data->card =
    card_box;

g_signal_connect(
    delete_button,
    "clicked",
    G_CALLBACK(
        sentinx_delete_notification
    ),
    delete_data
);

gtk_box_pack_start(
    GTK_BOX(card_box),
    card,
    TRUE,
    TRUE,
    0
);

gtk_box_pack_end(
    GTK_BOX(card_box),
    delete_button,
    FALSE,
    FALSE,
    0
);

            gtk_box_pack_start(
GTK_BOX(notif_box),
    card_box,
                FALSE,
                FALSE,
                5
            );
        }

        g_list_free_full(
            entries,
            (GDestroyNotify)
            xfce_notify_log_entry_unref
        );
    }
}

    footer = gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        10
    );

    gtk_box_pack_end(
        GTK_BOX(left_panel),
        footer,
        FALSE,
        FALSE,
        10
    );

dnd_row =
    gtk_box_new(
        GTK_ORIENTATION_HORIZONTAL,
        10
    );

dnd_label =
    gtk_label_new(
        "Do Not Disturb"
    );

dnd_switch =
    gtk_switch_new();

channel =
    xfconf_channel_get(
        "xfce4-notifyd"
    );

gtk_switch_set_active(
    GTK_SWITCH(dnd_switch),
    xfconf_channel_get_bool(
        channel,
        "/do-not-disturb",
        FALSE
    )
);

g_signal_connect(
    dnd_switch,
    "state-set",
    G_CALLBACK(sentinx_toggle_dnd),
    NULL
);

gtk_box_pack_start(
    GTK_BOX(dnd_row),
    dnd_label,
    FALSE,
    FALSE,
    0
);

gtk_box_pack_end(
    GTK_BOX(dnd_row),
    dnd_switch,
    FALSE,
    FALSE,
    0
);

gtk_box_pack_start(
    GTK_BOX(footer),
    dnd_row,
    FALSE,
    FALSE,
    5
);
    btn_clear = gtk_button_new_with_label(
        "Clear All"
    );
g_signal_connect(
    btn_clear,
    "clicked",
    G_CALLBACK(
        sentinx_clear_all_notifications
    ),
    notification_plugin
);


    gtk_box_pack_end(
        GTK_BOX(footer),
        btn_clear,
        FALSE,
        FALSE,
        5
    );

    date_label = gtk_label_new(
        "Friday\nJune 20 2026"
    );

    gtk_box_pack_start(
        GTK_BOX(right_panel),
        date_label,
        FALSE,
        FALSE,
        10
    );

    calendar = gtk_calendar_new();

    gtk_box_pack_start(
        GTK_BOX(right_panel),
        calendar,
        FALSE,
        FALSE,
        10
    );

    events_frame = gtk_frame_new(
        "Today"
    );

    events_label = gtk_label_new(
        "No Events"
    );

    gtk_container_add(
        GTK_CONTAINER(events_frame),
        events_label
    );

    gtk_box_pack_start(
        GTK_BOX(right_panel),
        events_frame,
        FALSE,
        FALSE,
        10
    );

    gtk_widget_show_all(paned);

    return paned;
}

void sentinx_notification_center_show(void)
{
    if (!window || !GTK_IS_WINDOW(window))
    {
        window = NULL;
        sentinx_notification_center_create();
    }

    gtk_widget_show(window);
    gtk_window_present(GTK_WINDOW(window));
}

GtkWidget *
sentinx_notification_center_create(void)
{
    GtkWidget *window;
    GtkWidget *content;

    window =
        gtk_window_new(
            GTK_WINDOW_TOPLEVEL
        );

g_print("SENTINX WINDOW CREATED\n");

content =
    sentinx_notification_center_widget(
	NULL
    );

    gtk_container_add(
        GTK_CONTAINER(window),
        content
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        900,
        650
    );

    gtk_widget_show_all(window);

    return window;
}
