#include <glm/glm.hpp>
#include <string>

class Camera
{
  public:
    glm::vec3 position;
    float f;

    Camera()
    {
    }

    Camera(glm::vec3 pos, float foc){
      position = pos;
      f = foc;
    }
};

std::ostream& operator<<(std::ostream& os, const Camera& camera)
{
    os << "Camera Position: " << "[" << camera.position.x << "," << camera.position.y << "," << camera.position.z << "]"<< std::endl;
    os << "Camera Focal Length: " << camera.f;
    return os;
}
