
#ifndef Fourobo_MainScene_hpp
#define Fourobo_MainScene_hpp

#include "SceneManager.hpp"
#include "cinder/gl/gl.h"
#include "PauseScene.hpp"

class MainScene : public SceneManager::Scene {
	ci::Vec2f pos;
	float t;
	
	PauseScene ps;
	
	virtual void onDeactivate(SceneManager &sm) {
		//delete this;
	}
public:
	MainScene() : pos(0,0), t(0), ps(this) {}
	
	virtual void draw() {
		ci::gl::color(255,128,128);
		
		ci::gl::drawSolidCircle(pos, 50);
	}
	
	virtual void update(float dt) {
		t += dt;
		pos.x = cos(t) * 100 + 250;
		pos.y = sin(t) * 100 + 250;
	}
	
	void onKeyUp(ci::app::KeyEvent &e) {
		if ( e.getCode() == ci::app::KeyEvent::KEY_SPACE ) {
			//shove pause scene
			getManager()->push(&ps);
		}
	}
};

#endif
