# Sonic Refiner v0.5.0

Sonic Refiner v0.5.0 adds optional **Adaptive Tone Balance (ATB)** to the
v0.4.0 feature set.

ATB is disabled by default. Existing users therefore keep the previous fixed
Depth / Clarity sound until they explicitly enable ATB.

## Adaptive Tone Balance

### Low

- Decision metric: Bass 60–180 Hz vs Body 200–500 Hz
- Bass/Body target: +6.5 dB
- Processing: dry signal plus parallel filtered 60–180 Hz Bass addition
- Automatic cuts: none
- Absolute Auto Low maximum: +10.0 dB

### High

- Primary metric: 3.5–10 kHz High vs 300 Hz–2.0 kHz Mid
- Secondary metric: 5–10 kHz Treble vs 2–5 kHz Presence
- High/Mid shortage reference: -6 dB with 1.5 dB tolerance
- Automatic cuts: none
- Absolute Auto High maximum: +10.0 dB

When ATB is enabled, Depth and Clarity act as maximum permissions for
automatic correction. Width and Ambience remain manual.

## Behavior

- analyzes the pre-Sonic-Refiner signal
- rolling analysis and slow gain movement reduce pumping
- very low input below approximately -55 dBFS is excluded from analysis
- track changes, seek, Stop and ATB Off→On restart analysis
- Pause/Resume preserves analysis
- multichannel analysis uses the first L/R pair
- runtime analysis state is never persisted

## Presets

- existing 11 built-in presets remain unchanged and load ATB Off
- existing built-in presets can be used as normal, then ATB may be enabled
- user presets store ATB On/Off
- `.srpbackup` stores ATB On/Off in SRP4 data
- DSP preset write format is preset_version 9
- SRP1/2/3 and DSP preset versions 1–8 remain readable and load ATB Off

## A/B

A/B now stores ATB On/Off along with Depth, Clarity, Width, Ambience, and
Master Strength. Ending comparison restores the complete settings that were
active immediately before comparison began.

## Recommended DSP order

Sonic Refiner
→ R128 Real-time Loudness Normalizer
→ Output

Sonic Refiner remains a tone/soundstage processor. Final loudness,
True Peak management and limiting remain the job of the downstream
R128 Real-time Loudness Normalizer.
