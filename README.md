# SentinX Panel

SentinX Panel is the desktop shell component of the SentinX OS project.

Built on top of XFCE 4.20, SentinX replaces standard desktop components with custom-branded and customized alternatives designed to provide a lightweight AI-first Linux desktop experience.

---

## Components

### SentinX Launcher

Custom fork of XFCE4 Whisker Menu.

Features:

* SentinX branding
* Applications page opens by default
* Future Sentinel integration
* Future AI command launcher
* SentinX settings integration

Source:

```text
source/xfce4-whiskermenu-plugin
```

---

### SentinX Notification Center

Custom fork of XFCE4 Notifyd Panel Plugin.

Features:

* Notification history
* Notification center window
* Future Sentinel alerts
* Future AI system notifications

Source:

```text
source/xfce4-notifyd
```

---

### XFCE Configuration

Preconfigured desktop experience.

Includes:

* Panel layout
* Window manager settings
* Desktop settings
* Keyboard shortcuts
* Power management settings

Location:

```text
configs/xfce
```

---

## Development Environment

Tested On:

* Arch Linux
* XFCE 4.20
* GCC 16+
* Meson
* Ninja

---

## Dependencies

Install required development tools:

```bash
sudo pacman -S \
git \
base-devel \
meson \
ninja \
glib2-devel \
xfce4-dev-tools \
libxfce4ui \
libxfce4panel \
xfconf \
libnotify \
sqlite
```

---

# Building SentinX Launcher

```bash
cd source/xfce4-whiskermenu-plugin

meson setup build

meson compile -C build

sudo meson install -C build
```

Restart XFCE panel:

```bash
xfce4-panel -r
```

---

# Building SentinX Notification Center

```bash
cd source/xfce4-notifyd

meson setup build

meson compile -C build

sudo meson install -C build
```

Restart XFCE panel:

```bash
xfce4-panel --quit
xfce4-panel &
```

---

# Recovery Procedure

If XFCE resets:

Restore configuration:

```bash
cp configs/xfce/*.xml \
~/.config/xfce4/xfconf/xfce-perchannel-xml/
```

Restart panel:

```bash
xfce4-panel -r
```

Reinstall custom plugins:

```bash
cd source/xfce4-whiskermenu-plugin
sudo meson install -C build

cd ../xfce4-notifyd
sudo meson install -C build
```

---

# Repository Structure

```text
SentinX-Panel
│
├── assets
├── configs
├── docs
├── plugins
├── source
│   ├── xfce4-whiskermenu-plugin
│   └── xfce4-notifyd
├── scripts
└── logs
```

---

# Roadmap

## v0.3

* Remove favorites page
* Remove recent page

## v0.4

* SentinX icons
* Custom branding

## v0.5

* Sentinel shortcut
* Development shortcuts

## v1.0

* Full Sentinel integration
* AI desktop workflows
* ISO integration
* Installer integration

---

## License

Based on XFCE open-source components.

Original licensing and copyright notices are preserved.

SentinX modifications are maintained by Danny Soundaraj and the SentinX project.
