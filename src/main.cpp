#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(PlayerObject) {
    bool pushButton(PlayerButton p0) {
        if (!m_gameLayer) return PlayerObject::pushButton(p0);

        bool ret = PlayerObject::pushButton(p0);
        if (ret && m_isSwing) {
            this->flipGravity(this->m_isUpsideDown, true);
        }

        return ret;
    }

    bool releaseButton(PlayerButton p0) {
        if (!m_gameLayer) return PlayerObject::releaseButton(p0);

        bool ret = PlayerObject::releaseButton(p0);
        if (ret && m_isSwing) {
            this->flipGravity(!this->m_isUpsideDown, true);
        }

        return ret;
    }
};

// uninstall popup.
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        if (Mod::get()->getSavedValue<bool>("never-show")) return true;

        auto popup = createQuickPopup(
            "Shipcopter Mod",
            "Shipcopter (by Beat) is no longer supported. Please use the Shipcopter hack in Eclipse Menu or Mega Hack instead. \n\nUninstall Shipcopter and restart?",
            "Never show", "Uninstall",
            [this](auto, bool btn2) {
                if (btn2) {
                    Mod::get()->uninstall(true);
                    game::restart();

                } else {
                    Mod::get()->setSavedValue<bool>("never-show", true);
                }
            }, false
        );
        popup->m_scene = this;
        popup->show();
        return true;
    }
};