#include "Application.h"
#include "SceneBlinnPhong.h"
#include "ScenePBR.h"
#include "SceneTerrain.h"
#include "SceneParticles.h"
#include "ScenePointSprite.h"
#include "SceneRipple.h"
#include "SceneSubdivide.h"
int main() {
	Application app("Nano3DViewer", 800, 600, 4);
	// SceneBlinnPhong scene;
	// ScenePBR scene;
	// SceneTerrain scene;
	// SceneParticles scene;
	// ScenePointSprite scene;
	// SceneRipple scene;
	SceneSubdivide scene;
	app.addScene(&scene);
	app.run();
}
