
#include "example.h"
#include <mgdl/mgdl-draw2d.h>

#include "rocket/mgdl-rocket.h"
#ifdef SYNC_PLAYER
    #include MGDL_ROCKET_FILE_H
    #include MGDL_ROCKET_FILE_CPP
#else
    static ROCKET_TRACK faceX;
    static ROCKET_TRACK faceY;
    static ROCKET_TRACK faceScale;
    static ROCKET_TRACK faceRotation;
    static ROCKET_TRACK faceZeta;
    static ROCKET_TRACK presentX;
    static ROCKET_TRACK presentY;
    static ROCKET_TRACK presentZ;
    static ROCKET_TRACK presentScale;
    static ROCKET_TRACK presentVisible;

    static ROCKET_TRACK scrollX;
    static ROCKET_TRACK scrollY;
    static ROCKET_TRACK scrollSize;

    static ROCKET_TRACK greetX;
    static ROCKET_TRACK greetY;
    static ROCKET_TRACK greetSize;
#endif


#include <string>

static float facepX = 0.0f;
static float facepY = 0.0f;
static float faceS = 1.0f;
static float faceR = 0.0f;
static float faceZ = 0.0f;

static float px = 1.0f;
static float pz = 1.0f;
static float py = 1.0f;
static float pScale = 1.0f;
static bool pv = false;
static float textX = 0.0f;
static float textY = 0.0f;
static float textSz = 16.0f;
static std::string scrollText = "HAPPY BIRTHDAY MUFFINHOP!! YOU IS THE BESTEST BEAN! Your Marmot friends are wishing you a very happy birthday from the funny boat that sails and goes doo doo do do do etc etc.. we made this funny wii demo just for you on the thursday night before leaving for JML, and we are sharing it at the party for everyone to \"enjoy\"!!!!!!!";
static std::string greetsText = "greetings to jumalan lautta, Mehu, Slipstream, SVaTG, FTG, RBBS, matt current, Magnetismin Tietokonekerho, mfx, unique, Dekadence, Znorgonzola, Accession, etc, Paraguay, RiFT, MB, PB, like 50 other groups, Fairlight, bC!, fuckings to Nintendo";
static float grtX = 0.0f;
static float grtY = 0.0f;
static float grtSz = 16.0f;

Example::Example()
{

}

void Example::Init()
{
    barb = gdl::LoadImage("assets/barb.png", gdl::TextureFilterModes::Linear);
    debugFont = gdl::LoadDebugFont();

    sampleMusic = gdl::LoadOgg("assets/BDAY.ogg");

    wiiTexture = gdl::LoadImage("assets/texture.png", gdl::TextureFilterModes::Nearest);

    gdl::FBXFile* wiiFbx = new gdl::FBXFile();
    wiiScene = wiiFbx->LoadFile("assets/wrapped_present.fbx");
    wiiScene->SetMaterialTexture("standardSurface1.001", wiiTexture);

    musicLooping = sampleMusic->GetLooping();
    glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gdl::RocketSync::InitRocket(sampleMusic, 140, 4);
#ifndef SYNC_PLAYER
   faceX = gdl::RocketSync::GetTrack("faceX");
   faceY = gdl::RocketSync::GetTrack("faceY");
   faceScale = gdl::RocketSync::GetTrack("faceScale");
   faceRotation = gdl::RocketSync::GetTrack("faceRotation");
   faceZeta = gdl::RocketSync::GetTrack("faceZeta");
   presentX = gdl::RocketSync::GetTrack("presentX");
   presentY = gdl::RocketSync::GetTrack("presentY");
   presentZ = gdl::RocketSync::GetTrack("presentZ");
   presentScale = gdl::RocketSync::GetTrack("presentScale");
   presentVisible = gdl::RocketSync::GetTrack("presentVisible");

   scrollX = gdl::RocketSync::GetTrack("scrollX");
   scrollY = gdl::RocketSync::GetTrack("scrollY");
   scrollSize = gdl::RocketSync::GetTrack("scrollSize");

   greetX = gdl::RocketSync::GetTrack("greetX");
   greetY = gdl::RocketSync::GetTrack("greetY");
   greetSize = gdl::RocketSync::GetTrack("greetSize");
#endif
    gdl::RocketSync::StartSync();
}

void Example::Update()
{
    gdl::RocketSync::UpdateRow();
    facepX = gdl::RocketSync::GetFloat(faceX);
    facepY = gdl::RocketSync::GetFloat(faceY);
    faceS = gdl::RocketSync::GetFloat(faceScale);
    faceR = gdl::RocketSync::GetFloat(faceRotation);
    faceZ = gdl::RocketSync::GetFloat(faceZeta);
    px = gdl::RocketSync::GetFloat(presentX);
    py = gdl::RocketSync::GetFloat(presentY);
    pz = gdl::RocketSync::GetFloat(presentZ);
    pv = gdl::RocketSync::GetFloat(presentVisible);
    pScale = gdl::RocketSync::GetFloat(presentScale);
    textX = gdl::RocketSync::GetFloat(scrollX);
    textY = gdl::RocketSync::GetFloat(scrollY);
    textSz = gdl::RocketSync::GetFloat(scrollSize);
    grtX = gdl::RocketSync::GetFloat(greetX);
    grtY = gdl::RocketSync::GetFloat(greetY);
    grtSz = gdl::RocketSync::GetFloat(greetSize);
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

void DrawTextDouble(const char* text, short x, short y, float textHeight, gdl::Font* font, gdl::Color color)
{
        font->Print(gdl::Colors::Black, x, y, textHeight, gdl::LJustify, gdl::LJustify, text);

        font->Print(color, x-1, y-1, textHeight, gdl::LJustify, gdl::LJustify, text);
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
    DrawTextDouble(scrollText.c_str(), textX, textY, textSz, debugFont, gdl::Colors::LightGreen);
    DrawTextDouble(greetsText.c_str(), grtX, grtY, grtSz, debugFont, gdl::Colors::LightRed);
}

void Example::DrawImage()
{
    // Start to move back before present appears
    glPushMatrix();
    glTranslatef(0.0f, faceZ, 0.0f);
    // Draw Image
    barb->Draw2DAligned(
            gdl::GetScreenWidth()/2 + facepX,
            gdl::GetScreenHeight()/2 + facepY,
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

    glTranslatef(px, py, pz);
    glRotatef(elapsedSeconds * 10.0f, elapsedSeconds*15.0f, elapsedSeconds * -4.0f, 0.0f);
    glScalef(pScale, pScale, pScale);

    wiiScene->Draw();

    glPopMatrix();
    glDisable(GL_DEPTH_TEST);
}
