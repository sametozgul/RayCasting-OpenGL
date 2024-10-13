Raycasting Implementation in OpenGL
This repository demonstrates the implementation of raycasting in OpenGL. The code enables picking rectangles on the screen using mouse input.

Raycasting Functions
There are three key functions that assist in implementing raycasting:

getRay(float xPos, float yPos)

glm::vec3 OGLRenderer::getRay(float xPos, float yPos)
This function takes the mouse position and converts it into world coordinates.
intersectRayPlane

bool OGLRenderer::intersectRayPlane(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                                    const glm::vec3& planeNormal, const glm::vec3& planePoint,
                                    float& t)
Parameters:
rayOrigin: The camera position.
rayDirection: Obtained from the mouse position using getRay.
planeNormal: The normal of the surface.
planePoint: A point on the surface, which can be the center of the surface or any other point.
intersectDisc

bool OGLRenderer::intersectDisc(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
                                const glm::vec3& planeNormal, const glm::vec3& planePoint,
                                const float& radius)
Parameters:
rayOrigin: The camera position.
rayDirection: Obtained from the mouse position using getRay.
planeNormal: The normal of the surface.
planePoint: A point on the surface, which can be the center of the surface or any other point.
radius: Defines the radius of the disc that covers the surface.
