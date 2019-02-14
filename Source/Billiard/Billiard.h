#pragma once

#include <iostream>
#include <vector>

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include "camera/Camera.h"
#include "transform3D/Transform3D.h"
#include "table/BilliardTable.h"
#include "ball/Ball.h"
#include "ball/WhiteBall.h"
#include "tac/Tac.h"
#include "collision/Collision.h"

class Billiard : public SimpleScene
{
public:
	Billiard();
	~Billiard();

	void Init() override;

private:
	/*
		stare 0 : in care mutam bila, se trece in stare 1 cand se citeste "space"
		stare 1 : in care puteam muta tac-ul
		stare 2 : in care se depleaza tac-ul
		stare 3 : pila este lovita
		stare 4 : desfasureare lovituri
	*/
	int mod;
	bool first = true;
	bool sw = false;
	bool mv = true;

	void printRules();

	MyCamera::Camera *camera;
	glm::mat4 projectionMatrix;

	float clock;
	int isTacActive;

	// pentru retinerea texturilor
	std::unordered_map<std::string, Texture2D*> mapTextures;

	void initTextures();
	void initShaders();
	void initMesh();
	void initBall();

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMeshGeneric(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 color, int isTac, Texture2D* texture = NULL);
	void RenderMeshTexture(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, Texture2D* texture);
	void RenderMeshColor(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 color);
	void RenderTac(Shader * shader, const glm::mat4 & modelMatrix);

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	BilliardTable billiardTable;
	void drawBilliardTable();
	void drawBall();
	void drawTac(float deltaTimeSeconds);

	// bilele :
	WhiteBall * whiteBall;
	std::vector<Ball> redBall;
	std::vector<Ball> yellowBall;
	Ball * blackBall;
	void moveWhiteBall(float deltaX, float deltaZ);
	void moveWhiteBall2(float deltaX, float deltaZ);

	// tacul
	Tac tac;
	float angleTac;
	void generateClock(float deltaTime);

	// functie initializare vitezei:
	void initSpeedWhiteBall();
	void updateBall(float acceleration, float deltaTime);

	const float init_v = 4.0f;
	const float G = 0;

	int turn;
	/*
		0 -> nimeni nu a ales
		1 -> player 1 red, player 2 yellow
		2 -> player 2 red, player 1 yellow
	*/
	int typeBall;
	bool fault = true;
	int nr_fault[2] = { 0, 0 };
	int fault0 = 0;
	int fault1 = 0;

	void checkCollision();
	void collisionManta();
	void collisonBall();
	void collisionHole();

	void cameraSystem();
	glm::vec3 getPosition();
	void checkCondition();
	void nextTurn();
	void removeOutBall();
	void lose();
	void win();

	int outRedTotal = 0;
	int outYellowTotal = 0;
	int outRedTurn = 0;
	int outYellowTurn = 0;

	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	unsigned int materialShininess;
	float materialKd;
	float materialKs;

};