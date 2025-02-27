#include <ultra64.h>
#include "constants.h"
#include "game/file.h"
#include "game/stubs/game_175f50.h"
#include "bss.h"
#include "lib/lib_074f0.h"
#include "lib/dma.h"
#include "lib/memory.h"
#include "lib/rng.h"
#include "data.h"
#include "types.h"

extern void *_file_bg_sev_seg;
extern void *_file_bg_silo_seg;
extern void *_file_bg_stat_seg;
extern void *_file_bg_arec_seg;
extern void *_file_bg_arch_seg;
extern void *_file_bg_tra_seg;
extern void *_file_bg_dest_seg;
extern void *_file_bg_sevb_seg;
extern void *_file_bg_azt_seg;
extern void *_file_bg_pete_seg;
extern void *_file_bg_depo_seg;
extern void *_file_bg_ref_seg;
extern void *_file_bg_cryp_seg;
extern void *_file_bg_dam_seg;
extern void *_file_bg_ark_seg;
extern void *_file_bg_run_seg;
extern void *_file_bg_sevx_seg;
extern void *_file_bg_jun_seg;
extern void *_file_bg_dish_seg;
extern void *_file_bg_cave_seg;
extern void *_file_bg_cat_seg;
extern void *_file_bg_crad_seg;
extern void *_file_bg_sho_seg;
extern void *_file_bg_eld_seg;
extern void *_file_bg_imp_seg;
extern void *_file_bg_ash_seg;
extern void *_file_bg_lue_seg;
extern void *_file_bg_ame_seg;
extern void *_file_bg_rit_seg;
extern void *_file_bg_oat_seg;
extern void *_file_bg_ear_seg;
extern void *_file_bg_lee_seg;
extern void *_file_bg_lip_seg;
extern void *_file_bg_len_seg;
extern void *_file_bg_wax_seg;
extern void *_file_bg_pam_seg;
extern void *_file_bg_uff_seg;
extern void *_file_bg_old_seg;
extern void *_file_bg_ate_seg;
extern void *_file_bg_lam_seg;
extern void *_file_bg_mp1_seg;
extern void *_file_bg_mp2_seg;
extern void *_file_bg_mp3_seg;
extern void *_file_bg_mp4_seg;
extern void *_file_bg_mp5_seg;
extern void *_file_bg_mp6_seg;
extern void *_file_bg_mp7_seg;
extern void *_file_bg_mp8_seg;
extern void *_file_bg_mp9_seg;
extern void *_file_bg_mp10_seg;
extern void *_file_bg_mp11_seg;
extern void *_file_bg_mp12_seg;
extern void *_file_bg_mp13_seg;
extern void *_file_bg_mp14_seg;
extern void *_file_bg_mp15_seg;
extern void *_file_bg_mp16_seg;
extern void *_file_bg_mp17_seg;
extern void *_file_bg_mp18_seg;
extern void *_file_bg_mp19_seg;
extern void *_file_bg_mp20_seg;
extern void *_file_ob_mid_seg;
extern void *_file_Ca51guardZ;
extern void *_file_Carea51guardZ;
extern void *_file_CcarringtonZ;
extern void *_file_CcassandraZ;
extern void *_file_Cdark_combatZ;
extern void *_file_Cdark_frockZ;
extern void *_file_Cdark_trenchZ;
extern void *_file_CddshockZ;
extern void *_file_Cdd_secguardZ;
extern void *_file_CdjbondZ;
extern void *_file_CdrcarrollZ;
extern void *_file_CelvisZ;
extern void *_file_Celvis1Z;
extern void *_file_CeyespyZ;
extern void *_file_Cfem_guardZ;
extern void *_file_ClabtechZ;
extern void *_file_CmrblondeZ;
extern void *_file_CofficeworkerZ;
extern void *_file_Cofficeworker2Z;
extern void *_file_CoverallZ;
extern void *_file_CsecretaryZ;
extern void *_file_CskedarZ;
extern void *_file_CstripesZ;
extern void *_file_CtestchrZ;
extern void *_file_CthekingZ;
extern void *_file_CtrentZ;
extern void *_file_GcartblueZ;
extern void *_file_GcartridgeZ;
extern void *_file_GcartrifleZ;
extern void *_file_GcartshellZ;
extern void *_file_GjoypadZ;
extern void *_file_Pa51_crate1Z;
extern void *_file_Pa51_crate2Z;
extern void *_file_Pa51_crate3Z;
extern void *_file_Pa51_exp1Z;
extern void *_file_Pa51_exp2Z;
extern void *_file_Pa51_horiz_door_botZ;
extern void *_file_Pa51_horiz_door_glZ;
extern void *_file_Pa51_horiz_door_secretZ;
extern void *_file_Pa51_horiz_door_topZ;
extern void *_file_Pa51_lift_controlZ;
extern void *_file_Pa51_lift_hangarZ;
extern void *_file_Pa51_lift_storeZ;
extern void *_file_Pa51_lift_thinwallZ;
extern void *_file_Pa51_unexp1Z;
extern void *_file_Pa51_unexp2Z;
extern void *_file_Pa51_unexp3Z;
extern void *_file_Pa51_vert_door_leftZ;
extern void *_file_Pa51_vert_door_rightZ;
extern void *_file_Pa51_vert_door_stZ;
extern void *_file_Pa51boardZ;
extern void *_file_Pa51chairZ;
extern void *_file_Pa51deskentZ;
extern void *_file_Pa51divideZ;
extern void *_file_Pa51screenZ;
extern void *_file_Pa51tableZ;
extern void *_file_Pa51trolleyZ;
extern void *_file_Pa51wastebinZ;
extern void *_file_Paivillabot1Z;
extern void *_file_Paivillabot2Z;
extern void *_file_Paivillabot3Z;
extern void *_file_Paivilladoor1Z;
extern void *_file_Paivilladoor2aZ;
extern void *_file_Paivilladoor4Z;
extern void *_file_PaivillawindmillZ;
extern void *_file_Pal_airlockZ;
extern void *_file_Pal_dockliftZ;
extern void *_file_Paldoor_lZ;
extern void *_file_Paldoor_rZ;
extern void *_file_Pborg_crateZ;
extern void *_file_PcaseZ;
extern void *_file_Pch_shutter1Z;
extern void *_file_PchrbriefcaseZ;
extern void *_file_PchrbugZ;
extern void *_file_PchrdatathiefZ;
extern void *_file_Pcryptdoor1bZ;
extern void *_file_Pdd_ac_expZ;
extern void *_file_Pdd_ac_unexpZ;
extern void *_file_Pdd_acbot_expZ;
extern void *_file_Pdd_acbot_unexpZ;
extern void *_file_Pdd_bannerZ;
extern void *_file_Pdd_chairZ;
extern void *_file_Pdd_decodoorZ;
extern void *_file_Pdd_deskZ;
extern void *_file_Pdd_fanroofZ;
extern void *_file_Pdd_fanwallZ;
extern void *_file_Pdd_hovcabZ;
extern void *_file_Pdd_hovcarZ;
extern void *_file_Pdd_hovcopZ;
extern void *_file_Pdd_hovercopterZ;
extern void *_file_Pdd_hovmotoZ;
extern void *_file_Pdd_hovtruckZ;
extern void *_file_Pdd_lab_cautionZ;
extern void *_file_Pdd_lab_cautiontopZ;
extern void *_file_Pdd_lab_door_bsZ;
extern void *_file_Pdd_lab_door_secZ;
extern void *_file_Pdd_lab_door_windZ;
extern void *_file_Pdd_lab_hazardZ;
extern void *_file_Pdd_lab_restrictedZ;
extern void *_file_Pdd_lab_sector2botZ;
extern void *_file_Pdd_lab_sector2topZ;
extern void *_file_Pdd_lab_sector3Z;
extern void *_file_Pdd_lab_sector3topZ;
extern void *_file_Pdd_lab_sector3windZ;
extern void *_file_Pdd_lab_sector4topZ;
extern void *_file_Pdd_liftdoorZ;
extern void *_file_Pdd_liftrZ;
extern void *_file_Pdd_officedoorZ;
extern void *_file_Pdd_plantrubberZ;
extern void *_file_Pdd_plantspiderZ;
extern void *_file_Pdd_plantspikeZ;
extern void *_file_Pdd_redarmZ;
extern void *_file_Pdd_redsofaZ;
extern void *_file_Pdd_secretdoorZ;
extern void *_file_Pdd_secretdoor2Z;
extern void *_file_Pdd_servicedoorZ;
extern void *_file_Pdd_stonedeskZ;
extern void *_file_Pdd_vertblindZ;
extern void *_file_Pdd_winddoorZ;
extern void *_file_Pdd_windowZ;
extern void *_file_PddjumpshipZ;
extern void *_file_Pdoor1a_G5Z;
extern void *_file_Pdoor1atri_G5Z;
extern void *_file_Pdoor1b_G5Z;
extern void *_file_Pdoor2_G5Z;
extern void *_file_Pdoor2a_G5Z;
extern void *_file_Pdoor4a_G5Z;
extern void *_file_Pdoor4b_G5Z;
extern void *_file_Pdoor_rollertrainZ;
extern void *_file_PdoorconsoleZ;
extern void *_file_Pdr_caroll_doorZ;
extern void *_file_Pdr_caroll_door_baseZ;
extern void *_file_Pdr_caroll_door_bleftZ;
extern void *_file_Pdr_caroll_door_bmainZ;
extern void *_file_Pdr_caroll_door_brightZ;
extern void *_file_Pdr_caroll_door_leftZ;
extern void *_file_Pdr_caroll_door_mainZ;
extern void *_file_Pdr_caroll_door_rightZ;
extern void *_file_PdropshipZ;
extern void *_file_PdumpsterZ;
extern void *_file_PexplosionbitZ;
extern void *_file_PflagZ;
extern void *_file_Pg5_escdoordownZ;
extern void *_file_Pg5_escdoordownboomZ;
extern void *_file_Pg5_escdoorupZ;
extern void *_file_Pg5_escdoorupboomZ;
extern void *_file_Pg5_mainframeZ;
extern void *_file_Pg5safedoorZ;
extern void *_file_Pg5carliftdoorZ;
extern void *_file_PgoldeneyelogoZ;
extern void *_file_PhooverbotZ;
extern void *_file_PhovbikeZ;
extern void *_file_PhoverbedZ;
extern void *_file_Phovercrate1Z;
extern void *_file_PlasdoorZ;
extern void *_file_PmarkerZ;
extern void *_file_Pmedlabwin1Z;
extern void *_file_Pmedlabwin2Z;
extern void *_file_PmodemboxZ;
extern void *_file_PnintendologoZ;
extern void *_file_Pnlogo2Z;
extern void *_file_Pnlogo3Z;
extern void *_file_PnlogoZ;
extern void *_file_Ppc1Z;
extern void *_file_PpdfourZ;
extern void *_file_PpdoneZ;
extern void *_file_PpdthreeZ;
extern void *_file_PpdtwoZ;
extern void *_file_PperfectdarkZ;
extern void *_file_PpolicecarZ;
extern void *_file_PravineliftZ;
extern void *_file_PropeZ;
extern void *_file_Psk_cryopod1_botZ;
extern void *_file_Psk_cryopod1_topZ;
extern void *_file_Psk_door1Z;
extern void *_file_Psk_fighter1Z;
extern void *_file_Psk_hangardoor_botZ;
extern void *_file_Psk_hangardoor_topZ;
extern void *_file_Psk_ship_door1Z;
extern void *_file_Psk_ship_holo1Z;
extern void *_file_Psk_ship_holo2Z;
extern void *_file_Psk_ship_hulldoor1Z;
extern void *_file_Psk_ship_hulldoor2Z;
extern void *_file_Psk_ship_hulldoor3Z;
extern void *_file_Psk_ship_hulldoor4Z;
extern void *_file_Psk_under_generatorZ;
extern void *_file_Psk_under_transZ;
extern void *_file_Pskcrev_exp1Z;
extern void *_file_Pskcrev_unexp1Z;
extern void *_file_Psktnl_exp1Z;
extern void *_file_Psktnl_unexp1Z;
extern void *_file_PtaxicabZ;
extern void *_file_PtesterbotZ;
extern void *_file_PtestobjZ;
extern void *_file_PtvscreenZ;
extern void *_file_PwindowZ;
extern void *_file_Ump_setupameZ;
extern void *_file_Ump_setuparchZ;
extern void *_file_Ump_setuparecZ;
extern void *_file_Ump_setuparkZ;
extern void *_file_Ump_setupashZ;
extern void *_file_Ump_setupaztZ;
extern void *_file_Ump_setupcatZ;
extern void *_file_Ump_setupcaveZ;
extern void *_file_Ump_setupcradZ;
extern void *_file_Ump_setupcrypZ;
extern void *_file_Ump_setupdamZ;
extern void *_file_Ump_setupdepoZ;
extern void *_file_Ump_setupdestZ;
extern void *_file_Ump_setupdishZ;
extern void *_file_Ump_setupearZ;
extern void *_file_Ump_setupeldZ;
extern void *_file_Ump_setupimpZ;
extern void *_file_Ump_setupjunZ;
extern void *_file_Ump_setupleeZ;
extern void *_file_Ump_setuplenZ;
extern void *_file_Ump_setuplipZ;
extern void *_file_Ump_setuplueZ;
extern void *_file_Ump_setupoatZ;
extern void *_file_Ump_setuppamZ;
extern void *_file_Ump_setuppeteZ;
extern void *_file_Ump_setuprefZ;
extern void *_file_Ump_setupritZ;
extern void *_file_Ump_setuprunZ;
extern void *_file_Ump_setupsevZ;
extern void *_file_Ump_setupsevbZ;
extern void *_file_Ump_setupsevxZ;
extern void *_file_Ump_setupshoZ;
extern void *_file_Ump_setupsiloZ;
extern void *_file_Ump_setupstatZ;
extern void *_file_Ump_setuptraZ;
extern void *_file_Ump_setupwaxZ;
extern void *_file_UsetupameZ;
extern void *_file_UsetuparchZ;
extern void *_file_UsetuparecZ;
extern void *_file_UsetuparkZ;
extern void *_file_UsetupashZ;
extern void *_file_UsetupaztZ;
extern void *_file_UsetupcatZ;
extern void *_file_UsetupcaveZ;
extern void *_file_UsetupcradZ;
extern void *_file_UsetupcrypZ;
extern void *_file_UsetupdamZ;
extern void *_file_UsetupdepoZ;
extern void *_file_UsetupdestZ;
extern void *_file_UsetupdishZ;
extern void *_file_UsetupearZ;
extern void *_file_UsetupeldZ;
extern void *_file_UsetupimpZ;
extern void *_file_UsetupjunZ;
extern void *_file_UsetupleeZ;
extern void *_file_UsetuplenZ;
extern void *_file_UsetuplipZ;
extern void *_file_UsetuplueZ;
extern void *_file_UsetupoatZ;
extern void *_file_UsetuppamZ;
extern void *_file_UsetuppeteZ;
extern void *_file_UsetuprefZ;
extern void *_file_UsetupritZ;
extern void *_file_UsetuprunZ;
extern void *_file_UsetupsevZ;
extern void *_file_UsetupsevbZ;
extern void *_file_UsetupsevxZ;
extern void *_file_UsetupsevxbZ;
extern void *_file_UsetupshoZ;
extern void *_file_UsetupsiloZ;
extern void *_file_UsetupstatZ;
extern void *_file_UsetuptraZ;
extern void *_file_UsetupwaxZ;
extern void *_file_bg_ame_padsZ;
extern void *_file_bg_ame_tilesZ;
extern void *_file_bg_arch_padsZ;
extern void *_file_bg_arch_tilesZ;
extern void *_file_bg_arec_padsZ;
extern void *_file_bg_arec_tilesZ;
extern void *_file_bg_ark_padsZ;
extern void *_file_bg_ark_tilesZ;
extern void *_file_bg_ash_padsZ;
extern void *_file_bg_ash_tilesZ;
extern void *_file_bg_azt_padsZ;
extern void *_file_bg_azt_tilesZ;
extern void *_file_bg_cat_padsZ;
extern void *_file_bg_cat_tilesZ;
extern void *_file_bg_cave_padsZ;
extern void *_file_bg_cave_tilesZ;
extern void *_file_bg_crad_padsZ;
extern void *_file_bg_crad_tilesZ;
extern void *_file_bg_cryp_padsZ;
extern void *_file_bg_cryp_tilesZ;
extern void *_file_bg_dam_padsZ;
extern void *_file_bg_dam_tilesZ;
extern void *_file_bg_depo_padsZ;
extern void *_file_bg_depo_tilesZ;
extern void *_file_bg_dest_padsZ;
extern void *_file_bg_dest_tilesZ;
extern void *_file_bg_dish_padsZ;
extern void *_file_bg_dish_tilesZ;
extern void *_file_bg_ear_padsZ;
extern void *_file_bg_ear_tilesZ;
extern void *_file_bg_eld_padsZ;
extern void *_file_bg_eld_tilesZ;
extern void *_file_bg_imp_padsZ;
extern void *_file_bg_imp_tilesZ;
extern void *_file_bg_jun_padsZ;
extern void *_file_bg_jun_tilesZ;
extern void *_file_bg_lee_padsZ;
extern void *_file_bg_lee_tilesZ;
extern void *_file_bg_len_padsZ;
extern void *_file_bg_len_tilesZ;
extern void *_file_bg_lip_padsZ;
extern void *_file_bg_lip_tilesZ;
extern void *_file_bg_lue_padsZ;
extern void *_file_bg_lue_tilesZ;
extern void *_file_bg_oat_padsZ;
extern void *_file_bg_oat_tilesZ;
extern void *_file_bg_pam_padsZ;
extern void *_file_bg_pam_tilesZ;
extern void *_file_bg_pete_padsZ;
extern void *_file_bg_pete_tilesZ;
extern void *_file_bg_ref_padsZ;
extern void *_file_bg_ref_tilesZ;
extern void *_file_bg_rit_padsZ;
extern void *_file_bg_rit_tilesZ;
extern void *_file_bg_run_padsZ;
extern void *_file_bg_run_tilesZ;
extern void *_file_bg_sev_padsZ;
extern void *_file_bg_sev_tilesZ;
extern void *_file_bg_sevb_padsZ;
extern void *_file_bg_sevb_tilesZ;
extern void *_file_bg_sevx_padsZ;
extern void *_file_bg_sevx_tilesZ;
extern void *_file_bg_sho_padsZ;
extern void *_file_bg_sho_tilesZ;
extern void *_file_bg_silo_padsZ;
extern void *_file_bg_silo_tilesZ;
extern void *_file_bg_stat_padsZ;
extern void *_file_bg_stat_tilesZ;
extern void *_file_bg_tra_padsZ;
extern void *_file_bg_tra_tilesZ;
extern void *_file_bg_wax_padsZ;
extern void *_file_bg_wax_tilesZ;
extern void *_file_GtestgunZ;
extern void *_file_Cdd_labtechZ;
extern void *_file_Pcctv_pdZ;
extern void *_file_PcomhubZ;
extern void *_file_PquadpodZ;
extern void *_file_Ppd_consoleZ;
extern void *_file_CconneryZ;
extern void *_file_CmooreZ;
extern void *_file_CdaltonZ;
extern void *_file_Cheaddark_combatZ;
extern void *_file_CheadelvisZ;
extern void *_file_CheadrossZ;
extern void *_file_CheadcarringtonZ;
extern void *_file_CheadmrblondeZ;
extern void *_file_CheadtrentZ;
extern void *_file_CheadddshockZ;
extern void *_file_CheadgrahamZ;
extern void *_file_Cheaddark_frockZ;
extern void *_file_CheadsecretaryZ;
extern void *_file_CheadcassandraZ;
extern void *_file_CheadthekingZ;
extern void *_file_Cheadfem_guardZ;
extern void *_file_CheadjonZ;
extern void *_file_Plift_platformZ;
extern void *_file_Pdd_grateZ;
extern void *_file_PlightswitchZ;
extern void *_file_PblastshieldZ;
extern void *_file_Plightswitch2Z;
extern void *_file_Pdd_accessdoorupZ;
extern void *_file_Pdd_accessdoordnZ;
extern void *_file_Cdark_rippedZ;
extern void *_file_Cheadmark2Z;
extern void *_file_CheadchristZ;
extern void *_file_Plab_containerZ;
extern void *_file_Plab_chairZ;
extern void *_file_Plab_tableZ;
extern void *_file_Plab_microscopeZ;
extern void *_file_Plab_mainframeZ;
extern void *_file_Pdd_labdoorZ;
extern void *_file_Pdd_lab_doortopZ;
extern void *_file_Pmulti_ammo_crateZ;
extern void *_file_CheadrussZ;
extern void *_file_CheadgreyZ;
extern void *_file_CheaddarlingZ;
extern void *_file_Cdd_guardZ;
extern void *_file_CheadrobertZ;
extern void *_file_Cdd_shockZ;
extern void *_file_CheadbeauZ;
extern void *_file_PchrchainZ;
extern void *_file_Cdd_shock_infZ;
extern void *_file_Cheadfem_guard2Z;
extern void *_file_ProofgunZ;
extern void *_file_PtdoorZ;
extern void *_file_CbiotechZ;
extern void *_file_CfbiguyZ;
extern void *_file_PgroundgunZ;
extern void *_file_CciaguyZ;
extern void *_file_Ca51trooperZ;
extern void *_file_CheadbrianZ;
extern void *_file_CheadjamieZ;
extern void *_file_Cheadduncan2Z;
extern void *_file_CheadbiotechZ;
extern void *_file_UsetupuffZ;
extern void *_file_Ump_setupuffZ;
extern void *_file_bg_uff_padsZ;
extern void *_file_bg_uff_tilesZ;
extern void *_file_UsetupoldZ;
extern void *_file_Ump_setupoldZ;
extern void *_file_bg_old_padsZ;
extern void *_file_bg_old_tilesZ;
extern void *_file_UsetupateZ;
extern void *_file_Ump_setupateZ;
extern void *_file_bg_ate_padsZ;
extern void *_file_bg_ate_tilesZ;
extern void *_file_UsetuplamZ;
extern void *_file_Ump_setuplamZ;
extern void *_file_bg_lam_padsZ;
extern void *_file_bg_lam_tilesZ;
extern void *_file_Usetupmp1Z;
extern void *_file_Ump_setupmp1Z;
extern void *_file_bg_mp1_padsZ;
extern void *_file_bg_mp1_tilesZ;
extern void *_file_Usetupmp2Z;
extern void *_file_Ump_setupmp2Z;
extern void *_file_bg_mp2_padsZ;
extern void *_file_bg_mp2_tilesZ;
extern void *_file_Usetupmp3Z;
extern void *_file_Ump_setupmp3Z;
extern void *_file_bg_mp3_padsZ;
extern void *_file_bg_mp3_tilesZ;
extern void *_file_Usetupmp4Z;
extern void *_file_Ump_setupmp4Z;
extern void *_file_bg_mp4_padsZ;
extern void *_file_bg_mp4_tilesZ;
extern void *_file_Usetupmp5Z;
extern void *_file_Ump_setupmp5Z;
extern void *_file_bg_mp5_padsZ;
extern void *_file_bg_mp5_tilesZ;
extern void *_file_Usetupmp6Z;
extern void *_file_Ump_setupmp6Z;
extern void *_file_bg_mp6_padsZ;
extern void *_file_bg_mp6_tilesZ;
extern void *_file_Usetupmp7Z;
extern void *_file_Ump_setupmp7Z;
extern void *_file_bg_mp7_padsZ;
extern void *_file_bg_mp7_tilesZ;
extern void *_file_Usetupmp8Z;
extern void *_file_Ump_setupmp8Z;
extern void *_file_bg_mp8_padsZ;
extern void *_file_bg_mp8_tilesZ;
extern void *_file_Usetupmp9Z;
extern void *_file_Ump_setupmp9Z;
extern void *_file_bg_mp9_padsZ;
extern void *_file_bg_mp9_tilesZ;
extern void *_file_Usetupmp10Z;
extern void *_file_Ump_setupmp10Z;
extern void *_file_bg_mp10_padsZ;
extern void *_file_bg_mp10_tilesZ;
extern void *_file_Usetupmp11Z;
extern void *_file_Ump_setupmp11Z;
extern void *_file_bg_mp11_padsZ;
extern void *_file_bg_mp11_tilesZ;
extern void *_file_Usetupmp12Z;
extern void *_file_Ump_setupmp12Z;
extern void *_file_bg_mp12_padsZ;
extern void *_file_bg_mp12_tilesZ;
extern void *_file_Usetupmp13Z;
extern void *_file_Ump_setupmp13Z;
extern void *_file_bg_mp13_padsZ;
extern void *_file_bg_mp13_tilesZ;
extern void *_file_Usetupmp14Z;
extern void *_file_Ump_setupmp14Z;
extern void *_file_bg_mp14_padsZ;
extern void *_file_bg_mp14_tilesZ;
extern void *_file_Usetupmp15Z;
extern void *_file_Ump_setupmp15Z;
extern void *_file_bg_mp15_padsZ;
extern void *_file_bg_mp15_tilesZ;
extern void *_file_Usetupmp16Z;
extern void *_file_Ump_setupmp16Z;
extern void *_file_bg_mp16_padsZ;
extern void *_file_bg_mp16_tilesZ;
extern void *_file_Usetupmp17Z;
extern void *_file_Ump_setupmp17Z;
extern void *_file_bg_mp17_padsZ;
extern void *_file_bg_mp17_tilesZ;
extern void *_file_Usetupmp18Z;
extern void *_file_Ump_setupmp18Z;
extern void *_file_bg_mp18_padsZ;
extern void *_file_bg_mp18_tilesZ;
extern void *_file_Usetupmp19Z;
extern void *_file_Ump_setupmp19Z;
extern void *_file_bg_mp19_padsZ;
extern void *_file_bg_mp19_tilesZ;
extern void *_file_Usetupmp20Z;
extern void *_file_Ump_setupmp20Z;
extern void *_file_bg_mp20_padsZ;
extern void *_file_bg_mp20_tilesZ;
extern void *_file_Ca51airmanZ;
extern void *_file_Cheadneil2Z;
extern void *_file_Pci_sofaZ;
extern void *_file_Pci_liftZ;
extern void *_file_Pci_liftdoorZ;
extern void *_file_CchicrobZ;
extern void *_file_CstewardZ;
extern void *_file_CheadedmcgZ;
extern void *_file_CstewardessZ;
extern void *_file_CheadankaZ;
extern void *_file_CpresidentZ;
extern void *_file_Cstewardess_coatZ;
extern void *_file_Cheadleslie_sZ;
extern void *_file_PlasercutZ;
extern void *_file_Psk_shuttleZ;
extern void *_file_CminiskedarZ;
extern void *_file_PnewvilladoorZ;
extern void *_file_Cnsa_lackeyZ;
extern void *_file_Cheadmatt_cZ;
extern void *_file_Cpres_securityZ;
extern void *_file_Cheadpeer_sZ;
extern void *_file_CnegotiatorZ;
extern void *_file_Cheadeileen_tZ;
extern void *_file_Psk_pillarleftZ;
extern void *_file_Psk_pillarrightZ;
extern void *_file_Psk_plinth_tZ;
extern void *_file_Psk_plinth_mlZ;
extern void *_file_Psk_plinth_mrZ;
extern void *_file_Psk_plinth_blZ;
extern void *_file_Psk_plinth_brZ;
extern void *_file_Psk_fl_shad_tZ;
extern void *_file_Psk_fl_shad_mlZ;
extern void *_file_Psk_fl_shad_mrZ;
extern void *_file_Psk_fl_shad_blZ;
extern void *_file_Psk_fl_shad_brZ;
extern void *_file_Psk_fl_noshad_tZ;
extern void *_file_Psk_fl_noshad_mlZ;
extern void *_file_Psk_fl_noshad_mrZ;
extern void *_file_Psk_fl_noshad_blZ;
extern void *_file_Psk_fl_noshad_brZ;
extern void *_file_GhudpieceZ;
extern void *_file_Psk_templecolumn1Z;
extern void *_file_Psk_templecolumn2Z;
extern void *_file_Psk_templecolumn3Z;
extern void *_file_Psk_sunshad1Z;
extern void *_file_Psk_sunshad2Z;
extern void *_file_Psk_sunnoshad1Z;
extern void *_file_Psk_sunnoshad2Z;
extern void *_file_Cg5_guardZ;
extern void *_file_Cheadandy_rZ;
extern void *_file_Cpelagic_guardZ;
extern void *_file_Cg5_swat_guardZ;
extern void *_file_Calaskan_guardZ;
extern void *_file_Cmaian_soldierZ;
extern void *_file_Cheadben_rZ;
extern void *_file_Cheadsteve_kZ;
extern void *_file_PbarrelZ;
extern void *_file_Pglass_floorZ;
extern void *_file_Pesca_stepZ;
extern void *_file_Pmatrix_liftZ;
extern void *_file_Prubble1Z;
extern void *_file_Prubble2Z;
extern void *_file_Prubble3Z;
extern void *_file_Prubble4Z;
extern void *_file_Arecep01M;
extern void *_file_Arecep02M;
extern void *_file_Arecep03M;
extern void *_file_Arecep04M;
extern void *_file_Arecep05M;
extern void *_file_Arecep06M;
extern void *_file_Arlguard1M;
extern void *_file_Arltech01M;
extern void *_file_Arltech02M;
extern void *_file_Arltech03M;
extern void *_file_Arltech04M;
extern void *_file_Arltech05M;
extern void *_file_Arltech06M;
extern void *_file_Ascie2aM;
extern void *_file_Ascie2bM;
extern void *_file_Ascie2cM;
extern void *_file_Ascie2dM;
extern void *_file_Ascie2eM;
extern void *_file_Ascie2fM;
extern void *_file_Ascie2gM;
extern void *_file_Ascie3aM;
extern void *_file_Ascie3bM;
extern void *_file_Ascie3cM;
extern void *_file_Ascie3dM;
extern void *_file_Ascie3eM;
extern void *_file_Ascie3gM;
extern void *_file_Ascien10aM;
extern void *_file_Ascien2_aM;
extern void *_file_Ascien3_aM;
extern void *_file_Ascien4_aM;
extern void *_file_Ascien5_aM;
extern void *_file_Ascien6_aM;
extern void *_file_Ascien7_aM;
extern void *_file_Ascien9_aM;
extern void *_file_AvilgrimM;
extern void *_file_Awepgd01M;
extern void *_file_Awepgd02M;
extern void *_file_Awepgd03M;
extern void *_file_Awepsc01M;
extern void *_file_Awepsc02M;
extern void *_file_Awepsc03M;
extern void *_file_Aa51elv01M;
extern void *_file_Aa51elv02M;
extern void *_file_Aa51elv03M;
extern void *_file_Aa51grd01M;
extern void *_file_Aa51grd02M;
extern void *_file_Aa51grd03M;
extern void *_file_Aa51grd04M;
extern void *_file_Aa51grd05M;
extern void *_file_Aa51grd06M;
extern void *_file_Aa51grd07M;
extern void *_file_Aa51grd08M;
extern void *_file_Aa51grd09M;
extern void *_file_Aa51grd10M;
extern void *_file_Aa51jo1M;
extern void *_file_Aa51jo2M;
extern void *_file_Aa51jo3M;
extern void *_file_Aa51jo4M;
extern void *_file_Aa51jo5M;
extern void *_file_Aa51jo6M;
extern void *_file_Aa51jon01M;
extern void *_file_Aa51jon02M;
extern void *_file_Aa51jon03M;
extern void *_file_Aa51jon04M;
extern void *_file_Aa51jon05M;
extern void *_file_Aa51jon06M;
extern void *_file_Aa51jon07M;
extern void *_file_Aa51jon08M;
extern void *_file_Aa51jon09M;
extern void *_file_Aa51jon10M;
extern void *_file_Aa51jon11M;
extern void *_file_Aa51jon12M;
extern void *_file_Aa51jon14M;
extern void *_file_Aa51jon15M;
extern void *_file_Aa51sci1M;
extern void *_file_Aaf1jo01M;
extern void *_file_Aaf1jo02M;
extern void *_file_Aaf1jo03M;
extern void *_file_Aaf1pr01M;
extern void *_file_Aaf1pr02M;
extern void *_file_Aaf1pr03M;
extern void *_file_Aaf1pr04M;
extern void *_file_Aaf1pr05M;
extern void *_file_Aaf1pr06M;
extern void *_file_Aaf1pr07M;
extern void *_file_Aaf1pr08M;
extern void *_file_Aaf1pr09M;
extern void *_file_Aaf1pr10M;
extern void *_file_Aaf1tr01M;
extern void *_file_Aaf1tr02M;
extern void *_file_Aaf1tr03M;
extern void *_file_Aairbgd01M;
extern void *_file_Aairbgd02M;
extern void *_file_Aairbgd03M;
extern void *_file_Aairbgd04M;
extern void *_file_Aairbgd05M;
extern void *_file_Aairbgd06M;
extern void *_file_Aairbgd07M;
extern void *_file_Aairbgd08M;
extern void *_file_Aairbgd09M;
extern void *_file_Aairbgd10M;
extern void *_file_Aairbgd11M;
extern void *_file_Aairbgd12M;
extern void *_file_Aairbgd13M;
extern void *_file_Aairbgd14M;
extern void *_file_Aairbgd15M;
extern void *_file_Aairbgd16M;
extern void *_file_Aairstw01M;
extern void *_file_Aairstw02M;
extern void *_file_Aairstw03M;
extern void *_file_Aassael01M;
extern void *_file_Aassael02M;
extern void *_file_Aassael03M;
extern void *_file_Aassael04M;
extern void *_file_Aassael05M;
extern void *_file_Aassael06M;
extern void *_file_Absewrk01M;
extern void *_file_Absewrk02M;
extern void *_file_Absewrk03M;
extern void *_file_Absewrk04M;
extern void *_file_Absewrk05M;
extern void *_file_Acetael01M;
extern void *_file_Achdroid1M;
extern void *_file_Achdroid2M;
extern void *_file_Acsec01M;
extern void *_file_Acsec02M;
extern void *_file_Acsec03M;
extern void *_file_Acstan1M;
extern void *_file_Acstan2M;
extern void *_file_Adevr01M;
extern void *_file_Adevr02M;
extern void *_file_Adevr03M;
extern void *_file_Adevr04M;
extern void *_file_Adevr05M;
extern void *_file_Adevr06M;
extern void *_file_Adevr07M;
extern void *_file_Adevr08M;
extern void *_file_Adevr09M;
extern void *_file_Adevr10M;
extern void *_file_Adevr11M;
extern void *_file_Adevr12M;
extern void *_file_Aexec01M;
extern void *_file_Aexec02M;
extern void *_file_Aexec04M;
extern void *_file_Aexec05M;
extern void *_file_Aexec06M;
extern void *_file_Aexec07M;
extern void *_file_Aexec08M;
extern void *_file_Aexec09M;
extern void *_file_Aexec10M;
extern void *_file_Aexec11M;
extern void *_file_Aexec12M;
extern void *_file_Aexec13M;
extern void *_file_Aexec14M;
extern void *_file_Ahelic01M;
extern void *_file_Ahelic02M;
extern void *_file_Ahelic03M;
extern void *_file_Ahologd01M;
extern void *_file_AholohopkM;
extern void *_file_Ainvcar01M;
extern void *_file_Ainvcar02M;
extern void *_file_Ainvcar03M;
extern void *_file_Ainvcar04M;
extern void *_file_Ainvcar05M;
extern void *_file_Ainvcar06M;
extern void *_file_Ainvcar07M;
extern void *_file_Ainvcar08M;
extern void *_file_Ainvcar09M;
extern void *_file_Ainvcar10M;
extern void *_file_Ainvcar11M;
extern void *_file_Ainvcar12M;
extern void *_file_AinvfarrM;
extern void *_file_AinvfemaM;
extern void *_file_AinvfostM;
extern void *_file_AinvgrimM;
extern void *_file_AinvhopkM;
extern void *_file_AinvmaleM;
extern void *_file_Ajoexec01M;
extern void *_file_Ajoexec02M;
extern void *_file_Ajosci01M;
extern void *_file_Ajosci02M;
extern void *_file_Ajosci03M;
extern void *_file_Alabacc1M;
extern void *_file_Alabacc2M;
extern void *_file_Alabacc3M;
extern void *_file_Alabacc4M;
extern void *_file_Alabacc5M;
extern void *_file_Alabacc6M;
extern void *_file_Alabtech1M;
extern void *_file_Alabtech2M;
extern void *_file_Alabtech3M;
extern void *_file_Alabtech5M;
extern void *_file_Alabtech6M;
extern void *_file_Alabtech7M;
extern void *_file_Alabtech8M;
extern void *_file_Alabtech9M;
extern void *_file_Aoffwrk01M;
extern void *_file_Aoffwrk02M;
extern void *_file_Aoffwrk03M;
extern void *_file_Aoffwrk04M;
extern void *_file_Cpresident_cloneZ;
extern void *_file_CheadjonathanZ;
extern void *_file_Cheadmaian_sZ;
extern void *_file_Cdark_af1Z;
extern void *_file_Pcable_carZ;
extern void *_file_Pelvis_saucerZ;
extern void *_file_Pstewardess_trolleyZ;
extern void *_file_Pairbase_lift_enclosedZ;
extern void *_file_Pairbase_lift_angleZ;
extern void *_file_Pairbase_safedoorZ;
extern void *_file_Paf1_pilotchairZ;
extern void *_file_Paf1_passchairZ;
extern void *_file_CheadshaunZ;
extern void *_file_PchrnightsightZ;
extern void *_file_PchrshieldZ;
extern void *_file_Pchrfalcon2Z;
extern void *_file_Pchrleegun1Z;
extern void *_file_PchrmaulerZ;
extern void *_file_Pchrdy357Z;
extern void *_file_Pchrdy357trentZ;
extern void *_file_PchrmaianpistolZ;
extern void *_file_Pchrfalcon2silZ;
extern void *_file_Pchrfalcon2scopeZ;
extern void *_file_Pchrcmp150Z;
extern void *_file_Pchrar34Z;
extern void *_file_PchrdragonZ;
extern void *_file_PchrsuperdragonZ;
extern void *_file_PchravengerZ;
extern void *_file_PchrcycloneZ;
extern void *_file_PchrmaiansmgZ;
extern void *_file_Pchrrcp120Z;
extern void *_file_PchrpcgunZ;
extern void *_file_PchrshotgunZ;
extern void *_file_PchrskminigunZ;
extern void *_file_PchrdyrocketZ;
extern void *_file_PchrdevastatorZ;
extern void *_file_PchrskrocketZ;
extern void *_file_Pchrz2020Z;
extern void *_file_PchrsniperrifleZ;
extern void *_file_PchrcrossbowZ;
extern void *_file_PchrdruggunZ;
extern void *_file_PchrknifeZ;
extern void *_file_PchrnbombZ;
extern void *_file_PchrflashbangZ;
extern void *_file_PchrgrenadeZ;
extern void *_file_PchrtimedmineZ;
extern void *_file_PchrproximitymineZ;
extern void *_file_PchrremotemineZ;
extern void *_file_PchrecmmineZ;
extern void *_file_PchrwppkZ;
extern void *_file_Pchrtt33Z;
extern void *_file_PchrskorpionZ;
extern void *_file_PchrkalashZ;
extern void *_file_PchruziZ;
extern void *_file_Pchrmp5kZ;
extern void *_file_Pchrm16Z;
extern void *_file_Pchrfnp90Z;
extern void *_file_PchrdyrocketmisZ;
extern void *_file_PchrskrocketmisZ;
extern void *_file_PchrcrossboltZ;
extern void *_file_PchrdevgrenadeZ;
extern void *_file_PchrdraggrenadeZ;
extern void *_file_Gfalcon2Z;
extern void *_file_Gleegun1Z;
extern void *_file_GskpistolZ;
extern void *_file_Gdy357Z;
extern void *_file_Gdy357trentZ;
extern void *_file_GmaianpistolZ;
extern void *_file_Gcmp150Z;
extern void *_file_Gar34Z;
extern void *_file_GdydragonZ;
extern void *_file_GdysuperdragonZ;
extern void *_file_Gk7avengerZ;
extern void *_file_GcycloneZ;
extern void *_file_GmaiansmgZ;
extern void *_file_Grcp120Z;
extern void *_file_GpcgunZ;
extern void *_file_GshotgunZ;
extern void *_file_GskminigunZ;
extern void *_file_GdyrocketZ;
extern void *_file_GdydevastatorZ;
extern void *_file_GskrocketZ;
extern void *_file_Gz2020Z;
extern void *_file_GsniperrifleZ;
extern void *_file_GcrossbowZ;
extern void *_file_GdruggunZ;
extern void *_file_GknifeZ;
extern void *_file_GgrenadeZ;
extern void *_file_GtimedmineZ;
extern void *_file_GproximitymineZ;
extern void *_file_GremotemineZ;
extern void *_file_GwppkZ;
extern void *_file_Gtt33Z;
extern void *_file_GskorpionZ;
extern void *_file_Gak47Z;
extern void *_file_GuziZ;
extern void *_file_Gmp5kZ;
extern void *_file_Gm16Z;
extern void *_file_Gfnp90Z;
extern void *_file_Gfalcon2lodZ;
extern void *_file_GskminigunlodZ;
extern void *_file_Pa51_turretZ;
extern void *_file_PpelagicdoorZ;
extern void *_file_Am1_l1_aM;
extern void *_file_Am1_l1_bM;
extern void *_file_Am1_l1_cM;
extern void *_file_Am1_l1_dM;
extern void *_file_Am1_l2_aM;
extern void *_file_Am1_l2_bM;
extern void *_file_Am1_l2_cM;
extern void *_file_Am1_l2_dM;
extern void *_file_Am1_l3_aM;
extern void *_file_Am1_l3_bM;
extern void *_file_Am1_l3_cM;
extern void *_file_Am1_l3_dM;
extern void *_file_Am2_l1_aM;
extern void *_file_Am2_l1_bM;
extern void *_file_Am2_l1_cM;
extern void *_file_Am2_l1_dM;
extern void *_file_Am3_l1_aM;
extern void *_file_Am3_l1_bM;
extern void *_file_Am3_l1_cM;
extern void *_file_Am3_l1_dM;
extern void *_file_Am3_l2_aM;
extern void *_file_Am3_l2_bM;
extern void *_file_Am3_l2_cM;
extern void *_file_Am3_l2_dM;
extern void *_file_Am4_l1_aM;
extern void *_file_Am4_l1_bM;
extern void *_file_Am4_l1_cM;
extern void *_file_Am4_l1_dM;
extern void *_file_Am4_l2_aM;
extern void *_file_Am4_l2_bM;
extern void *_file_Am4_l2_cM;
extern void *_file_Am4_l2_dM;
extern void *_file_Am4_l3_aM;
extern void *_file_Am4_l3_bM;
extern void *_file_Am4_l3_cM;
extern void *_file_Am4_l3_dM;
extern void *_file_Am5_l1_aM;
extern void *_file_Am5_l1_bM;
extern void *_file_Am5_l1_cM;
extern void *_file_Am5_l1_dM;
extern void *_file_Am5_l2_aM;
extern void *_file_Am5_l2_bM;
extern void *_file_Am5_l2_cM;
extern void *_file_Am5_l2_dM;
extern void *_file_Am5_l3_aM;
extern void *_file_Am5_l3_bM;
extern void *_file_Am5_l3_cM;
extern void *_file_Am5_l3_dM;
extern void *_file_Am6_l1_aM;
extern void *_file_Am6_l1_bM;
extern void *_file_Am6_l1_cM;
extern void *_file_Am6_l1_dM;
extern void *_file_Am6_l2_aM;
extern void *_file_Am6_l2_bM;
extern void *_file_Am6_l2_cM;
extern void *_file_Am6_l2_dM;
extern void *_file_Am7_l1_aM;
extern void *_file_Am7_l1_bM;
extern void *_file_Am7_l1_cM;
extern void *_file_Am7_l1_dM;
extern void *_file_Am8_l1_aM;
extern void *_file_Am8_l1_bM;
extern void *_file_Am8_l1_cM;
extern void *_file_Am8_l1_dM;
extern void *_file_Am9_l1_aM;
extern void *_file_Am9_l1_bM;
extern void *_file_Am9_l1_cM;
extern void *_file_Am9_l1_dM;
extern void *_file_Ap1_01_joM;
extern void *_file_Ap1_02_caM;
extern void *_file_Ap1_03_joM;
extern void *_file_Ap1_04_caM;
extern void *_file_Ap1_05_joM;
extern void *_file_Ap1_06_caM;
extern void *_file_Ap1_07_joM;
extern void *_file_Ap1_08_caM;
extern void *_file_Ap2_01_joM;
extern void *_file_Ap2_02_joM;
extern void *_file_Ap2_03_drM;
extern void *_file_Ap2_04_joM;
extern void *_file_Ap2_05_joM;
extern void *_file_Ap2_06_drM;
extern void *_file_Ap2_07_drM;
extern void *_file_Ap3_01_gdM;
extern void *_file_Ap3_02_joM;
extern void *_file_Ap3_03_joM;
extern void *_file_Ap4_01_dvM;
extern void *_file_Ap4_02_joM;
extern void *_file_Ap4_03_dvM;
extern void *_file_Ap4_04_joM;
extern void *_file_Ap4_05_dvM;
extern void *_file_Ap4_06_joM;
extern void *_file_Ap4_07_blM;
extern void *_file_Ap4_08_dvM;
extern void *_file_Ap4_09_dvM;
extern void *_file_Ap5_01_joM;
extern void *_file_Ap5_02_joM;
extern void *_file_Ap5_03_joM;
extern void *_file_Ap6_01_joM;
extern void *_file_Ap6_02_caM;
extern void *_file_Ap6_03_joM;
extern void *_file_Ap6_04_caM;
extern void *_file_Ap6_05_joM;
extern void *_file_Ap6_06_caM;
extern void *_file_Ap7_01_caM;
extern void *_file_Ap7_02_joM;
extern void *_file_Ap7_03_caM;
extern void *_file_Ap7_04_joM;
extern void *_file_Ap8_01_dvM;
extern void *_file_Ap8_02_blM;
extern void *_file_Ap8_03_dvM;
extern void *_file_Ap8_04_blM;
extern void *_file_Ap8_06_blM;
extern void *_file_Ap8_07_trM;
extern void *_file_Ap8_08_dvM;
extern void *_file_Ap8_09_trM;
extern void *_file_Ap8_10_blM;
extern void *_file_Ap9_01_joM;
extern void *_file_Ap9_02_caM;
extern void *_file_Ap9_03_joM;
extern void *_file_Ap10_01_caM;
extern void *_file_Ap10_02_caM;
extern void *_file_Ap10_03_caM;
extern void *_file_Ap10_04_caM;
extern void *_file_Ap10_05_joM;
extern void *_file_Ap10_06_caM;
extern void *_file_Ap10_07_joM;
extern void *_file_Ap10_08_caM;
extern void *_file_Ap10_09_joM;
extern void *_file_Ap11_01_jnM;
extern void *_file_Ap11_02_joM;
extern void *_file_Ap11_03_jnM;
extern void *_file_Ap11_04_joM;
extern void *_file_Ap11_05_jnM;
extern void *_file_Ap11_06_joM;
extern void *_file_Ap11_07_jnM;
extern void *_file_Ap11_08_joM;
extern void *_file_Ap12_01_jnM;
extern void *_file_Ap12_02_joM;
extern void *_file_Ap12_03_jnM;
extern void *_file_Ap12_04_joM;
extern void *_file_Ap12_05_jnM;
extern void *_file_Ap12_06_joM;
extern void *_file_Ap12_07_jnM;
extern void *_file_Ap12_08_joM;
extern void *_file_Ap12_09_jnM;
extern void *_file_Ap12_10_joM;
extern void *_file_Ap13_01_joM;
extern void *_file_Ap13_02_suM;
extern void *_file_Ap13_03_joM;
extern void *_file_Ap13_04_suM;
extern void *_file_Ap13_06_suM;
extern void *_file_Ap14_03_suM;
extern void *_file_Ap14_04_joM;
extern void *_file_Ap14_05_suM;
extern void *_file_Ap14_07_joM;
extern void *_file_Ap15_01_elM;
extern void *_file_Ap15_02_elM;
extern void *_file_Ap15_03_joM;
extern void *_file_Ap15_04_jnM;
extern void *_file_Ap15_05_elM;
extern void *_file_Ap15_06_joM;
extern void *_file_Ap15_07_elM;
extern void *_file_Ap15_08_joM;
extern void *_file_Ap15_09_elM;
extern void *_file_Ap15_10_joM;
extern void *_file_Ap15_11_elM;
extern void *_file_Ap16_01_joM;
extern void *_file_Ap16_02_caM;
extern void *_file_Ap16_04_caM;
extern void *_file_Ap16_05_joM;
extern void *_file_Ap16_06_caM;
extern void *_file_Ap17_01_trM;
extern void *_file_Ap17_02_prM;
extern void *_file_Ap17_03_trM;
extern void *_file_Ap17_04_prM;
extern void *_file_Ap17_05_trM;
extern void *_file_Ap17_06_trM;
extern void *_file_Ap18_01_joM;
extern void *_file_Ap18_02_elM;
extern void *_file_Ap18_03_elM;
extern void *_file_Ap18_04_joM;
extern void *_file_Ap18_05_elM;
extern void *_file_Ap19_01_caM;
extern void *_file_Ap19_02_caM;
extern void *_file_Ap19_03_joM;
extern void *_file_Ap19_04_caM;
extern void *_file_Ap19_05_joM;
extern void *_file_Ap19_06_joM;
extern void *_file_Ap20_01_joM;
extern void *_file_Ap20_02_prM;
extern void *_file_Ap20_03_joM;
extern void *_file_Ap20_04_prM;
extern void *_file_Ap20_05_joM;
extern void *_file_Ap20_06_blM;
extern void *_file_Ap20_07_trM;
extern void *_file_Ap20_08_trM;
extern void *_file_Ap21_01_elM;
extern void *_file_Ap21_02_joM;
extern void *_file_Ap21_03_elM;
extern void *_file_Ap21_04_joM;
extern void *_file_Ap22_01_elM;
extern void *_file_Ap22_02_joM;
extern void *_file_Ap22_03_elM;
extern void *_file_Ap22_04_joM;
extern void *_file_Ap23_01_joM;
extern void *_file_Ap23_02_drM;
extern void *_file_Ap23_03_joM;
extern void *_file_Ap23_04_drM;
extern void *_file_Ap23_05_joM;
extern void *_file_Ap23_06_drM;
extern void *_file_Ap23_07_joM;
extern void *_file_Ap23_08_drM;
extern void *_file_Ap24_01_caM;
extern void *_file_Ap24_02_joM;
extern void *_file_Ap24_03_caM;
extern void *_file_Ap24_04_joM;
extern void *_file_Ap24_05_caM;
extern void *_file_Ap24_06_caM;
extern void *_file_Ap24_07_joM;
extern void *_file_Ap24_08_joM;
extern void *_file_Ap25_01_joM;
extern void *_file_Ap25_02_joM;
extern void *_file_Ap26_01_joM;
extern void *_file_Ap26_02_dvM;
extern void *_file_Ap26_03_joM;
extern void *_file_Ap26_04_dvM;
extern void *_file_Ap26_05_dvM;
extern void *_file_Ap26_06_joM;
extern void *_file_Ap26_07_dvM;
extern void *_file_Ap26_08_dvM;
extern void *_file_Ap27_01_joM;
extern void *_file_Ap27_02_elM;
extern void *_file_Ap27_03_elM;
extern void *_file_Ap27_04_joM;
extern void *_file_Ap27_05_joM;
extern void *_file_Ap27_06_elM;
extern void *_file_Ap28_01_elM;
extern void *_file_Ap28_02_joM;
extern void *_file_Ap28_03_elM;
extern void *_file_Ap28_04_joM;
extern void *_file_Ap28_05_elM;
extern void *_file_Ap28_06_joM;
extern void *_file_Ap29_01_elM;
extern void *_file_Ap29_02_joM;
extern void *_file_Ap29_03_elM;
extern void *_file_Ap29_04_joM;
extern void *_file_Ap29_05_joM;
extern void *_file_Ap29_06_elM;
extern void *_file_Ap29_07_joM;
extern void *_file_Ap29_08_elM;
extern void *_file_Ap29_09_joM;
extern void *_file_Ap29_10_elM;
extern void *_file_PautosurgeonZ;
extern void *_file_CdarkwetZ;
extern void *_file_CdarkaqualungZ;
extern void *_file_CdarksnowZ;
extern void *_file_CdarklabZ;
extern void *_file_CfemlabtechZ;
extern void *_file_CddsniperZ;
extern void *_file_Cpilotaf1Z;
extern void *_file_CcilabtechZ;
extern void *_file_CcifemtechZ;
extern void *_file_Cheadeileen_hZ;
extern void *_file_Cheadscott_hZ;
extern void *_file_CcarreveningsuitZ;
extern void *_file_CjonathonZ;
extern void *_file_CcisoldierZ;
extern void *_file_CheadsanchezZ;
extern void *_file_CheaddarkaquaZ;
extern void *_file_CheadddsniperZ;
extern void *_file_PlimoZ;
extern void *_file_PpdmenuZ;
extern void *_file_Pa51interceptorZ;
extern void *_file_Pa51dishZ;
extern void *_file_Pa51radarconsoleZ;
extern void *_file_Pa51lockerdoorZ;
extern void *_file_Pg5generatorZ;
extern void *_file_Pg5dumpsterZ;
extern void *_file_Gar34lodZ;
extern void *_file_GavengerlodZ;
extern void *_file_Gcmp150lodZ;
extern void *_file_GcrossbowlodZ;
extern void *_file_GcyclonelodZ;
extern void *_file_GdruggunlodZ;
extern void *_file_Gdy357lodZ;
extern void *_file_Gdy357trentlodZ;
extern void *_file_GdevastatorlodZ;
extern void *_file_GdydragonlodZ;
extern void *_file_GdysuperdragonlodZ;
extern void *_file_GknifelodZ;
extern void *_file_GlaserlodZ;
extern void *_file_GmagseclodZ;
extern void *_file_GmayanpistollodZ;
extern void *_file_GmayansmglodZ;
extern void *_file_GpcgunlodZ;
extern void *_file_Grcp120lodZ;
extern void *_file_GrocketlodZ;
extern void *_file_GshotgunlodZ;
extern void *_file_GskpistollodZ;
extern void *_file_GskrocketlodZ;
extern void *_file_GsniperlodZ;
extern void *_file_Gz2020lodZ;
extern void *_file_PchrcloakerZ;
extern void *_file_PchrspeedpillZ;
extern void *_file_PbaggagecarrierZ;
extern void *_file_PminesignZ;
extern void *_file_PchamberZ;
extern void *_file_PisotopeexperimentZ;
extern void *_file_PisotopeZ;
extern void *_file_PreactordoorZ;
extern void *_file_PsaucerinsideZ;
extern void *_file_PvillastoolZ;
extern void *_file_Pcetanwindow1Z;
extern void *_file_Pcetanwindow2Z;
extern void *_file_Pcetanwindow3Z;
extern void *_file_Apelelv01M;
extern void *_file_Apelgrd01M;
extern void *_file_Ap29_11_joM;
extern void *_file_GlaserZ;
extern void *_file_PbigpelagicdoorZ;
extern void *_file_Psk_jonrubble3Z;
extern void *_file_Psk_jonrubble4Z;
extern void *_file_Psk_jonrubble5Z;
extern void *_file_Psk_jonrubble6Z;
extern void *_file_GcombathandslodZ;
extern void *_file_PbinocularsZ;
extern void *_file_PsubmarineZ;
extern void *_file_Pairforce1Z;
extern void *_file_PenginepartZ;
extern void *_file_Am3l2carrM;
extern void *_file_Aelvcet01M;
extern void *_file_Aelvcet02M;
extern void *_file_Ajorep01M;
extern void *_file_Ajorep02M;
extern void *_file_Ajorep03M;
extern void *_file_Ajorep04M;
extern void *_file_PcetroofgunZ;
extern void *_file_PcetansmalldoorZ;
extern void *_file_PpowernodeZ;
extern void *_file_PcetanbluegreenlZ;
extern void *_file_PcetanbluegreenrZ;
extern void *_file_PskedarconsoleZ;
extern void *_file_PskedarconsolepanelZ;
extern void *_file_Ajorpld01M;
extern void *_file_Ajorpld02M;
extern void *_file_Ajorpld03M;
extern void *_file_Ajorpld04M;
extern void *_file_GnbombZ;
extern void *_file_GnbomblodZ;
extern void *_file_GgrenadelodZ;
extern void *_file_PweaponcdoorZ;
extern void *_file_PtargetZ;
extern void *_file_PdevicesecretdoorZ;
extern void *_file_PcarringtonsecretdoorZ;
extern void *_file_PsinisterpcZ;
extern void *_file_PsinisterstationZ;
extern void *_file_PkeypadlockZ;
extern void *_file_PthumbprintscannerZ;
extern void *_file_PretinalockZ;
extern void *_file_PcardlockZ;
extern void *_file_PgoodstationZ;
extern void *_file_PgoodpcZ;
extern void *_file_CskedarkingZ;
extern void *_file_CelviswaistcoatZ;
extern void *_file_CheadgriffeyZ;
extern void *_file_CheadmotoZ;
extern void *_file_CheadkeithZ;
extern void *_file_CheadwinnerZ;
extern void *_file_Ca51faceplateZ;
extern void *_file_PchrautogunZ;
extern void *_file_Pg5bigchairZ;
extern void *_file_Pg5smallchairZ;
extern void *_file_PkingsceptreZ;
extern void *_file_PlabcoatZ;
extern void *_file_Atrjo01M;
extern void *_file_Atrgrim01M;
extern void *_file_Atrgrim02M;
extern void *_file_Atrcarr06M;
extern void *_file_Atrcarr07M;
extern void *_file_Atrcarr08M;
extern void *_file_Atrcarr01M;
extern void *_file_Atrcarr02M;
extern void *_file_Atrcarr03M;
extern void *_file_Atrcarr04M;
extern void *_file_Atrcarr05M;
extern void *_file_Atrcarr12M;
extern void *_file_Abnblde01M;
extern void *_file_Abncass01M;
extern void *_file_Pcidoor1Z;
extern void *_file_Pg5_chairZ;
extern void *_file_Pg5_chair2Z;
extern void *_file_Pdd_window_foyerZ;
extern void *_file_Ghand_jowetsuitZ;
extern void *_file_Ghand_trentZ;
extern void *_file_Ghand_jofrockZ;
extern void *_file_Ghand_jotrenchZ;
extern void *_file_Ghand_ddsniperZ;
extern void *_file_Ghand_presidentZ;
extern void *_file_Ghand_joaf1Z;
extern void *_file_Ghand_jopilotZ;
extern void *_file_Ghand_carringtonZ;
extern void *_file_Ghand_mrblondeZ;
extern void *_file_Ghand_ciaZ;
extern void *_file_Ghand_cifemtechZ;
extern void *_file_Ghand_fbiarmZ;
extern void *_file_Ghand_josnowZ;
extern void *_file_Ghand_vriesZ;
extern void *_file_Ghand_ddsecurityZ;
extern void *_file_Ghand_tragic_pelagicZ;
extern void *_file_Ghand_stewardess_coatZ;
extern void *_file_Ghand_ddlabtechZ;
extern void *_file_Pci_cabinetZ;
extern void *_file_Pci_deskZ;
extern void *_file_Pci_carr_deskZ;
extern void *_file_Pci_f_chairZ;
extern void *_file_Pci_loungerZ;
extern void *_file_Pci_f_sofaZ;
extern void *_file_Pci_tableZ;
extern void *_file_Pcv_coffee_tableZ;
extern void *_file_Pcv_chair1Z;
extern void *_file_Pcv_chair2Z;
extern void *_file_Pcv_sofaZ;
extern void *_file_Pcv_chair4Z;
extern void *_file_Pcv_lampZ;
extern void *_file_Pcv_cabinetZ;
extern void *_file_Pcv_f_bedZ;
extern void *_file_Ppel_chair1Z;
extern void *_file_Psk_console2Z;
extern void *_file_Pdd_ear_tableZ;
extern void *_file_Pdd_ear_chairZ;
extern void *_file_Pairbase_table2Z;
extern void *_file_Pairbase_chair2Z;
extern void *_file_Pmisc_crateZ;
extern void *_file_Pmisc_irspecsZ;
extern void *_file_Cheadelvis_gogsZ;
extern void *_file_CheadstevemZ;
extern void *_file_Pa51_roofgunZ;
extern void *_file_Psk_drone_gunZ;
extern void *_file_Pci_roofgunZ;
extern void *_file_Pcv_tableZ;
extern void *_file_Cdark_leatherZ;
extern void *_file_Cheaddark_snowZ;
extern void *_file_CheadpresidentZ;
extern void *_file_Pcidoor1_refZ;
extern void *_file_Palaskadoor_outZ;
extern void *_file_Palaskadoor_inZ;
extern void *_file_PwirefenceZ;
extern void *_file_PrarelogoZ;
extern void *_file_Chead_vdZ;
extern void *_file_Apelelv02M;
extern void *_file_PkeycardZ;
extern void *_file_PbodyarmourZ;
extern void *_file_Pa51gate_rZ;
extern void *_file_Pa51gate_lZ;
extern void *_file_Paf1_lampZ;
extern void *_file_Paf1_toiletZ;
extern void *_file_Paf1_doorbig2Z;
extern void *_file_Paf1_phoneZ;
extern void *_file_Paf1_cargodoorZ;
extern void *_file_Pg5_alarmZ;
extern void *_file_Pg5_laser_switchZ;
extern void *_file_Psk_templecolumn4Z;
extern void *_file_PcorehatchZ;
extern void *_file_LameE;
extern void *_file_LameJ;
extern void *_file_LameP;
extern void *_file_Lame_str_gZ;
extern void *_file_Lame_str_fZ;
extern void *_file_Lame_str_sZ;
extern void *_file_Lame_str_iZ;
extern void *_file_LarchE;
extern void *_file_LarchJ;
extern void *_file_LarchP;
extern void *_file_Larch_str_gZ;
extern void *_file_Larch_str_fZ;
extern void *_file_Larch_str_sZ;
extern void *_file_Larch_str_iZ;
extern void *_file_LarecE;
extern void *_file_LarecJ;
extern void *_file_LarecP;
extern void *_file_Larec_str_gZ;
extern void *_file_Larec_str_fZ;
extern void *_file_Larec_str_sZ;
extern void *_file_Larec_str_iZ;
extern void *_file_LarkE;
extern void *_file_LarkJ;
extern void *_file_LarkP;
extern void *_file_Lark_str_gZ;
extern void *_file_Lark_str_fZ;
extern void *_file_Lark_str_sZ;
extern void *_file_Lark_str_iZ;
extern void *_file_LashE;
extern void *_file_LashJ;
extern void *_file_LashP;
extern void *_file_Lash_str_gZ;
extern void *_file_Lash_str_fZ;
extern void *_file_Lash_str_sZ;
extern void *_file_Lash_str_iZ;
extern void *_file_LateE;
extern void *_file_LateJ;
extern void *_file_LateP;
extern void *_file_Late_str_gZ;
extern void *_file_Late_str_fZ;
extern void *_file_Late_str_sZ;
extern void *_file_Late_str_iZ;
extern void *_file_LaztE;
extern void *_file_LaztJ;
extern void *_file_LaztP;
extern void *_file_Lazt_str_gZ;
extern void *_file_Lazt_str_fZ;
extern void *_file_Lazt_str_sZ;
extern void *_file_Lazt_str_iZ;
extern void *_file_LcatE;
extern void *_file_LcatJ;
extern void *_file_LcatP;
extern void *_file_Lcat_str_gZ;
extern void *_file_Lcat_str_fZ;
extern void *_file_Lcat_str_sZ;
extern void *_file_Lcat_str_iZ;
extern void *_file_LcaveE;
extern void *_file_LcaveJ;
extern void *_file_LcaveP;
extern void *_file_Lcave_str_gZ;
extern void *_file_Lcave_str_fZ;
extern void *_file_Lcave_str_sZ;
extern void *_file_Lcave_str_iZ;
extern void *_file_LcradE;
extern void *_file_LcradJ;
extern void *_file_LcradP;
extern void *_file_Lcrad_str_gZ;
extern void *_file_Lcrad_str_fZ;
extern void *_file_Lcrad_str_sZ;
extern void *_file_Lcrad_str_iZ;
extern void *_file_LcrypE;
extern void *_file_LcrypJ;
extern void *_file_LcrypP;
extern void *_file_Lcryp_str_gZ;
extern void *_file_Lcryp_str_fZ;
extern void *_file_Lcryp_str_sZ;
extern void *_file_Lcryp_str_iZ;
extern void *_file_LdamE;
extern void *_file_LdamJ;
extern void *_file_LdamP;
extern void *_file_Ldam_str_gZ;
extern void *_file_Ldam_str_fZ;
extern void *_file_Ldam_str_sZ;
extern void *_file_Ldam_str_iZ;
extern void *_file_LdepoE;
extern void *_file_LdepoJ;
extern void *_file_LdepoP;
extern void *_file_Ldepo_str_gZ;
extern void *_file_Ldepo_str_fZ;
extern void *_file_Ldepo_str_sZ;
extern void *_file_Ldepo_str_iZ;
extern void *_file_LdestE;
extern void *_file_LdestJ;
extern void *_file_LdestP;
extern void *_file_Ldest_str_gZ;
extern void *_file_Ldest_str_fZ;
extern void *_file_Ldest_str_sZ;
extern void *_file_Ldest_str_iZ;
extern void *_file_LdishE;
extern void *_file_LdishJ;
extern void *_file_LdishP;
extern void *_file_Ldish_str_gZ;
extern void *_file_Ldish_str_fZ;
extern void *_file_Ldish_str_sZ;
extern void *_file_Ldish_str_iZ;
extern void *_file_LearE;
extern void *_file_LearJ;
extern void *_file_LearP;
extern void *_file_Lear_str_gZ;
extern void *_file_Lear_str_fZ;
extern void *_file_Lear_str_sZ;
extern void *_file_Lear_str_iZ;
extern void *_file_LeldE;
extern void *_file_LeldJ;
extern void *_file_LeldP;
extern void *_file_Leld_str_gZ;
extern void *_file_Leld_str_fZ;
extern void *_file_Leld_str_sZ;
extern void *_file_Leld_str_iZ;
extern void *_file_LgunE;
extern void *_file_LgunJ;
extern void *_file_LgunP;
extern void *_file_Lgun_str_gZ;
extern void *_file_Lgun_str_fZ;
extern void *_file_Lgun_str_sZ;
extern void *_file_Lgun_str_iZ;
extern void *_file_LimpE;
extern void *_file_LimpJ;
extern void *_file_LimpP;
extern void *_file_Limp_str_gZ;
extern void *_file_Limp_str_fZ;
extern void *_file_Limp_str_sZ;
extern void *_file_Limp_str_iZ;
extern void *_file_LjunE;
extern void *_file_LjunJ;
extern void *_file_LjunP;
extern void *_file_Ljun_str_gZ;
extern void *_file_Ljun_str_fZ;
extern void *_file_Ljun_str_sZ;
extern void *_file_Ljun_str_iZ;
extern void *_file_LlamE;
extern void *_file_LlamJ;
extern void *_file_LlamP;
extern void *_file_Llam_str_gZ;
extern void *_file_Llam_str_fZ;
extern void *_file_Llam_str_sZ;
extern void *_file_Llam_str_iZ;
extern void *_file_LleeE;
extern void *_file_LleeJ;
extern void *_file_LleeP;
extern void *_file_Llee_str_gZ;
extern void *_file_Llee_str_fZ;
extern void *_file_Llee_str_sZ;
extern void *_file_Llee_str_iZ;
extern void *_file_LlenE;
extern void *_file_LlenJ;
extern void *_file_LlenP;
extern void *_file_Llen_str_gZ;
extern void *_file_Llen_str_fZ;
extern void *_file_Llen_str_sZ;
extern void *_file_Llen_str_iZ;
extern void *_file_LlipE;
extern void *_file_LlipJ;
extern void *_file_LlipP;
extern void *_file_Llip_str_gZ;
extern void *_file_Llip_str_fZ;
extern void *_file_Llip_str_sZ;
extern void *_file_Llip_str_iZ;
extern void *_file_LlueE;
extern void *_file_LlueJ;
extern void *_file_LlueP;
extern void *_file_Llue_str_gZ;
extern void *_file_Llue_str_fZ;
extern void *_file_Llue_str_sZ;
extern void *_file_Llue_str_iZ;
extern void *_file_LmiscE;
extern void *_file_LmiscJ;
extern void *_file_LmiscP;
extern void *_file_Lmisc_str_gZ;
extern void *_file_Lmisc_str_fZ;
extern void *_file_Lmisc_str_sZ;
extern void *_file_Lmisc_str_iZ;
extern void *_file_Lmp10E;
extern void *_file_Lmp10J;
extern void *_file_Lmp10P;
extern void *_file_Lmp10_str_gZ;
extern void *_file_Lmp10_str_fZ;
extern void *_file_Lmp10_str_sZ;
extern void *_file_Lmp10_str_iZ;
extern void *_file_Lmp11E;
extern void *_file_Lmp11J;
extern void *_file_Lmp11P;
extern void *_file_Lmp11_str_gZ;
extern void *_file_Lmp11_str_fZ;
extern void *_file_Lmp11_str_sZ;
extern void *_file_Lmp11_str_iZ;
extern void *_file_Lmp12E;
extern void *_file_Lmp12J;
extern void *_file_Lmp12P;
extern void *_file_Lmp12_str_gZ;
extern void *_file_Lmp12_str_fZ;
extern void *_file_Lmp12_str_sZ;
extern void *_file_Lmp12_str_iZ;
extern void *_file_Lmp13E;
extern void *_file_Lmp13J;
extern void *_file_Lmp13P;
extern void *_file_Lmp13_str_gZ;
extern void *_file_Lmp13_str_fZ;
extern void *_file_Lmp13_str_sZ;
extern void *_file_Lmp13_str_iZ;
extern void *_file_Lmp14E;
extern void *_file_Lmp14J;
extern void *_file_Lmp14P;
extern void *_file_Lmp14_str_gZ;
extern void *_file_Lmp14_str_fZ;
extern void *_file_Lmp14_str_sZ;
extern void *_file_Lmp14_str_iZ;
extern void *_file_Lmp15E;
extern void *_file_Lmp15J;
extern void *_file_Lmp15P;
extern void *_file_Lmp15_str_gZ;
extern void *_file_Lmp15_str_fZ;
extern void *_file_Lmp15_str_sZ;
extern void *_file_Lmp15_str_iZ;
extern void *_file_Lmp16E;
extern void *_file_Lmp16J;
extern void *_file_Lmp16P;
extern void *_file_Lmp16_str_gZ;
extern void *_file_Lmp16_str_fZ;
extern void *_file_Lmp16_str_sZ;
extern void *_file_Lmp16_str_iZ;
extern void *_file_Lmp17E;
extern void *_file_Lmp17J;
extern void *_file_Lmp17P;
extern void *_file_Lmp17_str_gZ;
extern void *_file_Lmp17_str_fZ;
extern void *_file_Lmp17_str_sZ;
extern void *_file_Lmp17_str_iZ;
extern void *_file_Lmp18E;
extern void *_file_Lmp18J;
extern void *_file_Lmp18P;
extern void *_file_Lmp18_str_gZ;
extern void *_file_Lmp18_str_fZ;
extern void *_file_Lmp18_str_sZ;
extern void *_file_Lmp18_str_iZ;
extern void *_file_Lmp19E;
extern void *_file_Lmp19J;
extern void *_file_Lmp19P;
extern void *_file_Lmp19_str_gZ;
extern void *_file_Lmp19_str_fZ;
extern void *_file_Lmp19_str_sZ;
extern void *_file_Lmp19_str_iZ;
extern void *_file_Lmp1E;
extern void *_file_Lmp1J;
extern void *_file_Lmp1P;
extern void *_file_Lmp1_str_gZ;
extern void *_file_Lmp1_str_fZ;
extern void *_file_Lmp1_str_sZ;
extern void *_file_Lmp1_str_iZ;
extern void *_file_Lmp20E;
extern void *_file_Lmp20J;
extern void *_file_Lmp20P;
extern void *_file_Lmp20_str_gZ;
extern void *_file_Lmp20_str_fZ;
extern void *_file_Lmp20_str_sZ;
extern void *_file_Lmp20_str_iZ;
extern void *_file_Lmp2E;
extern void *_file_Lmp2J;
extern void *_file_Lmp2P;
extern void *_file_Lmp2_str_gZ;
extern void *_file_Lmp2_str_fZ;
extern void *_file_Lmp2_str_sZ;
extern void *_file_Lmp2_str_iZ;
extern void *_file_Lmp3E;
extern void *_file_Lmp3J;
extern void *_file_Lmp3P;
extern void *_file_Lmp3_str_gZ;
extern void *_file_Lmp3_str_fZ;
extern void *_file_Lmp3_str_sZ;
extern void *_file_Lmp3_str_iZ;
extern void *_file_Lmp4E;
extern void *_file_Lmp4J;
extern void *_file_Lmp4P;
extern void *_file_Lmp4_str_gZ;
extern void *_file_Lmp4_str_fZ;
extern void *_file_Lmp4_str_sZ;
extern void *_file_Lmp4_str_iZ;
extern void *_file_Lmp5E;
extern void *_file_Lmp5J;
extern void *_file_Lmp5P;
extern void *_file_Lmp5_str_gZ;
extern void *_file_Lmp5_str_fZ;
extern void *_file_Lmp5_str_sZ;
extern void *_file_Lmp5_str_iZ;
extern void *_file_Lmp6E;
extern void *_file_Lmp6J;
extern void *_file_Lmp6P;
extern void *_file_Lmp6_str_gZ;
extern void *_file_Lmp6_str_fZ;
extern void *_file_Lmp6_str_sZ;
extern void *_file_Lmp6_str_iZ;
extern void *_file_Lmp7E;
extern void *_file_Lmp7J;
extern void *_file_Lmp7P;
extern void *_file_Lmp7_str_gZ;
extern void *_file_Lmp7_str_fZ;
extern void *_file_Lmp7_str_sZ;
extern void *_file_Lmp7_str_iZ;
extern void *_file_Lmp8E;
extern void *_file_Lmp8J;
extern void *_file_Lmp8P;
extern void *_file_Lmp8_str_gZ;
extern void *_file_Lmp8_str_fZ;
extern void *_file_Lmp8_str_sZ;
extern void *_file_Lmp8_str_iZ;
extern void *_file_Lmp9E;
extern void *_file_Lmp9J;
extern void *_file_Lmp9P;
extern void *_file_Lmp9_str_gZ;
extern void *_file_Lmp9_str_fZ;
extern void *_file_Lmp9_str_sZ;
extern void *_file_Lmp9_str_iZ;
extern void *_file_LmpmenuE;
extern void *_file_LmpmenuJ;
extern void *_file_LmpmenuP;
extern void *_file_Lmpmenu_str_gZ;
extern void *_file_Lmpmenu_str_fZ;
extern void *_file_Lmpmenu_str_sZ;
extern void *_file_Lmpmenu_str_iZ;
extern void *_file_LmpweaponsE;
extern void *_file_LmpweaponsJ;
extern void *_file_LmpweaponsP;
extern void *_file_Lmpweapons_str_gZ;
extern void *_file_Lmpweapons_str_fZ;
extern void *_file_Lmpweapons_str_sZ;
extern void *_file_Lmpweapons_str_iZ;
extern void *_file_LoatE;
extern void *_file_LoatJ;
extern void *_file_LoatP;
extern void *_file_Loat_str_gZ;
extern void *_file_Loat_str_fZ;
extern void *_file_Loat_str_sZ;
extern void *_file_Loat_str_iZ;
extern void *_file_LoldE;
extern void *_file_LoldJ;
extern void *_file_LoldP;
extern void *_file_Lold_str_gZ;
extern void *_file_Lold_str_fZ;
extern void *_file_Lold_str_sZ;
extern void *_file_Lold_str_iZ;
extern void *_file_LoptionsE;
extern void *_file_LoptionsJ;
extern void *_file_LoptionsP;
extern void *_file_Loptions_str_gZ;
extern void *_file_Loptions_str_fZ;
extern void *_file_Loptions_str_sZ;
extern void *_file_Loptions_str_iZ;
extern void *_file_LpamE;
extern void *_file_LpamJ;
extern void *_file_LpamP;
extern void *_file_Lpam_str_gZ;
extern void *_file_Lpam_str_fZ;
extern void *_file_Lpam_str_sZ;
extern void *_file_Lpam_str_iZ;
extern void *_file_LpeteE;
extern void *_file_LpeteJ;
extern void *_file_LpeteP;
extern void *_file_Lpete_str_gZ;
extern void *_file_Lpete_str_fZ;
extern void *_file_Lpete_str_sZ;
extern void *_file_Lpete_str_iZ;
extern void *_file_LpropobjE;
extern void *_file_LpropobjJ;
extern void *_file_LpropobjP;
extern void *_file_Lpropobj_str_gZ;
extern void *_file_Lpropobj_str_fZ;
extern void *_file_Lpropobj_str_sZ;
extern void *_file_Lpropobj_str_iZ;
extern void *_file_LrefE;
extern void *_file_LrefJ;
extern void *_file_LrefP;
extern void *_file_Lref_str_gZ;
extern void *_file_Lref_str_fZ;
extern void *_file_Lref_str_sZ;
extern void *_file_Lref_str_iZ;
extern void *_file_LritE;
extern void *_file_LritJ;
extern void *_file_LritP;
extern void *_file_Lrit_str_gZ;
extern void *_file_Lrit_str_fZ;
extern void *_file_Lrit_str_sZ;
extern void *_file_Lrit_str_iZ;
extern void *_file_LrunE;
extern void *_file_LrunJ;
extern void *_file_LrunP;
extern void *_file_Lrun_str_gZ;
extern void *_file_Lrun_str_fZ;
extern void *_file_Lrun_str_sZ;
extern void *_file_Lrun_str_iZ;
extern void *_file_LsevE;
extern void *_file_LsevJ;
extern void *_file_LsevP;
extern void *_file_Lsev_str_gZ;
extern void *_file_Lsev_str_fZ;
extern void *_file_Lsev_str_sZ;
extern void *_file_Lsev_str_iZ;
extern void *_file_LsevbE;
extern void *_file_LsevbJ;
extern void *_file_LsevbP;
extern void *_file_Lsevb_str_gZ;
extern void *_file_Lsevb_str_fZ;
extern void *_file_Lsevb_str_sZ;
extern void *_file_Lsevb_str_iZ;
extern void *_file_LsevxE;
extern void *_file_LsevxJ;
extern void *_file_LsevxP;
extern void *_file_Lsevx_str_gZ;
extern void *_file_Lsevx_str_fZ;
extern void *_file_Lsevx_str_sZ;
extern void *_file_Lsevx_str_iZ;
extern void *_file_LsevxbE;
extern void *_file_LsevxbJ;
extern void *_file_LsevxbP;
extern void *_file_Lsevxb_str_gZ;
extern void *_file_Lsevxb_str_fZ;
extern void *_file_Lsevxb_str_sZ;
extern void *_file_Lsevxb_str_iZ;
extern void *_file_LshoE;
extern void *_file_LshoJ;
extern void *_file_LshoP;
extern void *_file_Lsho_str_gZ;
extern void *_file_Lsho_str_fZ;
extern void *_file_Lsho_str_sZ;
extern void *_file_Lsho_str_iZ;
extern void *_file_LsiloE;
extern void *_file_LsiloJ;
extern void *_file_LsiloP;
extern void *_file_Lsilo_str_gZ;
extern void *_file_Lsilo_str_fZ;
extern void *_file_Lsilo_str_sZ;
extern void *_file_Lsilo_str_iZ;
extern void *_file_LstatE;
extern void *_file_LstatJ;
extern void *_file_LstatP;
extern void *_file_Lstat_str_gZ;
extern void *_file_Lstat_str_fZ;
extern void *_file_Lstat_str_sZ;
extern void *_file_Lstat_str_iZ;
extern void *_file_LtitleE;
extern void *_file_LtitleJ;
extern void *_file_LtitleP;
extern void *_file_Ltitle_str_gZ;
extern void *_file_Ltitle_str_fZ;
extern void *_file_Ltitle_str_sZ;
extern void *_file_Ltitle_str_iZ;
extern void *_file_LtraE;
extern void *_file_LtraJ;
extern void *_file_LtraP;
extern void *_file_Ltra_str_gZ;
extern void *_file_Ltra_str_fZ;
extern void *_file_Ltra_str_sZ;
extern void *_file_Ltra_str_iZ;
extern void *_file_LuffE;
extern void *_file_LuffJ;
extern void *_file_LuffP;
extern void *_file_Luff_str_gZ;
extern void *_file_Luff_str_fZ;
extern void *_file_Luff_str_sZ;
extern void *_file_Luff_str_iZ;
extern void *_file_LwaxE;
extern void *_file_LwaxJ;
extern void *_file_LwaxP;
extern void *_file_Lwax_str_gZ;
extern void *_file_Lwax_str_fZ;
extern void *_file_Lwax_str_sZ;
extern void *_file_Lwax_str_iZ;
extern void *_file_Pa51grateZ;
extern void *_file_GecmmineZ;
extern void *_file_GcommsuplinkZ;
extern void *_file_GirscannerZ;
extern void *_file_Paf1escapedoorZ;
extern void *_file_PprescapsuleZ;
extern void *_file_PskedarbridgeZ;
extern void *_file_Ppelagicdoor2Z;
extern void *_file_Avault2M;
extern void *_file_Ap29_12_elM;
extern void *_file_Pttb_boxZ;
extern void *_file_PinstfrontdoorZ;
extern void *_file_Ap14_09_joM;
extern void *_file_Ap19_07_joM;
extern void *_file_Ap19_08_joM;
extern void *_file_PchrlaserZ;
extern void *_file_PbaftaZ;
extern void *_file_PchrsonicscrewerZ;
extern void *_file_PchrlumphammerZ;
extern void *_file_PskedarbombZ;
extern void *_file_PexplosivebrickZ;
extern void *_file_PresearchtapeZ;
extern void *_file_PziggycardZ;
extern void *_file_PsafeitemZ;
extern void *_file_Ghand_elvisZ;
extern void *_file_Paf1_tableZ;
extern void *_file_Ghand_a51guardZ;
extern void *_file_Ghand_ddshockZ;
extern void *_file_Ghand_blackguardZ;
extern void *_file_Ghand_ddfodderZ;
extern void *_file_Ghand_ddbioZ;
extern void *_file_Ghand_a51airmanZ;
extern void *_file_Ghand_g5guardZ;
extern void *_file_Ghand_cisoldierZ;
extern void *_file_PsensitiveinfoZ;
extern void *_file_PrussdarZ;
extern void *_file_PxrayspecsZ;
extern void *_file_PchreyespyZ;
extern void *_file_PchrdoordecoderZ;
extern void *_file_PbriefcaseZ;
extern void *_file_PsuitcaseZ;
extern void *_file_PshuttledoorZ;
extern void *_file_PruinbridgeZ;
extern void *_file_PsecretindoorZ;
extern void *_file_PskpuzzleobjectZ;
extern void *_file_Pa51liftdoorZ;
extern void *_file_Acicarr06M;
extern void *_file_Acicarr11M;
extern void *_file_Acifarr08M;
extern void *_file_Acifarr12M;
extern void *_file_Acifema01M;
extern void *_file_Acifema04M;
extern void *_file_Acifema07M;
extern void *_file_Acifema08M;
extern void *_file_Acifema09M;
extern void *_file_Acifema14M;
extern void *_file_Acifost08M;
extern void *_file_Acifost12M;
extern void *_file_Acigrim05M;
extern void *_file_Acigrim06M;
extern void *_file_Acigrim07M;
extern void *_file_Acigrim08M;
extern void *_file_Acigrim09M;
extern void *_file_Acigrim10M;
extern void *_file_Acihopk09M;
extern void *_file_Acihopk11M;
extern void *_file_Acimale02M;
extern void *_file_Acimale03M;
extern void *_file_Acimale07M;
extern void *_file_Acimale09M;
extern void *_file_Acimale11M;
extern void *_file_Acimale13M;
extern void *_file_Aciroge08M;
extern void *_file_Aciroge12M;
extern void *_file_Cdark_negotiatorZ;
extern void *_file_PcihubZ;
extern void *_file_Psk_ship_door2Z;
extern void *_file_Psk_window1Z;
extern void *_file_Psk_hangardoorb_topZ;
extern void *_file_Psk_hangardoorb_botZ;
extern void *_file_Paf1_innerdoorZ;
extern void *_file_Plaser_postZ;
extern void *_file_Atrfost01M;
extern void *_file_Atrfost02M;
extern void *_file_Atrfost03M;
extern void *_file_Atrcarr09M;
extern void *_file_Atrcarr10M;
extern void *_file_Atrcarr11M;
extern void *_file_Acifarr01M;
extern void *_file_Acifarr02M;
extern void *_file_Acifarr03M;
extern void *_file_Acigrim01M;
extern void *_file_Acigrim03M;
extern void *_file_Acigrim04M;
extern void *_file_Acihopk01M;
extern void *_file_Acihopk04M;
extern void *_file_Acihopk06M;
extern void *_file_Aciroge01M;
extern void *_file_Aciroge02M;
extern void *_file_Atrroge01M;
extern void *_file_Acicarr07M;
extern void *_file_Acicarr08M;
extern void *_file_PtargetampZ;
extern void *_file_Psk_liftZ;
extern void *_file_PknockknockZ;
extern void *_file_PcetandoorZ;
extern void *_file_Ajoinst01M;
extern void *_file_Ajoinst02M;
extern void *_file_Ajoinst03M;
extern void *_file_Ajoinst04M;
extern void *_file_Ap25_03_joM;
extern void *_file_Paf1rubbleZ;
extern void *_file_Pdd_dr_nonrefZ;
extern void *_file_CheadtimZ;
extern void *_file_CheadgrantZ;
extern void *_file_CheadpennyZ;
extern void *_file_CheadrobinZ;
extern void *_file_CheadalexZ;
extern void *_file_CheadjulianneZ;
extern void *_file_CheadlauraZ;
extern void *_file_CheaddavecZ;
extern void *_file_CheadkenZ;
extern void *_file_CheadjoelZ;
extern void *_file_PcetandoorsideZ;
extern void *_file_Ap29_13_joM;
extern void *_file_Ap29_14_joM;
extern void *_file_Acicarr09M;
extern void *_file_Acicarr10M;
extern void *_file_PbuddybridgeZ;
extern void *_file_CheadcookZ;
extern void *_file_CheadpryceZ;
extern void *_file_CheadsilkeZ;
extern void *_file_CheadsmithZ;
extern void *_file_CheadgarethZ;
extern void *_file_CheadmurchieZ;
extern void *_file_CheadwongZ;
extern void *_file_CheadcarterZ;
extern void *_file_CheadtintinZ;
extern void *_file_CheadmuntonZ;
extern void *_file_CheadstamperZ;
extern void *_file_CheadjonesZ;
extern void *_file_CheadphelpsZ;
extern void *_file_Ap29_15_joM;
extern void *_file_Ap16_03_joM;
extern void *_file_Acarrbye02M;
#if VERSION >= VERSION_NTSC_1_0
extern void *_file_Asaucerexp1M;
#endif
extern void *_filenamesSegmentRomStart;

#if VERSION < VERSION_NTSC_1_0
const char var7f1b1d40nb[] = "DMA-Crash %s %d Ram: %02x%02x%02x%02x%02x%02x%02x%02x";
const char var7f1b1d78nb[] = "ob.c";
const char var7f1b1d80nb[] = "DMA-Crash %s %d Ram: %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x";
const char var7f1b1dd8nb[] = "ob.c";
#endif

struct fileinfo g_FileInfo[NUM_FILES];
u32 var800aa570;

void *filetable[] = {
	/*0x0000*/ NULL,
	/*0x0001*/ &_file_bg_sev_seg,
	/*0x0002*/ &_file_bg_silo_seg,
	/*0x0003*/ &_file_bg_stat_seg,
	/*0x0004*/ &_file_bg_arec_seg,
	/*0x0005*/ &_file_bg_arch_seg,
	/*0x0006*/ &_file_bg_tra_seg,
	/*0x0007*/ &_file_bg_dest_seg,
	/*0x0008*/ &_file_bg_sevb_seg,
	/*0x0009*/ &_file_bg_azt_seg,
	/*0x000a*/ &_file_bg_pete_seg,
	/*0x000b*/ &_file_bg_depo_seg,
	/*0x000c*/ &_file_bg_ref_seg,
	/*0x000d*/ &_file_bg_cryp_seg,
	/*0x000e*/ &_file_bg_dam_seg,
	/*0x000f*/ &_file_bg_ark_seg,
	/*0x0010*/ &_file_bg_run_seg,
	/*0x0011*/ &_file_bg_sevx_seg,
	/*0x0012*/ &_file_bg_jun_seg,
	/*0x0013*/ &_file_bg_dish_seg,
	/*0x0014*/ &_file_bg_cave_seg,
	/*0x0015*/ &_file_bg_cat_seg,
	/*0x0016*/ &_file_bg_crad_seg,
	/*0x0017*/ &_file_bg_sho_seg,
	/*0x0018*/ &_file_bg_eld_seg,
	/*0x0019*/ &_file_bg_imp_seg,
	/*0x001a*/ &_file_bg_ash_seg,
	/*0x001b*/ &_file_bg_lue_seg,
	/*0x001c*/ &_file_bg_ame_seg,
	/*0x001d*/ &_file_bg_rit_seg,
	/*0x001e*/ &_file_bg_oat_seg,
	/*0x001f*/ &_file_bg_ear_seg,
	/*0x0020*/ &_file_bg_lee_seg,
	/*0x0021*/ &_file_bg_lip_seg,
	/*0x0022*/ &_file_bg_len_seg,
	/*0x0023*/ &_file_bg_wax_seg,
	/*0x0024*/ &_file_bg_pam_seg,
	/*0x0025*/ &_file_bg_uff_seg,
	/*0x0026*/ &_file_bg_old_seg,
	/*0x0027*/ &_file_bg_ate_seg,
	/*0x0028*/ &_file_bg_lam_seg,
	/*0x0029*/ &_file_bg_mp1_seg,
	/*0x002a*/ &_file_bg_mp2_seg,
	/*0x002b*/ &_file_bg_mp3_seg,
	/*0x002c*/ &_file_bg_mp4_seg,
	/*0x002d*/ &_file_bg_mp5_seg,
	/*0x002e*/ &_file_bg_mp6_seg,
	/*0x002f*/ &_file_bg_mp7_seg,
	/*0x0030*/ &_file_bg_mp8_seg,
	/*0x0031*/ &_file_bg_mp9_seg,
	/*0x0032*/ &_file_bg_mp10_seg,
	/*0x0033*/ &_file_bg_mp11_seg,
	/*0x0034*/ &_file_bg_mp12_seg,
	/*0x0035*/ &_file_bg_mp13_seg,
	/*0x0036*/ &_file_bg_mp14_seg,
	/*0x0037*/ &_file_bg_mp15_seg,
	/*0x0038*/ &_file_bg_mp16_seg,
	/*0x0039*/ &_file_bg_mp17_seg,
	/*0x003a*/ &_file_bg_mp18_seg,
	/*0x003b*/ &_file_bg_mp19_seg,
	/*0x003c*/ &_file_bg_mp20_seg,
	/*0x003d*/ &_file_ob_mid_seg,
	/*0x003e*/ &_file_Ca51guardZ,
	/*0x003f*/ &_file_Carea51guardZ,
	/*0x0040*/ &_file_CcarringtonZ,
	/*0x0041*/ &_file_CcassandraZ,
	/*0x0042*/ &_file_Cdark_combatZ,
	/*0x0043*/ &_file_Cdark_frockZ,
	/*0x0044*/ &_file_Cdark_trenchZ,
	/*0x0045*/ &_file_CddshockZ,
	/*0x0046*/ &_file_Cdd_secguardZ,
	/*0x0047*/ &_file_CdjbondZ,
	/*0x0048*/ &_file_CdrcarrollZ,
	/*0x0049*/ &_file_CelvisZ,
	/*0x004a*/ &_file_Celvis1Z,
	/*0x004b*/ &_file_CeyespyZ,
	/*0x004c*/ &_file_Cfem_guardZ,
	/*0x004d*/ &_file_ClabtechZ,
	/*0x004e*/ &_file_CmrblondeZ,
	/*0x004f*/ &_file_CofficeworkerZ,
	/*0x0050*/ &_file_Cofficeworker2Z,
	/*0x0051*/ &_file_CoverallZ,
	/*0x0052*/ &_file_CsecretaryZ,
	/*0x0053*/ &_file_CskedarZ,
	/*0x0054*/ &_file_CstripesZ,
	/*0x0055*/ &_file_CtestchrZ,
	/*0x0056*/ &_file_CthekingZ,
	/*0x0057*/ &_file_CtrentZ,
	/*0x0058*/ &_file_GcartblueZ,
	/*0x0059*/ &_file_GcartridgeZ,
	/*0x005a*/ &_file_GcartrifleZ,
	/*0x005b*/ &_file_GcartshellZ,
	/*0x005c*/ &_file_GjoypadZ,
	/*0x005d*/ &_file_Pa51_crate1Z,
	/*0x005e*/ &_file_Pa51_crate2Z,
	/*0x005f*/ &_file_Pa51_crate3Z,
	/*0x0060*/ &_file_Pa51_exp1Z,
	/*0x0061*/ &_file_Pa51_exp2Z,
	/*0x0062*/ &_file_Pa51_horiz_door_botZ,
	/*0x0063*/ &_file_Pa51_horiz_door_glZ,
	/*0x0064*/ &_file_Pa51_horiz_door_secretZ,
	/*0x0065*/ &_file_Pa51_horiz_door_topZ,
	/*0x0066*/ &_file_Pa51_lift_controlZ,
	/*0x0067*/ &_file_Pa51_lift_hangarZ,
	/*0x0068*/ &_file_Pa51_lift_storeZ,
	/*0x0069*/ &_file_Pa51_lift_thinwallZ,
	/*0x006a*/ &_file_Pa51_unexp1Z,
	/*0x006b*/ &_file_Pa51_unexp2Z,
	/*0x006c*/ &_file_Pa51_unexp3Z,
	/*0x006d*/ &_file_Pa51_vert_door_leftZ,
	/*0x006e*/ &_file_Pa51_vert_door_rightZ,
	/*0x006f*/ &_file_Pa51_vert_door_stZ,
	/*0x0070*/ &_file_Pa51boardZ,
	/*0x0071*/ &_file_Pa51chairZ,
	/*0x0072*/ &_file_Pa51deskentZ,
	/*0x0073*/ &_file_Pa51divideZ,
	/*0x0074*/ &_file_Pa51screenZ,
	/*0x0075*/ &_file_Pa51tableZ,
	/*0x0076*/ &_file_Pa51trolleyZ,
	/*0x0077*/ &_file_Pa51wastebinZ,
	/*0x0078*/ &_file_Paivillabot1Z,
	/*0x0079*/ &_file_Paivillabot2Z,
	/*0x007a*/ &_file_Paivillabot3Z,
	/*0x007b*/ &_file_Paivilladoor1Z,
	/*0x007c*/ &_file_Paivilladoor2aZ,
	/*0x007d*/ &_file_Paivilladoor4Z,
	/*0x007e*/ &_file_PaivillawindmillZ,
	/*0x007f*/ &_file_Pal_airlockZ,
	/*0x0080*/ &_file_Pal_dockliftZ,
	/*0x0081*/ &_file_Paldoor_lZ,
	/*0x0082*/ &_file_Paldoor_rZ,
	/*0x0083*/ &_file_Pborg_crateZ,
	/*0x0084*/ &_file_PcaseZ,
	/*0x0085*/ &_file_Pch_shutter1Z,
	/*0x0086*/ &_file_PchrbriefcaseZ,
	/*0x0087*/ &_file_PchrbugZ,
	/*0x0088*/ &_file_PchrdatathiefZ,
	/*0x0089*/ &_file_Pcryptdoor1bZ,
	/*0x008a*/ &_file_Pdd_ac_expZ,
	/*0x008b*/ &_file_Pdd_ac_unexpZ,
	/*0x008c*/ &_file_Pdd_acbot_expZ,
	/*0x008d*/ &_file_Pdd_acbot_unexpZ,
	/*0x008e*/ &_file_Pdd_bannerZ,
	/*0x008f*/ &_file_Pdd_chairZ,
	/*0x0090*/ &_file_Pdd_decodoorZ,
	/*0x0091*/ &_file_Pdd_deskZ,
	/*0x0092*/ &_file_Pdd_fanroofZ,
	/*0x0093*/ &_file_Pdd_fanwallZ,
	/*0x0094*/ &_file_Pdd_hovcabZ,
	/*0x0095*/ &_file_Pdd_hovcarZ,
	/*0x0096*/ &_file_Pdd_hovcopZ,
	/*0x0097*/ &_file_Pdd_hovercopterZ,
	/*0x0098*/ &_file_Pdd_hovmotoZ,
	/*0x0099*/ &_file_Pdd_hovtruckZ,
	/*0x009a*/ &_file_Pdd_lab_cautionZ,
	/*0x009b*/ &_file_Pdd_lab_cautiontopZ,
	/*0x009c*/ &_file_Pdd_lab_door_bsZ,
	/*0x009d*/ &_file_Pdd_lab_door_secZ,
	/*0x009e*/ &_file_Pdd_lab_door_windZ,
	/*0x009f*/ &_file_Pdd_lab_hazardZ,
	/*0x00a0*/ &_file_Pdd_lab_restrictedZ,
	/*0x00a1*/ &_file_Pdd_lab_sector2botZ,
	/*0x00a2*/ &_file_Pdd_lab_sector2topZ,
	/*0x00a3*/ &_file_Pdd_lab_sector3Z,
	/*0x00a4*/ &_file_Pdd_lab_sector3topZ,
	/*0x00a5*/ &_file_Pdd_lab_sector3windZ,
	/*0x00a6*/ &_file_Pdd_lab_sector4topZ,
	/*0x00a7*/ &_file_Pdd_liftdoorZ,
	/*0x00a8*/ &_file_Pdd_liftrZ,
	/*0x00a9*/ &_file_Pdd_officedoorZ,
	/*0x00aa*/ &_file_Pdd_plantrubberZ,
	/*0x00ab*/ &_file_Pdd_plantspiderZ,
	/*0x00ac*/ &_file_Pdd_plantspikeZ,
	/*0x00ad*/ &_file_Pdd_redarmZ,
	/*0x00ae*/ &_file_Pdd_redsofaZ,
	/*0x00af*/ &_file_Pdd_secretdoorZ,
	/*0x00b0*/ &_file_Pdd_secretdoor2Z,
	/*0x00b1*/ &_file_Pdd_servicedoorZ,
	/*0x00b2*/ &_file_Pdd_stonedeskZ,
	/*0x00b3*/ &_file_Pdd_vertblindZ,
	/*0x00b4*/ &_file_Pdd_winddoorZ,
	/*0x00b5*/ &_file_Pdd_windowZ,
	/*0x00b6*/ &_file_PddjumpshipZ,
	/*0x00b7*/ &_file_Pdoor1a_G5Z,
	/*0x00b8*/ &_file_Pdoor1atri_G5Z,
	/*0x00b9*/ &_file_Pdoor1b_G5Z,
	/*0x00ba*/ &_file_Pdoor2_G5Z,
	/*0x00bb*/ &_file_Pdoor2a_G5Z,
	/*0x00bc*/ &_file_Pdoor4a_G5Z,
	/*0x00bd*/ &_file_Pdoor4b_G5Z,
	/*0x00be*/ &_file_Pdoor_rollertrainZ,
	/*0x00bf*/ &_file_PdoorconsoleZ,
	/*0x00c0*/ &_file_Pdr_caroll_doorZ,
	/*0x00c1*/ &_file_Pdr_caroll_door_baseZ,
	/*0x00c2*/ &_file_Pdr_caroll_door_bleftZ,
	/*0x00c3*/ &_file_Pdr_caroll_door_bmainZ,
	/*0x00c4*/ &_file_Pdr_caroll_door_brightZ,
	/*0x00c5*/ &_file_Pdr_caroll_door_leftZ,
	/*0x00c6*/ &_file_Pdr_caroll_door_mainZ,
	/*0x00c7*/ &_file_Pdr_caroll_door_rightZ,
	/*0x00c8*/ &_file_PdropshipZ,
	/*0x00c9*/ &_file_PdumpsterZ,
	/*0x00ca*/ &_file_PexplosionbitZ,
	/*0x00cb*/ &_file_PflagZ,
	/*0x00cc*/ &_file_Pg5_escdoordownZ,
	/*0x00cd*/ &_file_Pg5_escdoordownboomZ,
	/*0x00ce*/ &_file_Pg5_escdoorupZ,
	/*0x00cf*/ &_file_Pg5_escdoorupboomZ,
	/*0x00d0*/ &_file_Pg5_mainframeZ,
	/*0x00d1*/ &_file_Pg5safedoorZ,
	/*0x00d2*/ &_file_Pg5carliftdoorZ,
	/*0x00d3*/ &_file_PgoldeneyelogoZ,
	/*0x00d4*/ &_file_PhooverbotZ,
	/*0x00d5*/ &_file_PhovbikeZ,
	/*0x00d6*/ &_file_PhoverbedZ,
	/*0x00d7*/ &_file_Phovercrate1Z,
	/*0x00d8*/ &_file_PlasdoorZ,
	/*0x00d9*/ &_file_PmarkerZ,
	/*0x00da*/ &_file_Pmedlabwin1Z,
	/*0x00db*/ &_file_Pmedlabwin2Z,
	/*0x00dc*/ &_file_PmodemboxZ,
	/*0x00dd*/ &_file_PnintendologoZ,
	/*0x00de*/ &_file_Pnlogo2Z,
	/*0x00df*/ &_file_Pnlogo3Z,
	/*0x00e0*/ &_file_PnlogoZ,
	/*0x00e1*/ &_file_Ppc1Z,
	/*0x00e2*/ &_file_PpdfourZ,
	/*0x00e3*/ &_file_PpdoneZ,
	/*0x00e4*/ &_file_PpdthreeZ,
	/*0x00e5*/ &_file_PpdtwoZ,
	/*0x00e6*/ &_file_PperfectdarkZ,
	/*0x00e7*/ &_file_PpolicecarZ,
	/*0x00e8*/ &_file_PravineliftZ,
	/*0x00e9*/ &_file_PropeZ,
	/*0x00ea*/ &_file_Psk_cryopod1_botZ,
	/*0x00eb*/ &_file_Psk_cryopod1_topZ,
	/*0x00ec*/ &_file_Psk_door1Z,
	/*0x00ed*/ &_file_Psk_fighter1Z,
	/*0x00ee*/ &_file_Psk_hangardoor_botZ,
	/*0x00ef*/ &_file_Psk_hangardoor_topZ,
	/*0x00f0*/ &_file_Psk_ship_door1Z,
	/*0x00f1*/ &_file_Psk_ship_holo1Z,
	/*0x00f2*/ &_file_Psk_ship_holo2Z,
	/*0x00f3*/ &_file_Psk_ship_hulldoor1Z,
	/*0x00f4*/ &_file_Psk_ship_hulldoor2Z,
	/*0x00f5*/ &_file_Psk_ship_hulldoor3Z,
	/*0x00f6*/ &_file_Psk_ship_hulldoor4Z,
	/*0x00f7*/ &_file_Psk_under_generatorZ,
	/*0x00f8*/ &_file_Psk_under_transZ,
	/*0x00f9*/ &_file_Pskcrev_exp1Z,
	/*0x00fa*/ &_file_Pskcrev_unexp1Z,
	/*0x00fb*/ &_file_Psktnl_exp1Z,
	/*0x00fc*/ &_file_Psktnl_unexp1Z,
	/*0x00fd*/ &_file_PtaxicabZ,
	/*0x00fe*/ &_file_PtesterbotZ,
	/*0x00ff*/ &_file_PtestobjZ,
	/*0x0100*/ &_file_PtvscreenZ,
	/*0x0101*/ &_file_PwindowZ,
	/*0x0102*/ &_file_Ump_setupameZ,
	/*0x0103*/ &_file_Ump_setuparchZ,
	/*0x0104*/ &_file_Ump_setuparecZ,
	/*0x0105*/ &_file_Ump_setuparkZ,
	/*0x0106*/ &_file_Ump_setupashZ,
	/*0x0107*/ &_file_Ump_setupaztZ,
	/*0x0108*/ &_file_Ump_setupcatZ,
	/*0x0109*/ &_file_Ump_setupcaveZ,
	/*0x010a*/ &_file_Ump_setupcradZ,
	/*0x010b*/ &_file_Ump_setupcrypZ,
	/*0x010c*/ &_file_Ump_setupdamZ,
	/*0x010d*/ &_file_Ump_setupdepoZ,
	/*0x010e*/ &_file_Ump_setupdestZ,
	/*0x010f*/ &_file_Ump_setupdishZ,
	/*0x0110*/ &_file_Ump_setupearZ,
	/*0x0111*/ &_file_Ump_setupeldZ,
	/*0x0112*/ &_file_Ump_setupimpZ,
	/*0x0113*/ &_file_Ump_setupjunZ,
	/*0x0114*/ &_file_Ump_setupleeZ,
	/*0x0115*/ &_file_Ump_setuplenZ,
	/*0x0116*/ &_file_Ump_setuplipZ,
	/*0x0117*/ &_file_Ump_setuplueZ,
	/*0x0118*/ &_file_Ump_setupoatZ,
	/*0x0119*/ &_file_Ump_setuppamZ,
	/*0x011a*/ &_file_Ump_setuppeteZ,
	/*0x011b*/ &_file_Ump_setuprefZ,
	/*0x011c*/ &_file_Ump_setupritZ,
	/*0x011d*/ &_file_Ump_setuprunZ,
	/*0x011e*/ &_file_Ump_setupsevZ,
	/*0x011f*/ &_file_Ump_setupsevbZ,
	/*0x0120*/ &_file_Ump_setupsevxZ,
	/*0x0121*/ &_file_Ump_setupshoZ,
	/*0x0122*/ &_file_Ump_setupsiloZ,
	/*0x0123*/ &_file_Ump_setupstatZ,
	/*0x0124*/ &_file_Ump_setuptraZ,
	/*0x0125*/ &_file_Ump_setupwaxZ,
	/*0x0126*/ &_file_UsetupameZ,
	/*0x0127*/ &_file_UsetuparchZ,
	/*0x0128*/ &_file_UsetuparecZ,
	/*0x0129*/ &_file_UsetuparkZ,
	/*0x012a*/ &_file_UsetupashZ,
	/*0x012b*/ &_file_UsetupaztZ,
	/*0x012c*/ &_file_UsetupcatZ,
	/*0x012d*/ &_file_UsetupcaveZ,
	/*0x012e*/ &_file_UsetupcradZ,
	/*0x012f*/ &_file_UsetupcrypZ,
	/*0x0130*/ &_file_UsetupdamZ,
	/*0x0131*/ &_file_UsetupdepoZ,
	/*0x0132*/ &_file_UsetupdestZ,
	/*0x0133*/ &_file_UsetupdishZ,
	/*0x0134*/ &_file_UsetupearZ,
	/*0x0135*/ &_file_UsetupeldZ,
	/*0x0136*/ &_file_UsetupimpZ,
	/*0x0137*/ &_file_UsetupjunZ,
	/*0x0138*/ &_file_UsetupleeZ,
	/*0x0139*/ &_file_UsetuplenZ,
	/*0x013a*/ &_file_UsetuplipZ,
	/*0x013b*/ &_file_UsetuplueZ,
	/*0x013c*/ &_file_UsetupoatZ,
	/*0x013d*/ &_file_UsetuppamZ,
	/*0x013e*/ &_file_UsetuppeteZ,
	/*0x013f*/ &_file_UsetuprefZ,
	/*0x0140*/ &_file_UsetupritZ,
	/*0x0141*/ &_file_UsetuprunZ,
	/*0x0142*/ &_file_UsetupsevZ,
	/*0x0143*/ &_file_UsetupsevbZ,
	/*0x0144*/ &_file_UsetupsevxZ,
	/*0x0145*/ &_file_UsetupsevxbZ,
	/*0x0146*/ &_file_UsetupshoZ,
	/*0x0147*/ &_file_UsetupsiloZ,
	/*0x0148*/ &_file_UsetupstatZ,
	/*0x0149*/ &_file_UsetuptraZ,
	/*0x014a*/ &_file_UsetupwaxZ,
	/*0x014b*/ &_file_bg_ame_padsZ,
	/*0x014c*/ &_file_bg_ame_tilesZ,
	/*0x014d*/ &_file_bg_arch_padsZ,
	/*0x014e*/ &_file_bg_arch_tilesZ,
	/*0x014f*/ &_file_bg_arec_padsZ,
	/*0x0150*/ &_file_bg_arec_tilesZ,
	/*0x0151*/ &_file_bg_ark_padsZ,
	/*0x0152*/ &_file_bg_ark_tilesZ,
	/*0x0153*/ &_file_bg_ash_padsZ,
	/*0x0154*/ &_file_bg_ash_tilesZ,
	/*0x0155*/ &_file_bg_azt_padsZ,
	/*0x0156*/ &_file_bg_azt_tilesZ,
	/*0x0157*/ &_file_bg_cat_padsZ,
	/*0x0158*/ &_file_bg_cat_tilesZ,
	/*0x0159*/ &_file_bg_cave_padsZ,
	/*0x015a*/ &_file_bg_cave_tilesZ,
	/*0x015b*/ &_file_bg_crad_padsZ,
	/*0x015c*/ &_file_bg_crad_tilesZ,
	/*0x015d*/ &_file_bg_cryp_padsZ,
	/*0x015e*/ &_file_bg_cryp_tilesZ,
	/*0x015f*/ &_file_bg_dam_padsZ,
	/*0x0160*/ &_file_bg_dam_tilesZ,
	/*0x0161*/ &_file_bg_depo_padsZ,
	/*0x0162*/ &_file_bg_depo_tilesZ,
	/*0x0163*/ &_file_bg_dest_padsZ,
	/*0x0164*/ &_file_bg_dest_tilesZ,
	/*0x0165*/ &_file_bg_dish_padsZ,
	/*0x0166*/ &_file_bg_dish_tilesZ,
	/*0x0167*/ &_file_bg_ear_padsZ,
	/*0x0168*/ &_file_bg_ear_tilesZ,
	/*0x0169*/ &_file_bg_eld_padsZ,
	/*0x016a*/ &_file_bg_eld_tilesZ,
	/*0x016b*/ &_file_bg_imp_padsZ,
	/*0x016c*/ &_file_bg_imp_tilesZ,
	/*0x016d*/ &_file_bg_jun_padsZ,
	/*0x016e*/ &_file_bg_jun_tilesZ,
	/*0x016f*/ &_file_bg_lee_padsZ,
	/*0x0170*/ &_file_bg_lee_tilesZ,
	/*0x0171*/ &_file_bg_len_padsZ,
	/*0x0172*/ &_file_bg_len_tilesZ,
	/*0x0173*/ &_file_bg_lip_padsZ,
	/*0x0174*/ &_file_bg_lip_tilesZ,
	/*0x0175*/ &_file_bg_lue_padsZ,
	/*0x0176*/ &_file_bg_lue_tilesZ,
	/*0x0177*/ &_file_bg_oat_padsZ,
	/*0x0178*/ &_file_bg_oat_tilesZ,
	/*0x0179*/ &_file_bg_pam_padsZ,
	/*0x017a*/ &_file_bg_pam_tilesZ,
	/*0x017b*/ &_file_bg_pete_padsZ,
	/*0x017c*/ &_file_bg_pete_tilesZ,
	/*0x017d*/ &_file_bg_ref_padsZ,
	/*0x017e*/ &_file_bg_ref_tilesZ,
	/*0x017f*/ &_file_bg_rit_padsZ,
	/*0x0180*/ &_file_bg_rit_tilesZ,
	/*0x0181*/ &_file_bg_run_padsZ,
	/*0x0182*/ &_file_bg_run_tilesZ,
	/*0x0183*/ &_file_bg_sev_padsZ,
	/*0x0184*/ &_file_bg_sev_tilesZ,
	/*0x0185*/ &_file_bg_sevb_padsZ,
	/*0x0186*/ &_file_bg_sevb_tilesZ,
	/*0x0187*/ &_file_bg_sevx_padsZ,
	/*0x0188*/ &_file_bg_sevx_tilesZ,
	/*0x0189*/ &_file_bg_sho_padsZ,
	/*0x018a*/ &_file_bg_sho_tilesZ,
	/*0x018b*/ &_file_bg_silo_padsZ,
	/*0x018c*/ &_file_bg_silo_tilesZ,
	/*0x018d*/ &_file_bg_stat_padsZ,
	/*0x018e*/ &_file_bg_stat_tilesZ,
	/*0x018f*/ &_file_bg_tra_padsZ,
	/*0x0190*/ &_file_bg_tra_tilesZ,
	/*0x0191*/ &_file_bg_wax_padsZ,
	/*0x0192*/ &_file_bg_wax_tilesZ,
	/*0x0193*/ &_file_GtestgunZ,
	/*0x0194*/ &_file_Cdd_labtechZ,
	/*0x0195*/ &_file_Pcctv_pdZ,
	/*0x0196*/ &_file_PcomhubZ,
	/*0x0197*/ &_file_PquadpodZ,
	/*0x0198*/ &_file_Ppd_consoleZ,
	/*0x0199*/ &_file_CconneryZ,
	/*0x019a*/ &_file_CmooreZ,
	/*0x019b*/ &_file_CdaltonZ,
	/*0x019c*/ &_file_Cheaddark_combatZ,
	/*0x019d*/ &_file_CheadelvisZ,
	/*0x019e*/ &_file_CheadrossZ,
	/*0x019f*/ &_file_CheadcarringtonZ,
	/*0x01a0*/ &_file_CheadmrblondeZ,
	/*0x01a1*/ &_file_CheadtrentZ,
	/*0x01a2*/ &_file_CheadddshockZ,
	/*0x01a3*/ &_file_CheadgrahamZ,
	/*0x01a4*/ &_file_Cheaddark_frockZ,
	/*0x01a5*/ &_file_CheadsecretaryZ,
	/*0x01a6*/ &_file_CheadcassandraZ,
	/*0x01a7*/ &_file_CheadthekingZ,
	/*0x01a8*/ &_file_Cheadfem_guardZ,
	/*0x01a9*/ &_file_CheadjonZ,
	/*0x01aa*/ &_file_Plift_platformZ,
	/*0x01ab*/ &_file_Pdd_grateZ,
	/*0x01ac*/ &_file_PlightswitchZ,
	/*0x01ad*/ &_file_PblastshieldZ,
	/*0x01ae*/ &_file_Plightswitch2Z,
	/*0x01af*/ &_file_Pdd_accessdoorupZ,
	/*0x01b0*/ &_file_Pdd_accessdoordnZ,
	/*0x01b1*/ &_file_Cdark_rippedZ,
	/*0x01b2*/ &_file_Cheadmark2Z,
	/*0x01b3*/ &_file_CheadchristZ,
	/*0x01b4*/ &_file_Plab_containerZ,
	/*0x01b5*/ &_file_Plab_chairZ,
	/*0x01b6*/ &_file_Plab_tableZ,
	/*0x01b7*/ &_file_Plab_microscopeZ,
	/*0x01b8*/ &_file_Plab_mainframeZ,
	/*0x01b9*/ &_file_Pdd_labdoorZ,
	/*0x01ba*/ &_file_Pdd_lab_doortopZ,
	/*0x01bb*/ &_file_Pmulti_ammo_crateZ,
	/*0x01bc*/ &_file_CheadrussZ,
	/*0x01bd*/ &_file_CheadgreyZ,
	/*0x01be*/ &_file_CheaddarlingZ,
	/*0x01bf*/ &_file_Cdd_guardZ,
	/*0x01c0*/ &_file_CheadrobertZ,
	/*0x01c1*/ &_file_Cdd_shockZ,
	/*0x01c2*/ &_file_CheadbeauZ,
	/*0x01c3*/ &_file_PchrchainZ,
	/*0x01c4*/ &_file_Cdd_shock_infZ,
	/*0x01c5*/ &_file_Cheadfem_guard2Z,
	/*0x01c6*/ &_file_ProofgunZ,
	/*0x01c7*/ &_file_PtdoorZ,
	/*0x01c8*/ &_file_CbiotechZ,
	/*0x01c9*/ &_file_CfbiguyZ,
	/*0x01ca*/ &_file_PgroundgunZ,
	/*0x01cb*/ &_file_CciaguyZ,
	/*0x01cc*/ &_file_Ca51trooperZ,
	/*0x01cd*/ &_file_CheadbrianZ,
	/*0x01ce*/ &_file_CheadjamieZ,
	/*0x01cf*/ &_file_Cheadduncan2Z,
	/*0x01d0*/ &_file_CheadbiotechZ,
	/*0x01d1*/ &_file_UsetupuffZ,
	/*0x01d2*/ &_file_Ump_setupuffZ,
	/*0x01d3*/ &_file_bg_uff_padsZ,
	/*0x01d4*/ &_file_bg_uff_tilesZ,
	/*0x01d5*/ &_file_UsetupoldZ,
	/*0x01d6*/ &_file_Ump_setupoldZ,
	/*0x01d7*/ &_file_bg_old_padsZ,
	/*0x01d8*/ &_file_bg_old_tilesZ,
	/*0x01d9*/ &_file_UsetupateZ,
	/*0x01da*/ &_file_Ump_setupateZ,
	/*0x01db*/ &_file_bg_ate_padsZ,
	/*0x01dc*/ &_file_bg_ate_tilesZ,
	/*0x01dd*/ &_file_UsetuplamZ,
	/*0x01de*/ &_file_Ump_setuplamZ,
	/*0x01df*/ &_file_bg_lam_padsZ,
	/*0x01e0*/ &_file_bg_lam_tilesZ,
	/*0x01e1*/ &_file_Usetupmp1Z,
	/*0x01e2*/ &_file_Ump_setupmp1Z,
	/*0x01e3*/ &_file_bg_mp1_padsZ,
	/*0x01e4*/ &_file_bg_mp1_tilesZ,
	/*0x01e5*/ &_file_Usetupmp2Z,
	/*0x01e6*/ &_file_Ump_setupmp2Z,
	/*0x01e7*/ &_file_bg_mp2_padsZ,
	/*0x01e8*/ &_file_bg_mp2_tilesZ,
	/*0x01e9*/ &_file_Usetupmp3Z,
	/*0x01ea*/ &_file_Ump_setupmp3Z,
	/*0x01eb*/ &_file_bg_mp3_padsZ,
	/*0x01ec*/ &_file_bg_mp3_tilesZ,
	/*0x01ed*/ &_file_Usetupmp4Z,
	/*0x01ee*/ &_file_Ump_setupmp4Z,
	/*0x01ef*/ &_file_bg_mp4_padsZ,
	/*0x01f0*/ &_file_bg_mp4_tilesZ,
	/*0x01f1*/ &_file_Usetupmp5Z,
	/*0x01f2*/ &_file_Ump_setupmp5Z,
	/*0x01f3*/ &_file_bg_mp5_padsZ,
	/*0x01f4*/ &_file_bg_mp5_tilesZ,
	/*0x01f5*/ &_file_Usetupmp6Z,
	/*0x01f6*/ &_file_Ump_setupmp6Z,
	/*0x01f7*/ &_file_bg_mp6_padsZ,
	/*0x01f8*/ &_file_bg_mp6_tilesZ,
	/*0x01f9*/ &_file_Usetupmp7Z,
	/*0x01fa*/ &_file_Ump_setupmp7Z,
	/*0x01fb*/ &_file_bg_mp7_padsZ,
	/*0x01fc*/ &_file_bg_mp7_tilesZ,
	/*0x01fd*/ &_file_Usetupmp8Z,
	/*0x01fe*/ &_file_Ump_setupmp8Z,
	/*0x01ff*/ &_file_bg_mp8_padsZ,
	/*0x0200*/ &_file_bg_mp8_tilesZ,
	/*0x0201*/ &_file_Usetupmp9Z,
	/*0x0202*/ &_file_Ump_setupmp9Z,
	/*0x0203*/ &_file_bg_mp9_padsZ,
	/*0x0204*/ &_file_bg_mp9_tilesZ,
	/*0x0205*/ &_file_Usetupmp10Z,
	/*0x0206*/ &_file_Ump_setupmp10Z,
	/*0x0207*/ &_file_bg_mp10_padsZ,
	/*0x0208*/ &_file_bg_mp10_tilesZ,
	/*0x0209*/ &_file_Usetupmp11Z,
	/*0x020a*/ &_file_Ump_setupmp11Z,
	/*0x020b*/ &_file_bg_mp11_padsZ,
	/*0x020c*/ &_file_bg_mp11_tilesZ,
	/*0x020d*/ &_file_Usetupmp12Z,
	/*0x020e*/ &_file_Ump_setupmp12Z,
	/*0x020f*/ &_file_bg_mp12_padsZ,
	/*0x0210*/ &_file_bg_mp12_tilesZ,
	/*0x0211*/ &_file_Usetupmp13Z,
	/*0x0212*/ &_file_Ump_setupmp13Z,
	/*0x0213*/ &_file_bg_mp13_padsZ,
	/*0x0214*/ &_file_bg_mp13_tilesZ,
	/*0x0215*/ &_file_Usetupmp14Z,
	/*0x0216*/ &_file_Ump_setupmp14Z,
	/*0x0217*/ &_file_bg_mp14_padsZ,
	/*0x0218*/ &_file_bg_mp14_tilesZ,
	/*0x0219*/ &_file_Usetupmp15Z,
	/*0x021a*/ &_file_Ump_setupmp15Z,
	/*0x021b*/ &_file_bg_mp15_padsZ,
	/*0x021c*/ &_file_bg_mp15_tilesZ,
	/*0x021d*/ &_file_Usetupmp16Z,
	/*0x021e*/ &_file_Ump_setupmp16Z,
	/*0x021f*/ &_file_bg_mp16_padsZ,
	/*0x0220*/ &_file_bg_mp16_tilesZ,
	/*0x0221*/ &_file_Usetupmp17Z,
	/*0x0222*/ &_file_Ump_setupmp17Z,
	/*0x0223*/ &_file_bg_mp17_padsZ,
	/*0x0224*/ &_file_bg_mp17_tilesZ,
	/*0x0225*/ &_file_Usetupmp18Z,
	/*0x0226*/ &_file_Ump_setupmp18Z,
	/*0x0227*/ &_file_bg_mp18_padsZ,
	/*0x0228*/ &_file_bg_mp18_tilesZ,
	/*0x0229*/ &_file_Usetupmp19Z,
	/*0x022a*/ &_file_Ump_setupmp19Z,
	/*0x022b*/ &_file_bg_mp19_padsZ,
	/*0x022c*/ &_file_bg_mp19_tilesZ,
	/*0x022d*/ &_file_Usetupmp20Z,
	/*0x022e*/ &_file_Ump_setupmp20Z,
	/*0x022f*/ &_file_bg_mp20_padsZ,
	/*0x0230*/ &_file_bg_mp20_tilesZ,
	/*0x0231*/ &_file_Ca51airmanZ,
	/*0x0232*/ &_file_Cheadneil2Z,
	/*0x0233*/ &_file_Pci_sofaZ,
	/*0x0234*/ &_file_Pci_liftZ,
	/*0x0235*/ &_file_Pci_liftdoorZ,
	/*0x0236*/ &_file_CchicrobZ,
	/*0x0237*/ &_file_CstewardZ,
	/*0x0238*/ &_file_CheadedmcgZ,
	/*0x0239*/ &_file_CstewardessZ,
	/*0x023a*/ &_file_CheadankaZ,
	/*0x023b*/ &_file_CpresidentZ,
	/*0x023c*/ &_file_Cstewardess_coatZ,
	/*0x023d*/ &_file_Cheadleslie_sZ,
	/*0x023e*/ &_file_PlasercutZ,
	/*0x023f*/ &_file_Psk_shuttleZ,
	/*0x0240*/ &_file_CminiskedarZ,
	/*0x0241*/ &_file_PnewvilladoorZ,
	/*0x0242*/ &_file_Cnsa_lackeyZ,
	/*0x0243*/ &_file_Cheadmatt_cZ,
	/*0x0244*/ &_file_Cpres_securityZ,
	/*0x0245*/ &_file_Cheadpeer_sZ,
	/*0x0246*/ &_file_CnegotiatorZ,
	/*0x0247*/ &_file_Cheadeileen_tZ,
	/*0x0248*/ &_file_Psk_pillarleftZ,
	/*0x0249*/ &_file_Psk_pillarrightZ,
	/*0x024a*/ &_file_Psk_plinth_tZ,
	/*0x024b*/ &_file_Psk_plinth_mlZ,
	/*0x024c*/ &_file_Psk_plinth_mrZ,
	/*0x024d*/ &_file_Psk_plinth_blZ,
	/*0x024e*/ &_file_Psk_plinth_brZ,
	/*0x024f*/ &_file_Psk_fl_shad_tZ,
	/*0x0250*/ &_file_Psk_fl_shad_mlZ,
	/*0x0251*/ &_file_Psk_fl_shad_mrZ,
	/*0x0252*/ &_file_Psk_fl_shad_blZ,
	/*0x0253*/ &_file_Psk_fl_shad_brZ,
	/*0x0254*/ &_file_Psk_fl_noshad_tZ,
	/*0x0255*/ &_file_Psk_fl_noshad_mlZ,
	/*0x0256*/ &_file_Psk_fl_noshad_mrZ,
	/*0x0257*/ &_file_Psk_fl_noshad_blZ,
	/*0x0258*/ &_file_Psk_fl_noshad_brZ,
	/*0x0259*/ &_file_GhudpieceZ,
	/*0x025a*/ &_file_Psk_templecolumn1Z,
	/*0x025b*/ &_file_Psk_templecolumn2Z,
	/*0x025c*/ &_file_Psk_templecolumn3Z,
	/*0x025d*/ &_file_Psk_sunshad1Z,
	/*0x025e*/ &_file_Psk_sunshad2Z,
	/*0x025f*/ &_file_Psk_sunnoshad1Z,
	/*0x0260*/ &_file_Psk_sunnoshad2Z,
	/*0x0261*/ &_file_Cg5_guardZ,
	/*0x0262*/ &_file_Cheadandy_rZ,
	/*0x0263*/ &_file_Cpelagic_guardZ,
	/*0x0264*/ &_file_Cg5_swat_guardZ,
	/*0x0265*/ &_file_Calaskan_guardZ,
	/*0x0266*/ &_file_Cmaian_soldierZ,
	/*0x0267*/ &_file_Cheadben_rZ,
	/*0x0268*/ &_file_Cheadsteve_kZ,
	/*0x0269*/ &_file_PbarrelZ,
	/*0x026a*/ &_file_Pglass_floorZ,
	/*0x026b*/ &_file_Pesca_stepZ,
	/*0x026c*/ &_file_Pmatrix_liftZ,
	/*0x026d*/ &_file_Prubble1Z,
	/*0x026e*/ &_file_Prubble2Z,
	/*0x026f*/ &_file_Prubble3Z,
	/*0x0270*/ &_file_Prubble4Z,
	/*0x0271*/ &_file_Arecep01M,
	/*0x0272*/ &_file_Arecep02M,
	/*0x0273*/ &_file_Arecep03M,
	/*0x0274*/ &_file_Arecep04M,
	/*0x0275*/ &_file_Arecep05M,
	/*0x0276*/ &_file_Arecep06M,
	/*0x0277*/ &_file_Arlguard1M,
	/*0x0278*/ &_file_Arltech01M,
	/*0x0279*/ &_file_Arltech02M,
	/*0x027a*/ &_file_Arltech03M,
	/*0x027b*/ &_file_Arltech04M,
	/*0x027c*/ &_file_Arltech05M,
	/*0x027d*/ &_file_Arltech06M,
	/*0x027e*/ &_file_Ascie2aM,
	/*0x027f*/ &_file_Ascie2bM,
	/*0x0280*/ &_file_Ascie2cM,
	/*0x0281*/ &_file_Ascie2dM,
	/*0x0282*/ &_file_Ascie2eM,
	/*0x0283*/ &_file_Ascie2fM,
	/*0x0284*/ &_file_Ascie2gM,
	/*0x0285*/ &_file_Ascie3aM,
	/*0x0286*/ &_file_Ascie3bM,
	/*0x0287*/ &_file_Ascie3cM,
	/*0x0288*/ &_file_Ascie3dM,
	/*0x0289*/ &_file_Ascie3eM,
	/*0x028a*/ &_file_Ascie3gM,
	/*0x028b*/ &_file_Ascien10aM,
	/*0x028c*/ &_file_Ascien2_aM,
	/*0x028d*/ &_file_Ascien3_aM,
	/*0x028e*/ &_file_Ascien4_aM,
	/*0x028f*/ &_file_Ascien5_aM,
	/*0x0290*/ &_file_Ascien6_aM,
	/*0x0291*/ &_file_Ascien7_aM,
	/*0x0292*/ &_file_Ascien9_aM,
	/*0x0293*/ &_file_AvilgrimM,
	/*0x0294*/ &_file_Awepgd01M,
	/*0x0295*/ &_file_Awepgd02M,
	/*0x0296*/ &_file_Awepgd03M,
	/*0x0297*/ &_file_Awepsc01M,
	/*0x0298*/ &_file_Awepsc02M,
	/*0x0299*/ &_file_Awepsc03M,
	/*0x029a*/ &_file_Aa51elv01M,
	/*0x029b*/ &_file_Aa51elv02M,
	/*0x029c*/ &_file_Aa51elv03M,
	/*0x029d*/ &_file_Aa51grd01M,
	/*0x029e*/ &_file_Aa51grd02M,
	/*0x029f*/ &_file_Aa51grd03M,
	/*0x02a0*/ &_file_Aa51grd04M,
	/*0x02a1*/ &_file_Aa51grd05M,
	/*0x02a2*/ &_file_Aa51grd06M,
	/*0x02a3*/ &_file_Aa51grd07M,
	/*0x02a4*/ &_file_Aa51grd08M,
	/*0x02a5*/ &_file_Aa51grd09M,
	/*0x02a6*/ &_file_Aa51grd10M,
	/*0x02a7*/ &_file_Aa51jo1M,
	/*0x02a8*/ &_file_Aa51jo2M,
	/*0x02a9*/ &_file_Aa51jo3M,
	/*0x02aa*/ &_file_Aa51jo4M,
	/*0x02ab*/ &_file_Aa51jo5M,
	/*0x02ac*/ &_file_Aa51jo6M,
	/*0x02ad*/ &_file_Aa51jon01M,
	/*0x02ae*/ &_file_Aa51jon02M,
	/*0x02af*/ &_file_Aa51jon03M,
	/*0x02b0*/ &_file_Aa51jon04M,
	/*0x02b1*/ &_file_Aa51jon05M,
	/*0x02b2*/ &_file_Aa51jon06M,
	/*0x02b3*/ &_file_Aa51jon07M,
	/*0x02b4*/ &_file_Aa51jon08M,
	/*0x02b5*/ &_file_Aa51jon09M,
	/*0x02b6*/ &_file_Aa51jon10M,
	/*0x02b7*/ &_file_Aa51jon11M,
	/*0x02b8*/ &_file_Aa51jon12M,
	/*0x02b9*/ &_file_Aa51jon14M,
	/*0x02ba*/ &_file_Aa51jon15M,
	/*0x02bb*/ &_file_Aa51sci1M,
	/*0x02bc*/ &_file_Aaf1jo01M,
	/*0x02bd*/ &_file_Aaf1jo02M,
	/*0x02be*/ &_file_Aaf1jo03M,
	/*0x02bf*/ &_file_Aaf1pr01M,
	/*0x02c0*/ &_file_Aaf1pr02M,
	/*0x02c1*/ &_file_Aaf1pr03M,
	/*0x02c2*/ &_file_Aaf1pr04M,
	/*0x02c3*/ &_file_Aaf1pr05M,
	/*0x02c4*/ &_file_Aaf1pr06M,
	/*0x02c5*/ &_file_Aaf1pr07M,
	/*0x02c6*/ &_file_Aaf1pr08M,
	/*0x02c7*/ &_file_Aaf1pr09M,
	/*0x02c8*/ &_file_Aaf1pr10M,
	/*0x02c9*/ &_file_Aaf1tr01M,
	/*0x02ca*/ &_file_Aaf1tr02M,
	/*0x02cb*/ &_file_Aaf1tr03M,
	/*0x02cc*/ &_file_Aairbgd01M,
	/*0x02cd*/ &_file_Aairbgd02M,
	/*0x02ce*/ &_file_Aairbgd03M,
	/*0x02cf*/ &_file_Aairbgd04M,
	/*0x02d0*/ &_file_Aairbgd05M,
	/*0x02d1*/ &_file_Aairbgd06M,
	/*0x02d2*/ &_file_Aairbgd07M,
	/*0x02d3*/ &_file_Aairbgd08M,
	/*0x02d4*/ &_file_Aairbgd09M,
	/*0x02d5*/ &_file_Aairbgd10M,
	/*0x02d6*/ &_file_Aairbgd11M,
	/*0x02d7*/ &_file_Aairbgd12M,
	/*0x02d8*/ &_file_Aairbgd13M,
	/*0x02d9*/ &_file_Aairbgd14M,
	/*0x02da*/ &_file_Aairbgd15M,
	/*0x02db*/ &_file_Aairbgd16M,
	/*0x02dc*/ &_file_Aairstw01M,
	/*0x02dd*/ &_file_Aairstw02M,
	/*0x02de*/ &_file_Aairstw03M,
	/*0x02df*/ &_file_Aassael01M,
	/*0x02e0*/ &_file_Aassael02M,
	/*0x02e1*/ &_file_Aassael03M,
	/*0x02e2*/ &_file_Aassael04M,
	/*0x02e3*/ &_file_Aassael05M,
	/*0x02e4*/ &_file_Aassael06M,
	/*0x02e5*/ &_file_Absewrk01M,
	/*0x02e6*/ &_file_Absewrk02M,
	/*0x02e7*/ &_file_Absewrk03M,
	/*0x02e8*/ &_file_Absewrk04M,
	/*0x02e9*/ &_file_Absewrk05M,
	/*0x02ea*/ &_file_Acetael01M,
	/*0x02eb*/ &_file_Achdroid1M,
	/*0x02ec*/ &_file_Achdroid2M,
	/*0x02ed*/ &_file_Acsec01M,
	/*0x02ee*/ &_file_Acsec02M,
	/*0x02ef*/ &_file_Acsec03M,
	/*0x02f0*/ &_file_Acstan1M,
	/*0x02f1*/ &_file_Acstan2M,
	/*0x02f2*/ &_file_Adevr01M,
	/*0x02f3*/ &_file_Adevr02M,
	/*0x02f4*/ &_file_Adevr03M,
	/*0x02f5*/ &_file_Adevr04M,
	/*0x02f6*/ &_file_Adevr05M,
	/*0x02f7*/ &_file_Adevr06M,
	/*0x02f8*/ &_file_Adevr07M,
	/*0x02f9*/ &_file_Adevr08M,
	/*0x02fa*/ &_file_Adevr09M,
	/*0x02fb*/ &_file_Adevr10M,
	/*0x02fc*/ &_file_Adevr11M,
	/*0x02fd*/ &_file_Adevr12M,
	/*0x02fe*/ &_file_Aexec01M,
	/*0x02ff*/ &_file_Aexec02M,
	/*0x0300*/ &_file_Aexec04M,
	/*0x0301*/ &_file_Aexec05M,
	/*0x0302*/ &_file_Aexec06M,
	/*0x0303*/ &_file_Aexec07M,
	/*0x0304*/ &_file_Aexec08M,
	/*0x0305*/ &_file_Aexec09M,
	/*0x0306*/ &_file_Aexec10M,
	/*0x0307*/ &_file_Aexec11M,
	/*0x0308*/ &_file_Aexec12M,
	/*0x0309*/ &_file_Aexec13M,
	/*0x030a*/ &_file_Aexec14M,
	/*0x030b*/ &_file_Ahelic01M,
	/*0x030c*/ &_file_Ahelic02M,
	/*0x030d*/ &_file_Ahelic03M,
	/*0x030e*/ &_file_Ahologd01M,
	/*0x030f*/ &_file_AholohopkM,
	/*0x0310*/ &_file_Ainvcar01M,
	/*0x0311*/ &_file_Ainvcar02M,
	/*0x0312*/ &_file_Ainvcar03M,
	/*0x0313*/ &_file_Ainvcar04M,
	/*0x0314*/ &_file_Ainvcar05M,
	/*0x0315*/ &_file_Ainvcar06M,
	/*0x0316*/ &_file_Ainvcar07M,
	/*0x0317*/ &_file_Ainvcar08M,
	/*0x0318*/ &_file_Ainvcar09M,
	/*0x0319*/ &_file_Ainvcar10M,
	/*0x031a*/ &_file_Ainvcar11M,
	/*0x031b*/ &_file_Ainvcar12M,
	/*0x031c*/ &_file_AinvfarrM,
	/*0x031d*/ &_file_AinvfemaM,
	/*0x031e*/ &_file_AinvfostM,
	/*0x031f*/ &_file_AinvgrimM,
	/*0x0320*/ &_file_AinvhopkM,
	/*0x0321*/ &_file_AinvmaleM,
	/*0x0322*/ &_file_Ajoexec01M,
	/*0x0323*/ &_file_Ajoexec02M,
	/*0x0324*/ &_file_Ajosci01M,
	/*0x0325*/ &_file_Ajosci02M,
	/*0x0326*/ &_file_Ajosci03M,
	/*0x0327*/ &_file_Alabacc1M,
	/*0x0328*/ &_file_Alabacc2M,
	/*0x0329*/ &_file_Alabacc3M,
	/*0x032a*/ &_file_Alabacc4M,
	/*0x032b*/ &_file_Alabacc5M,
	/*0x032c*/ &_file_Alabacc6M,
	/*0x032d*/ &_file_Alabtech1M,
	/*0x032e*/ &_file_Alabtech2M,
	/*0x032f*/ &_file_Alabtech3M,
	/*0x0330*/ &_file_Alabtech5M,
	/*0x0331*/ &_file_Alabtech6M,
	/*0x0332*/ &_file_Alabtech7M,
	/*0x0333*/ &_file_Alabtech8M,
	/*0x0334*/ &_file_Alabtech9M,
	/*0x0335*/ &_file_Aoffwrk01M,
	/*0x0336*/ &_file_Aoffwrk02M,
	/*0x0337*/ &_file_Aoffwrk03M,
	/*0x0338*/ &_file_Aoffwrk04M,
	/*0x0339*/ &_file_Cpresident_cloneZ,
	/*0x033a*/ &_file_CheadjonathanZ,
	/*0x033b*/ &_file_Cheadmaian_sZ,
	/*0x033c*/ &_file_Cdark_af1Z,
	/*0x033d*/ &_file_Pcable_carZ,
	/*0x033e*/ &_file_Pelvis_saucerZ,
	/*0x033f*/ &_file_Pstewardess_trolleyZ,
	/*0x0340*/ &_file_Pairbase_lift_enclosedZ,
	/*0x0341*/ &_file_Pairbase_lift_angleZ,
	/*0x0342*/ &_file_Pairbase_safedoorZ,
	/*0x0343*/ &_file_Paf1_pilotchairZ,
	/*0x0344*/ &_file_Paf1_passchairZ,
	/*0x0345*/ &_file_CheadshaunZ,
	/*0x0346*/ &_file_PchrnightsightZ,
	/*0x0347*/ &_file_PchrshieldZ,
	/*0x0348*/ &_file_Pchrfalcon2Z,
	/*0x0349*/ &_file_Pchrleegun1Z,
	/*0x034a*/ &_file_PchrmaulerZ,
	/*0x034b*/ &_file_Pchrdy357Z,
	/*0x034c*/ &_file_Pchrdy357trentZ,
	/*0x034d*/ &_file_PchrmaianpistolZ,
	/*0x034e*/ &_file_Pchrfalcon2silZ,
	/*0x034f*/ &_file_Pchrfalcon2scopeZ,
	/*0x0350*/ &_file_Pchrcmp150Z,
	/*0x0351*/ &_file_Pchrar34Z,
	/*0x0352*/ &_file_PchrdragonZ,
	/*0x0353*/ &_file_PchrsuperdragonZ,
	/*0x0354*/ &_file_PchravengerZ,
	/*0x0355*/ &_file_PchrcycloneZ,
	/*0x0356*/ &_file_PchrmaiansmgZ,
	/*0x0357*/ &_file_Pchrrcp120Z,
	/*0x0358*/ &_file_PchrpcgunZ,
	/*0x0359*/ &_file_PchrshotgunZ,
	/*0x035a*/ &_file_PchrskminigunZ,
	/*0x035b*/ &_file_PchrdyrocketZ,
	/*0x035c*/ &_file_PchrdevastatorZ,
	/*0x035d*/ &_file_PchrskrocketZ,
	/*0x035e*/ &_file_Pchrz2020Z,
	/*0x035f*/ &_file_PchrsniperrifleZ,
	/*0x0360*/ &_file_PchrcrossbowZ,
	/*0x0361*/ &_file_PchrdruggunZ,
	/*0x0362*/ &_file_PchrknifeZ,
	/*0x0363*/ &_file_PchrnbombZ,
	/*0x0364*/ &_file_PchrflashbangZ,
	/*0x0365*/ &_file_PchrgrenadeZ,
	/*0x0366*/ &_file_PchrtimedmineZ,
	/*0x0367*/ &_file_PchrproximitymineZ,
	/*0x0368*/ &_file_PchrremotemineZ,
	/*0x0369*/ &_file_PchrecmmineZ,
	/*0x036a*/ &_file_PchrwppkZ,
	/*0x036b*/ &_file_Pchrtt33Z,
	/*0x036c*/ &_file_PchrskorpionZ,
	/*0x036d*/ &_file_PchrkalashZ,
	/*0x036e*/ &_file_PchruziZ,
	/*0x036f*/ &_file_Pchrmp5kZ,
	/*0x0370*/ &_file_Pchrm16Z,
	/*0x0371*/ &_file_Pchrfnp90Z,
	/*0x0372*/ &_file_PchrdyrocketmisZ,
	/*0x0373*/ &_file_PchrskrocketmisZ,
	/*0x0374*/ &_file_PchrcrossboltZ,
	/*0x0375*/ &_file_PchrdevgrenadeZ,
	/*0x0376*/ &_file_PchrdraggrenadeZ,
	/*0x0377*/ &_file_Gfalcon2Z,
	/*0x0378*/ &_file_Gleegun1Z,
	/*0x0379*/ &_file_GskpistolZ,
	/*0x037a*/ &_file_Gdy357Z,
	/*0x037b*/ &_file_Gdy357trentZ,
	/*0x037c*/ &_file_GmaianpistolZ,
	/*0x037d*/ &_file_Gcmp150Z,
	/*0x037e*/ &_file_Gar34Z,
	/*0x037f*/ &_file_GdydragonZ,
	/*0x0380*/ &_file_GdysuperdragonZ,
	/*0x0381*/ &_file_Gk7avengerZ,
	/*0x0382*/ &_file_GcycloneZ,
	/*0x0383*/ &_file_GmaiansmgZ,
	/*0x0384*/ &_file_Grcp120Z,
	/*0x0385*/ &_file_GpcgunZ,
	/*0x0386*/ &_file_GshotgunZ,
	/*0x0387*/ &_file_GskminigunZ,
	/*0x0388*/ &_file_GdyrocketZ,
	/*0x0389*/ &_file_GdydevastatorZ,
	/*0x038a*/ &_file_GskrocketZ,
	/*0x038b*/ &_file_Gz2020Z,
	/*0x038c*/ &_file_GsniperrifleZ,
	/*0x038d*/ &_file_GcrossbowZ,
	/*0x038e*/ &_file_GdruggunZ,
	/*0x038f*/ &_file_GknifeZ,
	/*0x0390*/ &_file_GgrenadeZ,
	/*0x0391*/ &_file_GtimedmineZ,
	/*0x0392*/ &_file_GproximitymineZ,
	/*0x0393*/ &_file_GremotemineZ,
	/*0x0394*/ &_file_GwppkZ,
	/*0x0395*/ &_file_Gtt33Z,
	/*0x0396*/ &_file_GskorpionZ,
	/*0x0397*/ &_file_Gak47Z,
	/*0x0398*/ &_file_GuziZ,
	/*0x0399*/ &_file_Gmp5kZ,
	/*0x039a*/ &_file_Gm16Z,
	/*0x039b*/ &_file_Gfnp90Z,
	/*0x039c*/ &_file_Gfalcon2lodZ,
	/*0x039d*/ &_file_GskminigunlodZ,
	/*0x039e*/ &_file_Pa51_turretZ,
	/*0x039f*/ &_file_PpelagicdoorZ,
	/*0x03a0*/ &_file_Am1_l1_aM,
	/*0x03a1*/ &_file_Am1_l1_bM,
	/*0x03a2*/ &_file_Am1_l1_cM,
	/*0x03a3*/ &_file_Am1_l1_dM,
	/*0x03a4*/ &_file_Am1_l2_aM,
	/*0x03a5*/ &_file_Am1_l2_bM,
	/*0x03a6*/ &_file_Am1_l2_cM,
	/*0x03a7*/ &_file_Am1_l2_dM,
	/*0x03a8*/ &_file_Am1_l3_aM,
	/*0x03a9*/ &_file_Am1_l3_bM,
	/*0x03aa*/ &_file_Am1_l3_cM,
	/*0x03ab*/ &_file_Am1_l3_dM,
	/*0x03ac*/ &_file_Am2_l1_aM,
	/*0x03ad*/ &_file_Am2_l1_bM,
	/*0x03ae*/ &_file_Am2_l1_cM,
	/*0x03af*/ &_file_Am2_l1_dM,
	/*0x03b0*/ &_file_Am3_l1_aM,
	/*0x03b1*/ &_file_Am3_l1_bM,
	/*0x03b2*/ &_file_Am3_l1_cM,
	/*0x03b3*/ &_file_Am3_l1_dM,
	/*0x03b4*/ &_file_Am3_l2_aM,
	/*0x03b5*/ &_file_Am3_l2_bM,
	/*0x03b6*/ &_file_Am3_l2_cM,
	/*0x03b7*/ &_file_Am3_l2_dM,
	/*0x03b8*/ &_file_Am4_l1_aM,
	/*0x03b9*/ &_file_Am4_l1_bM,
	/*0x03ba*/ &_file_Am4_l1_cM,
	/*0x03bb*/ &_file_Am4_l1_dM,
	/*0x03bc*/ &_file_Am4_l2_aM,
	/*0x03bd*/ &_file_Am4_l2_bM,
	/*0x03be*/ &_file_Am4_l2_cM,
	/*0x03bf*/ &_file_Am4_l2_dM,
	/*0x03c0*/ &_file_Am4_l3_aM,
	/*0x03c1*/ &_file_Am4_l3_bM,
	/*0x03c2*/ &_file_Am4_l3_cM,
	/*0x03c3*/ &_file_Am4_l3_dM,
	/*0x03c4*/ &_file_Am5_l1_aM,
	/*0x03c5*/ &_file_Am5_l1_bM,
	/*0x03c6*/ &_file_Am5_l1_cM,
	/*0x03c7*/ &_file_Am5_l1_dM,
	/*0x03c8*/ &_file_Am5_l2_aM,
	/*0x03c9*/ &_file_Am5_l2_bM,
	/*0x03ca*/ &_file_Am5_l2_cM,
	/*0x03cb*/ &_file_Am5_l2_dM,
	/*0x03cc*/ &_file_Am5_l3_aM,
	/*0x03cd*/ &_file_Am5_l3_bM,
	/*0x03ce*/ &_file_Am5_l3_cM,
	/*0x03cf*/ &_file_Am5_l3_dM,
	/*0x03d0*/ &_file_Am6_l1_aM,
	/*0x03d1*/ &_file_Am6_l1_bM,
	/*0x03d2*/ &_file_Am6_l1_cM,
	/*0x03d3*/ &_file_Am6_l1_dM,
	/*0x03d4*/ &_file_Am6_l2_aM,
	/*0x03d5*/ &_file_Am6_l2_bM,
	/*0x03d6*/ &_file_Am6_l2_cM,
	/*0x03d7*/ &_file_Am6_l2_dM,
	/*0x03d8*/ &_file_Am7_l1_aM,
	/*0x03d9*/ &_file_Am7_l1_bM,
	/*0x03da*/ &_file_Am7_l1_cM,
	/*0x03db*/ &_file_Am7_l1_dM,
	/*0x03dc*/ &_file_Am8_l1_aM,
	/*0x03dd*/ &_file_Am8_l1_bM,
	/*0x03de*/ &_file_Am8_l1_cM,
	/*0x03df*/ &_file_Am8_l1_dM,
	/*0x03e0*/ &_file_Am9_l1_aM,
	/*0x03e1*/ &_file_Am9_l1_bM,
	/*0x03e2*/ &_file_Am9_l1_cM,
	/*0x03e3*/ &_file_Am9_l1_dM,
	/*0x03e4*/ &_file_Ap1_01_joM,
	/*0x03e5*/ &_file_Ap1_02_caM,
	/*0x03e6*/ &_file_Ap1_03_joM,
	/*0x03e7*/ &_file_Ap1_04_caM,
	/*0x03e8*/ &_file_Ap1_05_joM,
	/*0x03e9*/ &_file_Ap1_06_caM,
	/*0x03ea*/ &_file_Ap1_07_joM,
	/*0x03eb*/ &_file_Ap1_08_caM,
	/*0x03ec*/ &_file_Ap2_01_joM,
	/*0x03ed*/ &_file_Ap2_02_joM,
	/*0x03ee*/ &_file_Ap2_03_drM,
	/*0x03ef*/ &_file_Ap2_04_joM,
	/*0x03f0*/ &_file_Ap2_05_joM,
	/*0x03f1*/ &_file_Ap2_06_drM,
	/*0x03f2*/ &_file_Ap2_07_drM,
	/*0x03f3*/ &_file_Ap3_01_gdM,
	/*0x03f4*/ &_file_Ap3_02_joM,
	/*0x03f5*/ &_file_Ap3_03_joM,
	/*0x03f6*/ &_file_Ap4_01_dvM,
	/*0x03f7*/ &_file_Ap4_02_joM,
	/*0x03f8*/ &_file_Ap4_03_dvM,
	/*0x03f9*/ &_file_Ap4_04_joM,
	/*0x03fa*/ &_file_Ap4_05_dvM,
	/*0x03fb*/ &_file_Ap4_06_joM,
	/*0x03fc*/ &_file_Ap4_07_blM,
	/*0x03fd*/ &_file_Ap4_08_dvM,
	/*0x03fe*/ &_file_Ap4_09_dvM,
	/*0x03ff*/ &_file_Ap5_01_joM,
	/*0x0400*/ &_file_Ap5_02_joM,
	/*0x0401*/ &_file_Ap5_03_joM,
	/*0x0402*/ &_file_Ap6_01_joM,
	/*0x0403*/ &_file_Ap6_02_caM,
	/*0x0404*/ &_file_Ap6_03_joM,
	/*0x0405*/ &_file_Ap6_04_caM,
	/*0x0406*/ &_file_Ap6_05_joM,
	/*0x0407*/ &_file_Ap6_06_caM,
	/*0x0408*/ &_file_Ap7_01_caM,
	/*0x0409*/ &_file_Ap7_02_joM,
	/*0x040a*/ &_file_Ap7_03_caM,
	/*0x040b*/ &_file_Ap7_04_joM,
	/*0x040c*/ &_file_Ap8_01_dvM,
	/*0x040d*/ &_file_Ap8_02_blM,
	/*0x040e*/ &_file_Ap8_03_dvM,
	/*0x040f*/ &_file_Ap8_04_blM,
	/*0x0410*/ &_file_Ap8_06_blM,
	/*0x0411*/ &_file_Ap8_07_trM,
	/*0x0412*/ &_file_Ap8_08_dvM,
	/*0x0413*/ &_file_Ap8_09_trM,
	/*0x0414*/ &_file_Ap8_10_blM,
	/*0x0415*/ &_file_Ap9_01_joM,
	/*0x0416*/ &_file_Ap9_02_caM,
	/*0x0417*/ &_file_Ap9_03_joM,
	/*0x0418*/ &_file_Ap10_01_caM,
	/*0x0419*/ &_file_Ap10_02_caM,
	/*0x041a*/ &_file_Ap10_03_caM,
	/*0x041b*/ &_file_Ap10_04_caM,
	/*0x041c*/ &_file_Ap10_05_joM,
	/*0x041d*/ &_file_Ap10_06_caM,
	/*0x041e*/ &_file_Ap10_07_joM,
	/*0x041f*/ &_file_Ap10_08_caM,
	/*0x0420*/ &_file_Ap10_09_joM,
	/*0x0421*/ &_file_Ap11_01_jnM,
	/*0x0422*/ &_file_Ap11_02_joM,
	/*0x0423*/ &_file_Ap11_03_jnM,
	/*0x0424*/ &_file_Ap11_04_joM,
	/*0x0425*/ &_file_Ap11_05_jnM,
	/*0x0426*/ &_file_Ap11_06_joM,
	/*0x0427*/ &_file_Ap11_07_jnM,
	/*0x0428*/ &_file_Ap11_08_joM,
	/*0x0429*/ &_file_Ap12_01_jnM,
	/*0x042a*/ &_file_Ap12_02_joM,
	/*0x042b*/ &_file_Ap12_03_jnM,
	/*0x042c*/ &_file_Ap12_04_joM,
	/*0x042d*/ &_file_Ap12_05_jnM,
	/*0x042e*/ &_file_Ap12_06_joM,
	/*0x042f*/ &_file_Ap12_07_jnM,
	/*0x0430*/ &_file_Ap12_08_joM,
	/*0x0431*/ &_file_Ap12_09_jnM,
	/*0x0432*/ &_file_Ap12_10_joM,
	/*0x0433*/ &_file_Ap13_01_joM,
	/*0x0434*/ &_file_Ap13_02_suM,
	/*0x0435*/ &_file_Ap13_03_joM,
	/*0x0436*/ &_file_Ap13_04_suM,
	/*0x0437*/ &_file_Ap13_06_suM,
	/*0x0438*/ &_file_Ap14_03_suM,
	/*0x0439*/ &_file_Ap14_04_joM,
	/*0x043a*/ &_file_Ap14_05_suM,
	/*0x043b*/ &_file_Ap14_07_joM,
	/*0x043c*/ &_file_Ap15_01_elM,
	/*0x043d*/ &_file_Ap15_02_elM,
	/*0x043e*/ &_file_Ap15_03_joM,
	/*0x043f*/ &_file_Ap15_04_jnM,
	/*0x0440*/ &_file_Ap15_05_elM,
	/*0x0441*/ &_file_Ap15_06_joM,
	/*0x0442*/ &_file_Ap15_07_elM,
	/*0x0443*/ &_file_Ap15_08_joM,
	/*0x0444*/ &_file_Ap15_09_elM,
	/*0x0445*/ &_file_Ap15_10_joM,
	/*0x0446*/ &_file_Ap15_11_elM,
	/*0x0447*/ &_file_Ap16_01_joM,
	/*0x0448*/ &_file_Ap16_02_caM,
	/*0x0449*/ &_file_Ap16_04_caM,
	/*0x044a*/ &_file_Ap16_05_joM,
	/*0x044b*/ &_file_Ap16_06_caM,
	/*0x044c*/ &_file_Ap17_01_trM,
	/*0x044d*/ &_file_Ap17_02_prM,
	/*0x044e*/ &_file_Ap17_03_trM,
	/*0x044f*/ &_file_Ap17_04_prM,
	/*0x0450*/ &_file_Ap17_05_trM,
	/*0x0451*/ &_file_Ap17_06_trM,
	/*0x0452*/ &_file_Ap18_01_joM,
	/*0x0453*/ &_file_Ap18_02_elM,
	/*0x0454*/ &_file_Ap18_03_elM,
	/*0x0455*/ &_file_Ap18_04_joM,
	/*0x0456*/ &_file_Ap18_05_elM,
	/*0x0457*/ &_file_Ap19_01_caM,
	/*0x0458*/ &_file_Ap19_02_caM,
	/*0x0459*/ &_file_Ap19_03_joM,
	/*0x045a*/ &_file_Ap19_04_caM,
	/*0x045b*/ &_file_Ap19_05_joM,
	/*0x045c*/ &_file_Ap19_06_joM,
	/*0x045d*/ &_file_Ap20_01_joM,
	/*0x045e*/ &_file_Ap20_02_prM,
	/*0x045f*/ &_file_Ap20_03_joM,
	/*0x0460*/ &_file_Ap20_04_prM,
	/*0x0461*/ &_file_Ap20_05_joM,
	/*0x0462*/ &_file_Ap20_06_blM,
	/*0x0463*/ &_file_Ap20_07_trM,
	/*0x0464*/ &_file_Ap20_08_trM,
	/*0x0465*/ &_file_Ap21_01_elM,
	/*0x0466*/ &_file_Ap21_02_joM,
	/*0x0467*/ &_file_Ap21_03_elM,
	/*0x0468*/ &_file_Ap21_04_joM,
	/*0x0469*/ &_file_Ap22_01_elM,
	/*0x046a*/ &_file_Ap22_02_joM,
	/*0x046b*/ &_file_Ap22_03_elM,
	/*0x046c*/ &_file_Ap22_04_joM,
	/*0x046d*/ &_file_Ap23_01_joM,
	/*0x046e*/ &_file_Ap23_02_drM,
	/*0x046f*/ &_file_Ap23_03_joM,
	/*0x0470*/ &_file_Ap23_04_drM,
	/*0x0471*/ &_file_Ap23_05_joM,
	/*0x0472*/ &_file_Ap23_06_drM,
	/*0x0473*/ &_file_Ap23_07_joM,
	/*0x0474*/ &_file_Ap23_08_drM,
	/*0x0475*/ &_file_Ap24_01_caM,
	/*0x0476*/ &_file_Ap24_02_joM,
	/*0x0477*/ &_file_Ap24_03_caM,
	/*0x0478*/ &_file_Ap24_04_joM,
	/*0x0479*/ &_file_Ap24_05_caM,
	/*0x047a*/ &_file_Ap24_06_caM,
	/*0x047b*/ &_file_Ap24_07_joM,
	/*0x047c*/ &_file_Ap24_08_joM,
	/*0x047d*/ &_file_Ap25_01_joM,
	/*0x047e*/ &_file_Ap25_02_joM,
	/*0x047f*/ &_file_Ap26_01_joM,
	/*0x0480*/ &_file_Ap26_02_dvM,
	/*0x0481*/ &_file_Ap26_03_joM,
	/*0x0482*/ &_file_Ap26_04_dvM,
	/*0x0483*/ &_file_Ap26_05_dvM,
	/*0x0484*/ &_file_Ap26_06_joM,
	/*0x0485*/ &_file_Ap26_07_dvM,
	/*0x0486*/ &_file_Ap26_08_dvM,
	/*0x0487*/ &_file_Ap27_01_joM,
	/*0x0488*/ &_file_Ap27_02_elM,
	/*0x0489*/ &_file_Ap27_03_elM,
	/*0x048a*/ &_file_Ap27_04_joM,
	/*0x048b*/ &_file_Ap27_05_joM,
	/*0x048c*/ &_file_Ap27_06_elM,
	/*0x048d*/ &_file_Ap28_01_elM,
	/*0x048e*/ &_file_Ap28_02_joM,
	/*0x048f*/ &_file_Ap28_03_elM,
	/*0x0490*/ &_file_Ap28_04_joM,
	/*0x0491*/ &_file_Ap28_05_elM,
	/*0x0492*/ &_file_Ap28_06_joM,
	/*0x0493*/ &_file_Ap29_01_elM,
	/*0x0494*/ &_file_Ap29_02_joM,
	/*0x0495*/ &_file_Ap29_03_elM,
	/*0x0496*/ &_file_Ap29_04_joM,
	/*0x0497*/ &_file_Ap29_05_joM,
	/*0x0498*/ &_file_Ap29_06_elM,
	/*0x0499*/ &_file_Ap29_07_joM,
	/*0x049a*/ &_file_Ap29_08_elM,
	/*0x049b*/ &_file_Ap29_09_joM,
	/*0x049c*/ &_file_Ap29_10_elM,
	/*0x049d*/ &_file_PautosurgeonZ,
	/*0x049e*/ &_file_CdarkwetZ,
	/*0x049f*/ &_file_CdarkaqualungZ,
	/*0x04a0*/ &_file_CdarksnowZ,
	/*0x04a1*/ &_file_CdarklabZ,
	/*0x04a2*/ &_file_CfemlabtechZ,
	/*0x04a3*/ &_file_CddsniperZ,
	/*0x04a4*/ &_file_Cpilotaf1Z,
	/*0x04a5*/ &_file_CcilabtechZ,
	/*0x04a6*/ &_file_CcifemtechZ,
	/*0x04a7*/ &_file_Cheadeileen_hZ,
	/*0x04a8*/ &_file_Cheadscott_hZ,
	/*0x04a9*/ &_file_CcarreveningsuitZ,
	/*0x04aa*/ &_file_CjonathonZ,
	/*0x04ab*/ &_file_CcisoldierZ,
	/*0x04ac*/ &_file_CheadsanchezZ,
	/*0x04ad*/ &_file_CheaddarkaquaZ,
	/*0x04ae*/ &_file_CheadddsniperZ,
	/*0x04af*/ &_file_PlimoZ,
	/*0x04b0*/ &_file_PpdmenuZ,
	/*0x04b1*/ &_file_Pa51interceptorZ,
	/*0x04b2*/ &_file_Pa51dishZ,
	/*0x04b3*/ &_file_Pa51radarconsoleZ,
	/*0x04b4*/ &_file_Pa51lockerdoorZ,
	/*0x04b5*/ &_file_Pg5generatorZ,
	/*0x04b6*/ &_file_Pg5dumpsterZ,
	/*0x04b7*/ &_file_Gar34lodZ,
	/*0x04b8*/ &_file_GavengerlodZ,
	/*0x04b9*/ &_file_Gcmp150lodZ,
	/*0x04ba*/ &_file_GcrossbowlodZ,
	/*0x04bb*/ &_file_GcyclonelodZ,
	/*0x04bc*/ &_file_GdruggunlodZ,
	/*0x04bd*/ &_file_Gdy357lodZ,
	/*0x04be*/ &_file_Gdy357trentlodZ,
	/*0x04bf*/ &_file_GdevastatorlodZ,
	/*0x04c0*/ &_file_GdydragonlodZ,
	/*0x04c1*/ &_file_GdysuperdragonlodZ,
	/*0x04c2*/ &_file_GknifelodZ,
	/*0x04c3*/ &_file_GlaserlodZ,
	/*0x04c4*/ &_file_GmagseclodZ,
	/*0x04c5*/ &_file_GmayanpistollodZ,
	/*0x04c6*/ &_file_GmayansmglodZ,
	/*0x04c7*/ &_file_GpcgunlodZ,
	/*0x04c8*/ &_file_Grcp120lodZ,
	/*0x04c9*/ &_file_GrocketlodZ,
	/*0x04ca*/ &_file_GshotgunlodZ,
	/*0x04cb*/ &_file_GskpistollodZ,
	/*0x04cc*/ &_file_GskrocketlodZ,
	/*0x04cd*/ &_file_GsniperlodZ,
	/*0x04ce*/ &_file_Gz2020lodZ,
	/*0x04cf*/ &_file_PchrcloakerZ,
	/*0x04d0*/ &_file_PchrspeedpillZ,
	/*0x04d1*/ &_file_PbaggagecarrierZ,
	/*0x04d2*/ &_file_PminesignZ,
	/*0x04d3*/ &_file_PchamberZ,
	/*0x04d4*/ &_file_PisotopeexperimentZ,
	/*0x04d5*/ &_file_PisotopeZ,
	/*0x04d6*/ &_file_PreactordoorZ,
	/*0x04d7*/ &_file_PsaucerinsideZ,
	/*0x04d8*/ &_file_PvillastoolZ,
	/*0x04d9*/ &_file_Pcetanwindow1Z,
	/*0x04da*/ &_file_Pcetanwindow2Z,
	/*0x04db*/ &_file_Pcetanwindow3Z,
	/*0x04dc*/ &_file_Apelelv01M,
	/*0x04dd*/ &_file_Apelgrd01M,
	/*0x04de*/ &_file_Ap29_11_joM,
	/*0x04df*/ &_file_GlaserZ,
	/*0x04e0*/ &_file_PbigpelagicdoorZ,
	/*0x04e1*/ &_file_Psk_jonrubble3Z,
	/*0x04e2*/ &_file_Psk_jonrubble4Z,
	/*0x04e3*/ &_file_Psk_jonrubble5Z,
	/*0x04e4*/ &_file_Psk_jonrubble6Z,
	/*0x04e5*/ &_file_GcombathandslodZ,
	/*0x04e6*/ &_file_PbinocularsZ,
	/*0x04e7*/ &_file_PsubmarineZ,
	/*0x04e8*/ &_file_Pairforce1Z,
	/*0x04e9*/ &_file_PenginepartZ,
	/*0x04ea*/ &_file_Am3l2carrM,
	/*0x04eb*/ &_file_Aelvcet01M,
	/*0x04ec*/ &_file_Aelvcet02M,
	/*0x04ed*/ &_file_Ajorep01M,
	/*0x04ee*/ &_file_Ajorep02M,
	/*0x04ef*/ &_file_Ajorep03M,
	/*0x04f0*/ &_file_Ajorep04M,
	/*0x04f1*/ &_file_PcetroofgunZ,
	/*0x04f2*/ &_file_PcetansmalldoorZ,
	/*0x04f3*/ &_file_PpowernodeZ,
	/*0x04f4*/ &_file_PcetanbluegreenlZ,
	/*0x04f5*/ &_file_PcetanbluegreenrZ,
	/*0x04f6*/ &_file_PskedarconsoleZ,
	/*0x04f7*/ &_file_PskedarconsolepanelZ,
	/*0x04f8*/ &_file_Ajorpld01M,
	/*0x04f9*/ &_file_Ajorpld02M,
	/*0x04fa*/ &_file_Ajorpld03M,
	/*0x04fb*/ &_file_Ajorpld04M,
	/*0x04fc*/ &_file_GnbombZ,
	/*0x04fd*/ &_file_GnbomblodZ,
	/*0x04fe*/ &_file_GgrenadelodZ,
	/*0x04ff*/ &_file_PweaponcdoorZ,
	/*0x0500*/ &_file_PtargetZ,
	/*0x0501*/ &_file_PdevicesecretdoorZ,
	/*0x0502*/ &_file_PcarringtonsecretdoorZ,
	/*0x0503*/ &_file_PsinisterpcZ,
	/*0x0504*/ &_file_PsinisterstationZ,
	/*0x0505*/ &_file_PkeypadlockZ,
	/*0x0506*/ &_file_PthumbprintscannerZ,
	/*0x0507*/ &_file_PretinalockZ,
	/*0x0508*/ &_file_PcardlockZ,
	/*0x0509*/ &_file_PgoodstationZ,
	/*0x050a*/ &_file_PgoodpcZ,
	/*0x050b*/ &_file_CskedarkingZ,
	/*0x050c*/ &_file_CelviswaistcoatZ,
	/*0x050d*/ &_file_CheadgriffeyZ,
	/*0x050e*/ &_file_CheadmotoZ,
	/*0x050f*/ &_file_CheadkeithZ,
	/*0x0510*/ &_file_CheadwinnerZ,
	/*0x0511*/ &_file_Ca51faceplateZ,
	/*0x0512*/ &_file_PchrautogunZ,
	/*0x0513*/ &_file_Pg5bigchairZ,
	/*0x0514*/ &_file_Pg5smallchairZ,
	/*0x0515*/ &_file_PkingsceptreZ,
	/*0x0516*/ &_file_PlabcoatZ,
	/*0x0517*/ &_file_Atrjo01M,
	/*0x0518*/ &_file_Atrgrim01M,
	/*0x0519*/ &_file_Atrgrim02M,
	/*0x051a*/ &_file_Atrcarr06M,
	/*0x051b*/ &_file_Atrcarr07M,
	/*0x051c*/ &_file_Atrcarr08M,
	/*0x051d*/ &_file_Atrcarr01M,
	/*0x051e*/ &_file_Atrcarr02M,
	/*0x051f*/ &_file_Atrcarr03M,
	/*0x0520*/ &_file_Atrcarr04M,
	/*0x0521*/ &_file_Atrcarr05M,
	/*0x0522*/ &_file_Atrcarr12M,
	/*0x0523*/ &_file_Abnblde01M,
	/*0x0524*/ &_file_Abncass01M,
	/*0x0525*/ &_file_Pcidoor1Z,
	/*0x0526*/ &_file_Pg5_chairZ,
	/*0x0527*/ &_file_Pg5_chair2Z,
	/*0x0528*/ &_file_Pdd_window_foyerZ,
	/*0x0529*/ &_file_Ghand_jowetsuitZ,
	/*0x052a*/ &_file_Ghand_trentZ,
	/*0x052b*/ &_file_Ghand_jofrockZ,
	/*0x052c*/ &_file_Ghand_jotrenchZ,
	/*0x052d*/ &_file_Ghand_ddsniperZ,
	/*0x052e*/ &_file_Ghand_presidentZ,
	/*0x052f*/ &_file_Ghand_joaf1Z,
	/*0x0530*/ &_file_Ghand_jopilotZ,
	/*0x0531*/ &_file_Ghand_carringtonZ,
	/*0x0532*/ &_file_Ghand_mrblondeZ,
	/*0x0533*/ &_file_Ghand_ciaZ,
	/*0x0534*/ &_file_Ghand_cifemtechZ,
	/*0x0535*/ &_file_Ghand_fbiarmZ,
	/*0x0536*/ &_file_Ghand_josnowZ,
	/*0x0537*/ &_file_Ghand_vriesZ,
	/*0x0538*/ &_file_Ghand_ddsecurityZ,
	/*0x0539*/ &_file_Ghand_tragic_pelagicZ,
	/*0x053a*/ &_file_Ghand_stewardess_coatZ,
	/*0x053b*/ &_file_Ghand_ddlabtechZ,
	/*0x053c*/ &_file_Pci_cabinetZ,
	/*0x053d*/ &_file_Pci_deskZ,
	/*0x053e*/ &_file_Pci_carr_deskZ,
	/*0x053f*/ &_file_Pci_f_chairZ,
	/*0x0540*/ &_file_Pci_loungerZ,
	/*0x0541*/ &_file_Pci_f_sofaZ,
	/*0x0542*/ &_file_Pci_tableZ,
	/*0x0543*/ &_file_Pcv_coffee_tableZ,
	/*0x0544*/ &_file_Pcv_chair1Z,
	/*0x0545*/ &_file_Pcv_chair2Z,
	/*0x0546*/ &_file_Pcv_sofaZ,
	/*0x0547*/ &_file_Pcv_chair4Z,
	/*0x0548*/ &_file_Pcv_lampZ,
	/*0x0549*/ &_file_Pcv_cabinetZ,
	/*0x054a*/ &_file_Pcv_f_bedZ,
	/*0x054b*/ &_file_Ppel_chair1Z,
	/*0x054c*/ &_file_Psk_console2Z,
	/*0x054d*/ &_file_Pdd_ear_tableZ,
	/*0x054e*/ &_file_Pdd_ear_chairZ,
	/*0x054f*/ &_file_Pairbase_table2Z,
	/*0x0550*/ &_file_Pairbase_chair2Z,
	/*0x0551*/ &_file_Pmisc_crateZ,
	/*0x0552*/ &_file_Pmisc_irspecsZ,
	/*0x0553*/ &_file_Cheadelvis_gogsZ,
	/*0x0554*/ &_file_CheadstevemZ,
	/*0x0555*/ &_file_Pa51_roofgunZ,
	/*0x0556*/ &_file_Psk_drone_gunZ,
	/*0x0557*/ &_file_Pci_roofgunZ,
	/*0x0558*/ &_file_Pcv_tableZ,
	/*0x0559*/ &_file_Cdark_leatherZ,
	/*0x055a*/ &_file_Cheaddark_snowZ,
	/*0x055b*/ &_file_CheadpresidentZ,
	/*0x055c*/ &_file_Pcidoor1_refZ,
	/*0x055d*/ &_file_Palaskadoor_outZ,
	/*0x055e*/ &_file_Palaskadoor_inZ,
	/*0x055f*/ &_file_PwirefenceZ,
	/*0x0560*/ &_file_PrarelogoZ,
	/*0x0561*/ &_file_Chead_vdZ,
	/*0x0562*/ &_file_Apelelv02M,
	/*0x0563*/ &_file_PkeycardZ,
	/*0x0564*/ &_file_PbodyarmourZ,
	/*0x0565*/ &_file_Pa51gate_rZ,
	/*0x0566*/ &_file_Pa51gate_lZ,
	/*0x0567*/ &_file_Paf1_lampZ,
	/*0x0568*/ &_file_Paf1_toiletZ,
	/*0x0569*/ &_file_Paf1_doorbig2Z,
	/*0x056a*/ &_file_Paf1_phoneZ,
	/*0x056b*/ &_file_Paf1_cargodoorZ,
	/*0x056c*/ &_file_Pg5_alarmZ,
	/*0x056d*/ &_file_Pg5_laser_switchZ,
	/*0x056e*/ &_file_Psk_templecolumn4Z,
	/*0x056f*/ &_file_PcorehatchZ,
	/*0x0570*/ &_file_LameE,
	/*0x0571*/ &_file_LameJ,
	/*0x0572*/ &_file_LameP,
	/*0x0573*/ &_file_Lame_str_gZ,
	/*0x0574*/ &_file_Lame_str_fZ,
	/*0x0575*/ &_file_Lame_str_sZ,
	/*0x0576*/ &_file_Lame_str_iZ,
	/*0x0577*/ &_file_LarchE,
	/*0x0578*/ &_file_LarchJ,
	/*0x0579*/ &_file_LarchP,
	/*0x057a*/ &_file_Larch_str_gZ,
	/*0x057b*/ &_file_Larch_str_fZ,
	/*0x057c*/ &_file_Larch_str_sZ,
	/*0x057d*/ &_file_Larch_str_iZ,
	/*0x057e*/ &_file_LarecE,
	/*0x057f*/ &_file_LarecJ,
	/*0x0580*/ &_file_LarecP,
	/*0x0581*/ &_file_Larec_str_gZ,
	/*0x0582*/ &_file_Larec_str_fZ,
	/*0x0583*/ &_file_Larec_str_sZ,
	/*0x0584*/ &_file_Larec_str_iZ,
	/*0x0585*/ &_file_LarkE,
	/*0x0586*/ &_file_LarkJ,
	/*0x0587*/ &_file_LarkP,
	/*0x0588*/ &_file_Lark_str_gZ,
	/*0x0589*/ &_file_Lark_str_fZ,
	/*0x058a*/ &_file_Lark_str_sZ,
	/*0x058b*/ &_file_Lark_str_iZ,
	/*0x058c*/ &_file_LashE,
	/*0x058d*/ &_file_LashJ,
	/*0x058e*/ &_file_LashP,
	/*0x058f*/ &_file_Lash_str_gZ,
	/*0x0590*/ &_file_Lash_str_fZ,
	/*0x0591*/ &_file_Lash_str_sZ,
	/*0x0592*/ &_file_Lash_str_iZ,
	/*0x0593*/ &_file_LateE,
	/*0x0594*/ &_file_LateJ,
	/*0x0595*/ &_file_LateP,
	/*0x0596*/ &_file_Late_str_gZ,
	/*0x0597*/ &_file_Late_str_fZ,
	/*0x0598*/ &_file_Late_str_sZ,
	/*0x0599*/ &_file_Late_str_iZ,
	/*0x059a*/ &_file_LaztE,
	/*0x059b*/ &_file_LaztJ,
	/*0x059c*/ &_file_LaztP,
	/*0x059d*/ &_file_Lazt_str_gZ,
	/*0x059e*/ &_file_Lazt_str_fZ,
	/*0x059f*/ &_file_Lazt_str_sZ,
	/*0x05a0*/ &_file_Lazt_str_iZ,
	/*0x05a1*/ &_file_LcatE,
	/*0x05a2*/ &_file_LcatJ,
	/*0x05a3*/ &_file_LcatP,
	/*0x05a4*/ &_file_Lcat_str_gZ,
	/*0x05a5*/ &_file_Lcat_str_fZ,
	/*0x05a6*/ &_file_Lcat_str_sZ,
	/*0x05a7*/ &_file_Lcat_str_iZ,
	/*0x05a8*/ &_file_LcaveE,
	/*0x05a9*/ &_file_LcaveJ,
	/*0x05aa*/ &_file_LcaveP,
	/*0x05ab*/ &_file_Lcave_str_gZ,
	/*0x05ac*/ &_file_Lcave_str_fZ,
	/*0x05ad*/ &_file_Lcave_str_sZ,
	/*0x05ae*/ &_file_Lcave_str_iZ,
	/*0x05af*/ &_file_LcradE,
	/*0x05b0*/ &_file_LcradJ,
	/*0x05b1*/ &_file_LcradP,
	/*0x05b2*/ &_file_Lcrad_str_gZ,
	/*0x05b3*/ &_file_Lcrad_str_fZ,
	/*0x05b4*/ &_file_Lcrad_str_sZ,
	/*0x05b5*/ &_file_Lcrad_str_iZ,
	/*0x05b6*/ &_file_LcrypE,
	/*0x05b7*/ &_file_LcrypJ,
	/*0x05b8*/ &_file_LcrypP,
	/*0x05b9*/ &_file_Lcryp_str_gZ,
	/*0x05ba*/ &_file_Lcryp_str_fZ,
	/*0x05bb*/ &_file_Lcryp_str_sZ,
	/*0x05bc*/ &_file_Lcryp_str_iZ,
	/*0x05bd*/ &_file_LdamE,
	/*0x05be*/ &_file_LdamJ,
	/*0x05bf*/ &_file_LdamP,
	/*0x05c0*/ &_file_Ldam_str_gZ,
	/*0x05c1*/ &_file_Ldam_str_fZ,
	/*0x05c2*/ &_file_Ldam_str_sZ,
	/*0x05c3*/ &_file_Ldam_str_iZ,
	/*0x05c4*/ &_file_LdepoE,
	/*0x05c5*/ &_file_LdepoJ,
	/*0x05c6*/ &_file_LdepoP,
	/*0x05c7*/ &_file_Ldepo_str_gZ,
	/*0x05c8*/ &_file_Ldepo_str_fZ,
	/*0x05c9*/ &_file_Ldepo_str_sZ,
	/*0x05ca*/ &_file_Ldepo_str_iZ,
	/*0x05cb*/ &_file_LdestE,
	/*0x05cc*/ &_file_LdestJ,
	/*0x05cd*/ &_file_LdestP,
	/*0x05ce*/ &_file_Ldest_str_gZ,
	/*0x05cf*/ &_file_Ldest_str_fZ,
	/*0x05d0*/ &_file_Ldest_str_sZ,
	/*0x05d1*/ &_file_Ldest_str_iZ,
	/*0x05d2*/ &_file_LdishE,
	/*0x05d3*/ &_file_LdishJ,
	/*0x05d4*/ &_file_LdishP,
	/*0x05d5*/ &_file_Ldish_str_gZ,
	/*0x05d6*/ &_file_Ldish_str_fZ,
	/*0x05d7*/ &_file_Ldish_str_sZ,
	/*0x05d8*/ &_file_Ldish_str_iZ,
	/*0x05d9*/ &_file_LearE,
	/*0x05da*/ &_file_LearJ,
	/*0x05db*/ &_file_LearP,
	/*0x05dc*/ &_file_Lear_str_gZ,
	/*0x05dd*/ &_file_Lear_str_fZ,
	/*0x05de*/ &_file_Lear_str_sZ,
	/*0x05df*/ &_file_Lear_str_iZ,
	/*0x05e0*/ &_file_LeldE,
	/*0x05e1*/ &_file_LeldJ,
	/*0x05e2*/ &_file_LeldP,
	/*0x05e3*/ &_file_Leld_str_gZ,
	/*0x05e4*/ &_file_Leld_str_fZ,
	/*0x05e5*/ &_file_Leld_str_sZ,
	/*0x05e6*/ &_file_Leld_str_iZ,
	/*0x05e7*/ &_file_LgunE,
	/*0x05e8*/ &_file_LgunJ,
	/*0x05e9*/ &_file_LgunP,
	/*0x05ea*/ &_file_Lgun_str_gZ,
	/*0x05eb*/ &_file_Lgun_str_fZ,
	/*0x05ec*/ &_file_Lgun_str_sZ,
	/*0x05ed*/ &_file_Lgun_str_iZ,
	/*0x05ee*/ &_file_LimpE,
	/*0x05ef*/ &_file_LimpJ,
	/*0x05f0*/ &_file_LimpP,
	/*0x05f1*/ &_file_Limp_str_gZ,
	/*0x05f2*/ &_file_Limp_str_fZ,
	/*0x05f3*/ &_file_Limp_str_sZ,
	/*0x05f4*/ &_file_Limp_str_iZ,
	/*0x05f5*/ &_file_LjunE,
	/*0x05f6*/ &_file_LjunJ,
	/*0x05f7*/ &_file_LjunP,
	/*0x05f8*/ &_file_Ljun_str_gZ,
	/*0x05f9*/ &_file_Ljun_str_fZ,
	/*0x05fa*/ &_file_Ljun_str_sZ,
	/*0x05fb*/ &_file_Ljun_str_iZ,
	/*0x05fc*/ &_file_LlamE,
	/*0x05fd*/ &_file_LlamJ,
	/*0x05fe*/ &_file_LlamP,
	/*0x05ff*/ &_file_Llam_str_gZ,
	/*0x0600*/ &_file_Llam_str_fZ,
	/*0x0601*/ &_file_Llam_str_sZ,
	/*0x0602*/ &_file_Llam_str_iZ,
	/*0x0603*/ &_file_LleeE,
	/*0x0604*/ &_file_LleeJ,
	/*0x0605*/ &_file_LleeP,
	/*0x0606*/ &_file_Llee_str_gZ,
	/*0x0607*/ &_file_Llee_str_fZ,
	/*0x0608*/ &_file_Llee_str_sZ,
	/*0x0609*/ &_file_Llee_str_iZ,
	/*0x060a*/ &_file_LlenE,
	/*0x060b*/ &_file_LlenJ,
	/*0x060c*/ &_file_LlenP,
	/*0x060d*/ &_file_Llen_str_gZ,
	/*0x060e*/ &_file_Llen_str_fZ,
	/*0x060f*/ &_file_Llen_str_sZ,
	/*0x0610*/ &_file_Llen_str_iZ,
	/*0x0611*/ &_file_LlipE,
	/*0x0612*/ &_file_LlipJ,
	/*0x0613*/ &_file_LlipP,
	/*0x0614*/ &_file_Llip_str_gZ,
	/*0x0615*/ &_file_Llip_str_fZ,
	/*0x0616*/ &_file_Llip_str_sZ,
	/*0x0617*/ &_file_Llip_str_iZ,
	/*0x0618*/ &_file_LlueE,
	/*0x0619*/ &_file_LlueJ,
	/*0x061a*/ &_file_LlueP,
	/*0x061b*/ &_file_Llue_str_gZ,
	/*0x061c*/ &_file_Llue_str_fZ,
	/*0x061d*/ &_file_Llue_str_sZ,
	/*0x061e*/ &_file_Llue_str_iZ,
	/*0x061f*/ &_file_LmiscE,
	/*0x0620*/ &_file_LmiscJ,
	/*0x0621*/ &_file_LmiscP,
	/*0x0622*/ &_file_Lmisc_str_gZ,
	/*0x0623*/ &_file_Lmisc_str_fZ,
	/*0x0624*/ &_file_Lmisc_str_sZ,
	/*0x0625*/ &_file_Lmisc_str_iZ,
	/*0x0626*/ &_file_Lmp10E,
	/*0x0627*/ &_file_Lmp10J,
	/*0x0628*/ &_file_Lmp10P,
	/*0x0629*/ &_file_Lmp10_str_gZ,
	/*0x062a*/ &_file_Lmp10_str_fZ,
	/*0x062b*/ &_file_Lmp10_str_sZ,
	/*0x062c*/ &_file_Lmp10_str_iZ,
	/*0x062d*/ &_file_Lmp11E,
	/*0x062e*/ &_file_Lmp11J,
	/*0x062f*/ &_file_Lmp11P,
	/*0x0630*/ &_file_Lmp11_str_gZ,
	/*0x0631*/ &_file_Lmp11_str_fZ,
	/*0x0632*/ &_file_Lmp11_str_sZ,
	/*0x0633*/ &_file_Lmp11_str_iZ,
	/*0x0634*/ &_file_Lmp12E,
	/*0x0635*/ &_file_Lmp12J,
	/*0x0636*/ &_file_Lmp12P,
	/*0x0637*/ &_file_Lmp12_str_gZ,
	/*0x0638*/ &_file_Lmp12_str_fZ,
	/*0x0639*/ &_file_Lmp12_str_sZ,
	/*0x063a*/ &_file_Lmp12_str_iZ,
	/*0x063b*/ &_file_Lmp13E,
	/*0x063c*/ &_file_Lmp13J,
	/*0x063d*/ &_file_Lmp13P,
	/*0x063e*/ &_file_Lmp13_str_gZ,
	/*0x063f*/ &_file_Lmp13_str_fZ,
	/*0x0640*/ &_file_Lmp13_str_sZ,
	/*0x0641*/ &_file_Lmp13_str_iZ,
	/*0x0642*/ &_file_Lmp14E,
	/*0x0643*/ &_file_Lmp14J,
	/*0x0644*/ &_file_Lmp14P,
	/*0x0645*/ &_file_Lmp14_str_gZ,
	/*0x0646*/ &_file_Lmp14_str_fZ,
	/*0x0647*/ &_file_Lmp14_str_sZ,
	/*0x0648*/ &_file_Lmp14_str_iZ,
	/*0x0649*/ &_file_Lmp15E,
	/*0x064a*/ &_file_Lmp15J,
	/*0x064b*/ &_file_Lmp15P,
	/*0x064c*/ &_file_Lmp15_str_gZ,
	/*0x064d*/ &_file_Lmp15_str_fZ,
	/*0x064e*/ &_file_Lmp15_str_sZ,
	/*0x064f*/ &_file_Lmp15_str_iZ,
	/*0x0650*/ &_file_Lmp16E,
	/*0x0651*/ &_file_Lmp16J,
	/*0x0652*/ &_file_Lmp16P,
	/*0x0653*/ &_file_Lmp16_str_gZ,
	/*0x0654*/ &_file_Lmp16_str_fZ,
	/*0x0655*/ &_file_Lmp16_str_sZ,
	/*0x0656*/ &_file_Lmp16_str_iZ,
	/*0x0657*/ &_file_Lmp17E,
	/*0x0658*/ &_file_Lmp17J,
	/*0x0659*/ &_file_Lmp17P,
	/*0x065a*/ &_file_Lmp17_str_gZ,
	/*0x065b*/ &_file_Lmp17_str_fZ,
	/*0x065c*/ &_file_Lmp17_str_sZ,
	/*0x065d*/ &_file_Lmp17_str_iZ,
	/*0x065e*/ &_file_Lmp18E,
	/*0x065f*/ &_file_Lmp18J,
	/*0x0660*/ &_file_Lmp18P,
	/*0x0661*/ &_file_Lmp18_str_gZ,
	/*0x0662*/ &_file_Lmp18_str_fZ,
	/*0x0663*/ &_file_Lmp18_str_sZ,
	/*0x0664*/ &_file_Lmp18_str_iZ,
	/*0x0665*/ &_file_Lmp19E,
	/*0x0666*/ &_file_Lmp19J,
	/*0x0667*/ &_file_Lmp19P,
	/*0x0668*/ &_file_Lmp19_str_gZ,
	/*0x0669*/ &_file_Lmp19_str_fZ,
	/*0x066a*/ &_file_Lmp19_str_sZ,
	/*0x066b*/ &_file_Lmp19_str_iZ,
	/*0x066c*/ &_file_Lmp1E,
	/*0x066d*/ &_file_Lmp1J,
	/*0x066e*/ &_file_Lmp1P,
	/*0x066f*/ &_file_Lmp1_str_gZ,
	/*0x0670*/ &_file_Lmp1_str_fZ,
	/*0x0671*/ &_file_Lmp1_str_sZ,
	/*0x0672*/ &_file_Lmp1_str_iZ,
	/*0x0673*/ &_file_Lmp20E,
	/*0x0674*/ &_file_Lmp20J,
	/*0x0675*/ &_file_Lmp20P,
	/*0x0676*/ &_file_Lmp20_str_gZ,
	/*0x0677*/ &_file_Lmp20_str_fZ,
	/*0x0678*/ &_file_Lmp20_str_sZ,
	/*0x0679*/ &_file_Lmp20_str_iZ,
	/*0x067a*/ &_file_Lmp2E,
	/*0x067b*/ &_file_Lmp2J,
	/*0x067c*/ &_file_Lmp2P,
	/*0x067d*/ &_file_Lmp2_str_gZ,
	/*0x067e*/ &_file_Lmp2_str_fZ,
	/*0x067f*/ &_file_Lmp2_str_sZ,
	/*0x0680*/ &_file_Lmp2_str_iZ,
	/*0x0681*/ &_file_Lmp3E,
	/*0x0682*/ &_file_Lmp3J,
	/*0x0683*/ &_file_Lmp3P,
	/*0x0684*/ &_file_Lmp3_str_gZ,
	/*0x0685*/ &_file_Lmp3_str_fZ,
	/*0x0686*/ &_file_Lmp3_str_sZ,
	/*0x0687*/ &_file_Lmp3_str_iZ,
	/*0x0688*/ &_file_Lmp4E,
	/*0x0689*/ &_file_Lmp4J,
	/*0x068a*/ &_file_Lmp4P,
	/*0x068b*/ &_file_Lmp4_str_gZ,
	/*0x068c*/ &_file_Lmp4_str_fZ,
	/*0x068d*/ &_file_Lmp4_str_sZ,
	/*0x068e*/ &_file_Lmp4_str_iZ,
	/*0x068f*/ &_file_Lmp5E,
	/*0x0690*/ &_file_Lmp5J,
	/*0x0691*/ &_file_Lmp5P,
	/*0x0692*/ &_file_Lmp5_str_gZ,
	/*0x0693*/ &_file_Lmp5_str_fZ,
	/*0x0694*/ &_file_Lmp5_str_sZ,
	/*0x0695*/ &_file_Lmp5_str_iZ,
	/*0x0696*/ &_file_Lmp6E,
	/*0x0697*/ &_file_Lmp6J,
	/*0x0698*/ &_file_Lmp6P,
	/*0x0699*/ &_file_Lmp6_str_gZ,
	/*0x069a*/ &_file_Lmp6_str_fZ,
	/*0x069b*/ &_file_Lmp6_str_sZ,
	/*0x069c*/ &_file_Lmp6_str_iZ,
	/*0x069d*/ &_file_Lmp7E,
	/*0x069e*/ &_file_Lmp7J,
	/*0x069f*/ &_file_Lmp7P,
	/*0x06a0*/ &_file_Lmp7_str_gZ,
	/*0x06a1*/ &_file_Lmp7_str_fZ,
	/*0x06a2*/ &_file_Lmp7_str_sZ,
	/*0x06a3*/ &_file_Lmp7_str_iZ,
	/*0x06a4*/ &_file_Lmp8E,
	/*0x06a5*/ &_file_Lmp8J,
	/*0x06a6*/ &_file_Lmp8P,
	/*0x06a7*/ &_file_Lmp8_str_gZ,
	/*0x06a8*/ &_file_Lmp8_str_fZ,
	/*0x06a9*/ &_file_Lmp8_str_sZ,
	/*0x06aa*/ &_file_Lmp8_str_iZ,
	/*0x06ab*/ &_file_Lmp9E,
	/*0x06ac*/ &_file_Lmp9J,
	/*0x06ad*/ &_file_Lmp9P,
	/*0x06ae*/ &_file_Lmp9_str_gZ,
	/*0x06af*/ &_file_Lmp9_str_fZ,
	/*0x06b0*/ &_file_Lmp9_str_sZ,
	/*0x06b1*/ &_file_Lmp9_str_iZ,
	/*0x06b2*/ &_file_LmpmenuE,
	/*0x06b3*/ &_file_LmpmenuJ,
	/*0x06b4*/ &_file_LmpmenuP,
	/*0x06b5*/ &_file_Lmpmenu_str_gZ,
	/*0x06b6*/ &_file_Lmpmenu_str_fZ,
	/*0x06b7*/ &_file_Lmpmenu_str_sZ,
	/*0x06b8*/ &_file_Lmpmenu_str_iZ,
	/*0x06b9*/ &_file_LmpweaponsE,
	/*0x06ba*/ &_file_LmpweaponsJ,
	/*0x06bb*/ &_file_LmpweaponsP,
	/*0x06bc*/ &_file_Lmpweapons_str_gZ,
	/*0x06bd*/ &_file_Lmpweapons_str_fZ,
	/*0x06be*/ &_file_Lmpweapons_str_sZ,
	/*0x06bf*/ &_file_Lmpweapons_str_iZ,
	/*0x06c0*/ &_file_LoatE,
	/*0x06c1*/ &_file_LoatJ,
	/*0x06c2*/ &_file_LoatP,
	/*0x06c3*/ &_file_Loat_str_gZ,
	/*0x06c4*/ &_file_Loat_str_fZ,
	/*0x06c5*/ &_file_Loat_str_sZ,
	/*0x06c6*/ &_file_Loat_str_iZ,
	/*0x06c7*/ &_file_LoldE,
	/*0x06c8*/ &_file_LoldJ,
	/*0x06c9*/ &_file_LoldP,
	/*0x06ca*/ &_file_Lold_str_gZ,
	/*0x06cb*/ &_file_Lold_str_fZ,
	/*0x06cc*/ &_file_Lold_str_sZ,
	/*0x06cd*/ &_file_Lold_str_iZ,
	/*0x06ce*/ &_file_LoptionsE,
	/*0x06cf*/ &_file_LoptionsJ,
	/*0x06d0*/ &_file_LoptionsP,
	/*0x06d1*/ &_file_Loptions_str_gZ,
	/*0x06d2*/ &_file_Loptions_str_fZ,
	/*0x06d3*/ &_file_Loptions_str_sZ,
	/*0x06d4*/ &_file_Loptions_str_iZ,
	/*0x06d5*/ &_file_LpamE,
	/*0x06d6*/ &_file_LpamJ,
	/*0x06d7*/ &_file_LpamP,
	/*0x06d8*/ &_file_Lpam_str_gZ,
	/*0x06d9*/ &_file_Lpam_str_fZ,
	/*0x06da*/ &_file_Lpam_str_sZ,
	/*0x06db*/ &_file_Lpam_str_iZ,
	/*0x06dc*/ &_file_LpeteE,
	/*0x06dd*/ &_file_LpeteJ,
	/*0x06de*/ &_file_LpeteP,
	/*0x06df*/ &_file_Lpete_str_gZ,
	/*0x06e0*/ &_file_Lpete_str_fZ,
	/*0x06e1*/ &_file_Lpete_str_sZ,
	/*0x06e2*/ &_file_Lpete_str_iZ,
	/*0x06e3*/ &_file_LpropobjE,
	/*0x06e4*/ &_file_LpropobjJ,
	/*0x06e5*/ &_file_LpropobjP,
	/*0x06e6*/ &_file_Lpropobj_str_gZ,
	/*0x06e7*/ &_file_Lpropobj_str_fZ,
	/*0x06e8*/ &_file_Lpropobj_str_sZ,
	/*0x06e9*/ &_file_Lpropobj_str_iZ,
	/*0x06ea*/ &_file_LrefE,
	/*0x06eb*/ &_file_LrefJ,
	/*0x06ec*/ &_file_LrefP,
	/*0x06ed*/ &_file_Lref_str_gZ,
	/*0x06ee*/ &_file_Lref_str_fZ,
	/*0x06ef*/ &_file_Lref_str_sZ,
	/*0x06f0*/ &_file_Lref_str_iZ,
	/*0x06f1*/ &_file_LritE,
	/*0x06f2*/ &_file_LritJ,
	/*0x06f3*/ &_file_LritP,
	/*0x06f4*/ &_file_Lrit_str_gZ,
	/*0x06f5*/ &_file_Lrit_str_fZ,
	/*0x06f6*/ &_file_Lrit_str_sZ,
	/*0x06f7*/ &_file_Lrit_str_iZ,
	/*0x06f8*/ &_file_LrunE,
	/*0x06f9*/ &_file_LrunJ,
	/*0x06fa*/ &_file_LrunP,
	/*0x06fb*/ &_file_Lrun_str_gZ,
	/*0x06fc*/ &_file_Lrun_str_fZ,
	/*0x06fd*/ &_file_Lrun_str_sZ,
	/*0x06fe*/ &_file_Lrun_str_iZ,
	/*0x06ff*/ &_file_LsevE,
	/*0x0700*/ &_file_LsevJ,
	/*0x0701*/ &_file_LsevP,
	/*0x0702*/ &_file_Lsev_str_gZ,
	/*0x0703*/ &_file_Lsev_str_fZ,
	/*0x0704*/ &_file_Lsev_str_sZ,
	/*0x0705*/ &_file_Lsev_str_iZ,
	/*0x0706*/ &_file_LsevbE,
	/*0x0707*/ &_file_LsevbJ,
	/*0x0708*/ &_file_LsevbP,
	/*0x0709*/ &_file_Lsevb_str_gZ,
	/*0x070a*/ &_file_Lsevb_str_fZ,
	/*0x070b*/ &_file_Lsevb_str_sZ,
	/*0x070c*/ &_file_Lsevb_str_iZ,
	/*0x070d*/ &_file_LsevxE,
	/*0x070e*/ &_file_LsevxJ,
	/*0x070f*/ &_file_LsevxP,
	/*0x0710*/ &_file_Lsevx_str_gZ,
	/*0x0711*/ &_file_Lsevx_str_fZ,
	/*0x0712*/ &_file_Lsevx_str_sZ,
	/*0x0713*/ &_file_Lsevx_str_iZ,
	/*0x0714*/ &_file_LsevxbE,
	/*0x0715*/ &_file_LsevxbJ,
	/*0x0716*/ &_file_LsevxbP,
	/*0x0717*/ &_file_Lsevxb_str_gZ,
	/*0x0718*/ &_file_Lsevxb_str_fZ,
	/*0x0719*/ &_file_Lsevxb_str_sZ,
	/*0x071a*/ &_file_Lsevxb_str_iZ,
	/*0x071b*/ &_file_LshoE,
	/*0x071c*/ &_file_LshoJ,
	/*0x071d*/ &_file_LshoP,
	/*0x071e*/ &_file_Lsho_str_gZ,
	/*0x071f*/ &_file_Lsho_str_fZ,
	/*0x0720*/ &_file_Lsho_str_sZ,
	/*0x0721*/ &_file_Lsho_str_iZ,
	/*0x0722*/ &_file_LsiloE,
	/*0x0723*/ &_file_LsiloJ,
	/*0x0724*/ &_file_LsiloP,
	/*0x0725*/ &_file_Lsilo_str_gZ,
	/*0x0726*/ &_file_Lsilo_str_fZ,
	/*0x0727*/ &_file_Lsilo_str_sZ,
	/*0x0728*/ &_file_Lsilo_str_iZ,
	/*0x0729*/ &_file_LstatE,
	/*0x072a*/ &_file_LstatJ,
	/*0x072b*/ &_file_LstatP,
	/*0x072c*/ &_file_Lstat_str_gZ,
	/*0x072d*/ &_file_Lstat_str_fZ,
	/*0x072e*/ &_file_Lstat_str_sZ,
	/*0x072f*/ &_file_Lstat_str_iZ,
	/*0x0730*/ &_file_LtitleE,
	/*0x0731*/ &_file_LtitleJ,
	/*0x0732*/ &_file_LtitleP,
	/*0x0733*/ &_file_Ltitle_str_gZ,
	/*0x0734*/ &_file_Ltitle_str_fZ,
	/*0x0735*/ &_file_Ltitle_str_sZ,
	/*0x0736*/ &_file_Ltitle_str_iZ,
	/*0x0737*/ &_file_LtraE,
	/*0x0738*/ &_file_LtraJ,
	/*0x0739*/ &_file_LtraP,
	/*0x073a*/ &_file_Ltra_str_gZ,
	/*0x073b*/ &_file_Ltra_str_fZ,
	/*0x073c*/ &_file_Ltra_str_sZ,
	/*0x073d*/ &_file_Ltra_str_iZ,
	/*0x073e*/ &_file_LuffE,
	/*0x073f*/ &_file_LuffJ,
	/*0x0740*/ &_file_LuffP,
	/*0x0741*/ &_file_Luff_str_gZ,
	/*0x0742*/ &_file_Luff_str_fZ,
	/*0x0743*/ &_file_Luff_str_sZ,
	/*0x0744*/ &_file_Luff_str_iZ,
	/*0x0745*/ &_file_LwaxE,
	/*0x0746*/ &_file_LwaxJ,
	/*0x0747*/ &_file_LwaxP,
	/*0x0748*/ &_file_Lwax_str_gZ,
	/*0x0749*/ &_file_Lwax_str_fZ,
	/*0x074a*/ &_file_Lwax_str_sZ,
	/*0x074b*/ &_file_Lwax_str_iZ,
	/*0x074c*/ &_file_Pa51grateZ,
	/*0x074d*/ &_file_GecmmineZ,
	/*0x074e*/ &_file_GcommsuplinkZ,
	/*0x074f*/ &_file_GirscannerZ,
	/*0x0750*/ &_file_Paf1escapedoorZ,
	/*0x0751*/ &_file_PprescapsuleZ,
	/*0x0752*/ &_file_PskedarbridgeZ,
	/*0x0753*/ &_file_Ppelagicdoor2Z,
	/*0x0754*/ &_file_Avault2M,
	/*0x0755*/ &_file_Ap29_12_elM,
	/*0x0756*/ &_file_Pttb_boxZ,
	/*0x0757*/ &_file_PinstfrontdoorZ,
	/*0x0758*/ &_file_Ap14_09_joM,
	/*0x0759*/ &_file_Ap19_07_joM,
	/*0x075a*/ &_file_Ap19_08_joM,
	/*0x075b*/ &_file_PchrlaserZ,
	/*0x075c*/ &_file_PbaftaZ,
	/*0x075d*/ &_file_PchrsonicscrewerZ,
	/*0x075e*/ &_file_PchrlumphammerZ,
	/*0x075f*/ &_file_PskedarbombZ,
	/*0x0760*/ &_file_PexplosivebrickZ,
	/*0x0761*/ &_file_PresearchtapeZ,
	/*0x0762*/ &_file_PziggycardZ,
	/*0x0763*/ &_file_PsafeitemZ,
	/*0x0764*/ &_file_Ghand_elvisZ,
	/*0x0765*/ &_file_Paf1_tableZ,
	/*0x0766*/ &_file_Ghand_a51guardZ,
	/*0x0767*/ &_file_Ghand_ddshockZ,
	/*0x0768*/ &_file_Ghand_blackguardZ,
	/*0x0769*/ &_file_Ghand_ddfodderZ,
	/*0x076a*/ &_file_Ghand_ddbioZ,
	/*0x076b*/ &_file_Ghand_a51airmanZ,
	/*0x076c*/ &_file_Ghand_g5guardZ,
	/*0x076d*/ &_file_Ghand_cisoldierZ,
	/*0x076e*/ &_file_PsensitiveinfoZ,
	/*0x076f*/ &_file_PrussdarZ,
	/*0x0770*/ &_file_PxrayspecsZ,
	/*0x0771*/ &_file_PchreyespyZ,
	/*0x0772*/ &_file_PchrdoordecoderZ,
	/*0x0773*/ &_file_PbriefcaseZ,
	/*0x0774*/ &_file_PsuitcaseZ,
	/*0x0775*/ &_file_PshuttledoorZ,
	/*0x0776*/ &_file_PruinbridgeZ,
	/*0x0777*/ &_file_PsecretindoorZ,
	/*0x0778*/ &_file_PskpuzzleobjectZ,
	/*0x0779*/ &_file_Pa51liftdoorZ,
	/*0x077a*/ &_file_Acicarr06M,
	/*0x077b*/ &_file_Acicarr11M,
	/*0x077c*/ &_file_Acifarr08M,
	/*0x077d*/ &_file_Acifarr12M,
	/*0x077e*/ &_file_Acifema01M,
	/*0x077f*/ &_file_Acifema04M,
	/*0x0780*/ &_file_Acifema07M,
	/*0x0781*/ &_file_Acifema08M,
	/*0x0782*/ &_file_Acifema09M,
	/*0x0783*/ &_file_Acifema14M,
	/*0x0784*/ &_file_Acifost08M,
	/*0x0785*/ &_file_Acifost12M,
	/*0x0786*/ &_file_Acigrim05M,
	/*0x0787*/ &_file_Acigrim06M,
	/*0x0788*/ &_file_Acigrim07M,
	/*0x0789*/ &_file_Acigrim08M,
	/*0x078a*/ &_file_Acigrim09M,
	/*0x078b*/ &_file_Acigrim10M,
	/*0x078c*/ &_file_Acihopk09M,
	/*0x078d*/ &_file_Acihopk11M,
	/*0x078e*/ &_file_Acimale02M,
	/*0x078f*/ &_file_Acimale03M,
	/*0x0790*/ &_file_Acimale07M,
	/*0x0791*/ &_file_Acimale09M,
	/*0x0792*/ &_file_Acimale11M,
	/*0x0793*/ &_file_Acimale13M,
	/*0x0794*/ &_file_Aciroge08M,
	/*0x0795*/ &_file_Aciroge12M,
	/*0x0796*/ &_file_Cdark_negotiatorZ,
	/*0x0797*/ &_file_PcihubZ,
	/*0x0798*/ &_file_Psk_ship_door2Z,
	/*0x0799*/ &_file_Psk_window1Z,
	/*0x079a*/ &_file_Psk_hangardoorb_topZ,
	/*0x079b*/ &_file_Psk_hangardoorb_botZ,
	/*0x079c*/ &_file_Paf1_innerdoorZ,
	/*0x079d*/ &_file_Plaser_postZ,
	/*0x079e*/ &_file_Atrfost01M,
	/*0x079f*/ &_file_Atrfost02M,
	/*0x07a0*/ &_file_Atrfost03M,
	/*0x07a1*/ &_file_Atrcarr09M,
	/*0x07a2*/ &_file_Atrcarr10M,
	/*0x07a3*/ &_file_Atrcarr11M,
	/*0x07a4*/ &_file_Acifarr01M,
	/*0x07a5*/ &_file_Acifarr02M,
	/*0x07a6*/ &_file_Acifarr03M,
	/*0x07a7*/ &_file_Acigrim01M,
	/*0x07a8*/ &_file_Acigrim03M,
	/*0x07a9*/ &_file_Acigrim04M,
	/*0x07aa*/ &_file_Acihopk01M,
	/*0x07ab*/ &_file_Acihopk04M,
	/*0x07ac*/ &_file_Acihopk06M,
	/*0x07ad*/ &_file_Aciroge01M,
	/*0x07ae*/ &_file_Aciroge02M,
	/*0x07af*/ &_file_Atrroge01M,
	/*0x07b0*/ &_file_Acicarr07M,
	/*0x07b1*/ &_file_Acicarr08M,
	/*0x07b2*/ &_file_PtargetampZ,
	/*0x07b3*/ &_file_Psk_liftZ,
	/*0x07b4*/ &_file_PknockknockZ,
	/*0x07b5*/ &_file_PcetandoorZ,
	/*0x07b6*/ &_file_Ajoinst01M,
	/*0x07b7*/ &_file_Ajoinst02M,
	/*0x07b8*/ &_file_Ajoinst03M,
	/*0x07b9*/ &_file_Ajoinst04M,
	/*0x07ba*/ &_file_Ap25_03_joM,
	/*0x07bb*/ &_file_Paf1rubbleZ,
	/*0x07bc*/ &_file_Pdd_dr_nonrefZ,
	/*0x07bd*/ &_file_CheadtimZ,
	/*0x07be*/ &_file_CheadgrantZ,
	/*0x07bf*/ &_file_CheadpennyZ,
	/*0x07c0*/ &_file_CheadrobinZ,
	/*0x07c1*/ &_file_CheadalexZ,
	/*0x07c2*/ &_file_CheadjulianneZ,
	/*0x07c3*/ &_file_CheadlauraZ,
	/*0x07c4*/ &_file_CheaddavecZ,
	/*0x07c5*/ &_file_CheadkenZ,
	/*0x07c6*/ &_file_CheadjoelZ,
	/*0x07c7*/ &_file_PcetandoorsideZ,
	/*0x07c8*/ &_file_Ap29_13_joM,
	/*0x07c9*/ &_file_Ap29_14_joM,
	/*0x07ca*/ &_file_Acicarr09M,
	/*0x07cb*/ &_file_Acicarr10M,
	/*0x07cc*/ &_file_PbuddybridgeZ,
	/*0x07cd*/ &_file_CheadcookZ,
	/*0x07ce*/ &_file_CheadpryceZ,
	/*0x07cf*/ &_file_CheadsilkeZ,
	/*0x07d0*/ &_file_CheadsmithZ,
	/*0x07d1*/ &_file_CheadgarethZ,
	/*0x07d2*/ &_file_CheadmurchieZ,
	/*0x07d3*/ &_file_CheadwongZ,
	/*0x07d4*/ &_file_CheadcarterZ,
	/*0x07d5*/ &_file_CheadtintinZ,
	/*0x07d6*/ &_file_CheadmuntonZ,
	/*0x07d7*/ &_file_CheadstamperZ,
	/*0x07d8*/ &_file_CheadjonesZ,
	/*0x07d9*/ &_file_CheadphelpsZ,
	/*0x07da*/ &_file_Ap29_15_joM,
	/*0x07db*/ &_file_Ap16_03_joM,
	/*0x07dc*/ &_file_Acarrbye02M,
#if VERSION >= VERSION_NTSC_1_0
	/*0x07dd*/ &_file_Asaucerexp1M,
#endif
	/*0x07de*/ &_filenamesSegmentRomStart,
};

void *fileGetRomAddress(s32 filenum)
{
	return filetable[filenum];
}

u32 fileGetRomSizeByTableAddress(u32 *filetableaddr)
{
	u32 difference;

	if (filetableaddr[1]) {
		difference = filetableaddr[1] - filetableaddr[0];
	} else {
		difference = 0;
	}

	return difference;
}

s32 fileGetRomSizeByFileNum(s32 filenum)
{
	return fileGetRomSizeByTableAddress((u32 *)&filetable[filenum]);
}

u32 func0f166ea8(u32 *filetableaddr)
{
	return 0;
}

#if VERSION >= VERSION_NTSC_1_0
void func0f166eb4(void *dst, u32 scratchlen, u32 *romaddrptr, struct fileinfo *info)
{
	u32 romsize = fileGetRomSizeByTableAddress(romaddrptr);
	u8 buffer[5 * 1024];
	u32 tmp;

	if (scratchlen == 0) {
		// DMA with no inflate
		dmaExec(dst, *romaddrptr, romsize);
	} else {
		// DMA the compressed data to scratch space then inflate
		u32 scratchaddr = ((u32)dst + scratchlen) - (romsize + 7 & 0xfffffff8);

		if (scratchaddr - (u32)dst < 8) {
			info->size = 0;
		} else {
			dmaExec((void *)scratchaddr, *romaddrptr, romsize);
			info->size = ALIGN16(rzipInflate((void *)scratchaddr, dst, buffer));
		}
	}
}
#else
GLOBAL_ASM(
glabel func0f166eb4
/*  f1616b4:	27bdeb20 */ 	addiu	$sp,$sp,-5344
/*  f1616b8:	afbf003c */ 	sw	$ra,0x3c($sp)
/*  f1616bc:	afb00038 */ 	sw	$s0,0x38($sp)
/*  f1616c0:	afa414e0 */ 	sw	$a0,0x14e0($sp)
/*  f1616c4:	00a08025 */ 	or	$s0,$a1,$zero
/*  f1616c8:	afa614e8 */ 	sw	$a2,0x14e8($sp)
/*  f1616cc:	afa714ec */ 	sw	$a3,0x14ec($sp)
/*  f1616d0:	0fc58595 */ 	jal	fileGetRomSizeByTableAddress
/*  f1616d4:	00c02025 */ 	or	$a0,$a2,$zero
/*  f1616d8:	8fa714e0 */ 	lw	$a3,0x14e0($sp)
/*  f1616dc:	8fa914e8 */ 	lw	$t1,0x14e8($sp)
/*  f1616e0:	16000006 */ 	bnez	$s0,.NB0f1616fc
/*  f1616e4:	00403025 */ 	or	$a2,$v0,$zero
/*  f1616e8:	00e02025 */ 	or	$a0,$a3,$zero
/*  f1616ec:	0c003664 */ 	jal	dmaExec
/*  f1616f0:	8d250000 */ 	lw	$a1,0x0($t1)
/*  f1616f4:	1000003b */ 	beqz	$zero,.NB0f1617e4
/*  f1616f8:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f1616fc:
/*  f1616fc:	2408fff8 */ 	addiu	$t0,$zero,-8
/*  f161700:	244e0007 */ 	addiu	$t6,$v0,0x7
/*  f161704:	01c87824 */ 	and	$t7,$t6,$t0
/*  f161708:	00f01821 */ 	addu	$v1,$a3,$s0
/*  f16170c:	006fc023 */ 	subu	$t8,$v1,$t7
/*  f161710:	0307c823 */ 	subu	$t9,$t8,$a3
/*  f161714:	2f210008 */ 	sltiu	$at,$t9,0x8
/*  f161718:	10200004 */ 	beqz	$at,.NB0f16172c
/*  f16171c:	24cb0007 */ 	addiu	$t3,$a2,0x7
/*  f161720:	8faa14ec */ 	lw	$t2,0x14ec($sp)
/*  f161724:	1000002e */ 	beqz	$zero,.NB0f1617e0
/*  f161728:	ad400000 */ 	sw	$zero,0x0($t2)
.NB0f16172c:
/*  f16172c:	01686024 */ 	and	$t4,$t3,$t0
/*  f161730:	006c8023 */ 	subu	$s0,$v1,$t4
/*  f161734:	02002025 */ 	or	$a0,$s0,$zero
/*  f161738:	0c003664 */ 	jal	dmaExec
/*  f16173c:	8d250000 */ 	lw	$a1,0x0($t1)
/*  f161740:	8fa514e0 */ 	lw	$a1,0x14e0($sp)
/*  f161744:	02002025 */ 	or	$a0,$s0,$zero
/*  f161748:	0c001da4 */ 	jal	rzipInflate
/*  f16174c:	27a600dc */ 	addiu	$a2,$sp,0xdc
/*  f161750:	1440001e */ 	bnez	$v0,.NB0f1617cc
/*  f161754:	00401825 */ 	or	$v1,$v0,$zero
/*  f161758:	920d0000 */ 	lbu	$t5,0x0($s0)
/*  f16175c:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f161760:	3c067f1b */ 	lui	$a2,0x7f1b
/*  f161764:	afad0010 */ 	sw	$t5,0x10($sp)
/*  f161768:	920e0001 */ 	lbu	$t6,0x1($s0)
/*  f16176c:	24c61d78 */ 	addiu	$a2,$a2,0x1d78
/*  f161770:	24a51d40 */ 	addiu	$a1,$a1,0x1d40
/*  f161774:	afae0014 */ 	sw	$t6,0x14($sp)
/*  f161778:	920f0002 */ 	lbu	$t7,0x2($s0)
/*  f16177c:	27a40054 */ 	addiu	$a0,$sp,0x54
/*  f161780:	240700cc */ 	addiu	$a3,$zero,0xcc
/*  f161784:	afaf0018 */ 	sw	$t7,0x18($sp)
/*  f161788:	92180003 */ 	lbu	$t8,0x3($s0)
/*  f16178c:	afb8001c */ 	sw	$t8,0x1c($sp)
/*  f161790:	92190004 */ 	lbu	$t9,0x4($s0)
/*  f161794:	afb90020 */ 	sw	$t9,0x20($sp)
/*  f161798:	920a0005 */ 	lbu	$t2,0x5($s0)
/*  f16179c:	afaa0024 */ 	sw	$t2,0x24($sp)
/*  f1617a0:	920b0006 */ 	lbu	$t3,0x6($s0)
/*  f1617a4:	afab0028 */ 	sw	$t3,0x28($sp)
/*  f1617a8:	920c0007 */ 	lbu	$t4,0x7($s0)
/*  f1617ac:	afa200d4 */ 	sw	$v0,0xd4($sp)
/*  f1617b0:	0c004fc1 */ 	jal	sprintf
/*  f1617b4:	afac002c */ 	sw	$t4,0x2c($sp)
/*  f1617b8:	0c003074 */ 	jal	func0000c1d0nb
/*  f1617bc:	27a40054 */ 	addiu	$a0,$sp,0x54
/*  f1617c0:	240d0045 */ 	addiu	$t5,$zero,0x45
/*  f1617c4:	8fa300d4 */ 	lw	$v1,0xd4($sp)
/*  f1617c8:	a00d0000 */ 	sb	$t5,0x0($zero)
.NB0f1617cc:
/*  f1617cc:	8fb814ec */ 	lw	$t8,0x14ec($sp)
/*  f1617d0:	2463000f */ 	addiu	$v1,$v1,0xf
/*  f1617d4:	346e000f */ 	ori	$t6,$v1,0xf
/*  f1617d8:	39cf000f */ 	xori	$t7,$t6,0xf
/*  f1617dc:	af0f0000 */ 	sw	$t7,0x0($t8)
.NB0f1617e0:
/*  f1617e0:	8fbf003c */ 	lw	$ra,0x3c($sp)
.NB0f1617e4:
/*  f1617e4:	8fb00038 */ 	lw	$s0,0x38($sp)
/*  f1617e8:	27bd14e0 */ 	addiu	$sp,$sp,0x14e0
/*  f1617ec:	03e00008 */ 	jr	$ra
/*  f1617f0:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

GLOBAL_ASM(
glabel func0f166f74
/*  f166f74:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*  f166f78:	afb20020 */ 	sw	$s2,0x20($sp)
/*  f166f7c:	afb1001c */ 	sw	$s1,0x1c($sp)
/*  f166f80:	afb40028 */ 	sw	$s4,0x28($sp)
/*  f166f84:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f166f88:	3c11800a */ 	lui	$s1,%hi(g_FileInfo)
/*  f166f8c:	3c128008 */ 	lui	$s2,%hi(filetable)
/*  f166f90:	afbf002c */ 	sw	$ra,0x2c($sp)
/*  f166f94:	afb30024 */ 	sw	$s3,0x24($sp)
/*  f166f98:	26522060 */ 	addiu	$s2,$s2,%lo(filetable)
/*  f166f9c:	26316680 */ 	addiu	$s1,$s1,%lo(g_FileInfo)
/*  f166fa0:	24100001 */ 	addiu	$s0,$zero,0x1
/*  f166fa4:	241407de */ 	addiu	$s4,$zero,0x7de
/*  f166fa8:	001070c0 */ 	sll	$t6,$s0,0x3
.L0f166fac:
/*  f166fac:	022e1021 */ 	addu	$v0,$s1,$t6
/*  f166fb0:	00107880 */ 	sll	$t7,$s0,0x2
/*  f166fb4:	ac400000 */ 	sw	$zero,0x0($v0)
/*  f166fb8:	ac400004 */ 	sw	$zero,0x4($v0)
/*  f166fbc:	0fc59b95 */ 	jal	fileGetRomSizeByTableAddress
/*  f166fc0:	024f2021 */ 	addu	$a0,$s2,$t7
/*  f166fc4:	26100001 */ 	addiu	$s0,$s0,0x1
/*  f166fc8:	5614fff8 */ 	bnel	$s0,$s4,.L0f166fac
/*  f166fcc:	001070c0 */ 	sll	$t6,$s0,0x3
/*  f166fd0:	8fbf002c */ 	lw	$ra,0x2c($sp)
/*  f166fd4:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f166fd8:	8fb1001c */ 	lw	$s1,0x1c($sp)
/*  f166fdc:	8fb20020 */ 	lw	$s2,0x20($sp)
/*  f166fe0:	8fb30024 */ 	lw	$s3,0x24($sp)
/*  f166fe4:	8fb40028 */ 	lw	$s4,0x28($sp)
/*  f166fe8:	03e00008 */ 	jr	$ra
/*  f166fec:	27bd0030 */ 	addiu	$sp,$sp,0x30
);

//void func0f166f74(void)
//{
//	s32 i;
//
//	for (i = 1; i < NUM_FILES; i++) {
//		g_FileInfo[i].size = 0;
//		g_FileInfo[i].unk04 = 0;
//
//		fileGetRomSizeByTableAddress(&filetable[i]);
//	}
//}

void func0f166ff0(u16 filenum, void *memaddr, s32 offset, u32 len)
{
	u32 stack[2];

	if (fileGetRomSizeByTableAddress((u32 *)&filetable[filenum])) {
		dmaExec(memaddr, (u32)filetable[filenum] + offset, len);
	}
}

#if VERSION >= VERSION_NTSC_1_0
GLOBAL_ASM(
glabel fileGetInflatedLength
/*  f167054:	27bdff78 */ 	addiu	$sp,$sp,-136
/*  f167058:	3c0f8008 */ 	lui	$t7,%hi(filetable)
/*  f16705c:	25ef2060 */ 	addiu	$t7,$t7,%lo(filetable)
/*  f167060:	00047080 */ 	sll	$t6,$a0,0x2
/*  f167064:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f167068:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f16706c:	01cf2021 */ 	addu	$a0,$t6,$t7
/*  f167070:	8c850000 */ 	lw	$a1,0x0($a0)
/*  f167074:	27b00044 */ 	addiu	$s0,$sp,0x44
/*  f167078:	2401fff0 */ 	addiu	$at,$zero,-16
/*  f16707c:	14a0000c */ 	bnez	$a1,.L0f1670b0
/*  f167080:	24060040 */ 	addiu	$a2,$zero,0x40
/*  f167084:	0fc59baa */ 	jal	func0f166ea8
/*  f167088:	00000000 */ 	nop
/*  f16708c:	27b00044 */ 	addiu	$s0,$sp,0x44
/*  f167090:	2401fff0 */ 	addiu	$at,$zero,-16
/*  f167094:	02012824 */ 	and	$a1,$s0,$at
/*  f167098:	00a08025 */ 	or	$s0,$a1,$zero
/*  f16709c:	00402025 */ 	or	$a0,$v0,$zero
/*  f1670a0:	0fc5d7d6 */ 	jal	stub0f175f58
/*  f1670a4:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f1670a8:	10000004 */ 	b	.L0f1670bc
/*  f1670ac:	00000000 */ 	nop
.L0f1670b0:
/*  f1670b0:	02012024 */ 	and	$a0,$s0,$at
/*  f1670b4:	0c003504 */ 	jal	dmaExec
/*  f1670b8:	00808025 */ 	or	$s0,$a0,$zero
.L0f1670bc:
/*  f1670bc:	0c002277 */ 	jal	rzipIs1173
/*  f1670c0:	02002025 */ 	or	$a0,$s0,$zero
/*  f1670c4:	10400009 */ 	beqz	$v0,.L0f1670ec
/*  f1670c8:	8fbf001c */ 	lw	$ra,0x1c($sp)
/*  f1670cc:	92090002 */ 	lbu	$t1,0x2($s0)
/*  f1670d0:	92080004 */ 	lbu	$t0,0x4($s0)
/*  f1670d4:	920c0003 */ 	lbu	$t4,0x3($s0)
/*  f1670d8:	00095400 */ 	sll	$t2,$t1,0x10
/*  f1670dc:	010a5825 */ 	or	$t3,$t0,$t2
/*  f1670e0:	000c6a00 */ 	sll	$t5,$t4,0x8
/*  f1670e4:	10000002 */ 	b	.L0f1670f0
/*  f1670e8:	016d1025 */ 	or	$v0,$t3,$t5
.L0f1670ec:
/*  f1670ec:	00001025 */ 	or	$v0,$zero,$zero
.L0f1670f0:
/*  f1670f0:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1670f4:	03e00008 */ 	jr	$ra
/*  f1670f8:	27bd0088 */ 	addiu	$sp,$sp,0x88
);
#else
GLOBAL_ASM(
glabel fileGetInflatedLength
/*  f1618d4:	27bdfeb8 */ 	addiu	$sp,$sp,-328
/*  f1618d8:	3c0f8008 */ 	lui	$t7,0x8008
/*  f1618dc:	25ef48c0 */ 	addiu	$t7,$t7,0x48c0
/*  f1618e0:	00047080 */ 	sll	$t6,$a0,0x2
/*  f1618e4:	afbf005c */ 	sw	$ra,0x5c($sp)
/*  f1618e8:	afb00058 */ 	sw	$s0,0x58($sp)
/*  f1618ec:	01cf2021 */ 	addu	$a0,$t6,$t7
/*  f1618f0:	8c850000 */ 	lw	$a1,0x0($a0)
/*  f1618f4:	27b00104 */ 	addiu	$s0,$sp,0x104
/*  f1618f8:	2401fff0 */ 	addiu	$at,$zero,-16
/*  f1618fc:	14a0000c */ 	bnez	$a1,.NB0f161930
/*  f161900:	24060040 */ 	addiu	$a2,$zero,0x40
/*  f161904:	0fc585aa */ 	jal	func0f166ea8
/*  f161908:	00000000 */ 	sll	$zero,$zero,0x0
/*  f16190c:	27b00104 */ 	addiu	$s0,$sp,0x104
/*  f161910:	2401fff0 */ 	addiu	$at,$zero,-16
/*  f161914:	02012824 */ 	and	$a1,$s0,$at
/*  f161918:	00a08025 */ 	or	$s0,$a1,$zero
/*  f16191c:	00402025 */ 	or	$a0,$v0,$zero
/*  f161920:	0fc5c2fe */ 	jal	stub0f175f58
/*  f161924:	24060010 */ 	addiu	$a2,$zero,0x10
/*  f161928:	10000004 */ 	beqz	$zero,.NB0f16193c
/*  f16192c:	00000000 */ 	sll	$zero,$zero,0x0
.NB0f161930:
/*  f161930:	02012024 */ 	and	$a0,$s0,$at
/*  f161934:	0c003664 */ 	jal	dmaExec
/*  f161938:	00808025 */ 	or	$s0,$a0,$zero
.NB0f16193c:
/*  f16193c:	0c0022df */ 	jal	rzipIs1173
/*  f161940:	02002025 */ 	or	$a0,$s0,$zero
/*  f161944:	5040000a */ 	beqzl	$v0,.NB0f161970
/*  f161948:	920e0000 */ 	lbu	$t6,0x0($s0)
/*  f16194c:	92090002 */ 	lbu	$t1,0x2($s0)
/*  f161950:	92080004 */ 	lbu	$t0,0x4($s0)
/*  f161954:	920c0003 */ 	lbu	$t4,0x3($s0)
/*  f161958:	00095400 */ 	sll	$t2,$t1,0x10
/*  f16195c:	010a5825 */ 	or	$t3,$t0,$t2
/*  f161960:	000c6a00 */ 	sll	$t5,$t4,0x8
/*  f161964:	1000002d */ 	beqz	$zero,.NB0f161a1c
/*  f161968:	016d1025 */ 	or	$v0,$t3,$t5
/*  f16196c:	920e0000 */ 	lbu	$t6,0x0($s0)
.NB0f161970:
/*  f161970:	3c057f1b */ 	lui	$a1,0x7f1b
/*  f161974:	3c067f1b */ 	lui	$a2,0x7f1b
/*  f161978:	afae0010 */ 	sw	$t6,0x10($sp)
/*  f16197c:	920f0001 */ 	lbu	$t7,0x1($s0)
/*  f161980:	24c61dd8 */ 	addiu	$a2,$a2,0x1dd8
/*  f161984:	24a51d80 */ 	addiu	$a1,$a1,0x1d80
/*  f161988:	afaf0014 */ 	sw	$t7,0x14($sp)
/*  f16198c:	92180002 */ 	lbu	$t8,0x2($s0)
/*  f161990:	27a40070 */ 	addiu	$a0,$sp,0x70
/*  f161994:	240701be */ 	addiu	$a3,$zero,0x1be
/*  f161998:	afb80018 */ 	sw	$t8,0x18($sp)
/*  f16199c:	92190003 */ 	lbu	$t9,0x3($s0)
/*  f1619a0:	afb9001c */ 	sw	$t9,0x1c($sp)
/*  f1619a4:	92090004 */ 	lbu	$t1,0x4($s0)
/*  f1619a8:	afa90020 */ 	sw	$t1,0x20($sp)
/*  f1619ac:	92080005 */ 	lbu	$t0,0x5($s0)
/*  f1619b0:	afa80024 */ 	sw	$t0,0x24($sp)
/*  f1619b4:	920a0006 */ 	lbu	$t2,0x6($s0)
/*  f1619b8:	afaa0028 */ 	sw	$t2,0x28($sp)
/*  f1619bc:	920c0007 */ 	lbu	$t4,0x7($s0)
/*  f1619c0:	afac002c */ 	sw	$t4,0x2c($sp)
/*  f1619c4:	920b0008 */ 	lbu	$t3,0x8($s0)
/*  f1619c8:	afab0030 */ 	sw	$t3,0x30($sp)
/*  f1619cc:	920d0009 */ 	lbu	$t5,0x9($s0)
/*  f1619d0:	afad0034 */ 	sw	$t5,0x34($sp)
/*  f1619d4:	920e000a */ 	lbu	$t6,0xa($s0)
/*  f1619d8:	afae0038 */ 	sw	$t6,0x38($sp)
/*  f1619dc:	920f000b */ 	lbu	$t7,0xb($s0)
/*  f1619e0:	afaf003c */ 	sw	$t7,0x3c($sp)
/*  f1619e4:	9218000c */ 	lbu	$t8,0xc($s0)
/*  f1619e8:	afb80040 */ 	sw	$t8,0x40($sp)
/*  f1619ec:	9219000d */ 	lbu	$t9,0xd($s0)
/*  f1619f0:	afb90044 */ 	sw	$t9,0x44($sp)
/*  f1619f4:	9209000e */ 	lbu	$t1,0xe($s0)
/*  f1619f8:	afa90048 */ 	sw	$t1,0x48($sp)
/*  f1619fc:	9208000f */ 	lbu	$t0,0xf($s0)
/*  f161a00:	0c004fc1 */ 	jal	sprintf
/*  f161a04:	afa8004c */ 	sw	$t0,0x4c($sp)
/*  f161a08:	0c003074 */ 	jal	func0000c1d0nb
/*  f161a0c:	27a40070 */ 	addiu	$a0,$sp,0x70
/*  f161a10:	240a0045 */ 	addiu	$t2,$zero,0x45
/*  f161a14:	a00a0000 */ 	sb	$t2,0x0($zero)
/*  f161a18:	00001025 */ 	or	$v0,$zero,$zero
.NB0f161a1c:
/*  f161a1c:	8fbf005c */ 	lw	$ra,0x5c($sp)
/*  f161a20:	8fb00058 */ 	lw	$s0,0x58($sp)
/*  f161a24:	27bd0148 */ 	addiu	$sp,$sp,0x148
/*  f161a28:	03e00008 */ 	jr	$ra
/*  f161a2c:	00000000 */ 	sll	$zero,$zero,0x0
);
#endif

//u32 fileGetInflatedLength(u32 filenum)
//{
//	u8 buffer[0x50];
//	u8 *alignedbuffer;
//	void *romaddr;
//	u32 tmp;
//
//	romaddr = filetable[filenum];
//	alignedbuffer = buffer;
//
//	if (romaddr == NULL) {
//		alignedbuffer = (u8 *)(((u32)alignedbuffer) & ~0xf);
//
//		stub0f175f58(func0f166ea8((u32 *) &filetable[filenum]), (u32)alignedbuffer, 16);
//	} else {
//		alignedbuffer = (u8 *)(((u32)alignedbuffer) & ~0xf);
//		dmaExec((void *)alignedbuffer, romaddr, 0x40);
//	}
//
//	if (rzipIs1173((void *)alignedbuffer)) {
//		return (alignedbuffer[2] << 16) | (alignedbuffer[3] << 8) | alignedbuffer[4];
//	}
//
//	return 0;
//}

GLOBAL_ASM(
glabel func0f1670fc
/*  f1670fc:	27bdffd0 */ 	addiu	$sp,$sp,-48
/*  f167100:	24010011 */ 	addiu	$at,$zero,0x11
/*  f167104:	afbf001c */ 	sw	$ra,0x1c($sp)
/*  f167108:	afb00018 */ 	sw	$s0,0x18($sp)
/*  f16710c:	afa40030 */ 	sw	$a0,0x30($sp)
/*  f167110:	10a10004 */ 	beq	$a1,$at,.L0f167124
/*  f167114:	afa50034 */ 	sw	$a1,0x34($sp)
/*  f167118:	24010022 */ 	addiu	$at,$zero,0x22
/*  f16711c:	14a1002c */ 	bne	$a1,$at,.L0f1671d0
/*  f167120:	00000000 */ 	nop
.L0f167124:
/*  f167124:	8faf0030 */ 	lw	$t7,0x30($sp)
/*  f167128:	3c19800a */ 	lui	$t9,%hi(g_FileInfo)
/*  f16712c:	27396680 */ 	addiu	$t9,$t9,%lo(g_FileInfo)
/*  f167130:	000fc0c0 */ 	sll	$t8,$t7,0x3
/*  f167134:	03198021 */ 	addu	$s0,$t8,$t9
/*  f167138:	8e080000 */ 	lw	$t0,0x0($s0)
/*  f16713c:	5500000e */ 	bnezl	$t0,.L0f167178
/*  f167140:	8e040000 */ 	lw	$a0,0x0($s0)
/*  f167144:	0fc59c15 */ 	jal	fileGetInflatedLength
/*  f167148:	01e02025 */ 	or	$a0,$t7,$zero
/*  f16714c:	24490020 */ 	addiu	$t1,$v0,0x20
/*  f167150:	2401fff0 */ 	addiu	$at,$zero,-16
/*  f167154:	01215024 */ 	and	$t2,$t1,$at
/*  f167158:	ae0a0000 */ 	sw	$t2,0x0($s0)
/*  f16715c:	8fab0034 */ 	lw	$t3,0x34($sp)
/*  f167160:	24010011 */ 	addiu	$at,$zero,0x11
/*  f167164:	15610003 */ 	bne	$t3,$at,.L0f167174
/*  f167168:	34018000 */ 	dli	$at,0x8000
/*  f16716c:	01416821 */ 	addu	$t5,$t2,$at
/*  f167170:	ae0d0000 */ 	sw	$t5,0x0($s0)
.L0f167174:
/*  f167174:	8e040000 */ 	lw	$a0,0x0($s0)
.L0f167178:
/*  f167178:	0c0048f2 */ 	jal	malloc
/*  f16717c:	24050004 */ 	addiu	$a1,$zero,0x4
/*  f167180:	afa20024 */ 	sw	$v0,0x24($sp)
/*  f167184:	8e050000 */ 	lw	$a1,0x0($s0)
/*  f167188:	3c198008 */ 	lui	$t9,%hi(filetable)
/*  f16718c:	27392060 */ 	addiu	$t9,$t9,%lo(filetable)
/*  f167190:	ae050004 */ 	sw	$a1,0x4($s0)
/*  f167194:	8fae0030 */ 	lw	$t6,0x30($sp)
/*  f167198:	00402025 */ 	or	$a0,$v0,$zero
/*  f16719c:	02003825 */ 	or	$a3,$s0,$zero
/*  f1671a0:	000ec080 */ 	sll	$t8,$t6,0x2
/*  f1671a4:	0fc59bad */ 	jal	func0f166eb4
/*  f1671a8:	03193021 */ 	addu	$a2,$t8,$t9
/*  f1671ac:	8fa80034 */ 	lw	$t0,0x34($sp)
/*  f1671b0:	24010011 */ 	addiu	$at,$zero,0x11
/*  f1671b4:	8fa40024 */ 	lw	$a0,0x24($sp)
/*  f1671b8:	11010007 */ 	beq	$t0,$at,.L0f1671d8
/*  f1671bc:	24060004 */ 	addiu	$a2,$zero,0x4
/*  f1671c0:	0c00490c */ 	jal	memReallocate
/*  f1671c4:	8e050000 */ 	lw	$a1,0x0($s0)
/*  f1671c8:	10000004 */ 	b	.L0f1671dc
/*  f1671cc:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f1671d0:
/*  f1671d0:	1000ffff */ 	b	.L0f1671d0
/*  f1671d4:	00000000 */ 	nop
.L0f1671d8:
/*  f1671d8:	8fbf001c */ 	lw	$ra,0x1c($sp)
.L0f1671dc:
/*  f1671dc:	8fa20024 */ 	lw	$v0,0x24($sp)
/*  f1671e0:	8fb00018 */ 	lw	$s0,0x18($sp)
/*  f1671e4:	03e00008 */ 	jr	$ra
/*  f1671e8:	27bd0030 */ 	addiu	$sp,$sp,0x30
/*  f1671ec:	00047080 */ 	sll	$t6,$a0,0x2
/*  f1671f0:	3c018008 */ 	lui	$at,%hi(filetable)
/*  f1671f4:	002e0821 */ 	addu	$at,$at,$t6
/*  f1671f8:	03e00008 */ 	jr	$ra
/*  f1671fc:	ac202060 */ 	sw	$zero,%lo(filetable)($at)
);

//void *func0f1670fc(u32 filenum, u32 arg1)
//{
//	struct fileinfo *info;
//	u32 stack;
//	void *ptr;
//
//	if (arg1 == 0x11 || arg1 == 0x22) {
//		// 124
//		info = &g_FileInfo[filenum];
//
//		// 13c
//		if (info->unk00 == 0) {
//			info->unk00 = (fileGetInflatedLength(filenum) + 0x20) & 0xfffffff0;
//
//			// 164
//			if (arg1 == 0x11) {
//				info->unk00 += 0x8000;
//			}
//		}
//
//		// 174
//		ptr = malloc(info->unk00, MEMPOOL_STAGE);
//		info->unk04 = info->unk00;
//		func0f166eb4(ptr, info->unk00, &filetable[filenum], info);
//
//		if (arg1 != 0x11) {
//			memReallocate(ptr, info->unk00, MEMPOOL_STAGE);
//		}
//	} else {
//		while (true) {
//			// empty
//		}
//	}
//
//	return ptr;
//}

GLOBAL_ASM(
glabel func0f167200
/*  f167200:	27bdffe8 */ 	addiu	$sp,$sp,-24
/*  f167204:	24010011 */ 	addiu	$at,$zero,0x11
/*  f167208:	afbf0014 */ 	sw	$ra,0x14($sp)
/*  f16720c:	afa40018 */ 	sw	$a0,0x18($sp)
/*  f167210:	afa60020 */ 	sw	$a2,0x20($sp)
/*  f167214:	10a10004 */ 	beq	$a1,$at,.L0f167228
/*  f167218:	afa70024 */ 	sw	$a3,0x24($sp)
/*  f16721c:	24010022 */ 	addiu	$at,$zero,0x22
/*  f167220:	14a10012 */ 	bne	$a1,$at,.L0f16726c
/*  f167224:	00000000 */ 	nop
.L0f167228:
/*  f167228:	8fae0018 */ 	lw	$t6,0x18($sp)
/*  f16722c:	8fb90024 */ 	lw	$t9,0x24($sp)
/*  f167230:	3c18800a */ 	lui	$t8,%hi(g_FileInfo)
/*  f167234:	27186680 */ 	addiu	$t8,$t8,%lo(g_FileInfo)
/*  f167238:	000e78c0 */ 	sll	$t7,$t6,0x3
/*  f16723c:	01f83821 */ 	addu	$a3,$t7,$t8
/*  f167240:	acf90004 */ 	sw	$t9,0x4($a3)
/*  f167244:	8fa80018 */ 	lw	$t0,0x18($sp)
/*  f167248:	3c0a8008 */ 	lui	$t2,%hi(filetable)
/*  f16724c:	254a2060 */ 	addiu	$t2,$t2,%lo(filetable)
/*  f167250:	00084880 */ 	sll	$t1,$t0,0x2
/*  f167254:	012a3021 */ 	addu	$a2,$t1,$t2
/*  f167258:	8fa50024 */ 	lw	$a1,0x24($sp)
/*  f16725c:	0fc59bad */ 	jal	func0f166eb4
/*  f167260:	8fa40020 */ 	lw	$a0,0x20($sp)
/*  f167264:	10000003 */ 	b	.L0f167274
/*  f167268:	8fbf0014 */ 	lw	$ra,0x14($sp)
.L0f16726c:
/*  f16726c:	1000ffff */ 	b	.L0f16726c
/*  f167270:	00000000 */ 	nop
.L0f167274:
/*  f167274:	8fa20020 */ 	lw	$v0,0x20($sp)
/*  f167278:	03e00008 */ 	jr	$ra
/*  f16727c:	27bd0018 */ 	addiu	$sp,$sp,0x18
);

// Mismatch: Reordered instructions, most likely related to debug ifdefs.
//void *func0f167200(s32 filenum, s32 arg1, u8 *ptr, u32 size)
//{
//	if (arg1 == 0x11 || arg1 == 0x22) {
//		g_FileInfo[filenum].unk04 = size;
//
//		func0f166eb4(ptr, size, &filetable[filenum], &g_FileInfo[filenum]);
//	} else {
//		while (1);
//	}
//
//	return ptr;
//}

u32 fileGetSize(s32 filenum)
{
	return g_FileInfo[filenum].size;
}

u32 fileGetUnk04(s32 filenum)
{
	return g_FileInfo[filenum].unk04;
}

void func0f1672a8(s32 filenum, void *ptr, u32 size, bool resizing)
{
	g_FileInfo[filenum].size = size;
	g_FileInfo[filenum].unk04 = size;

	if (resizing) {
		memReallocate((u32) ptr, g_FileInfo[filenum].size, MEMPOOL_STAGE);
	}
}

void func0f1672f0(u8 arg0)
{
	s32 i;

	for (i = 1; i < 2014; i++) {
		if (arg0 == 4) {
			g_FileInfo[i].size = 0;
		}
	}
}

void func0f167330(void)
{
	func0f1672f0(5);
}
