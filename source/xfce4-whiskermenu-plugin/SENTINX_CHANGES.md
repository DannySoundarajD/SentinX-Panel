# SentinX Changes

## Overview

SentinX Launcher is a customized fork of the XFCE4 Whisker Menu plugin developed as part of the SentinX OS project.

This fork retains compatibility with XFCE while introducing SentinX-specific branding, launcher behavior, and future Sentinel integrations.

## Current Modifications

### Branding

* Renamed visible launcher branding from "Whisker Menu" to "SentinX"
* Updated settings dialog title to "SentinX"
* Updated desktop entry name to "SentinX"

### Launcher Behavior

* Changed default startup category from Favorites to Applications
* Applications page now opens by default when the launcher is activated

### Build Status

* Successfully compiles using Meson and Ninja
* Successfully tested on Arch Linux XFCE 4.20
* Successfully loaded as a replacement for the stock Whisker Menu plugin

## Planned Modifications

### v0.3.0

* Remove Favorites page
* Remove Recent page
* Simplify launcher navigation

### v0.4.0

* Replace Whisker icon assets with SentinX branding
* Custom launcher visuals

### v0.5.0

* Add Sentinel shortcut
* Add SentinX Settings shortcut
* Add development shortcuts (VS Code, Terminal)

### v1.0.0

* Deep Sentinel integration
* SentinX OS installer integration
* Custom launcher experience optimized for SentinX OS

## Licensing

SentinX Launcher is based on XFCE4 Whisker Menu and remains subject to the original GPL licensing terms.

Original project authors and copyright notices are preserved.

Only SentinX-specific modifications are authored by the SentinX project.
