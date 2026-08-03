Sonic Refiner 0.2.0
Adaptive Audio Enhancement DSP for foobar2000

OVERVIEW
Sonic Refiner adjusts tone and spatial presentation in real time. It provides
four main controls—Depth, Clarity, Width and Ambience—plus output gain,
automatic headroom protection and level-matched bypass comparison.

MAIN FEATURES
- Depth: low-shelf enhancement around 120 Hz, up to approximately +16 dB
- Clarity: high-shelf enhancement from around 3.5 kHz, up to approximately +14 dB
- Width: frequency-dependent Mid/Side widening with low-frequency protection,
  up to Side 600%
- Ambience: short early reflections around 11 ms and 19 ms, up to Wet Mix 85%
- Master Strength: scales Depth, Clarity, Width and Ambience from 0% to 100%
- Output Gain: -12.0 dB to +6.0 dB in 0.5 dB steps
- Automatic headroom protection around -0.2 dBFS block peak
- Level-matched bypass comparison
- Eleven built-in presets
- Up to 20 named user presets
- User-preset backup and restore using .srpbackup files
- Integrated Help, Glossary, Safety Notices and MIT License pages
- Light and dark mode support

BUILT-IN PRESETS
Standard / Bass Boost / Vocal Focus / Wide / Live / Headphones
Super Bass / Super Clarity / Super Wide / Large Hall / Full Boost

PROCESSING ORDER
Depth -> Clarity -> Width -> Ambience -> Level Match
-> Output Gain -> Automatic Headroom Protection

RECOMMENDED DSP ORDER
Sonic Refiner -> R128 Real-time Loudness Normalizer -> output

IMPORTANT
Values from 80% to 100% are intended for strong effects and testing. Very high
Depth, Width or Ambience settings may sound unnatural or place additional load
on playback equipment. Lower the listening volume before testing extreme
settings.

Automatic Headroom is a lightweight sample/block-peak safety function. It is
not a True Peak limiter. For normal use, keep Automatic Headroom enabled and
place an appropriate loudness/True Peak processor after Sonic Refiner.

PRESET COMPATIBILITY
Existing Sonic Refiner preview settings and SRP1/SRP2 user presets remain
readable. Legacy presets without Output Gain are loaded with 0.0 dB.

LICENSE
MIT License. Copyright (c) 2026 Maximum.
The full license is included as MIT_LICENSE.txt and is also available from the
component's License button.

THIRD-PARTY NOTICE
This package does not include the foobar2000 SDK. foobar2000 and the official
SDK remain subject to their respective terms.


VERSION 0.1.1
- Unified the official downstream normalizer name as:
  R128 Real-time Loudness Normalizer
- Updated Help, Glossary, Safety Notices and public documentation
- No DSP processing, preset format or saved-setting behavior was changed


VERSION 0.2.0
- Added Master Strength from 0% to 100% as a stable public feature
- Scales Depth and Clarity gain, Width above Side 100%, and Ambience wet/dry effect
- Does not scale Output Gain, Automatic Headroom or Level Match
- Added SRP3 user-preset storage with Master Strength
- Reads SRP1 and SRP2 presets with Master Strength set to 100%
- Reads v0.1.x DSP settings with Master Strength set to 100%
