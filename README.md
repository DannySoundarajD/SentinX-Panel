# SentinX Panel

A modern XFCE panel transformation project that reimagines the traditional notification experience and desktop interaction model for SentinX OS.

---

## Overview

SentinX Panel is a custom XFCE panel enhancement project focused on bringing a modern desktop experience inspired by contemporary operating systems while preserving XFCE's performance and flexibility.

Current development focuses on a fully redesigned notification center integrated directly into the XFCE notification infrastructure.

---

## Current Features

### Custom Notification Center

* Custom SentinX notification dropdown
* Dual-panel layout
* Notification area on the left
* Calendar section on the right
* Integrated directly into XFCE notification plugin
* Large dropdown layout (900x650)

### XFCE Integration

* Built on xfce4-notifyd
* Uses native XFCE notification services
* Uses XFCE notification log backend
* Uses XFCE panel plugin architecture
* Compatible with existing XFCE notification workflows

### SentinX UI Foundation

* Modern split-pane notification design
* Dedicated notification section
* Dedicated calendar section
* Expandable architecture for future widgets

---

## Development Progress

### Sprint 1

Completed:

* Notification center prototype
* Basic panel integration
* Toggle launch behavior
* Notification center layout design

### Sprint 2

Completed:

* Split-pane layout
* Calendar integration
* Larger notification center dimensions
* Improved panel interaction

### Sprint 3

Completed:

* Notification center embedded into XFCE notification plugin
* Custom menu container
* SentinX panel rendering engine

### Sprint 4

Completed:

* Notification center migration into notification-plugin-log.c
* Stable compilation
* Plugin rebuild pipeline
* Git branch workflow

### Sprint 5 (In Progress)

Current:

* Notification container system
* Scrollable notification area
* Real XFCE notification backend research
* DND integration preparation
* Clear All integration preparation

Planned:

* Real notification rendering
* Notification timestamps
* Application icons
* Notification counters
* Read/unread indicators
* Dynamic notification cards

---

## Architecture

### Components

```text
SentinX Panel
│
├── XFCE Panel Plugin
│
├── Notification Center
│   ├── Notification List
│   ├── Notification Cards
│   ├── DND Controls
│   ├── Clear Actions
│   └── Notification Counter
│
├── Calendar Module
│
└── XFCE Notifyd Backend
```

### Core Source Files

```text
panel-plugin/
├── notification-plugin.c
├── notification-plugin.h
├── notification-plugin-log.c
├── sentinx-notification-center.c
└── sentinx-notification-center.h
```

---

## Build Instructions

```bash
meson setup build
ninja -C build
```

Install:

```bash
sudo cp \
build/panel-plugin/libnotification-plugin.so \
/usr/lib/xfce4/panel/plugins/libnotification-plugin.so
```

Restart XFCE panel:

```bash
pkill xfce4-panel

xfce4-panel &
```

---

## Roadmap

### Notification Center

* Real-time notification cards
* Notification grouping
* Notification actions
* Application icons
* Notification search
* Notification categories

### Productivity Features

* Calendar events
* Agenda view
* Quick actions
* Workspace integration

### SentinX OS Integration

* AI service notifications
* Ollama status integration
* System monitoring widgets
* Sentinel service status
* GPU and AI workload monitoring

---

## Status

Active Development

Current Branches:

```text
main
sentinx-notification-center
sentinx-popover-migration
```

Target Platform:

```text
Arch Linux
XFCE 4.20
GTK3
```

Project Goal:

Create a modern Linux desktop notification experience while retaining XFCE's speed, modularity, and reliability.
