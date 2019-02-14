#include "Billiard.h"

Billiard::Billiard()
{
}

Billiard::~Billiard()
{
	delete this->whiteBall;
	delete this->blackBall;
}

void Billiard::Init()
{
	mod = 0;
	turn = 0;
	typeBall = 0;
	camera = new MyCamera::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	isTacActive = 0;
	angleTac = 0;

	initShaders();
	initTextures();
	initMesh();
	initBall();

	//Light & material properties
	{
		lightPosition = glm::vec3(0, 2, 0);
		lightDirection = glm::vec3(0, -1, 0);
		materialShininess = 30;
		materialKd = 1;
		materialKs = 1;
	}

	printRules();
}

/********************************************************************** Reguli *****************************************************************/

void Billiard::printRules()
{
	std::cout <<  std::endl << std::endl << std::endl;
	std::cout << "								                                                                                                           dddddddd" << std::endl;
	std::cout << "BBBBBBBBBBBBBBBBB          iiii       lllllll      lllllll        iiii                                                                   d::::::d" << std::endl;
	std::cout << "B::::::::::::::::B        i::::i      l:::::l      l:::::l       i::::i                                                                  d::::::d" << std::endl;
	std::cout << "B::::::BBBBBB:::::B        iiii       l:::::l      l:::::l        iiii                                                                   d::::::d" << std::endl;
	std::cout << "BB:::::B     B:::::B                  l:::::l      l:::::l                                                                               d:::::d " << std::endl;
	std::cout << "  B::::B     B:::::B     iiiiiii       l::::l       l::::l      iiiiiii        aaaaaaaaaaaaa        rrrrr   rrrrrrrrr            ddddddddd:::::d " << std::endl;
	std::cout << "  B::::B     B:::::B     i:::::i       l::::l       l::::l      i:::::i        a::::::::::::a       r::::rrr:::::::::r         dd::::::::::::::d " << std::endl;
	std::cout << "  B::::BBBBBB:::::B       i::::i       l::::l       l::::l       i::::i        aaaaaaaaa:::::a      r:::::::::::::::::r       d::::::::::::::::d " << std::endl;
	std::cout << "  B:::::::::::::BB        i::::i       l::::l       l::::l       i::::i                 a::::a      rr::::::rrrrr::::::r     d:::::::ddddd:::::d " << std::endl;
	std::cout << "  B::::BBBBBB:::::B       i::::i       l::::l       l::::l       i::::i          aaaaaaa:::::a       r:::::r     r:::::r     d::::::d    d:::::d " << std::endl;
	std::cout << "  B::::B     B:::::B      i::::i       l::::l       l::::l       i::::i        aa::::::::::::a       r:::::r     rrrrrrr     d:::::d     d:::::d " << std::endl;
	std::cout << "  B::::B     B:::::B      i::::i       l::::l       l::::l       i::::i       a::::aaaa::::::a       r:::::r                 d:::::d     d:::::d " << std::endl;
	std::cout << "  B::::B     B:::::B      i::::i       l::::l       l::::l       i::::i      a::::a    a:::::a       r:::::r                 d:::::d     d:::::d " << std::endl;
	std::cout << "BB:::::BBBBBB::::::B     i::::::i     l::::::l     l::::::l     i::::::i     a::::a    a:::::a       r:::::r                 d::::::ddddd::::::dd" << std::endl;
	std::cout << "B:::::::::::::::::B      i::::::i     l::::::l     l::::::l     i::::::i     a:::::aaaa::::::a       r:::::r                  d:::::::::::::::::d" << std::endl;
	std::cout << "B::::::::::::::::B       i::::::i     l::::::l     l::::::l     i::::::i      a::::::::::aa:::a      r:::::r                   d:::::::::ddd::::d" << std::endl;
	std::cout << "BBBBBBBBBBBBBBBBB        iiiiiiii     llllllll     llllllll     iiiiiiii       aaaaaaaaaa  aaaa      rrrrrrr                    ddddddddd   ddddd" << std::endl;
	std::cout << std::endl << std::endl << std::endl << std::endl;
	
	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<          REGULI          >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;

	std::cout << "\t2) Culoarea unui jucator se alege la inceput. In joc sunt doua culori : rosu si galben." << std::endl;
	std::cout << "\"Culoarea cu care joaca un player este aleasa in momentul in care jucatorul introduce in "<< std::endl;
	std::cout << "buzunar prima bila de culoare galbena sau rosie. Dupa aceea, jucatorul respectiv trebuie" << std::endl;
	std::cout << "sa introduca toate bilele de culoarea respectiva in buzunar, iar celalalt jucator trebuie" << std::endl;
	std::cout << "sa introduca bilele de cealalta culoare.\"" << std::endl;
	std::cout << "\t3) Un jucator poate sa faca maxim 7 faut-uri. Un fault insemana :" << std::endl;
	std::cout << "a. \"Daca un jucator, la o lovitura, nu isi atinge prima data propriile bile\"" << std::endl;
	std::cout << "b. Introducearea bilei albe." << std::endl;
	std::cout << "\t4) Daca s-a introdus bila negra fara sa introduci celelate bile, cum este mentionat mai sus, " << std::endl;
	std::cout << "duce la pirderea jocului " << std::endl;
	std::cout << "\t5)\"Jucatorul care incepe va putea deplasa bila alba in prima treime a mesei. Dupa ce a mutat" << std::endl;
	std::cout << "bila unde doreste cu tastele “WASD”, apasa pe \"SPACE\".\"" << std::endl;
	std::cout << "\t6)\"\"Right Mouse Button\" se poate misca tacul in jurul bilei albe " << std::endl;
	std::cout << "\t7) Declamsarea lovituri se face prin \"Left Mouse Button\"" << std::endl;
	std::cout << "\t8) \"Daca este comis un fault, celalalt jucator poate plasa bila alba oriunde pe masa cu tastele WASD\"" << std::endl << std::endl;

	std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl << std::endl;

	std::cout << "Urmatoarea tura o sa fie jucatorul : " << turn << std::endl;
}

/***************************************************************************************************************************************************/

void Billiard::initTextures()
{
	const std::string textureLoc = "Source/Billiard/textures/";

	// Load textures
	{
		Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "manta.jpg").c_str(), GL_REPEAT);
		mapTextures["manta"] = texture;
	}

	{
		Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "body.jpg").c_str(), GL_REPEAT);
		mapTextures["body"] = texture;
	}

	{
		Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "surface.jpg").c_str(), GL_REPEAT);
		mapTextures["surface"] = texture;
	}

	{
		Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "silver.jpg").c_str(), GL_REPEAT);
		mapTextures["silver"] = texture;
	}

	{
		Texture2D *texture = new Texture2D();
		texture->Load2D((textureLoc + "tac.jpg").c_str(), GL_REPEAT);
		mapTextures["tac"] = texture;
	}

}

void Billiard::initShaders()
{
	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("ShaderBiliard");
		shader->AddShader("Source/Billiard/shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Billiard/shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Billiard::initMesh()
{
	// Load meshes
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Billiard::initBall()
{
	this->whiteBall = new WhiteBall(billiardTable.getInitPositionWhiteBall(), billiardTable.getRadius());
	this->blackBall = new Ball(billiardTable.getInitPositionBlackBall(), billiardTable.getRadius(), glm::vec3(0));

	for (glm::vec3 position : billiardTable.getInitPositionRedBalls()) {
		this->redBall.push_back(Ball(position, billiardTable.getRadius(), glm::vec3(1, 0, 0)));
	}

	for (glm::vec3 position : billiardTable.getInitPositionYellowBalls()) {
		this->yellowBall.push_back(Ball(position, billiardTable.getRadius(), glm::vec3(1, 1, 0)));
	}
}

void Billiard::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Billiard::Update(float deltaTimeSeconds)
{
	if (mod == 0) {
		angleTac = 0;
		clock = 0;
	}
	removeOutBall();
	cameraSystem();
	//updateBall(- G * billiardTable.coef, deltaTimeSeconds);
	updateBall(-0.25f, deltaTimeSeconds);
	drawBilliardTable();
	

	if(mod != 8)
		drawBall();

	if (mod == 1|| mod == 2 || mod == 3) {
		drawTac(deltaTimeSeconds);
	}

	initSpeedWhiteBall();
	checkCollision();
	nextTurn();
	checkCondition();
	win();
	lose();
}

void Billiard::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Billiard::RenderMeshGeneric(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 color, int isTac, Texture2D * texture)
{
	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// get shader location for uniform mat4 "Model"
	GLint location_model = glGetUniformLocation(shader->program, "Model");
	// set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location_model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// get shader location for uniform mat4 "View"
	GLint location_view = glGetUniformLocation(shader->program, "View");
	// set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(location_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// get shader location for uniform mat4 "Projection"
	GLint location_projection = glGetUniformLocation(shader->program, "Projection");
	//  set shader uniform "Projection" to projectionMatrix
	glUniformMatrix4fv(location_projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture) {
		//activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());
		// Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

		GLint location_useTexture = glGetUniformLocation(shader->program, "useTexture");
		glUniform1i(location_useTexture, 1);
	}
	else {
		GLint location_useTexture = glGetUniformLocation(shader->program, "useTexture");
		glUniform1i(location_useTexture, 0);
	}

	GLint location_object_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(location_object_color, 1, glm::value_ptr(color));

	float cmp = whiteBall->getPositionCenter().z - camera->GetPosition().z;
	float m;
	if (cmp < 0) {
		m = 1.0f;
	}
	else {
		m = -1.0f;
	}

	// Set shader uniforms for light & material properties
	// TODO: Set light position uniform
	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	// TODO: Set eye position (camera position) uniform
	glm::vec3 eyePosition = camera->GetPosition();//GetSceneCamera()->transform->GetWorldPosition();
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	// TODO: Set material property uniforms (shininess, kd, ks, object color) 
	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);

	
	GLint location_clock = glGetUniformLocation(shader->program, "distance");
	glUniform1f(location_clock, m * clock);

	GLint location_angle = glGetUniformLocation(shader->program, "angle");
	glUniform1f(location_angle, angleTac);

	GLint location_isTacActive = glGetUniformLocation(shader->program, "isTacActive");
	glUniform1i(location_isTacActive, isTacActive * isTac);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Billiard::RenderMeshTexture(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, Texture2D * texture)
{
	RenderMeshGeneric(mesh, shader, modelMatrix, glm::vec3(1), 0, texture);
}

void Billiard::RenderMeshColor(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, glm::vec3 color)
{
	RenderMeshGeneric(mesh, shader, modelMatrix, color, 0, NULL);
}

void Billiard::RenderTac(Shader * shader, const glm::mat4 & modelMatrix)
{
	RenderMeshGeneric(meshes["box"], shader, modelMatrix, glm::vec3(0), 1, mapTextures["tac"]);
}

void Billiard::OnInputUpdate(float deltaTime, int mods)
{
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && (mod == 0) || (mod == 1) || (mod == 5)) {
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_W)) {
			camera->TranslateForward(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			camera->TranslateRight(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->TranslateForward(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->TranslateRight(cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			camera->TranslateUpword(-cameraSpeed * deltaTime);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			camera->TranslateUpword(cameraSpeed * deltaTime);
		}
	}

	if (mod == 0 ) {
		if (!sw && mv && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
			if (window->KeyHold(GLFW_KEY_W)) {
				moveWhiteBall(0, -deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_A)) {
				moveWhiteBall(-deltaTime, 0);
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				moveWhiteBall(0, deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				moveWhiteBall(deltaTime, 0);
			}
		}
		else if(sw && !window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
			if (window->KeyHold(GLFW_KEY_W)) {
				moveWhiteBall2(0, -deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_A)) {
				moveWhiteBall2(-deltaTime, 0);
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				moveWhiteBall2(0, deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				moveWhiteBall2(deltaTime, 0);
			}
		}


		if (window->KeyHold(GLFW_KEY_SPACE)) {
			glm::vec3 tacPosition = whiteBall->getPositionCenter() + glm::vec3(0, 0, 1) * ((tac.getDimension().z / 2 + 0.03f) + billiardTable.getRadius());
			tacPosition += glm::vec3(0, 0.01f, 0);
			tac.setPosition(tacPosition);

			tacPosition += glm::vec3(0, 1, 0) *  (4 * billiardTable.getRadius());
			mv = false;
			mod = 1;
		}
	}

	if (mod == 1) {

		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			isTacActive = 1;
			mod = 2;
		}
	}

	if (mod == 2) {
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		}
		else {
			isTacActive = 0;
			mod = 3;
		}
	}
}

void Billiard::OnKeyPress(int key, int mods)
{
}

void Billiard::OnKeyRelease(int key, int mods)
{
}

void Billiard::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && ((mod == 0) || (mod == 4)))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * deltaX);
		}

	}

	if (mod == 1) {
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
			float sensivityOX = 0.001f;

			angleTac += sensivityOX * -deltaX;
		}
	}

}

void Billiard::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Billiard::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Billiard::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Billiard::OnWindowResize(int width, int height)
{
}

void Billiard::drawBilliardTable()
{
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 dimension;

	for (ComponentTable component : billiardTable.getComponent()) {
		position = component.getPosition();
		dimension = component.getDimension();

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshTexture(meshes["box"], shaders["ShaderBiliard"], modelMatrix, mapTextures[component.getTextureName()]);
	}

	for (Hole hole : billiardTable.getHoles()) {
		position = hole.getPosition();
		dimension = glm::vec3(2 * hole.getRadius());

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshColor(meshes["sphere"], shaders["ShaderBiliard"], modelMatrix, glm::vec3(0));
	}

	for (ComponentTable component : billiardTable.getManta()) {
		position = component.getPosition();
		dimension = component.getDimension();

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshTexture(meshes["box"], shaders["ShaderBiliard"], modelMatrix, mapTextures[component.getTextureName()]);
	}
}

void Billiard::drawBall()
{
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 dimension;

	if (!whiteBall->inHole()) {
		position = whiteBall->getPositionCenter();
		dimension = glm::vec3(2 * whiteBall->getRadius());

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshColor(meshes["sphere"], shaders["ShaderBiliard"], modelMatrix, whiteBall->getColor());
	}

	if (!blackBall->inHole()) {
		position = blackBall->getPositionCenter();
		dimension = glm::vec3(2 * blackBall->getRadius());

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshColor(meshes["sphere"], shaders["ShaderBiliard"], modelMatrix, blackBall->getColor());
	}

	for (Ball ball : redBall) {
		if (ball.isOut())
			continue;
		position = ball.getPositionCenter();
		dimension = glm::vec3(2 * ball.getRadius());

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshColor(meshes["sphere"], shaders["ShaderBiliard"], modelMatrix, ball.getColor());
	}

	for (Ball ball : yellowBall) {
		if (ball.isOut())
			continue;
		position = ball.getPositionCenter();
		dimension = glm::vec3(2 * ball.getRadius());

		modelMatrix = Transform3D::Translate(position.x, position.y, position.z);
		modelMatrix *= Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		RenderMeshColor(meshes["sphere"], shaders["ShaderBiliard"], modelMatrix, ball.getColor());
	}
}

void Billiard::drawTac(float deltaTimeSeconds)
{
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 dimension;

	generateClock(deltaTimeSeconds);

	position = tac.getPosition();
	dimension = tac.getDimension();

	modelMatrix = Transform3D::Translate(position.x, position.y, position.z) * Transform3D::Translate(-dimension.x / 2, 0, -dimension.z / 2 - billiardTable.getRadius() - 0.03f) *Transform3D::RotateOY(angleTac) * Transform3D::Translate(dimension.x /2, 0, dimension.z/ 2 + billiardTable.getRadius() + 0.03f) * Transform3D::Scale(dimension.x, dimension.y, dimension.z);
	RenderTac( shaders["ShaderBiliard"], modelMatrix);
}

void Billiard::moveWhiteBall(float deltaX, float deltaZ)
{
	
	glm::vec3 newPosition = whiteBall->getPositionCenter() + glm::vec3(deltaX, 0, deltaZ);

	if (billiardTable.canMoveWhileBall(newPosition)) {

		whiteBall->setPosition(newPosition);
	}
}

void Billiard::moveWhiteBall2(float deltaX, float deltaZ)
{
	glm::vec3 newPosition = whiteBall->getPositionCenter() + glm::vec3(deltaX, 0, deltaZ);

	if (billiardTable.canMoveWhileBall2(newPosition)) {
		
		float x_white = newPosition.x;
		float z_white = newPosition.z;
		float distX;
		float distZ;
		float radius =  2 * blackBall->getRadius();
		radius *= radius;

		// negru
		distX = x_white - blackBall->getPositionCenter().x;
		distZ = z_white - blackBall->getPositionCenter().z;
		if (distX * distX + distZ * distZ <= radius) {
			return;
		}

		for (Ball ball : redBall) {
			distX = x_white - ball.getPositionCenter().x;
			distZ = z_white - ball.getPositionCenter().z;
			if (distX * distX + distZ * distZ <= radius) {
				return;
			}
		}

		for (Ball ball : yellowBall) {
			distX = x_white - ball.getPositionCenter().x;
			distZ = z_white - ball.getPositionCenter().z;
			if (distX * distX + distZ * distZ <= radius) {
				return;
			}
		}

		whiteBall->setPosition(newPosition);

	}
}

void Billiard::generateClock(float deltaTime)
{
	static int direction = 1;

	if (isTacActive == 1) {
		if (clock < 0.0f || clock > 1.0f) {
			direction = -direction;
		}

		clock += deltaTime * direction;
	}
}

void Billiard::initSpeedWhiteBall()
{
	if (mod == 3) {
		glm::vec3 position = tac.getPosition();
		glm::vec3 dimension = tac.getDimension();

		glm::mat4 modelMatrix = Transform3D::Translate(position.x, position.y, position.z) * Transform3D::Translate(-dimension.x / 2, 0, -dimension.z / 2 - billiardTable.getRadius() - 0.03f) *Transform3D::RotateOY(angleTac) * Transform3D::Translate(dimension.x / 2, 0, dimension.z / 2 + billiardTable.getRadius() + 0.03f) * Transform3D::Scale(dimension.x, dimension.y, dimension.z);
		glm::vec4 positioTac = glm::vec4(0, 0, 0, 1);
		positioTac = modelMatrix * positioTac;

		float v = init_v * (clock + 0.1f) / 1.1f;
		float v_x = v * sinf(angleTac);
		float v_z = -v * cosf(angleTac);

		whiteBall->setSpeed(glm::vec3(v_x, 0, v_z));
		
		mod = 4;
	}
}

void Billiard::updateBall(float acceleration, float deltaTime)
{
	whiteBall->updateBall(glm::vec3(acceleration), deltaTime);
	blackBall->updateBall(glm::vec3(acceleration), deltaTime);

	for (Ball &ball : redBall) {
		ball.updateBall(glm::vec3(acceleration), deltaTime);
	}

	for (Ball &ball : yellowBall) {
		ball.updateBall(glm::vec3(acceleration), deltaTime);
	}
}

/********************************************************** FUNCTILE PENTRU COLIZIUNE  ************************************************************/

void Billiard::checkCollision()
{
	collisionManta();
	collisonBall();
	collisionHole();
}

void Billiard::collisionManta()
{
	// colisiunile cu mantaua
	Collision::collisionBallManta(*whiteBall, billiardTable);
	Collision::collisionBallManta(*blackBall, billiardTable);

	for (Ball &ball : redBall) {
		Collision::collisionBallManta(ball, billiardTable);
	}
	for (Ball &ball : yellowBall) {
		Collision::collisionBallManta(ball, billiardTable);
	}
}

void Billiard::collisonBall()
{
	// bila alba
	Collision::collisionBallBall(*whiteBall, *blackBall);
	for (Ball &ball : redBall) {
		if (Collision::collisionBallBall(*whiteBall, ball)) {
			if ((typeBall == 1 && turn == 0) || (typeBall == 2 && turn == 1))
				fault = false;
		}
	}
	for (Ball &ball : yellowBall) {
		if (Collision::collisionBallBall(*whiteBall, ball)) {
			if ((typeBall == 1 && turn == 1) || (typeBall == 2 && turn == 0))
				fault = false;
		}
	}

	// bila neagra
	for (Ball &ball : redBall) {
		Collision::collisionBallBall(*blackBall, ball);
	}
	for (Ball &ball : yellowBall) {
		Collision::collisionBallBall(*blackBall, ball);
	}

	// bilele rosi
	for (int i = 0; i < redBall.size(); i++) {
		Ball &ball_ref = redBall.at(i);

		for (int j = i + 1; j < redBall.size(); j++) {
			Ball &ball_ref1 = redBall.at(j);
			Collision::collisionBallBall(ball_ref, ball_ref1);
		}

		for (Ball ball : yellowBall) {
			Collision::collisionBallBall(ball_ref, ball);
		}
	}

	// bile galbene
	for (int i = 0; i < yellowBall.size(); i++) {
		Ball &ball_ref = yellowBall.at(i);

		for (int j = i + 1; j < yellowBall.size(); j++) {
			Ball &ball_ref1 = yellowBall.at(j);
			Collision::collisionBallBall(ball_ref, ball_ref1);
		}
	}

	whiteBall->calcSpeed();
	blackBall->calcSpeed();
	for (Ball &ball : redBall) {
		ball.calcSpeed();
	}
	for (Ball &ball : yellowBall) {
		ball.calcSpeed();
	}
}

void Billiard::collisionHole()
{
	// colisiunile cu gaurile
	if (Collision::collisoinBallHole(*whiteBall, billiardTable)) {
		std::cout << "Player " << turn << " Fault" << std::endl;
		nr_fault[turn]++;
	}
	if (Collision::collisoinBallHole(*blackBall, billiardTable)) {
		mod = 5;
	}

	for (Ball &ball : redBall) {

		if (Collision::collisoinBallHole(ball, billiardTable)) {
			if (typeBall == 0) {
				if (turn == 0) {
					typeBall = 1;
				}
				else {
					typeBall = 2;
				}
				fault = false;
			}

			this->outRedTurn++;
		}
	}
	for (Ball &ball : yellowBall) {

		if (Collision::collisoinBallHole(ball, billiardTable)) {
			if (typeBall == 0) {
				if (turn == 0) {
					typeBall = 2;
				}
				else {
					typeBall = 1;
				}
				fault = false;
			}

			this->outYellowTurn++;
		}
	}

}

/***************************************************************************************************************************************************/

void Billiard::cameraSystem()
{
	if (mod == 1 || mod == 2) {
		glm::vec3 position = tac.getPosition();
		glm::vec3 dimension = tac.getDimension();

		glm::mat4 modelMatrix = Transform3D::Translate(position.x, position.y, position.z) * Transform3D::Translate(-dimension.x / 2, 0, -dimension.z / 2 - billiardTable.getRadius() - 0.03f) *Transform3D::RotateOY(angleTac) * Transform3D::Translate(dimension.x / 2, 0, dimension.z / 2 + billiardTable.getRadius() + 0.03f) * Transform3D::Scale(dimension.x, dimension.y, dimension.z);

		glm::vec4 cameraPos_aux = glm::vec4(0, 0, 0, 1);
		cameraPos_aux = modelMatrix * cameraPos_aux;
		glm::vec3 cameraPos = glm::vec3(cameraPos_aux.x, cameraPos_aux.y, cameraPos_aux.z) + glm::vec3(0, 1, 0) *  (4 * billiardTable.getRadius());
		camera->Set(cameraPos, whiteBall->getPositionCenter(), glm::vec3(0, 1, 0));

	}

	if (mod == 4) {
		camera->Set(glm::vec3(0, 4, 0), billiardTable.getCenter(), glm::vec3(0, 1, 0));
	}
}


glm::vec3 Billiard::getPosition()
{
	glm::vec3 ceva = billiardTable.getInitPositionWhiteBall();

	float radius = 2 * blackBall->getRadius();
	radius *= radius;

	bool var3 = false;
	while (true) {
		var3 = false;

		float x_white = ceva.x;
		float z_white = ceva.z;
		float distX;
		float distZ;

		distX = x_white - blackBall->getPositionCenter().x;
		distZ = z_white - blackBall->getPositionCenter().z;
		if (distX * distX + distZ * distZ <= radius) {
			var3 = true;
		}

		for (Ball ball : redBall) {
			distX = x_white - ball.getPositionCenter().x;
			distZ = z_white - ball.getPositionCenter().z;
			if (distX * distX + distZ * distZ <= radius) {
				var3 = true;
			}
		}

		for (Ball ball : yellowBall) {
			distX = x_white - ball.getPositionCenter().x;
			distZ = z_white - ball.getPositionCenter().z;
			if (distX * distX + distZ * distZ <= radius) {
				var3 = true;
			}
		}

		if (!var3)
			break;

		ceva += glm::vec3(whiteBall->getRadius(), 0, 0);
	}

	return ceva;
}

void Billiard::checkCondition()
{
	if (mod == 5) {
		
		if (typeBall == 0)
			fault = false;
		
		if (blackBall->isOut() || blackBall->inHole()) {
			if (typeBall == 1) {
				if (turn == 0) {
					if (outRedTotal + outRedTurn == 7) {
						mod = 6; // win
					}
					else {
						mod = 7; // lose
					}
				}
				else {
					if (outYellowTotal + outYellowTurn == 7) {
						mod = 6; // win
					}
					else {
						mod = 7; // lose
					}
				}
			}
			else if (typeBall == 2) {
				if (turn == 1) {
					if (outRedTotal + outRedTurn == 7) {
						mod = 6; // win
					}
					else {
						mod = 7; // lose
					}
				}
				else {
					if (outYellowTotal + outYellowTurn == 7) {
						mod = 6; // win
					}
					else {
						mod = 7; // lose
					}
				}
			}
			return;
		}

		if (fault) {
			std::cout << "Player " << turn << " fault!" << std::endl;
			nr_fault[turn]++;
		}

		if (nr_fault[turn] > 6) {
			mod = 7;
			return;
		}

		std::cout << std::endl << "Acesta Tura : Player : " << turn << " Bile rosi introduse : " << outRedTurn 
			<< " Bile galbene introduse : " << outYellowTurn << " Nr fault-uri : " << nr_fault[turn] << std::endl;

		outRedTotal += outRedTurn;
		outYellowTotal += outYellowTurn;
		std::cout << "Bile ramase in joc: " << "Rosi : " << 7 - outRedTotal << " Galbene : " << 7 - outYellowTotal << std::endl;

		fault = true;
		sw = false;
		mod = 0;
		if (whiteBall->isOut()) {
			glm::vec3 newPosition = getPosition();
			whiteBall->setPosition(newPosition);
			whiteBall->setSpeed(glm::vec3(0));
			turn = 1 - turn;
			whiteBall->setInHole(false);

			sw = true;
			first = false;
			std::cout << "Urmatoarea tura o sa fie jucatorul : " << turn << std::endl;
			return;
		}

		if (typeBall == 0 && first) {
			first = false;
		}else if (typeBall == 0) {
			turn = 1 - turn;
		}else if (typeBall == 1) {
			if ((turn == 0 && outRedTurn == 0) || (turn == 1 && outYellowTurn == 0)) {
				turn = 1 - turn;
			}
		}
		else if (typeBall == 2) {
			if ((turn == 1 && outRedTurn == 0) || (turn == 0 && outYellowTurn == 0)) {
				turn = 1 - turn;
			}
		}

		outRedTurn = 0;
		outYellowTurn = 0;
		std::cout << "Urmatoarea tura o sa fie jucatorul : " << turn << std::endl;
		
	}
}

void Billiard::nextTurn()
{
	if (mod == 4) {
		if (!whiteBall->isStatic()) {
			return;
		}

		if (!blackBall->isStatic()) {
			return;
		}

		for (Ball ball : redBall) {
			if (!ball.isStatic() && !ball.isOut()) {
				return;
			}
		}

		for (Ball ball : yellowBall) {
			if (!ball.isStatic() && !ball.isOut()) {
				return;
			}
		}
	
		camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		mod = 5;
	}
}

void Billiard::removeOutBall()
{
	std::vector<Ball> auxRed;
	std::vector<Ball> auxYellow;

	for (Ball ball : redBall) {
		if (!ball.isOut()) {
			auxRed.push_back(ball);
		}
	}

	for (Ball ball : yellowBall) {
		if (!ball.isOut()) {
			auxYellow.push_back(ball);
		}
	}

	redBall = auxRed;
	yellowBall = auxYellow;
}

void Billiard::lose()
{
	if (mod == 7) {
		std::cout << "\t\t\t\t\t Player " << 1 - turn << " Win !!!!!" << std::endl;
		std::cout << "\t\t\t\t\t Player " << turn << " Lose !!!!!" << std::endl;
		
		mod = 8;
	}

}

void Billiard::win()
{
	if (mod == 6) {
		std::cout << "\t\t\t\t\t Player " << turn << " Win !!!!!" << std::endl;
		std::cout << "\t\t\t\t\t Player " << 1 - turn << " Lose !!!!!" << std::endl;

		mod = 8;
	}
}