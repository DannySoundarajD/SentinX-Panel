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

GtkWidget *sentinx_notification_center_create(void)
{
    GtkWidget *main_box;
    GtkWidget *paned;

    GtkWidget *left_panel;
    GtkWidget *right_panel;

    GtkWidget *header;

    GtkWidget *scroll;
    GtkWidget *notif_box;

    GtkWidget *footer;
    GtkWidget *btn_dnd;
    GtkWidget *btn_clear;

    GtkWidget *card1;
    GtkWidget *card2;

    GtkWidget *card1_box;
    GtkWidget *card2_box;

    GtkWidget *title;
    GtkWidget *desc;

    GtkWidget *date_label;
    GtkWidget *calendar;
    GtkWidget *events_frame;
    GtkWidget *events_label;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    g_signal_connect(
        window,
        "delete-event",
        G_CALLBACK(on_window_delete),
        NULL
    );

    gtk_window_set_title(
        GTK_WINDOW(window),
        "SentinX Notification Center"
    );

    gtk_window_set_default_size(
        GTK_WINDOW(window),
        900,
        650
    );

    main_box =
        gtk_box_new(
            GTK_ORIENTATION_VERTICAL,
            0
        );

    gtk_container_add(
        GTK_CONTAINER(window),
        main_box
    );

    paned =
        gtk_paned_new(
            GTK_ORIENTATION_HORIZONTAL
        );

    gtk_box_pack_start(
        GTK_BOX(main_box),
        paned,
        TRUE,
        TRUE,
        0
    );

    left_panel =
        gtk_box_new(
            GTK_ORIENTATION_VERTICAL,
            10
        );

    right_panel =
        gtk_box_new(
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

    scroll =
        gtk_scrolled_window_new(
            NULL,
            NULL
        );

    gtk_widget_set_vexpand(
        scroll,
        TRUE
    );

    gtk_box_pack_start(
        GTK_BOX(left_panel),
        scroll,
        TRUE,
        TRUE,
        0
    );

    notif_box =
        gtk_box_new(
            GTK_ORIENTATION_VERTICAL,
            10
        );

    gtk_container_add(
        GTK_CONTAINER(scroll),
        notif_box
    );

    card1 = gtk_frame_new(NULL);

    gtk_box_pack_start(
        GTK_BOX(notif_box),
        card1,
        FALSE,
        FALSE,
        5
    );

    card1_box =
        gtk_box_new(
            GTK_ORIENTATION_VERTICAL,
            5
        );

    gtk_container_add(
        GTK_CONTAINER(card1),
        card1_box
    );

    title =
        gtk_label_new(
            "🌐 WiFi Connected"
        );

    gtk_box_pack_start(
        GTK_BOX(card1_box),
        title,
        FALSE,
        FALSE,
        5
    );

    desc =
        gtk_label_new(
            "Connected to SentinX-5G"
        );

    gtk_box_pack_start(
        GTK_BOX(card1_box),
        desc,
        FALSE,
        FALSE,
        5
    );

    card2 = gtk_frame_new(NULL);

    gtk_box_pack_start(
        GTK_BOX(notif_box),
        card2,
        FALSE,
        FALSE,
        5
    );

    card2_box =
        gtk_box_new(
            GTK_ORIENTATION_VERTICAL,
            5
        );

    gtk_container_add(
        GTK_CONTAINER(card2),
        card2_box
    );

    title =
        gtk_label_new(
            "🤖 Ollama Started"
        );

    gtk_box_pack_start(
        GTK_BOX(card2_box),
        title,
        FALSE,
        FALSE,
        5
    );

    desc =
        gtk_label_new(
            "Qwen Model Loaded"
        );

    gtk_box_pack_start(
        GTK_BOX(card2_box),
        desc,
        FALSE,
        FALSE,
        5
    );

    footer =
        gtk_box_new(
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

    btn_dnd =
        gtk_button_new_with_label(
            "DND"
        );

    gtk_box_pack_start(
        GTK_BOX(footer),
        btn_dnd,
        FALSE,
        FALSE,
        5
    );

    btn_clear =
        gtk_button_new_with_label(
            "Clear All"
        );

    gtk_box_pack_end(
        GTK_BOX(footer),
        btn_clear,
        FALSE,
        FALSE,
        5
    );

    date_label =
        gtk_label_new(
            "Friday\nJune 20 2026"
        );

    gtk_box_pack_start(
        GTK_BOX(right_panel),
        date_label,
        FALSE,
        FALSE,
        10
    );

    calendar =
        gtk_calendar_new();

    gtk_box_pack_start(
        GTK_BOX(right_panel),
        calendar,
        FALSE,
        FALSE,
        10
    );

    events_frame =
        gtk_frame_new(
            "Today"
        );

    events_label =
        gtk_label_new(
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

    gtk_widget_show_all(window);

    return window;
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
