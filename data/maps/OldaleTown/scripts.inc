.set LOCALID_MART_EMPLOYEE, 2
.set LOCALID_TWIN, 3
.set LOCALID_RIVAL, 4

OldaleTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldaleTown_OnTransition
	.byte 0

OldaleTown_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	setflag FLAG_VISITED_OLDALE_TOWN
	call_if_unset FLAG_ADVENTURE_STARTED, Oldale_Evt_TwinBlockPath
	call_if_unset FLAG_RECEIVED_POTION_OLDALE, OldaleTown_EventScript_MoveMartEmployee
	call_if_set FLAG_ADVENTURE_STARTED, OldaleTown_EventScript_SetOldaleState
	end

@ ===================================================== @
@ =====================  OnEvents ===================== @
@ ===================================================== @
Oldale_Evt_TwinBlockPath::
	setobjectxyperm LOCALID_TWIN, 22, 30
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_LOOK_AROUND
	return
	
@ ==================================================== @
@ ================= NPC Interactions ================= @
@ ==================================================== @
Oldale_Evt_Twin::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Oldale_Evt_Twin_NotBlockingPath
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_FollowRival

	checkplayergender
	call_if_eq VAR_RESULT, MALE, Oldale_Evt_ImLookingForSomeone_Male
	call_if_eq VAR_RESULT, FEMALE, Oldale_Evt_ImLookingForSomeone_Female

	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

	Oldale_Evt_ImLookingForSomeone_Male::
		msgbox Oldale_Tx_ImLookingForSomeoneMale, MSGBOX_DEFAULT
		closemessage
		return

	Oldale_Evt_ImLookingForSomeone_Female::
		msgbox Oldale_Tx_ImLookingForSomeoneFemale, MSGBOX_DEFAULT
		closemessage
		return

		Oldale_Tx_ImLookingForSomeoneMale:
			.string "A girl that told me to talk\n"
			.string "to some boy if I saw him.\p"
			.string "But I don't know how I'll\n"
			.string "recognize that boy if I see him!$"

		Oldale_Tx_ImLookingForSomeoneFemale:
			.string "A boy that told me to talk\n"
			.string "to some girl if I saw her.\p"
			.string "But I don't know how I'll\n"
			.string "recognize that girl if I see her!$"

	Oldale_Evt_Twin_FollowRival::
		msgbox Oldale_Tx_YouShouldFollowRival, MSGBOX_DEFAULT
		release
		end

		Oldale_Tx_YouShouldFollowRival:
			.string "You should go with your friend.\p"
			.string "Making people wait is rude.$"

	Oldale_Evt_Twin_NotBlockingPath::
		msgbox Oldale_Tx_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
		release
		end

		Oldale_Tx_GoodLuckCatchingPokemon:
			.string "Are you going to catch POKéMON?\n"
			.string "Good luck!$"

Oldale_Evt_MartEmployee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_POTION_OLDALE, Oldale_Evt_ExplainPotion
	goto_if_set FLAG_TEMP_1, Oldale_Evt_ExplainPotion
	setflag FLAG_TEMP_1
	playbgm MUS_FOLLOW_ME, FALSE
	msgbox Oldale_Tx_IWorkAtPokemonMart, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, Oldale_Evt_GoToMartNorth
	case DIR_EAST, Oldale_Evt_GoToMartEast
	goto Oldale_Evt_GoToMartEast
	end

	Oldale_Tx_IWorkAtPokemonMart:
		.string "Hi!\n"
		.string "I work at a Pokémon Mart.\p"
		.string "Can I get you to come with me?$"

	Oldale_Tx_ThisIsAPokemonMart:
		.string "This is a Pokémon Mart.\n"
		.string "Just look for our blue roof.\p"
		.string "We sell a variety of goods including\n"
		.string "Poké Balls for catching Pokémon.\p"
		.string "Here, I'd like you to have this as\n"
		.string "a promotional item.$"

	Oldale_Tx_PotionExplanation:
		.string "A Potion can be used anytime, so it's\n"
		.string "even more useful than a Pokémon Center\l"
		.string "in certain situations.$"

	Oldale_Evt_GoToMartNorth::
		applymovement LOCALID_MART_EMPLOYEE, Oldale_Move_EmployeeNorth
		applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_PlayerNorth
		waitmovement 0
		goto Oldale_Evt_ExplainPokemonMart
		end

		Oldale_Move_EmployeeNorth:
			walk_down
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_in_place_faster_up
			step_end

		Oldale_Move_PlayerNorth:
			lock_facing_direction
			walk_down
			unlock_facing_direction
			walk_up
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_right
			walk_right
			walk_right
			walk_right
			walk_in_place_faster_up
			step_end

	Oldale_Evt_GoToMartEast::
		applymovement LOCALID_MART_EMPLOYEE, Oldale_Move_EmployeeEast
		applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_PlayerEast
		waitmovement 0
		goto Oldale_Evt_ExplainPokemonMart
		end

		Oldale_Move_EmployeeEast:
			walk_down
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_in_place_faster_up
			step_end

		Oldale_Move_PlayerEast:
			walk_down
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_right
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_up
			walk_right
			walk_right
			walk_right
			walk_right
			walk_in_place_faster_up
			step_end

	Oldale_Evt_ExplainPokemonMart::
		msgbox Oldale_Tx_ThisIsAPokemonMart, MSGBOX_DEFAULT
		giveitem ITEM_POTION
		goto_if_eq VAR_RESULT, FALSE, OldaleTown_EventScript_BagIsFull
		msgbox Oldale_Tx_PotionExplanation, MSGBOX_DEFAULT
		setflag FLAG_RECEIVED_POTION_OLDALE
		fadedefaultbgm
		release
		end

	Oldale_Evt_ExplainPotion::
		msgbox Oldale_Tx_PotionExplanation, MSGBOX_DEFAULT
		release
		end

@ ==================================================== @
@ ================== Trigger events ================== @
@ ==================================================== @
Oldale_Evt_RivalIsLookingForYou1::
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_BlockPathFollowRival
	call Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GetBehindTwin1
	waitmovement 0
	
	call Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove
	end

Oldale_Evt_RivalIsLookingForYou2::
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_BlockPathFollowRival
	call Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GetBehindTwin2
	waitmovement 0
	
	call Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove
	end

Oldale_Evt_RivalIsLookingForYou3::
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_BlockPathFollowRival
	call Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GetBehindTwin3
	waitmovement 0
	
	call Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove
	end

Oldale_Evt_RivalIsLookingForYou4::
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_BlockPathFollowRival
	call Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GetBehindTwin4
	waitmovement 0
	
	call Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove
	end

Oldale_Evt_RivalIsLookingForYou5::
	goto_if_set FLAG_FIRST_RIVAL_BATTLE_FOUGHT, Oldale_Evt_Twin_BlockPathFollowRival
	call Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GetBehindTwin5
	waitmovement 0
	
	call Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove
	end

Oldale_Evt_RivalIsLookingForYou_BeforePlayerMove::
	lockall
	playse SE_PIN
	applymovement LOCALID_TWIN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_TWIN, Oldale_Move_Twin_NoticePlayer
	waitmovement 0

	checkplayergender
	call_if_eq VAR_RESULT, MALE, Oldale_Evt_RivalIsLookingForYou_TexMale
	call_if_eq VAR_RESULT, FEMALE, Oldale_Evt_RivalIsLookingForYou_TexFemale
	closemessage
	return

Oldale_Evt_RivalIsLookingForYou_AfterPlayerMove::
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_TWIN, Oldale_Move_Twin_GuidedToRival
	applymovement OBJ_EVENT_ID_PLAYER, Oldale_Move_Player_GuidedToRival
	waitmovement 0

	checkplayergender
	call_if_eq VAR_RESULT, MALE, Oldale_Evt_RivalIsThatWay_TexMale
	call_if_eq VAR_RESULT, FEMALE, Oldale_Evt_RivalIsThatWay_TexFemale
	closemessage

	applymovement LOCALID_TWIN, Oldale_Move_Twin_ReturnToBlockingSpot
	waitmovement 0
	setobjectxy LOCALID_TWIN, 22, 30
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_LOOK_AROUND
	fadedefaultbgm
	return

Oldale_Evt_RivalIsLookingForYou_TexMale::
	msgbox Oldale_Tx_SomeoneWasLookingForYouMale
	return
Oldale_Evt_RivalIsLookingForYou_TexFemale::
	msgbox Oldale_Tx_SomeoneWasLookingForYouFemale
	return

Oldale_Evt_RivalIsThatWay_TexMale::
	msgbox Oldale_Tx_TheyAreThatWayMale
	return
Oldale_Evt_RivalIsThatWay_TexFemale::
	msgbox Oldale_Tx_TheyAreThatWayFemale
	return

	

Oldale_Evt_RivalTellsYouToGoToLab::
	lockall
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
	waitmovement 0
	setvar VAR_0x8009, 0
	goto Oldale_Evt_RivalGoLabMessage
	end

Oldale_Evt_RivalTellsYouToGoToLabTrigger1::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto Oldale_Evt_RivalGoLabMessage
	end

Oldale_Evt_RivalTellsYouToGoToLabTrigger2::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer2
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto Oldale_Evt_RivalGoLabMessage
	end

Oldale_Evt_RivalTellsYouToGoToLabTrigger3::
	lockall
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalApproachPlayer3
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	setvar VAR_0x8009, 1
	goto Oldale_Evt_RivalGoLabMessage
	end

Oldale_Evt_RivalGoLabMessage::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Oldale_Evt_RivalGoLabMessageMale
	goto_if_eq VAR_RESULT, FEMALE, Oldale_Evt_RivalGoLabMessageFemale
	end

Oldale_Evt_RivalGoLabMessageMale::
	msgbox Oldale_Tx_LetsGoBackToLabMale, MSGBOX_DEFAULT
	goto Oldale_Evt_RivalTellsYouToGoToLabFinish
	end

Oldale_Tx_LetsGoBackToLabMale:
	.string "MAY: {PLAYER}{KUN}!\n"
	.string "Over here!\p"
	.string "After such a battle, you should pay\n"
	.string "a visit to the Pokémon center.\p"
	.string "Then hurry to my father's lab,\n"
	.string "I'll be waiting you!$"

Oldale_Evt_RivalGoLabMessageFemale::
	msgbox Oldale_Tx_LetsGoBackToLabFemale, MSGBOX_DEFAULT
	goto Oldale_Evt_RivalTellsYouToGoToLabFinish
	end

Oldale_Tx_LetsGoBackToLabFemale:
	.string "BRENDAN: Just healed my Pokémon in\n"
	.string "the Pokémon Center.\p"
	.string "I'll be heading back to my dad's\n"
	.string "LAB now.\p"
	.string "You should come too, {PLAYER}!\n"
	.string "I'll be waiting for you.$"

Oldale_Evt_RivalTellsYouToGoToLabFinish::
	closemessage
	call_if_eq VAR_0x8009, 0, OldaleTown_EventScript_DoExitMovement1
	call_if_eq VAR_0x8009, 1, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	removeobject LOCALID_RIVAL
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	releaseall
	end

OldaleTown_EventScript_DoExitMovement1::
	goto_if_ne VAR_FACING, DIR_SOUTH, OldaleTown_EventScript_DoExitMovement2
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

OldaleTown_EventScript_DoExitMovement2::
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_WatchRivalExit
	applymovement LOCALID_RIVAL, OldaleTown_Movement_RivalExit
	waitmovement 0
	return

Oldale_Move_Twin_NoticePlayer:
	delay_8
    face_left
	disable_jump_landing_ground_effect
	jump_in_place_left
	step_end

Oldale_Move_Player_GetBehindTwin1:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

Oldale_Move_Player_GetBehindTwin2:
	walk_down
	walk_right
	walk_right
	step_end

Oldale_Move_Player_GetBehindTwin3:
	walk_right
	walk_right
	step_end

Oldale_Move_Player_GetBehindTwin4:
	walk_up
	walk_right
	walk_right
	step_end

Oldale_Move_Player_GetBehindTwin5:
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Oldale_Move_Twin_GuidedToRival:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
    walk_right
	face_up
	step_end

Oldale_Move_Player_GuidedToRival:
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

Oldale_Move_Twin_ReturnToBlockingSpot:
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
	walk_left
	walk_left
	step_end

Oldale_Tx_SomeoneWasLookingForYouMale:
	.string "Hey, you!\p"
	.string "A girl told me to look out for\n"
	.string "some boy. I think it may be you!\p"
	.string "She went that way I think,\n"
	.string "Let me show you.$"
Oldale_Tx_SomeoneWasLookingForYouFemale:
	.string "Hey, you!\p"
	.string "A boy told me to look out for\n"
	.string "some girl. I think it may be you!\p"
	.string "She went that way I think,\n"
	.string "Let me show you.$"
Oldale_Tx_TheyAreThatWayMale:
	.string "Yes, she went in that direction.\n"
	.string "She looked happy that you'd come.$"
Oldale_Tx_TheyAreThatWayFemale:
	.string "Yes, he went in that direction.\n"
	.string "He looked happy that you'd come.$"

Oldale_Evt_Twin_BlockPathFollowRival::
	lockall
	playse SE_PIN
	applymovement LOCALID_TWIN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_TWIN, Oldale_Move_Twin_NoticePlayer
	waitmovement 0

	msgbox Oldale_Tx_YouShouldFollowRival, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight
	return

OldaleTown_EventScript_BlockedPath::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, OldaleTown_Movement_PlayerStepBack
	applymovement LOCALID_TWIN, OldaleTown_Movement_BackUp
	waitmovement 0
	msgbox OldaleTown_Text_WaitDontComeInHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, OldaleTown_Movement_ReturnToOriginalPosition
	waitmovement 0
	releaseall
	end

@@@@@@@@@@@@@@@@@@@@@@@
@@@ here be dragons @@@
@@@@@@@@@@@@@@@@@@@@@@@

@ This script seems pointless because nothing uses VAR_OLDALE_TOWN_STATE
OldaleTown_EventScript_SetOldaleState::
	setvar VAR_OLDALE_TOWN_STATE, 1
	return

OldaleTown_EventScript_MoveMartEmployee::
	setobjectxyperm LOCALID_MART_EMPLOYEE, 24, 28
	setobjectmovementtype LOCALID_MART_EMPLOYEE, MOVEMENT_TYPE_FACE_DOWN
	return

OldaleTown_EventScript_CitySign::
	msgbox OldaleTown_Text_CitySign, MSGBOX_SIGN
	end

OldaleTown_EventScript_Girl::
	msgbox OldaleTown_Text_SavingMyProgress, MSGBOX_NPC
	end

OldaleTown_EventScript_BagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	fadedefaultbgm
	release
	end

OldaleTown_Movement_Unknown1:
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_Unknown2:
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

OldaleTown_Movement_RivalApproachPlayer1:
	walk_left
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer2:
	walk_left
	step_end

OldaleTown_Movement_RivalApproachPlayer3:
	face_left
	step_end

OldaleTown_Movement_RivalExit:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

OldaleTown_Movement_WatchRivalExit:
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

OldaleTown_Movement_PlayerStepBack:
	delay_8
	walk_right
	step_end

OldaleTown_Movement_BackUp:
	walk_fast_up
	walk_in_place_faster_left
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

OldaleTown_Movement_ReturnToOriginalPosition:
	walk_down
	walk_left
	step_end

OldaleTown_Text_SavingMyProgress:
	.string "I want to take a rest, so I'm saving my\n"
	.string "progress.$"

OldaleTown_Text_WaitDontComeInHere:
	.string "Aaaaah! Wait!\n"
	.string "Please don't come in here.\p"
	.string "I just discovered the footprints of\n"
	.string "a rare POKéMON!\p"
	.string "Wait until I finish sketching\n"
	.string "them, okay?$"

OldaleTown_Text_CitySign:
	.string "OLDALE TOWN\n"
	.string "“Where things start off scarce.”$"

