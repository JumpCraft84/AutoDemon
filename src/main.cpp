#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

// Set your Level IDs here
static const int FIRST_DEMON_ID = 10565723;  // Bloodbath (Example ID)
static const int SECOND_DEMON_ID = 21086082; // Different Demon ID

class $modify(DemonSwitcherLayer, PlayLayer) {
    bool init(GJGameLevel* level, bool useReplay, bool dontSign) {
        // If the player beat the first demon, redirect them to the second demon
        bool beatFirst = Mod::get()->getSavedValue<bool>(fmt::format("beat_{}", FIRST_DEMON_ID), false);

        if (beatFirst && level->m_levelID.value() == FIRST_DEMON_ID) {
            log::info("Bloodbath already beaten! Loading second Demon...");
            
            // Fetch level object for second demon and load it
            auto targetLevel = GameLevelManager::sharedState()->getMainLevel(SECOND_DEMON_ID, nullptr);
            if (targetLevel) {
                auto scene = PlayLayer::scene(targetLevel, false, false);
                CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
                return false;
            }
        }

        return PlayLayer::init(level, useReplay, dontSign);
    }

    void levelComplete() {
        // Mark Bloodbath as completed when reaching 100%
        if (m_level && m_level->m_levelID.value() == FIRST_DEMON_ID) {
            Mod::get()->setSavedValue<bool>(fmt::format("beat_{}", FIRST_DEMON_ID), true);
            log::info("Bloodbath completed! Redirect unlocked for next attempt.");
        }

        PlayLayer::levelComplete();
    }
};
