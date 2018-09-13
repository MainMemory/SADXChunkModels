// ChunkTest.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SADXModLoader.h"
#include "E:\Documents\GitHub\sadx-mod-loader\libmodutils\ModelInfo.h"

FastcallFunctionPointer(void, sub_7917F0, (Sint32 *a1, Sint16 *a2), 0x7917F0);
void DrawChunkModel(NJS_CNK_MODEL *model)
{
	sub_7917F0(model->vlist, model->plist);
}

void njCnkAction_Queue(NJS_ACTION *action, float frame, QueuedModelFlagsB flags)
{
	DisplayAnimationFrame(action, frame, flags, 0, (void(__cdecl *)(NJS_MODEL_SADX *, int, int))DrawChunkModel);
}

void njCnkAction(NJS_ACTION *action, float frame)
{
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0, (void(__cdecl *)(NJS_MODEL_SADX *, int, int))DrawChunkModel);
}

// void __usercall(NJS_MOTION *a1@<eax>, NJS_OBJECT *a2@<edi>, float frameNumber, int a4, int a5, void (__cdecl *a6)(NJS_MODEL_SADX *, int, int))
static const void *const sub_4052F0Ptr = (void*)0x4052F0;
static inline void sub_4052F0(NJS_MOTION *a1, NJS_OBJECT *a2, float frameNumber, int a4, int a5, void(__cdecl *a6)(NJS_MODEL_SADX *, int, int))
{
	__asm
	{
		push[a6]
		push[a5]
		push[a4]
		push[frameNumber]
		mov edi, [a2]
		mov eax, [a1]
		call sub_4052F0Ptr
		add esp, 16
	}
}

void njCnkAction_QueueObject(NJS_OBJECT *a1, NJS_MOTION *a2, float a3)
{
	sub_4052F0(a2, a1, a3, 0, 0, (void(__cdecl *)(NJS_MODEL_SADX *, int, int))DrawChunkModel);
}

NJS_OBJECT *sonicmodel;
void DrawSonicModel_i(int a1, CharObj2 *a2)
{
	int v2; // eax
	NJS_OBJECT *v3; // eax
	NJS_ACTION *v4; // ecx
	int v5; // edi

	v2 = a1;
	if (MetalSonicFlag)
	{
		v5 = v2 * 16;
		v4 = a2->AnimationThing.AnimData[v2].Animation;
		v3 = v4->object;
		if (v4->object == *SONIC_OBJECTS)
		{
			if (v4 == *SONIC_ACTIONS)
			{
				njSetTexture(&METALSONIC_TEXLIST);
				njAction_QueueObject(SONIC_OBJECTS[68], SONIC_MOTIONS[1], a2->AnimationThing.Frame);
			}
			else
			{
				njSetTexture(&METALSONIC_TEXLIST);
				njAction_QueueObject(
					SONIC_OBJECTS[68],
					(*(NJS_ACTION **)((char *)&a2->AnimationThing.AnimData->Animation + v5))->motion,
					a2->AnimationThing.Frame);
			}
		}
		else if (v3 == SONIC_OBJECTS[66])
		{
			njSetTexture(&METALSONIC_TEXLIST);
			njAction_QueueObject(
				SONIC_OBJECTS[69],
				(*(NJS_ACTION **)((char *)&a2->AnimationThing.AnimData->Animation + v5))->motion,
				a2->AnimationThing.Frame);
		}
		else if (v3 == SONIC_OBJECTS[67])
		{
			njSetTexture(&METALSONIC_TEXLIST);
			njAction_QueueObject(
				SONIC_OBJECTS[70],
				(*(NJS_ACTION **)((char *)&a2->AnimationThing.AnimData->Animation + v5))->motion,
				a2->AnimationThing.Frame);
		}
		else
		{
			njAction(v4, a2->AnimationThing.Frame);
		}
	}
	else if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njAction_Queue(a2->AnimationThing.AnimData[v2].Animation, a2->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njAction(a2->AnimationThing.AnimData[v2].Animation, a2->AnimationThing.Frame);
	}
}

static void __declspec(naked) DrawSonicModel()
{
	__asm
	{
		push esi // a2
		push eax // a1

		// Call your __cdecl function here:
		call DrawSonicModel_i

		pop eax // a1
		pop esi // a2
		retn
	}
}

void DrawSonicModelAlt_i(CharObj2 *a1)
{
	NJS_OBJECT *v1; // eax
	NJS_ACTION *v2; // ecx

	if (MetalSonicFlag)
	{
		v2 = a1->AnimationThing.action;
		v1 = v2->object;
		if (v2->object == *SONIC_OBJECTS)
		{
			if (v2 == *SONIC_ACTIONS)
			{
				njSetTexture(&METALSONIC_TEXLIST);
				njAction_QueueObject(SONIC_OBJECTS[68], SONIC_MOTIONS[1], a1->AnimationThing.Frame);
			}
			else
			{
				njSetTexture(&METALSONIC_TEXLIST);
				njAction_QueueObject(SONIC_OBJECTS[68], a1->AnimationThing.action->motion, a1->AnimationThing.Frame);
			}
		}
		else if (v1 == SONIC_OBJECTS[66])
		{
			njSetTexture(&METALSONIC_TEXLIST);
			njAction_QueueObject(SONIC_OBJECTS[69], a1->AnimationThing.action->motion, a1->AnimationThing.Frame);
		}
		else if (v1 == SONIC_OBJECTS[67])
		{
			njSetTexture(&METALSONIC_TEXLIST);
			njAction_QueueObject(SONIC_OBJECTS[70], a1->AnimationThing.action->motion, a1->AnimationThing.Frame);
		}
		else
		{
			njAction(v2, a1->AnimationThing.Frame);
		}
	}
	else if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njAction_Queue(a1->AnimationThing.action, a1->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njAction(a1->AnimationThing.action, a1->AnimationThing.Frame);
	}
}

static void __declspec(naked) DrawSonicModelAlt()
{
	__asm
	{
		push esi // a1

		// Call your __cdecl function here:
		call DrawSonicModelAlt_i

		pop esi // a1
		retn
	}
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		sonicmodel = (new ModelInfo("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Sonic Adventure 2\\models\\sonicmdl\\0.sa2mdl"))->getmodel();
		WriteJump((void*)0x494400, DrawSonicModel);
		WriteJump((void*)0x494570, DrawSonicModelAlt);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}