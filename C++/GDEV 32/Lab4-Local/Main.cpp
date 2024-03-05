#include <glm/glm.hpp>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

struct Ray
{
    glm::vec3 origin; // Ray origin
    glm::vec3 direction; // Ray direction
};

struct Material
{
    glm::vec3 ambient; // Ambient
    glm::vec3 diffuse; // Diffuse
    glm::vec3 specular; // Specular
    float shininess; // Shininess
};

struct SceneObject
{
    Material material; // Material

    /**
     * Template function for calculating the intersection of this object with the provided ray.
     * @param[in]   incomingRay             Ray that will be checked for intersection with this object
     * @param[out]  outIntersectionPoint    Point of intersection (in case there is an intersection)
     * @param[out]  outIntersectionNormal   Normal vector at the point of intersection (in case there is an intersection)
     * @return If there is an intersection, returns the distance from the ray origin to the intersection point. Otherwise, returns a negative number.
     */
    virtual float Intersect(const Ray& incomingRay, glm::vec3& outIntersectionPoint, glm::vec3& outIntersectionNormal) = 0;
};

// Subclass of SceneObject representing a Sphere scene object
struct Sphere : public SceneObject
{
    glm::vec3 center; // center
    float radius; // radius

    /**
     * @brief Ray-sphere intersection
     * @param[in]   incomingRay             Ray that will be checked for intersection with this object
     * @param[out]  outIntersectionPoint    Point of intersection (in case there is an intersection)
     * @param[out]  outIntersectionNormal   Normal vector at the point of intersection (in case there is an intersection)
     * @return If there is an intersection, returns the distance from the ray origin to the intersection point. Otherwise, returns a negative number.
     */
    virtual float Intersect(const Ray& incomingRay, glm::vec3& outIntersectionPoint, glm::vec3& outIntersectionNormal)
    {
        float s = 0.0f;

        glm::vec3 rayPosition = incomingRay.origin;
        glm::vec3 rayDirection = incomingRay.direction;

        glm::vec3 m = rayPosition - center; // x - c
        float b = glm::dot(m, rayDirection);
        float c = glm::dot(m, m);
        c = c - glm::pow(radius, 2);

        float determinant = glm::pow(b, 2) - c;
        if (determinant < 0) //negative, no roots
        {
            s = -1.0f;
        }
        else if (determinant == 0) //one root
        {
            s = -b;
        }
        else if (determinant > 0)
        {
            float firstRoot = -b + glm::sqrt(determinant);
            float secondRoot = -b - glm::sqrt(determinant);

            if (firstRoot < 0 && secondRoot < 0) // no intersection or roots
            {
                //pass
            }
            else if (firstRoot > 0 && secondRoot < 0) // only first root is positive
            {
                s = firstRoot;
            }
            else if (firstRoot < 0 && secondRoot > 0) // only second root is positive
            {
                s = secondRoot;
            }
            else if (firstRoot > 0 && secondRoot > 0) // if both roots are positive
            {
                float smallestRoot = firstRoot;
                if (secondRoot < firstRoot)
                {
                    smallestRoot = secondRoot;
                }

                s = smallestRoot;
            }
        }
        outIntersectionPoint = rayPosition + (s * rayDirection);
        outIntersectionNormal = glm::normalize(outIntersectionPoint);

        return s;
    }
};

// Subclass of SceneObject representing a Triangle scene object
struct Triangle : public SceneObject
{
    glm::vec3 A; // First point
    glm::vec3 B; // Second point
    glm::vec3 C; // Third point

    /**
     * @brief Ray-Triangle intersection
     * @param[in]   incomingRay             Ray that will be checked for intersection with this object
     * @param[out]  outIntersectionPoint    Point of intersection (in case there is an intersection)
     * @param[out]  outIntersectionNormal   Normal vector at the point of intersection (in case there is an intersection)
     * @return If there is an intersection, returns the distance from the ray origin to the intersection point. Otherwise, returns a negative number.
     */
    virtual float Intersect(const Ray& incomingRay, glm::vec3& outIntersectionPoint, glm::vec3& outIntersectionNormal)
    {
        float s = 0.0f;

        glm::vec3 rayDirection = incomingRay.direction;
        glm::vec3 rayPosition = incomingRay.origin;

        glm::vec3 n = glm::cross((B - A), (C - A));
        float f = glm::dot(-rayDirection, n);
        glm::vec3 e = glm::cross(-rayDirection, (rayPosition - A));

        if (f <= 0) // no intersection
        {
            s = -1.0f;
            return s;
        }
        else
        {
            float t = (glm::dot((rayPosition - A), n)) / f;

            if (t <= 0) // no intersection
            {
                s = -1.0f;
                return s;
            }
            else
            {
                float u = (glm::dot((C - A), e)) / f;
                float v = (glm::dot(-(B - A), e)) / f;

                if (u >= 0 && v >= 0 && (u + v <= 1)) // satisfies the requirements for u and v, meaning there is an intersection
                {
                    s = t;

                    outIntersectionPoint = A + (u * (B - A)) + (v * (C - A));
                    outIntersectionNormal = glm::normalize(outIntersectionPoint);
                    return s;
                }
                else
                {
                    s = -1.0f;
                    return s;
                }
            }
        }
    }
};

struct Camera
{
    glm::vec3 position; // Position
    glm::vec3 lookTarget; // Look target
    glm::vec3 globalUp; // Global up-vector
    float fovY; // Vertical field of view
    float focalLength; // Focal length

    int imageWidth; // image width
    int imageHeight; // image height
};

struct Light
{
    glm::vec4 position; // Light position (w = 1 if point light, w = 0 if directional light)

    glm::vec3 ambient; // Light's ambient intensity
    glm::vec3 diffuse; // Light's diffuse intensity
    glm::vec3 specular; // Light's specular intensity

    // --- Attenuation variables ---
    float constant; // Constant factor
    float linear; // Linear factor
    float quadratic; // Quadratic factor
};

struct IntersectionInfo
{
    Ray incomingRay; // Ray used to calculate the intersection
    float t; // Distance from the ray's origin to the point of intersection (if there was an intersection).
    SceneObject* obj; // Object that the ray intersected with. If this is equal to nullptr, then no intersection occured.
    glm::vec3 intersectionPoint; // Point where the intersection occured (if there was an intersection)
    glm::vec3 intersectionNormal; // Normal vector at the point of intersection (if there was an intersection)
};

struct Scene
{
    std::vector<SceneObject*> objects; // List of all objects in the scene
    std::vector<Light> lights; // List of all lights in the scene
};

struct Image
{
    std::vector<unsigned char> data; // Image data
    int width; // Image width
    int height; // Image height

    /**
     * @brief Constructor
     * @param[in] w Width
     * @param[in] h Height
     */
    Image(const int& w, const int& h)
        : width(w)
        , height(h)
    {
        data.resize(w * h * 3, 0);
    }

    /**
     * @brief Converts the provided color value from [0, 1] to [0, 255]
     * @param[in] c Color value in [0, 1] range
     * @return Color value in [0, 255] range
     */
    unsigned char ToChar(float c)
    {
        c = glm::clamp(c, 0.0f, 1.0f);
        return static_cast<unsigned char>(c * 255);
    }

    /**
     * @brief Sets the color at the specified pixel location
     * @param[in] x     X-coordinate of the pixel
     * @param[in] y     Y-coordinate of the pixel
     * @param[in] color Pixel color
     */
    void SetColor(const int& x, const int& y, const glm::vec3& color)
    {
        int index = (y * width + x) * 3;
        data[index] = ToChar(color.r);
        data[index + 1] = ToChar(color.g);
        data[index + 2] = ToChar(color.b);
    }
};

/**
 * @brief Gets the ray that goes from the camera's position to the specified pixel at (x, y)
 * @param[in] camera Camera data
 * @param[in] x X-coordinate of the pixel (upper-left corner of the pixel)
 * @param[in] y Y-coordinate of the pixel (upper-left corner of the pixel)
 * @return Ray that passes through the pixel at (x, y)
 */
Ray GetRayThruPixel(const Camera& camera, const int& pixelX, const int& pixelY)
{
    Ray ray;

    glm::vec3 cameraDirection = glm::normalize(camera.lookTarget - camera.position);

    float aspectRatio = camera.imageWidth / (float)camera.imageHeight;
    float hViewport = 2 * camera.focalLength * glm::tan(glm::radians(camera.fovY / 2));
    float wViewport = aspectRatio * hViewport;

    glm::vec3 u = glm::cross(cameraDirection, camera.globalUp);
    glm::vec3 v = glm::cross(u, cameraDirection);

    if (u.x != 0 && u.y != 0 && u.z != 0) //preventing undefined
    {
        u = glm::normalize(u);
    }

    if (v.x != 0 && v.y != 0 && v.z != 0) //preventing undefined
    {
        v = glm::normalize(v);
    }
    glm::vec3 lowerLeftViewport = camera.position + (cameraDirection * camera.focalLength) - (u * (wViewport / 2)) - (v * (hViewport / 2));

    float s = ((pixelX + 0.5) / camera.imageWidth) * wViewport;
    float t = ((pixelY + 0.5) / camera.imageHeight) * hViewport;

    glm::vec3 pixel = lowerLeftViewport + (u * s) + (v * t);
    ray.origin = camera.position;
    ray.direction = pixel - ray.origin;

    if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0) //preventing undefined
    {
        //pass
    }
    else
    {
        ray.direction = glm::normalize(ray.direction);
    }

    return ray;
}

/**
 * @brief Cast a ray to the scene.
 * @param[in] ray   Ray to cast to the scene
 * @param[in] scene Scene object
 * @return Returns an IntersectionInfo object that will contain the results of the raycast
 */
IntersectionInfo Raycast(const Ray& ray, const Scene& scene)
{
    IntersectionInfo ret;
    ret.incomingRay = ray;

    int sceneObjectsNum = scene.objects.size();
    float smallestT;
    bool noIntersectionYet = true;

    glm::vec3 outIntersectionPoint(0.0f);
    glm::vec3 outIntersectionNormal(0.0f);

    // Fields that need to be populated:
    ret.intersectionPoint = glm::vec3(0.0f); // Intersection point
    ret.intersectionNormal = glm::vec3(0.0f); // Intersection normal
    ret.t = 0.0f; // Distance from ray origin to intersection point
    ret.obj = nullptr; // First object hit by the ray. Set to nullptr if the ray does not hit anything

    for (int i = 0; i < sceneObjectsNum; i++)
    {
        ret.t = scene.objects[i]->Intersect(ret.incomingRay, outIntersectionPoint, outIntersectionNormal);
        if (ret.t > 0) // if there was an intersection
        {
            if (noIntersectionYet) // takes the first intersection as the smallest distance
            {
                smallestT = ret.t;
                noIntersectionYet = false;
                ret.obj = scene.objects[i];
                ret.intersectionPoint = outIntersectionPoint;
                ret.intersectionNormal = outIntersectionNormal;
            }
            else
            {
                if (ret.t < smallestT) // if current object is closer to the ray origin
                {
                    smallestT = ret.t;
                    ret.obj = scene.objects[i];
                    ret.intersectionPoint = outIntersectionPoint;
                    ret.intersectionNormal = outIntersectionNormal;
                }
            }
        }
    }

    return ret;
}

/**
 * @brief Perform a ray-trace to the scene
 * @param[in] ray       Ray to trace
 * @param[in] scene     Scene data
 * @param[in] camera    Camera data
 * @param[in] maxDepth  Maximum depth of the trace
 * @return Resulting color after the ray bounced around the scene
 */
glm::vec3 RayTrace(const Ray& ray, const Scene& scene, const Camera& camera, int maxDepth = 1)
{
    IntersectionInfo intersectionInfo;
    intersectionInfo = Raycast(ray, scene);
    glm::vec3 color(0.0f);

    int numberOfLights = scene.lights.size();
    if (intersectionInfo.obj == nullptr) // ray did not hit an object
    {
        return color;
    }
    else // ray did hit an object
    {
        glm::vec3 totalAmbient(0.0f);
        glm::vec3 pLTotal(0.0f);
        glm::vec3 dLTotal(0.0f);

        for (int i = 0; i < numberOfLights; i++)
        {
            if (scene.lights[i].position.w == 1.0f) // point light 
            {
                // ambient
                glm::vec3 pointLightAmbient = scene.lights[i].ambient;
                totalAmbient = totalAmbient + pointLightAmbient;

                // diffuse
                glm::vec3 pointLightNorm = intersectionInfo.intersectionNormal;
                glm::vec3 pointLightDirection = glm::normalize(glm::vec3(scene.lights[i].position) - intersectionInfo.intersectionPoint);
                float pointLightDiff = glm::max(glm::dot(pointLightNorm, pointLightDirection), 0.0f);
                glm::vec3 pLDCalculation = scene.lights[i].diffuse * pointLightDiff * intersectionInfo.obj->material.diffuse;

                // specular
                glm::vec3 pointLightViewDir = glm::normalize(camera.position - intersectionInfo.intersectionPoint);
                glm::vec3 pointLightReflectDir = glm::reflect(-pointLightDirection, pointLightNorm);
                float pointLightSpec = pow(glm::max(glm::dot(pointLightViewDir, pointLightReflectDir), 0.f), intersectionInfo.obj->material.shininess);
                glm::vec3 pLSCalculation = scene.lights[i].specular * pointLightSpec * intersectionInfo.obj->material.specular;

                // attenuation
                float pointLightDistance = glm::length(camera.position - intersectionInfo.intersectionPoint);
                float pointLightAttenuation = 1.0f / (scene.lights[i].constant + (scene.lights[i].linear * pointLightDistance) + scene.lights[i].quadratic * pow(pointLightDistance, 2));
                pLDCalculation = pLDCalculation * pointLightAttenuation;
                pLSCalculation = pLSCalculation * pointLightAttenuation;

                pLTotal = pLDCalculation + pLSCalculation;
            }
            else if (scene.lights[i].position.w == 0.0f) // directional light
            {
                // ambient
                glm::vec3 directionalLightAmbient = scene.lights[i].ambient;
                totalAmbient = totalAmbient + directionalLightAmbient;

                // diffuse
                glm::vec3 directionalLightNorm = intersectionInfo.intersectionNormal;
                glm::vec3 directionalLightLightDirection = glm::normalize(-1.0f * glm::vec3(scene.lights[i].position) - intersectionInfo.intersectionPoint);
                float directionalLightDiff = glm::max(glm::dot(directionalLightNorm, directionalLightLightDirection), 0.0f);
                glm::vec3 dLDCalculation = scene.lights[i].diffuse * directionalLightDiff * intersectionInfo.obj->material.diffuse;

                // specular
                glm::vec3 directionalLightViewDir = glm::normalize(camera.position - intersectionInfo.intersectionPoint);
                glm::vec3 directionalLightReflectDir = glm::reflect(-glm::vec3(scene.lights[i].position), directionalLightNorm);
                float directionalLightSpec = pow(glm::max(dot(directionalLightViewDir, directionalLightReflectDir), 0.f), intersectionInfo.obj->material.shininess);
                glm::vec3 dLSCalculation = scene.lights[i].specular * directionalLightSpec * intersectionInfo.obj->material.specular;

                // attenuation
                float directionalLightDistance = glm::length(camera.position - intersectionInfo.intersectionPoint);
                float directionalLightAttenuation = 1.0f / (scene.lights[i].constant + (scene.lights[i].linear * directionalLightDistance) + scene.lights[i].quadratic * pow(directionalLightDistance, 2));
                dLDCalculation = dLDCalculation * directionalLightAttenuation;
                dLSCalculation = dLSCalculation * directionalLightAttenuation;

                dLTotal = dLDCalculation + dLSCalculation;
            }
        }
        // ambient calculations
        glm::vec3 ambientAverage(0.0f);
        ambientAverage.x = totalAmbient.x / numberOfLights;
        ambientAverage.y = totalAmbient.y / numberOfLights;
        ambientAverage.z = totalAmbient.z / numberOfLights;
        glm::vec3 ambientAddend = intersectionInfo.obj->material.ambient * ambientAverage;

        pLTotal = pLTotal + ambientAddend;
        dLTotal = dLTotal + ambientAddend;

        color = color + pLTotal + dLTotal;
        return color;
    }
}

/**
 * Main function
 */
int main()
{
    Scene scene;
    Camera camera;
    Sphere* sphere;
    Triangle* triangle;
    Light light;

    std::ifstream myfile;
    myfile.open("scene0.test");

    std::vector<std::string> values;
    std::string mystring;
    if (myfile.is_open())
    {
        char mychar;
        while (myfile)
        {
            mychar = myfile.get();
            if (mychar != ' ')
            {
                mystring = mystring + mychar;
            }
            if (mychar == ' ')
            {
                values.push_back(mystring);
                mystring.clear();
            }
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }

    camera.imageWidth = stoi(values[0]);
    camera.imageHeight = stoi(values[1]);
    camera.position.x = stof(values[2]);
    camera.position.y = stof(values[3]);
    camera.position.z = stof(values[4]);
    camera.lookTarget.x = stof(values[5]);
    camera.lookTarget.y = stof(values[6]);
    camera.lookTarget.z = stof(values[7]);
    camera.globalUp.x = stof(values[8]);
    camera.globalUp.y = stof(values[9]);
    camera.globalUp.z = stof(values[10]);
    camera.fovY = stof(values[11]);
    camera.focalLength = stof(values[12]);

    int maxDepth = stoi(values[13]);
    int numberOfObjects = stoi(values[14]);

    int offset = 15; // where counting will start for multiple objects

    for (int i = 0; i < numberOfObjects; i++)
    {
        if (values[offset] == "\nsphere")
        {
            sphere = new Sphere();
            sphere->center.x = stof(values[offset + 1]);
            sphere->center.y = stof(values[offset + 2]);
            sphere->center.z = stof(values[offset + 3]);
            sphere->radius = stof(values[offset + 4]);
            sphere->material.ambient.x = stof(values[offset + 5]);
            sphere->material.ambient.y = stof(values[offset + 6]);
            sphere->material.ambient.z = stof(values[offset + 7]);
            sphere->material.diffuse.x = stof(values[offset + 8]);
            sphere->material.diffuse.y = stof(values[offset + 9]);
            sphere->material.diffuse.z = stof(values[offset + 10]);
            sphere->material.specular.x = stof(values[offset + 11]);
            sphere->material.specular.y = stof(values[offset + 12]);
            sphere->material.specular.z = stof(values[offset + 13]);
            sphere->material.shininess = stof(values[offset + 14]);

            offset = offset + 15; // will now adjust the value of offset to account for other objects in the scene
            scene.objects.push_back(sphere);
        }

        if (values[offset] == "\ntri")
        {
            triangle = new Triangle();
            triangle->A.x = stof(values[offset + 1]);
            triangle->A.y = stof(values[offset + 2]);
            triangle->A.z = stof(values[offset + 3]);
            triangle->B.x = stof(values[offset + 4]);
            triangle->B.y = stof(values[offset + 5]);
            triangle->B.z = stof(values[offset + 6]);
            triangle->C.x = stof(values[offset + 7]);
            triangle->C.y = stof(values[offset + 8]);
            triangle->C.z = stof(values[offset + 9]);
            triangle->material.ambient.x = stof(values[offset + 10]);
            triangle->material.ambient.y = stof(values[offset + 11]);
            triangle->material.ambient.z = stof(values[offset + 12]);
            triangle->material.diffuse.x = stof(values[offset + 13]);
            triangle->material.diffuse.y = stof(values[offset + 14]);
            triangle->material.diffuse.z = stof(values[offset + 15]);
            triangle->material.specular.x = stof(values[offset + 16]);
            triangle->material.specular.y = stof(values[offset + 17]);
            triangle->material.specular.z = stof(values[offset + 18]);
            triangle->material.shininess = stof(values[offset + 19]);

            offset = offset + 20; // will now adjust the value of offset to account for other objects in the scene
            scene.objects.push_back(triangle);
        }
    }

    int numberOfLights = stoi(values[offset]);

    for (int i = 0; i < numberOfLights; i++)
    {
        light.position.x = stof(values[offset + 1]);
        light.position.y = stof(values[offset + 2]);
        light.position.z = stof(values[offset + 3]);
        light.position.w = stof(values[offset + 4]);
        light.ambient.x = stof(values[offset + 5]);
        light.ambient.y = stof(values[offset + 6]);
        light.ambient.z = stof(values[offset + 7]);
        light.diffuse.x = stof(values[offset + 8]);
        light.diffuse.y = stof(values[offset + 9]);
        light.diffuse.z = stof(values[offset + 10]);
        light.specular.x = stof(values[offset + 11]);
        light.specular.y = stof(values[offset + 12]);
        light.specular.z = stof(values[offset + 13]);
        light.constant = stof(values[offset + 14]);
        light.linear = stof(values[offset + 15]);
        light.quadratic = stof(values[offset + 16]);

        offset = offset + 16; // will now adjust the value of offset to account for other lights in the scene
        scene.lights.push_back(light);
    }

    Image image(camera.imageWidth, camera.imageHeight);
    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < image.width; ++x)
        {
            Ray ray = GetRayThruPixel(camera, x, image.height - y - 1);

            glm::vec3 color = RayTrace(ray, scene, camera, maxDepth);
            image.SetColor(x, y, color);
        }

        std::cout << "Row: " << std::setfill(' ') << std::setw(4) << (y + 1) << " / " << std::setfill(' ') << std::setw(4) << image.height << "\r" << std::flush;
    }
    std::cout << std::endl;

    std::string imageFileName = "scene.png"; // You might need to make this a full path if you are on Mac
    stbi_write_png(imageFileName.c_str(), image.width, image.height, 3, image.data.data(), 0);

    for (size_t i = 0; i < scene.objects.size(); ++i)
    {
        delete scene.objects[i];
    }

    return 0;
}

