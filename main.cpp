#include <mgdl.h>
#include "example.h"


#include "mgdl-rocket.h"



static Example example;

void Cross3D()
{
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);

        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(1.0f, 1.0f, -1.0f);

        glVertex3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
}

void Cross2D()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f((float)gdl::GetScreenWidth(), (float)gdl::GetScreenHeight());

    glVertex2f(0.0f, (float)gdl::GetScreenHeight());
    glVertex2f((float)gdl::GetScreenWidth(), 0.0f);
    glEnd();
}


//---------------------------------------------------------------------

void init()
{
    glViewport(0, 0, gdl::GetScreenWidth(), gdl::GetScreenHeight());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glClearColor(247.0f/255.0f, 1.0f, 174.0f/255.0f, 0.0f);
    example.Init();

}

// Called before render()
void update()
{
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::ButtonHome))
    {
        gdl::Platform& plat = gdl::Platform::GetPlatform();
        plat.DoProgramExit();
    }
    example.Update();

}

// Rendering callback. glFlush etc.. is done automatically after it
void render()
{
    // NOTE Use this instead of glClear() for Wii quirk.
    gdl::cross_glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    example.Draw();
}

int main()
{
    gdl::InitSystem(
        gdl::ScreenAspect::Screen4x3,
        init,
        update,  // std::function callbacks
        render
    );
}
