#include "stdafx.h"

DECLARE_COMPONENT_VERSION(
    "Sonic Refiner",
    "0.6.2",
    "Adaptive Audio Enhancement DSP for foobar2000.\n\n"
    "Adds adjustable depth, clarity, stereo width and ambience, with Master Strength, Adaptive Tone Balance, automatic headroom protection, level-matched bypass, built-in and user presets, preset backup and restore, A/B comparison slots, direct settings access from the Playback menu, keyboard-shortcut support, and a Japanese/English user interface."
);

VALIDATE_COMPONENT_FILENAME("foo_sonic_refiner.dll");

FOOBAR2000_IMPLEMENT_CFG_VAR_DOWNGRADE;
