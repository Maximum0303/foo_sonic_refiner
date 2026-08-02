#include "stdafx.h"

DECLARE_COMPONENT_VERSION(
    "Sonic Refiner",
    "0.1.1",
    "Adaptive Audio Enhancement DSP for foobar2000.\n\n"
    "Adds adjustable depth, clarity, stereo width and ambience, with automatic headroom protection, level-matched bypass, built-in and user presets, preset backup and restore, and integrated help."
);

VALIDATE_COMPONENT_FILENAME("foo_sonic_refiner.dll");

FOOBAR2000_IMPLEMENT_CFG_VAR_DOWNGRADE;
