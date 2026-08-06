#include "stdafx.h"

DECLARE_COMPONENT_VERSION(
    "Sonic Refiner",
    "0.3.0",
    "Adaptive Audio Enhancement DSP for foobar2000.\n\n"
    "Adds adjustable depth, clarity, stereo width and ambience, with Master Strength, automatic headroom protection, level-matched bypass, built-in and user presets, preset backup and restore, and a Japanese/English user interface."
);

VALIDATE_COMPONENT_FILENAME("foo_sonic_refiner.dll");

FOOBAR2000_IMPLEMENT_CFG_VAR_DOWNGRADE;
