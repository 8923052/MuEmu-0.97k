#include "stdafx.h"
#include "Fog.h"

CFog gFog;

CFog::CFog()
{

}

CFog::~CFog()
{

}

void CFog::Init()
{
        SetByte(0x00525ADD, 1); // FogEnable = true;

        SetCompleteHook(0xE9, 0x00511B66, &this->glEnableFog);

        SetDword(0x0055233C, (DWORD)&this->glClearColorFog);
}

_declspec(naked) void CFog::glEnableFog()
{
        static DWORD jmpBack = 0x00511B98;

        _asm
        {
                Pushad;
        }

        // Night
        FogColor[0] = 0.2f;
        FogColor[1] = 0.2f;
        FogColor[2] = 0.2f;
        FogColor[3] = 1.0f;

        // Day
        //FogColor[0] = 0.5f;
        //FogColor[1] = 0.7f;
        //FogColor[2] = 0.1f;
        //FogColor[3] = 1.0f;

        glFogi(GL_FOG_MODE, GL_LINEAR);

        glFogf(GL_FOG_START, CameraDistance);

        glFogf(GL_FOG_END, CameraViewFar * 0.57f);

        glFogfv(GL_FOG_COLOR, FogColor);

        _asm
        {
                Popad;
                Jmp[jmpBack];
        }
}

void WINAPI CFog::glClearColorFog(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
        if (SceneFlag == MAIN_SCENE && FogEnable)
        {
                return glClearColor(FogColor[0], FogColor[1], FogColor[2], FogColor[3]);
        }

        return glClearColor(red, green, blue, alpha);
}