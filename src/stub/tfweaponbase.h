#ifndef _INCLUDE_SIGSEGV_STUB_TFWEAPONBASE_H_
#define _INCLUDE_SIGSEGV_STUB_TFWEAPONBASE_H_


#include "stub/misc.h"
#include "stub/tfplayer.h"


class CBaseCombatWeapon : public CEconEntity
{
public:
	CBaseCombatCharacter *GetOwner() const { return this->m_hOwner; }
	
	bool IsMeleeWeapon() const { return ft_IsMeleeWeapon(this); }
	
	DECL_SENDPROP(float,                         m_flNextPrimaryAttack);
	DECL_SENDPROP(float,                         m_flNextSecondaryAttack);
	DECL_SENDPROP(float,                         m_flTimeWeaponIdle);
	DECL_SENDPROP(int,                           m_iState);
	DECL_SENDPROP(int,                           m_iPrimaryAmmoType);
	DECL_SENDPROP(int,                           m_iSecondaryAmmoType);
	DECL_SENDPROP(int,                           m_iClip1);
	DECL_SENDPROP(int,                           m_iClip2);
	
private:
	DECL_SENDPROP(CHandle<CBaseCombatCharacter>, m_hOwner);
	
	static MemberFuncThunk<const CBaseCombatWeapon *, bool> ft_IsMeleeWeapon;
};

class CTFWeaponBase : public CBaseCombatWeapon
{
public:
	CTFPlayer *GetTFPlayerOwner() const { return ToTFPlayer(this->GetOwner()); }
	
	int GetWeaponID() const      { return vt_GetWeaponID     (this); }
	int GetPenetrateType() const { return vt_GetPenetrateType(this); }
	
private:
	static MemberVFuncThunk<const CTFWeaponBase *, int> vt_GetWeaponID;
	static MemberVFuncThunk<const CTFWeaponBase *, int> vt_GetPenetrateType;
};

class CTFWeaponBaseMelee : public CTFWeaponBase
{
public:
	int GetSwingRange() { return vt_GetSwingRange(this); }
	
private:
	static MemberVFuncThunk<CTFWeaponBaseMelee *, int> vt_GetSwingRange;
};

class CTFWeaponBaseGun : public CTFWeaponBase {};

class CTFSniperRifle : public CTFWeaponBaseGun {};

class CTFBonesaw : public CTFWeaponBaseMelee {};

class CTFBuffItem : public CTFWeaponBaseMelee {};

class CTFLunchBox : public CTFWeaponBase {};
class CTFLunchBox_Drink : public CTFLunchBox {};

class CWeaponMedigun : public CTFWeaponBase
{
public:
	CBaseEntity *GetHealTarget() const { return this->m_hHealingTarget; }
	
private:
	DECL_SENDPROP(CHandle<CBaseEntity>, m_hHealingTarget);
};

class CTFFlameThrower : public CTFWeaponBaseGun {};

class CTFWeaponBuilder : public CTFWeaponBase {};
class CTFWeaponSapper : public CTFWeaponBuilder {};


bool WeaponID_IsSniperRifle(int id);
bool WeaponID_IsSniperRifleOrBow(int id);


#endif