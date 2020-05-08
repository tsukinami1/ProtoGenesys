//=====================================================================================

#include "../../StdAfx.hpp"

//=====================================================================================

namespace ProtoGenesys
{
	cAutowall _autoWall;

	float cAutowall::Autowall(sEntity* entity, Vector3 start, Vector3 end, short hitloc)
	{
		int iClientNum = CG->iClientNum;
		sEntity* pEntity = &CG->Entity[iClientNum];
		int iWeaponID = pEntity->NextEntityState.iWeaponID;
		sWeaponDef* pWeaponDef = GetWeaponDef(iWeaponID);
		ePenetrateType iPenetrateType = pWeaponDef->iPenetrateType;
		eWeaponType iWeaponType = pWeaponDef->iWeaponType;

		sBulletFireParams FP_Enter;
		ZeroMemory(&FP_Enter, sizeof(sBulletFireParams));

		sBulletTraceResults TR_Enter;
		ZeroMemory(&TR_Enter, sizeof(sBulletTraceResults));

		sBulletFireParams FP_Exit;
		ZeroMemory(&FP_Exit, sizeof(sBulletFireParams));

		sBulletTraceResults TR_Exit;
		ZeroMemory(&TR_Exit, sizeof(sBulletTraceResults));

		FP_Enter.iMaxEntNum = 1022;
		FP_Enter.iEntityNum = iClientNum;
		FP_Enter.flPower = 1.0f;
		FP_Enter.iBulletType = (pWeaponDef->bRifleBullet != 0) + 1;

		VectorCopy(start, FP_Enter.vViewOrigin);
		VectorCopy(start, FP_Enter.vStart);
		VectorCopy(end, FP_Enter.vEnd);

		VectorSubtract(end, start, FP_Enter.vDir);
		float flLength = VectorLength(FP_Enter.vDir);
		_mathematics.VectorNormalize(FP_Enter.vDir);

		bool bEnterHit = BulletTrace(&TR_Enter, &FP_Enter, pEntity, TRACE_HITTYPE_NONE);

		if (bEnterHit)
		{
			if (iPenetrateType <= PENETRATE_TYPE_NONE)
				return 0.0f;

			if (HitRiotshield(&TR_Enter))
				return 0.0f;

			if (_profiler.gAntiTeamKill->Current.bValue)
				if (HitTeammate(&TR_Enter))
					return 0.0f;

			if (GetTraceHitType(&TR_Enter) == entity->NextEntityState.iEntityNum)
				return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);

			float flEnterDepth = 0.0f;
			float flExitDepth = 0.0f;
			float flSurfaceDepth = 0.0f;

			Vector3 vHitPos = { 0.0f };
			Vector3 vTemp = { 0.0f };

			for (int iSurfaceCount = 0; bEnterHit && iSurfaceCount < ((sDvar*)dwPenetrationCount)->Current.iValue; ++iSurfaceCount)
			{
				flEnterDepth = GetSurfacePenetrationDepth(iPenetrateType, TR_Enter.iSurfaceType);

				if (HasPerk(6))
					flEnterDepth *= ((sDvar*)dwPenetrationMultiplier)->Current.flValue;

				if (flEnterDepth <= 0.0)
					return 0.0f;

				VectorCopy(TR_Enter.vHitPos, vHitPos);
				VectorSubtract(vHitPos, FP_Enter.vStart, vTemp);

				if (VectorLength(vTemp) >= flLength)
					return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);

				if (!AdvanceTrace(&FP_Enter, &TR_Enter, 0.13500001f))
					return 0.0f;

				bEnterHit = BulletTrace(&TR_Enter, &FP_Enter, pEntity, TR_Enter.iSurfaceType);

				if (HitRiotshield(&TR_Enter))
					return 0.0f;

				if (_profiler.gAntiTeamKill->Current.bValue)
					if (HitTeammate(&TR_Enter))
						return 0.0f;

				CopyMemory(&FP_Exit, &FP_Enter, sizeof(sBulletFireParams));
				VectorScale(FP_Enter.vDir, -1.0f, FP_Exit.vDir);

				VectorCopy(FP_Enter.vEnd, FP_Exit.vStart);
				VectorMA(vHitPos, 0.0099999998f, FP_Exit.vDir, FP_Exit.vEnd);

				CopyMemory(&TR_Exit, &TR_Enter, sizeof(sBulletTraceResults));
				VectorScale(TR_Exit.Trace.vNormal, -1.0f, TR_Exit.Trace.vNormal);

				if (bEnterHit)
					AdvanceTrace(&FP_Exit, &TR_Exit, 0.0099999998f);

				bool bExitHit = BulletTrace(&TR_Exit, &FP_Exit, pEntity, TR_Exit.iSurfaceType);
				bool bStaticModel = bExitHit && TR_Exit.Trace.bAllSolid || TR_Enter.Trace.bStartSolid && TR_Exit.Trace.bStartSolid;

				if (HitRiotshield(&TR_Exit))
					return 0.0f;

				if (_profiler.gAntiTeamKill->Current.bValue)
					if (HitTeammate(&TR_Exit))
						return 0.0f;

				if (bExitHit || bStaticModel)
				{
					if (bStaticModel)
						flSurfaceDepth = _mathematics.CalculateDistance(FP_Exit.vEnd, FP_Exit.vStart);
					else
						flSurfaceDepth = _mathematics.CalculateDistance(vHitPos, TR_Exit.vHitPos);

					flSurfaceDepth = max(flSurfaceDepth, 1.0f);

					if (bExitHit)
					{
						flExitDepth = GetSurfacePenetrationDepth(iPenetrateType, TR_Exit.iSurfaceType);

						if (HasPerk(6))
							flExitDepth *= ((sDvar*)dwPenetrationMultiplier)->Current.flValue;

						flEnterDepth = min(flEnterDepth, flExitDepth);

						if (flEnterDepth <= 0.0f)
							return 0.0f;
					}

					FP_Enter.flPower -= flSurfaceDepth / flEnterDepth;

					if (FP_Enter.flPower <= 0.0f)
						return 0.0f;

					if (!bStaticModel && iWeaponType == WEAPTYPE_BULLET)
					{
						Vector3 vLength;

						VectorSubtract(TR_Exit.vHitPos, TR_Enter.vHitPos, vLength);

						float flLength = DotProduct(vLength, vLength);

						if (flLength > ((sDvar*)dwPenetrationMinFxDist)->Current.flValue * ((sDvar*)dwPenetrationMinFxDist)->Current.flValue)
						{
							if (!bEnterHit)
								return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);
						}

						if (GetTraceHitType(&TR_Exit) == entity->NextEntityState.iEntityNum)
							return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);
					}
				}

				else if (!bEnterHit)
					return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);

				if (GetTraceHitType(&TR_Enter) == entity->NextEntityState.iEntityNum)
					return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);
			}

			return 0.0f;
		}

		return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);
	}
	/*
	//=====================================================================================
	*/
	float cAutowall::TraceBullet(sEntity* entity, Vector3 start, Vector3 end, short hitloc)
	{
		int iClientNum = CG->iClientNum;
		sEntity* pEntity = &CG->Entity[iClientNum];
		int iWeaponID = pEntity->NextEntityState.iWeaponID;
		sWeaponDef* pWeaponDef = GetWeaponDef(iWeaponID);

		sBulletFireParams FP_Enter;
		ZeroMemory(&FP_Enter, sizeof(sBulletFireParams));

		sBulletTraceResults TR_Enter;
		ZeroMemory(&TR_Enter, sizeof(sBulletTraceResults));

		FP_Enter.iMaxEntNum = 1022;
		FP_Enter.iEntityNum = iClientNum;
		FP_Enter.flPower = 1.0f;
		FP_Enter.iBulletType = (pWeaponDef->bRifleBullet != 0) + 1;

		VectorCopy(start, FP_Enter.vViewOrigin);
		VectorCopy(start, FP_Enter.vStart);
		VectorCopy(end, FP_Enter.vEnd);

		VectorSubtract(end, start, FP_Enter.vDir);
		_mathematics.VectorNormalize(FP_Enter.vDir);

		BulletTrace(&TR_Enter, &FP_Enter, pEntity, TRACE_HITTYPE_NONE);

		if (HitRiotshield(&TR_Enter))
			return 0.0f;

		if (GetTraceHitType(&TR_Enter) == entity->NextEntityState.iEntityNum || TR_Enter.Trace.flFraction == 1.0f)
			return GetRemainingDamage(&FP_Enter, &TR_Enter, hitloc, iWeaponID);

		return 0.0f;
	}
	/*
	//=====================================================================================
	*/
	bool cAutowall::TraceLine(sEntity* entity, Vector3 start, Vector3 end)
	{
		Vector3 vStart, vEnd;

		VectorCopy(start, vStart);
		VectorCopy(end, vEnd);

		sTrace Trace;
		ZeroMemory(&Trace, sizeof(sTrace));

		LocationalTrace(&Trace, vStart, vEnd, CG->iClientNum, 0x803003);

		return (Trace.wHitID == entity->NextEntityState.iEntityNum || Trace.flFraction == 1.0f);
	}
	/*
	//=====================================================================================
	*/
	bool cAutowall::BulletTrace(sBulletTraceResults* traceresults, sBulletFireParams* fireparams, sEntity* attacker, int surfacetype)
	{
		bool bResult = false;
		__declspec(align(16)) char szSave[512];
		_fxsave(szSave);
		__asm
		{
			push 0
			push surfacetype
			push attacker
			push fireparams
			push 0
			mov esi, traceresults
			call dwBulletTrace
			mov bResult, al
			add esp, 14h
		}
		_fxrstor(szSave);
		return bResult;
	}
	/*
	//=====================================================================================
	*/
	float cAutowall::GetRemainingDamage(sBulletFireParams* fireparams, sBulletTraceResults* traceresults, short partgroup, int weapon)
	{
		float flDamage = 0.0f;
		Vector3 vHitPos, vStart;

		if (fireparams->flPower > 0.0f)
		{
			VectorCopy(traceresults->vHitPos, vHitPos);
			VectorCopy(fireparams->vStart, vStart);

			flDamage = (float)GetWeaponDamageForRange(weapon, vStart, vHitPos) * fireparams->flPower;
			flDamage = GetWeaponHitLocationMultiplier(partgroup, weapon) * flDamage;

			if (flDamage <= 0.0f)
				flDamage = 1.0f;
		}

		return flDamage;
	}
	/*
	//=====================================================================================
	*/
	bool cAutowall::HitRiotshield(sBulletTraceResults* traceresults)
	{
		if (traceresults->iIgnoreHitEnt)
			return false;

		if (traceresults->Trace.wPartGroup == 20)
			return true;

		WORD wHitID = GetTraceHitType(traceresults);

		if (wHitID != 1022)
		{
			if (EntityIsDeployedRiotshield(&CG->Entity[wHitID]))
			{
				return true;
			}
		}

		return false;
	}
	/*
	//=====================================================================================
	*/
	bool cAutowall::HitTeammate(sBulletTraceResults* traceresults)
	{
		WORD wHitID = GetTraceHitType(traceresults);

		if (wHitID < MAX_CLIENTS)
		{
			if (EntityIsTeammate(&CG->Entity[wHitID]))
			{
				return true;
			}
		}

		return false;
	}
}

//=====================================================================================