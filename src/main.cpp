#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(PlayerObject) {
public:
    // check if gd is in gameplay, runs when player starts or stops holding
	bool integrityCheck() {
        if (!PlayLayer::get()) {
            if (!LevelEditorLayer::get()) {
                return false;
            }
        }
        return true;
    }

    bool pushButton(PlayerButton p0) {
        if (!integrityCheck()) return PlayerObject::pushButton(p0);		
        if (PlayerObject::pushButton(p0) && m_isSwing) {
            GJBaseGameLayer::get()->m_player1->flipGravity(m_isUpsideDown, true);
            GJBaseGameLayer::get()->m_player2->flipGravity(m_isUpsideDown, true); 
            return true;
        }
        return false;
    }

    bool releaseButton(PlayerButton p0) {
		if (!integrityCheck()) return PlayerObject::releaseButton(p0);		
        if (PlayerObject::releaseButton(p0) && m_isSwing) {
            GJBaseGameLayer::get()->m_player1->flipGravity(!m_isUpsideDown, true);
            GJBaseGameLayer::get()->m_player2->flipGravity(!m_isUpsideDown, true); 
            return true;
        }
        return false;
    }

};
