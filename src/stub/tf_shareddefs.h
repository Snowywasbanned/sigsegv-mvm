#ifndef _INCLUDE_SIGSEGV_STUB_TF_SHAREDDEFS_H_
#define _INCLUDE_SIGSEGV_STUB_TF_SHAREDDEFS_H_


#include "stub/baseentity.h"


enum
{
	TF_TEAM_RED  = 2,
	TF_TEAM_BLUE = 3,
	
	TF_TEAM_PVE_DEFENDERS = TF_TEAM_RED,
	TF_TEAM_PVE_INVADERS  = TF_TEAM_BLUE,
};

enum
{
	TF_WEAPON_NONE = 0,
	TF_WEAPON_BAT,
	TF_WEAPON_BAT_WOOD,
	TF_WEAPON_BOTTLE,
	TF_WEAPON_FIREAXE,
	TF_WEAPON_CLUB,
	TF_WEAPON_CROWBAR,
	TF_WEAPON_KNIFE,
	TF_WEAPON_FISTS,
	TF_WEAPON_SHOVEL,
	TF_WEAPON_WRENCH,
	TF_WEAPON_BONESAW,
	TF_WEAPON_SHOTGUN_PRIMARY,
	TF_WEAPON_SHOTGUN_SOLDIER,
	TF_WEAPON_SHOTGUN_HWG,
	TF_WEAPON_SHOTGUN_PYRO,
	TF_WEAPON_SCATTERGUN,
	TF_WEAPON_SNIPERRIFLE,
	TF_WEAPON_MINIGUN,
	TF_WEAPON_SMG,
	TF_WEAPON_SYRINGEGUN_MEDIC,
	TF_WEAPON_TRANQ,
	TF_WEAPON_ROCKETLAUNCHER,
	TF_WEAPON_GRENADELAUNCHER,
	TF_WEAPON_PIPEBOMBLAUNCHER,
	TF_WEAPON_FLAMETHROWER,
	TF_WEAPON_GRENADE_NORMAL,
	TF_WEAPON_GRENADE_CONCUSSION,
	TF_WEAPON_GRENADE_NAIL,
	TF_WEAPON_GRENADE_MIRV,
	TF_WEAPON_GRENADE_MIRV_DEMOMAN,
	TF_WEAPON_GRENADE_NAPALM,
	TF_WEAPON_GRENADE_GAS,
	TF_WEAPON_GRENADE_EMP,
	TF_WEAPON_GRENADE_CALTROP,
	TF_WEAPON_GRENADE_PIPEBOMB,
	TF_WEAPON_GRENADE_SMOKE_BOMB,
	TF_WEAPON_GRENADE_HEAL,
	TF_WEAPON_GRENADE_STUNBALL,
	TF_WEAPON_GRENADE_JAR,
	TF_WEAPON_GRENADE_JAR_MILK,
	TF_WEAPON_PISTOL,
	TF_WEAPON_PISTOL_SCOUT,
	TF_WEAPON_REVOLVER,
	TF_WEAPON_NAILGUN,
	TF_WEAPON_PDA,
	TF_WEAPON_PDA_ENGINEER_BUILD,
	TF_WEAPON_PDA_ENGINEER_DESTROY,
	TF_WEAPON_PDA_SPY,
	TF_WEAPON_BUILDER,
	TF_WEAPON_MEDIGUN,
	TF_WEAPON_GRENADE_MIRVBOMB,
	TF_WEAPON_FLAMETHROWER_ROCKET,
	TF_WEAPON_GRENADE_DEMOMAN,
	TF_WEAPON_SENTRY_BULLET,
	TF_WEAPON_SENTRY_ROCKET,
	TF_WEAPON_DISPENSER,
	TF_WEAPON_INVIS,
	TF_WEAPON_FLAREGUN,
	TF_WEAPON_LUNCHBOX,
	TF_WEAPON_JAR,
	TF_WEAPON_COMPOUND_BOW,
	TF_WEAPON_BUFF_ITEM,
	TF_WEAPON_PUMPKIN_BOMB,
	TF_WEAPON_SWORD,
	TF_WEAPON_DIRECTHIT,
	TF_WEAPON_LIFELINE,
	TF_WEAPON_LASER_POINTER,
	TF_WEAPON_DISPENSER_GUN,
	TF_WEAPON_SENTRY_REVENGE,
	TF_WEAPON_JAR_MILK,
	TF_WEAPON_HANDGUN_SCOUT_PRIMARY,
	TF_WEAPON_BAT_FISH,
	TF_WEAPON_CROSSBOW,
	TF_WEAPON_STICKBOMB,
	TF_WEAPON_HANDGUN_SCOUT_SEC,
	TF_WEAPON_SODA_POPPER,
	TF_WEAPON_SNIPERRIFLE_DECAP,
	TF_WEAPON_RAYGUN,
	TF_WEAPON_PARTICLE_CANNON,
	TF_WEAPON_MECHANICAL_ARM,
	TF_WEAPON_DRG_POMSON,
	TF_WEAPON_BAT_GIFTWRAP,
	TF_WEAPON_GRENADE_ORNAMENT,
	TF_WEAPON_RAYGUN_REVENGE,
	TF_WEAPON_PEP_BRAWLER_BLASTER,
	TF_WEAPON_CLEAVER,
	TF_WEAPON_GRENADE_CLEAVER,
	TF_WEAPON_STICKY_BALL_LAUNCHER,
	TF_WEAPON_GRENADE_STICKY_BALL,
	TF_WEAPON_SHOTGUN_BUILDING_RESCUE,
	TF_WEAPON_CANNON,
	TF_WEAPON_THROWABLE,
	TF_WEAPON_GRENADE_THROWABLE,
	TF_WEAPON_PDA_SPY_BUILD,
	TF_WEAPON_GRENADE_WATERBALLOON,
	TF_WEAPON_HARVESTER_SAW,
	TF_WEAPON_SPELLBOOK,
	TF_WEAPON_SPELLBOOK_PROJECTILE,
	TF_WEAPON_SNIPERRIFLE_CLASSIC,
	TF_WEAPON_PARACHUTE,
	TF_WEAPON_GRAPPLINGHOOK,
	TF_WEAPON_PASSTIME_GUN,
	TF_WEAPON_CHARGED_SMG,
};


enum ETFDmgCustom
{
	TF_DMG_CUSTOM_NONE = 0,
	TF_DMG_CUSTOM_HEADSHOT,
	TF_DMG_CUSTOM_BACKSTAB,
	TF_DMG_CUSTOM_BURNING,
	TF_DMG_WRENCH_FIX,
	TF_DMG_CUSTOM_MINIGUN,
	TF_DMG_CUSTOM_SUICIDE,
	TF_DMG_CUSTOM_TAUNTATK_HADOUKEN,
	TF_DMG_CUSTOM_BURNING_FLARE,
	TF_DMG_CUSTOM_TAUNTATK_HIGH_NOON,
	TF_DMG_CUSTOM_TAUNTATK_GRAND_SLAM,
	TF_DMG_CUSTOM_PENETRATE_MY_TEAM,
	TF_DMG_CUSTOM_PENETRATE_ALL_PLAYERS,
	TF_DMG_CUSTOM_TAUNTATK_FENCING,
	TF_DMG_CUSTOM_PENETRATE_HEADSHOT,
	TF_DMG_CUSTOM_TAUNTATK_ARROW_STAB,
	TF_DMG_CUSTOM_TELEFRAG,
	TF_DMG_CUSTOM_BURNING_ARROW,
	TF_DMG_CUSTOM_FLYINGBURN,
	TF_DMG_CUSTOM_PUMPKIN_BOMB,
	TF_DMG_CUSTOM_DECAPITATION,
	TF_DMG_CUSTOM_TAUNTATK_GRENADE,
	TF_DMG_CUSTOM_BASEBALL,
	TF_DMG_CUSTOM_CHARGE_IMPACT,
	TF_DMG_CUSTOM_TAUNTATK_BARBARIAN_SWING,
	TF_DMG_CUSTOM_AIR_STICKY_BURST,
	TF_DMG_CUSTOM_DEFENSIVE_STICKY,
	TF_DMG_CUSTOM_PICKAXE,
	TF_DMG_CUSTOM_ROCKET_DIRECTHIT,
	TF_DMG_CUSTOM_TAUNTATK_UBERSLICE,
	TF_DMG_CUSTOM_PLAYER_SENTRY,
	TF_DMG_CUSTOM_STANDARD_STICKY,
	TF_DMG_CUSTOM_SHOTGUN_REVENGE_CRIT,
	TF_DMG_CUSTOM_TAUNTATK_ENGINEER_GUITAR_SMASH,
	TF_DMG_CUSTOM_BLEEDING,
	TF_DMG_CUSTOM_GOLD_WRENCH,
	TF_DMG_CUSTOM_CARRIED_BUILDING,
	TF_DMG_CUSTOM_COMBO_PUNCH,
	TF_DMG_CUSTOM_TAUNTATK_ENGINEER_ARM_KILL,
	TF_DMG_CUSTOM_FISH_KILL,
	TF_DMG_CUSTOM_TRIGGER_HURT,
	TF_DMG_CUSTOM_DECAPITATION_BOSS,
	TF_DMG_CUSTOM_STICKBOMB_EXPLOSION,
	TF_DMG_CUSTOM_AEGIS_ROUND,
	TF_DMG_CUSTOM_FLARE_EXPLOSION,
	TF_DMG_CUSTOM_BOOTS_STOMP,
	TF_DMG_CUSTOM_PLASMA,
	TF_DMG_CUSTOM_PLASMA_CHARGED,
	TF_DMG_CUSTOM_PLASMA_GIB,
	TF_DMG_CUSTOM_PRACTICE_STICKY,
	TF_DMG_CUSTOM_EYEBALL_ROCKET,
	TF_DMG_CUSTOM_HEADSHOT_DECAPITATION,
	TF_DMG_CUSTOM_TAUNTATK_ARMAGEDDON,
	TF_DMG_CUSTOM_FLARE_PELLET,
	TF_DMG_CUSTOM_CLEAVER,
	TF_DMG_CUSTOM_CLEAVER_CRIT,
	TF_DMG_CUSTOM_SAPPER_RECORDER_DEATH,
	TF_DMG_CUSTOM_MERASMUS_PLAYER_BOMB,
	TF_DMG_CUSTOM_MERASMUS_GRENADE,
	TF_DMG_CUSTOM_MERASMUS_ZAP,
	TF_DMG_CUSTOM_MERASMUS_DECAPITATION,
	TF_DMG_CUSTOM_CANNONBALL_PUSH,
	TF_DMG_CUSTOM_TAUNTATK_ALLCLASS_GUITAR_RIFF,
	TF_DMG_CUSTOM_THROWABLE,
	TF_DMG_CUSTOM_THROWABLE_KILL,
	TF_DMG_CUSTOM_SPELL_TELEPORT,
	TF_DMG_CUSTOM_SPELL_SKELETON,
	TF_DMG_CUSTOM_SPELL_MIRV,
	TF_DMG_CUSTOM_SPELL_METEOR,
	TF_DMG_CUSTOM_SPELL_LIGHTNING,
	TF_DMG_CUSTOM_SPELL_FIREBALL,
	TF_DMG_CUSTOM_SPELL_MONOCULUS,
	TF_DMG_CUSTOM_SPELL_BLASTJUMP,
	TF_DMG_CUSTOM_SPELL_BATS,
	TF_DMG_CUSTOM_SPELL_TINY,
	TF_DMG_CUSTOM_KART,
	TF_DMG_CUSTOM_GIANT_HAMMER,
	TF_DMG_CUSTOM_RUNE_REFLECT,
};

enum
{
	OBJ_DISPENSER         = 0,
	OBJ_TELEPORTER        = 1,
	OBJ_SENTRYGUN         = 2,
	OBJ_ATTACHMENT_SAPPER = 3,
};

/* from SourceMod; can't seem to find these elsewhere */
enum
{
	TF_STUNFLAG_SLOWDOWN        = (1 << 0),	/**< activates slowdown modifier */
	TF_STUNFLAG_BONKSTUCK       = (1 << 1),	/**< bonk sound, stuck */
	TF_STUNFLAG_LIMITMOVEMENT   = (1 << 2),	/**< disable forward/backward movement */
	TF_STUNFLAG_CHEERSOUND      = (1 << 3),	/**< cheering sound */
	TF_STUNFLAG_NOSOUNDOREFFECT = (1 << 5),	/**< no sound or particle */
	TF_STUNFLAG_THIRDPERSON     = (1 << 6),	/**< panic animation */
	TF_STUNFLAG_GHOSTEFFECT     = (1 << 7),	/**< ghost particles */
	
	TF_STUNFLAGS_LOSERSTATE     = TF_STUNFLAG_SLOWDOWN | TF_STUNFLAG_NOSOUNDOREFFECT | TF_STUNFLAG_THIRDPERSON,
	TF_STUNFLAGS_GHOSTSCARE     = TF_STUNFLAG_GHOSTEFFECT | TF_STUNFLAG_THIRDPERSON,
	TF_STUNFLAGS_SMALLBONK      = TF_STUNFLAG_THIRDPERSON | TF_STUNFLAG_SLOWDOWN,
	TF_STUNFLAGS_NORMALBONK     = TF_STUNFLAG_BONKSTUCK,
	TF_STUNFLAGS_BIGBONK        = TF_STUNFLAG_CHEERSOUND | TF_STUNFLAG_BONKSTUCK,
};

enum
{
	TF_PROJECTILE_NONE,
	TF_PROJECTILE_BULLET,
	TF_PROJECTILE_ROCKET,
	TF_PROJECTILE_PIPEBOMB,
	TF_PROJECTILE_PIPEBOMB_REMOTE,
	TF_PROJECTILE_SYRINGE,
	TF_PROJECTILE_FLARE,
	TF_PROJECTILE_JAR,
	TF_PROJECTILE_ARROW,
	TF_PROJECTILE_FLAME_ROCKET,
	TF_PROJECTILE_JAR_MILK,
	TF_PROJECTILE_HEALING_BOLT,
	TF_PROJECTILE_ENERGY_BALL,
	TF_PROJECTILE_ENERGY_RING,
	TF_PROJECTILE_PIPE_REMOTE_PRACTICE,
	TF_PROJECTILE_CLEAVER,
	TF_PROJECTILE_STICKY_BALL,
	TF_PROJECTILE_CANNONBALL,
	TF_PROJECTILE_BUILDING_REPAIR_BOLT,
	TF_PROJECTILE_FESTIVE_ARROW,
	TF_PROJECTILE_THROWABLE,
	TF_PROJECTILE_SPELLFIREBALL,
	TF_PROJECTILE_FESTIVE_URINE,
	TF_PROJECTILE_FESTIVE_HEALING_BOLT,
	TF_PROJECTILE_BREADMONSTER_JARATE,
	TF_PROJECTILE_BREADMONSTER_MADMILK,
	TF_PROJECTILE_GRAPPLINGHOOK,
	TF_PROJECTILE_SENTRY_ROCKET,
	TF_PROJECTILE_BREAD_MONSTER,
	
	TF_NUM_PROJECTILES,
};

enum
{
	TF_WPN_TYPE_PRIMARY   = 0,
	TF_WPN_TYPE_SECONDARY = 1,
	TF_WPN_TYPE_MELEE     = 2,
	TF_WPN_TYPE_UTILITY   = 3,
	TF_WPN_TYPE_BUILDING  = 4, // sapper
	TF_WPN_TYPE_PDA       = 5, // engie build pda, disguise kit
	TF_WPN_TYPE_PDA2      = 6, // engie destroy pda, invis watch
	TF_WPN_TYPE_HEAD      = 7,
	TF_WPN_TYPE_MISC      = 8,
	TF_WPN_TYPE_ACTION    = 9, // canteens
	/* slot 10 unknown */
	TF_WPN_TYPE_TAUNT     = 11,
};


#define TF_FLAGINFO_NONE		0
#define TF_FLAGINFO_STOLEN		(1<<0)
#define TF_FLAGINFO_DROPPED		(1<<1)


/* I invented this function, because this particular idiom comes up frequently;
 * I can't seem to actually find it anywhere in the 2013 SDK or the 2007 leak,
 * so I don't know if it actually is an inlined function or just a copypasta */
inline int GetEnemyTeam(CBaseEntity *ent)
{
	int enemy_team = ent->GetTeamNumber();
	
	switch (enemy_team) {
	case TF_TEAM_RED:
		enemy_team = TF_TEAM_BLUE;
		break;
	case TF_TEAM_BLUE:
		enemy_team = TF_TEAM_RED;
		break;
	}
	
	return enemy_team;
}


#endif