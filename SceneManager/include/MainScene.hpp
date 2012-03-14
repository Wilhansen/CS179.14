
#ifndef Fourobo_MainScene_hpp
#define Fourobo_MainScene_hpp

#include "SceneManager.hpp"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIO.h"
#include "PauseScene.hpp"
#include <fstream>

class MainScene : public SceneManager::Scene {
	ci::Vec2f pos;
	float t;
	
	int tileRows, tileCols;
	
	std::vector<int> tileMap;
	
	PauseScene ps;
	
	virtual void onDeactivate(SceneManager &sm) {
		//delete this;
	}
public:
	ci::gl::Texture tiles;
	MainScene() : pos(0,0), t(0), ps(this) {
	}
	
	virtual void onLoad() {
		using namespace ci;
		std::ifstream f(
						app::loadResource("level.txt")->getFilePathHint().c_str()
						);
		f >> tileCols >> tileRows;
		tileMap.resize(tileCols * tileRows);
		for ( size_t i = 0; i < tileMap.size(); ++i )
			f >> tileMap[i];
		
		tiles = gl::Texture(loadImage(app::loadResource("tiles.png")));
	}
	
	virtual void draw() {
		using namespace ci;
		for ( size_t y = 0; y < tileRows; ++y ) {
			for ( size_t x = 0; x < tileCols; ++x ) {
				int index = tileMap[y * tileCols + x];
				
				const int TILE_SIZE = 32;
				
				const Vec2f ul((index % 2) * TILE_SIZE,(index/2) * TILE_SIZE);
				Vec2f lr = ul + Vec2f(TILE_SIZE,TILE_SIZE);
				Area src(ul, lr);
				
				Vec2f destUL(x * TILE_SIZE * 2.5, y * TILE_SIZE * 2.5);
				gl::draw(tiles, src, Rectf(destUL, destUL + Vec2f(TILE_SIZE * 2.5, TILE_SIZE * 2.5)));
			}
		}
		gl::color(255,128,128);
		
		gl::drawSolidCircle(pos, 50);
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
