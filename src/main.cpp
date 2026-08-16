#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

static const int FIRST_DEMON_ID = 10565723; // Bloodbath
static const int SECOND_DEMON_ID = 21086082; // Target Demon

class $modify(DemonSwitcherLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSign) {
        if (!PlayLayer::init(level, useReplay, dontSign)) return false;

        bool beatFirst = Mod::get()->getSavedValue<bool>(fmt::format("beat_{}", FIRST_DEMON_ID), false);

        if (beatFirst && level && level->m_levelID == FIRST_DEMON_ID) {
            log::info("Bloodbath beaten! Redirecting...");

            auto targetLevel = GameLevelManager::sharedState()->getMainLevel(SECOND_DEMON_ID, nullptr);
            if (targetLevel) {
                auto scene = PlayLayer::scene(targetLevel, false, false);
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
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
