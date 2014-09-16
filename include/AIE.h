/**
*	@author	Jamie Stewart
*	@date	12/11/2012
*	@brief	This is the main entry point for access to the functionality provided by the
*			AIE Static OpenGL Framework. This class needs to be included in your main.cpp
*			in order to get a simple 2d sprite game up and running.
**/

#ifndef _AIE_H_

#define _AIE_H_

/**
* DLL Export Define
**/
#ifdef AIE_DLL_BUILD
#define DLLEXPORT __declspec(dllexport)
#elif AIE_DLL
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT
#endif
/**
*
* @brief Enumerator to Describe Sprite Blend Modes
*
**/
typedef enum SpriteBlendModes

{
	_ZERO = 0,			// = GL_ZERO
	_ONE = 1,			// = GL_ONE
	_SRC_COLOR = 0x0300,		// = GL_SRC_colour
	_DST_COLOR = 0x0306,		// = GL_DST_colour
	_ONE_MINUS_SRC_COLOR = 0x0301,		// = GL_ONE_MINUS_SRC_colour
	_ONE_MINUS_DST_COLOR = 0x0307,		// = GL_ONE_MINUS_DST_colour
	_SRC_ALPHA = 0x0302,		// = GL_SRC_ALPHA
	_DST_ALPHA = 0x0304,		// = GL_DST_ALPHA
	_ONE_MINUS_SRC_ALPHA = 0x0303,		// = GL_ONE_MINUS_SRC_ALPHA
	_ONE_MINUS_DST_ALPHA = 0x0305,		// = GL_ONE_MINUS_DST_ALPHA
	_BLEND_END

}SpriteBlendModes;

/**
* @brief Enumerator to Describe camera Movement Directions
**/
typedef enum CameraDirection
{

	eC_UP = 0x0001,
	eC_DOWN = 0x0010,
	eC_LEFT = 0x0100,
	eC_RIGHT = 0x1000,
	eC_END = 0

}CameraDirection;
/**
* @brief enumerator to define Key and Mouse button values
**/
typedef enum
{
	/* Printable keys */
	GLFW_KEY_SPACE = 32,
	GLFW_KEY_APOSTROPHE = 39, /* ' */
	GLFW_KEY_COMMA = 44, /* , */
	GLFW_KEY_MINUS = 45, /* - */
	GLFW_KEY_PERIOD = 46, /* . */
	GLFW_KEY_SLASH = 47, /* / */
	GLFW_KEY_0 = 48,
	GLFW_KEY_1 = 49,
	GLFW_KEY_2 = 50,
	GLFW_KEY_3 = 51,
	GLFW_KEY_4 = 52,
	GLFW_KEY_5 = 53,
	GLFW_KEY_6 = 54,
	GLFW_KEY_7 = 55,
	GLFW_KEY_8 = 56,
	GLFW_KEY_9 = 57,
	GLFW_KEY_SEMICOLON = 59, /* , */
	GLFW_KEY_EQUAL = 61, /* = */
	GLFW_KEY_A = 65,
	GLFW_KEY_B = 66,
	GLFW_KEY_C = 67,
	GLFW_KEY_D = 68,
	GLFW_KEY_E = 69,
	GLFW_KEY_F = 70,
	GLFW_KEY_G = 71,
	GLFW_KEY_H = 72,
	GLFW_KEY_I = 73,
	GLFW_KEY_J = 74,
	GLFW_KEY_K = 75,
	GLFW_KEY_L = 76,
	GLFW_KEY_M = 77,
	GLFW_KEY_N = 78,
	GLFW_KEY_O = 79,
	GLFW_KEY_P = 80,
	GLFW_KEY_Q = 81,
	GLFW_KEY_R = 82,
	GLFW_KEY_S = 83,
	GLFW_KEY_T = 84,
	GLFW_KEY_U = 85,
	GLFW_KEY_V = 86,
	GLFW_KEY_W = 87,
	GLFW_KEY_X = 88,
	GLFW_KEY_Y = 89,
	GLFW_KEY_Z = 90,
	GLFW_KEY_LEFT_BRACKET = 91, /* [ */
	GLFW_KEY_BACKSLASH = 92, /* \ */
	GLFW_KEY_RIGHT_BRACKET = 93, /* ] */
	GLFW_KEY_GRAVE_ACCENT = 96, /* ` */
	GLFW_KEY_WORLD_1 = 161, /* non-US #1 */
	GLFW_KEY_WORLD_2 = 162, /* non-US #2 */
	/* Function keys */
	GLFW_KEY_ESCAPE = 256,
	GLFW_KEY_ENTER = 257,
	GLFW_KEY_TAB = 258,
	GLFW_KEY_BACKSPACE = 259,
	GLFW_KEY_INSERT = 260,
	GLFW_KEY_DELETE = 261,
	GLFW_KEY_RIGHT = 262,
	GLFW_KEY_LEFT = 263,
	GLFW_KEY_DOWN = 264,
	GLFW_KEY_UP = 265,
	GLFW_KEY_PAGE_UP = 266,
	GLFW_KEY_PAGE_DOWN = 267,
	GLFW_KEY_HOME = 268,
	GLFW_KEY_END = 269,
	GLFW_KEY_CAPS_LOCK = 280,
	GLFW_KEY_SCROLL_LOCK = 281,
	GLFW_KEY_NUM_LOCK = 282,
	GLFW_KEY_PRINT_SCREEN = 283,
	GLFW_KEY_PAUSE = 284,
	GLFW_KEY_F1 = 290,
	GLFW_KEY_F2 = 291,
	GLFW_KEY_F3 = 292,
	GLFW_KEY_F4 = 293,
	GLFW_KEY_F5 = 294,
	GLFW_KEY_F6 = 295,
	GLFW_KEY_F7 = 296,
	GLFW_KEY_F8 = 297,
	GLFW_KEY_F9 = 298,
	GLFW_KEY_F10 = 299,
	GLFW_KEY_F11 = 300,
	GLFW_KEY_F12 = 301,
	GLFW_KEY_F13 = 302,
	GLFW_KEY_F14 = 303,
	GLFW_KEY_F15 = 304,
	GLFW_KEY_F16 = 305,
	GLFW_KEY_F17 = 306,
	GLFW_KEY_F18 = 307,
	GLFW_KEY_F19 = 308,
	GLFW_KEY_F20 = 309,
	GLFW_KEY_F21 = 310,
	GLFW_KEY_F22 = 311,
	GLFW_KEY_F23 = 312,
	GLFW_KEY_F24 = 313,
	GLFW_KEY_F25 = 314,
	GLFW_KEY_KP_0 = 320,
	GLFW_KEY_KP_1 = 321,
	GLFW_KEY_KP_2 = 322,
	GLFW_KEY_KP_3 = 323,
	GLFW_KEY_KP_4 = 324,
	GLFW_KEY_KP_5 = 325,
	GLFW_KEY_KP_6 = 326,
	GLFW_KEY_KP_7 = 327,
	GLFW_KEY_KP_8 = 328,
	GLFW_KEY_KP_9 = 329,
	GLFW_KEY_KP_DECIMAL = 330,
	GLFW_KEY_KP_DIVIDE = 331,
	GLFW_KEY_KP_MULTIPLY = 332,
	GLFW_KEY_KP_SUBTRACT = 333,
	GLFW_KEY_KP_ADD = 334,
	GLFW_KEY_KP_ENTER = 335,
	GLFW_KEY_KP_EQUAL = 336,
	GLFW_KEY_LEFT_SHIFT = 340,
	GLFW_KEY_LEFT_CONTROL = 341,
	GLFW_KEY_LEFT_ALT = 342,
	GLFW_KEY_LEFT_SUPER = 343,
	GLFW_KEY_RIGHT_SHIFT = 344,
	GLFW_KEY_RIGHT_CONTROL = 345,
	GLFW_KEY_RIGHT_ALT = 346,
	GLFW_KEY_RIGHT_SUPER = 347,
	GLFW_KEY_MENU = 348,
	GLFW_KEY_LAST = GLFW_KEY_MENU,
};

/**
* @brief A Structure to describe a colour value as an unsigned int, and as individual 8 bit components (char values)
**/
struct SColour
{
	/// @brief Default constructor for a SColour object
	SColour() {}
	/// @brief Constructor for an SColour obejct that constructs the SColour object from an unsigned integer value
	/// @param a_iColor the colour that the SColour will be created to specify
	SColour(unsigned int a_iColour) { argb.colour = a_iColour; }
	/// @brief Constructor to create an SColor object from four char values RGBA
	/// @param r unsigned char to represent the red component of an SColour object
	/// @param g unsigned char to represent the red component of an SColour object
	/// @param b unsigned char to represent the red component of an SColour object
	/// @param a unsigned char to represent the red component of an SColour object
	SColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		argb.colours.r = r;
		argb.colours.g = g;
		argb.colours.b = b;
		argb.colours.a = a;
	}
	/// and unnamed union that causes SColours member variables to use the same area of memory.
	/// this means that @param colour and @param colours occupy the same space, a change to one is
	/// reflected in the other.
	union
	{
		unsigned int colour;
		struct SColours
		{
			unsigned char a, r, g, b;
		} colours;
	}argb;

};

//////////////////////////////////////////////////////////////////////////
/// @brief Call this function to initialise the framework
/// @param a_iWidth the width in pixels that we want the screen to display for the width of the window
/// @param a_height the width in pixels that we want the screen to display for the height of the window
/// @param a_bFullscreen should this application run in a fullscreen mode.
/// @param a_pWIndowTitle the title that we want to be displayed in the windows title bar
//////////////////////////////////////////////////////////////////////////
DLLEXPORT int			Initialise(int a_iWidth, int a_iHeight, bool a_bFullscreen = false, const char* a_pWindowTitle = nullptr);
//////////////////////////////////////////////////////////////////////////
/// @brief This function should be called just prior to exiting your program
///			 it will unload all the components of the AIE Framework that have been loaded
//////////////////////////////////////////////////////////////////////////
DLLEXPORT void			Shutdown();
//////////////////////////////////////////////////////////////////////////
/// @brief This function is to be called each frame to update the current frame.
/// @return a boolean value indicating that the framework updated successfully
//////////////////////////////////////////////////////////////////////////
DLLEXPORT bool			FrameworkUpdate();
//////////////////////////////////////////////////////////////////////////
/// @brief Call this function to clear any content that has been rendered to the screen
//////////////////////////////////////////////////////////////////////////
DLLEXPORT void			ClearScreen();
//////////////////////////////////////////////////////////////////////////
/// @brief Call this function to Set the background colour
/// @param a_BGColour the colour to set the background scene to
//////////////////////////////////////////////////////////////////////////
DLLEXPORT void			SetBackgroundColour(SColour a_BGColour);
/// Function to create a Sprite
/// @param a_pTextureName - the name of the texture that the sprite image resides in
/// @param a_fWidth - the width that the sprite object is to be draw on the screen, this width is in pixels
/// @param a_fHeight - the height that the sprite object is to be draw on the screen, this height is in pixels
/// @param a_bDrawFromCenter - weather or not the sprite is to be drawn from the center position, defaults to true
/// @param a_sColour - the colour tint that the sprite is to be given, defaults to white.
/// @return the ID for the sprite, this is an unsigned integer.
DLLEXPORT unsigned int	CreateSprite(const char* a_pTextureName, int a_iWidth, int a_iHeight, bool a_bDrawFromCenter, SColour a_sColour = SColour(0xFF, 0xFF, 0xFF, 0xFF));
/// Function to create a Sprite
/// @param a_pTextureName - the name of the texture that the sprite image resides in
/// @param a_fv2Size - the width and height of the sprite in Pixels as a float vector
/// @param a_fv2Origin - The origin position for the sprite matrix, this dictates where the sprite will be drawn from (Top Left, Top Right etc)
/// @param a_v4UVCoords - The UV Coordinates for the sprite as a float 4, components  1 & 2 correspond to origin point, components 3 & 4 correspond to end point.
/// @param a_sColour - the colour tint that the sprite is to be given, defaults to white.
/// @return the ID for the sprite, this is an unsigned integer.
DLLEXPORT unsigned int	CreateSprite(const char* a_pTextureName, float* a_fv2Size, float* a_fv2Origin, float* a_fv4UVCoords = nullptr, SColour a_sColour = SColour(0xFF, 0xFF, 0xFF, 0xFF));
/// Function to Duplicate an existing Sprite
/// @param a_uiSpriteID This is ID of the sprite that is to be duplicated
/// @return Returns a new sprite ID.
DLLEXPORT unsigned int	DuplicateSprite(unsigned int a_uiSpriteID);
/// This function is used to free up the memory associated with the Sprite ID passed in. After this function is called the sprite can no longer be drawn as it ceases to exist
/// @param a_uiSpriteID the ID of the sprite to be destroyed.
DLLEXPORT void			DestroySprite(unsigned int a_uiSpriteID);


DLLEXPORT void			SetSpriteColour(unsigned int a_uiSpriteID, SColour& a_sColour);

DLLEXPORT void			GetSpriteColour(unsigned int a_uiSpriteID, SColour& a_sColour);
/// This funciton moves a Sprite
/// @param a_uiSpriteID the ID of the sprite to be moved
/// @param a_fXPos the X co-ordinate that the sprite is to be moved to in screenspace
/// @param a_fYPos the Y co-ordinate that the sprite is to be moved to in screenspace
DLLEXPORT void			MoveSprite(unsigned int a_uiSpriteID, float a_fXPos, float a_fYPos);
/// This funciton moves a Sprite
/// @param a_uiSpriteID the ID of the sprite to be moved
/// @param a_fVec a float vector that contains two values (X & Y) to relocate the sprite to
DLLEXPORT void			MoveSprite(unsigned int a_uiSpriteID, float* a_vFloatVec);
/// @brief This function sets the 4x4 matrix for the sprite
/// @param a_uiSpriteID the unique identifier for the sprite
/// @param a_fm4 a float pointer indicating the start of a float array containing 16 values representing a 4 x 4 matrix
DLLEXPORT void			SetSpriteMatrix(unsigned int a_uiSpriteID, float* a_fm4);
/// @brief This function gets the 4x4 matrix for the sprite
/// @param a_uiSpriteID the unique identifier for the sprite
/// @param a_fm4 a float pointer indicating the start of a float array that is to be used to hold the 16 float values representing a 4 x 4 matrix
DLLEXPORT void			GetSpriteMatrix(unsigned int a_uiSpriteID, float* a_fm4);
DLLEXPORT void			RotateSprite(unsigned int a_uiSpriteID, float a_fRotation);



DLLEXPORT void			DrawSprite(unsigned int a_uiSpriteID);

DLLEXPORT void			SetSpriteUVCoordinates(unsigned int a_uiSpriteID, float a_minUCoord, float a_minVCoord, float a_maxUCoord, float a_maxVCoord);

DLLEXPORT void			SetSpriteUVCoordinates(unsigned int a_uiSpriteID, float* a_fUVVec4);

DLLEXPORT void			GetSpriteUVCoordinates(unsigned int a_uiSpriteID, float& a_minUCoord, float& a_minVCoord, float& a_maxUCoord, float& a_maxVCoord);

DLLEXPORT void			GetSpriteUVCoordinates(unsigned int a_uiSpriteID, float* a_fUVVec4);

DLLEXPORT void			SetSpriteScale(unsigned int a_uiSpriteID, float& a_fSpriteWidth, float& a_fSpriteHeight);

DLLEXPORT void			GetSpriteScale(unsigned int a_uiSpriteID, float& a_fSpriteWidth, float& a_fSpriteHeight);

DLLEXPORT void			SetSpriteBlendMode(unsigned int a_uiSpriteID, const unsigned int& a_uiSourceFactor, const unsigned int& a_uiDestinationFactor);

DLLEXPORT void			GetSpriteBlendMode(unsigned int a_uiSpriteID, unsigned int& a_uiSourceFactor, unsigned int& a_uiDestinationFactor);

//////////////////////////////////////////////////////////////////////////

// Basic Line Drawing Functionality

//////////////////////////////////////////////////////////////////////////

DLLEXPORT void			DrawLine(int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY);

DLLEXPORT void			DrawLine(int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY, SColour a_sColour);

DLLEXPORT void			DrawLine(int a_iStartX, int a_iStartY, int a_iEndX, int a_iEndY, SColour a_sStartColour, SColour a_sEndColour);



//////////////////////////////////////////////////////////////////////////

// Draws a String to the screen

//////////////////////////////////////////////////////////////////////////

DLLEXPORT void			DrawString(const char* a_pText, int a_iXPos, int a_iYPos, SColour a_sColour = SColour(0xFF, 0xFF, 0xFF, 0xFF));
DLLEXPORT void			AddFont(const char* a_pFontName);
DLLEXPORT void			SetFont(const char* a_pFontName);
DLLEXPORT void			RemoveFont(const char* a_pFontName);

//////////////////////////////////////////////////////////////////////////

// Input Handling Functionality

//////////////////////////////////////////////////////////////////////////

DLLEXPORT bool			IsKeyDown(int a_iKey);

DLLEXPORT void			GetMouseLocation(double& a_iMouseX, double& a_iMouseY);

DLLEXPORT bool			GetMouseButtonDown(int a_iMouseButtonToTest);

DLLEXPORT bool			GetMouseButtonReleased(int a_iMouseButtonToTest);

//////////////////////////////////////////////////////////////////////////

// Basic Camera Control

//////////////////////////////////////////////////////////////////////////

DLLEXPORT void			MoveCamera(CameraDirection a_eCameraDirection, float a_fCameraSpeed);

DLLEXPORT void			MoveCamera(float a_fXPos, float a_fYPos);

DLLEXPORT void			RotateCamera(float a_fRotation);

DLLEXPORT void			GetCameraPosition(float& a_fx, float& a_fy);

//////////////////////////////////////////////////////////////////////////

// Gets the Delta Time

//////////////////////////////////////////////////////////////////////////

DLLEXPORT float 		GetDeltaTime();

//////////////////////////////////////////////////////////////////////////

#endif //_AIE_H_

//////////////////////////////////////////////////////////////////////////
