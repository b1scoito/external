# external
 
 CS:GO external cheat with the most basic features that I like to use such as perfect bhop and non-flickering glow, really focused on performance.  
 I made this for fun and personal use, don't expect it to be reliable for you.

## Credits

- [qo0-base](https://github.com/rollraw/qo0-base) for their structs and organized code.
- [hazedumper](https://github.com/frk1/hazedumper) for all the offsets.

## Compiling

You need [LLVM-Obfuscator](https://github.com/heroims/obfuscator) for [Clang 13](https://github.com/heroims/obfuscator/tree/llvm-13.x) to successfully compile this project in Release.
Once installed, follow [this guide](https://docs.microsoft.com/en-us/cpp/build/clang-support-msbuild?view=msvc-170#custom_llvm_location) and change the property `LLVMInstallDir` to the path of the compiled llvm-obfuscator with the libraries and binaries.

## Keybinds

- `Mouse 5` - Hold for triggerbot
- `Home` - Toggle for glow
- `Del` - Unload
- `End` - Toggle skin changer (currently hard-coded vanilla M9 Bayonet, high cpu usage, unstable, may cause the cheat or the game to crash.)
