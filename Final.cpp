/*---------------------------------------------------------*/
/*------------- Alumno:  Jimenez Perez Patricia Alejandra     ---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(10.0f, 10.0f, 120.0f));//(0.0f, 10.0f, 90.0f))
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

//// Light
glm::vec3 lightColor = glm::vec3(0.7f);
glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
glm::vec3 ambientColor = diffuseColor * glm::vec3(0.85f);

//Variables para manipulacion de posiciones de los toroides

float	movToroideV_x = 0.0f,
movToroideV_y = 0.0f,
movToroideV_z = 0.0f,

movToroideA_x = 0.0f,
movToroideA_y = 0.0f,
movToroideA_z = 0.0f,

movToroideR_x = 0.0f,
movToroideR_y = 0.0f,
movToroideR_z = 0.0f
;

bool IniciaAnimacion = false;
int  animaciontoroide = 1;


void animate(void)
{
	
	//---INICIA LA ANIMACION DE LA TORRE DE HANOY
	if (IniciaAnimacion)
	{//formas pata armar las condiciones de cada toroide
		
		//PASO 1 MOVIMIENTO DEL TOROIDE 1 (AZUL) SE TRASLADA A LA BASE 3
		if (animaciontoroide == 1) {//1.TOROIDE AZUL ARRIBA
			movToroideA_y += 0.5f;
			if (movToroideA_y >= 20.0f) {
				animaciontoroide = 3;
			}
		}
		if (animaciontoroide == 2) {//2.TOROIDE AZUL ABAJO
			movToroideA_y -= 0.50f;
			if (movToroideA_y <= -9.0f && movToroideA_x >= 80.0f) {
				animaciontoroide = 4;
			}
		}
		if (animaciontoroide == 3) {//3.TOROIDE AZUL ENFRENTE
			movToroideA_x += 0.50f;
			if (movToroideA_x >= 80.0f && movToroideA_y >= 20.0f) {
				animaciontoroide = 2;
			}
		}
		//PASO 2 MOVIMIENTO DEL TOROIDE 2 (VERDE) SE TRASLADA A LA BASE 2
		if (animaciontoroide == 4) {//4.TOROIDE VERDE ARRIBA
			movToroideV_y += 0.50f;
			if (movToroideV_y >= 24.5f) {
				animaciontoroide = 5;
			}
		}
		if (animaciontoroide == 5) {//5.TOROIDE VERDE ENFRENTE
			movToroideV_x += 0.50f;
			if (movToroideV_x >= 40.0f) {
				animaciontoroide = 6;
			}
		}

		if (animaciontoroide == 6) {//5.TOROIDE VERDE ABAJO
			movToroideV_y -= 0.50f;
			if (movToroideV_y <= -4.5f) {
				animaciontoroide = 7;
			}
		}
		// PASO 3 MOVIMIENTO DEL TOROIDE 3(AZUL), SE TRASLADA A LA BASE 2
		if (animaciontoroide == 7) {//5.TOROIDE AZUL ARRIBA 
			movToroideA_y += 0.50f;
			if (movToroideA_y >= 20.0f) {
				animaciontoroide = 8;
			}
		}
		if (animaciontoroide == 8) {//5.TOROIDE AZUL ATRAS 
			movToroideA_x -= 0.50f;
			if (movToroideA_x <= 40.0f) {
				animaciontoroide = 9;
			}
		}
		if (animaciontoroide == 9) {//5.TOROIDE AZUL ABAJO
			movToroideA_y -= 0.50f;
			if (movToroideA_y <= -4.50f) {
				animaciontoroide = 10;
			}
		}
		// PASO 4 MOVIMIENTO DEL TOROIDE 1(ROJO), SE TRASLADA A LA BASE 3
		if (animaciontoroide == 10) {//5.TOROIDE ROJO ARRIBA
			movToroideR_y += 0.50f;
			if (movToroideR_y >= 27.0f) {
				animaciontoroide = 11;
			}
		}

		if (animaciontoroide == 11) {//5.TOROIDE ROJO ENFRENTE
			movToroideR_x += 0.50f;
			if (movToroideR_x >= 80.0f) {
				animaciontoroide = 12;
			}
		}

		if (animaciontoroide == 12) {//5.TOROIDE ROJO ABAJO
			movToroideR_y -= 0.50f;
			if (movToroideR_y <= -0.0f) {
				animaciontoroide = 13;
			}
		}
		// PASO 5 MOVIMIENTO DEL TOROIDE 3(AZUL), SE TRASLADA A LA BASE 1
		if (animaciontoroide == 13) {//5.TOROIDE AZUL ARRIBA
			movToroideA_y += 0.50f;
			if (movToroideA_y >= 20.0f) {
				animaciontoroide = 14;
			}
		}
		if (animaciontoroide == 14) {//5.TOROIDE AZUL ATRAS
			movToroideA_x -= 0.50f;
			if (movToroideA_x <= 0.0f) {
				animaciontoroide = 15;
			}
		}

		if (animaciontoroide == 15) {//5.TOROIDE AZUL ABAJO
			movToroideA_y -= 0.50f;
			if (movToroideA_y <= -9.0f) {
				animaciontoroide = 16;
			}
		}
		// PASO 6 MOVIMIENTO DEL TOROIDE 2(VERDE), SE TRASLADA A LA BASE 3
		if (animaciontoroide == 16) {//5.TOROIDE VERDE ARRIBA
			movToroideV_y += 0.50f;
			if (movToroideV_y >= 24.5f) {
				animaciontoroide = 17;
			}
		}
		if (animaciontoroide == 17) {//5.TOROIDE VERDE ENFRENTE
			movToroideV_x += 0.50f;
			if (movToroideV_x >= 80.0f) {
				animaciontoroide = 18;
			}
		}
		if (animaciontoroide == 18) {//5.TOROIDE VERDE ABAJO
			movToroideV_y -= 0.50f;
			if (movToroideV_y <= 0.0f) {
				animaciontoroide = 19;
			}
		}
		// PASO 7 MOVIMIENTO DEL TOROIDE 3(AZUL), SE TRASLADA A LA BASE 3
		if (animaciontoroide == 19) {//5.TOROIDE AZUL ARRIBA
			movToroideA_y += 0.50f;
			if (movToroideA_y >= 20.0f) {
				animaciontoroide = 20;
			}
		}
		if (animaciontoroide == 20) {//5.TOROIDE AZUL ADELANTE
			movToroideA_x += 0.50f;
			if (movToroideA_x >= 80.0f) {
				animaciontoroide = 21;
			}
		}

		if (animaciontoroide == 21) {//5.TOROIDE AZUL ABAJO
			movToroideA_y -= 0.50f;
			if (movToroideA_y <= 0.0f) {
				animaciontoroide = 22;
			}
		}
		//SE DETIENE LA ANIMACION
		if (animaciontoroide == 22) {
			movToroideV_x += 0.0f;
			if (movToroideV_x == 0.0f) {
				IniciaAnimacion = false;
			}
		}

	}
}



void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGEIHC JIMENEZ PEREZ PATRICIA ALEJANDRA", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);//activa la profundidad

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights_mod.fs");// modelos estaticos
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");//modelos con animacion 


	vector<std::string> faces
	{
		"resources/skybox/cafe.jpg",
		"resources/skybox/cafe.jpg",
		"resources/skybox/cafe.jpg",
		"resources/skybox/cabebase.jpg",
		"resources/skybox/cafe.jpg",
		"resources/skybox/cafe.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// CARGA DE LOS MODELOS 
	Model base("resources/objects/Bases/BaseFinal.obj");
	Model verde("resources/objects/ToroideVerde/ToroideVerde.obj");
	Model azul("resources/objects/ToroideAzul/ToroideAzul.obj");
	Model rojo("resources/objects/ToroideRojo/ToroideRojo.obj");
	Model Nombre("resources/objects/PlanoNombre/PlanoNombre.obj");


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", ambientColor);
		staticShader.setVec3("dirLight.diffuse", diffuseColor);
		staticShader.setVec3("dirLight.specular", glm::vec3(0.6f, 0.6f, 0.6f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.08f);
		staticShader.setFloat("pointLight[0].linear", 0.009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-80.0, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.032f);

		staticShader.setVec3("spotLight[0].position", glm::vec3(0.0f, 20.0f, 10.0f));
		staticShader.setVec3("spotLight[0].direction", glm::vec3(0.0f, -1.0f, 0.0f));
		staticShader.setVec3("spotLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("spotLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("spotLight[0].cutOff", glm::cos(glm::radians(10.0f)));
		staticShader.setFloat("spotLight[0].outerCutOff", glm::cos(glm::radians(60.0f)));
		staticShader.setFloat("spotLight[0].constant", 1.0f);
		staticShader.setFloat("spotLight[0].linear", 0.0009f);
		staticShader.setFloat("spotLight[0].quadratic", 0.0005f);
		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);


		// ACOMODO DE LOS MODELOS EN EL ESCENARIO

		staticShader.use();//shader estatico para dibujos de modelos
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

	//TOROIDE AZUL
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movToroideA_x, movToroideA_y, 0.0f));
		staticShader.setMat4("model", model);
		azul.Draw(staticShader);
	//TOROIDE VERDE
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movToroideV_x, movToroideV_y, 0.0f));
		staticShader.setMat4("model", model);
		verde.Draw(staticShader);
	//TOROIDE ROJO
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::translate(glm::mat4(1.0f), glm::vec3(movToroideR_x, movToroideR_y, 0.0f));
		staticShader.setMat4("model", model);
		rojo.Draw(staticShader);
	//TRES BASES
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		staticShader.setMat4("model", model);
		base.Draw(staticShader);

	//PLANO CON NOMBRE
		model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 20.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		Nombre.Draw(staticShader);

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	
//BOTON INICIO DE LA ANIMACION
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		IniciaAnimacion ^= true;
	}
//BOTON DE REINICIO
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		movToroideV_y = 0.0f;
		movToroideV_x = 0.0f;
		movToroideA_x = 0.0f;
		movToroideA_y = 0.0f;
		movToroideR_x = 0.0f;
		movToroideR_y = 0.0f;
		animaciontoroide = 1;
	}
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}