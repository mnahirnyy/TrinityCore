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
 * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pal_".
 */

#include "ScriptMgr.h"
#include "Group.h"
#include "Player.h"
#include "Random.h"
#include "SpellAuraEffects.h"
#include "SpellHistory.h"
#include "SpellMgr.h"
#include "SpellScript.h"

enum PaladinSpells
{
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID   = 37878,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN = 37879,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST  = 37880,
    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN  = 37881,
    SPELL_PALADIN_BLINDING_LIGHT_EFFECT          = 105421,
    SPELL_PALADIN_DIVINE_PURPOSE_PROC            = 90174,
    SPELL_PALADIN_DIVINE_STEED_HUMAN             = 221883,
    SPELL_PALADIN_DIVINE_STEED_DRAENEI           = 221887,
    SPELL_PALADIN_DIVINE_STEED_BLOODELF          = 221886,
    SPELL_PALADIN_DIVINE_STEED_TAUREN            = 221885,
    SPELL_PALADIN_DIVINE_STORM_DAMAGE            = 224239,
    SPELL_PALADIN_ENDURING_LIGHT                 = 40471,
    SPELL_PALADIN_ENDURING_JUDGEMENT             = 40472,
    SPELL_PALADIN_FINAL_STAND                    = 204077,
    SPELL_PALADIN_FINAL_STAND_EFFECT             = 204079,
    SPELL_PALADIN_FORBEARANCE                    = 25771,
    SPELL_PALADIN_HAND_OF_SACRIFICE              = 6940,
    SPELL_PALADIN_HOLY_MENDING                   = 64891,
    SPELL_PALADIN_HOLY_POWER_ARMOR               = 28790,
    SPELL_PALADIN_HOLY_POWER_ATTACK_POWER        = 28791,
    SPELL_PALADIN_HOLY_POWER_SPELL_POWER         = 28793,
    SPELL_PALADIN_HOLY_POWER_MP5                 = 28795,
    SPELL_PALADIN_HOLY_SHOCK_R1                  = 20473,
    SPELL_PALADIN_HOLY_SHOCK_R1_DAMAGE           = 25912,
    SPELL_PALADIN_HOLY_SHOCK_R1_HEALING          = 25914,
    SPELL_PALADIN_IMMUNE_SHIELD_MARKER           = 61988,
    SPELL_PALADIN_ITEM_HEALING_TRANCE            = 37706,
    SPELL_PALADIN_JUDGEMENT_DAMAGE               = 54158,
    SPELL_PALADIN_CRUSADERS_MIGHT = 196926,
    SPELL_PALADIN_CRUSADER_STRIKE = 35395,
    SPELL_PALADIN_HOLY_SHOCK_DAMAGE = 25912,
    SPELL_PALADIN_HOLY_SHOCK_GENERIC = 20473,
    SPELL_PALADIN_HOLY_SHOCK_HEAL = 25914,
    SPELL_PALADIN_LIGHT_OF_DAWN = 85222,
    SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER = 185984,
    SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS = 53600,
    SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS_PROC = 132403,
    SPELL_PALADIN_SHIELD_OF_VENGEANCE_DAMAGE = 184689,
    SPELL_PALADIN_TEMPLARS_VERDICT = 85256,
    SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE = 224266,
    SPELL_PALADIN_FIST_OF_JUSTICE = 198054,
    SPELL_PALADIN_FIST_OF_JUSTICE_RETRI = 234299,
    SPELL_PALADIN_HAMMER_OF_JUSTICE = 853,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY = 197646,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1 = 216411,
    SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2 = 216413,
    SPELL_PALADIN_DIVINE_PURPOSE_RET = 223817,
    SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA = 223819,
    SPELL_PALADIN_INFUSION_OF_LIGHT_AURA = 54149,
    SPELL_PALADIN_JUDGMENT = 20271,
    SPELL_PALADIN_JUDGMENT_HOLY_DEBUFF = 214222,
    SPELL_PALADIN_JUDGMENT_OF_LIGHT_HEAL = 183811,
    SPELL_PALADIN_JUDGMENT_RETRI_DEBUFF = 197277,
    SPELL_PALADIN_BEACON_OF_FAITH = 156910,
    SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA = 177173,
    SPELL_PALADIN_BEACON_OF_LIGHT = 53563,
    SPELL_PALADIN_BEACON_OF_LIGHT_HEAL = 53652,
    SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA = 53651,
    SPELL_PALADIN_BEACON_OF_VIRTUE = 200025,
    SPELL_PALADIN_ARCING_LIGHT_DAMAGE = 114919,
    SPELL_PALADIN_ARCING_LIGHT_HEAL = 119952,
    SPELL_PALADIN_ARDENT_DEFENDER = 31850,
    SPELL_PALADIN_ARDENT_DEFENDER_HEAL = 66235,
    SPELL_PALADIN_AVENGERS_SHIELD = 31935,
    SPELL_PALADIN_AVENGING_WRATH = 31884,
    SPELL_PALADIN_AURA_OF_SACRIFICE = 183416,
    SPELL_PALADIN_AURA_OF_SACRIFICE_ALLY = 210372,
    SPELL_PALADIN_AURA_OF_SACRIFICE_DAMAGE = 210380,
    SPELL_PALADIN_AURA_OF_SACRIFICE_HEAL = 210383,
    SPELL_PALADIN_HOLY_PRISM_ALLIES = 114871,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL = 114862,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2 = 114870,
    SPELL_PALADIN_HOLY_PRISM_ENNEMIES = 114852,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL = 121551,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2 = 121552,
    SPELL_PALADIN_LIGHT_OF_THE_MARTYR = 183998,
    SPELL_PALADIN_LIGHT_OF_THE_MARTYR_DAMAGE = 196917,
    SPELL_PALADIN_LIGHT_OF_THE_PROTECTOR = 184092,
};

enum PaladinSpellVisualKit
{
    PALADIN_VISUAL_KIT_DIVINE_STORM = 73892
};

/*********************************
 *** RERIBUTION PALADIN SPELLS ***
 *********************************/

// 35395 - Crusader Strike
class spell_pal_crusader_strike : public SpellScript
{
    PrepareSpellScript(spell_pal_crusader_strike);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (caster->HasAura(SPELL_PALADIN_CRUSADERS_MIGHT))
        {
            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HOLY_SHOCK_GENERIC))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HOLY_SHOCK_GENERIC, -1.5 * IN_MILLISECONDS);

            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_LIGHT_OF_DAWN))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_LIGHT_OF_DAWN, -1.5 * IN_MILLISECONDS);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_crusader_strike::HandleOnHit, EFFECT_0, SPELL_EFFECT_NORMALIZED_WEAPON_DMG);
    }
};

// 19750 - Flash of Light
class spell_pal_flash_of_light : public SpellScript
{
    PrepareSpellScript(spell_pal_flash_of_light);

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->RemoveAurasDueToSpell(SPELL_PALADIN_INFUSION_OF_LIGHT_AURA);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_flash_of_light::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
    }
};

// 20271 - Judgement
class spell_pal_judgment : public SpellScript
{
    PrepareSpellScript(spell_pal_judgment);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetExplTargetUnit();
        uint32 spec = caster->GetUInt32Value(PLAYER_FIELD_CURRENT_SPEC_ID);
        switch (spec)
        {
            case TALENT_SPEC_PALADIN_RETRIBUTION:
            {
                caster->CastSpell(target, SPELL_PALADIN_JUDGMENT_RETRI_DEBUFF);
                break;
            }
            case TALENT_SPEC_PALADIN_HOLY:
            {
                caster->CastSpell(target, SPELL_PALADIN_JUDGMENT_HOLY_DEBUFF);

                if (caster->HasAura(SPELL_PALADIN_FIST_OF_JUSTICE))
                {
                    if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
                        caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, -10 * IN_MILLISECONDS);
                }
                break;
            }
            case TALENT_SPEC_PALADIN_PROTECTION:
            {
                caster->ToPlayer()->GetSpellHistory()->ReduceChargeCooldown(sSpellMgr->GetSpellInfo(SPELL_PALADIN_SHIELD_OF_THE_RIGHTEOUS)->ChargeCategoryId, 1000);

                if (caster->HasAura(SPELL_PALADIN_FIST_OF_JUSTICE))
                {
                    if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
                        caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, -10 * IN_MILLISECONDS);
                }
                break;
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_judgment::HandleDummy, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

// 85256 - Templar's Verdict
class spell_pal_templar_s_verdict : public SpellScript
{
    PrepareSpellScript(spell_pal_templar_s_verdict);

    bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE });
    }

    void HandleOnHit(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();

        if (Unit* target = GetExplTargetUnit())
            caster->CastSpell(target, SPELL_PALADIN_TEMPLARS_VERDICT_DAMAGE, true);

        if (caster->HasAura(SPELL_PALADIN_FIST_OF_JUSTICE_RETRI))
        {
            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, -7.5 * IN_MILLISECONDS);
        }

        if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA))
            caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_templar_s_verdict::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 184662 - Shield of Vengeance
class spell_pal_shield_of_vengeance : public AuraScript
{
    PrepareAuraScript(spell_pal_shield_of_vengeance);

    int32 absorb;
    int32 currentAbsorb;

    void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
    {
        if (Unit* caster = GetCaster())
        {
            canBeRecalculated = false;

            float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
            absorb = (ap * 20);
            amount += absorb;
        }
    }

    void Absorb(AuraEffect* /*aurEff*/, DamageInfo& dmgInfo, uint32& /*absorbAmount*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        currentAbsorb += dmgInfo.GetDamage();
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        if (currentAbsorb < absorb)
            return;

        absorb /= 1; // TO DO: Implement it properly

        caster->CastCustomSpell(SPELL_PALADIN_SHIELD_OF_VENGEANCE_DAMAGE, SPELLVALUE_BASE_POINT0, absorb, caster, true);
    }

    void Register() override
    {
        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_shield_of_vengeance::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_shield_of_vengeance::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
        OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_shield_of_vengeance::Absorb, EFFECT_0);
    }
};

// 53385 - Divine Storm
class spell_pal_divine_storm : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_storm);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_DIVINE_STORM_DAMAGE });
    }

    void HandleOnCast()
    {
        Unit* caster = GetCaster();
        caster->SendPlaySpellVisualKit(PALADIN_VISUAL_KIT_DIVINE_STORM, 0, 0);

        if (caster->HasAura(SPELL_PALADIN_FIST_OF_JUSTICE_RETRI))
        {
            if (caster->GetSpellHistory()->HasCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE))
                caster->GetSpellHistory()->ModifyCooldown(SPELL_PALADIN_HAMMER_OF_JUSTICE, -7.5 * IN_MILLISECONDS);
        }

        if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA))
            caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_RET_AURA);
    }

    void HandleDummy(SpellEffIndex /* effIndex */)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetHitUnit())
                caster->CastSpell(target, SPELL_PALADIN_DIVINE_STORM_DAMAGE, true);
    }

    void Register() override
    {
        OnCast += SpellCastFn(spell_pal_divine_storm::HandleOnCast);
        OnEffectHitTarget += SpellEffectFn(spell_pal_divine_storm::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

/*********************************
 *** HOLY PALADIN SPELLS ***
 *********************************/

 // 20473 - Holy Shock
class spell_pal_holy_shock : public SpellScript
{
    PrepareSpellScript(spell_pal_holy_shock);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({
            SPELL_PALADIN_HOLY_SHOCK_HEAL,
            SPELL_PALADIN_HOLY_SHOCK_DAMAGE
        });
    }

    SpellCastResult CheckCast()
    {
        Unit* caster = GetCaster();
        if (Unit* target = GetExplTargetUnit())
        {
            if (!caster->IsFriendlyTo(target))
            {
                if (!caster->IsValidAttackTarget(target))
                    return SPELL_FAILED_BAD_TARGETS;

                if (!caster->isInFront(target))
                    return SPELL_FAILED_UNIT_NOT_INFRONT;
            }
        }
        else
            return SPELL_FAILED_BAD_TARGETS;
        return SPELL_CAST_OK;
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Player* caster = GetCaster()->ToPlayer())
        {
            if (Unit* unitTarget = GetHitUnit())
            {
                if (caster->IsFriendlyTo(unitTarget))
                    caster->CastSpell(unitTarget, SPELL_PALADIN_HOLY_SHOCK_HEAL, true);
                else
                    caster->CastSpell(unitTarget, SPELL_PALADIN_HOLY_SHOCK_DAMAGE, true);
            }

            if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1))
                caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_1);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_holy_shock::CheckCast);
        OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

// 200025 - Beacon of Virtue
class spell_pal_beacon_of_virtue : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_virtue);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        Unit* caster = GetCaster();
        if (!caster)
            return;

        uint8 maxTargets = GetSpellInfo()->GetEffect(EFFECT_1)->BasePoints + 1;
        if (!maxTargets)
            return;

        if (targets.size() > maxTargets)
        {
            targets.sort(Trinity::HealthPctOrderPred());
            targets.resize(maxTargets);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtue::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtue::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ALLY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_beacon_of_virtue::FilterTargets, EFFECT_2, TARGET_UNIT_DEST_AREA_ALLY);
    }
};

// 156910 - Beacon of Faith
class spell_pal_beacon_of_faith : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_faith);

    SpellCastResult CheckCast()
    {
        Unit* target = GetExplTargetUnit();

        if (!target)
            return SPELL_FAILED_DONT_REPORT;

        if (target->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT))
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register()
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_beacon_of_faith::CheckCast);
    }
};

// 53563 - Beacon of Light
class spell_pal_beacon_of_light : public SpellScript
{
    PrepareSpellScript(spell_pal_beacon_of_light);

    SpellCastResult CheckCast()
    {
        Unit* target = GetExplTargetUnit();

        if (!target)
            return SPELL_FAILED_DONT_REPORT;

        if (target->HasAura(SPELL_PALADIN_BEACON_OF_FAITH))
            return SPELL_FAILED_BAD_TARGETS;

        return SPELL_CAST_OK;
    }

    void Register()
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_beacon_of_light::CheckCast);
    }
};

// 53563 - Beacon of Light / 156910 - Beacon of Faith  / 200025 - Beacon of Virtue Aura
class spell_pal_beacon_of_light_aura : public AuraScript
{
    PrepareAuraScript(spell_pal_beacon_of_light_aura);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();
        Unit* target = GetTarget();

        if (!caster)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT || GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_VIRTUE)
            caster->CastSpell(target, SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA, true);
        else
            caster->CastSpell(target, SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA, true);
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        Unit* caster = GetCaster();

        if (!caster)
            return;

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT || GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_VIRTUE)
            caster->RemoveAura(SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA);
        else
            caster->RemoveAura(SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA);
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_pal_beacon_of_light_aura::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_pal_beacon_of_light_aura::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

// 53651 - Beacon of Light Proc / Beacon of Faith (proc aura) - 177173
class spell_pal_beacon_of_light_proc : public AuraScript
{
    PrepareAuraScript(spell_pal_beacon_of_light_proc);

    int32 GetPctBySpell(uint32 spellID) const
    {
        int32 pct = 0;

        switch (spellID)
        {
        case SPELL_PALADIN_ARCING_LIGHT_HEAL: // Light's Hammer
        case SPELL_PALADIN_HOLY_PRISM_ALLIES: // Holy Prism
        case SPELL_PALADIN_LIGHT_OF_DAWN: // Light of Dawn
            pct = 15; // 15% heal from these spells
            break;
        default:
            pct = 40; // 40% heal from all other heals
            break;
        }

        return pct;
    }

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        Unit* ownerOfBeacon = GetTarget();
        Unit* targetOfBeacon = GetCaster();
        Unit* targetOfHeal = eventInfo.GetActionTarget();

        if (eventInfo.GetSpellInfo() && eventInfo.GetSpellInfo()->Id != SPELL_PALADIN_BEACON_OF_LIGHT_HEAL && eventInfo.GetSpellInfo()->Id != SPELL_PALADIN_LIGHT_OF_THE_MARTYR && targetOfBeacon->IsWithinLOSInMap(ownerOfBeacon) && targetOfHeal->GetGUID() != targetOfBeacon->GetGUID())
            return true;

        return false;
    }

    void OnProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
    {
        PreventDefaultAction();
        bool auraCheck;
        Unit* ownerOfBeacon = GetTarget();
        Unit* targetOfBeacon = GetCaster();

        if (!targetOfBeacon)
            return;

        HealInfo* healInfo = eventInfo.GetHealInfo();

        if (!healInfo)
            return;

        int32 bp = CalculatePct(healInfo->GetHeal(), GetPctBySpell(GetSpellInfo()->Id));

        if (GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_LIGHT_PROC_AURA && (targetOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT) || targetOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_VIRTUE)))
        {
            ownerOfBeacon->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, bp, targetOfBeacon, true);
            auraCheck = true;
        }

        if ((GetSpellInfo()->Id == SPELL_PALADIN_BEACON_OF_FAITH_PROC_AURA && targetOfBeacon->HasAura(SPELL_PALADIN_BEACON_OF_FAITH)))
        {
            bp /= 2;
            ownerOfBeacon->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, bp, targetOfBeacon, true);
            auraCheck = true;
        }

        if (!auraCheck)
            ownerOfBeacon->RemoveAura(GetSpellInfo()->Id);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_beacon_of_light_proc::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_beacon_of_light_proc::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
    }
};

// 85222 - Light of Dawn
class spell_pal_light_of_dawn : public SpellScriptLoader
{
public:
    spell_pal_light_of_dawn() : SpellScriptLoader("spell_pal_light_of_dawn") {}

    class spell_pal_light_of_dawn_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_light_of_dawn_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (Unit* caster = GetCaster())
            {
                caster->CastSpell(caster, SPELL_PALADIN_LIGHT_OF_DAWN_TRIGGER, true);

                if (caster->HasAura(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2))
                    caster->RemoveAurasDueToSpell(SPELL_PALADIN_DIVINE_PURPOSE_HOLY_AURA_2);
            }
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_light_of_dawn_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_light_of_dawn_SpellScript();
    }
};

// 185984 - Light of Dawn aoe heal
class spell_pal_light_of_dawn_trigger : public SpellScriptLoader
{
public:
    spell_pal_light_of_dawn_trigger() : SpellScriptLoader("spell_pal_light_of_dawn_trigger") {}

    class spell_pal_light_of_dawn_trigger_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_light_of_dawn_trigger_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            Unit* caster = GetCaster();
            uint8 limit = 5;

            targets.remove_if([caster](WorldObject* target)
            {
                Position pos = target->GetPosition();
                return !(caster->IsWithinDist2d(&pos, 15.0f) && caster->isInFront(target, float(M_PI / 3))); //must be in a cone in 15 yards
            });

            Trinity::Containers::RandomResize(targets, limit); //max 5 targets.
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            int32 dmg = GetHitHeal();

            dmg += GetCaster()->GetUInt32Value(UNIT_FIELD_ATTACK_POWER) * 1.8f;

            SetHitHeal(dmg);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_light_of_dawn_trigger_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            OnEffectHitTarget += SpellEffectFn(spell_pal_light_of_dawn_trigger_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_HEAL);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_light_of_dawn_trigger_SpellScript();
    }
};

// 53576 - Infusion of Light
class spell_pal_infusion_of_light : public AuraScript
{
    PrepareAuraScript(spell_pal_infusion_of_light);

    bool CheckProc(ProcEventInfo& eventInfo)
    {
        bool _spellCanProc = (eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_SHOCK_DAMAGE || eventInfo.GetSpellInfo()->Id == SPELL_PALADIN_HOLY_SHOCK_HEAL);

        if (_spellCanProc)
            return true;

        return false;
    }

    void HandleEffectProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
    {
        Unit* caster = GetCaster();

        caster->CastSpell(caster, SPELL_PALADIN_INFUSION_OF_LIGHT_AURA, true);
    }

    void Register() override
    {
        DoCheckProc += AuraCheckProcFn(spell_pal_infusion_of_light::CheckProc);
        OnEffectProc += AuraEffectProcFn(spell_pal_infusion_of_light::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
    }
};
 /*********************************
  *** PROTECTION PALADIN SPELLS ***
  *********************************/


// 37877 - Blessing of Faith
class spell_pal_blessing_of_faith : public SpellScriptLoader
{
    public:
        spell_pal_blessing_of_faith() : SpellScriptLoader("spell_pal_blessing_of_faith") { }

        class spell_pal_blessing_of_faith_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_blessing_of_faith_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID,
                    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN,
                    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST,
                    SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN
                });
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    uint32 spell_id = 0;
                    switch (unitTarget->getClass())
                    {
                        case CLASS_DRUID:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_DRUID;
                            break;
                        case CLASS_PALADIN:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PALADIN;
                            break;
                        case CLASS_PRIEST:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_PRIEST;
                            break;
                        case CLASS_SHAMAN:
                            spell_id = SPELL_PALADIN_BLESSING_OF_LOWER_CITY_SHAMAN;
                            break;
                        default:
                            return; // ignore for non-healing classes
                    }
                    Unit* caster = GetCaster();
                    caster->CastSpell(caster, spell_id, true);
                }
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_blessing_of_faith_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pal_blessing_of_faith_SpellScript();
        }
};

// 1022 - Blessing of Protection
// 204018 - Blessing of Spellwarding
class spell_pal_blessing_of_protection : public SpellScript
{
    PrepareSpellScript(spell_pal_blessing_of_protection);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo(
        {
            SPELL_PALADIN_FORBEARANCE,
            // uncomment when we have serverside only spells
            //SPELL_PALADIN_IMMUNE_SHIELD_MARKER
        }) && spellInfo->ExcludeTargetAuraSpell == SPELL_PALADIN_IMMUNE_SHIELD_MARKER;
    }

    SpellCastResult CheckForbearance()
    {
        Unit* target = GetExplTargetUnit();
        if (!target || target->HasAura(SPELL_PALADIN_FORBEARANCE))
            return SPELL_FAILED_TARGET_AURASTATE;

        return SPELL_CAST_OK;
    }

    void TriggerForbearance()
    {
        if (Unit* target = GetHitUnit())
        {
            GetCaster()->CastSpell(target, SPELL_PALADIN_FORBEARANCE, true);
            GetCaster()->CastSpell(target, SPELL_PALADIN_IMMUNE_SHIELD_MARKER, true);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_blessing_of_protection::CheckForbearance);
        AfterHit += SpellHitFn(spell_pal_blessing_of_protection::TriggerForbearance);
    }
};

// 115750 - Blinding Light
class spell_pal_blinding_light : public SpellScript
{
    PrepareSpellScript(spell_pal_blinding_light);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_BLINDING_LIGHT_EFFECT });
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_PALADIN_BLINDING_LIGHT_EFFECT, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_pal_blinding_light::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

// 642 - Divine Shield
class spell_pal_divine_shield : public SpellScript
{
    PrepareSpellScript(spell_pal_divine_shield);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo(
        {
            SPELL_PALADIN_FINAL_STAND,
            SPELL_PALADIN_FINAL_STAND_EFFECT,
            SPELL_PALADIN_FORBEARANCE,
            // uncomment when we have serverside only spells
            //SPELL_PALADIN_IMMUNE_SHIELD_MARKER
        }) && spellInfo->ExcludeCasterAuraSpell == SPELL_PALADIN_IMMUNE_SHIELD_MARKER;
    }

    SpellCastResult CheckForbearance()
    {
        if (GetCaster()->HasAura(SPELL_PALADIN_FORBEARANCE))
            return SPELL_FAILED_TARGET_AURASTATE;

        return SPELL_CAST_OK;
    }

    void HandleFinalStand()
    {
        if (GetCaster()->HasAura(SPELL_PALADIN_FINAL_STAND))
            GetCaster()->CastSpell((Unit*)nullptr, SPELL_PALADIN_FINAL_STAND_EFFECT, true);
    }

    void TriggerForbearance()
    {
        Unit* caster = GetCaster();
        caster->CastSpell(caster, SPELL_PALADIN_FORBEARANCE, true);
        caster->CastSpell(caster, SPELL_PALADIN_IMMUNE_SHIELD_MARKER, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_divine_shield::CheckForbearance);
        AfterCast += SpellCastFn(spell_pal_divine_shield::HandleFinalStand);
        AfterCast += SpellCastFn(spell_pal_divine_shield::TriggerForbearance);
    }
};

// 190784 - Divine Steed
class spell_pal_divine_steed : public SpellScriptLoader
{
public:
    spell_pal_divine_steed() : SpellScriptLoader("spell_pal_divine_steed") { }

    class spell_pal_divine_steed_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_divine_steed_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            return ValidateSpellInfo(
            {
                SPELL_PALADIN_DIVINE_STEED_HUMAN,
                SPELL_PALADIN_DIVINE_STEED_DRAENEI,
                SPELL_PALADIN_DIVINE_STEED_BLOODELF,
                SPELL_PALADIN_DIVINE_STEED_TAUREN
            });
        }

        void HandleOnCast()
        {
            Unit* caster = GetCaster();

            uint32 spellId = SPELL_PALADIN_DIVINE_STEED_HUMAN;
            switch (caster->getRace())
            {
                case RACE_HUMAN:
                case RACE_DWARF:
                    spellId = SPELL_PALADIN_DIVINE_STEED_HUMAN;
                    break;
                case RACE_DRAENEI:
                    spellId = SPELL_PALADIN_DIVINE_STEED_DRAENEI;
                    break;
                case RACE_BLOODELF:
                    spellId = SPELL_PALADIN_DIVINE_STEED_BLOODELF;
                    break;
                case RACE_TAUREN:
                    spellId = SPELL_PALADIN_DIVINE_STEED_TAUREN;
                    break;
                default:
                    break;
            }

            caster->CastSpell(caster, spellId, true);
        }

        void Register() override
        {
            OnCast += SpellCastFn(spell_pal_divine_steed_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_divine_steed_SpellScript();
    }
};

// -75806 - Grand Crusader
class spell_pal_grand_crusader : public SpellScriptLoader
{
    public:
        spell_pal_grand_crusader() : SpellScriptLoader("spell_pal_grand_crusader") { }

        class spell_pal_grand_crusader_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_grand_crusader_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_AVENGERS_SHIELD });
            }

            bool CheckProc(ProcEventInfo& /*eventInfo*/)
            {
                return GetTarget()->GetTypeId() == TYPEID_PLAYER;
            }

            void HandleEffectProc(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                GetTarget()->GetSpellHistory()->ResetCooldown(SPELL_PALADIN_AVENGERS_SHIELD, true);
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_pal_grand_crusader_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_pal_grand_crusader_AuraScript::HandleEffectProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_grand_crusader_AuraScript();
        }
};

// 54968 - Glyph of Holy Light
class spell_pal_glyph_of_holy_light : public SpellScriptLoader
{
    public:
        spell_pal_glyph_of_holy_light() : SpellScriptLoader("spell_pal_glyph_of_holy_light") { }

        class spell_pal_glyph_of_holy_light_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_glyph_of_holy_light_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                uint32 const maxTargets = GetSpellInfo()->MaxAffectedTargets;

                if (targets.size() > maxTargets)
                {
                    targets.sort(Trinity::HealthPctOrderPred());
                    targets.resize(maxTargets);
                }
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_pal_glyph_of_holy_light_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pal_glyph_of_holy_light_SpellScript();
        }
};

// 6940 - Hand of Sacrifice
class spell_pal_hand_of_sacrifice : public SpellScriptLoader
{
    public:
        spell_pal_hand_of_sacrifice() : SpellScriptLoader("spell_pal_hand_of_sacrifice") { }

        class spell_pal_hand_of_sacrifice_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_hand_of_sacrifice_AuraScript);

        public:
            spell_pal_hand_of_sacrifice_AuraScript()
            {
                remainingAmount = 0;
            }

        private:
            int32 remainingAmount;

            bool Load() override
            {
                if (Unit* caster = GetCaster())
                {
                    remainingAmount = caster->GetMaxHealth();
                    return true;
                }
                return false;
            }

            void Split(AuraEffect* /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & splitAmount)
            {
                remainingAmount -= splitAmount;

                if (remainingAmount <= 0)
                {
                    GetTarget()->RemoveAura(SPELL_PALADIN_HAND_OF_SACRIFICE);
                }
            }

            void Register() override
            {
                OnEffectSplit += AuraEffectSplitFn(spell_pal_hand_of_sacrifice_AuraScript::Split, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_hand_of_sacrifice_AuraScript();
        }
};

// 37705 - Healing Discount
class spell_pal_item_healing_discount : public SpellScriptLoader
{
    public:
        spell_pal_item_healing_discount() : SpellScriptLoader("spell_pal_item_healing_discount") { }

        class spell_pal_item_healing_discount_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_item_healing_discount_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_ITEM_HEALING_TRANCE });
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& /*eventInfo*/)
            {
                PreventDefaultAction();
                GetTarget()->CastSpell(GetTarget(), SPELL_PALADIN_ITEM_HEALING_TRANCE, true, NULL, aurEff);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_pal_item_healing_discount_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_item_healing_discount_AuraScript();
        }
};

// Activate Forbearance
// Called by Blessing of Protection - 1022, Lay on Hands - 633, Blessing of Spellwarding - 204018
class spell_pal_activate_forbearance : public SpellScript
{
    PrepareSpellScript(spell_pal_activate_forbearance);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_PALADIN_FORBEARANCE });
    }

    SpellCastResult CheckForbearance()
    {
        if (Unit* target = GetExplTargetUnit())
        {
            if (target->HasAura(SPELL_PALADIN_FORBEARANCE))
            {
                return SPELL_FAILED_TARGET_AURASTATE;
            }
        }
        return SPELL_CAST_OK;
    }

    void HandleOnHit()
    {
        if (Player* player = GetCaster()->ToPlayer())
            if (Unit* target = GetHitUnit())
                player->CastSpell(target, SPELL_PALADIN_FORBEARANCE, true);
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_activate_forbearance::CheckForbearance);
        OnHit += SpellHitFn(spell_pal_activate_forbearance::HandleOnHit);
    }
};

// 40470 - Paladin Tier 6 Trinket
class spell_pal_item_t6_trinket : public SpellScriptLoader
{
    public:
        spell_pal_item_t6_trinket() : SpellScriptLoader("spell_pal_item_t6_trinket") { }

        class spell_pal_item_t6_trinket_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_item_t6_trinket_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_ENDURING_LIGHT, SPELL_PALADIN_ENDURING_JUDGEMENT });
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();
                SpellInfo const* spellInfo = eventInfo.GetSpellInfo();
                if (!spellInfo)
                    return;

                uint32 spellId;
                int32 chance;

                // Holy Light & Flash of Light
                if (spellInfo->SpellFamilyFlags[0] & 0xC0000000)
                {
                    spellId = SPELL_PALADIN_ENDURING_LIGHT;
                    chance = 15;
                }
                // Judgements
                else if (spellInfo->SpellFamilyFlags[0] & 0x00800000)
                {
                    spellId = SPELL_PALADIN_ENDURING_JUDGEMENT;
                    chance = 50;
                }
                else
                    return;

                if (roll_chance_i(chance))
                    eventInfo.GetActor()->CastSpell(eventInfo.GetProcTarget(), spellId, true, nullptr, aurEff);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_pal_item_t6_trinket_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_item_t6_trinket_AuraScript();
        }
};

// 20271 - Judgement
/// Updated 4.3.4
class spell_pal_judgement : public SpellScriptLoader
{
    public:
        spell_pal_judgement() : SpellScriptLoader("spell_pal_judgement") { }

        class spell_pal_judgement_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_pal_judgement_SpellScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_JUDGEMENT_DAMAGE });
            }

            void HandleScriptEffect(SpellEffIndex /*effIndex*/)
            {
                uint32 spellId = SPELL_PALADIN_JUDGEMENT_DAMAGE;

                // some seals have SPELL_AURA_DUMMY in EFFECT_2
                Unit::AuraEffectList const& auras = GetCaster()->GetAuraEffectsByType(SPELL_AURA_DUMMY);
                for (Unit::AuraEffectList::const_iterator i = auras.begin(); i != auras.end(); ++i)
                {
                    if ((*i)->GetSpellInfo()->GetSpellSpecific() == SPELL_SPECIFIC_SEAL && (*i)->GetEffIndex() == EFFECT_2)
                    {
                        if (sSpellMgr->GetSpellInfo((*i)->GetAmount()))
                        {
                            spellId = (*i)->GetAmount();
                            break;
                        }
                    }
                }

                GetCaster()->CastSpell(GetHitUnit(), spellId, true);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_pal_judgement_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_pal_judgement_SpellScript();
        }
};

// 633 - Lay on Hands
class spell_pal_lay_on_hands : public SpellScript
{
    PrepareSpellScript(spell_pal_lay_on_hands);

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo(
        {
            SPELL_PALADIN_FORBEARANCE,
            // uncomment when we have serverside only spells
            //SPELL_PALADIN_IMMUNE_SHIELD_MARKER
        }) && spellInfo->ExcludeTargetAuraSpell == SPELL_PALADIN_IMMUNE_SHIELD_MARKER;
    }

    SpellCastResult CheckForbearance()
    {
        Unit* target = GetExplTargetUnit();
        if (!target || target->HasAura(SPELL_PALADIN_FORBEARANCE))
            return SPELL_FAILED_TARGET_AURASTATE;

        return SPELL_CAST_OK;
    }

    void TriggerForbearance()
    {
        if (Unit* target = GetHitUnit())
        {
            GetCaster()->CastSpell(target, SPELL_PALADIN_FORBEARANCE, true);
            GetCaster()->CastSpell(target, SPELL_PALADIN_IMMUNE_SHIELD_MARKER, true);
        }
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_pal_lay_on_hands::CheckForbearance);
        AfterHit += SpellHitFn(spell_pal_lay_on_hands::TriggerForbearance);
    }
};

// 53651 - Light's Beacon - Beacon of Light
class spell_pal_light_s_beacon : public SpellScriptLoader
{
    public:
        spell_pal_light_s_beacon() : SpellScriptLoader("spell_pal_light_s_beacon") { }

        class spell_pal_light_s_beacon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_light_s_beacon_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_BEACON_OF_LIGHT, SPELL_PALADIN_BEACON_OF_LIGHT_HEAL });
            }

            bool CheckProc(ProcEventInfo& eventInfo)
            {
                if (!eventInfo.GetActionTarget())
                    return false;
                if (eventInfo.GetActionTarget()->HasAura(SPELL_PALADIN_BEACON_OF_LIGHT, eventInfo.GetActor()->GetGUID()))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                HealInfo* healInfo = eventInfo.GetHealInfo();
                if (!healInfo || !healInfo->GetHeal())
                    return;

                uint32 heal = CalculatePct(healInfo->GetHeal(), aurEff->GetAmount());

                Unit::AuraList const& auras = GetCaster()->GetSingleCastAuras();
                for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                {
                    if ((*itr)->GetId() == SPELL_PALADIN_BEACON_OF_LIGHT)
                    {
                        std::list<AuraApplication*> applications;
                        (*itr)->GetApplicationList(applications);
                        if (!applications.empty())
                            eventInfo.GetActor()->CastCustomSpell(SPELL_PALADIN_BEACON_OF_LIGHT_HEAL, SPELLVALUE_BASE_POINT0, heal, applications.front()->GetTarget(), true);
                        return;
                    }
                }
            }

            void Register() override
            {
                DoCheckProc += AuraCheckProcFn(spell_pal_light_s_beacon_AuraScript::CheckProc);
                OnEffectProc += AuraEffectProcFn(spell_pal_light_s_beacon_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_light_s_beacon_AuraScript();
        }
};

// 28789 - Holy Power
class spell_pal_t3_6p_bonus : public SpellScriptLoader
{
    public:
        spell_pal_t3_6p_bonus() : SpellScriptLoader("spell_pal_t3_6p_bonus") { }

        class spell_pal_t3_6p_bonus_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_t3_6p_bonus_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo(
                {
                    SPELL_PALADIN_HOLY_POWER_ARMOR,
                    SPELL_PALADIN_HOLY_POWER_ATTACK_POWER,
                    SPELL_PALADIN_HOLY_POWER_SPELL_POWER,
                    SPELL_PALADIN_HOLY_POWER_MP5
                });
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                uint32 spellId;
                Unit* caster = eventInfo.GetActor();
                Unit* target = eventInfo.GetProcTarget();

                switch (target->getClass())
                {
                    case CLASS_PALADIN:
                    case CLASS_PRIEST:
                    case CLASS_SHAMAN:
                    case CLASS_DRUID:
                        spellId = SPELL_PALADIN_HOLY_POWER_MP5;
                        break;
                    case CLASS_MAGE:
                    case CLASS_WARLOCK:
                        spellId = SPELL_PALADIN_HOLY_POWER_SPELL_POWER;
                        break;
                    case CLASS_HUNTER:
                    case CLASS_ROGUE:
                        spellId = SPELL_PALADIN_HOLY_POWER_ATTACK_POWER;
                        break;
                    case CLASS_WARRIOR:
                        spellId = SPELL_PALADIN_HOLY_POWER_ARMOR;
                        break;
                    default:
                        return;
                }

                caster->CastSpell(target, spellId, true, nullptr, aurEff);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_pal_t3_6p_bonus_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_t3_6p_bonus_AuraScript();
        }
};

// 64890 Item - Paladin T8 Holy 2P Bonus
class spell_pal_t8_2p_bonus : public SpellScriptLoader
{
    public:
        spell_pal_t8_2p_bonus() : SpellScriptLoader("spell_pal_t8_2p_bonus") { }

        class spell_pal_t8_2p_bonus_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_pal_t8_2p_bonus_AuraScript);

            bool Validate(SpellInfo const* /*spellInfo*/) override
            {
                return ValidateSpellInfo({ SPELL_PALADIN_HOLY_MENDING });
            }

            void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                HealInfo* healInfo = eventInfo.GetHealInfo();
                if (!healInfo || !healInfo->GetHeal())
                    return;

                Unit* caster = eventInfo.GetActor();
                Unit* target = eventInfo.GetProcTarget();

                SpellInfo const* spellInfo = sSpellMgr->AssertSpellInfo(SPELL_PALADIN_HOLY_MENDING);
                int32 amount = CalculatePct(static_cast<int32>(healInfo->GetHeal()), aurEff->GetAmount());
                amount /= spellInfo->GetMaxTicks(DIFFICULTY_NONE);
                // Add remaining ticks to damage done
                amount += target->GetRemainingPeriodicAmount(caster->GetGUID(), SPELL_PALADIN_HOLY_MENDING, SPELL_AURA_PERIODIC_HEAL);

                caster->CastCustomSpell(SPELL_PALADIN_HOLY_MENDING, SPELLVALUE_BASE_POINT0, amount, target, true, nullptr, aurEff);
            }

            void Register() override
            {
                OnEffectProc += AuraEffectProcFn(spell_pal_t8_2p_bonus_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_pal_t8_2p_bonus_AuraScript();
        }
};

/*######
## AddSC
######*/
void AddSC_paladin_spell_scripts()
{
    RegisterSpellScript(spell_pal_crusader_strike);
    RegisterSpellScript(spell_pal_flash_of_light);
    RegisterSpellScript(spell_pal_judgment);
    RegisterSpellScript(spell_pal_templar_s_verdict);
    RegisterAuraScript(spell_pal_shield_of_vengeance);
    RegisterSpellScript(spell_pal_divine_storm);
    /**/
    RegisterSpellScript(spell_pal_holy_shock);
    RegisterSpellScript(spell_pal_beacon_of_faith);
    RegisterSpellScript(spell_pal_beacon_of_light);
    RegisterSpellScript(spell_pal_beacon_of_virtue);
    RegisterAuraScript(spell_pal_beacon_of_light_aura);
    RegisterAuraScript(spell_pal_beacon_of_light_proc);
    new spell_pal_light_of_dawn();
    new spell_pal_light_of_dawn_trigger();
    RegisterAuraScript(spell_pal_infusion_of_light);
    /**/
    new spell_pal_blessing_of_faith();
    RegisterSpellScript(spell_pal_blessing_of_protection);
    RegisterSpellScript(spell_pal_blinding_light);
    RegisterSpellScript(spell_pal_divine_shield);
    new spell_pal_divine_steed();
    new spell_pal_glyph_of_holy_light();
    new spell_pal_grand_crusader();
    new spell_pal_hand_of_sacrifice();
    new spell_pal_item_healing_discount();
    RegisterSpellScript(spell_pal_activate_forbearance); // activate forbearance
    new spell_pal_item_t6_trinket();
    new spell_pal_judgement();
    RegisterSpellScript(spell_pal_lay_on_hands);
    new spell_pal_light_s_beacon();
    new spell_pal_t3_6p_bonus();
    new spell_pal_t8_2p_bonus();
}
