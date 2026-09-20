# Command Cheats Bypass

A LeviLauncher Android native mod project targeting the supplied `libminecraftpe.so`.

## Current state

This first revision is a **safe loader/analysis build**. It loads as a native mod and records the exact offsets discovered in the supplied library, but it intentionally does **not** install a guessed native hook.

The supplied library is:

- ARM64 Android ELF
- NDK r28c build
- Build ID: `868e275cb295e9a275bb29d2258edc2f7dc48761`

The next revision will replace the diagnostic code with the verified command-permission hook and a host-only guard.

## Phone-only build

Push this repository to GitHub and let the included GitHub Actions workflow build the `.levipack`.

The launcher SDK follows the current LeviLaunchroid native-mod path and uses `preloader-android` 0.2.2.
