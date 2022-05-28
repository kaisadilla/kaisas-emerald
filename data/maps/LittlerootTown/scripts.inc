.set LOCALID_FOOTPRINTS_MAN, 1
.set LOCALID_MOM, 4
.set LOCALID_RIVAL, 7
.set LOCALID_BIRCH, 8

LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_BIRCH, Littleroot_Evt_SetFootprintsManPos
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	end

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, Littleroot_Evt_StepOffTruck_Male
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, Littleroot_Evt_StepOffTruck_Female
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	.2byte 0
	
@ ===================================================== @
@ =====================  OnEvents ===================== @
@ ===================================================== @
@ the position of the footprints' man when he allows you to pass to save Birch.
Littleroot_Evt_SetFootprintsManPos::
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, Littleroot_Evt_SetFootprintsManBlockingPos
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 11, 0
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_FACE_UP
	return

@ the position of the footprints' man when he doesn't allow you to pass.
Littleroot_Evt_SetFootprintsManBlockingPos::
	setobjectxyperm LOCALID_FOOTPRINTS_MAN, 12, 2
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_LOOK_AROUND
	return

@ ==================================================== @
@ ================= NPC Interactions ================= @
@ ==================================================== @

Littleroot_EvtNPC_FootprintsMan::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, Littleroot_Evt_GoSaveBirch
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_FatMan::
	msgbox Littleroot_Tx_ILostMyPotion, MSGBOX_NPC
	end

Littleroot_Tx_ILostMyPotion:
	.string "I think I lost my potion\n"
	.string "somewhere around here.\p"
	.string "I've been searching for a while\n"
	.string "but I haven't found it.\l"
	.string "Maybe I left it in my PC?$"

Littleroot_EvtNPC_Boy::
	msgbox Littleroot_Tx_BirchSpendsDaysInLab, MSGBOX_NPC
	end

Littleroot_Tx_BirchSpendsDaysInLab:
	.string "Prof. Birch spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does Prof. Birch spend time\n"
	.string "at home?$"

Littleroot_EvtNPC_Elder::
	msgbox Littleroot_Tx_CanUsePCToStoreItems, MSGBOX_NPC
	end

Littleroot_Tx_CanUsePCToStoreItems:
	.string "If you use a PC, you can store items\n"
	.string "and even Pokémon.\p"
	.string "I'd never imagine something like that\n"
	.string "in my younger days!$"

Littleroot_EvtNPC_Twin::
	msgbox Littleroot_Tx_ILikeThisVillage, MSGBOX_NPC
	end

Littleroot_Tx_ILikeThisVillage:
	.string "I like this village.\n"
	.string "It's a very calm place, nothing ever\l"
	.string "happens here.\p"
	.string "But, without Pokémon, I cannot travel\n"
	.string "to nearby towns.$"

@ ==================================================== @
@ ================== Trigger events ================== @
@ ==================================================== @

@ @@ Jump off the truck and welcome by Mom.
Littleroot_Evt_StepOffTruck_Male::
	lockall
	setvar VAR_0x8004, 12 @ brendan's house door x?
	setvar VAR_0x8005, 20 @ brendan's house door y?
	call Littleroot_Evt_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

Littleroot_Evt_StepOffTruck_Female::
	lockall
	setvar VAR_0x8004, 25 @ may's house door x?
	setvar VAR_0x8005, 21 @ may's house door y?
	call Littleroot_Evt_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

Littleroot_Evt_GoInsideWithMom::
	delay 15

	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, Littleroot_Move_Player_StepOffTruck
	waitmovement 0

	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim

	addobject LOCALID_MOM
	applymovement LOCALID_MOM, Littleroot_Move_MomExitHouse
	waitmovement 0

	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10

	checkplayergender
	call_if_eq VAR_RESULT, MALE, Littleroot_Evt_GoInsideWithMom_MomApproachPlayer_Male
	call_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GoInsideWithMom_MomApproachPlayer_Female
	waitmovement 0

	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage

	checkplayergender
	call_if_eq VAR_RESULT, MALE, Littleroot_Evt_GoInsideWithMom_MomApproachDoor_Male
	call_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GoInsideWithMom_MomApproachDoor_Female
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0

	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomEnterHouse
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Littleroot_Evt_GoInsideWithMom_PlayerEnterHouseMale
	call_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GoInsideWithMom_PlayerEnterHouseFemale
	waitmovement 0
	
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

Littleroot_Evt_GoInsideWithMom_MomApproachPlayer_Male::
	applymovement LOCALID_MOM, Littleroot_Move_Mom_ApproachPlayerAtTruck
	return
	
Littleroot_Evt_GoInsideWithMom_MomApproachPlayer_Female::
	applymovement LOCALID_MOM, Littleroot_Move_Mom_ApproachPlayerAtTruckLong
	return

Littleroot_Evt_GoInsideWithMom_MomApproachDoor_Male::
	applymovement LOCALID_MOM, Littleroot_Move_Mom_ApproachDoor
	return

Littleroot_Evt_GoInsideWithMom_MomApproachDoor_Female::
	applymovement LOCALID_MOM, Littleroot_Move_Mom_ApproachDoorLong
	return

Littleroot_Evt_GoInsideWithMom_PlayerEnterHouseMale::
	applymovement OBJ_EVENT_ID_PLAYER, Littleroot_Move_Player_EnterHouse
	return

Littleroot_Evt_GoInsideWithMom_PlayerEnterHouseFemale::
	applymovement OBJ_EVENT_ID_PLAYER, Littleroot_Move_Player_EnterHouseLong
	return

Littleroot_Move_MomExitHouse:
	walk_down
	step_end

Littleroot_Move_Mom_ApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

Littleroot_Move_Mom_ApproachPlayerAtTruckLong:
	walk_down
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

Littleroot_Move_Mom_ApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

Littleroot_Move_Mom_ApproachDoorLong:
	delay_16
	delay_8
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

Littleroot_Move_Player_EnterHouse:
	walk_up
	walk_up
	step_end

Littleroot_Move_Player_EnterHouseLong:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Littleroot_Move_Player_StepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

@ @@ Footprints investigator blocks the path before talking to May/Brandon for the first time.
   @ left -> player passes through the left tile. right -> right tile.
Littleroot_Evt_BlockPathFootprints_Left::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Littleroot_Move_Player_StepBack
	applymovement LOCALID_FOOTPRINTS_MAN, Littleroot_Move_FootprintsMan_StepBackToLeft
	waitmovement 0
	msgbox Littleroot_Tx_FootprintsMan_DontComeInHere
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Littleroot_Move_FootprintsMan_ReturnFromLeft
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_LOOK_AROUND
	end

Littleroot_Evt_BlockPathFootprints_Right::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Littleroot_Move_Player_StepBack
	applymovement LOCALID_FOOTPRINTS_MAN, Littleroot_Move_FootprintsMan_StepBackToRight
	waitmovement 0
	msgbox Littleroot_Tx_FootprintsMan_DontComeInHere
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Littleroot_Move_FootprintsMan_ReturnFromRight
	setobjectmovementtype LOCALID_FOOTPRINTS_MAN, MOVEMENT_TYPE_LOOK_AROUND
	end
	
Littleroot_Move_Player_StepBack:
	delay_8
	walk_down
	step_end

Littleroot_Move_FootprintsMan_StepBackToLeft:
	walk_fast_left
	walk_in_place_faster_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Littleroot_Move_FootprintsMan_StepBackToRight:
	walk_fast_right
	walk_in_place_faster_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

Littleroot_Move_FootprintsMan_ReturnFromLeft:
	walk_right
	walk_up
	step_end

Littleroot_Move_FootprintsMan_ReturnFromRight:
	walk_left
	walk_up
	step_end

Littleroot_Tx_FootprintsMan_DontComeInHere:
	.string "Aaaaah! Wait!\n"
	.string "Please don't come in here.\p"
	.string "I just discovered the footprints of\n"
	.string "a rare Pokémon!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

@ @@ Footprints investigator asks you for help.
@ The event triggered by talking to Footprints guy directly.
Littleroot_Evt_GoSaveBirch::
	special GetPlayerBigGuyGirlString
	msgbox Littleroot_Tx_GoSaveBirchTrigger_CanYouGoSee, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

@ The event triggered by stepping into a trigger.
Littleroot_Evt_GoSaveBirchTrigger::
	lockall
	@applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FacePlayer
	waitmovement 0
	@applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox Littleroot_Tx_GoSaveBirchTrigger_CanYouGoSee, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_YouSavedBirch::
	special GetPlayerBigGuyGirlString
	msgbox Littleroot_Tx_FootprintsMan_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

Littleroot_Tx_GoSaveBirchTrigger_CanYouGoSee:
	.string "Um, hi\p"
	.string "I can hear someone screaming outside!\n"
	.string "I want to go see what's going on,\l"
	.string "but I'm too scared of wild Pokémon!\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

Littleroot_Tx_FootprintsMan_YouSavedBirch:
	.string "You saved Prof. Birch!\n"
	.string "I'm so glad!\p"
	.string "About the footprints I was\n"
	.string "investigating before…\p"
	.string "I think they were my own footprints.\n"
	.string "Haha…$"

@ @@ Mom gives you shoes when you talk to her.
Littleroot_Evt_Mom::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Littleroot_Evt_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_SetHomeDoorCoordsFemale
	call Littleroot_Evt_GiveRunningShoes
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, Littleroot_Move_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto Littleroot_Evt_SetReceivedRunningShoes
	end

@ @@ Mom gives you shoes

Littleroot_Evt_GiveShoesTriggerMaleRight1::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleRight1
	release
	end
Littleroot_Evt_GiveShoesTriggerMaleRight2::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleRight2
	release
	end
Littleroot_Evt_GiveShoesTriggerMaleRight3::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleRight3
	release
	end
Littleroot_Evt_GiveShoesTriggerMaleRight4::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleRight4
	release
	end

Littleroot_Evt_GiveShoesTriggerMaleLeft1::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleLeft1
	release
	end
Littleroot_Evt_GiveShoesTriggerMaleLeft2::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleLeft2
	release
	end
Littleroot_Evt_GiveShoesTriggerMaleLeft3::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Littleroot_Evt_GiveShoesMaleLeft3
	release
	end

Littleroot_Evt_GiveShoesTriggerFemale1::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GiveShoesFemale1
	release
	end
Littleroot_Evt_GiveShoesTriggerFemale2::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GiveShoesFemale2
	release
	end
Littleroot_Evt_GiveShoesTriggerFemale3::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, Littleroot_Evt_GiveShoesFemale3
	release
	end

Littleroot_Evt_GiveShoesMaleRight1::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleRight1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleRight1
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesMaleRight2::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleRight2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleRight2
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesMaleRight3::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleRight3
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleRight3
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesMaleRight4::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleRight4
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleRight4
	goto Littleroot_Evt_SetReceivedRunningShoes
	end

Littleroot_Evt_GiveShoesMaleLeft1::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleLeft1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleLeft1
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesMaleLeft2::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleLeft2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleLeft2
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesMaleLeft3::
	call Littleroot_Evt_GiveShoesMale_StepA
	call Littleroot_Evt_MomApproachMaleLeft3
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	call Littleroot_Evt_GiveShoesMale_StepB
	call Littleroot_Evt_MomReturnHomeMaleLeft3
	goto Littleroot_Evt_SetReceivedRunningShoes
	end

Littleroot_Evt_GiveShoesFemale1::
	call Littleroot_Evt_GiveShoesFemale_StepA
	call Littleroot_Evt_MomApproachFemale1
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	call Littleroot_Evt_GiveShoesFemale_StepB
	call Littleroot_Evt_MomReturnHomeFemale1
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesFemale2::
	call Littleroot_Evt_GiveShoesFemale_StepA
	call Littleroot_Evt_MomApproachFemale2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	call Littleroot_Evt_GiveShoesFemale_StepB
	call Littleroot_Evt_MomReturnHomeFemale2
	goto Littleroot_Evt_SetReceivedRunningShoes
	end
Littleroot_Evt_GiveShoesFemale3::
	call Littleroot_Evt_GiveShoesFemale_StepA
	call Littleroot_Evt_MomApproachFemale3
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	call Littleroot_Evt_GiveShoesFemale_StepB
	call Littleroot_Evt_MomReturnHomeFemale3
	goto Littleroot_Evt_SetReceivedRunningShoes
	end

Littleroot_Evt_GiveShoesMale_StepA::
	lockall
	call Littleroot_Evt_SetHomeDoorCoordsMale
	call Littleroot_Evt_MomNoticePlayer
	msgbox Littleroot_Tx_WaitPlayerGetShoes, MSGBOX_DEFAULT
	closemessage
	return

Littleroot_Evt_GiveShoesMale_StepB::
	waitmovement 0
	call Littleroot_Evt_GiveRunningShoes
	return

Littleroot_Evt_GiveShoesFemale_StepA::
	lockall
	call Littleroot_Evt_SetHomeDoorCoordsFemale
	call Littleroot_Evt_MomNoticePlayer
	msgbox Littleroot_Tx_WaitPlayerGetShoes, MSGBOX_DEFAULT
	closemessage
	return

Littleroot_Evt_GiveShoesFemale_StepB::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	call Littleroot_Evt_GiveRunningShoes
	return

Littleroot_Evt_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 12
	setvar VAR_0x800A, 20
	return

Littleroot_Evt_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 25
	setvar VAR_0x800A, 21
	return

Littleroot_Evt_MomNoticePlayer::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

Littleroot_Evt_MomApproachMaleRight1::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleRight1
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleRight1:
	walk_right
	walk_right
	walk_right
	walk_in_place_up
	step_end

Littleroot_Evt_MomApproachMaleRight2::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleRight2
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleRight2:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_up
	step_end

Littleroot_Evt_MomApproachMaleRight3::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleRight3
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleRight3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_up
	step_end

Littleroot_Evt_MomApproachMaleRight4::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleRight4
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleRight4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_up
	step_end

Littleroot_Evt_MomApproachMaleLeft1::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleLeft1
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleLeft1:
	walk_in_place_down
	step_end

Littleroot_Evt_MomApproachMaleLeft2::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleLeft2
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleLeft2:
	walk_down
	walk_in_place_down
	step_end

Littleroot_Evt_MomApproachMaleLeft3::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerMaleLeft3
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerMaleLeft3:
	walk_down
	walk_down
	walk_in_place_down
	step_end

Littleroot_Evt_MomApproachFemale1::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerFemale1
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerFemale1:
	walk_down
	walk_down
	walk_in_place_right
	step_end

Littleroot_Evt_MomApproachFemale2::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerFemale2
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerFemale2:
	walk_down
	walk_down
	walk_down
	walk_in_place_right
	step_end

Littleroot_Evt_MomApproachFemale3::
	applymovement LOCALID_MOM, Littleroot_Move_MomApproachPlayerFemale3
	waitmovement 0
	return

Littleroot_Move_MomApproachPlayerFemale3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_right
	step_end

Littleroot_Tx_WaitPlayerGetShoes:
	.string "MOM: Wait, {PLAYER}!$"

Littleroot_Evt_GiveRunningShoes::
	msgbox Littleroot_Tx_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message Littleroot_Tx_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES

	msgbox Littleroot_Tx_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox Littleroot_Tx_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage

	delay 30
	return

Littleroot_Tx_WearTheseRunningShoes:
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to Prof. Birch?\p"
	.string "Oh! What an adorable Pokémon!\n"
	.string "You got it from Prof. Birch. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with Pokémon!\p"
	.string "Here, honey! If you're going out on an\n"
	.string "adventure, wear these Running Shoes.\p"
	.string "They'll put a zip in your step!$"

Littleroot_Tx_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

Littleroot_Tx_ExplainRunningShoes:
	.string "MOM: {PLAYER}, those shoes came with\n"
	.string "instructions.\p"
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"

Littleroot_Tx_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "To think that you have your very own\n"
	.string "POKéMON now…\l"
	.string "Your father will be overjoyed.\p"
	.string "…But please be careful.\n"
	.string "If anything happens, you can come home.\p"
	.string "Go on, go get them, honey!$"

Littleroot_Evt_MomReturnHomeMaleRight1::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleRight1
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleRight1:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleRight2::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleRight2
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleRight2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleRight3::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleRight3
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleRight3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleRight4::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleRight4
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleRight4:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleLeft1::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleLeft1
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleLeft1:
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleLeft2::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleLeft2
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleLeft2:
	walk_up
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeMaleLeft3::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeMaleLeft3
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeMaleLeft3:
	walk_up
	walk_up
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeFemale1::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeFemale1
	goto Littleroot_Evt_MomReturnHome_StepA
	return
	
Littleroot_Move_MomReturnHomeFemale1:
	walk_up
	walk_up
	walk_in_place_faster_up
	step_end

Littleroot_Evt_MomReturnHomeFemale2::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeFemale2
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Move_MomReturnHomeFemale2:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_up
	step_end
Littleroot_Evt_MomReturnHomeFemale3::
	applymovement LOCALID_MOM, Littleroot_Move_MomReturnHomeFemale3
	goto Littleroot_Evt_MomReturnHome_StepA
	return

Littleroot_Evt_MomReturnHome_StepA::
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, Littleroot_Move_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return
	
Littleroot_Move_MomReturnHomeFemale3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_up
	step_end	

Littleroot_Move_MomExitThroughDoor:
	walk_up
	step_end

Littleroot_Evt_SetReceivedRunningShoes::
	removeobject LOCALID_MOM
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

@@@@@@@@@@@@@@@@@@@@@@@
@@@ here be dragons @@@
@@@@@@@@@@@@@@@@@@@@@@@

LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale::
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_MOM, 25, 21
	return

LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetMomInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_MOM, 12, 21
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_MOM, 25, 22
	return

LittlerootTown_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade::
	addobject LOCALID_BIRCH
	addobject LOCALID_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale::
	setobjectxy LOCALID_RIVAL, 6, 10
	setobjectxy LOCALID_BIRCH, 5, 10
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale::
	setobjectxy LOCALID_RIVAL, 13, 10
	setobjectxy LOCALID_BIRCH, 14, 10
	end

LittlerootTown_EventScript_GoodLuck::
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_NeedPokemonTriggerCenter::
	lockall
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon::
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FOOTPRINTS_MAN, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_BirchsHouseSignMale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_Text_OurNewHomeLetsGoInside:
	.string "MOM: {PLAYER}, we're here, honey!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is LITTLEROOT TOWN.\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Um, um, um!\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "LITTLEROOT TOWN\n"
	.string "“A town that can't be shaded any hue.”\p"
	.string "{RIGHT_ARROW} Prof. Birch's Laboratory.$"

LittlerootTown_Text_ProfBirchsLab:
	.string "PROF. BIRCH'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

LittlerootTown_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

LittlerootTown_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

