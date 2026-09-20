#include "CommandCheatsBypass.h"

#include <cstdint>
#include <iomanip>
#include <sstream>

namespace {
// Static RVAs discovered in the supplied libminecraftpe.so.
// These are analysis notes only; they are NOT hooked yet.
constexpr std::uintptr_t kCheatsRequiredStringRva = 0x2306368;
constexpr std::uintptr_t kAreCheatsEnabledStringRva = 0x22fb77a;
constexpr std::uintptr_t kAllowCheatsStringRva = 0x238f9ff;
constexpr std::uintptr_t kCheatsAllowedStringRva = 0x2657927;
constexpr std::uintptr_t kRequiresCheatsStringRva = 0x26887ff;
constexpr std::uintptr_t kIsLocalPlayerHostingStringRva = 0x238b969;
}

CommandCheatsBypass& CommandCheatsBypass::instance() {
    static CommandCheatsBypass mod;
    return mod;
}

CommandCheatsBypass::CommandCheatsBypass()
    : mSelf(*ll::mod::NativeMod::current()) {}

bool CommandCheatsBypass::load() {
    auto& log = getSelf().getLogger();
    log.info("Loaded {} v{}", getSelf().getName(), getSelf().getVersion());
    log.info("Target library: libminecraftpe.so (ARM64)");
    log.info("Analysis Build ID: 868e275cb295e9a275bb29d2258edc2f7dc48761");
    log.info("cheatsRequired string RVA: 0x{:x}", kCheatsRequiredStringRva);
    log.info("areCheatsEnabled string RVA: 0x{:x}", kAreCheatsEnabledStringRva);
    log.info("allowCheats string RVA: 0x{:x}", kAllowCheatsStringRva);
    log.info("cheatsAllowed string RVA: 0x{:x}", kCheatsAllowedStringRva);
    log.info("requires_cheats string RVA: 0x{:x}", kRequiresCheatsStringRva);
    log.info("isLocalPlayerHosting string RVA: 0x{:x}", kIsLocalPlayerHostingStringRva);
    return true;
}

bool CommandCheatsBypass::enable() {
    // Deliberately no binary hook is installed until the exact command
    // permission function and ABI have been verified for this library.
    getSelf().getLogger().info(
        "Native mod enabled; command hook pending exact target verification.");
    return true;
}

bool CommandCheatsBypass::disable() {
    return true;
}

bool CommandCheatsBypass::unload() {
    return true;
}
