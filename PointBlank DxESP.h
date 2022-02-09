/*
Created By : Leopard
NOT FOR SHARED... SHARE ONLY... 
*/

#include "PointBlank dxColor.h"
#include "PointBlank dxDefines.h"
#include "PointBlank dxRanks.h"
#include "PointBlank dxStruct.h"
#include "PointBlank dxWeapon.h"
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#define _CRT_SECURE_NO_WARNINGS// 

#define CHAR_WIDTH  8
#define Q_COLOR_ESCAPE	'^'
#define Q_IsColorString(p)	( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE )
#define LR_WIDTH 1

#define OFS_RDATA   0x1A0610 // ?g_pRenderContext@@3PAVi3RenderContext
LPD3DXLINE pLine    = NULL;
LPD3DXFONT fName	= NULL;
LPD3DXFONT fSmall	= NULL;
LPD3DXFONT Title    = NULL;
LPD3DXFONT      g_pFont = NULL; //D3D Font
LPD3DXLINE      g_Line = NULL; //D3D Line
D3DVIEWPORT9    g_ViewPort; //ViewPort
LPDIRECT3DDEVICE9 pDevice;
D3DVIEWPORT9 Viewport;
	float ScreenCenterX = (Viewport.Width /2.0f);
	float ScreenCenterY = (Viewport.Height /2.0f);
	float ScreenBottomY = (Viewport.Height);

//DWORD * VTable;
DWORD A_GameContext,A_Player,A_My_id,A_Player_Name,A_GetCurrentHP;
DWORD dwGFX			= (DWORD)GetModuleHandle("i3GfxDx.dll");
RenderContext *pRC	= (RenderContext*)(dwGFX + OFS_RDATA);
class dxESP;

class dxESP
{
public:
	int DrawStrlen( const char *str );
	int GetTeam(char MyT);
	void DrawString(int x, int y, DWORD color, const char *fmt, ...);
	void DrawEnjoy(int x, int y, DWORD color, const char *fmt, ...);
	bool ADDXW2S(LPDIRECT3DDEVICE9 pDevice,D3DVECTOR Player,D3DVECTOR &PlayerScaled); 
	void PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font);
	void DrawRect ( long X, long Y, long W, long H, D3DCOLOR Color );
	void DrawLineRect( long X, long Y, long W, long H, D3DCOLOR Color );
	void GarisGrentong  ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health);
	void DrawLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color );
	void DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice );
	void DrawBoxESP(int x, int y, int w, int h, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice);
	void DrawBox( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice );
	void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice );
	void Healthbar(float x, float y, float Health);//(int x, int y, float Health)
	void Healthbarnew(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health);
	void Healthbarccd(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health);
	void HealthEqui(LPDIRECT3DDEVICE9 pDevice,int x, int y, float Health);
	float FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,CPlayers* pPlayer,CPlayers* pLocal);
	void GetWeapon(int iW, float x, float y);
	void dxESP::MouseMove(float x, float y);
	int __stdcall GetDistance( long x1, long x2, long y1, long y2 );
};

class GM;

class GM
{
public:
BYTE iRank; //0x0000
char _0x0001[15];
WORD iHack; //0x0010

};//Size=0x0012
class SHOWNAMEPI;
class SHOWNAMEPI
{
public:
	BYTE bShow;
	char _0x001[15];
};

class OBSERVER;
class OBSERVER
{
public:
	BYTE bObser;
	char _0x001[15];
};

int dxESP::DrawStrlen( const char *str ) {
	const char *s = str;
	int count = 0;

	while ( *s ) {
		if ( Q_IsColorString( s ) ) {
			s += 2;
		} else {
			count++;
			s++;
		}
	}

	return count;
}
float FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,CPlayers* pPlayer,CPlayers* pLocal)
{
	return sqrt((pLocal->pos.x-pPlayer->pos.x)*(pLocal->pos.x-pPlayer->pos.x) + (pLocal->pos.y-pPlayer->pos.y)*(pLocal->pos.y-pPlayer->pos.y) + (pLocal->pos.z-pPlayer->pos.z)*(pLocal->pos.z-pPlayer->pos.z));
}

int dxESP::GetTeam(char MyT)
{
	if  (MyT == 0 ||
		 MyT == 2 || 
		 MyT == 4 || 
		 MyT == 6 || 
		 MyT == 8 || 
		 MyT == 10|| 
		 MyT == 12|| 
		 MyT == 14)
			return 1;

else if (MyT == 1 ||
		 MyT == 3 || 
		 MyT == 5 || 
		 MyT == 7 || 
		 MyT == 9 || 
		 MyT == 11|| 
		 MyT == 13|| 
		 MyT == 15)
			return 2;
	return 0;
}


void dxESP::PrintText(char pString[], int x, int y, D3DCOLOR col, ID3DXFont *font)
{
    RECT FontRect = { x, y, x+500, y+50 };
    font->DrawText( NULL, pString, -1, &FontRect, DT_LEFT | DT_WORDBREAK, col);
}

void dxESP::GarisGrentong  ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, float Health)
{	
	DWORD HPcol = GREEN;  // Deklarasi Health Protection Color 
	if (Health < 85 )HPcol = WHITE; // Jika HP Di Bawah 90 = Color
	if (Health < 70 )HPcol = BLUE; // Jika HP Di Bawah 70 = Color
	if (Health < 50 )HPcol = YELLOW; // Jika HP Di Bawah 50 = Color
	if (Health < 30) HPcol = ORANGE; // Jika HP Di Bawah 30 = Color
	if (Health < 10) HPcol = RED2; // Jika HP Di Bawah 10 = Color
	if (Health = 0) HPcol  = BLACK; // Jika HP Di Bawah 10 = Color
	D3DXVECTOR2 vLine[ 2 ]; // 2 Poin
	pLine->SetAntialias( 0 ); // Set Tepi
	pLine->SetWidth( dwWidth ); // Lebar Dari Line
	pLine->Begin();
		vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array
		vLine[ 0 ][ 1 ] = Ya;
		vLine[ 1 ][ 0 ] = Xb;
		vLine[ 1 ][ 1 ] = Yb;

		vLine[ 0 ][ 0 ] = Xa; // Jadikan Point Menjadi Array
		vLine[ 0 ][ 1 ] = Ya;
		vLine[ 1 ][ 0 ] = Xb;
		vLine[ 1 ][ 1 ] = Yb;

	pLine->Draw( vLine, 2, HPcol ); // Draw Garis , Jumlah Garis , Warna Garis 
	pLine->End(); // Selesai
}
void dxESP::DrawLine ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color )
{
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( 0 );

	pLine->SetWidth( (float)dwWidth );
	pLine->Begin();

	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;

	pLine->Draw( vLine, 2, Color );
	pLine->End();
}

bool dxESP::ADDXW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
   D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	pDevice->GetViewport(&Viewport);
	Viewport.X = Viewport.Y = 0;
    Viewport.MinZ     = 0;
    Viewport.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
  
 if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
 {
     PlayerScaled.x = vScreen.x;
     PlayerScaled.y = vScreen.y ;
     PlayerScaled.z = vScreen.z;

  return true; 
 }
 return false;
}
void dxESP::DrawString(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	fSmall->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void dxESP::DrawEnjoy(int x, int y, DWORD color, const char *fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = {'\0'};
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);
	
	Title->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void dxESP::DrawRect ( long X, long Y, long W, long H, D3DCOLOR Color )
{
        D3DXVECTOR2 vLine[ 2 ];
        pLine->SetWidth( (float) W );
        pLine->SetAntialias( 0 );
        pLine->SetGLLines( 1 );
 
        pLine->SetWidth( (float) W );
        pLine->Begin();
 
                vLine[ 0 ][ 0 ] = (float)X+W/2;
                vLine[ 0 ][ 1 ] = (float)Y;
                vLine[ 1 ][ 0 ] = (float)X+W/2;
                vLine[ 1 ][ 1 ] = (float)Y+H;
 
        pLine->Draw( vLine, 2, Color );
        pLine->End();
}

void dxESP::DrawLineRect( long X, long Y, long W, long H, D3DCOLOR Color )
{
       
        DrawRect( X, Y, W, LR_WIDTH, Color );
        DrawRect( X, Y, LR_WIDTH, H, Color );
       
        DrawRect( X + W, Y, LR_WIDTH, H, Color );
        DrawRect( X, Y + H, W, LR_WIDTH, Color );
}



void dxESP::Healthbar(float x, float y, float Health)
{
	DWORD HPcol = GREEN;
	if (Health < 90 )HPcol = GREEN;
	if (Health < 50 )HPcol = YELLOW;
	if (Health < 10) HPcol = RED;
	DrawRect(x,y,Health/2,3,HPcol);
	DrawLineRect(x-1,y-1,52,5,BLACK);
}
bool KyuubiW2S(LPDIRECT3DDEVICE9 pDevice, D3DVECTOR Player,D3DVECTOR &PlayerScaled)
{
   D3DXVECTOR3 PlayerPos(Player.x,Player.y,Player.z);
	D3DXMATRIX identity;
    D3DXVECTOR3 vScreen;
	pDevice->GetViewport(&Viewport);
	Viewport.X = Viewport.Y = 0;
    Viewport.MinZ     = 0;
    Viewport.MaxZ     = 1;
	D3DXVec3Project(&vScreen, &PlayerPos, &Viewport, &pRC->pRenderData->ProjMatrix, &pRC->pRenderData->ViewMatrix, &pRC->pRenderData->World);
  
 if (vScreen.z < 1.0f && vScreen.x > 0.0f && vScreen.y > 0.0f && vScreen.x < Viewport.Width && vScreen.y < Viewport.Height)
 {
     PlayerScaled.x = vScreen.x;
     PlayerScaled.y = vScreen.y ;
     PlayerScaled.z = vScreen.z;

  return true; 
 }
 return false;
}
float dxESP::FindDistance(D3DXVECTOR3 my,D3DXVECTOR3 other,CPlayers* pPlayer,CPlayers* pLocal)
{
	return sqrt((pLocal->pos.x-pPlayer->pos.x)*(pLocal->pos.x-pPlayer->pos.x) + (pLocal->pos.y-pPlayer->pos.y)*(pLocal->pos.y-pPlayer->pos.y) + (pLocal->pos.z-pPlayer->pos.z)*(pLocal->pos.z-pPlayer->pos.z));
}
//=====================================================================================================//
void DrawLineBone ( long Xa, long Ya, long Xb, long Yb, DWORD dwWidth, D3DCOLOR Color )
{
	D3DXVECTOR2 vLine[ 2 ];
	pLine->SetAntialias( 0 );

	pLine->SetWidth( (float)dwWidth );
	pLine->Begin();

	vLine[ 0 ][ 0 ] = (float)Xa;
	vLine[ 0 ][ 1 ] = (float)Ya;
	vLine[ 1 ][ 0 ] = (float)Xb;
	vLine[ 1 ][ 1 ] = (float)Yb;

	pLine->Draw( vLine, 2, Color );
	pLine->End();
}
//=====================================================================================================//
bool GetBonePos(CGameCharaBase*m_CharaBase,D3DXVECTOR3 &outpos,int BoneIndex)
{
outpos.x = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._41;
outpos.y = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._42;
outpos.z = m_CharaBase->m_BoneContext->m_Bone[BoneIndex].m_Bone._43;
return true;
}
//=====================================================================================================//
void DrawBone(CGameCharaBase* m_CharaBase,int Start,int End,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
D3DXVECTOR3 vStart,vEnd;
D3DXVECTOR3 vvStart,vvEnd;
if(GetBonePos(m_CharaBase,vStart,Start))
{
if(GetBonePos(m_CharaBase,vEnd,End))
{
if(KyuubiW2S(pDevice,vStart,vvStart))
{
if(KyuubiW2S(pDevice,vEnd,vvEnd))
{
DrawLineBone(vvStart.x,vvStart.y,vvEnd.x,vvEnd.y,1,Color);
}
}
}
}
}
//=====================================================================================================//
void DrawSkeleton(CGameCharaBase* m_CharaBase,DWORD Color,LPDIRECT3DDEVICE9 pDevice)
{
float wraw = 2;
DrawBone(m_CharaBase,0,6,Color,pDevice);
DrawBone(m_CharaBase,6,10,Color,pDevice);
DrawBone(m_CharaBase,6,11,Color,pDevice);
DrawBone(m_CharaBase,0,12,Color,pDevice);
DrawBone(m_CharaBase,0,13,Color,pDevice);
DrawBone(m_CharaBase,12,14,Color,pDevice);
DrawBone(m_CharaBase,13,15,Color,pDevice);
DrawBone(m_CharaBase,14,8,Color,pDevice);
DrawBone(m_CharaBase,15,9,Color,pDevice);
}
void dxESP::GetWeapon(int iW, float x, float y)
{
	char *weap = new char[33];
	if		(iW < 100003100) sprintf(weap,"%s",dAssault[iW-100003000]);
	else if (iW < 200004100) sprintf(weap,"%s",dSMG[iW-200004000]);
	else if (iW < 300005100) sprintf(weap,"%s",dSniper[iW-300005000]);
	else if (iW < 400006100) sprintf(weap,"%s",dShotgun[iW-400006000]);
	PrintText(weap,x,y,WHITE,fSmall);
}

void dxESP::MouseMove(float x, float y)
{
	float ScreenX = (Viewport.Width / 2.0f);
	float ScreenY = (Viewport.Height / 2.0f);
	x -= ScreenX;
	y -= ScreenY;
	INPUT Input;
	memset(&Input, 0, sizeof(Input));
	Input.type	= INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	Input.mi.dx = (long) x;
	Input.mi.dy = (long) y;
	::SendInput(1,&Input,sizeof(INPUT));
}

int __stdcall dxESP::GetDistance( long x1, long x2, long y1, long y2 )
{
	long ResA = (x1 - x2) * (x1 - x2);

	long ResB = (y1 - y2) * (y1 - y2);

	double ResC = (double)(ResA + ResB);

	return (int)sqrt( ResC );
}

void FillRGB3( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;

D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
void dxESP::DrawBox( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
FillRGB3( x, (y + h - px), w, px, BorderColor, pDevice );
FillRGB3( x, y, px, h, BorderColor, pDevice );
FillRGB3( x, y, w, px, BorderColor, pDevice );
FillRGB3( (x + w - px), y, px, h, BorderColor, pDevice );
}

void dxESP::FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
 
D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}
 
void dxESP::DrawBorder( int x, int y, int w, int h, int px, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
FillRGB( x, (y + h - px), w, px, BorderColor, pDevice );
FillRGB( x, y, px, h, BorderColor, pDevice );
FillRGB( x, y, w, px, BorderColor, pDevice );
FillRGB( (x + w - px), y, px, h, BorderColor, pDevice );
}
 
void dxESP::DrawBoxESP( int x, int y, int w, int h, D3DCOLOR BorderColor, IDirect3DDevice9* pDevice )
{
DrawBorder( x, y, w, h, 1, BorderColor, pDevice );
} 

void dxESP::Healthbarnew(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health)
{
DWORD HPcol = GREEN;
if (Health < 90 )HPcol = BLUE;
if (Health < 80 )HPcol = ORANGE;
if (Health < 50 )HPcol = ORANGE;
if (Health < 40 )HPcol = YELLOW;
if (Health < 30) HPcol = RED;
if (Health < 10) HPcol = RED;
DrawBorder(x-1,y-1,52,5,1,BLACK,pDevice);
FillRGB(x,y,Health/2,3,HPcol,pDevice );
}
void dxESP::Healthbarccd(LPDIRECT3DDEVICE9 pDevice,float x, float y, float Health)
{
DWORD HPcol = GREEN;
	if (Health < 90)HPcol = YELLOW;
	if (Health < 80) HPcol = ORANGE;
	if (Health < 40) HPcol = RED;
	if (Health < 10) HPcol = BLACK;
	//DrawString(x-35, y-4, HPcol, "HP: %0.0f", Health);
	DrawBox(x-1,y-1,27,6,BLACK,BLACK,pDevice );
	FillRGB(x,y,Health/4,4,HPcol,pDevice );
}
//-------------------------W2S----------------------------------------------------------//
void FillRGB( int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice )
{
if( w < 0 )w = 1;
if( h < 0 )h = 1;
if( x < 0 )x = 1;
if( y < 0 )y = 1;
 
D3DRECT rec = { x, y, x + w, y + h };
pDevice->Clear( 1, &rec, D3DCLEAR_TARGET, color, 0, 0 );
}

void dxESP::HealthEqui(LPDIRECT3DDEVICE9 pDevice,int x, int y, float Health)
{
const int SizeY[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
const D3DCOLOR colours[] = { RED, RED, RED, RED, ORANGE, ORANGE, ORANGE, ORANGE, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLUE, BLUE }; // this is our order
int boxSizeX = 2; // you can fiddle with the box size and gap between them
int boxSizeY = 6;
int boxGap = 1;
for ( int i = 0 ; i < 20; i++ )
{
if ( Health > ( 5 * i ) )
FillRGB(x,y, boxSizeX, SizeY[i],colours[i],pDevice);
else
FillRGB(x,y, boxSizeX, SizeY[i],GREY,pDevice);
//DrawBorder(x-1,y-1,50,6,1,BLACK,npDevice);
x = x + boxSizeX+ boxGap; // will move to next tile 1 unit to the right
}
}
