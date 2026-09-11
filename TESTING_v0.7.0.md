# Sonic Refiner v0.7.0 Final Verification

The v0.7.0 formal source is based directly on the fully tested v0.7.0-dev.33 source.

Final regression verification completed before formalization:

- Preset Manager opens correctly in Japanese and English.
- Light / Dark display verified.
- Apply button and double-click Apply verified.
- New from Current verified.
- Update from Current verified.
- Duplicate verified.
- Rename verified.
- Delete verified.
- Backup verified.
- Restore verified.
- Move Up / Move Down verified.
- Alt+Up / Alt+Down verified.
- Drag-and-drop reorder verified.
- Search / Ctrl+F / Ctrl+Backspace verified.
- Right-click context menu verified.
- 20-user-preset limit behavior verified.
- Empty-list / no-search-match states verified.
- Parent Cancel restore behavior verified.
- Parent OK commit behavior verified.
- Session-only selected-preset memory verified.
- Persistent Preset Manager window-size memory verified.
- Persistent splitter-ratio memory verified.
- Tab / Shift+Tab order verified.
- Simplified parent User Presets layout verified in Japanese and English.

Formalization changes only version strings and release documentation.
No DSP / ATB behavior was changed.
