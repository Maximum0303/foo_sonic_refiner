# Sonic Refiner v0.8.1 test checklist

v0.8.1 formalizes the documentation-only v0.8.1-dev.1 changes. Audio behavior should match v0.8.0.

Validated v0.8.1-dev.1 package SHA-256: `b15d1640b3f7faeadf78c66ba8fa5158340cac41a96f51a03dd30db74b3dbdfb`.
The validated dev build passed install, version-display, Help / Glossary / Important Notes review, restart persistence, and playback smoke testing before formalization.

1. Build Release x64 successfully.
2. Install component and confirm version `0.8.1`.
3. Confirm main settings caption and Preset Manager caption show `0.8.1`.
4. Open Help in Japanese and English; confirm Natural -18 recommendation and R128 standard/additional-mastering distinction are readable.
5. Open Glossary in Japanese and English; confirm all seven current R128 preset names are shown in the intended two groups.
6. Open Important Notes in Japanese and English; confirm Natural -18 is identified as the recommended R128 starting point.
7. Confirm the existing Reverb UI and all 16 built-in presets are unchanged.
8. Confirm Adaptive Hall / Arena / Dome / Open Air values are unchanged from v0.8.0.
9. Confirm existing SRP5 user presets load normally and retain Reverb.
10. Confirm a legacy SRP4 / .srpbackup still restores with Reverb = 0.
11. Confirm A/B comparison, Preset Manager operations, track-end Reverb tail, seek/stop reset, and Auto Headroom behave the same as v0.8.0.
12. Confirm the packaged readme.txt identifies v0.8.1 and documents Natural -18 guidance.

Expected result: documentation/UI text changes only; no audible difference from v0.8.0 with identical settings.
