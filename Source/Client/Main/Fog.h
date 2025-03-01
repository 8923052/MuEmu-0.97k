#pragma once

class CFog
{
public:

	CFog();

	virtual ~CFog();

	void Init();

private:

	static void glEnableFog();

	static void WINAPI glClearColorFog(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
};

extern CFog gFog;