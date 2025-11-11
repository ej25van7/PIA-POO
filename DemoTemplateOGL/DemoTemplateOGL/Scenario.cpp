#include "Scenario.h"
#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif

Scenario::Scenario(Camera *cam) {
    glm::vec3 translate;
	glm::vec3 scale;
    Model* model = new Model("models/Cube/Cube.obj", cam);
	translate = glm::vec3(0.0f, 0.0f, 3.0f);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	InitGraph(model);
}
Scenario::Scenario(Model *camIni) {
    InitGraph(camIni);
}
void Scenario::InitGraph(Model *main) {
    float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	//Defino las escalas de cada eje por separado
	float escalaY;
	float escalaX;
	float escalaZ;
	//Defino las posiciones de cada eje por separado
	float posX;
	float posY;
	float posZ;
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 20, (WCHAR*)L"skydome/cielo.jpg", main->cameraDetails);
	//creamos el terreno
	terreno = new Terreno((WCHAR*)L"skydome/terreno2.jpg", (WCHAR*)L"skydome/piso.jpg", 400, 400, main->cameraDetails);
	water = new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/water.bmp", 5, 5, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	translate = glm::vec3(80.0f, 1.0f, 40.0f);
	water->setTranslate(&translate);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	water->setScale(&scale);
	// load models
	// -----------
	ourModel.emplace_back(main);
	Model* model;

	/*ESTO CARGA AL PEZ Y LO CLONA
	Model *pez = new Model("models/pez/pez.obj", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 50.0f), 50.0f);
	pez->setNextTranslate(&translate);
	pez->setTranslate(&translate);
	ourModel.emplace_back(pez);
	ModelAttributes m;
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x = 5;
	model = CollitionBox::GenerateAABB(m.translate, pez->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	m.hitbox = model;
	pez->getModelAttributes()->push_back(m);
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x = 10;
	model = CollitionBox::GenerateAABB(m.translate, pez->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	m.hitbox = model; // Le decimos al ultimo ModelAttribute que tiene un hitbox asignado
	pez->getModelAttributes()->push_back(m);

	//ESTO CARGA SILLY DANCING Y LO CLONA CON ANIMACIONES
	Model* silly = new Model("models/Silly_Dancing/Silly_Dancing.fbx", main->cameraDetails);
	translate = glm::vec3(10.0f, terreno->Superficie(10.0f, 60.0f) , 60.0f);
	scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
	silly->setTranslate(&translate);
	silly->setNextTranslate(&translate);
	silly->setScale(&scale);
	silly->setNextRotY(180);
	ourModel.emplace_back(silly);
	try{
		std::vector<Animation> animations = Animation::loadAllAnimations("models/Silly_Dancing/Silly_Dancing.fbx", silly->GetBoneInfoMap(), silly->getBonesInfo(), silly->GetBoneCount());
		for (Animation animation : animations)
			silly->setAnimator(Animator(animation));
		silly->setAnimation(0);
	}catch(...){
		ERRORL("Could not load animation!", "ANIMACION");
	}
	m.setTranslate(&translate);
	m.setNextTranslate(&translate);
	m.translate.x += 10;
	m.setScale(&scale);
	m.setNextRotY(180);
	m.setRotY(180);
	model = CollitionBox::GenerateAABB(m.translate, silly->AABBsize, main->cameraDetails);
	model->setTranslate(&m.translate);
	model->setNextTranslate(&m.translate);
	model->setScale(&scale);
	model->setNextRotY(180);
	model->setRotY(180);
	m.hitbox = model; // Le decimos al ultimo ModelAttribute que tiene un hitbox asignado
	silly->getModelAttributes()->push_back(m);
	// Import model and clone with bones and animations
	model = new Model("models/Silly_Dancing/Silly_Dancing.fbx", main->cameraDetails);
	translate = glm::vec3(30.0f, terreno->Superficie(30.0f, 60.0f) , 60.0f);
	scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
	model->name = "Silly_Dancing1";
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	model->setScale(&scale);
	model->setNextRotY(180);
	ourModel.emplace_back(model);
	// Para clonar la animacion se eliminan los huesos del modelo actual y se copian los modelos y animators
	model->GetBoneInfoMap()->clear();
	model->getBonesInfo()->clear();
	*model->GetBoneInfoMap() = *silly->GetBoneInfoMap();
	*model->getBonesInfo() = *silly->getBonesInfo();
	model->setAnimator(silly->getAnimator());*/

	

	//CARGAMOS EL ARBOL1
	Model* arbol1 = new Model("models/Arbol1/arbol1.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.7f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 30.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	arbol1->setTranslate(&translate);
	arbol1->setNextTranslate(&translate);
	arbol1->setNextRotX(-90);
	arbol1->setScale(&scale);
	ourModel.emplace_back(arbol1);

	// CARGAMOS EL ARBOL2
		Model * arbol2 = new Model("models/Arbol2/arbol2.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.7f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 50.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	arbol2->setTranslate(&translate);
	arbol2->setNextTranslate(&translate);
	arbol2->setNextRotX(-90);
	arbol2->setScale(&scale);
	ourModel.emplace_back(arbol2);
	
	// CARGAMOS EL ARBOL3
	Model* arbol3 = new Model("models/Arbol3/arbol3.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.7f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 70.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	arbol3->setTranslate(&translate);
	arbol3->setNextTranslate(&translate);
	arbol3->setNextRotX(-90);
	arbol3->setScale(&scale);
	ourModel.emplace_back(arbol3);

	// CARGAMOS EL ARBOL4
	Model* arbol4 = new Model("models/Arbol4/arbol4.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 1.3f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 90.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	arbol4->setTranslate(&translate);
	arbol4->setNextTranslate(&translate);
	arbol4->setNextRotX(-90);
	arbol4->setScale(&scale);
	ourModel.emplace_back(arbol4);

	// CARGAMOS EL ARBUSTO
	Model* arbusto = new Model("models/Arbusto/arbusto.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 1.0f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 110.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	arbusto->setTranslate(&translate);
	arbusto->setNextTranslate(&translate);
	arbusto->setNextRotX(-90);
	arbusto->setScale(&scale);
	ourModel.emplace_back(arbusto);

	// CARGAMOS EL BANCO
	Model* banco = new Model("models/Banco/banco.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 2.0f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 120.0f;
	posZ = -10.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	banco->setTranslate(&translate);
	banco->setNextTranslate(&translate);
	banco->setNextRotX(-90);
	banco->setScale(&scale);
	ourModel.emplace_back(banco);

	// CARGAMOS EL FANTASMA
	Model* fantasma = new Model("models/Fantasma/fantasma.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 10.0f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 110.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ)+1; //+1 para que siempre este flotando independientemente de si la superficie varía
	translate = glm::vec3(posX, posY, posZ);
	fantasma->setTranslate(&translate);
	fantasma->setNextTranslate(&translate);
	fantasma->setNextRotY(180);
	fantasma->setScale(&scale);
	ourModel.emplace_back(fantasma);

	// CARGAMOS LA LAMPARA
	Model* lampara = new Model("models/Lampara/lampara.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 3.0f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 100.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	lampara->setTranslate(&translate);
	lampara->setNextTranslate(&translate);
	lampara->setNextRotX(-90);
	lampara->setScale(&scale);
	ourModel.emplace_back(lampara);


	// CARGAMOS LA VALLA
	Model* valla = new Model("models/Valla/valla.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.8f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 90.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	valla->setTranslate(&translate);
	valla->setNextTranslate(&translate);
	valla->setNextRotX(-90);
	valla->setScale(&scale);
	ourModel.emplace_back(valla);

	//CARGAMOS LA CABAÑA
	Model* cabin = new Model("models/Cabin/cabin.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.5f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 50.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	cabin->setTranslate(&translate);
	cabin->setNextTranslate(&translate);
	cabin->setNextRotX(-90);
	cabin->setNextRotZ(180);
	cabin->setScale(&scale);
	ourModel.emplace_back(cabin);

	//CARGAMOS EL GATO
	Model* gato = new Model("models/Gato/gato.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.01f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 20.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	gato->setTranslate(&translate);
	gato->setNextTranslate(&translate);
	gato->setScale(&scale);
	ourModel.emplace_back(gato);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/Gato/gato.fbx", gato->GetBoneInfoMap(), gato->getBonesInfo(), gato->GetBoneCount());
		for (Animation animation : animations)
			gato->setAnimator(Animator(animation));
		gato->setAnimation(0);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}

	//CARGAMOS EL OTRO FANTASMA
	Model* fantasma2 = new Model("models/Fantasma2/fantasma2.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.02f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = 0.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	fantasma2->setTranslate(&translate);
	fantasma2->setNextTranslate(&translate);
	fantasma2->setScale(&scale);
	ourModel.emplace_back(fantasma2);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/Fantasma2/fantasma2.fbx", fantasma2->GetBoneInfoMap(), fantasma2->getBonesInfo(), fantasma2->GetBoneCount());
		for (Animation animation : animations)
			fantasma2->setAnimator(Animator(animation));
		fantasma2->setAnimation(0);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}

	//CARGAMOS EL PERRO
	Model* perro = new Model("models/Perro/perro.fbx", main->cameraDetails);
	escalaX = escalaY = escalaZ = 0.03f;
	scale = glm::vec3(escalaX, escalaY, escalaZ);
	posX = -10.0f;
	posZ = 30.0f;
	posY = terreno->Superficie(posX, posZ);
	translate = glm::vec3(posX, posY, posZ);
	perro->setTranslate(&translate);
	perro->setNextTranslate(&translate);
	perro->setScale(&scale);
	ourModel.emplace_back(perro);
	try {
		std::vector<Animation> animations = Animation::loadAllAnimations("models/Perro/perro.fbx", perro->GetBoneInfoMap(), perro->getBonesInfo(), perro->GetBoneCount());
		for (Animation animation : animations)
			perro->setAnimator(Animator(animation));
		perro->setAnimation(0);
	}
	catch (...) {
		ERRORL("Could not load animation!", "ANIMACION");
	}


	

	//CARGA BILLBOARDS
	inicializaBillboards();
	std::wstring prueba(L"Alooo jugador");
	ourText.emplace_back(new Texto(prueba, 20, 0, 0, SCR_HEIGHT, 0, camara));
	//billBoard2D.emplace_back(new Billboard2D((WCHAR*)L"billboards/awesomeface.png", 6, 6, 100, 200, 0, camara->cameraDetails));
	//scale = glm::vec3(100.0f, 100.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	//billBoard2D.back()->setScale(&scale);
	}

void Scenario::inicializaBillboards() {
	float ye = terreno->Superficie(0, 0);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol.png", 6, 6, 0, ye - 1, 0, camara->cameraDetails));

	ye = terreno->Superficie(-9, -15);
	billBoard.emplace_back(new Billboard((WCHAR*)L"billboards/Arbol3.png", 8, 8, -9, ye - 1, -15, camara->cameraDetails));

	BillboardAnimation *billBoardAnimated = new BillboardAnimation();
	ye = terreno->Superficie(5, -5);
	for (int frameArbol = 1; frameArbol < 4; frameArbol++){
		wchar_t textura[50] = {L"billboards/Arbol"};
		if (frameArbol != 1){
			wchar_t convert[25];
			swprintf(convert, 25, L"%d", frameArbol);
			wcscat_s(textura, 50, convert);
		}
		wcscat_s(textura, 50, L".png");
		billBoardAnimated->pushFrame(new Billboard((WCHAR*)textura, 6, 6, 5, ye - 1, -5, camara->cameraDetails));		
	}
	billBoardAnim.emplace_back(billBoardAnimated);
}

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
Scene* Scenario::Render() {
	//borramos el biffer de color y el z para el control de profundidad a la 
	//hora del render a nivel pixel.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

	if (this->animacion > 10) { // Timer se ejecuta cada 1000/30 = 33.333 ms
		for (BillboardAnimation *b : billBoardAnim){
			b->nextAnimation();
		}
		this->animacion = 0;
	} else {
		animacion = animacion + (1 * gameTime.deltaTime/100);
	}
	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	terreno->Draw();
	water->Draw();
	// Dibujamos cada billboard que este cargado en el arreglo de billboards.
	for (int i = 0; i < billBoard.size(); i++)
		billBoard[i]->Draw();
	for (int i = 0; i < billBoardAnim.size(); i++)
		billBoardAnim[i]->Draw();
	for (int i = 0; i < billBoard2D.size(); i++)
		billBoard2D[i]->Draw();
	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
	for (int i = 0; i < ourModel.size(); i++) {
			ourModel[i]->Draw();
	}
	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}
		// Le decimos a winapi que haga el update en la ventana
	return this;
}
	
std::vector<Model*> *Scenario::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*> *Scenario::getLoadedBillboards() {
	return &billBoard;
}
std::vector<Billboard2D*> *Scenario::getLoadedBillboards2D(){
	return &billBoard2D;
}
std::vector<Texto*> *Scenario::getLoadedText(){
	return &ourText;
}
std::vector<BillboardAnimation*> *Scenario::getLoadedBillboardsAnimation(){
	return &billBoardAnim;
}

Model* Scenario::getMainModel() {
	return this->camara;
}
void Scenario::setMainModel(Model* mainModel){
	this->camara = mainModel;
}
float Scenario::getAngulo() {
	return this->angulo;
}
void Scenario::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario::getSky() {
	return sky;
}
Terreno* Scenario::getTerreno() {
	return terreno;
}

Scenario::~Scenario() {
	if (this->sky != NULL) {
		delete this->sky;
		this->sky = NULL;
	}
	if (this->terreno != NULL) {
		delete this->terreno;
		this->terreno = NULL;
	}
	if (billBoard.size() > 0)
		for (int i = 0; i < billBoard.size(); i++)
			delete billBoard[i];
	if (billBoardAnim.size() > 0)
		for (int i = 0; i < billBoardAnim.size(); i++)
			delete billBoardAnim[i];
	if (billBoard2D.size() > 0)
		for (int i = 0; i < billBoard2D.size(); i++)
			delete billBoard2D[i];
	this->billBoard.clear();
	if (ourText.size() > 0)
		for (int i = 0; i < ourText.size(); i++)
			if (!(ourText[i]->name.compare("FPSCounter") || ourText[i]->name.compare("Coordenadas")))
				delete ourText[i];
	this->ourText.clear();
	if (ourModel.size() > 0)
		for (int i = 0; i < ourModel.size(); i++)
			if (ourModel[i] != camara)
			delete ourModel[i];
	this->ourModel.clear();
}
