// SA2Sonic.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IniFile.hpp"
#include "SADXModLoader.h"
#include "ModelInfo.h"
#include "AnimationFile.h"

using std::unordered_map;
using std::vector;
using std::string;

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

void NullModel(NJS_MODEL_SADX*, int, int)
{

}

void njNullAction(NJS_ACTION* action, float frame)
{
	DisplayAnimationFrame(action, frame, (QueuedModelFlagsB)0, 0, NullModel);
}

char modelnum;
char currentplayer;
NJS_MATRIX flt_1A51A3C, flt_1A51AA0, flt_1A519D0, flt_1A51A6C, flt_1A51A00, flt_1A51994, flt_1A51ADC, flt_1A51900, flt_1A51930;
unordered_map<int, NJS_OBJECT *> modelmap;
short twistamount[8] = {};
void NodeCallback(NJS_OBJECT *obj)
{
	float *v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[2] || obj == modelmap[419] || obj == modelmap[67])
	{
		if (EntityData1Ptrs[currentplayer]->Action == 2)
			njRotateX(v1, twistamount[currentplayer]);
	}
	else if (obj == modelmap[23] || obj == modelmap[88])
		memcpy(flt_1A51A3C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[24] || obj == modelmap[89])
		memcpy(flt_1A51AA0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[11] || obj == modelmap[76])
		memcpy(flt_1A519D0, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[12] || obj == modelmap[77])
		memcpy(flt_1A51A6C, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[74])
		memcpy(flt_1A51ADC, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[75])
		memcpy(flt_1A51994, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[90])
		memcpy(flt_1A51930, v1, sizeof(NJS_MATRIX));
	else if (obj == modelmap[91])
		memcpy(flt_1A51900, v1, sizeof(NJS_MATRIX));
}

void NodeCallback2(NJS_OBJECT* obj)
{
	float* v1 = _nj_current_matrix_ptr_;
	if (obj == modelmap[15])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[0]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[6]);
	}
	else if (obj == modelmap[16])
	{
		NJS_VECTOR v = { 0, 0, 0 };
		njCalcPoint(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[1]);
		v.z = 1;
		njCalcVector(v1, &v, &CharObj2Ptrs[currentplayer]->SoManyVectors[7]);
	}
}

void(__cdecl **NodeCallbackFuncPtr)(NJS_OBJECT *obj) = (decltype(NodeCallbackFuncPtr))0x3AB9908;
void DrawSonicModel(int a1, CharObj2* a2)
{
	njPushMatrix(nullptr);
	// The next three lines help to reduce floating-point rounding errors at large coordinates.
	ProjectToWorldSpace(); // set WorldMatrix to _nj_current_matrix_ptr_ * InverseViewMatrix
	Direct3D_SetWorldTransform(); // set device's world transform to WorldMatrix
	memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX)); // reset current matrix to ViewMatrix
	Direct3D_SetChunkModelRenderState();
	*NodeCallbackFuncPtr = NodeCallback;
	if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njCnkAction_Queue(a2->AnimationThing.AnimData[a1].Animation, a2->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njCnkAction(a2->AnimationThing.AnimData[a1].Animation, a2->AnimationThing.Frame);
	}
	*NodeCallbackFuncPtr = nullptr;
	if (!MetalSonicFlag && a1 != 32)
		switch (modelnum)
		{
		case 0:
			if (a1 < 134 || a1 > 145)
			{
				if ((a2->Upgrades & Upgrades_CrystalRing) && modelmap.find(26) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A3C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[26]);
				}
				if ((a2->Upgrades & Upgrades_LightShoes) && modelmap.find(14) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[14]);
					memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[13]);
				}
			}
			break;
		case 1:
			if (a1 < 134 || a1 > 145)
			{
				if ((a2->Upgrades & Upgrades_LightShoes) && modelmap.find(79) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[79]);
					memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[78]);
				}
			}
			if (modelmap.find(92) != modelmap.cend() && (a1 == 11 || a1 == 12 || a1 == 13))
			{
				NJS_OBJECT* v4 = modelmap[92];
				if (!(LevelFrameCount & 1))
				{
					v4 = modelmap[93];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51994, sizeof(NJS_MATRIX));
				DrawChunkObject(v4);
				NJS_OBJECT* v5 = modelmap[96];
				if (!(LevelFrameCount & 1))
				{
					v5 = modelmap[97];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51ADC, sizeof(NJS_MATRIX));
				DrawChunkObject(v5);
				NJS_OBJECT* v6 = modelmap[94];
				if (!(LevelFrameCount & 1))
				{
					v6 = modelmap[95];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51900, sizeof(NJS_MATRIX));
				DrawChunkObject(v6);
				NJS_OBJECT* v7 = modelmap[98];
				if (!(LevelFrameCount & 1))
				{
					v7 = modelmap[99];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51930, sizeof(NJS_MATRIX));
				DrawChunkObject(v7);
			}
			break;
		}
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
	*NodeCallbackFuncPtr = NodeCallback2;
	njPushMatrix((NJS_MATRIX_PTR)&IdentityMatrix);
	njNullAction(a2->AnimationThing.AnimData[a1].Animation, a2->AnimationThing.Frame);
	njPopMatrix(1);
	*NodeCallbackFuncPtr = nullptr;
}

void DrawSonicModelAlt(CharObj2 *a1)
{
	njPushMatrix(nullptr);
	// The next three lines help to reduce floating-point rounding errors at large coordinates.
	ProjectToWorldSpace(); // set WorldMatrix to _nj_current_matrix_ptr_ * InverseViewMatrix
	Direct3D_SetWorldTransform(); // set device's world transform to WorldMatrix
	memcpy(_nj_current_matrix_ptr_, &ViewMatrix, sizeof(NJS_MATRIX)); // reset current matrix to ViewMatrix
	Direct3D_SetChunkModelRenderState();
	*NodeCallbackFuncPtr = NodeCallback;
	if (*(int*)0x3ABD9CC)
	{
		DrawQueueDepthBias = -5952.0;
		njCnkAction_Queue(a1->AnimationThing.action, a1->AnimationThing.Frame, QueuedModelFlagsB_EnableZWrite);
		DrawQueueDepthBias = 0.0;
	}
	else
	{
		njCnkAction(a1->AnimationThing.action, a1->AnimationThing.Frame);
	}
	*NodeCallbackFuncPtr = nullptr;
	if (!MetalSonicFlag && a1->AnimationThing.Index != 32)
		switch (modelnum)
		{
		case 0:
			if (a1->AnimationThing.Index < 134 || a1->AnimationThing.Index > 145)
			{
				if ((a1->Upgrades & Upgrades_CrystalRing) && modelmap.find(26) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A3C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[26]);
				}
				if ((a1->Upgrades & Upgrades_LightShoes) && modelmap.find(14) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[14]);
					memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[13]);
				}
			}
			break;
		case 1:
			if (a1->AnimationThing.Index < 134 || a1->AnimationThing.Index > 145)
			{
				if ((a1->Upgrades & Upgrades_LightShoes) && modelmap.find(79) != modelmap.cend())
				{
					memcpy(_nj_current_matrix_ptr_, flt_1A51A6C, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[79]);
					memcpy(_nj_current_matrix_ptr_, flt_1A519D0, sizeof(NJS_MATRIX));
					DrawChunkObject(modelmap[78]);
				}
			}
			if (modelmap.find(92) != modelmap.cend() && (a1->AnimationThing.Index == 11 || a1->AnimationThing.Index == 12 || a1->AnimationThing.Index == 13))
			{
				NJS_OBJECT* v4 = modelmap[92];
				if (!(LevelFrameCount & 1))
				{
					v4 = modelmap[93];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51994, sizeof(NJS_MATRIX));
				DrawChunkObject(v4);
				NJS_OBJECT* v5 = modelmap[96];
				if (!(LevelFrameCount & 1))
				{
					v5 = modelmap[97];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51ADC, sizeof(NJS_MATRIX));
				DrawChunkObject(v5);
				NJS_OBJECT* v6 = modelmap[94];
				if (!(LevelFrameCount & 1))
				{
					v6 = modelmap[95];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51900, sizeof(NJS_MATRIX));
				DrawChunkObject(v6);
				NJS_OBJECT* v7 = modelmap[98];
				if (!(LevelFrameCount & 1))
				{
					v7 = modelmap[99];
				}
				memcpy(_nj_current_matrix_ptr_, flt_1A51930, sizeof(NJS_MATRIX));
				DrawChunkObject(v7);
			}
			break;
		}
	Direct3D_UnsetChunkModelRenderState();
	njPopMatrix(1);
	*NodeCallbackFuncPtr = NodeCallback2;
	njPushMatrix((NJS_MATRIX_PTR)&IdentityMatrix);
	njNullAction(a1->AnimationThing.action, a1->AnimationThing.Frame);
	njPopMatrix(1);
	*NodeCallbackFuncPtr = nullptr;
}

int sub_446960(int result, int a2, __int16 a3)
{
	result = (unsigned __int16)result;
	if ((signed __int16)(result - a3) > a2 || (signed __int16)(result - a3) < -a2)
	{
		if (((short)result - a3) & 0x8000)
		{
			result = (unsigned __int16)(a3 - a2);
		}
		else
		{
			result = (unsigned __int16)(a3 + a2);
		}
	}
	return result;
}

short savedyrot[8][256];
uint8_t savedyrotindex[8] = {};
FunctionPointer(void, sub_4187D0, (EntityData1 *a1), 0x4187D0);
FunctionPointer(void, sub_49F0B0, (EntityData1 *a1, struct_a3 *a2), 0x49F0B0);
FunctionPointer(void, sub_791A80, (NJS_MATRIX_PTR a1), 0x791A80);
void __cdecl Sonic_Display_r(ObjectMaster *obj)
{
	EntityData2 *data2_pp; // ebx
	EntityData1 *data1; // edi
	CharObj2 *data2; // esi
	unsigned int v4; // ebp
	Angle v5; // eax
	Angle v6; // eax
	NJS_VECTOR a2; // [esp+Ch] [ebp-Ch]

	data2_pp = (EntityData2*)obj->Data2;
	data2 = data2_pp->CharacterData;
	data1 = obj->Data1;
	if (!IsGamePaused())
	{
		savedyrot[data1->CharIndex][savedyrotindex[data1->CharIndex]++] = data1->Rotation.y;
		if (data2->PhysicsData.RollEnd > (double)data2->Speed.x)
			v5 = 0;
		else
		{
			v5 = savedyrot[data1->CharIndex][(uint8_t)(savedyrotindex[data1->CharIndex] - 3)];
			v5 = sub_446960(4 * (signed __int16)(LOWORD(v5) - LOWORD(data1->Rotation.y)), 0x1D00, 0);
		}
		v6 = twistamount[data1->CharIndex];
		unsigned short v7 = (unsigned __int16)(v5 - v6);
		if ((v7 & 0x8000u) != 0)
			v7 = -v7;
		twistamount[data1->CharIndex] = sub_446960(v5, (unsigned int)(unsigned __int16)v7 >> 2, v6);
	}
	currentplayer = data1->CharIndex;
	if (IsVisible(&data1->Position, 15.0))
	{
		Direct3D_SetZFunc(1u);
		BackupConstantAttr();
		AddConstantAttr(0, NJD_FLAG_IGNORE_SPECULAR);
		njControl3D_Backup();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
		SetMaterialAndSpriteColor_Float(1.0, 1.0, 1.0, 1.0);
		if (SuperSonicFlag)
			Direct3D_PerformLighting(4);
		else
			Direct3D_PerformLighting(2);
		if (!MetalSonicFlag && SONIC_OBJECTS[6]->sibling != *(NJS_OBJECT**)0x3C55D40)
		{
			data2->AnimationThing.field_2 = 2;
			ProcessVertexWelds(data1, data2_pp, data2);
			data2->AnimationThing.WeldInfo[0xB].ModelB = SONIC_OBJECTS[6]->sibling;
			data2->AnimationThing.field_2 = 0;
			ProcessVertexWelds(data1, data2_pp, data2);
			*(NJS_OBJECT**)0x3C55D40 = SONIC_OBJECTS[6]->sibling;
		}
		v4 = (unsigned __int16)data2->AnimationThing.Index;
		if (data2->AnimationThing.State == 2)
			v4 = (unsigned __int16)data2->AnimationThing.LastIndex;
		if (!(data1->InvulnerableTime & 2))
		{
			if (MetalSonicFlag)
				njSetTexture(&METALSONIC_TEXLIST);
			else if (modelnum == 2 || v4 < 134 || v4 > 145)
				njSetTexture(&SONIC_TEXLIST);
			else
				njSetTexture(&SUPERSONIC_TEXLIST);
			njPushMatrix(0);
			if (*((_DWORD *)data1->field_3C + 16))
				njTranslateV(0, &data1->CollisionInfo->CollisionArray->origin);
			else
				njTranslateV(0, &data1->Position);
			v5 = data1->Rotation.z;
			if (v5)
				njRotateZ(0, (unsigned __int16)v5);
			v6 = data1->Rotation.x;
			if (v6)
				njRotateX(0, (unsigned __int16)v6);
			if (data1->Rotation.y != 0x8000)
				njRotateY(0, (unsigned __int16)(-0x8000 - LOWORD(data1->Rotation.y)));
			if (v4 == 14)
			{
				if (data1->Status & (Status_Unknown1 | Status_Ground))
				{
					a2.x = 0;
					a2.y = -1;
					a2.z = 0;
					njTranslateV(0, &a2);
					njTranslate(0, 0, 5, 0);
					njRotateZ(0, 0x2000);
					njTranslate(0, 0, -5, 0);
					a2.x = 0.69999999f;
					a2.y = 1.1f;
					a2.z = 0.80000001f;
					njScaleV(0, &a2);
				}
			}
			if (*((_DWORD *)data1->field_3C + 16))
				sub_4187D0(data1);
			else
			{
				if (data2->AnimationThing.State == 2)
					DrawSonicModelAlt(data2);
				else
				{
					if (!MetalSonicFlag && (data1->Status & Status_Ball) && v4 != 145 && (data2->SonicSpinTimer & 0x11))
						v4 = 32;
					DrawSonicModel(v4, data2);
				}
				/*if (data1->Status & Status_LightDash)
				{
					Direct3D_PerformLighting(0);
					Sonic_DisplayLightDashModel(data1, data2_pp, data2);
				}*/
			}
			njPopMatrix(1u);
		}
		Direct3D_PerformLighting(0);
		ClampGlobalColorThing_Thing();
		njControl3D_Restore();
		RestoreConstantAttr();
		Direct3D_ResetZFunc();
		if (IsGamePaused())
			sub_49F0B0(data1, &data2->_struct_a3);
	}
}

#define AnimCount 147
AnimData_t SonicAnimList[AnimCount];
AnimData_t MetalAnimList[AnimCount];
int loc_49AB51 = 0x49AB51;
__declspec(naked) void SetAnimList()
{
	__asm
	{
		mov eax, [MetalSonicFlag]
		mov al, [eax]
		test al, al
		jnz metal
		mov dword ptr[ebp + 140h], offset SonicAnimList
		jmp loc_49AB51
	metal:
		mov dword ptr[ebp + 140h], offset MetalAnimList
		jmp loc_49AB51
	}
}

void __cdecl MetalSonic_AfterImage_Display_r(ObjectMaster *obj)
{
	EntityData1 *v1; // edi
	CharObj2 *v2; // esi
	Angle v3; // eax
	float r; // ST08_4
	Angle v5; // eax
	Angle v6; // eax

	v1 = obj->Data1;
	v2 = GetCharObj2(0);
	if (v2)
	{
		if (IsVisible(&v1->Position, 15.0))
		{
			BackupConstantAttr();
			AddConstantAttr(0, NJD_FLAG_USE_ALPHA);
			njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
			njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
			r = *(float*)&v1->CharIndex - 1;
			SetMaterialAndSpriteColor_Float(r, 1, 1, 1);
			njSetTexture(&METALSONIC_TEXLIST);
			njPushMatrix(0);
			njTranslateV(0, &v1->Position);
			v3 = v1->Rotation.z;
			if (v3)
			{
				njRotateZ(0, (unsigned __int16)v3);
			}
			v5 = v1->Rotation.x;
			if (v5)
			{
				njRotateX(0, (unsigned __int16)v5);
			}
			v6 = v1->Rotation.y;
			if (v6 != 0x8000)
			{
				njRotateY(0, (unsigned __int16)(-32768 - v6));
			}
			DrawSonicModel((unsigned __int16)v2->AnimationThing.Index, v2);
			njPopMatrix(1u);
			njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
			njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
			ClampGlobalColorThing_Thing();
			RestoreConstantAttr();
		}
	}
}

void __cdecl MetalSonic_AfterImage_Main_r(ObjectMaster *obj)
{
	EntityData1 *v1; // esi
	float v2; // st7

	v1 = obj->Data1;
	MetalSonic_AfterImage_Display_r(obj);
	v2 = *(float*)&v1->CharIndex - 0.1f;
	*(float*)&v1->CharIndex = v2;
	if (v2 <= 0.0)
	{
		CheckThingButThenDeleteObject(obj);
	}
}

void __cdecl MetalSonic_AfterImages_Main_r(ObjectMaster *obj)
{
	EntityData1 *v1; // eax
	_BOOL1 v2; // sf
	ObjectMaster *v3; // esi
	CharObj2 *v4; // edi
	ObjectMaster *v5; // eax
	EntityData1 *v6; // ecx
	Rotation3 *v7; // edx
	Rotation3 *v8; // esi

	v1 = obj->Data1;
	v2 = (*(int*)&v1->Object)-- - 1 < 0;
	if (v2)
	{
		CheckThingButThenDeleteObject(obj);
	}
	else
	{
		v3 = GetCharacterObject(0);
		if (v3)
		{
			v4 = GetCharObj2(0);
			if (v4)
			{
				v5 = LoadObject(LoadObj_Data1, 4, MetalSonic_AfterImage_Main_r);
				if (v5)
				{
					v6 = v5->Data1;
					v6->Position = v3->Data1->Position;
					v7 = &v3->Data1->Rotation;
					v8 = &v6->Rotation;
					v8->x = v7->x;
					v8->y = v7->y;
					v8->z = v7->z;
					*(float*)&v6->LoopData = v4->AnimationThing.Frame;
					*(float*)&v6->CharIndex = 0.5;
					v5->DisplaySub = MetalSonic_AfterImage_Display_r;
				}
			}
		}
	}
}

void ProcessAnimList(AnimData_t *animlist, const IniFile *mtnini, const string &mtnpath)
{
	char idxbuf[4];
	for (int i = 0; i < AnimCount; i++)
	{
		sprintf_s(idxbuf, "%d", i);
		if (mtnini->hasGroup(idxbuf))
		{
			const IniGroup *grp = mtnini->getGroup(idxbuf);
			AnimationFile *mtn = new AnimationFile(mtnpath + grp->getString("Animation") + ".saanim");
			animlist[i].Animation = new NJS_ACTION();
			animlist[i].Animation->object = modelmap[grp->getInt("Model")];
			animlist[i].Animation->motion = mtn->getmotion();
			animlist[i].Instance = (char)mtn->getmodelcount();
			animlist[i].Property = (char)grp->getInt("Property");
			if (animlist[i].Property >= 5) --animlist[i].Property;
			animlist[i].NextAnim = (short)grp->getInt("NextAnimation");
			animlist[i].TransitionSpeed = grp->getFloat("TransitionSpeed");
			animlist[i].AnimationSpeed = grp->getFloat("AnimationSpeed");
		}
		else
			animlist[i] = animlist[0];
	}
	delete mtnini;
}

extern "C"
{
	__declspec(dllexport) void Init(const char *path, const HelperFunctions &helperFunctions)
	{
		const string mdlpath = string(path) + "\\system\\sonicmdl\\";
		unordered_map<string, void*> labels;
		WIN32_FIND_DATAA data;
		const string srcPathSearch = mdlpath + "*.sa2mdl";
		const HANDLE hFind = FindFirstFileA(srcPathSearch.c_str(), &data);
		if (hFind == INVALID_HANDLE_VALUE)
		{
			// No files found.
			return;
		}

		do
		{
			const string modFile = mdlpath + string(data.cFileName);
			ModelInfo *mdl = new ModelInfo(modFile.c_str());
			auto map = mdl->getlabels();
			for (auto i = map->cbegin(); i != map->cend(); ++i)
				labels[i->first] = i->second;
		} while (FindNextFileA(hFind, &data) != 0);
		FindClose(hFind);
		const IniFile *mdlini = new IniFile(mdlpath + "sonicmdl.ini");
		const IniGroup *mdlgrp = mdlini->getGroup("");
		for (auto i = mdlgrp->cbegin(); i != mdlgrp->cend(); ++i)
			modelmap[std::stol(i->first)] = (NJS_OBJECT *)labels[i->second];
		delete mdlini;
		string mtnpath = string(path) + "\\system\\sonicmtn\\";
		const IniFile* cfgini = new IniFile(string(path) + "\\config.ini");
		const string mdlset = cfgini->getString("", "Model", "Sonic");
		if (!mdlset.compare("Shadow"))
		{
			modelnum = 1;
			mtnpath = string(path) + "\\system\\teriosmtn\\";
			if (helperFunctions.Version >= 6)
			{
				helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\terios.pvm");
				helperFunctions.ReplaceFile("system\\son_eff.pvm", "system\\sh_eff.pvm");
				helperFunctions.ReplaceFile("system\\supersonic.pvm", "system\\sshadow.pvm");
			}
			else
			{
				SonicPVMList[0].Name = "TERIOS";
				SonicPVMList[1].Name = "SH_EFF";
				CHAOS7_0SURFACE_TEXLISTS[4].Name = "SSHADOW";
			}
		}
		else if (!mdlset.compare("Amy"))
		{
			modelnum = 2;
			mtnpath = string(path) + "\\system\\amymtn\\";
			if (helperFunctions.Version >= 6)
			{
				helperFunctions.ReplaceFile("system\\sonic.pvm", "system\\samy.pvm");
				helperFunctions.ReplaceFile("system\\son_eff.pvm", "system\\samy_eff.pvm");
			}
			else
			{
				SonicPVMList[0].Name = "SAMY";
				SonicPVMList[1].Name = "SAMY_EFF";
			}
		}
		delete cfgini;
		ProcessAnimList(SonicAnimList, new IniFile(mtnpath + "Animation List.ini"), mtnpath);
		mtnpath = string(path) + "\\system\\metalsonicmtn\\";
		ProcessAnimList(MetalAnimList, new IniFile(mtnpath + "Animation List.ini"), mtnpath);
		WriteJump((void*)0x49AB47, SetAnimList);
		WriteData((char*)0x49ACD8, (char)0xEB);
		WriteJump(Sonic_Display, Sonic_Display_r);
		WriteJump(MetalSonic_AfterImages_Main, MetalSonic_AfterImages_Main_r);
		WriteData<2>((void*)0x4916A5, 0x90u); // disable metal's weird tilting thing
		WriteData((char*)0x49BE22, (char)0xEB);
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}