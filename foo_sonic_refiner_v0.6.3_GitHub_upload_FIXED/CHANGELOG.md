# Changelog

## [0.6.3] - 2026-08-28

### Changed

- When current DSP settings do not match any of the 12 built-in presets, the
  Built-in Presets combo displays `Custom / カスタム` instead of appearing blank.
- `Custom / カスタム` is a UI-only state and is not loadable as a built-in preset.
- With Adaptive Tone Balance ON, Depth and Clarity labels explicitly identify
  them as the Auto Low / Auto High correction limits.
- ATB-mode descriptions clarify that 100% is an upper permission and does not
  force a constant +10 dB boost.
- Help / Glossary ATB explanations were reorganized for practical user
  understanding.
- Glossary entries separately define Adaptive Tone Balance, Auto Low, Auto High,
  and ATB Analysis State.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset / backup compatibility is unchanged.

### Validation

- Custom display: matching, non-matching, restart, language switching, user
  presets, A/B, Cancel, Light / Dark all verified.
- ATB labels: ON / OFF, Japanese / English, restart, Cancel, Light / Dark all
  verified.
- Help / Glossary: Japanese / English and Light / Dark verified.
- Full-track Adaptive Standard smoke playback completed without dropout,
  click / pop noise, abrupt unnatural tonal change, or crash.

## [0.6.3-dev.3] - 2026-08-28

### Help / Glossary clarity
- Reorganized Adaptive Tone Balance Help around practical user behavior.
- Clarified that ATB is boost-only and that Depth / Clarity are correction limits while ATB is On.
- Clarified that 100% permits up to +10.0 dB but does not force a constant +10 dB boost.
- Clarified that Width / Ambience remain manual and Master Strength also scales adaptive correction.
- Added separate Glossary entries for Auto Low, Auto High, and ATB Analysis State using the current validated frequency ranges.
- Clarified fresh-analysis conditions and Pause→Resume history preservation.
- No DSP / ATB algorithm, preset value, or serialization changes.

## [0.6.3-dev.2] - 2026-08-28

### Changed

- When Adaptive Tone Balance is ON, the Depth and Clarity labels now explicitly identify them as the Auto Low / Auto High correction limits.
- The ATB-mode descriptions now state that 100% is only a maximum permission and does not mean a constant +10 dB boost.
- When Adaptive Tone Balance is OFF, the original fixed-mode Depth / Clarity labels and descriptions are shown.
- The Depth / Clarity label fields were widened inside the existing 560 x 320 layout to avoid text clipping in Japanese and English.
- The `Custom / カスタム` state added in v0.6.3-dev.1 is retained unchanged.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.3-dev.1] - 2026-08-28

### Changed

- When current DSP settings do not match any of the 12 built-in presets, the Built-in Presets combo now displays `Custom / カスタム` instead of appearing blank.
- `Custom / カスタム` is a UI-only state, not an additional built-in preset.
- The built-in preset Load button remains disabled while the Custom state is displayed.
- Japanese / English switching updates the Custom label while preserving the current DSP settings.
- Loading or otherwise reaching an exact built-in preset match returns the combo to that built-in preset name.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.2] - 2026-08-23

### Fixed

- The Built-in Presets combo now reflects the built-in preset that exactly matches the currently restored DSP settings when the settings dialog opens.
- Restarting foobar2000 after using a built-in preset no longer causes the combo to visually fall back to `Standard` while another preset's settings remain active.
- When the current settings do not exactly match any built-in preset, the built-in combo is left unselected instead of showing a misleading preset name.
- Slider / option changes, user-preset loads, and A/B listening resynchronize the displayed built-in preset selection.
- Selecting a combo item still requires `Load` before the DSP settings are changed.

### Compatibility

- No DSP / ATB algorithm changes.
- All 12 built-in preset values are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- Legacy preset and backup compatibility is unchanged.

## [0.6.1] - 2026-08-23

### Fixed

- Added a clear ATB analysis-pending status so stale Auto Low / Auto High values from the previous playback position are not shown as if they belonged to the new one.
- Playback start, Next, Previous, direct track jumps, natural track changes, seeks, Stop -> playback, and ATB Off -> On now show `自動補正：解析中...` / `Auto: Analyzing...` while fresh analysis is being accumulated.
- New-track and seek notifications use a runtime-only playback discontinuity generation consumed by the ATB processor so fresh analysis begins reliably on the new playback position.
- Pause / Resume continues to preserve the current ATB analysis state.

### Compatibility

- No audible DSP or Adaptive Tone Balance decision-algorithm changes from v0.6.0.
- Auto Low / Auto High mapping, smoothing, startup protection, and +10.0 dB absolute limits are unchanged.
- SRP4 and `preset_version 9` are unchanged.
- All 12 built-in presets are unchanged.
- Legacy DSP presets and SRP1 / SRP2 / SRP3 / SRP4 backup/preset compatibility are unchanged.
- Runtime analyzer state remains non-persistent.

### Validation

- Verified playback start, Next, Previous, direct track jump, seek, natural track advance, Stop -> playback, and ATB Off -> On all enter the analyzing state.
- Verified Pause -> Resume preserves analysis and does not restart it.
- Verified the analyzing state returns to numeric Auto Low / Auto High status after sufficient fresh analysis.
- Verified Japanese / English, Light / Dark, and full-track playback without dropout, click noise, abrupt unnatural tonal change, or crash.

## [0.6.1-dev.2] - 2026-08-23

### Fixed

- Track changes triggered by Next / Previous / direct track jumps now immediately enter the ATB `Analyzing...` UI state.
- Added a runtime-only playback discontinuity generation so the ATB analyzer is reset for new-track and seek notifications even when the DSP discontinuity callback arrives through a different path or timing.
- Pause / Resume continues to preserve ATB analysis history.

### Compatibility

- No change to the ATB Low / High decision algorithm, boost mapping, smoothing rates, or absolute limits.
- No change to SRP4, `preset_version 9`, user presets, `.srpbackup`, or the 12 built-in presets.

## [0.6.1-dev.1] - 2026-08-23

### Fixed

- Track changes and seeks now invalidate the previous track's displayed Auto Low / Auto High values immediately while Adaptive Tone Balance is enabled.
- The normal ATB status line shows `自動補正：解析中...` / `Auto: Analyzing...` until the new playback segment has accumulated the normal minimum stable analysis history.
- Added a runtime-only UI analysis-pending guard so a retained transition gain cannot be mistaken for the new track's completed analysis result.

### Unchanged

- No audible DSP or Adaptive Tone Balance algorithm changes.
- ATB targets, filters, smoothing, startup protection, gain limits and click-free transition behavior are unchanged from v0.6.0.
- Pause / Resume history behavior, built-in presets, `preset_version 9`, SRP4, legacy compatibility, `.srpbackup`, A/B, Cancel and persistence behavior are unchanged.

## [0.6.0] - 2026-08-23

### Added

- Added the 12th built-in preset, `Adaptive Standard / 適応型標準`.
- Adaptive Standard uses Depth 100, Clarity 100, Width 50, Ambience 40, Master Strength 100%, Output Gain 0.0 dB, both protection options On, Sonic Refiner enabled, and Adaptive Tone Balance On.
- The preset gives Auto Low / Auto High the full permitted automatic-correction range while retaining the Standard preset's Width / Ambience values.

### Fixed

- Widened the Depth and Clarity value fields so Japanese ATB limit text such as `100% / 自動上限 +10.0 dB` is fully visible.
- Formal source packaging retains the exact Japanese helper filename `ビルドと梱包.cmd` without a garbled duplicate.

### Compatibility

- Existing 11 built-in presets remain unchanged and continue to load ATB Off.
- DSP and Adaptive Tone Balance algorithms are unchanged from v0.5.0.
- `preset_version 9` and SRP4 remain unchanged.
- SRP1 / SRP2 / SRP3 / SRP4 and legacy DSP preset reading remain supported.
- `.srpbackup`, A/B, Cancel, direct settings access, language behavior, and runtime analyzer persistence rules are unchanged.

### Validation

- The release candidate was verified in Japanese and English, Light and Dark mode.
- Adaptive Standard settings, restart persistence, A/B switching/restoration, Cancel restoration, SRP4 user-preset backup/restore, existing Standard behavior, and continuous playback were checked.
- v0.6.0 formal source keeps the validated v0.6.0-dev.3 DSP and preset behavior; formalization changes version markers and public release documentation only.

## [0.6.0-dev.3] - 2026-08-23

### Fixed

- Corrected the source ZIP packaging so the Japanese build helper is stored with the exact filename `ビルドと梱包.cmd`.
- Removed the garbled duplicate filename that was accidentally present in the v0.6.0-dev.2 source ZIP.

### Unchanged

- Compiled DSP code and Adaptive Tone Balance behavior are unchanged from v0.6.0-dev.2.
- Adaptive Standard settings and the existing 11 built-in presets are unchanged.
- `preset_version 9`, SRP4, legacy preset reading, `.srpbackup`, A/B and runtime-state persistence behavior are unchanged.
- The v0.6.0-dev.2 UI clipping fix is retained.

## [0.6.0-dev.2] - 2026-08-23

### Fixed

- Widened the Depth and Clarity value text fields so the Japanese ATB limit display such as `100% / 自動上限 +10.0 dB` is not clipped at the right edge.

### Unchanged

- No DSP or Adaptive Tone Balance algorithm changes.
- Adaptive Standard settings are unchanged from v0.6.0-dev.1.
- `preset_version 9`, SRP4, legacy preset reading, `.srpbackup`, A/B and runtime-state persistence behavior are unchanged.

## [0.6.0-dev.1] - 2026-08-23

### Added

- Added one built-in preset: **適応型標準 / Adaptive Standard**.
- The preset uses Depth 100, Clarity 100, Width 50, Ambience 40, Master Strength 100%, Output Gain 0.0 dB, both protection options On, Sonic Refiner enabled, and Adaptive Tone Balance On.
- With ATB On, Depth / Clarity 100 grant the existing Auto Low / Auto High logic the full permitted range without changing the ATB algorithm.

### Compatibility

- Existing 11 built-in presets are unchanged.
- `preset_version 9`, SRP4, legacy preset reading and `.srpbackup` compatibility are unchanged.
- No DSP algorithm, ATB target, filter, smoothing, A/B or runtime-state persistence behavior changed.

## [0.5.0] - 2026-08-23

### Added

- Added optional Adaptive Tone Balance (ATB), disabled by default.
- Added source-dependent boost-only automatic Low and High tonal correction.
- Added current Auto Low / Auto High status to the normal settings UI.
- Added ATB On/Off to A/B slots, user presets, DSP presets, and `.srpbackup` data.

### Adaptive Tone Balance

- Auto Low uses Bass 60–180 Hz vs Body 200–500 Hz with a +6.5 dB Bass/Body target.
- Auto Low preserves the dry signal and adds a parallel filtered 60–180 Hz Bass component.
- Auto High combines High/Mid and Treble/Presence balance.
- Auto Low absolute maximum is +10.0 dB.
- Auto High absolute maximum is +10.0 dB.
- Depth and Clarity become automatic-correction limits while ATB is On.
- ATB Off preserves the v0.4.0 fixed Depth / Clarity behavior.
- Slow rolling analysis, startup protection, confidence gating, and asymmetric gain movement reduce abrupt tonal changes.
- Track changes, seeks, Stop, and ATB Off→On restart analysis; Pause/Resume preserves it.

### Presets and compatibility

- DSP preset write format advanced to `preset_version 9`.
- User-preset / `.srpbackup` write format advanced to `SRP4`.
- SRP1, SRP2, SRP3, SRP4 and DSP preset versions 1–8 remain readable.
- Legacy data without ATB state loads ATB Off.
- Existing 11 built-in presets remain unchanged and load ATB Off.
- Runtime analyzer history and current automatic-gain state are not persisted.

### A/B and UI

- A/B slots store ATB On/Off and restore the complete pre-comparison settings when comparison ends.
- Development-only diagnostic readouts were removed from the formal UI.
- Light/Dark mode, continuous playback, restart persistence, Cancel behavior, preset backup/restore, legacy SRP3 import, and A/B ATB switching were validated on the release candidate.

## [0.5.0-dev.25] - 2026-08-23

### UI / cleanup

- Removed the development-only diagnostic text from the normal settings window.
- Restored the bottom status line to the normal processing state display while Adaptive Tone Balance is enabled.
- Kept the user-facing Adaptive Tone Balance runtime status showing current Auto Low / Auto High correction.
- Disabled the development-only pre/post Bass/Body comparison pass because it did not feed the correction algorithm.

### Unchanged

- No intended audio correction change from dev.23/dev.24.
- Low: parallel 60–180 Hz Bass-band addition, Bass/Body target +6.5 dB, Auto Low maximum +10.0 dB.
- High: H/M + T/P combined decision, Auto High maximum +10.0 dB.
- T/P analysis required by Auto High remains active.
- Smoothing and startup protection are unchanged.
- `preset_version 9` and `SRP4` persistence are unchanged.
- Legacy SRP1/2/3 and DSP preset versions 1–8 remain compatible with ATB Off.
- A/B behavior, presets, Output Gain, level matching, and automatic headroom are unchanged.

## [0.5.0-dev.24] - 2026-08-22

### Persistence integration

- Formalized the existing Adaptive Tone Balance persistence contract without changing the tested dev.23 audio algorithm.
- DSP preset write format is `preset_version 9` and stores Adaptive Tone Balance On/Off.
- User-preset and `.srpbackup` write format is `SRP4` and stores Adaptive Tone Balance On/Off.
- `SRP1`, `SRP2`, `SRP3`, and DSP preset versions 1–8 remain readable.
- Legacy formats default Adaptive Tone Balance to Off.
- Built-in presets continue to use Adaptive Tone Balance Off.
- Runtime analysis history, current automatic gains, confidence values, and diagnostics are not persisted.
- Updated current Help / Important Notes / README documentation to the tested +10 dB Auto Low and +10 dB Auto High absolute limits.

### Audio

- No DSP algorithm changes from dev.23.
- Low remains the parallel 60–180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low absolute maximum +10.0 dB.
- High remains the H/M + T/P combined decision with Auto High absolute maximum +10.0 dB.
- Smoothing, startup protection, Width, Ambience, Master Strength, Output Gain, level matching, and automatic headroom are unchanged.

## [0.5.0-dev.23] - 2026-08-22

### Changed

- Raised the Auto Low absolute maximum from +8.0 dB to +10.0 dB.

### Unchanged

- Adaptive Low filter topology is identical to dev.22/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body decision target remains +6.5 dB.
- Low confidence logic and smoothing are unchanged.
- H/M + T/P combined High decision is identical to dev.22/dev.21.
- Auto High absolute maximum remains +10.0 dB.
- High thresholds, confidence logic and smoothing are unchanged.
- Startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.22] - 2026-08-22

### Changed

- Raised the Auto Low absolute maximum from +6.0 dB to +8.0 dB.

### Unchanged

- Adaptive Low filter topology is identical to dev.21/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body decision target remains +6.5 dB.
- H/M + T/P combined High decision is identical to dev.21.
- Auto High absolute maximum remains +10.0 dB.
- All High thresholds, confidence logic and smoothing are unchanged.
- Startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.21] - 2026-08-22

### Changed

- Raised the Auto High absolute maximum from +8.0 dB to +10.0 dB.

### Unchanged

- H/M + T/P combined High decision logic is identical to dev.20.
- Gentle High baseline remains +3.2 dB.
- H/M severity mapping remains -13.0 dB to -16.0 dB.
- T/P severity mapping remains -5.0 dB to -7.5 dB.
- Existing H/M shortage confidence gate is unchanged.
- Low processing and Low decision logic are unchanged.
- Bass/Body target remains +6.5 dB and Auto Low maximum remains +6.0 dB.
- Smoothing, startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.20] - 2026-08-22

### Changed

- Experimental Auto High demand now combines H/M and T/P after at least six valid T/P windows are available.
- The existing H/M shortage percentage still controls increase / hold / release behavior.
- The old H/M-only candidate remains the hard upper bound for the new combined candidate.
- Added `HC` (High Candidate) to the development diagnostic line so the current automatic target can be inspected without waiting for the smoothed output gain to catch up.

### Experimental combined High map

- Gentle baseline: up to +3.2 dB.
- H/M extra-correction severity begins below -13.0 dB and reaches full severity at -16.0 dB.
- T/P extra-correction severity begins below -5.0 dB and reaches full severity at -7.5 dB.
- Extra correction uses `sqrt(H/M severity * T/P severity)`, so both metrics must indicate a deeper deficiency before HC approaches +8.0 dB.
- HC never exceeds the original H/M-derived shortage estimate, the Clarity slider limit, or the +8.0 dB absolute Auto High cap.

### Unchanged

- Low processing is identical to dev.19/dev.13: dry signal plus parallel 60-180 Hz Bass-band addition.
- Bass/Body target remains +6.5 dB and Auto Low absolute maximum remains +6.0 dB.
- H/M target remains -6.0 dB and the existing H/M shortage confidence thresholds remain unchanged.
- Smoothing, startup protection, Master Strength, Width, Ambience, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.
- H/M MAD, T/P MAD, P/M and Crest remain diagnostic-only.

## [0.5.0-dev.19] - 2026-08-22

### Added

- Added diagnostic-only H/M variability using MAD (median absolute deviation) across the existing 12 valid 1-second analysis windows.
- Added diagnostic-only T/P variability using MAD across the same 12-window history used by T/P.
- H/M and T/P are displayed as `median±MAD`.
- Added a coherent H/M stability snapshot so H/M median, MAD, shortage percentage and history count are published from the same analysis update.

### Changed

- Compacted the development diagnostic status line to make room for the variability values.

### Unchanged

- MAD values do not control Auto High or Auto Low.
- Audio processing is identical to dev.18/dev.17.
- Auto High absolute maximum remains +8.0 dB.
- Existing H/M target and all High decision/confidence/smoothing behavior are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- T/P, P/M and Crest remain diagnostic-only.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.18] - 2026-08-22

### Added

- Added diagnostic-only `Crest`, measuring crest factor in the 2-10 kHz high-detail band (upper edge limited to 45% of sample rate when necessary).
- Crest is calculated per valid 1-second window as `20 * log10(peak / RMS)` and displayed as the median of the same 12-window history used by T/P and P/M.
- T/P, P/M and Crest are published together in one coherent 64-bit runtime snapshot.

### Unchanged

- Crest does not control Auto High in dev.18.
- Audio processing is identical to dev.17/dev.16/dev.15.
- Auto High absolute maximum remains +8.0 dB.
- H/M target and all existing High decision/confidence/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.17] - 2026-08-22

### Added

- Added diagnostic-only `P/M`, defined as Presence (2-5 kHz) energy density divided by Mid (300-2000 Hz) energy density.
- `P/M` is shown next to the existing `T/P` runtime diagnostic.
- `P/M` uses the same pre-Sonic-Refiner source, 1-second valid windows, 12-window history and median display as `T/P`.

### Unchanged

- `P/M` does not control Auto High in dev.17.
- Audio processing is identical to dev.16/dev.15.
- Auto High absolute maximum remains +8.0 dB.
- H/M target and all existing High decision/confidence/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.16] - 2026-08-22

### Added

- Added a diagnostic-only Presence band at 2-5 kHz.
- Added a diagnostic-only Treble band at 5-10 kHz (upper edge limited to 45% of sample rate when necessary).
- Added `T/P` (Treble/Presence energy-density ratio) to the runtime diagnostic line.
- The diagnostic uses the pre-Sonic-Refiner input and a 12-window median, matching the existing analysis cadence.

### Unchanged

- Audio processing is identical to dev.15.
- Auto High absolute maximum remains +8.0 dB.
- Existing H/M target and all High decision/smoothing logic are unchanged.
- Low processing remains the dev.13 parallel 60-180 Hz Bass-band design with Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.

## [0.5.0-dev.15] - 2026-08-22

### Changed

- Increased the Adaptive Tone Balance Auto High absolute maximum from +6.0 dB to +8.0 dB.

### Unchanged

- H/M target remains -6.0 dB.
- High shortage-confidence logic, smoothing and timing behavior are unchanged.
- Low processing remains identical to dev.14/dev.13, including the parallel 60-180 Hz Bass-band addition, Bass/Body target +6.5 dB and Auto Low maximum +6.0 dB.
- Width, Ambience, Master Strength, Output Gain, level matching, automatic headroom, presets and A/B behavior are unchanged.


## [0.5.0-dev.13] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now preserves the dry signal and adds a filtered 60-180 Hz Bass-band component in parallel.
- Added band scale is derived from the current Auto Low gain as `10^(gain/20) - 1`.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Fixed

- Normalized the Japanese build wrapper filename to `ビルドと梱包.cmd`.
- Removed mojibake duplicate CMD wrapper filenames from the source package.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.12] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now uses a 180 Hz fourth-order Linkwitz-Riley-style low/high crossover.
- Auto Low gain is applied only to the Low branch; the High branch is recombined without Low gain.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.11] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, Auto Low now uses two peaking EQs centered at 80 Hz and 150 Hz.
- Both peaks use Q 1.4 and 85% of the current Auto Low gain.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.10] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, automatic Low correction now uses a dedicated 110 Hz, Q 1.0 peaking EQ.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth low shelf.

### Unchanged

- Bass/Body decision target remains +6.5 dB.
- Auto Low caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic remains enabled.
- Presets, A/B behavior, Width, Ambience, Output Gain, level matching and headroom protection are unchanged.

## [0.5.0-dev.9] - 2026-08-22

### Changed

- While Adaptive Tone Balance is ON, automatic Low correction now uses a 180 Hz low shelf instead of the legacy 120 Hz shelf.
- Adaptive Tone Balance OFF continues to use the original 120 Hz Depth shelf.

### Unchanged

- Bass/Body target remains +6.5 dB.
- Auto Low gain calculation, caps, smoothing, confidence logic and intro protection are unchanged.
- High correction remains H/M-based with target -6.0 dB.
- The paired Input/Post/Delta Bass/Body diagnostic from dev.8 remains enabled.
- Presets, A/B storage, Width, Ambience, Output Gain, level matching and headroom behavior are unchanged.

## [0.5.0-dev.8] - 2026-08-22

### Added

- Added a paired, measurement-only Bass/Body analyzer before and immediately after the Depth/Clarity tone-filter stage.
- Added diagnostic display of Input Bass/Body, Post Bass/Body, and Delta.
- Paired values are accumulated from the same frames and published coherently.

### Unchanged

- Audible DSP and Adaptive Tone Balance behavior are unchanged from v0.5.0-dev.7.
- Low target remains Bass/Body +6.5 dB.
- High target remains H/M -6.0 dB.
- Gain caps, smoothing, intro protection, presets, A/B, headroom protection, and level matching are unchanged.

## [0.5.0-dev.7] - 2026-08-22

### Changed

- Low automatic correction now uses Bass/Body (60-180 Hz / 200-500 Hz) instead of L/M as its primary decision metric.
- Added a provisional Bass/Body target of +6.5 dB for development listening tests.
- L/M remains diagnostic-only.

### Unchanged

- High correction remains H/M-based with target -6.0 dB.
- Boost caps, tolerance, confidence thresholds, smoothing, intro protection, presets, A/B behavior, headroom protection, and level matching are unchanged from v0.5.0-dev.6.

## [0.5.0-dev.6] - 2026-08-22

### Added

- Added a diagnostic-only Bass band (60-180 Hz).
- Added a bandwidth-corrected Bass/Body diagnostic ratio using Body 200-500 Hz.
- Included Bass/Body in the coherent single-atomic diagnostic snapshot.

### Unchanged

- Adaptive Tone Balance targets, gain decisions, audible processing, preset behavior, and A/B behavior remain unchanged from v0.5.0-dev.5.

## [0.5.0-dev.5] - 2026-08-22

### Fixed

- Made the development diagnostic data a single coherent 64-bit atomic snapshot.
- Prevented L/M, Body/Core, H/M, shortage percentages, and history count from being mixed across different analysis updates.
- Adaptive Tone Balance audio/correction behavior remains unchanged from v0.5.0-dev.4.

## [0.5.0-dev.4] - 2026-08-22

### Diagnostic

- Added Body 200–500 Hz / Core 500 Hz–2 kHz diagnostic analysis.
- Added Body/Core median ratio to the development diagnostic line.
- Adaptive Tone Balance correction logic remains identical to v0.5.0-dev.3.

## [0.5.0-dev.3] - 2026-08-22

### Added

- Added a temporary Adaptive Tone Balance diagnostic readout for real-world tuning.
- The bottom status line now shows the current median Low/Mid and High/Mid analysis values, configured targets, shortage-window percentages, and valid history count.
- Diagnostic data is runtime-only and is not stored in DSP presets, user presets, A/B slots, or `.srpbackup` files.
- No intended Adaptive Tone Balance algorithm or target change from v0.5.0-dev.2.

## [0.5.0-dev.2] - 2026-08-22

### Fixed

- Fixed Visual Studio C2275 / C2737 in the Adaptive Tone Balance analysis-window size calculation.
- Corrected the `std::max` call syntax for `window_frame_target`.
- No intended DSP behavior change from v0.5.0-dev.1.

## [0.5.0-dev.1] - 2026-08-22

### Added

- Added **Adaptive Tone Balance** (適応型音色補正), disabled by default.
- Added boost-only source-dependent low/high correction using the original pre-processing signal.
- Analysis bands: Low 60-250 Hz, Mid reference 300 Hz-2.0 kHz, High 3.5-10 kHz.
- Targets: Low = Mid +3 dB, High = Mid -6 dB, with 1.5 dB tolerance.
- Safety limits: Auto Depth up to +6.0 dB and Auto Clarity up to +4.0 dB.
- Added compact live status for Off / Waiting / Analyzing / applied Low & High correction.
- Added Adaptive Tone Balance On/Off state to A/B slots, user presets and preset backups.
- User-preset write format advanced to SRP4 and foobar2000 DSP preset format to `preset_version 9`.

### Behavior

- With Adaptive Tone Balance Off, Depth and Clarity retain the v0.4.0 fixed behavior.
- With Adaptive Tone Balance On, Depth and Clarity act as maximum automatic-correction limits.
- Width and Ambience remain manual. Master Strength also scales the adaptive correction.
- The analyzer uses lightweight IIR/Biquad filters rather than FFT.
- Runtime analysis history is never serialized.
- Track changes, seeks and Stop reset analysis; Pause/Resume preserves it.
- Existing 11 built-in presets explicitly keep Adaptive Tone Balance Off.

### Compatibility

- SRP1, SRP2 and SRP3 remain readable; legacy user presets load Adaptive Tone Balance as Off.
- Legacy DSP preset versions 1-8 remain readable; Adaptive Tone Balance defaults to Off.
- Existing `.srpbackup` files remain importable.
- Recommended DSP order remains Sonic Refiner -> R128 Real-time Loudness Normalizer -> Output.

## [0.4.0] - 2026-08-22

### Added
- Temporary A/B comparison slots for Depth, Clarity, Width, Ambience, and Master Strength.
- Playback menu command for direct Sonic Refiner settings access.
- Modeless owned direct-settings window and Keyboard Shortcuts integration.
- Safety checks for missing/multiple active instances and runtime DSP-chain changes.

### Fixed
- Finalized A/B layout readability and group-border rendering in Japanese/English Light/Dark modes.
- Fixed the C3246 service-registration build error found during direct-settings development.

### Compatibility
- DSP processing remains unchanged from v0.3.0.
- SRP3, `preset_version 8`, `.srpbackup`, and existing preset compatibility are unchanged.

## [0.4.0-dev.5] - 2026-08-22

### Fixed
- Fixed the Visual Studio C3246 build failure in the direct-settings main-menu command registration.
- Removed the invalid `final` qualifier from `mainmenu_commands_sonic_refiner_settings`; foobar2000 SDK service registration wraps and derives from this command class.

### Compatibility
- Direct-settings behavior is otherwise unchanged from v0.4.0-dev.4.
- DSP processing, A/B comparison, SRP3, `preset_version 8`, and `.srpbackup` are unchanged.

## [0.4.0-dev.4] - 2026-08-22

### Added
- Playback menu command for direct Sonic Refiner settings access.
- Modeless owned settings window so foobar2000 remains usable while editing.
- Keyboard Shortcuts integration through the main-menu command.
- Safety checks for missing or multiple Sonic Refiner instances in the active DSP chain.
- Runtime detection if the target Sonic Refiner is removed or duplicated while direct editing is open.

### Compatibility
- DSP processing is unchanged from v0.4.0-dev.3.
- SRP3, preset_version 8 and .srpbackup remain unchanged.
- The conventional DSP Manager configuration path remains available.

All notable public changes to Sonic Refiner are documented here.

## [0.4.0-dev.3] - 2026-08-22

### Fixed
- Prevented the lower-left border of the Master/Output/Protection group from being erased by the extreme-range notice control.
- Kept the settings window at 560 x 320 with no A/B or DSP behavior changes.

## [0.4.0-dev.2] - 2026-08-22

### Fixed
- Improved disabled End Comparison button readability in dark mode.
- Adjusted A/B and Master/Output/Protection layout spacing while retaining the 560 x 320 settings window.

## [0.4.0-dev.1] - 2026-08-22

### Added
- Temporary A/B comparison slots for Depth, Clarity, Width, Ambience, and Master Strength
- Instant A/B listening with restoration of the settings present before comparison began
- Japanese/English A/B comparison controls and status text

### Compatibility
- DSP processing algorithm is unchanged from v0.3.0
- `preset_version 8` remains unchanged
- User-preset write format remains `SRP3`
- `.srpbackup` format remains unchanged
- A/B slots are held only in memory and are cleared when foobar2000 exits

## [0.3.0] - 2026-08-06

### Added

- Japanese and English user interface
- Language selection based on the Windows display language on first use
- Instant language switching without restarting foobar2000
- Persistent language preference stored separately from DSP settings
- Localized built-in preset names, controls, messages, file dialogs, Help, Glossary, Important Notes and License pages
- English-first public documentation

### Compatibility

- DSP processing behavior is unchanged from v0.2.0
- `preset_version 8` remains unchanged
- User-preset format remains `SRP3`
- SRP1, SRP2 and SRP3 remain readable
- `.srpbackup` format remains unchanged
- Existing user-preset names are preserved and are not translated
- Settings window remains 560 × 320

### Validation

- Release / x64 build and package creation confirmed
- Japanese and English switching confirmed without restart or crash
- User-preset save/load and backup export/import confirmed
- Light and dark modes, restart persistence, cancellation, and continuous playback operation confirmed

## [0.2.0] - 2026-08-03

### Added

- Master Strength control from 0% to 100%
- Effective-value labels that reflect Master Strength
- SRP3 user-preset format with Master Strength storage
- Integrated Help, Glossary and Safety Notice documentation for Master Strength

### Compatibility

- v0.1.x DSP settings load with Master Strength at 100%
- SRP1 and SRP2 user presets load with Master Strength at 100%
- Output Gain, Automatic Headroom and Level Match are not scaled
- Existing built-in presets retain their original sound at 100%
- Confirmed operation at 0%, 50% and 100%, preset save/restore, backup import/export, restart persistence, cancellation, light/dark modes and continuous playback control

## [0.1.1] - 2026-08-02

### Changed

- Unified the official downstream normalizer name as
  `R128 Real-time Loudness Normalizer`
- Updated the integrated Help, Glossary and Safety Notices
- Updated README, Quick Start, component package documentation and release notes
- Updated the formal package version and filename to `v0.1.1`

### Compatibility

- No DSP processing behavior was changed
- No preset values or preset file formats were changed
- Existing settings and SRP1/SRP2 user presets remain compatible

## [0.1.0] - 2026-08-02

### Added

- Initial public release
- Depth low-frequency enhancement
- Clarity high-frequency enhancement
- Frequency-dependent stereo Width processing with low-frequency protection
- Short early-reflection Ambience processing
- Output Gain from -12.0 dB to +6.0 dB
- Automatic headroom protection
- Level-matched bypass comparison
- Eleven built-in presets
- Up to 20 user presets
- User-preset export and import using `.srpbackup`
- Integrated Help, Glossary, Safety Notices and License pages
- Light and dark mode support
- Automated Release/x64 build and `.fb2k-component` packaging
- SHA-256 checksum generation

### Compatibility

- Reads legacy preview DSP settings
- Reads SRP1 and SRP2 user-preset formats
- Legacy settings without Output Gain load at 0.0 dB

### Notes

- Values from 80% to 100% are intended for strong effects and testing.
- Automatic Headroom is not a True Peak limiter.
- Recommended DSP order:
  `Sonic Refiner -> R128 Real-time Loudness Normalizer -> output`
