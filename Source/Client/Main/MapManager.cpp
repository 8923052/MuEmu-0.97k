#include "stdafx.h"
#include "MapManager.h"

CMapManager gMapManager;

CMapManager::CMapManager()
{
	for (int n = 0; n < MAX_MAPS; n++)
	{
		this->m_MapManager[n].MapNumber = -1;
	}

	this->Init();
}

CMapManager::~CMapManager()
{

}

void CMapManager::Init(MAP_MANAGER_INFO* info)
{
	for (int i = 0; i < MAX_MAPS; i++)
	{
		this->SetInfo(info[i]);
	}
}

void CMapManager::SetInfo(MAP_MANAGER_INFO info)
{
	if (!MAP_RANGE(info.MapNumber))
	{
		return;
	}

	this->m_MapManager[info.MapNumber] = info;
}

void CMapManager::Init()
{
	SetCompleteHook(0xE9, 0x004EF120, &this->GetMapName);

	SetCompleteHook(0xE9, 0x004EF44F, &this->GetPartyMapName);

	SetCompleteHook(0xE9, 0x00526D0C, &this->LoadMapMusic);

	SetCompleteHook(0xE9, 0x00443B45, &this->SwimAnimationStart);

	SetCompleteHook(0xE9, 0x00443172, &this->SwimAnimationStop);

	SetCompleteHook(0xE9, 0x00451AED, &this->SwimSoundPlay);

	SetCompleteHook(0xE9, 0x004582E7, &this->SwimBackItemRender);
}

/*=================================================================
			FUNCIONES
==================================================================*/

BYTE CMapManager::GetMiniMap(int map)
{
	if (!MAP_RANGE(map))
	{
		return 0;
	}

	return this->m_MapManager[map].MiniMap;
}

bool CMapManager::GetMapMovement(int map)
{
	if (!MAP_RANGE(map))
	{
		return false;
	}

	return this->m_MapManager[map].MapMovement;
}

char* CMapManager::GetMapName(int MapNumber)
{
	if (MAP_RANGE(MapNumber))
	{
		if (gMapManager.m_MapManager[MapNumber].MapNumber != -1)
		{
			return gMapManager.m_MapManager[MapNumber].MapName;
		}
		else if (MapNumber == 10)
		{
			return GlobalText[55];
		}
		else if (MapNumber >= 11 && MapNumber <= 16)
		{
			return GlobalText[56];
		}
		else if (MapNumber < 17)
		{
			return GlobalText[MapNumber + 30];
		}

		return GlobalText[MapNumber + 40];
	}
	
	return "";
}

__declspec(naked) void CMapManager::GetPartyMapName()
{
	static DWORD jmpBack = 0x004EF48D;

	_asm
	{
		Push Eax;
		Lea Ecx, gMapManager;
		Call[CMapManager::GetMapName];
		Add Esp, 4;
		Jmp[jmpBack];
	}
}

__declspec(naked) void CMapManager::LoadMapMusic()
{
	static DWORD jmpBack = 0x00527475;

	if (MAP_RANGE(World))
	{
		if (gMapManager.m_MapManager[World].MapNumber != -1)
		{
			PlayMp3(gMapManager.m_MapManager[World].SongName, FALSE);
		}
	}

	_asm
	{
		Jmp jmpBack;
	}
}

__declspec(naked) void CMapManager::SwimAnimationStart()
{
	static DWORD Jmp_Back = 0x00443B61;
	static DWORD Jmp_True = 0x00443B4A;

	_asm
	{
		Pushad;
	}

	if (MAP_RANGE(World))
	{
		if (gMapManager.m_MapManager[World].MapNumber != -1)
		{
			if (gMapManager.m_MapManager[World].SwimableMap)
			{
				goto JUMP_OK;
			}
		}
	}

	_asm
	{
		Popad;
		Jmp Jmp_Back;
	}

JUMP_OK:

	_asm
	{
		Popad;
		Jmp Jmp_True;
	}
}

__declspec(naked) void CMapManager::SwimAnimationStop()
{
	static DWORD Jmp_Back = 0x00443183;
	static DWORD Jmp_True = 0x00443177;

	_asm
	{
		Pushad;
	}

	if (MAP_RANGE(World))
	{
		if (gMapManager.m_MapManager[World].MapNumber != -1)
		{
			if (gMapManager.m_MapManager[World].SwimableMap)
			{
				goto JUMP_OK;
			}
		}
	}

	_asm
	{
		Popad;
		Jmp Jmp_Back;
	}

JUMP_OK:

	_asm
	{
		Popad;
		Jmp Jmp_True;
	}
}

__declspec(naked) void CMapManager::SwimSoundPlay()
{
	static DWORD Jmp_Back = 0x00451B0B;
	static DWORD Jmp_True = 0x00451AF2;

	_asm
	{
		Pushad;
	}

	if (MAP_RANGE(World))
	{
		if (gMapManager.m_MapManager[World].MapNumber != -1)
		{
			if (gMapManager.m_MapManager[World].SwimableMap)
			{
				goto JUMP_OK;
			}
		}
	}

	_asm
	{
		Popad;
		Jmp Jmp_Back;
	}

JUMP_OK:

	_asm
	{
		Popad;
		Jmp Jmp_True;
	}
}

__declspec(naked) void CMapManager::SwimBackItemRender()
{
	static DWORD Jmp_Back = 0x004582FC;
	static DWORD Jmp_True = 0x004582EC;

	_asm
	{
		Pushad;
	}

	if (MAP_RANGE(World))
	{
		if (gMapManager.m_MapManager[World].MapNumber != -1)
		{
			if (gMapManager.m_MapManager[World].SwimableMap)
			{
				goto JUMP_OK;
			}
		}
	}

	_asm
	{
		Popad;
		Jmp Jmp_Back;
	}

JUMP_OK:

	_asm
	{
		Popad;
		Jmp Jmp_True;
	}
}