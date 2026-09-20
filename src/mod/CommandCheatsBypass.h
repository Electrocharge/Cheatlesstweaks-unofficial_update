#pragma once

#include <pl/Mod.hpp>

class CommandCheatsBypass {
public:
    static CommandCheatsBypass& instance();

    CommandCheatsBypass();

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

private:
    ll::mod::NativeMod& mSelf;
};
