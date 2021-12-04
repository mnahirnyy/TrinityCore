/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_DEMONHUNTER and SPELLFAMILY_GENERIC spells used by demon hunter players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dh_".
 */

#include "ScriptMgr.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "SpellScript.h"

enum DemonHunterSpells
{
    SPELL_DH_ANNIHILATION                   = 201427,
    SPELL_DH_ANNIHILATION_MAINHAIND         = 201428,
    SPELL_DH_ANNIHILATION_OFFHAND           = 227518,
    SPELL_DH_BLADE_DANCE                    = 188499,
    SPELL_DH_BLIND_FURY                     = 203550,
    SPELL_DH_BLOODLET                       = 206473,
    SPELL_DH_BLOODLET_DOT                   = 207690,
    SPELL_DH_BLUR                           = 198589,
    SPELL_DH_BURNING_ALIVE                  = 207739,
    SPELL_DH_CHAOS_CLEAVE                   = 206475,
    SPELL_DH_CHAOS_CLEAVE_DAMAGE            = 236237,
    SPELL_DH_CHAOS_NOVA                     = 179057,
    SPELL_DH_CHAOS_STRIKE                   = 162794,
    SPELL_DH_CHAOS_STRIKE_MAIN_HAND         = 199547,
    SPELL_DH_CHAOS_STRIKE_OFF_HAND          = 222031,
    SPELL_DH_CHAOS_STRIKE_PROC              = 193840,
    SPELL_DH_CONSUME_MAGIC                  = 183752,
    SPELL_DH_CONSUME_SOUL_10                = 228532,
    SPELL_DH_CONSUME_SOUL_10_VENG           = 203794,
    SPELL_DH_CONSUME_SOUL_25                = 178963,
    SPELL_DH_CONSUME_SOUL_25_VENG           = 210042,
    SPELL_DH_CONSUME_SOUL_DEMON             = 202644,
    SPELL_DH_CONSUME_SOUL_DEMON_VENG        = 208015,
    SPELL_DH_CONSUME_SOUL_MISSILE           = 210047,
    SPELL_DH_DARKNESS_BUFF                  = 209426,
    SPELL_DH_DEMON_BLADES                   = 203555,
    SPELL_DH_DEMON_BLADES_TRIGGER           = 203796,
    SPELL_DH_DEMON_REBORN                   = 193897,
    SPELL_DH_DEMON_SPIKES                   = 203720,
    SPELL_DH_DEMON_SPIKES_BUFF              = 203819,
    SPELL_DH_DEMONIC                        = 213410,
    SPELL_DH_DEMONIC_APPETITE               = 206478,
    SPELL_DH_DEMONIC_APPETITE_FURY          = 210041,
    SPELL_DH_DEMONS_BITE                    = 162243,
    SPELL_DH_EYE_BEAM                       = 198013,
    SPELL_DH_EYE_BEAM_DAMAGE                = 198030,
    SPELL_DH_EYE_BEAM_VISUAL                = 194326,
    SPELL_DH_FEAST_OF_SOULS                 = 207697,
    SPELL_DH_FEAST_OF_SOULS_HEAL            = 207693,
    SPELL_DH_FEED_THE_DEMON                 = 218612,
    SPELL_DH_FEL_BARRAGE                    = 211053,
    SPELL_DH_FEL_BARRAGE_TRIGGER            = 211052,
    SPELL_DH_FEL_DEVASTATION_DAMAGE         = 212105,
    SPELL_DH_FEL_DEVASTATION_HEAL           = 212106,
    SPELL_DH_FEL_ERUPTION                   = 211881,
    SPELL_DH_FEL_ERUPTION_DAMAGE            = 225102,
    SPELL_DH_FEL_MASTERY                    = 192939,
    SPELL_DH_FEL_RUSH                       = 195072,
    SPELL_DH_FEL_RUSH_AIR                   = 197923,
    SPELL_DH_FEL_RUSH_DAMAGE                = 192611,
    SPELL_DH_FEL_RUSH_DASH                  = 197922,
    SPELL_DH_FEL_RUSH_DASH2                 = 208101,
    SPELL_DH_FELBLADE                       = 232893,
    SPELL_DH_FELBLADE_CHARGE                = 213241,
    SPELL_DH_FELBLADE_DAMAGE                = 213243,
    SPELL_DH_FIERY_BRAND_DOT                = 207771,
    SPELL_DH_FIRST_BLOOD                    = 206416,
    SPELL_DH_FLAME_CRASH                    = 227322,
    SPELL_DH_FRAILITY                       = 224509,
    SPELL_DH_GLIDE                          = 131347,
    SPELL_DH_GLIDE_KNOCKBACK                = 196353,
    SPELL_DH_GLUTTONY                       = 227327,
    SPELL_DH_GLUTTONY_BUFF                  = 227330,
    SPELL_DH_IMMOLATION_AURA                = 178740,
    SPELL_DH_IMMOLATION_AURA_VISUAL         = 201122,
    SPELL_DH_INFERNAL_STRIKE                = 189110,
    SPELL_DH_INFERNAL_STRIKE_DAMAGE         = 189112,
    SPELL_DH_INFERNAL_STRIKE_JUMP           = 189111,
    SPELL_DH_INFERNAL_STRIKE_VISUAL         = 208461,
    SPELL_DH_LAST_RESORT_DEBUFF             = 209261,
    SPELL_DH_METAMORPHOSIS                  = 191427,
    SPELL_DH_METAMORPHOSIS_BUFFS            = 162264,
    SPELL_DH_METAMORPHOSIS_IMMUNITY         = 201453,
    SPELL_DH_METAMORPHOSIS_LEAP             = 191428,
    SPELL_DH_METAMORPHOSIS_STUN             = 200166,
    SPELL_DH_METAMORPHOSIS_VENGEANCE        = 187827,
    SPELL_DH_MOMENTUM                       = 206476,
    SPELL_DH_MOMENTUM_BUFF                  = 208628,
    SPELL_DH_NEMESIS                        = 206491,
    SPELL_DH_NETHER_BOND                    = 207810,
    SPELL_DH_NETHER_BOND_DAMAGE             = 207812,
    SPELL_DH_NETHER_BOND_PERIODIC           = 207811,
    SPELL_DH_PREPARED                       = 203551,
    SPELL_DH_RAZOR_SPIKES_SLOW              = 210003,
    SPELL_DH_SHATTERED_SOULS                = 178940,
    SPELL_DH_SHATTERED_SOULS_AT_DEMON       = 203795,
    SPELL_DH_SHATTERED_SOULS_AT_NORMAL      = 228537,
    SPELL_DH_SHATTERED_SOULS_LESSER         = 204255,
    SPELL_DH_SHATTERED_SOULS_MISSILE        = 209651,
    SPELL_DH_SHEAR                          = 203782,
    SPELL_DH_SIGIL_OF_CHAINS_EXPLOSION      = 208673,
    SPELL_DH_SIGIL_OF_CHAINS_SLOW           = 204843,
    SPELL_DH_SIGIL_OF_CHAINS_TRIGGER        = 208674,
    SPELL_DH_SIGIL_OF_FLAME_EXPLOSION       = 208710,
    SPELL_DH_SIGIL_OF_FLAME_NO_DEST         = 204513,
    SPELL_DH_SIGIL_OF_FLAME_TRIGGER         = 204598,
    SPELL_DH_SIGIL_OF_MISERY_EXPLOSION      = 208714,
    SPELL_DH_SIGIL_OF_MISERY_TRIGGER        = 207685,
    SPELL_DH_SIGIL_OF_SILENCE_EXPLOSION     = 208709,
    SPELL_DH_SIGIL_OF_SILENCE_TRIGGER       = 204490,
    SPELL_DH_SOUL_BARRIER                   = 227225,
    SPELL_DH_SOUL_CLEAVE_DAMAGE             = 228478,
    SPELL_DH_SOUL_RENDING_HAVOC             = 204909,
    SPELL_DH_SOUL_RENDING_VENGEANCE         = 217996,
    SPELL_DH_SPIRIT_BOMB                    = 247454,
    SPELL_DH_SPIRIT_BOMB_DAMAGE             = 247455,
    SPELL_DH_SPIRIT_BOMB_HEAL               = 227255,
    SPELL_DH_THROW_GLAIVE                   = 185123,
    SPELL_DH_VENGEFUL_RETREAT               = 198793,
    SPELL_DH_VENGEFUL_RETREAT_FURY          = 203650,
    SPELL_DH_VENGEFUL_RETREAT_TRIGGER       = 198813,
};

enum NemesisTargets
{
    NEMESIS_ABERRATION                          = 208607,
    NEMESIS_ELEMENTAL                           = 208611,
    NEMESIS_MECHANICAL                          = 208616,
    NEMESIS_DRAGONKIN                           = 208610,
    NEMESIS_HUMANOID                            = 208605,
    NEMESIS_CRITTERS                            = 208609,
    NEMESIS_DEMONS                              = 208579,
    NEMESIS_GIANTS                              = 208612,
    NEMESIS_UNDEAD                              = 208614,
    NEMESIS_BEASTS                              = 208608
};

// 197125 - Chaos Strike
class spell_dh_chaos_strike : public SpellScriptLoader
{
public:
    spell_dh_chaos_strike() : SpellScriptLoader("spell_dh_chaos_strike") { }

    class spell_dh_chaos_strike_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_dh_chaos_strike_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo({ SPELL_DH_CHAOS_STRIKE_PROC });
        }

        void HandleEffectProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
        {
            PreventDefaultAction();

            if (Unit* caster = GetCaster())
                caster->CastCustomSpell(SPELL_DH_CHAOS_STRIKE_PROC, SPELLVALUE_BASE_POINT0, aurEff->GetBaseAmount(), caster);
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_dh_chaos_strike_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_dh_chaos_strike_AuraScript();
    }
};

void AddSC_demon_hunter_spell_scripts()
{
    new spell_dh_chaos_strike();
}
