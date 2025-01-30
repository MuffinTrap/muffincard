
#include "example.h"
#include <mgdl/mgdl-draw2d.h>

#include "rocket/mgdl-rocket.h"
#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    #include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK faceScale;
    static ROCKET_TRACK faceRotation;
    static ROCKET_TRACK faceZeta;
    static ROCKET_TRACK presentY;
    static ROCKET_TRACK presentZ;
    static ROCKET_TRACK presentVisible;
    static ROCKET_TRACK scrollX;
    static ROCKET_TRACK scrollY;
    static ROCKET_TRACK scrollSz;
#endif


#include <string>

static float faceS = 1.0f;
static float faceR = 0.0f;
static float faceZ = 0.0f;
static float pz = 1.0f;
static float py = 1.0f;
static bool pv = false;
static float textX = 0.0f;
static float textY = 0.0f;
static float textSz = 16.0f;
static std::string scrollText = "HAPPY BIRTHDAY TO MUFFINHOP! THE BESTEST BEAN!";

Example::Example()
{

}

void Example::Init()
{
    barb = gdl::LoadImage("assets/barb.png", gdl::TextureFilterModes::Linear);
    debugFont = gdl::LoadDebugFont();

    sampleMusic = gdl::LoadOgg("assets/sample3.ogg");

    wiiTexture = gdl::LoadImage("assets/texture.png", gdl::TextureFilterModes::Nearest);

    gdl::FBXFile* wiiFbx = new gdl::FBXFile();
    wiiScene = wiiFbx->LoadFile("assets/present.fbx");
    wiiScene->SetMaterialTexture("texture", wiiTexture);

    musicLooping = sampleMusic->GetLooping();
    glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool rocketInit = gdl::RocketSync::InitRocket(sampleMusic, 120, 4);
#ifndef SYNC_PLAYER
   faceScale = gdl::RocketSync::GetTrack("faceScale");
   faceRotation = gdl::RocketSync::GetTrack("faceRotation");
   faceZeta = gdl::RocketSync::GetTrack("faceZeta");
   presentY = gdl::RocketSync::GetTrack("presentY");
   presentZ = gdl::RocketSync::GetTrack("presentZ");
   presentVisible = gdl::RocketSync::GetTrack("presentVisible");
   scrollX = gdl::RocketSync::GetTrack("scrollX");
   scrollY = gdl::RocketSync::GetTrack("scrollY");
   scrollSz = gdl::RocketSync::GetTrack("scrollSize");
#endif
    gdl::RocketSync::StartSync();
}

void Example::Update()
{
    gdl::RocketSync::UpdateRow();
    faceS = gdl::RocketSync::GetFloat(faceScale);
    faceR = gdl::RocketSync::GetFloat(faceRotation);
    faceZ = gdl::RocketSync::GetFloat(faceZeta);
    py = gdl::RocketSync::GetFloat(presentY);
    pz = gdl::RocketSync::GetFloat(presentZ);
    pv = gdl::RocketSync::GetFloat(presentVisible);
    textX = gdl::RocketSync::GetFloat(scrollX);
    textY = gdl::RocketSync::GetFloat(scrollY);
    textSz = gdl::RocketSync::GetFloat(scrollSz);
#ifndef SYNC_PLAYER
    if (gdl::GetController(0).ButtonPress(gdl::WiiButtons::Button2))
    {
        gdl::RocketSync::SaveAllTracks();
    }
#endif

    // These are available only during update
    elapsedSeconds = gdl::GetElapsedSeconds();
    deltaTime = gdl::GetDeltaTime();
}

void DrawTextDouble(const char* text, short x, short y, float textHeight, gdl::Font* font)
{
        font->Print(gdl::Colors::Black, x, y, textHeight, gdl::LJustify, gdl::LJustify, text);

        font->Print(gdl::Colors::LightGreen, x-1, y-1, textHeight, gdl::LJustify, gdl::LJustify, text);
}

void Example::Draw()
{
    gdl::InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    DrawImage();

    if (pv)
    {
        DrawWii();
    }

    gdl::InitOrthoProjection();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Draw scrolltext
    DrawTextDouble(scrollText.c_str(), textX, textY, textSz, debugFont);
}

void Example::DrawImage()
{
    // Start to move back before present appears
    glPushMatrix();
    glTranslatef(0.0f, faceZ, 0.0f);
    // Draw Image
    barb->Draw2DAligned(
            gdl::GetScreenWidth()/2,
            gdl::GetScreenHeight()/2,
            faceS,
            gdl::Centered, gdl::Centered);

    glPopMatrix();
}


void Example::DrawWii()
{
    // Try to draw Wii 3D model
    gdl::InitPerspectiveProjection(75.0f, 0.1f, 100.0f);
    gdl::InitCamera(gdl::vec3(0.0f, 0.0f, 0.0f), gdl::vec3(0.0f, 0.0f, -1.0f), gdl::vec3(0.0f, 1.0f, 0.0f));

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE); //  is this needed?

	// This is the other way around on Wii, but
	// hopefully OpenGX handles it
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);

    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();

    // Move forward when time
    //

    glTranslatef(0.0f, py, pz);
    glRotatef(elapsedSeconds * 10.0f, elapsedSeconds*15.0f, 1.0f, 0.0f);
    glScalef(0.1f, 0.1f, 0.1f);

    wiiScene->Draw();

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}
