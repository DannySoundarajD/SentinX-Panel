#include "sentinx-notification-center.h"

static GtkWidget *window = NULL;

static gboolean
on_window_delete(GtkWidget *widget,
                 GdkEvent *event,
                 gpointer data)
{
    gtk_widget_hide(widget);
    return TRUE;
}

static GtkWidget *
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

GtkWidget *sentinx_notification_center_widget(void)
{
    g_print("SENTINX WIDGET CREATED\n");
    GtkWidget *paned;

    GtkWidget *left_panel;
    GtkWidget *right_panel;

    GtkWidget *header;

    GtkWidget *scroll;
    GtkWidget *notif_box;

    GtkWidget *footer;
    GtkWidget *btn_dnd;
    GtkWidget *btn_clear;

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

    gtk_container_add(
        GTK_CONTAINER(scroll),
        notif_box
    );

    card = create_notification_card(
        "🌐",
        "WiFi Connected",
        "Connected to SentinX-5G",
        "2m ago"
    );

    gtk_box_pack_start(
        GTK_BOX(notif_box),
        card,
        FALSE,
        FALSE,
        5
    );

    card = create_notification_card(
        "🤖",
        "Ollama Started",
        "Qwen Model Loaded",
        "5m ago"
    );

    gtk_box_pack_start(
        GTK_BOX(notif_box),
        card,
        FALSE,
        FALSE,
        5
    );

    card = create_notification_card(
        "🛡",
        "Sentinel Active",
        "Monitoring System",
        "10m ago"
    );

    gtk_box_pack_start(
        GTK_BOX(notif_box),
        card,
        FALSE,
        FALSE,
        5
    );

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

    btn_dnd = gtk_button_new_with_label(
        "DND"
    );

    gtk_box_pack_start(
        GTK_BOX(footer),
        btn_dnd,
        FALSE,
        FALSE,
        5
    );

    btn_clear = gtk_button_new_with_label(
        "Clear All"
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
    sentinx_notification_center_widget();

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
