#include "app.h"
#include "utils.h"

#include "scene.h"
#include "quad.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


int main(void)
{
    Application app("OpenGL Sandbox", 1280, 720);


    std::shared_ptr<Scene> scene = app.NewScene("Sandbox");
    app.SetScene("Sandbox");

    for (int i = 0; i < 1000; i++) {
        Quad quad(
            { RandomFloat(0.0f, 1180.0f), RandomFloat(0.0f, 620.0f), 0.0f },
            { 100.0f, 100.0f, 0.0f },
            { RandomFloat(0.0f, 1.0f), RandomFloat(0.0f, 1.0f), RandomFloat(0.0f, 1.0f), 0.8f }
        );

        float dx = (i % 2 == 0 ? 1 : -1) * RandomFloat(150.0f, 350.0f);
        float dy = (i % 2 == 0 ? 1 : -1) * RandomFloat(150.0f, 350.0f);
        quad.AddComponent<TransformComponent>({ dx, dy, 0.0f });

        scene->AddToScene<Quad>(quad);
    }

    scene->AddProcedure(new UpdateQuad);

    scene->AttachGUI(new DiagnosticsGUI);

    while (app.IsOpen()) {

        /* Update all systems */
        app.Update();

        /* Render current scene. */
        app.Render();
    }

    return 0;
}