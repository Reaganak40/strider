#include "app.h"
#include "error.h"
#include "utils.h"

#include "scene.h"
#include "quad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <tests/testSampler.h>

int main(void)
{
    StriderEngine app;

    
    if (app.CreateWindow("OpenGL Sandbox", 1280, 720) < 0) {
        return -1;
    }

    std::shared_ptr<Scene> scene = app.NewScene("Sandbox");
    app.SetScene("Sandbox");

    Quad purpleQuad( 
        { 100.0f, 100.0f, 0.0f },
        { 100.0f, 100.0f, 0.0f },
        { 0.4f, 0.2f, 0.4f, 1.0f});

    Quad orangeQuad(
        { 0.0f, 200.0f, 0.0f },
        { 100.0f, 100.0f, 0.0f },
        { 1.0f, 0.5f, 0, 1.0f });

    scene->AddToScene<Quad>(purpleQuad);
    scene->AddToScene<Quad>(orangeQuad);

    float dx = 160.0f;
    float dy = 160.0f;
    while (app.IsOpen()) {

        /* Update all systems */
        app.Update();

        orangeQuad.Move(dx * app.timestep.deltaTime, dy * app.timestep.deltaTime);

        if (orangeQuad.position.x + orangeQuad.size.width >= 1280.0f ||
            orangeQuad.position.x <= 0.0f) {
            dx = -dx;
        }

        if (orangeQuad.position.y + orangeQuad.size.height >= 720.0f ||
            orangeQuad.position.y <= 0.0f) {
            dy = -dy;
        }

        /* Render current scene. */
        app.Render();
    }

    return 0;
}