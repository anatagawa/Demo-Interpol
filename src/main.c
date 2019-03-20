#include <raylib.h>
#include <raymath.h>
#include <string.h>
#include "data.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Vector2 Screen = (Vector2) { 720,566};
Vector2 VirtualScreen = (Vector2) { 720,566};

typedef struct Rond {
	Vector2 position;
	Vector2 rayon;
	Vector2 center;
	float offset;
	float angle;
} Rond;

Rond myrond1;
Rond myrond2;

Rond InitRond(float cx, float cy, float rx, float ry, float offset) {
	Rond p;
	p.rayon = (Vector2) { rx, ry };
	p.center = (Vector2) { cx, cy };
	p.offset = offset;
	p.position = p.center;
	return p;
}

void moveNext(Rond *rond) {
	rond->position.x = rond->center.x + rond->rayon.x * cos(rond->angle*rond->offset);
	rond->position.y = rond->center.y + rond->rayon.y * sin(rond->angle*rond->offset);
	rond->angle += rond->offset;
}

void DrawFrameBuffer(RenderTexture2D renderer);

// -------------------------------------------------------------------------------------------------------------
// Main Game
// -------------------------------------------------------------------------------------------------------------
int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(GetMonitorWidth(0),GetMonitorHeight(0),"Demo Interpol");
	SetWindowMinSize(Screen.x, Screen.y);

	HideCursor();
	
	InitAudioDevice();

	// -------------------------------------------------------------------------------------------------------------
	// Icone window
	// -------------------------------------------------------------------------------------------------------------

	Image icon = LoadImagePro( icon_data, 32, 32, UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	UnloadImage(icon);

	// -------------------------------------------------------------------------------------------------------------
	// Logo
	// -------------------------------------------------------------------------------------------------------------

	Image _logo = LoadImagePro(logo_data, 64, 22, UNCOMPRESSED_R8G8B8A8);
	Texture2D logo = LoadTextureFromImage(_logo);
	UnloadImage(_logo);

	// -------------------------------------------------------------------------------------------------------------
	// font data
	// -------------------------------------------------------------------------------------------------------------

	Image _font_data = LoadImagePro(font_data, 944, 24, UNCOMPRESSED_R8G8B8A8);
	Texture2D font_data = LoadTextureFromImage(_font_data);
	UnloadImage(_font_data);

	// -------------------------------------------------------------------------------------------------------------
	// Framebuffer
	// -------------------------------------------------------------------------------------------------------------

	RenderTexture2D frameBuffer = LoadRenderTexture( VirtualScreen.x, VirtualScreen.y );
	SetTextureFilter(frameBuffer.texture, FILTER_POINT);

	// -------------------------------------------------------------------------------------------------------------
	// Music
	// -------------------------------------------------------------------------------------------------------------

	Music music = LoadMusicStream("gypsies-smell.mod");
	PlayMusicStream(music);
	SetMusicVolume(music, 1.0f);

	// -------------------------------------------------------------------------------------------------------------
	// Divers
	// -------------------------------------------------------------------------------------------------------------

	SetTargetFPS(60);

	myrond1 = InitRond(720/2,244,180,150,0.25);
	myrond2 = InitRond(720/2,244,190,150,0.25);

	char * text1 =  "                                   \n" \
					"        ( I N T E R P O L )        \n" \
					"         -----------------         \n" \
					"                                   \n" \
					"          PROUDLY PRESENT          \n" \
					"                                   \n" \
					"             THEIR NEW             \n" \
					"                                   \n" \
					"            CRACK INTRO            \n" \
					"                                   \n" \
					"                                   \n" \
					"SOME NEWS ABOUT INTERPOL COMING UP \n";

	char * text2 =  "                                   \n" \
					"                                   \n" \
					"   INTERPOL GOT TWO NEW MEMBERS    \n" \
					"                                   \n" \
					"                                   \n" \
					"     ...KAOZ AND KILLRAVEN...      \n" \
					"                                   \n" \
					"                                   \n" \
					"       THEY DO MODEMTRADING        \n" \
					"      ----------------------       \n" \
					"                                   \n" \
					"            KAOZ&RAVEN             \n";

	char * text3 =  "                                   \n" \
					"  KAOZ IS THE FORMER REBEL MC OF   \n" \
					" NOXIOUS. HE LEFT THEN AND JOINED  \n" \
					"AS A PURE MODEM TRADER. SO FOR ALL \n" \
					"   WHO DONT KNOW IT YET... STOP    \n" \
					"CONTACTING HIM BECAUSE HE FINISHED \n" \
					"        ALL MAIL SWAPPING.         \n" \
					"                                   \n" \
					"KILLRAVEN LEFT PARADISE AND JOINED \n" \
					" US ALSO AS A MODEM TRADER BUT HE  \n" \
					" CONTINUES MAIL SWAPPING WITH HIS  \n" \
					"         BEST MATES ONLY.          \n";

	char * text4 =  "                                   \n" \
					"     CALL THE INTERPOL BOARDS      \n" \
					"                                   \n" \
					"                                   \n" \
					"NIRVANA                            \n" \
					"                      CONCEPT ELITE\n" \
					"CREEPING DEATH                     \n" \
					"                       DESERT STORM\n" \
					"                                   \n" \
					"  ASK THE ELITE FOR THE NUMBERS.   \n" \
					"                                   \n" \
					"         BEST MATES ONLY.          ";

	char * text5 = 	"                                   \n" \
					"                                   \n" \
					"           DEMO INTERPOL           \n" \
					"                                   \n" \
					"                                   \n" \
					"          CODING BY ANATA          \n" \
					"                                   \n" \
					"                                   \n" \
					"     MADE WITH RAYLIB LIBRARY      \n" \
					"                                   \n" \
					"                                   \n" \
					"                                   \n";

	char *completeText[] = { text1, text2, text3, text4, text5 };
	int textIndex = 0;
	int tick = 0;
	float alpha = 0;
	int timeText = 600;
	int nbPageText = 5;

	// -------------------------------------------------------------------------------------------------------------
	// Game Loop
	// -------------------------------------------------------------------------------------------------------------
	while(!WindowShouldClose()) {
		UpdateMusicStream(music);

		// -------------------------------------------------------------------------------------------------------------
		// Move triangles centers
		// -------------------------------------------------------------------------------------------------------------

		moveNext(&myrond1);
		moveNext(&myrond2);

		// -------------------------------------------------------------------------------------------------------------
		// Page Text change
		// -------------------------------------------------------------------------------------------------------------

		tick++;		
		int tempo = tick % timeText;

		if(tempo <= 100) alpha += 2.55;
		else if(tempo >= timeText-100) {
			alpha -= 2.55;
			tempo = (timeText-tempo) / 100;
		}

		alpha = Clamp(alpha, 0, 255);

		textIndex = ( tick / timeText ) % nbPageText;

		// -------------------------------------------------------------------------------------------------------------
		// Framebuffer
		// -------------------------------------------------------------------------------------------------------------

		BeginTextureMode(frameBuffer);
		{
			ClearBackground(BLANK);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Background
			// -------------------------------------------------------------------------------------------------------------

			DrawRectangle( 0, 35, 720, 400, (Color) { 0,32,66,255});

			// -------------------------------------------------------------------------------------------------------------
			// Draw Page Text
			// -------------------------------------------------------------------------------------------------------------

			Vector2 textOffset = { 0, 0 };

			for(int i = 0; i < strlen(completeText[textIndex]); i++) {
				if( (unsigned char)completeText[textIndex][i] == '\n') {
					textOffset.y += 26;
					textOffset.x = 0 - (i*16)-16;
				} else {
					DrawTexturePro(
						font_data,
						(Rectangle) { (completeText[textIndex][i] - 32) * 16, 0, 16, 24 },
						(Rectangle) { 88+textOffset.x + ( i * 16 + 1 ) , 45+textOffset.y , 16, 24 },
						(Vector2) {0},
						0,
						(Color) { 255, 255, 255, alpha }
					);
				}
			}

			// -------------------------------------------------------------------------------------------------------------
			// Draw triangles with blend effect
			// -------------------------------------------------------------------------------------------------------------

			BeginBlendMode(BLEND_ADDITIVE);
			{
				for(int i=720/12;i<720;i+=720/6 ) {
					// Top

					DrawTriangle(
						(Vector2) { i , 35 },
						(Vector2) { myrond2.position.x, myrond2.position.y},
						(Vector2) { i + 60, 35},
						(Color) { 16,32,115,128 }
					);

					DrawTriangle(
						(Vector2) { i , 35 },
						(Vector2) { myrond1.position.x, myrond1.position.y},
						(Vector2) { i + 60, 35},
						(Color) { 24,62,165,128 }
					);

					// Down
					DrawTriangle(
						(Vector2) { myrond2.position.x, myrond2.position.y},
						(Vector2) { i,435 },
						(Vector2) { i + (720/12), 435},
						(Color) { 16,32,115,128 }
					);

					DrawTriangle(
						(Vector2) { myrond1.position.x, myrond1.position.y},
						(Vector2) { i,435 },
						(Vector2) { i + (720/12), 435},
						(Color) { 24,62,165,128 }
					);
				}

				for (int i=38+(398/9);i<434;i+=398/4.5) {
					// Right
					DrawTriangle(
						(Vector2) { myrond2.position.x, myrond2.position.y},
						(Vector2) { 721,i+(398/9)},
						(Vector2) { 721,i },
						(Color) { 16,32,115,128 }
					);

					DrawTriangle(
						(Vector2) { myrond1.position.x, myrond1.position.y},
						(Vector2) { 721,i+(398/9)},
						(Vector2) { 721,i },
						(Color) { 24,62,165,128 }
					);
				}

				for (int i=38;i<434;i+=398/4.5) {
					// Left
					DrawTriangle(
						(Vector2) { 0,i },
						(Vector2) { 0,i+(398/9)},
						(Vector2) { myrond2.position.x, myrond2.position.y},
						(Color) { 16,32,115,128 }
					);

					DrawTriangle(
						(Vector2) { 0,i },
						(Vector2) { 0,i+(398/9)},
						(Vector2) { myrond1.position.x, myrond1.position.y},
						(Color) { 24,62,165,128 }
					);
				}
			}
			EndBlendMode();

			// -------------------------------------------------------------------------------------------------------------
			// Draw Logo
			// -------------------------------------------------------------------------------------------------------------

			DrawTexture(logo, 618, 403, WHITE);

			// -------------------------------------------------------------------------------------------------------------
			// Draw Horizontal lines
			// -------------------------------------------------------------------------------------------------------------

			DrawRectangle(0,33,720,3, GetColor(0xADAAFF));
			DrawRectangle(0,435,720,3, GetColor(0xADAAFF));
		}
		EndTextureMode();

		BeginDrawing();
		{
			ClearBackground(BLACK);

			// -------------------------------------------------------------------------------------------------------------
			// Draw final frameBuffer
			// -------------------------------------------------------------------------------------------------------------

			DrawFrameBuffer(frameBuffer);
		}
		EndDrawing();
	}

	UnloadRenderTexture(frameBuffer);
	UnloadTexture(logo);
	UnloadTexture(font_data);
	UnloadMusicStream(music);
	CloseWindow();
	return 0;
}

// -------------------------------------------------------------------------------------------------------------
// UPDATE BUFFER
// -------------------------------------------------------------------------------------------------------------

void DrawFrameBuffer(RenderTexture2D renderer) {
	float verticalScale = GetScreenHeight () / VirtualScreen.y;
	float horizontalScale = GetScreenWidth () / VirtualScreen.x;
	float scale = min (horizontalScale, verticalScale);

	DrawTexturePro (
		renderer.texture,
		(Rectangle) { 0.0f, 0.0f, (float)renderer.texture.width, (float)-renderer.texture.height },
		(Rectangle) { ( GetScreenWidth () - ( VirtualScreen.x*scale) ) * 0.5 , ( GetScreenHeight () - (VirtualScreen.y * scale) ) * 0.5, VirtualScreen.x * scale, VirtualScreen.y * scale },
		(Vector2) { 0, 0 },
		0.0f,
		WHITE
	);
}
