// Datei : DX8Graphics.hpp

// --------------------------------------------------------------------------------------
//
// Direct Graphics Klasse
// zum initialisieren von DirectX8
// beinhaltet zudem verschiedene Grafik-Funktionen zum Speichern von Screenshots usw
//
// (c) 2002 Jörg M. Winterstein
//
// --------------------------------------------------------------------------------------

#ifndef _DX8GRAPHICS_HPP_
#define _DX8GRAPHICS_HPP_

// --------------------------------------------------------------------------------------
// Include Dateien
// --------------------------------------------------------------------------------------

#include "SDL_port.hpp"
#if defined(USE_GL2) || defined(USE_GL3)
#  include "cshader.hpp"
#  if defined(USE_FBO)
#    include "cfbo.hpp"
#  endif /* USE_FBO */
#endif /* USE_GL2 || USE_GL3 */

// --------------------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------------------

enum class BlendModeEnum {
  ADDITIV,
  COLORKEY,
  WHITE
};

#if defined(USE_GL2) || defined(USE_GL3)
enum { PROGRAM_COLOR = 0, PROGRAM_TEXTURE, PROGRAM_RENDER, PROGRAM_TOTAL, PROGRAM_NONE };
#endif

// --------------------------------------------------------------------------------------
// Strukturen
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Struktur für einen 2D Vertex
// --------------------------------------------------------------------------------------

// DKS - Removed unnecessary z-coordinate:
struct VERTEX2D {
    float x, y;      // x,y Koordinaten
    D3DCOLOR color;  // Vertex-Color
    float tu, tv;    // Textur-Koordinaten
};

// DKS - Added
struct QUAD2D {
    VERTEX2D v1, v2, v3, v4;
};

// --------------------------------------------------------------------------------------
// Klassendeklaration
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// DirectGraphics Klasse
// --------------------------------------------------------------------------------------

class DirectGraphicsClass {
  private:
    enum class shader_t {COLOR, TEXTURE, RENDER};

  private:
    bool VSyncEnabled;  // VSync ein/aus ?
    bool FilterMode;    // Linearer Filter an/aus?
    bool CrtEnabled;
    const char *glextensions;
    shader_t use_shader;
    BlendModeEnum BlendMode;  // Additiv, Colorkey oder White mode aktiviert?
    int MaxTextureUnits;
    bool SupportedETC1;
    bool SupportedPVRTC;
#if defined(USE_GL2) || defined(USE_GL3)
    GLuint ProgramCurrent;
    GLuint NameTime;
    CShader Shaders[PROGRAM_TOTAL];
#endif
    glm::mat4x4 matProjWindow;
    glm::mat4x4 matProjRender;

#if SDL_VERSION_ATLEAST(2, 0, 0)
    SDL_Window *Window;
    SDL_GLContext GLcontext;
#else /* SDL 1.2 */
    SDL_Surface *Screen;
#endif
    SDL_Rect WindowView;
    SDL_Rect RenderView;
    SDL_Rect RenderRect;
#if (defined(USE_GL2) || defined(USE_GL3)) && defined(USE_FBO)
    CFbo RenderBuffer;
#endif

  public:
    void ShowBackBuffer();  // Present aufrufen

    DirectGraphicsClass();   // Konstruktor
    ~DirectGraphicsClass();  // Desktruktor

    bool Init(std::uint32_t dwBreite, std::uint32_t dwHoehe, std::uint32_t dwZ_Bits, bool VSync);
    bool Exit();  // D3D beenden
    bool SetDeviceInfo();

    bool TakeScreenshot(const char Filename[100], int screenx,
                        int screeny);   // Screenshot machen
    void SetColorKeyMode();         // Alpha für Colorkey oder
    void SetAdditiveMode();         // Additive-Blending nutzen
    void SetWhiteMode();            // Komplett weiss rendern
    void SetFilterMode(bool filteron);  // Linearer Textur Filter ein/aus

    void RendertoBuffer(GLenum PrimitiveType,          // Rendert in den Buffer, der am Ende
                        std::uint32_t PrimitiveCount,  // eines jeden Frames komplett in
                        void *pVertexStreamZeroData);  // den Backbuffer gerendert wird

    void DisplayBuffer();  // Render den Buffer auf den Backbuffer
    // DKS - SetTexture is now used for both GL and DirectX, and uses new TexturesystemClass:
    void SetTexture(int idx);
    bool ExtensionSupported(const char *ext);
    void SetupFramebuffers();
    void ClearBackBuffer();
#if (defined(USE_GL2) || defined(USE_GL3)) && defined(USE_FBO)
    void SelectBuffer(bool active);
#endif

    inline BlendModeEnum GetBlendMode() const { return BlendMode; }
    inline bool IsETC1Supported() const { return SupportedETC1; }
    inline bool IsPVRTCSupported() const { return SupportedPVRTC; }

#if SDL_VERSION_ATLEAST(2, 0, 0)
    void FlipSurface(SDL_Surface* surface);
#endif
};



// --------------------------------------------------------------------------------------
// Externals
// --------------------------------------------------------------------------------------

extern DirectGraphicsClass DirectGraphics;  // DirectGraphics Klasse
extern glm::mat4x4 matProj;                  // Projektionsmatrix
extern glm::mat4x4 matWorld;                 // Weltmatrix
extern float DegreetoRad[360];              // Tabelle mit Rotationswerten

#endif
