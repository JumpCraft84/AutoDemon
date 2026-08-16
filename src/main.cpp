#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static const int FIRST_DEMON_ID = 10565723;  // Bloodbath
static const int SECOND_DEMON_ID = 21086082; // Target Demon

class $modify(DemonSwitcherLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSign) {
        if (!PlayLayer::init(level, useReplay, dontSign)) return false;

        bool beatFirst = Mod::get()->getSavedValue<bool>(fmt::format("beat_{}", FIRST_DEMON_ID), false);

        if (beatFirst && level && level->m_levelID == FIRST_DEMON_ID) {
            log::info("Bloodbath beat! Loading target level...");

            auto levelObj = GameLevelManager::sharedState()->getMainLevel(SECOND_DEMON_ID, nullptr);
            if (levelObj) {
                auto scene = PlayLayer::scene(levelObj, false, false);
                CCDirector::sharedDirector()->replaceScene(scene);
                return false;
            }
        }

        return true;
    }

    void levelComplete() {
        PlayLayer::levelComplete();

        if (m_level && m_level->m_levelID == FIRST_DEMON_ID) {
            Mod::get()->setSavedValue<bool>(fmt::format("beat_{}", FIRST_DEMON_ID), true);
            log::info("Bloodbath completed!");
        }
    }
};
