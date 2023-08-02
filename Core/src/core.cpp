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

    float sPos[3] = { 100.0f, 100.0f, 0.0f };
    float sS[3] = { 100.0f, 100.0f, 0.0f };
    Quad shape(1, sPos, sS);

    scene->AddToScene<Quad>(shape);

    while (app.IsOpen()) {

        /* Update all systems */
        app.Update(0);

        /* Render current scene. */
        app.Render();
    }

    return 0;
}