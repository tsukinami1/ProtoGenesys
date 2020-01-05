//=====================================================================================

#pragma once

#include <vector>
#include "Helpers.hpp"
#include "Thunk.hpp"

//=====================================================================================

#define MAX_CLIENTS 18
#define MAX_ENTITIES 1024
#define EF_CROUCH 0x4
#define EF_PRONE 0x8
#define EF_SPRINT 0x20000
#define EF_ZOOM 0x80000
#define ID_ASSAULTSHIELD 89
#define M_METERS 55.0f
#define M_FEET (M_METERS*3.281f)
#define M_PI_DOUBLE ((float)M_PI*2.0f)

#define ByteToFloat(a) ((float)(a)/255.0f)
#define GetSign(a) ((a)?((*(int*)&(a)>>31)|1):0)
#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))
#define AngleToShort(a) ((int)((a)*(65536/360.0f))&65535)
#define ShortToAngle(a) ((float)((a)*(360.0f/65536)))
#define AngleNormalize(a) (ShortToAngle(AngleToShort((a))))
#define DotProduct(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VectorGetSign(a) ((a)[0]=(float)GetSign((a)[0]),(a)[1]=(float)GetSign((a)[1]),(a)[2]=(float)GetSign((a)[2]))
#define VectorCopy(a,b) ((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define VectorAdd(a,b,c) ((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorSubtract(a,b,c) ((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define	VectorScale(a,b,c) ((c)[0]=(a)[0]*(b),(c)[1]=(a)[1]*(b),(c)[2]=(a)[2]*(b))
#define	VectorMA(a,b,c,d) ((d)[0]=(a)[0]+(c)[0]*(b),(d)[1]=(a)[1]+(c)[1]*(b),(d)[2]=(a)[2]+(c)[2]*(b))
#define VectorAverage(a,b,c) ((c)[0]=((a)[0]+(b)[0])/2.0f,(c)[1]=((a)[1]+(b)[1])/2.0f,(c)[2]=((a)[2]+(b)[2])/2.0f)
#define GetDistance2D(a,b) (sqrtf(powf(((a)[0]-(b)[0]),2.0f)+powf(((a)[1]-(b)[1]),2.0f)))
#define GetDistance3D(a,b) (sqrtf(powf(((a)[0]-(b)[0]),2.0f)+powf(((a)[1]-(b)[1]),2.0f)+powf(((a)[2]-(b)[2]),2.0f)))

//=====================================================================================

namespace ProtoGenesys
{
	typedef unsigned __int64 QWORD;

	typedef float Vector;
	typedef Vector Vector2[2];
	typedef Vector Vector3[3];
	typedef Vector Vector4[4];
	typedef Vector3 RGB;
	typedef Vector4 RGBA;
	/*
	//=====================================================================================
	*/
	typedef enum
	{
		BONE_HEAD,
		BONE_NECK,
		BONE_UPPER_SPINE,
		BONE_LOWER_SPINE,
		BONE_LEFT_SHOULDER,
		BONE_RIGHT_SHOULDER,
		BONE_LEFT_HIP,
		BONE_RIGHT_HIP,
		BONE_LEFT_ELBOW,
		BONE_RIGHT_ELBOW,
		BONE_LEFT_KNEE,
		BONE_RIGHT_KNEE,
		BONE_LEFT_WRIST,
		BONE_RIGHT_WRIST,
		BONE_LEFT_ANKLE,
		BONE_RIGHT_ANKLE,
		BONE_MAX
	} eBone;
	/*
	//=====================================================================================
	*/
	typedef enum
	{
		PENETRATE_TYPE_NONE,
		PENETRATE_TYPE_SMALL,
		PENETRATE_TYPE_MEDIUM,
		PENETRATE_TYPE_LARGE,
		PENETRATE_TYPE_COUNT,
	} ePenetrateType;
	/*
	//=====================================================================================
	*/
	static std::vector<std::pair<std::string, std::string>> vBones =
	{
		std::make_pair("Head", "j_head"),
		std::make_pair("Neck", "j_neck"),
		std::make_pair("Upper Spine", "j_spineupper"),
		std::make_pair("Lower Spine", "j_spinelower"),
		std::make_pair("Left Shoulder", "j_shoulder_le"),
		std::make_pair("Right Shoulder", "j_shoulder_ri"),
		std::make_pair("Left Hip", "j_hip_le"),
		std::make_pair("Right Hip", "j_hip_ri"),
		std::make_pair("Left Elbow", "j_elbow_le"),
		std::make_pair("Right Elbow", "j_elbow_ri"),
		std::make_pair("Left Knee", "j_knee_le"),
		std::make_pair("Right Knee", "j_knee_ri"),
		std::make_pair("Left Wrist", "j_wrist_le"),
		std::make_pair("Right Wrist", "j_wrist_ri"),
		std::make_pair("Left Ankle", "j_ankle_le"),
		std::make_pair("Right Ankle", "j_ankle_ri")
	};
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iServerTime;
		char _0x4[0x14];
		int iOtherFlags;
		char _0x1C[0xC];
		Vector3 vOrigin;
		Vector3 vVelocity;
		char _0x40[0xC];
		float flWeaponTime;
		char _0x50[0x3C];
		int iGravity;
		char _0x90[0x4];
		int iSpeed;
		char _0x98[0x148];
		float flZoomProgress;
		char _0x1E4[0x4];
		float flSpreadOverride;
		int iSpreadOverrideState;
		char _0x1F0[0x8];
		Vector3 vViewAngles;
		int iPlayerHeight;
		Vector3 vPlayerHeight;
		char _0x214[0x2C];
		int iHealth;
		char _0x244[0x4];
		int iMaxHealth;
		char _0x24C[0x74];
		int iSecondaryWeaponID;
		char _0x2C4[0x18];
		int iPrimaryWeaponID;
		char _0x2E0[0x124];
		int iSecondaryAmmoStock;
		int iPrimaryAmmoStock;
		char _0x40C[0x34];
		int iSecondaryAmmoClip;
		int iPrimaryAmmoClip;
		int iLethalAmmo;
		int iTacticalAmmo;
		char _0x450[0x100];
		int iPerkFlags;
	}  sPlayerState;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char _0x0[0x8];
		int iWidth;
		int iHeight;
		char _0x10[0x10];
		float flFOVX;
		float flFOVY;
		float flFOVZ;
		char _0x2C[0x4];
		float flFOV;
		Vector3 vViewOrg;
		char _0x40[0x4];
		Vector3 vViewAxis[3];
	} sRefDef;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char _0x0[0x631];
		bool bRifleBullet;
		char _0x632[0x1AE];
		float flADSSpread;
	} sWeaponDef;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iInfoValid;
		int iNextValid;
		int iClientNum;
		char szName[32];
		int iTeam;
		int iTeam2;
		int iFFATeam;
		char _0x38[0x28];
		int iRank;
		char _0x64[0x30];
		int iScore;
		char _0x98[0x48];
		char szModel[64];
		char _0x120[0x3A4];
		Vector3 vViewAngles;
		char _0x4D0[0xF4];
		int iWeaponID;
		char _0x5C8[0x1C0];
		sWeaponDef* pCurrentWeapon;
		char _0x78C[0xC];
		sWeaponDef* pPrimaryWeapon;
		char _0x79C[0x6C];
	} sClientInfo;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iType;
		int iTime;
		int iDuration;
		Vector3 vBase;
		Vector3 vDelta;
	} sTrajectory;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char _0x0[0x4];
		short wUsedForPlayerMesh;
		char _0x6[0x26];
		Vector3 vOrigin;
		Vector3 vAngles;
		char _0x38[0x11C];
		int eFlags;
		char _0x164[0x4];
		sTrajectory OldTrajectory;
		char _0x18C[0x30];
		int iPlayerPrimaryWeaponID;
		int iPlayerSecondaryWeaponID;
		char _0x1C4[0x18];
		int iClientNum;
		int iFlags;
		char _0x1E4[0x4];
		sTrajectory NewTrajectory;
		char _0x20C[0x34];
		int iWeaponID2;
		char _0x244[0x70];
		short wEntityType;
		char _0x2B6[0xA];
		int iWeaponID1;
		char _0x2C4[0xB4];
		int iAlive;
		char _0x37C[0x4];
	} sEntity;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char _0x0[0x8];
		int iServerTime;
		char _0xC[0xC];
		int iPing;
	} sSnapShot;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iClientNum;
		char _0x4[0x20];
		sSnapShot* OldSnapShot;
		sSnapShot* NewSnapShot;
		char _0x2C[0x58];
		int iPing;
		int iNewTime;
		int iTime;
		int iOldTime;
		char _0x94[0x24];
		Vector3 vOrigin;
		Vector3 vVelocity;
		char _0xD0[0x8C];
		int iMoveType;
		char _0x160[0x2C];
		int iMoveFlag;
		char _0x190[0xB8];
		int iWeaponID;
		char _0x24C[0x24];
		float flZoomProgress;
		char _0x274[0x54];
		int iHealth;
		char _0x2CC[0x47DDC];
		sPlayerState PlayerState;
		char _0x485FC[0x5294];
		sRefDef RefDef;
		char _0x4D8F8[0x1C168];
		sClientInfo Client[MAX_CLIENTS];
		char _0x72AF0[0xE06C];
		float flSpread;
		char _0x80B60[0x6BD0];
		char szGameType[4];
		char _0x87734[0x1D90C];
		sEntity Entity[MAX_ENTITIES];
	} sCG;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iServerTime;
		int iButtons[2];
		int iViewAngles[3];
		char _0x18[0xC];
		char szForwardMove;
		char szRightMove;
		char _0x26[0x16];
	} sUserCmd;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		sUserCmd UserCmd[128];
		int iCurrentCmd;

		sUserCmd* GetUserCmd(int number)
		{
			return &UserCmd[number & 0x7F];
		}
	} sClientActive;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char _0x0[0x18];
		LPSTR szDisplayName;
		char _0x1C[0x8];
	} sWeaponName;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		Vector3 vAngles;
	} sViewAngles;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		Vector3 vAngles;
	} sRecoilAngles;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		Vector3 vNormal;
		char _0xC[0x4];
		float flFraction;
		int iSFlags;
		char _0x18[0x8];
		short wHitID;
		char _0x22[0x6];
		short wPartGroup;
		char bAllSolid;
		char bStartSolid;
		char _0x2C[0x14];
	} sTrace;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		sTrace Trace;
		char _0x40[0x4];
		Vector3 vHitPos;
		char iIgnoreHitEnt;
		char _0x51[0x3];
		int iSurfaceType;
		char _0x58[0x8];
	} sBulletTraceResults;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		int iMaxEntNum;
		int iEntityNum;
		float flPower;
		int iBulletType;
		Vector3 vViewOrigin;
		Vector3 vStart;
		Vector3 vEnd;
		Vector3 vDir;
	} sBulletFireParams;
	/*
	//=====================================================================================
	*/
	typedef struct
	{
		char szName[32];
		char _0x20[0x6E];
		char szIP[4];
		char _0x92[0xB6];
	} sNetAddr;
	/*
	//=====================================================================================
	*/
	static MODULEINFO hT6mp = GetModuleInfo(NULL);
	static MODULEINFO hGameOverlayRenderer = GetModuleInfo("GameOverlayRenderer.dll");

	static bool bIsSteamVersion = hT6mp.SizeOfImage == 0x400D000;

	static DWORD_PTR dwConnectPathsDvar = 0x2366AA4;
	static DWORD_PTR dwMouseAccelerationDvar = 0x11C7834;
	static DWORD_PTR dwDrawBigFPSDvar = 0x1140A08;
	static DWORD_PTR dwMaxClientsDvar = 0x25E456C;
	static DWORD_PTR dwNoDeltaDvar = 0x11C3634;

	static DWORD_PTR dwConnectPathsException1 = bIsSteamVersion ? 0x43B6DB : 0x53367B;
	static DWORD_PTR dwConnectPathsException2 = bIsSteamVersion ? 0x4CF0C5 : 0x488335;
	static DWORD_PTR dwObituaryException = bIsSteamVersion ? 0x7A345C : 0x7A40EC;

	static DWORD_PTR dwCG = *(DWORD_PTR*)0x113F18C;
	static DWORD_PTR dwClientActive = 0x11C7D74;
	static DWORD_PTR dwViewAngles = dwCG + 0xFE64393C;
	static DWORD_PTR dwRecoilAngles = dwCG + 0xFE6438B0;
	static DWORD_PTR dwWeaponNames = *(DWORD_PTR*)0x10A7E28;
	static DWORD_PTR dwWindowHandle = 0x2B6ED88;
	static DWORD_PTR dwServerSession = 0x12A7000;
	static DWORD_PTR dwServerID = 0x11D0ACC;

	static DWORD_PTR dwSetValueForKey = bIsSteamVersion ? 0x406830 : 0x551B00;
	static DWORD_PTR dwPredictPlayerState = bIsSteamVersion ? 0x5B3C40 : 0x5B4F40;
	static DWORD_PTR dwLocalClientIsInGame = bIsSteamVersion ? 0x5922F0 : 0x402F80;
	static DWORD_PTR dwAddReliableCommand = bIsSteamVersion ? 0x5E58E0 : 0x6A1C40;
	static DWORD_PTR dwGetSpreadForWeapon = bIsSteamVersion ? 0x402A80 : 0x5B0BE0;
	static DWORD_PTR dwRegisterTag = bIsSteamVersion ? 0x479B40 : 0x5EE820;
	static DWORD_PTR dwGetDObj = bIsSteamVersion ? 0x5D2590 : 0x4DA190;
	static DWORD_PTR dwGetTagPos = bIsSteamVersion ? 0x664930 : 0x4A1210;
	static DWORD_PTR dwLocationalTrace = bIsSteamVersion ? 0x6C6C00 : 0x50B870;
	static DWORD_PTR dwBulletTrace = bIsSteamVersion ? 0x7E0170 : 0x7E0A00;
	static DWORD_PTR dwGetTraceHitType = bIsSteamVersion ? 0x4AC3D0 : 0x6A32F0;
	static DWORD_PTR dwAdvanceTrace = bIsSteamVersion ? 0x5B0F60 : 0x703090;
	static DWORD_PTR dwGetPenetrateType = bIsSteamVersion ? 0x62E290 : 0x4AC220;
	static DWORD_PTR dwGetSurfacePenetrationDepth = bIsSteamVersion ? 0x572480 : 0x622CE0;
	static DWORD_PTR dwGetWeaponDamageForRange = bIsSteamVersion ? 0x6D85B0 : 0x676160;
	static DWORD_PTR dwGetWeaponHitLocationMultiplier = bIsSteamVersion ? 0x472780 : 0x669830;
	static DWORD_PTR dwEntityIsDeployedRiotshield = bIsSteamVersion ? 0x45D4D0 : 0x501160;
	static DWORD_PTR dwHasPerk = bIsSteamVersion ? 0x42BD20 : 0x530C10;
	static DWORD_PTR dwGetWeaponName = bIsSteamVersion ? 0x458190 : 0x9502B0;
	static DWORD_PTR dwWeaponAmmoAvailable = bIsSteamVersion ? 0x557C40 : 0x6DF580;
	static DWORD_PTR dwWeaponIsAkimbo = bIsSteamVersion ? 0x6625B0 : 0x52E780;
	static DWORD_PTR dwWeaponIsVehicle = bIsSteamVersion ? 0x5B8AD0 : 0x5AE8C0;
	static DWORD_PTR dwHashSeed = bIsSteamVersion ? 0x543CE0 : 0x6AACC0;
	static DWORD_PTR dwGetWeaponDef = bIsSteamVersion ? 0x5846F0 : 0x5225F0;
	static DWORD_PTR dwRandomFloat = bIsSteamVersion ? 0x6A3490 : 0x4947E0;
	static DWORD_PTR dwSeedRandom = bIsSteamVersion ? 0x4F38A0 : 0x556180;
	static DWORD_PTR dwEvaluateTrajectory = bIsSteamVersion ? 0x47F7A0 : 0x44CE20;
	static DWORD_PTR dwSetZoomState = bIsSteamVersion ? 0x42BD00 : 0x583950;
	static DWORD_PTR dwGetUsername = bIsSteamVersion ? 0x65FDE0 : 0x4B58D0;
	static DWORD_PTR dwGetClantag = bIsSteamVersion ? 0x5ACDA0 : 0x6D2900;
	static DWORD_PTR dwGetXuidstring = bIsSteamVersion ? 0x534D60 : 0x491870;
	static DWORD_PTR dwGetIntPlayerStatInternal = bIsSteamVersion ? 0x67A430 : 0x52EE10;
	static DWORD_PTR dwInt64ToString = bIsSteamVersion ? 0x57E0F0 : 0x427820;
	static DWORD_PTR dwProcessText = bIsSteamVersion ? 0x66AFA0 : 0x546D30;

	static DWORD_PTR dwSwapchain = bIsSteamVersion ? 0x3606F94 : 0x35E5F94;
	static DWORD_PTR dwMouseInput = 0x2B69969;

	static DWORD_PTR dwTacSSCheck = 0x2B68838;
	static DWORD_PTR dwTacSSPatch = 0x2B68824;
	static DWORD_PTR dwTacSSHandle = bIsSteamVersion ? 0x3A458F4 : 0x3A248F4;

	static DWORD_PTR dwPresent = (hGameOverlayRenderer.lpBaseOfDll && hGameOverlayRenderer.SizeOfImage) ? ReadPointer(FindPattern((DWORD_PTR)hGameOverlayRenderer.lpBaseOfDll, (DWORD_PTR)hGameOverlayRenderer.SizeOfImage, "\xFF\x15\x00\x00\x00\x00\x5B\x5D\xC2\x0C\x00", "xx????xxxxx"), 0x2) : (**(DWORD_PTR**)dwSwapchain + sizeof(DWORD_PTR) * 0x8);
	/*
	//=====================================================================================
	*/
	static sClientActive* ClientActive;
	static sCG* CG = (sCG*)dwCG;
	static sWeaponName* WeaponNames = (sWeaponName*)dwWeaponNames;
	static sViewAngles* ViewAngles = (sViewAngles*)dwViewAngles;
	static sRecoilAngles* RecoilAngles = (sRecoilAngles*)dwRecoilAngles;
	static sNetAddr* NetAddr = (sNetAddr*)(dwServerSession + 0x248);
	/*
	//=====================================================================================
	*/
	inline bool LocalClientIsInGame()
	{
		return VariadicCall<bool>(dwLocalClientIsInGame, 0);
	}
	/*
	//=====================================================================================
	*/
	inline int AddReliableCommand(std::string command)
	{
		return VariadicCall<int>(dwAddReliableCommand, 0, command.c_str());
	}
	/*
	//=====================================================================================
	*/
	inline WORD RegisterTag(std::string name)
	{
		return VariadicCall<WORD>(dwRegisterTag, name.c_str());
	}
	/*
	//=====================================================================================
	*/
	inline LPVOID GetDObj(sEntity* entity)
	{
		return VariadicCall<LPVOID>(dwGetDObj, entity->iClientNum, entity->wUsedForPlayerMesh);
	}
	/*
	//=====================================================================================
	*/
	inline LPVOID GetTagPosition(sEntity* entity, WORD tag, LPVOID dobj, Vector3 position)
	{
		return VariadicCall<LPVOID>(dwGetTagPos, entity, dobj, tag, position);
	}
	/*
	//=====================================================================================
	*/
	inline bool HasPerk(int perk)
	{
		return VariadicCall<bool>(dwHasPerk, 0, CG->iClientNum, perk);
	}
	/*
	//=====================================================================================
	*/
	inline LPSTR GetWeaponName(int weapon, LPSTR name, int length)
	{
		return VariadicCall<LPSTR>(dwGetWeaponName, weapon, name, length);
	}
	/*
	//=====================================================================================
	*/
	inline int WeaponAmmoAvailable()
	{
		return VariadicCall<int>(dwWeaponAmmoAvailable, &CG->PlayerState);
	}
	/*
	//=====================================================================================
	*/
	inline bool WeaponIsAkimbo()
	{
		return VariadicCall<bool>(dwWeaponIsAkimbo, CG->iWeaponID);
	}
	/*
	//=====================================================================================
	*/
	inline bool WeaponIsVehicle()
	{
		return VariadicCall<bool>(dwWeaponIsVehicle, &CG->PlayerState);
	}
	/*
	//=====================================================================================
	*/
	inline sWeaponDef* GetWeaponDef(int weapon)
	{
		return VariadicCall<sWeaponDef*>(dwGetWeaponDef, weapon);
	}
	/*
	//=====================================================================================
	*/
	inline ePenetrateType GetPenetrateType(int weapon)
	{
		return VariadicCall<ePenetrateType>(dwGetPenetrateType, weapon);
	}
	/*
	//=====================================================================================
	*/
	inline float GetSurfacePenetrationDepth(ePenetrateType penetration, int surface)
	{
		return VariadicCall<float>(dwGetSurfacePenetrationDepth, penetration, surface);
	}
	/*
	//=====================================================================================
	*/
	inline bool EntityIsDeployedRiotshield(sEntity* entity)
	{
		return VariadicCall<bool>(dwEntityIsDeployedRiotshield, entity);
	}
	/*
	//=====================================================================================
	*/
	inline int LocationalTrace(sTrace* trace, Vector3 from, Vector3 to, int skip, int mask)
	{
		return VariadicCall<int>(dwLocationalTrace, trace, from, to, skip, mask, 0, 0);
	}
	/*
	//=====================================================================================
	*/
	inline bool AdvanceTrace(sBulletFireParams* fireparams, sBulletTraceResults* traceresults, float distance)
	{
		return VariadicCall<bool>(dwAdvanceTrace, fireparams, traceresults, distance);
	}
	/*
	//=====================================================================================
	*/
	inline WORD GetTraceHitType(sBulletTraceResults* traceresults)
	{
		return VariadicCall<WORD>(dwGetTraceHitType, traceresults);
	}
	/*
	//=====================================================================================
	*/
	inline int GetWeaponDamageForRange(int weapon, Vector3 vieworigin, Vector3 hitpos)
	{
		return VariadicCall<int>(dwGetWeaponDamageForRange, weapon, vieworigin, hitpos);
	}
	/*
	//=====================================================================================
	*/
	inline float GetWeaponHitLocationMultiplier(int partgroup, int weapon)
	{
		return VariadicCall<float>(dwGetWeaponHitLocationMultiplier, partgroup, weapon);
	}
	/*
	//=====================================================================================
	*/
	inline void GetSpreadForWeapon(int weapon, float* minimum, float* maximum)
	{
		return VariadicCall<void>(dwGetSpreadForWeapon, &CG->PlayerState, weapon, minimum, maximum);
	}
	/*
	//=====================================================================================
	*/
	inline void HashSeed(int* servertime)
	{
		return VariadicCall<void>(dwHashSeed, servertime);
	}
	/*
	//=====================================================================================
	*/
	inline float RandomFloat(int* seed)
	{
		return VariadicCall<float>(dwRandomFloat, seed);
	}
	/*
	//=====================================================================================
	*/
	inline void SeedRandom(int* seed)
	{
		return VariadicCall<void>(dwSeedRandom, seed);
	}
	/*
	//=====================================================================================
	*/
	inline void EvaluateTrajectory(sTrajectory* trajectory, int time, Vector3 result)
	{
		return VariadicCall<void>(dwEvaluateTrajectory, trajectory, time, result);
	}
	/*
	//=====================================================================================
	*/
	inline int SetZoomState(bool enable)
	{
		return VariadicCall<int>(dwSetZoomState, 0, enable);
	}
	/*
	//=====================================================================================
	*/
	inline LPSTR GetUsername()
	{
		return VariadicCall<LPSTR>(dwGetUsername, 0);
	}
	/*
	//=====================================================================================
	*/
	inline LPSTR GetClantag()
	{
		return VariadicCall<LPSTR>(dwGetClantag, 0);
	}
	/*
	//=====================================================================================
	*/
	inline LPSTR GetXuidstring()
	{
		return VariadicCall<LPSTR>(dwGetXuidstring, 0);
	}
}

//=====================================================================================