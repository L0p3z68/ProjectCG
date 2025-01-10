#include "Camera.h"


Camera::Camera(glm::vec3 cameraPosition, glm::vec3 up, float cameraYaw, float cameraPitch)
	: frontCamera(glm::vec3(0.f, 0.f, -1.f)), front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(2.5f), mouseSensitivity(0.1f), fov(45.f)
{
	position = cameraPosition;
	worldUp = up;
	yaw = cameraYaw;
	pitch = cameraPitch;
	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + frontCamera, up);
}

void Camera::processKeyboardInput(const Uint8* keyState, float deltaTime) {
	float velocity = movementSpeed * deltaTime;
	if (keyState[SDL_SCANCODE_W]) move(FORWARD, velocity);
	if (keyState[SDL_SCANCODE_S]) move(BACKWARD, velocity);
	if (keyState[SDL_SCANCODE_A]) move(LEFT, velocity);
	if (keyState[SDL_SCANCODE_D]) move(RIGHT, velocity);
}

void Camera::processMouseInput(float xpos, float ypos, SDL_Window* window) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
	
	SDL_WarpMouseInWindow(window, 400, 300);

	lastX = 400;
	lastY = 300;

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;
	
	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	updateCameraVectors();
}


void Camera::processMouseScroll(float yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f) fov -= yoffset;
	if (fov <= 1.0f) fov = 1.0f;
	if (fov >= 45.0f) fov = 45.0f;
}

void Camera::updateCameraVectors()
{
	frontCamera.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontCamera.y = sin(glm::radians(pitch));
	frontCamera.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	frontCamera = glm::normalize(frontCamera);
	front = glm::normalize(glm::cross(worldUp, right));
	right = glm::normalize(glm::cross(frontCamera, worldUp));
	up = glm::normalize(glm::cross(right, frontCamera));
}

void Camera::move(CameraMovement direction, float velocity)
{
	if (direction == FORWARD) position += front * velocity;
	if (direction == BACKWARD) position -= front * velocity;
	if (direction == LEFT) position -= right * velocity;
	if (direction == RIGHT) position += right * velocity;
}