/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2011-2016 ArkCORE <http://www.arkania.net/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

/**********************
**Lancelombre du Temple
***********************/

#define spell_lance_de_lombre 89555 // Lance_de_L'ombre
#define spell_pacte_des_tenebres 89560 // Pacte_des_Ténèbres

class npc_lancelombre_du_temple : public CreatureScript
{
public:
       npc_lancelombre_du_temple() : CreatureScript("npc_lancelombre_du_temple") { }
       
       struct npc_lancelombre_du_templeAI : public ScriptedAI
       {
          npc_lancelombre_du_templeAI(Creature *c) : ScriptedAI(c) { }
          
          uint32 lance_de_lombre;
          uint32 pacte_des_tenebres;
          
          void Reset()
          {
          lance_de_lombre = 20000;
          pacte_des_tenebres = 25000;
          }
          
          void UpdateAI(uint32 diff)
          {
            if (!UpdateVictim())
            return;
            
            if (lance_de_lombre<= diff)
            {
            DoCast(me, spell_lance_de_lombre);
            lance_de_lombre = 20000;
            } else lance_de_lombre -= diff;
            
            if (pacte_des_tenebres<= diff)
            {
            DoCast(me, spell_pacte_des_tenebres);
            pacte_des_tenebres = 25000;
            } else pacte_des_tenebres -= diff;
            
            DoMeleeAttackIfReady();
          }
       };
       
      CreatureAI* GetAI(Creature* creature) const
      {
           return new npc_lancelombre_du_templeAI(creature);
      }
};

/**************************
**Traqueur Veloce du Temple
***************************/

#define spell_fleches_multiples 84836 // Flèches_Multiples
#define spell_tir 83877 // Tir
#define spell_tir_charge 94791 // Tir_Chargé

class npc_traqueur_veloce_du_temple : public CreatureScript
{
public:
      npc_traqueur_veloce_du_temple() : CreatureScript("npc_traqueur_veloce_du_temple") { }
      
      struct npc_traqueur_veloce_du_templeAI : public ScriptedAI
      {
         npc_traqueur_veloce_du_templeAI(Creature *c) : ScriptedAI(c) { }

         uint32 fleches_multiples;
         uint32 tir;
         uint32 tir_charge;
         
         void Reset()
         {
         fleches_multiples = 12000;
         tir = 2500;
         tir_charge = 19000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (fleches_multiples<= diff)
            {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
            DoCast(target, spell_fleches_multiples);
            fleches_multiples = 12000;
            } else fleches_multiples -= diff;
            
            if (tir<= diff)
            {
            DoCastVictim(spell_tir);
            tir = 2500;
            } else tir -= diff;
            
            if (tir_charge<= diff)
            {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_tir_charge);
            tir_charge = 19000;
            } else tir_charge -= diff;
            
             DoMeleeAttackIfReady();
         }
      };
      
      CreatureAI* GetAI(Creature* creature) const
      {
           return new npc_traqueur_veloce_du_templeAI(creature);
      }       
};      

/***************************
**Lanceur de Runes du Temple
****************************/

#define spell_enchainement_runique 91806 // Enchainement_Runique
#define spell_malediction_du_lanceur_de_runes 95181 // Malédiction_du_Lanceur_de_Runes

class npc_lanceur_de_runes_du_temple : public CreatureScript
{
public:
      npc_lanceur_de_runes_du_temple() : CreatureScript("npc_lanceur_de_runes_du_temple") { }
      
      struct npc_lanceur_de_runes_du_templeAI : public ScriptedAI
      {
         npc_lanceur_de_runes_du_templeAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 enchainement_runique;
         uint32 malediction_du_lanceur_de_runes;
         
         void Reset()
         {
         enchainement_runique = 10000;
         malediction_du_lanceur_de_runes = 15000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (enchainement_runique<= diff)
            {
            DoCastVictim(spell_enchainement_runique);
            enchainement_runique = 10000;
            } else enchainement_runique -= diff;
            
            if (malediction_du_lanceur_de_runes<= diff)
            {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM,0,100,true), spell_malediction_du_lanceur_de_runes);
            malediction_du_lanceur_de_runes = 15000;
            } else malediction_du_lanceur_de_runes -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
      
      CreatureAI* GetAI(Creature* creature) const
      {
           return new npc_lanceur_de_runes_du_templeAI(creature);
      }
};

/*********************
**Sculptefeu du Temple
**********************/

#define spell_barriere_de_la_fournaise 89542 // Barriere_de_la_Fournaise
#define spell_boule_de_feu 89854 // Boule_de_Feu
#define spell_eruption_flamboyante 89547 // Eruption_Flamboyante
#define spell_meteore 90023 // Météore

class npc_sculptefeu_du_temple : public CreatureScript
{
public:
      npc_sculptefeu_du_temple() : CreatureScript("npc_sculptefeu_du_temple") { }
      
      struct npc_sculptefeu_du_templeAI : public ScriptedAI
      {
         npc_sculptefeu_du_templeAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 barriere_de_la_fournaise;
         uint32 boule_de_feu;
         uint32 eruption_flamboyante;
         uint32 meteore;
         
         void Reset()
         {
         barriere_de_la_fournaise = 45000;
         boule_de_feu = 4000;
         eruption_flamboyante = 60000;
         meteore = 30000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (barriere_de_la_fournaise<= diff)
            {
            DoCast(me, spell_barriere_de_la_fournaise);
            barriere_de_la_fournaise = 45000;
            } else barriere_de_la_fournaise -= diff;
            
            if (boule_de_feu<= diff)
            {
            DoCastVictim(spell_boule_de_feu);
            boule_de_feu = 4000;
            } else boule_de_feu -= diff;
            
            if (eruption_flamboyante<= diff)
            {
            DoCast(me, spell_eruption_flamboyante);
            eruption_flamboyante = 60000;
            } else eruption_flamboyante -= diff;
            
            if (meteore<= diff)
            {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
            DoCast(target, spell_meteore);
            meteore = 30000;
            } else meteore -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
    
    CreatureAI* GetAI(Creature* creature) const
    {
           return new npc_sculptefeu_du_templeAI(creature);
    }
    
};

/*******************
**Scarabée Caustique
********************/

#define spell_attaque_a_la_lame_dentelee 74542 // Attaque_a_la_Lame_Dentelée
#define spell_projection_corrosive 89857 // Projection_Corrosive

class npc_scarabee_caustique : public CreatureScript
{
public:
      npc_scarabee_caustique() : CreatureScript("npc_scarabee_caustique") { }
      
      struct npc_scarabee_caustiqueAI : public ScriptedAI
      {
         npc_scarabee_caustiqueAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 attaque_a_la_lame_dentelee;
         uint32 projection_corrosive;
         
         void Reset()
         {
         attaque_a_la_lame_dentelee = 15000;
         projection_corrosive = 10000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (attaque_a_la_lame_dentelee<= diff)
            {
            DoCastVictim(spell_attaque_a_la_lame_dentelee);
            attaque_a_la_lame_dentelee = 15000;
            } else attaque_a_la_lame_dentelee -= diff;
            
            if (projection_corrosive<= diff)
            {
            DoCast(me, spell_projection_corrosive);
            projection_corrosive = 10000;
            } else projection_corrosive -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
    
    CreatureAI* GetAI(Creature* creature) const
    {
            return new npc_scarabee_caustiqueAI(creature);
    }
    
};

/******************
**Glisseur Venimeux
*******************/

#define spell_afflux 75158 // Afflux
#define spell_toxine RAND(89859,89856) // Toxine

class npc_glisseur_venimeux : public CreatureScript
{
public:
      npc_glisseur_venimeux() : CreatureScript("npc_glisseur_venimeux") { }
      
      struct npc_glisseur_venimeuxAI : public ScriptedAI
      {
         npc_glisseur_venimeuxAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 afflux;
         uint32 toxine;
         
         void Reset()
         {
         afflux = 15000;
         toxine = 10000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (afflux<= diff)
            {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
            DoCast(target, spell_afflux);
            afflux = 15000;
            } else afflux -= diff;
            
            if (toxine<= diff)
            {
            DoCastVictim(spell_toxine);
            toxine = 10000;
            } else toxine -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
      
    CreatureAI* GetAI(Creature* creature) const
    {
           return new npc_glisseur_venimeuxAI(creature);
    }
    
};

/*********************
**Horreur Os-Poussière
**********************/

#define spell_choc 75453 // Choc

class npc_horreur_os_poussiere : public CreatureScript
{
public:
      npc_horreur_os_poussiere() : CreatureScript("npc_horreur_os_poussiere") { }
      
      struct npc_horreur_os_poussiereAI : public ScriptedAI
      {
         npc_horreur_os_poussiereAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 choc;
         
         void Reset()
         {
         choc = 5000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (choc<= diff)
            {
            DoCastVictim(spell_choc);
            choc = 5000;
            } else choc -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
    
    CreatureAI* GetAI(Creature* creature) const
    {
            return new npc_horreur_os_poussiereAI(creature);
    }

};

/*************************
**Tourmenteur Os-Poussière
**************************/

#define spell_trait_de_lombre 89855 // Trait_de_Lombre
#define spell_malediction_depuisement 90006 // Malédiction_d'Epuisement

class npc_tourmenteur_os_poussiere : public CreatureScript
{
public:
      npc_tourmenteur_os_poussiere() : CreatureScript("npc_tourmenteur_os_poussiere") { }
      
      struct npc_tourmenteur_os_poussiereAI : public ScriptedAI
      {
         npc_tourmenteur_os_poussiereAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 trait_de_lombre;
         uint32 malediction_depuisement;
         
         void Reset()
         {
         trait_de_lombre = 6000;
         malediction_depuisement = 10000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (trait_de_lombre<= diff)
            {
            DoCastVictim(spell_trait_de_lombre);
            trait_de_lombre = 6000;
            } else trait_de_lombre -= diff;
            
            if (malediction_depuisement<= diff)
            {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_malediction_depuisement);
            malediction_depuisement = 10000;
            } else malediction_depuisement -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
      
    CreatureAI* GetAI(Creature* creature) const
    {
           return new npc_tourmenteur_os_poussiereAI(creature);
    }
    
};

/******************
**Chercheur du Vide
*******************/

#define spell_prison_anti_magie 76903 // Prison_Anti_Magie
#define spell_salve_de_traits_de_lombre 89846 // Salve_de_Traits_de_l'Ombre

class npc_chercheur_du_vide : public CreatureScript
{
public: 
     npc_chercheur_du_vide() : CreatureScript("npc_chercheur_du_vide") { }
     
     struct npc_chercheur_du_videAI : public ScriptedAI
     {
        npc_chercheur_du_videAI(Creature *c) : ScriptedAI(c) { }
        
        uint32 prison_anti_magie;
        uint32 salve_de_traits_de_lombre;
        
        void Reset()
        {
        prison_anti_magie = 30000;
        salve_de_traits_de_lombre = 12000;
        }
        
        void UpdateAI(uint32 diff)
        {
           if (!UpdateVictim())
           return;
           
           if (prison_anti_magie<= diff)
           {
           DoCast(SelectTarget(SELECT_TARGET_RANDOM,1,100,true), spell_prison_anti_magie);
           prison_anti_magie = 30000;
           } else prison_anti_magie -= diff;
           
           if (salve_de_traits_de_lombre<= diff)
           {
           DoCast(me, spell_salve_de_traits_de_lombre);
           salve_de_traits_de_lombre = 12000;
           } else salve_de_traits_de_lombre -= diff;
           
           DoMeleeAttackIfReady();
        }
     };
    
    CreatureAI* GetAI(Creature* creature) const
    {
          return new npc_chercheur_du_videAI(creature);
    }
    
};
    
/*****************
**Seigneur du Vide
******************/

#define spell_explosion_de_vide 89847 // Explosion_de_Vide
#define spell_salve_de_traits_de_lombre 89846 // Salve_de_Traits_de_l'Ombre
#define spell_infusion_de_vide 77470 // A mettre en place prochainement

class npc_seigneur_du_vide : public CreatureScript
{
public:
      npc_seigneur_du_vide() : CreatureScript("npc_seigneur_du_vide") { }
      
      struct npc_seigneur_du_videAI : public ScriptedAI
      {
         npc_seigneur_du_videAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 explosion_de_vide;
         uint32 salve_de_traits_de_lombre;
         
         void Reset()
         {
         explosion_de_vide = 30000;
         salve_de_traits_de_lombre = 16000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (explosion_de_vide<= diff)
            {
            DoCast(me, spell_explosion_de_vide);
            explosion_de_vide = 30000;
            } else explosion_de_vide -= diff;
            
            if (salve_de_traits_de_lombre<= diff)
            {
            DoCast(me, spell_salve_de_traits_de_lombre);
            salve_de_traits_de_lombre = 16000;
            } else salve_de_traits_de_lombre -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
            
    CreatureAI* GetAI(Creature* creature) const
    {
           return new npc_seigneur_du_videAI(creature);
    }
    
};

/******************
**Anomalie Spatiale
*******************/

#define spell_jaillissement_des_arcanes 89862 // Jaillissement_des_Arcanes

class npc_anomalie_spatiale : public CreatureScript
{
public:
     npc_anomalie_spatiale() : CreatureScript("npc_anomalie_spatiale") { }
     
     struct npc_anomalie_spatialeAI : public ScriptedAI
     {
        npc_anomalie_spatialeAI(Creature *c) : ScriptedAI(c) { }
        
        uint32 jaillissement_des_arcanes;
        
        void Reset()
        {
        jaillissement_des_arcanes = 15000;
        }
        
        void UpdateAI(uint32 diff)
        {
             if (!UpdateVictim())
             return;
             
             if (jaillissement_des_arcanes<= diff)
             {
             DoCast(me, spell_jaillissement_des_arcanes);
             jaillissement_des_arcanes = 15000;
             } else jaillissement_des_arcanes -= diff;
             
              DoMeleeAttackIfReady();
        }
     };
    
    CreatureAI* GetAI(Creature* creature) const
    {
            return new npc_anomalie_spatialeAI(creature);
    }
        
};

/******************
**Animateur de Flux
*******************/

#define spell_barrage_des_arcanes 89863 // Barrage_des_Arcanes

class npc_animateur_de_flux : public CreatureScript
{
public:
     npc_animateur_de_flux() : CreatureScript("npc_animateur_de_flux") { }
     
     struct npc_animateur_de_fluxAI : public ScriptedAI
     {
        npc_animateur_de_fluxAI(Creature *c) : ScriptedAI(c) { }
        
        uint32 barrage_des_arcanes;
        
        void Reset()
        {
        barrage_des_arcanes = 8000;
        }
        
        void UpdateAI(uint32 diff)
        {
           if (!UpdateVictim())
           return;
           
           if (barrage_des_arcanes<= diff)
           {
           if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
           DoCast(pTarget, spell_barrage_des_arcanes);
           barrage_des_arcanes = 8000;
           } else barrage_des_arcanes -= diff;
           
           DoMeleeAttackIfReady();
        }
     };
     
    CreatureAI* GetAI(Creature* creature) const
    {
          return new npc_animateur_de_fluxAI(creature);
    }
    
};

/********************
**Serviteur Solegrâce
*********************/

#define spell_disperser 88097 // A mettre en place plus tard
#define spell_dispersion_des_flammes 89852 // Dispersion_des_Flammes
#define spell_flammes_incendiaires 89849 // Flammes_Incendiaires

class npc_serviteur_solegrace : public CreatureScript
{
public :
    npc_serviteur_solegrace() : CreatureScript("npc_serviteur_solegrace") { }
      
    struct npc_serviteur_solegraceAI : public ScriptedAI
    {
        npc_serviteur_solegraceAI(Creature *c) : ScriptedAI(c) { }
          
        uint32 dispersion_des_flammes;
        uint32 flammes_incendiaires;
          
        void Reset()
        {
        dispersion_des_flammes = 15000;
        flammes_incendiaires = 10000;
        }
          
        void UpdateAI(uint32 diff)
        {
              if (!UpdateVictim())
              return;
              
              if (dispersion_des_flammes<= diff)
              {
              DoCast(me, dispersion_des_flammes);
              dispersion_des_flammes = 15000;
              } else dispersion_des_flammes -= diff;
              
              if (flammes_incendiaires<= diff)
              {
              if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
              DoCast(pTarget, spell_flammes_incendiaires);
              flammes_incendiaires = 10000;
              } else flammes_incendiaires -= diff;
              
              DoMeleeAttackIfReady();
        }
    };
      
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_serviteur_solegraceAI(creature);
    }
    
};

/**************
**Fée Solegrace
***************/

#define spell_disperser 88097 // A mettre en place plus tard
#define spell_pyrogenie 76158 // Pyrogénie
#define spell_dispersion_des_flammes 89852 // Dispersion_des_Flammes
#define spell_flammes_incendiaires 89849 // Flammes_Incendiaires

class npc_fee_solegrace : public CreatureScript
{
public :
    npc_fee_solegrace() : CreatureScript("npc_fee_solegrace") { }
      
    struct npc_fee_solegraceAI : public ScriptedAI
    {
        npc_fee_solegraceAI(Creature *c) : ScriptedAI(c) { }
         
        uint32 pyrogenie;
        uint32 dispersion_des_flammes;
        uint32 flammes_incendiaires;
         
        void Reset()
        {
        pyrogenie = 30000;
        dispersion_des_flammes = 20000;
        flammes_incendiaires = 15000;
        }
         
        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            return;
            
            if (pyrogenie<= diff)
            {
            DoCast(me, spell_pyrogenie);
            pyrogenie = 30000;
            } else pyrogenie -= diff;
            
            if (dispersion_des_flammes<= diff)
            {
            DoCast(me, dispersion_des_flammes);
            dispersion_des_flammes = 20000;
            } else dispersion_des_flammes -= diff;
              
            if (flammes_incendiaires<= diff)
            {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_flammes_incendiaires);
            flammes_incendiaires = 15000;
            } else flammes_incendiaires -= diff;
            
            DoMeleeAttackIfReady();
        }
    };
             
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fee_solegraceAI(creature);
    }            
    
};

/*********************
**Petite Fée Solegrace
**********************/

#define spell_pyrogenie 76158 // Pyrogénie
#define spell_dispersion_des_flammes 89852 // Dispersion_des_Flammes
#define spell_flammes_incendiaires 89849 // Flammes_Incendiaires

class npc_petite_fee_solegrace : public CreatureScript
{
public :
    npc_petite_fee_solegrace() : CreatureScript("npc_petite_fee_solegrace") { }

    struct npc_petite_fee_solegraceAI : public ScriptedAI
    {
        npc_petite_fee_solegraceAI(Creature *c) : ScriptedAI(c) { }

        uint32 pyrogenie;
        uint32 dispersion_des_flammes;
        uint32 flammes_incendiaires;

        void Reset()
        {
        pyrogenie = 30000;
        dispersion_des_flammes = 20000;
        flammes_incendiaires = 15000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            return;

            if (pyrogenie<= diff)
            {
            DoCast(me, spell_pyrogenie);
            pyrogenie = 30000;
            } else pyrogenie -= diff;

            if (dispersion_des_flammes<= diff)
            {
            DoCast(me, dispersion_des_flammes);
            dispersion_des_flammes = 20000;
            } else dispersion_des_flammes -= diff;

            if (flammes_incendiaires<= diff)
            {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_flammes_incendiaires);
            flammes_incendiaires = 15000;
            } else flammes_incendiaires -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_petite_fee_solegraceAI(creature);
    }

};

/***********************
**Porte Parole Solegrace
************************/

#define spell_pietinement_reverberant 89851 // Piétinement_Réverbérant
#define spell_tempete_de_feu 73861 // Tempête_de_Feu

class npc_porte_parole_solegrace : public CreatureScript
{
public:

      npc_porte_parole_solegrace() : CreatureScript("npc_porte_parole_solegrace") { }
      
      struct npc_porte_parole_solegraceAI : public ScriptedAI
      {
         npc_porte_parole_solegraceAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 pietinement_reverberant;
         uint32 tempete_de_feu;
         
         void Reset()
         {
         pietinement_reverberant = 25000;
         tempete_de_feu = 13000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;
            
            if (pietinement_reverberant<= diff)
            {
            DoCastVictim(spell_pietinement_reverberant);
            pietinement_reverberant = 25000;
            } else pietinement_reverberant -= diff;
            
            if (tempete_de_feu<= diff)
            {
            DoCast(SelectTarget(SELECT_TARGET_RANDOM,1,100,true), spell_tempete_de_feu);
            tempete_de_feu = 13000;
            } else tempete_de_feu -= diff;
            
            DoMeleeAttackIfReady();
         }
      };
    
    CreatureAI* GetAI(Creature* creature) const
    {
            return new npc_porte_parole_solegraceAI(creature);
    }
    
};

/***************************
**Nymphe Gardienne de la Vie
****************************/

#define spell_shoot 75958 // Tir
#define spell_tir_enchevetrant 89865 // Tir_Enchevetrant
#define spell_tranquillite 75940 // Tranquillité



class npc_nymphe_gardienne : public CreatureScript
{
public :

      npc_nymphe_gardienne() : CreatureScript("npc_nymphe_gardienne") { }
      
      struct npc_nymphe_gardienneAI : public ScriptedAI
      {
          npc_nymphe_gardienneAI(Creature *c) : ScriptedAI(c) { }
          
          uint32 tir;
          uint32 tir_enchevetrant;
          uint32 tranquillite;
          
          void Reset()
          {
          tir = 4000;
          tir_enchevetrant = 22000;
          tranquillite = 35000;
          }
          
          void UpdateAI(uint32 diff)
          {
             if (!UpdateVictim())
             return;
             
             if (tir<= diff)
             {
             DoCastVictim(spell_shoot);
             tir = 4000;
             } else tir -= diff;
             
             if (tir_enchevetrant<= diff)
             {
             if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
             DoCast(target, spell_tir_enchevetrant);
             tir_enchevetrant = 22000;
             } else tir_enchevetrant -= diff;
             
             if (tranquillite<= diff)
             {
             DoCast(me, spell_tranquillite);
             tranquillite = 35000;
             } else tranquillite -= diff;
             
             DoMeleeAttackIfReady();
           }
      };
      
    CreatureAI* GetAI(Creature* creature) const
    {
            return new npc_nymphe_gardienneAI(creature);
    }
    
};

/**************
**Liane Vivante
***************/

#define spell_souffle_de_spores 89864 // Souffle_de_Spores

class npc_liane_vivante : public CreatureScript
{
public :
      npc_liane_vivante() : CreatureScript("npc_liane_vivante") { }
      
      struct npc_liane_vivanteAI : public ScriptedAI
      {
         npc_liane_vivanteAI(Creature *c) : ScriptedAI(c) { }
         
         uint32 souffle_de_spores;
         
         void Reset()
         {
         souffle_de_spores = 8000;
         }
         
         void UpdateAI(uint32 diff)
         {
            if (!UpdateVictim())
            return;

            if (souffle_de_spores<= diff)
            {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
            DoCast(pTarget, spell_souffle_de_spores);
            souffle_de_spores = 8000;
            } else souffle_de_spores -= diff;
            
            DoMeleeAttackIfReady();
         }
      };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_liane_vivanteAI(creature);
    }           

};

/******************
**Spore en Bourgeon
*******************/

#define spell_nuage_de_spores 75701 // Nuage_de_Spores
#define spell_spores_nauseabondes 89889 // Spores_Nauséabondes

class npc_spore_en_bourgeon : public CreatureScript
{
public :
    npc_spore_en_bourgeon() : CreatureScript("npc_spore_en_bourgeon") { }
      
    struct npc_spore_en_bourgeonAI : public ScriptedAI
    {
        npc_spore_en_bourgeonAI(Creature *c) : ScriptedAI(c) { }

        uint32 nuage_de_spores;
        uint32 spores_nauseabondes;
         
        void Reset()
        {
            nuage_de_spores = 5000;
            spores_nauseabondes = 10000;
        }
         
        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
            return;
            
            if (nuage_de_spores<= diff)
            {
            DoCast(me, spell_nuage_de_spores);
            nuage_de_spores = 5000;
            } else nuage_de_spores -= diff;
            
            if (spores_nauseabondes<= diff)
            {
            DoCast(me, spell_spores_nauseabondes);
            spores_nauseabondes = 10000;
            } else spores_nauseabondes -= diff;
            
            DoMeleeAttackIfReady();
        }
    };
        
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spore_en_bourgeonAI(creature);
    }           

};

void AddSC_npc_trash_sdo()
{
    new npc_lancelombre_du_temple();
    new npc_traqueur_veloce_du_temple();
    new npc_lanceur_de_runes_du_temple();
    new npc_sculptefeu_du_temple();
    new npc_scarabee_caustique();
    new npc_glisseur_venimeux();
    new npc_horreur_os_poussiere();
    new npc_tourmenteur_os_poussiere();
    //new npc_chercheur_du_vide();
    new npc_seigneur_du_vide();
    new npc_anomalie_spatiale();
    new npc_animateur_de_flux();
    new npc_serviteur_solegrace();
    new npc_fee_solegrace();
    new npc_petite_fee_solegrace();
    new npc_porte_parole_solegrace();
    new npc_nymphe_gardienne();
    new npc_liane_vivante();
    new npc_spore_en_bourgeon();
}