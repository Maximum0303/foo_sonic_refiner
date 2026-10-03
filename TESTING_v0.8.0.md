# Sonic Refiner v0.8.0 formal release checklist

Formalization baseline: v0.8.0-dev.3.

1. Build Release x64 successfully.
2. Confirm package name is `foo_sonic_refiner_v0.8.0.fb2k-component`.
3. Install and confirm component version 0.8.0.
4. Confirm formalization did not change the validated venue values:
   - Adaptive Hall: Width 60 / Ambience 55 / Reverb 50.
   - Adaptive Arena: Width 72 / Ambience 65 / Reverb 68.
   - Adaptive Dome: Width 85 / Ambience 75 / Reverb 85.
   - Adaptive Open Air: Width 75 / Ambience 20 / Reverb 10.
5. No DSP or persistence regression retest is expected solely from formalization unless the build result differs from dev.3 behavior.
